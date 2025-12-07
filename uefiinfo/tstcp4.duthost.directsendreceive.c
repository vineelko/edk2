/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tstcp4.duthost.directsendreceive.c

Abstract:

    This module implements tcp4 dut + host test suite

Author:

    Vineel Kovvuri (vineelko) 10-Aug-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"
#include "protocols.h"
#include "testsuites.h"

#include "network_config.h"
#include "utils.h"

#define CLIENT_TX_DATA_SIZE 1024
#define CLIENT_RX_DATA_SIZE 1024
#define CLIENT_TX_BYTE      0xC1

#define SERVER_TX_DATA_SIZE 1024
#define SERVER_RX_DATA_SIZE 1024
#define SERVER_TX_BYTE      0x51

#define DHCP_OPTION_PARAMETER_REQUEST_LIST 55
#define DHCP_RETRIES                       4

static PBM_PROTOCOL_INFO gProtocolArray;
static CHAR8* gHostArguments;

static ENUM_TO_STRING Dhcp4StateMap[] = {
    {Dhcp4Stopped, STRINGIFY(Dhcp4Stopped)},
    {Dhcp4Init, STRINGIFY(Dhcp4Init)},
    {Dhcp4Selecting, STRINGIFY(Dhcp4Selecting)},
    {Dhcp4Requesting, STRINGIFY(Dhcp4Requesting)},
    {Dhcp4Bound, STRINGIFY(Dhcp4Bound)},
    {Dhcp4Renewing, STRINGIFY(Dhcp4Renewing)},
    {Dhcp4Rebinding, STRINGIFY(Dhcp4Rebinding)},
    {Dhcp4InitReboot, STRINGIFY(Dhcp4InitReboot)},
    {Dhcp4Rebooting, STRINGIFY(Dhcp4Rebooting)},
};

static ENUM_TO_STRING Tcp4StateMap[] = {
    {Tcp4StateClosed, STRINGIFY(Tcp4StateClosed)},
    {Tcp4StateListen, STRINGIFY(Tcp4StateListen)},
    {Tcp4StateSynSent, STRINGIFY(Tcp4StateSynSent)},
    {Tcp4StateSynReceived, STRINGIFY(Tcp4StateSynReceived)},
    {Tcp4StateEstablished, STRINGIFY(Tcp4StateEstablished)},
    {Tcp4StateFinWait1, STRINGIFY(Tcp4StateFinWait1)},
    {Tcp4StateFinWait2, STRINGIFY(Tcp4StateFinWait2)},
    {Tcp4StateClosing, STRINGIFY(Tcp4StateClosing)},
    {Tcp4StateTimeWait, STRINGIFY(Tcp4StateTimeWait)},
    {Tcp4StateCloseWait, STRINGIFY(Tcp4StateCloseWait)},
    {Tcp4StateLastAck, STRINGIFY(Tcp4StateLastAck)},
};

typedef struct _BM_TCP4_SOCKET {
    EFI_TCP4_PROTOCOL* Protocol;
    EFI_TCP4_CONNECTION_STATE State;
    EFI_TCP4_CONFIG_DATA ConfigData;
    EFI_TCP4_OPTION Options;
    EFI_TCP4_IO_TOKEN TransmitToken;
    EFI_TCP4_IO_TOKEN ReceiveToken;
    EFI_TCP4_TRANSMIT_DATA TransmitData;
    EFI_TCP4_RECEIVE_DATA ReceiveData;
} BM_TCP4_SOCKET;

typedef struct _BM_TCP4_CLIENT {
    BM_TCP4_SOCKET;
    EFI_TCP4_CONNECTION_TOKEN ConnectToken;
    BOOLEAN Connected;
    BOOLEAN Transmitted;
    BOOLEAN Received;
    BOOLEAN DataVerified;
} BM_TCP4_CLIENT, *PBM_TCP4_CLIENT;

typedef struct _BM_TCP4_CONTEXT {
    BM_TCP4_CLIENT Client;

    //
    // WaitForAcceptConnection event is used to stall main thread to wait until
    // both client and server finish 3 way handshake with Accept() from server
    // and Connect() from client
    //

    EFI_EVENT WaitForAcceptConnection;

    //
    // WaitForClientTransmitServerReceive event is used to stall main thread to wait
    // until both client and server Transmit() data from client and Receive()
    // from server
    //

    EFI_EVENT WaitForClientTransmitServerReceive;

    //
    // WaitForServerTransmitClientReceive event is used to stall main thread to wait
    // until both server and client Transmit() data from server and Receive()
    // from client
    //

    EFI_EVENT WaitForServerTransmitClientReceive;

} BM_TCP4_CONTEXT, *PBM_TCP4_CONTEXT;

static VOID EFIAPI Tcp4AcceptConnectionWaitCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);
}

static VOID EFIAPI Tcp4ClientConnectCallback(_In_ EFI_EVENT Event, _In_ PVOID _Context)
{
    PBM_TCP4_CONTEXT Context = _Context;
    PBM_TCP4_CLIENT Client = &Context->Client;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("Triggered Connect callback");

    Client->Connected = TRUE;

    gBS->SignalEvent(Context->WaitForAcceptConnection);
}

static EFI_STATUS Tcp4ConnectToServer(_In_ PBM_TCP4_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_TCP4_CLIENT Client = &Context->Client;

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientConnectCallback,
                              Context,
                              &Client->ConnectToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Client->Protocol->Connect(Client->Protocol, &Client->ConnectToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Connect() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

//
// Client/Server transmit/receive methods
//

static VOID EFIAPI Tcp4ClientTransmitServerReceiveWaitCallback(_In_ EFI_EVENT Event,
                                                               _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Tcp4ServerTransmitClientReceiveWaitCallback(_In_ EFI_EVENT Event,
                                                               _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Tcp4ClientTransmitCallback(_In_ EFI_EVENT Event, _In_ PVOID _Context)
{
    PBM_TCP4_CONTEXT Context = _Context;
    PBM_TCP4_CLIENT Client = &Context->Client;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("   Triggered client transmit callback");

    //
    // Signal the wait event when client transmit is done
    //

    Client->Transmitted = TRUE;
    gBS->SignalEvent(Context->WaitForClientTransmitServerReceive);
}

static VOID EFIAPI Tcp4ClientReceiveCallback(_In_ EFI_EVENT Event, _In_ PVOID _Context)
{
    PBM_TCP4_CONTEXT Context = _Context;
    EFI_TCP4_RECEIVE_DATA* ClientRxData = NULL;
    PBM_TCP4_CLIENT Client = &Context->Client;

    UNREFERENCED_PARAMETER(Event);

    ClientRxData = Client->ReceiveToken.Packet.RxData;

    DBG_INFO("   Triggered client receive callback");

    //
    // Lets read it and verify it to be SERVER_TX_BYTE
    //

    Client->DataVerified = TRUE;
    if (ClientRxData->DataLength != CLIENT_RX_DATA_SIZE) {
        DBG_ERROR("Expected %u bytes from server. Only got %u bytes",
                  CLIENT_RX_DATA_SIZE,
                  ClientRxData->DataLength);
        Client->DataVerified = FALSE;
    }

    for (UINTN i = 0; i < CLIENT_RX_DATA_SIZE; i++) {
        UINT8* TxBuffer = ClientRxData->FragmentTable[0].FragmentBuffer;
        if (TxBuffer[i] != SERVER_TX_BYTE) {
            Client->DataVerified = FALSE;
            break;
        }
    }

    Client->Received = TRUE;
    gBS->SignalEvent(Context->WaitForServerTransmitClientReceive);
}

static EFI_STATUS Tcp4TransmitAndReceiveData(_In_ PBM_TCP4_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Index = 0;
    EFI_TCP4_TRANSMIT_DATA* ClientTxData = NULL;
    EFI_TCP4_RECEIVE_DATA* ClientRxData = NULL;
    PBM_TCP4_CLIENT Client = &Context->Client;

    ClientTxData = &Client->TransmitData;
    ClientRxData = &Client->ReceiveData;

    //
    // Setup client tx buffers
    //

    ClientTxData->DataLength = CLIENT_TX_DATA_SIZE;
    ClientTxData->FragmentCount = 1;
    ClientTxData->FragmentTable[0].FragmentLength = ClientTxData->DataLength;
    ClientTxData->FragmentTable[0].FragmentBuffer = AllocateZeroPool(ClientTxData->DataLength);
    if (ClientTxData->FragmentTable[0].FragmentBuffer == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  ClientTxData->DataLength);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    SetMem(ClientTxData->FragmentTable[0].FragmentBuffer, CLIENT_TX_DATA_SIZE, CLIENT_TX_BYTE);

    //
    // Setup client rx buffers
    //

    ClientRxData->DataLength = CLIENT_RX_DATA_SIZE; // overwritten by the network driver on receive
    ClientRxData->FragmentCount = 1;
    ClientRxData->FragmentTable[0].FragmentLength = ClientRxData->DataLength;
    ClientRxData->FragmentTable[0].FragmentBuffer = AllocateZeroPool(ClientRxData->DataLength);
    if (ClientRxData->FragmentTable[0].FragmentBuffer == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  ClientRxData->DataLength);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Setup client tx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientTransmitCallback,
                              Context,
                              &Client->TransmitToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Client->TransmitToken.Packet.TxData = &Client->TransmitData;

    //
    // Setup client rx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientReceiveCallback,
                              Context,
                              &Client->ReceiveToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Client->ReceiveToken.Packet.RxData = &Client->ReceiveData;

    //
    // Setup client transmit, server receive wait event
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4ClientTransmitServerReceiveWaitCallback,
                              Context,
                              &Context->WaitForClientTransmitServerReceive);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Setup server transmit, client receive wait event
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4ServerTransmitClientReceiveWaitCallback,
                              Context,
                              &Context->WaitForServerTransmitClientReceive);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    for (UINT32 i = 0; i < 10; i++) {
        DBG_INFO("Iteration : %u", i);

        Index = 0;
        Client->Transmitted = FALSE;

        //
        // Client transmit
        //

        Status = Client->Protocol->Transmit(Client->Protocol, &Client->TransmitToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Transmit() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Wait until server receives the data transmitted by the client
        //

        Status = gBS->WaitForEvent(1, &Context->WaitForClientTransmitServerReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        Index = 0;
        Client->Received = FALSE;

        //
        // Client receive
        //

        Status = Client->Protocol->Receive(Client->Protocol, &Client->ReceiveToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Wait until client receives the data transmitted by the server
        //

        Status = gBS->WaitForEvent(1, &Context->WaitForServerTransmitClientReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        if (Client->DataVerified == FALSE ||
            EFI_ERROR(Client->ReceiveToken.CompletionToken.Status)) {
            DBG_ERROR("   Server transmit ==> Client receive (failed) : %s(0x%zx)",
                      E(Client->ReceiveToken.CompletionToken.Status),
                      Client->ReceiveToken.CompletionToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
        } else {
            DBG_INFO("   Server transmit ==> Client receive (passed)");
        }
    }

Exit:
    FreePool(ClientTxData->FragmentTable[0].FragmentBuffer);
    FreePool(ClientRxData->FragmentTable[0].FragmentBuffer);
    return Status;
}

static EFI_STATUS Tcp4GetClientMode(_Inout_ EFI_DHCP4_MODE_DATA* Mode)
{
    BYTE OptionBuffer[sizeof(EFI_DHCP4_PACKET_OPTION) + 1]; // +1 for Data[1]
    EFI_DHCP4_CONFIG_DATA Config = {0};
    EFI_DHCP4_MODE_DATA RetMode = {0};
    EFI_DHCP4_PACKET_OPTION* Option = {0};
    EFI_DHCP4_PROTOCOL* Dhcp4 = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 Timeout[4] = {4, 8, 16, 32};
    PBM_PROTOCOL_INFO ProtocolArray = gProtocolArray;

    Status = ProtocolArray[EFI_DHCP4_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DHCP4_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Dhcp4 = ProtocolArray[EFI_DHCP4_PROTOCOL_INDEX].Protocol;

    Status = Dhcp4->GetModeData(Dhcp4, &RetMode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    if (RetMode.State == Dhcp4Init || RetMode.State == Dhcp4InitReboot ||
        RetMode.State == Dhcp4Bound) {
        DBG_ERROR("Dhcp mode is already in one of the expected state %s",
                  Dhcp4StateMap[RetMode.State].String);
        goto Found;
    }

    //
    // Option Codes: https://tools.ietf.org/html/rfc2132#section-3
    // DHCP Packet format: https://tools.ietf.org/html/rfc2131#section-2
    //

    Option = (EFI_DHCP4_PACKET_OPTION*)OptionBuffer;
    Option->OpCode = DHCP_OPTION_PARAMETER_REQUEST_LIST;
    Option->Length = 2;
    Option->Data[0] = DHCP_OPTION_SUBNET;
    Option->Data[1] = DHCP_OPTION_ROUTER;

    Config.DiscoverTryCount = DHCP_RETRIES;
    Config.DiscoverTimeout = Timeout;
    Config.OptionCount = 1;
    Config.OptionList = (EFI_DHCP4_PACKET_OPTION**)&Option;

    Status = Dhcp4->Configure(Dhcp4, &Config);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Dhcp4->GetModeData(Dhcp4, &RetMode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    if (RetMode.State == Dhcp4Init) {
        Status = Dhcp4->Start(Dhcp4, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetModeData() failed : %s(0x%zx) Possibly no dhcp server",
                      E(Status),
                      Status);
            goto Exit;
        }
    } else {
        DBG_ERROR("Dhcp is not in expected state %s", Dhcp4StateMap[RetMode.State].String);
        goto Exit;
    }

    Status = Dhcp4->GetModeData(Dhcp4, &RetMode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("DHCP 4 State: %s", Dhcp4StateMap[RetMode.State].String);

Found:
#if 0
    DBG_INFO_RAW("IP 4 Address:");
    DumpIP4Address(&RetMode.ClientAddress);
    DBG_INFO_RAW("Mac Address:");
    DumpMacAddress(&RetMode.ClientMacAddress);
    DBG_INFO_RAW("Server Address:");
    DumpIP4Address(&RetMode.ServerAddress);
    DBG_INFO_RAW("Router Address:");
    DumpIP4Address(&RetMode.RouterAddress);
    DBG_INFO_RAW("Subnet Mask:");
    DumpIP4Address(&RetMode.SubnetMask);
    DBG_INFO("Lease Time: %u days", SEC_TO_DAYS(RetMode.LeaseTime));
#endif
    *Mode = RetMode;

Exit:

    return Status;
}

static EFI_STATUS Tcp4GetServerIPAddressAndPort(_Inout_ EFI_IPv4_ADDRESS* ServerIPAddress,
                                                _Out_ UINT16* ServerPort)
{
    EFI_STATUS Status = EFI_SUCCESS;
    CHAR8* ServerIPAddressStr = NULL;
    CHAR8* ServerPortStr = NULL;
    UINTN Ret = 0;
    UINT32 U0 = 0, U1 = 0, U2 = 0, U3 = 0;

    Status = GetHostArgument(gHostArguments, t("ServerIPAddress"), &ServerIPAddressStr);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetHostArgument() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Ret = sscanf_s((const char*)ServerIPAddressStr, "%u.%u.%u.%u", &U0, &U1, &U2, &U3);
    if (Ret == EOF) {
        DBG_ERROR("sscanf_s() failed to parse : %s", ServerIPAddressStr);
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    ServerIPAddress->Addr[0] = (UINT8)U0;
    ServerIPAddress->Addr[1] = (UINT8)U1;
    ServerIPAddress->Addr[2] = (UINT8)U2;
    ServerIPAddress->Addr[3] = (UINT8)U3;

    Status = GetHostArgument(gHostArguments, t("ServerPort"), &ServerPortStr);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetHostArgument() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Ret = sscanf_s((const char*)ServerPortStr, "%u", &U0);
    if (Ret == EOF) {
        DBG_ERROR("sscanf_s() failed to parse : %s", ServerPortStr);
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    *ServerPort = (UINT16)U0;
Exit:
    FreePool(ServerIPAddressStr);
    FreePool(ServerPortStr);
    return Status;
}

//
// Configure client and server on 127.0.0.1:10001 and 127.0.0.2:10002
//

static EFI_STATUS Tcp4ConfigureClient(_In_ PBM_TCP4_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_TCP4_CLIENT Client = &Context->Client;
    EFI_DHCP4_MODE_DATA Mode = {0};
    EFI_IPv4_ADDRESS ServerIPAdress = {0};
    UINT16 ServerPort = 0;

    Status = Tcp4GetClientMode(&Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4GetClientMode() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Tcp4GetServerIPAddressAndPort(&ServerIPAdress, &ServerPort);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4GetServerIPAddressAndPort() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Client->ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Client->ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Client->ConfigData.AccessPoint.UseDefaultAddress = FALSE;
    Client->ConfigData.AccessPoint.StationAddress.Addr[0] = Mode.ClientAddress.Addr[0];
    Client->ConfigData.AccessPoint.StationAddress.Addr[1] = Mode.ClientAddress.Addr[1];
    Client->ConfigData.AccessPoint.StationAddress.Addr[2] = Mode.ClientAddress.Addr[2];
    Client->ConfigData.AccessPoint.StationAddress.Addr[3] = Mode.ClientAddress.Addr[3];
    Client->ConfigData.AccessPoint.SubnetMask.Addr[0] = Mode.SubnetMask.Addr[0];
    Client->ConfigData.AccessPoint.SubnetMask.Addr[1] = Mode.SubnetMask.Addr[1];
    Client->ConfigData.AccessPoint.SubnetMask.Addr[2] = Mode.SubnetMask.Addr[2];
    Client->ConfigData.AccessPoint.SubnetMask.Addr[3] = Mode.SubnetMask.Addr[3];
    Client->ConfigData.AccessPoint.StationPort = 10002;

    Client->ConfigData.AccessPoint.ActiveFlag = TRUE; // Client

    Client->ConfigData.AccessPoint.RemoteAddress.Addr[0] = ServerIPAdress.Addr[0];
    Client->ConfigData.AccessPoint.RemoteAddress.Addr[1] = ServerIPAdress.Addr[1];
    Client->ConfigData.AccessPoint.RemoteAddress.Addr[2] = ServerIPAdress.Addr[2];
    Client->ConfigData.AccessPoint.RemoteAddress.Addr[3] = ServerIPAdress.Addr[3];
    Client->ConfigData.AccessPoint.RemotePort = ServerPort;

    Client->Options.ReceiveBufferSize = NETWORK_TCP_CONTROL_OPTION_RECEIVE_BUFFER_SIZE;
    Client->Options.SendBufferSize = NETWORK_TCP_CONTROL_OPTION_SEND_BUFFER_SIZE;
    Client->Options.MaxSynBackLog = NETWORK_TCP_CONTROL_OPTION_MAX_SYN_BACK_LOG;
    Client->Options.ConnectionTimeout = NETWORK_TCP_CONTROL_OPTION_CONNECTION_TIMEOUT;
    Client->Options.DataRetries = NETWORK_TCP_CONTROL_OPTION_DATA_RETRIES;
    Client->Options.FinTimeout = NETWORK_TCP_CONTROL_OPTION_FIN_TIMEOUT;
    Client->Options.TimeWaitTimeout = NETWORK_TCP_CONTROL_OPTION_TIME_WAIT_TIMEOUT;
    Client->Options.KeepAliveProbes = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_PROBES;
    Client->Options.KeepAliveTime = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_TIME;
    Client->Options.KeepAliveInterval = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_INTERVAL;
    Client->Options.EnableNagle = NETWORK_TCP_CONTROL_OPTION_ENABLE_NAGLE;
    Client->Options.EnableTimeStamp = NETWORK_TCP_CONTROL_OPTION_ENABLE_TIME_STAMP;
    Client->Options.EnableWindowScaling = NETWORK_TCP_CONTROL_OPTION_ENABLE_WINDOW_SCALING;
    Client->Options.EnableSelectiveAck = NETWORK_TCP_CONTROL_OPTION_ENABLE_SELECTIVE_ACK;
    Client->Options.EnablePathMtuDiscovery = NETWORK_TCP_CONTROL_OPTION_ENABLE_PATH_MTU_DISCOVERY;
    Client->ConfigData.ControlOption = &Client->Options;

    Status = Client->Protocol->Configure(Client->Protocol, &Client->ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static VOID Tcp4FreeContext(_In_ PBM_TCP4_CONTEXT Context)
{
    PBM_TCP4_CLIENT Client = &Context->Client;

    gBS->CloseEvent(Context->WaitForAcceptConnection);
    gBS->CloseEvent(Context->WaitForClientTransmitServerReceive);
    gBS->CloseEvent(Context->WaitForServerTransmitClientReceive);

    gBS->CloseEvent(Client->ConnectToken.CompletionToken.Event);
    gBS->CloseEvent(Client->TransmitToken.CompletionToken.Event);
    gBS->CloseEvent(Client->ReceiveToken.CompletionToken.Event);
    FreePool(Client->ReceiveData.FragmentTable[0].FragmentBuffer);
    FreePool(Client->TransmitData.FragmentTable[0].FragmentBuffer);
}

//
// TCP4 DUT + HOST test Main function
//

EFI_STATUS
Tcp4DirectDutHostSendReceiveTest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    BM_TCP4_CONTEXT Context = {0};
    PBM_TCP4_CLIENT Client = &Context.Client;
    UINTN Index = 0;

    UNREFERENCED_PARAMETER(Session);

    gProtocolArray = ProtocolArray;
    gHostArguments = Session->Arguments;

    Status = ProtocolArray[EFI_TCP4_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_TCP4_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Context.Client.Protocol = ProtocolArray[EFI_TCP4_PROTOCOL_INDEX].Protocol;

    //
    // WaitForAcceptConnection event is used to stall main thread to wait until
    // both client and server finish 3 way handshake with Accept() from server
    // and Connect() from client
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4AcceptConnectionWaitCallback,
                              NULL,
                              &Context.WaitForAcceptConnection);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Configure TCP instance in active mode - Client
    //

    Status = Tcp4ConfigureClient(&Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4ConfigureClient() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Connect to Server
    //

    Status = Tcp4ConnectToServer(&Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4ConnectToServer() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Wait until connection is established
    //

    Status = gBS->WaitForEvent(1, &Context.WaitForAcceptConnection, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Client->Protocol
                 ->GetModeData(Client->Protocol, &Client->State, NULL, NULL, NULL, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Client TCP instance is in %s(0x%x) state",
             Tcp4StateMap[Client->State].String,
             Tcp4StateMap[Client->State].Value);

    //
    // Send data to Server
    //

    Status = Tcp4TransmitAndReceiveData(&Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4TransmitAndReceiveData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:

    Tcp4FreeContext(&Context);

    return Status;
}

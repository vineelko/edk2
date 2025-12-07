/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsudp4.duthost.directsendreceive.c

Abstract:

    This module implements udp4 dut + host test suite

Author:

    Vineel Kovvuri (vineelko) 16-Aug-2020

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

typedef struct _BM_UDP4_SOCKET {
    EFI_UDP4_PROTOCOL* Protocol;
    EFI_UDP4_CONFIG_DATA ConfigData;
    EFI_UDP4_COMPLETION_TOKEN TransmitToken;
    EFI_UDP4_COMPLETION_TOKEN ReceiveToken;
    EFI_UDP4_TRANSMIT_DATA TransmitData;
    BOOLEAN Transmitted;
    BOOLEAN Received;
    BOOLEAN DataVerified;
} BM_UDP4_SOCKET, *PBM_UDP4_SOCKET;

typedef struct _BM_UDP4_CONTEXT {
    BM_UDP4_SOCKET Client;

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
} BM_UDP4_CONTEXT, *PBM_UDP4_CONTEXT;

//
// Client/Server transmit/receive methods
//

static VOID EFIAPI Udp4ClientTransmitServerReceiveWaitCallback(_In_ EFI_EVENT Event,
                                                               _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Udp4ServerTransmitClientReceiveWaitCallback(_In_ EFI_EVENT Event,
                                                               _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Udp4ClientTransmitCallback(_In_ EFI_EVENT Event, _In_ PVOID _Context)
{
    PBM_UDP4_CONTEXT Context = _Context;
    PBM_UDP4_SOCKET Client = &Context->Client;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("   Triggered client transmit callback");

    //
    // Signal the wait event when client transmit is done
    //

    Client->Transmitted = TRUE;
    gBS->SignalEvent(Context->WaitForClientTransmitServerReceive);
}

static VOID EFIAPI Udp4ClientReceiveCallback(_In_ EFI_EVENT Event, _In_ PVOID _Context)
{
    PBM_UDP4_CONTEXT Context = _Context;
    EFI_UDP4_RECEIVE_DATA* ClientRxData = NULL;
    PBM_UDP4_SOCKET Client = &Context->Client;

    UNREFERENCED_PARAMETER(Event);

    ClientRxData = Client->ReceiveToken.Packet.RxData;

    DBG_INFO("   Triggered client receive callback");

    //
    // Atomic read. If it turns out to be 1 it means the server has already
    // transmitted. So lets read it and verify it to be SERVER_TX_BYTE
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

static EFI_STATUS Udp4TransmitAndReceiveData(_In_ PBM_UDP4_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Index = 0;
    EFI_UDP4_TRANSMIT_DATA* ClientTxData = NULL;
    PBM_UDP4_SOCKET Client = &Context->Client;

    ClientTxData = &Client->TransmitData;

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
    //
    // Receive buffers for udp are populated by the UEFI driver
    //

    //
    // Setup client tx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Udp4ClientTransmitCallback,
                              Context,
                              &Client->TransmitToken.Event);
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
                              Udp4ClientReceiveCallback,
                              Context,
                              &Client->ReceiveToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Setup client transmit, server receive wait event
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Udp4ClientTransmitServerReceiveWaitCallback,
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
                              Udp4ServerTransmitClientReceiveWaitCallback,
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
            DBG_ERROR("Receive() failed : %s(0x%zx)", E(Status), Status);
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

        if (Client->DataVerified == FALSE || EFI_ERROR(Client->ReceiveToken.Status)) {
            DBG_ERROR("   Server transmit ==> Client receive (failed) : %s(0x%zx)",
                      E(Client->ReceiveToken.Status),
                      Client->ReceiveToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
        } else {
            DBG_INFO("   Server transmit ==> Client receive (passed)");
        }

        //
        // Signal UEFI to clean up client receive buffer
        //

        Status = gBS->SignalEvent(Client->ReceiveToken.Packet.RxData->RecycleSignal);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("SignalEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

Exit:
    FreePool(ClientTxData->FragmentTable[0].FragmentBuffer);
    return Status;
}

static EFI_STATUS Udp4GetClientMode(_Inout_ EFI_DHCP4_MODE_DATA* Mode)
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
    *Mode = RetMode;

Exit:

    return Status;
}

static EFI_STATUS Udp4GetServerIPAddressAndPort(_Inout_ EFI_IPv4_ADDRESS* ServerIPAddress,
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

static EFI_STATUS Udp4ConfigureClient(_In_ PBM_UDP4_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_UDP4_SOCKET Client = &Context->Client;
    EFI_DHCP4_MODE_DATA Mode = {0};
    EFI_IPv4_ADDRESS ServerIPAddress = {0};
    UINT16 ServerPort = 0;

    Status = Udp4GetClientMode(&Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4GetClientMode() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Udp4GetServerIPAddressAndPort(&ServerIPAddress, &ServerPort);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4GetServerIPAddressAndPort() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Client->ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Client->ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Client->ConfigData.UseDefaultAddress = FALSE;
    Client->ConfigData.StationAddress.Addr[0] = Mode.ClientAddress.Addr[0];
    Client->ConfigData.StationAddress.Addr[1] = Mode.ClientAddress.Addr[1];
    Client->ConfigData.StationAddress.Addr[2] = Mode.ClientAddress.Addr[2];
    Client->ConfigData.StationAddress.Addr[3] = Mode.ClientAddress.Addr[3];
    Client->ConfigData.SubnetMask.Addr[0] = Mode.SubnetMask.Addr[0];
    Client->ConfigData.SubnetMask.Addr[1] = Mode.SubnetMask.Addr[1];
    Client->ConfigData.SubnetMask.Addr[2] = Mode.SubnetMask.Addr[2];
    Client->ConfigData.SubnetMask.Addr[3] = Mode.SubnetMask.Addr[3];
    Client->ConfigData.StationPort = 11002;

    Client->ConfigData.RemoteAddress.Addr[0] = ServerIPAddress.Addr[0];
    Client->ConfigData.RemoteAddress.Addr[1] = ServerIPAddress.Addr[1];
    Client->ConfigData.RemoteAddress.Addr[2] = ServerIPAddress.Addr[2];
    Client->ConfigData.RemoteAddress.Addr[3] = ServerIPAddress.Addr[3];
    Client->ConfigData.RemotePort = ServerPort;

    Status = Client->Protocol->Configure(Client->Protocol, &Client->ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static VOID Udp4FreeContext(_In_ PBM_UDP4_CONTEXT Context)
{
    PBM_UDP4_SOCKET Client = &Context->Client;

    gBS->CloseEvent(Context->WaitForClientTransmitServerReceive);
    gBS->CloseEvent(Context->WaitForServerTransmitClientReceive);

    gBS->CloseEvent(Client->TransmitToken.Event);
    gBS->CloseEvent(Client->ReceiveToken.Event);
    FreePool(Client->TransmitData.FragmentTable[0].FragmentBuffer);
}

//
// UDP4 Loopback test Main function
//

EFI_STATUS
Udp4DirectDutHostSendReceiveTest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    BM_UDP4_CONTEXT Context = {0};

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    gProtocolArray = ProtocolArray;
    gHostArguments = Session->Arguments;

    Status = ProtocolArray[EFI_UDP4_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_UDP4_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Context.Client.Protocol = ProtocolArray[EFI_UDP4_PROTOCOL_INDEX].Protocol;

    //
    // Configure UDP instance in active mode - Client
    //

    Status = Udp4ConfigureClient(&Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4ConfigureClient() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Send and receive data to server
    //

    Status = Udp4TransmitAndReceiveData(&Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4TransmitAndReceiveData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:

    Udp4FreeContext(&Context);

    return Status;
}

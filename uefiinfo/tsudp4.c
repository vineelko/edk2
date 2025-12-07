/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsudp4.c

Abstract:

    This module implements udp4 test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"
#include "protocols.h"
#include "testsuites.h"

#include "network_config.h"

#define CLIENT_TX_DATA_SIZE 1024
#define CLIENT_RX_DATA_SIZE 1024
#define CLIENT_TX_BYTE      0xC1

#define SERVER_TX_DATA_SIZE 1024
#define SERVER_RX_DATA_SIZE 1024
#define SERVER_TX_BYTE      0x51

typedef struct _BM_UDP4_SOCKET {
    EFI_UDP4_PROTOCOL* Protocol;
    EFI_UDP4_CONFIG_DATA ConfigData;
    EFI_UDP4_COMPLETION_TOKEN TransmitToken;
    EFI_UDP4_COMPLETION_TOKEN ReceiveToken;
    EFI_UDP4_TRANSMIT_DATA TransmitData;
    //    EFI_UDP4_RECEIVE_DATA ReceiveData;
    BOOLEAN Transmitted;
    BOOLEAN Received;
    BOOLEAN DataVerified;
} BM_UDP4_SOCKET, *PBM_UDP4_SOCKET;

typedef struct _BM_UDP4_LOOPBACK_CONTEXT {
    BM_UDP4_SOCKET Client;
    BM_UDP4_SOCKET Server;

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
} BM_UDP4_LOOPBACK_CONTEXT, *PBM_UDP4_LOOPBACK_CONTEXT;

//
// Protocol instance creation utility functions
//

static EFI_STATUS ProtocolGetUdp4ClientServer(_Inout_ PBM_PROTOCOL_INFO Client,
                                              _Inout_ PBM_PROTOCOL_INFO Server)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* DeviceHandles = NULL;
    HANDLE ChildHandle = NULL;
    UINTN DeviceHandleCount = 0;

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     Client->ServiceBindingProtocolGuid,
                                     NULL,
                                     &DeviceHandleCount,
                                     &DeviceHandles);

    if (DeviceHandleCount != 2) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    ChildHandle = NULL;
    Client->ServiceBindingProtocolStatus = ProtocolOpenServiceBinding(
        DeviceHandles[0],
        Client->ServiceBindingProtocolGuid,
        &Client->ServiceBindingProtocol);

    if (!EFI_ERROR(Client->ServiceBindingProtocolStatus)) {
        Client->ProtocolStatus = ProtocolOpenServiceBindingChildProtocol(
            Client->ServiceBindingProtocol,
            Client->ProtocolGuid,
            &Client->Protocol,
            &ChildHandle);
    }

    ChildHandle = NULL;
    Server->ServiceBindingProtocolStatus = ProtocolOpenServiceBinding(
        DeviceHandles[1],
        Server->ServiceBindingProtocolGuid,
        &Server->ServiceBindingProtocol);

    if (!EFI_ERROR(Server->ServiceBindingProtocolStatus)) {
        Server->ProtocolStatus = ProtocolOpenServiceBindingChildProtocol(
            Server->ServiceBindingProtocol,
            Server->ProtocolGuid,
            &Server->Protocol,
            &ChildHandle);
    }

Exit:
    if (DeviceHandles) {
        gBS->FreePool(DeviceHandles);
    }

    return Status;
}

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

static VOID EFIAPI Udp4ClientTransmitCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("   Triggered client transmit callback");

    //
    // Signal the wait event only when both client transmit and server receive
    // are done
    //

    Client->Transmitted = TRUE;

    if (Server->Received == TRUE && Client->Transmitted == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForClientTransmitServerReceive);
    }
}

static VOID EFIAPI Udp4ClientReceiveCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    EFI_UDP4_RECEIVE_DATA* ClientRxData = NULL;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    ClientRxData = Client->ReceiveToken.Packet.RxData;

    DBG_INFO("   Triggered client receive callback");

    //
    // Atomic read. If it turns out to be 1 it means the server has already
    // transmitted. So lets read it and verify it to be SERVER_TX_BYTE
    //

    if (Server->Transmitted == TRUE) {
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
    }

    //
    // Signal the wait event only when both server transmit and client receive
    // are done
    //

    Client->Received = TRUE;

    if (Server->Transmitted == TRUE && Client->Received == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForServerTransmitClientReceive);
    }
}

static VOID EFIAPI Udp4ServerTransmitCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("   Triggered server transmit callback");

    //
    // Signal the wait event only when both server transmit and client receive
    // are done
    //

    Server->Transmitted = TRUE;

    if (Server->Transmitted == TRUE && Client->Received == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForServerTransmitClientReceive);
    }
}

static VOID EFIAPI Udp4ServerReceiveCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    EFI_UDP4_RECEIVE_DATA* ServerRxData = NULL;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    ServerRxData = Server->ReceiveToken.Packet.RxData;

    DBG_INFO("   Triggered server receive callback");

    //
    // Atomic read. If it turns out to be 1 it means the client has already
    // transmitted. So lets read it and verify it to be CLIENT_TX_BYTE
    //

    if (Client->Transmitted == TRUE) {
        Server->DataVerified = TRUE;
        if (ServerRxData->DataLength != SERVER_RX_DATA_SIZE) {
            DBG_ERROR("Expected %u bytes from server. Only got %u bytes",
                      SERVER_RX_DATA_SIZE,
                      ServerRxData->DataLength);
            Server->DataVerified = FALSE;
        }

        for (UINTN i = 0; i < SERVER_RX_DATA_SIZE; i++) {
            UINT8* TxBuffer = ServerRxData->FragmentTable[0].FragmentBuffer;
            if (TxBuffer[i] != CLIENT_TX_BYTE) {
                Server->DataVerified = FALSE;
                break;
            }
        }
    }

    //
    // Signal the wait event only when both client transmit and server receive
    // are done
    //

    Server->Received = TRUE;

    if (Server->Received == TRUE && Client->Transmitted == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForClientTransmitServerReceive);
    }
}

static EFI_STATUS Udp4TransmitAndReceiveData(_In_ PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Index = 0;
    EFI_UDP4_TRANSMIT_DATA* ClientTxData = NULL;
    EFI_UDP4_TRANSMIT_DATA* ServerTxData = NULL;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    ClientTxData = &Client->TransmitData;
    ServerTxData = &Server->TransmitData;

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
    // Setup server tx buffers
    //

    ServerTxData->DataLength = SERVER_TX_DATA_SIZE;
    ServerTxData->FragmentCount = 1;
    ServerTxData->FragmentTable[0].FragmentLength = ServerTxData->DataLength;
    ServerTxData->FragmentTable[0].FragmentBuffer = AllocateZeroPool(ServerTxData->DataLength);
    if (ServerTxData->FragmentTable[0].FragmentBuffer == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  ServerTxData->DataLength);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    SetMem(ServerTxData->FragmentTable[0].FragmentBuffer, SERVER_TX_DATA_SIZE, SERVER_TX_BYTE);

    //
    // Setup server rx buffers
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
                              LoopbackContext,
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
                              LoopbackContext,
                              &Client->ReceiveToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Setup server tx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Udp4ServerTransmitCallback,
                              LoopbackContext,
                              &Server->TransmitToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Server->TransmitToken.Packet.TxData = &Server->TransmitData;

    //
    // Setup server rx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Udp4ServerReceiveCallback,
                              LoopbackContext,
                              &Server->ReceiveToken.Event);
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
                              LoopbackContext,
                              &LoopbackContext->WaitForClientTransmitServerReceive);
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
                              LoopbackContext,
                              &LoopbackContext->WaitForServerTransmitClientReceive);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    for (UINT32 i = 0; i < 10; i++) {
        DBG_INFO("Iteration : %u", i);

        Index = 0;
        Client->Transmitted = FALSE;
        Server->Received = FALSE;

        //
        // Client transmit
        //

        Status = Client->Protocol->Transmit(Client->Protocol, &Client->TransmitToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Transmit() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Server receive
        //

        Status = Server->Protocol->Receive(Server->Protocol, &Server->ReceiveToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Receive() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Wait until server receives the data transmitted by the client
        //

        Status = gBS->WaitForEvent(1, &LoopbackContext->WaitForClientTransmitServerReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        if (Server->DataVerified == TRUE && EFI_ERROR(Server->ReceiveToken.Status) == FALSE) {
            DBG_INFO("   Client transmit ==> Server receive (passed)");
        } else {
            DBG_ERROR("   Client transmit ==> Server receive (failed) : %s(0x%zx)",
                      E(Server->ReceiveToken.Status),
                      Server->ReceiveToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
        }

        //
        // Signal UEFI to clean up server receive buffer
        //

        Status = gBS->SignalEvent(Server->ReceiveToken.Packet.RxData->RecycleSignal);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("SignalEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        Index = 0;
        Server->Transmitted = FALSE;
        Client->Received = FALSE;

        //
        // Server transmit
        //

        Status = Server->Protocol->Transmit(Server->Protocol, &Server->TransmitToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Transmit() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

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

        Status = gBS->WaitForEvent(1, &LoopbackContext->WaitForServerTransmitClientReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        if (Client->DataVerified == TRUE && EFI_ERROR(Client->ReceiveToken.Status) == FALSE) {
            DBG_INFO("   Server transmit ==> Client receive (passed)");
        } else {
            DBG_ERROR("   Server transmit ==> Client receive (failed) : %s(0x%zx)",
                      E(Client->ReceiveToken.Status),
                      Client->ReceiveToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
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
    FreePool(ServerTxData->FragmentTable[0].FragmentBuffer);
    return Status;
}

//
// Configure client and server on 127.0.0.1:10001 and 127.0.0.2:10002
//

static EFI_STATUS Udp4ConfigureClient(_In_ PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;

    Client->ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Client->ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Client->ConfigData.UseDefaultAddress = FALSE;
    Client->ConfigData.StationAddress.Addr[0] = 127;
    Client->ConfigData.StationAddress.Addr[1] = 0;
    Client->ConfigData.StationAddress.Addr[2] = 0;
    Client->ConfigData.StationAddress.Addr[3] = 1;
    Client->ConfigData.SubnetMask.Addr[0] = 255;
    Client->ConfigData.SubnetMask.Addr[1] = 255;
    Client->ConfigData.SubnetMask.Addr[2] = 254;
    Client->ConfigData.SubnetMask.Addr[3] = 0;
    Client->ConfigData.StationPort = 11001;

    Client->ConfigData.RemoteAddress.Addr[0] = 127;
    Client->ConfigData.RemoteAddress.Addr[1] = 0;
    Client->ConfigData.RemoteAddress.Addr[2] = 0;
    Client->ConfigData.RemoteAddress.Addr[3] = 2;
    Client->ConfigData.RemotePort = 11002;

    Status = Client->Protocol->Configure(Client->Protocol, &Client->ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static EFI_STATUS Udp4ConfigureServer(_In_ PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    Server->ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Server->ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Server->ConfigData.UseDefaultAddress = FALSE;
    Server->ConfigData.StationAddress.Addr[0] = 127;
    Server->ConfigData.StationAddress.Addr[1] = 0;
    Server->ConfigData.StationAddress.Addr[2] = 0;
    Server->ConfigData.StationAddress.Addr[3] = 2;
    Server->ConfigData.SubnetMask.Addr[0] = 255;
    Server->ConfigData.SubnetMask.Addr[1] = 255;
    Server->ConfigData.SubnetMask.Addr[2] = 254;
    Server->ConfigData.SubnetMask.Addr[3] = 0;
    Server->ConfigData.StationPort = 11002;

    Server->ConfigData.RemoteAddress.Addr[0] = 127;
    Server->ConfigData.RemoteAddress.Addr[1] = 0;
    Server->ConfigData.RemoteAddress.Addr[2] = 0;
    Server->ConfigData.RemoteAddress.Addr[3] = 1;
    Server->ConfigData.RemotePort = 11001;

    Status = Server->Protocol->Configure(Server->Protocol, &Server->ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static VOID Udp4FreeLoopbackContext(_In_ PBM_UDP4_LOOPBACK_CONTEXT LoopbackContext)
{
    PBM_UDP4_SOCKET Client = &LoopbackContext->Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext->Server;

    gBS->CloseEvent(LoopbackContext->WaitForClientTransmitServerReceive);
    gBS->CloseEvent(LoopbackContext->WaitForServerTransmitClientReceive);

    gBS->CloseEvent(Client->TransmitToken.Event);
    gBS->CloseEvent(Client->ReceiveToken.Event);
    FreePool(Client->TransmitData.FragmentTable[0].FragmentBuffer);

    gBS->CloseEvent(Server->TransmitToken.Event);
    gBS->CloseEvent(Server->ReceiveToken.Event);
    FreePool(Server->TransmitData.FragmentTable[0].FragmentBuffer);
}

//
// UDP4 Loopback test Main function
//

static EFI_STATUS Udp4pLoopbackClientServerTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                                _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    BM_UDP4_LOOPBACK_CONTEXT LoopbackContext = {0};
    PBM_UDP4_SOCKET Client = &LoopbackContext.Client;
    PBM_UDP4_SOCKET Server = &LoopbackContext.Server;

    BM_PROTOCOL_INFO UdpClientServer[2] = {
        SB_PROTO(&gEfiUdp4ProtocolGuid,
                 t("EFI_UDP4_PROTOCOL"),
                 &gEfiUdp4ServiceBindingProtocolGuid,
                 t("EFI_UDP4_SERVICE_BINDING_PROTOCOL")),
        SB_PROTO(&gEfiUdp4ProtocolGuid,
                 t("EFI_UDP4_PROTOCOL"),
                 &gEfiUdp4ServiceBindingProtocolGuid,
                 t("EFI_UDP4_SERVICE_BINDING_PROTOCOL")),
    };

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    //
    // Create two instance of UDP protocol from each ethernet adapter
    //

    Status = ProtocolGetUdp4ClientServer(&UdpClientServer[0], &UdpClientServer[1]);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ProtocolGetUdp4ClientServer() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Client->Protocol = UdpClientServer[0].Protocol;
    Server->Protocol = UdpClientServer[1].Protocol;
    DBG_INFO("Client = 0x%p", Client->Protocol);
    DBG_INFO("Server = 0x%p", Server->Protocol);

    //
    // Configure UDP instance in passive mode - Server
    //

    Status = Udp4ConfigureServer(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4ConfigureServer() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Configure UDP instance in active mode - Client
    //

    Status = Udp4ConfigureClient(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4ConfigureClient() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Send and receive data to server
    //

    Status = Udp4TransmitAndReceiveData(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Udp4TransmitAndReceiveData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:

    Udp4FreeLoopbackContext(&LoopbackContext);

    return Status;
}

extern EFI_STATUS Udp4DirectDutHostSendReceiveTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                                   _In_ PBM_SESSION Session);

extern EFI_STATUS Udp4DirectDutHostPerfTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                            _In_ PBM_SESSION Session);

static BM_TEST DutTests[] = {
    {
        .Name = t("udp4loopback"),
        .Description = t("UDP 4 Loopback client/server test"),
        .DutTestFn = Udp4pLoopbackClientServerTest,
    },
};

static BM_TEST DutHostTests[] = {
    {
        .Name = t("udp4directsendreceive"),
        .Description = t("UDP 4 Dut+Host direct send receive test"),
        .DutTestFn = Udp4DirectDutHostSendReceiveTest,
    },
    {
        .Name = t("udp4directperf"),
        .Description = t("UDP 4 Dut+Host direct perf test"),
        .DutTestFn = Udp4DirectDutHostPerfTest,
    },
};

BM_TEST_SUITE Udp4TestSuite = {
    .Description = t("UDP 4 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
    .DutHostTests = DutHostTests,
    .DutHostTestCount = _countof(DutHostTests),
};

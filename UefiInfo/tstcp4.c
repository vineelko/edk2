#include "common.h"
#include "protocols.h"
#include "testsuites.h"

#include "network_config.h"
#include <Protocol/Tcp4.h>
#include <Protocol/Dhcp4.h>

#define CLIENT_TX_DATA_SIZE 1024
#define CLIENT_RX_DATA_SIZE 1024
#define CLIENT_TX_BYTE      0xC1

#define SERVER_TX_DATA_SIZE 1024
#define SERVER_RX_DATA_SIZE 1024
#define SERVER_TX_BYTE      0x51

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

typedef struct _UEFIINFO_TCP4_SOCKET {
    EFI_TCP4_PROTOCOL* Protocol;
    EFI_TCP4_CONNECTION_STATE State;
    EFI_TCP4_CONFIG_DATA ConfigData;
    EFI_TCP4_OPTION Options;
    EFI_TCP4_IO_TOKEN TransmitToken;
    EFI_TCP4_IO_TOKEN ReceiveToken;
    EFI_TCP4_TRANSMIT_DATA TransmitData;
    EFI_TCP4_RECEIVE_DATA ReceiveData;
} UEFIINFO_TCP4_SOCKET;

typedef struct _UEFIINFO_TCP4_CLIENT {
    UEFIINFO_TCP4_SOCKET Socket;
    EFI_TCP4_CONNECTION_TOKEN ConnectToken;
    BOOLEAN Connected;
    BOOLEAN Transmitted;
    BOOLEAN Received;
    BOOLEAN DataVerified;
} UEFIINFO_TCP4_CLIENT, *PUEFIINFO_TCP4_CLIENT;

typedef struct _UEFIINFO_TCP4_SERVER {
    UEFIINFO_TCP4_SOCKET Socket;
    EFI_TCP4_LISTEN_TOKEN AcceptToken;
    BOOLEAN Accepted;
    EFI_HANDLE ConnectedHandle;
    EFI_TCP4_PROTOCOL* ConnectedClientProtocol;
    BOOLEAN Transmitted;
    BOOLEAN Received;
    BOOLEAN DataVerified;
} UEFIINFO_TCP4_SERVER, *PUEFIINFO_TCP4_SERVER;

typedef struct _UEFIINFO_TCP4_LOOPBACK_CONTEXT {
    UEFIINFO_TCP4_CLIENT Client;
    UEFIINFO_TCP4_SERVER Server;

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

} UEFIINFO_TCP4_LOOPBACK_CONTEXT, *PUEFIINFO_TCP4_LOOPBACK_CONTEXT;

//
// Protocol instance creation utility functions
//

static EFI_STATUS ProtocolGetTcp4ClientServer(IN OUT PPROTOCOL_INFO Client,
                                              IN OUT PPROTOCOL_INFO Server)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* DeviceHandles = NULL;
    EFI_HANDLE ChildHandle = NULL;
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
// Client/Server connect/accept(3-way handshake) functions
//

static VOID EFIAPI Tcp4AcceptConnectionWaitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);
}

static VOID EFIAPI Tcp4ServerAcceptCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("Triggered Accept callback");

    Server->Accepted = TRUE;

    if (Server->Accepted == TRUE && Client->Connected == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForAcceptConnection);
    }
}

static EFI_STATUS Tcp4AcceptConnections(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    //
    // WaitForAcceptConnection event is used to stall main thread to wait until
    // both client and server finish 3 way handshake with Accept() from server
    // and Connect() from client
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4AcceptConnectionWaitCallback,
                              LoopbackContext,
                              &LoopbackContext->WaitForAcceptConnection);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ServerAcceptCallback,
                              LoopbackContext,
                              &Server->AcceptToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Server->Socket.Protocol->Accept(Server->Socket.Protocol, &Server->AcceptToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Accept() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static VOID EFIAPI Tcp4ClientConnectCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    DBG_INFO("Triggered Connect callback");

    Client->Connected = TRUE;

    if (Server->Accepted == TRUE && Client->Connected == TRUE) {
        gBS->SignalEvent(LoopbackContext->WaitForAcceptConnection);
    }
}

static EFI_STATUS Tcp4ConnectToServer(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientConnectCallback,
                              LoopbackContext,
                              &Client->ConnectToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Client->Socket.Protocol->Connect(Client->Socket.Protocol, &Client->ConnectToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Connect() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

//
// Client/Server transmit/receive methods
//

static VOID EFIAPI Tcp4ClientTransmitServerReceiveWaitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Tcp4ServerTransmitClientReceiveWaitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI Tcp4ClientTransmitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

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

static VOID EFIAPI Tcp4ClientReceiveCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    EFI_TCP4_RECEIVE_DATA* ClientRxData = NULL;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    ClientRxData = Client->Socket.ReceiveToken.Packet.RxData;

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

static VOID EFIAPI Tcp4ServerTransmitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

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

static VOID EFIAPI Tcp4ServerReceiveCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext = Context;
    EFI_TCP4_RECEIVE_DATA* ServerRxData = NULL;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    UNREFERENCED_PARAMETER(Event);

    ServerRxData = Server->Socket.ReceiveToken.Packet.RxData;

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

static EFI_STATUS Tcp4TransmitAndReceiveData(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Index = 0;
    EFI_TCP4_TRANSMIT_DATA* ClientTxData = NULL;
    EFI_TCP4_RECEIVE_DATA* ClientRxData = NULL;
    EFI_TCP4_TRANSMIT_DATA* ServerTxData = NULL;
    EFI_TCP4_RECEIVE_DATA* ServerRxData = NULL;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    ClientTxData = &Client->Socket.TransmitData;
    ClientRxData = &Client->Socket.ReceiveData;
    ServerTxData = &Server->Socket.TransmitData;
    ServerRxData = &Server->Socket.ReceiveData;

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

    ServerRxData->DataLength = SERVER_RX_DATA_SIZE; // overwritten by the network driver on receive
    ServerRxData->FragmentCount = 1;
    ServerRxData->FragmentTable[0].FragmentLength = ServerRxData->DataLength;
    ServerRxData->FragmentTable[0].FragmentBuffer = AllocateZeroPool(ServerRxData->DataLength);
    if (ServerRxData->FragmentTable[0].FragmentBuffer == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  ServerRxData->DataLength);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Setup client tx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientTransmitCallback,
                              LoopbackContext,
                              &Client->Socket.TransmitToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Client->Socket.TransmitToken.Packet.TxData = &Client->Socket.TransmitData;

    //
    // Setup client rx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ClientReceiveCallback,
                              LoopbackContext,
                              &Client->Socket.ReceiveToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Client->Socket.ReceiveToken.Packet.RxData = &Client->Socket.ReceiveData;

    //
    // Setup server tx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ServerTransmitCallback,
                              LoopbackContext,
                              &Server->Socket.TransmitToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Server->Socket.TransmitToken.Packet.TxData = &Server->Socket.TransmitData;

    //
    // Setup server rx token
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              Tcp4ServerReceiveCallback,
                              LoopbackContext,
                              &Server->Socket.ReceiveToken.CompletionToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Server->Socket.ReceiveToken.Packet.RxData = &Server->Socket.ReceiveData;

    //
    // Setup client transmit, server receive wait event
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4ClientTransmitServerReceiveWaitCallback,
                              LoopbackContext,
                              &LoopbackContext->WaitForClientTransmitServerReceive);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Setup server transmit, client receive wait event
    //

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              Tcp4ServerTransmitClientReceiveWaitCallback,
                              LoopbackContext,
                              &LoopbackContext->WaitForServerTransmitClientReceive);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
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

        Status = Client->Socket.Protocol->Transmit(Client->Socket.Protocol, &Client->Socket.TransmitToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Transmit() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        //
        // Server receive
        //

        Status = Server->ConnectedClientProtocol->Receive(Server->ConnectedClientProtocol,
                                                          &Server->Socket.ReceiveToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Receive() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        //
        // Wait until server receives the data transmitted by the client
        //

        Status = gBS->WaitForEvent(1, &LoopbackContext->WaitForClientTransmitServerReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        if (Server->DataVerified == FALSE ||
            EFI_ERROR(Server->Socket.ReceiveToken.CompletionToken.Status)) {
            DBG_ERROR("   Client transmit ==> Server receive (failed) : %a(0x%x)",
                      E(Server->Socket.ReceiveToken.CompletionToken.Status),
                      Server->Socket.ReceiveToken.CompletionToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
        } else {
            DBG_INFO("   Client transmit ==> Server receive (passed)");
        }

        Index = 0;
        Server->Transmitted = FALSE;
        Client->Received = FALSE;

        //
        // Server transmit
        //

        Status = Server->ConnectedClientProtocol->Transmit(Server->ConnectedClientProtocol,
                                                           &Server->Socket.TransmitToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Transmit() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        //
        // Client receive
        //

        Status = Client->Socket.Protocol->Receive(Client->Socket.Protocol, &Client->Socket.ReceiveToken);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Receive() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        //
        // Wait until client receives the data transmitted by the server
        //

        Status = gBS->WaitForEvent(1, &LoopbackContext->WaitForServerTransmitClientReceive, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        if (Client->DataVerified == FALSE ||
            EFI_ERROR(Client->Socket.ReceiveToken.CompletionToken.Status)) {
            DBG_ERROR("   Server transmit ==> Client receive (failed) : %a(0x%x)",
                      E(Client->Socket.ReceiveToken.CompletionToken.Status),
                      Client->Socket.ReceiveToken.CompletionToken.Status);
            Status = EFI_INVALID_PARAMETER;
            break;
        } else {
            DBG_INFO("   Server transmit ==> Client receive (passed)");
        }
    }

Exit:
    FreePool(ClientTxData->FragmentTable[0].FragmentBuffer);
    FreePool(ClientRxData->FragmentTable[0].FragmentBuffer);
    FreePool(ServerTxData->FragmentTable[0].FragmentBuffer);
    FreePool(ServerRxData->FragmentTable[0].FragmentBuffer);
    return Status;
}

//
// Configure client and server on 127.0.0.1:10001 and 127.0.0.2:10002
//

static EFI_STATUS Tcp4ConfigureClient(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;

    Client->Socket.ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Client->Socket.ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Client->Socket.ConfigData.AccessPoint.UseDefaultAddress = FALSE;
    Client->Socket.ConfigData.AccessPoint.StationAddress.Addr[0] = 127;
    Client->Socket.ConfigData.AccessPoint.StationAddress.Addr[1] = 0;
    Client->Socket.ConfigData.AccessPoint.StationAddress.Addr[2] = 0;
    Client->Socket.ConfigData.AccessPoint.StationAddress.Addr[3] = 1;
    Client->Socket.ConfigData.AccessPoint.SubnetMask.Addr[0] = 255;
    Client->Socket.ConfigData.AccessPoint.SubnetMask.Addr[1] = 255;
    Client->Socket.ConfigData.AccessPoint.SubnetMask.Addr[2] = 254;
    Client->Socket.ConfigData.AccessPoint.SubnetMask.Addr[3] = 0;
    Client->Socket.ConfigData.AccessPoint.StationPort = 10001;

    Client->Socket.ConfigData.AccessPoint.ActiveFlag = TRUE; // Client

    Client->Socket.ConfigData.AccessPoint.RemoteAddress.Addr[0] = 127;
    Client->Socket.ConfigData.AccessPoint.RemoteAddress.Addr[1] = 0;
    Client->Socket.ConfigData.AccessPoint.RemoteAddress.Addr[2] = 0;
    Client->Socket.ConfigData.AccessPoint.RemoteAddress.Addr[3] = 2;
    Client->Socket.ConfigData.AccessPoint.RemotePort = 10002;

    Client->Socket.Options.ReceiveBufferSize = NETWORK_TCP_CONTROL_OPTION_RECEIVE_BUFFER_SIZE;
    Client->Socket.Options.SendBufferSize = NETWORK_TCP_CONTROL_OPTION_SEND_BUFFER_SIZE;
    Client->Socket.Options.MaxSynBackLog = NETWORK_TCP_CONTROL_OPTION_MAX_SYN_BACK_LOG;
    Client->Socket.Options.ConnectionTimeout = NETWORK_TCP_CONTROL_OPTION_CONNECTION_TIMEOUT;
    Client->Socket.Options.DataRetries = NETWORK_TCP_CONTROL_OPTION_DATA_RETRIES;
    Client->Socket.Options.FinTimeout = NETWORK_TCP_CONTROL_OPTION_FIN_TIMEOUT;
    Client->Socket.Options.TimeWaitTimeout = NETWORK_TCP_CONTROL_OPTION_TIME_WAIT_TIMEOUT;
    Client->Socket.Options.KeepAliveProbes = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_PROBES;
    Client->Socket.Options.KeepAliveTime = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_TIME;
    Client->Socket.Options.KeepAliveInterval = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_INTERVAL;
    Client->Socket.Options.EnableNagle = NETWORK_TCP_CONTROL_OPTION_ENABLE_NAGLE;
    Client->Socket.Options.EnableTimeStamp = NETWORK_TCP_CONTROL_OPTION_ENABLE_TIME_STAMP;
    Client->Socket.Options.EnableWindowScaling = NETWORK_TCP_CONTROL_OPTION_ENABLE_WINDOW_SCALING;
    Client->Socket.Options.EnableSelectiveAck = NETWORK_TCP_CONTROL_OPTION_ENABLE_SELECTIVE_ACK;
    Client->Socket.Options.EnablePathMtuDiscovery = NETWORK_TCP_CONTROL_OPTION_ENABLE_PATH_MTU_DISCOVERY;
    Client->Socket.ConfigData.ControlOption = &Client->Socket.Options;

    Status = Client->Socket.Protocol->Configure(Client->Socket.Protocol, &Client->Socket.ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static EFI_STATUS Tcp4ConfigureServer(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    Server->Socket.ConfigData.TypeOfService = NETWORK_TCP_TYPE_OF_SERVICE;
    Server->Socket.ConfigData.TimeToLive = NETWORK_TCP_TIME_TO_LIVE;
    Server->Socket.ConfigData.AccessPoint.UseDefaultAddress = FALSE;
    Server->Socket.ConfigData.AccessPoint.StationAddress.Addr[0] = 127;
    Server->Socket.ConfigData.AccessPoint.StationAddress.Addr[1] = 0;
    Server->Socket.ConfigData.AccessPoint.StationAddress.Addr[2] = 0;
    Server->Socket.ConfigData.AccessPoint.StationAddress.Addr[3] = 2;
    Server->Socket.ConfigData.AccessPoint.SubnetMask.Addr[0] = 255;
    Server->Socket.ConfigData.AccessPoint.SubnetMask.Addr[1] = 255;
    Server->Socket.ConfigData.AccessPoint.SubnetMask.Addr[2] = 254;
    Server->Socket.ConfigData.AccessPoint.SubnetMask.Addr[3] = 0;
    Server->Socket.ConfigData.AccessPoint.StationPort = 10002;

    Server->Socket.ConfigData.AccessPoint.ActiveFlag = FALSE; // Server
    Server->Socket.Options.ReceiveBufferSize = NETWORK_TCP_CONTROL_OPTION_RECEIVE_BUFFER_SIZE;
    Server->Socket.Options.SendBufferSize = NETWORK_TCP_CONTROL_OPTION_SEND_BUFFER_SIZE;
    Server->Socket.Options.MaxSynBackLog = NETWORK_TCP_CONTROL_OPTION_MAX_SYN_BACK_LOG;
    Server->Socket.Options.ConnectionTimeout = NETWORK_TCP_CONTROL_OPTION_CONNECTION_TIMEOUT;
    Server->Socket.Options.DataRetries = NETWORK_TCP_CONTROL_OPTION_DATA_RETRIES;
    Server->Socket.Options.FinTimeout = NETWORK_TCP_CONTROL_OPTION_FIN_TIMEOUT;
    Server->Socket.Options.TimeWaitTimeout = NETWORK_TCP_CONTROL_OPTION_TIME_WAIT_TIMEOUT;
    Server->Socket.Options.KeepAliveProbes = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_PROBES;
    Server->Socket.Options.KeepAliveTime = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_TIME;
    Server->Socket.Options.KeepAliveInterval = NETWORK_TCP_CONTROL_OPTION_KEEP_ALIVE_INTERVAL;
    Server->Socket.Options.EnableNagle = NETWORK_TCP_CONTROL_OPTION_ENABLE_NAGLE;
    Server->Socket.Options.EnableTimeStamp = NETWORK_TCP_CONTROL_OPTION_ENABLE_TIME_STAMP;
    Server->Socket.Options.EnableWindowScaling = NETWORK_TCP_CONTROL_OPTION_ENABLE_WINDOW_SCALING;
    Server->Socket.Options.EnableSelectiveAck = NETWORK_TCP_CONTROL_OPTION_ENABLE_SELECTIVE_ACK;
    Server->Socket.Options.EnablePathMtuDiscovery = NETWORK_TCP_CONTROL_OPTION_ENABLE_PATH_MTU_DISCOVERY;
    Server->Socket.ConfigData.ControlOption = &Server->Socket.Options;

    Status = Server->Socket.Protocol->Configure(Server->Socket.Protocol, &Server->Socket.ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Server->Socket.Protocol->GetModeData(Server->Socket.Protocol,
                                           &Server->Socket.State,
                                           &Server->Socket.ConfigData,
                                           NULL,
                                           NULL,
                                           NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    if (Server->Socket.State == Tcp4StateListen) {
        DBG_INFO("Server TCP instance successfully set to Tcp4StateListen state");
    } else {
        DBG_ERROR("Server TCP instance is not in expected state = %a(0x%x)",
                  Tcp4StateMap[Server->Socket.State].String,
                  Tcp4StateMap[Server->Socket.State].Value);
        Status = EFI_PROTOCOL_ERROR;
    }

Exit:
    return Status;
}

static VOID Tcp4FreeLoopbackContext(IN PUEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext)
{
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext->Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext->Server;

    gBS->CloseEvent(LoopbackContext->WaitForAcceptConnection);
    gBS->CloseEvent(LoopbackContext->WaitForClientTransmitServerReceive);
    gBS->CloseEvent(LoopbackContext->WaitForServerTransmitClientReceive);

    gBS->CloseEvent(Client->ConnectToken.CompletionToken.Event);
    gBS->CloseEvent(Client->Socket.TransmitToken.CompletionToken.Event);
    gBS->CloseEvent(Client->Socket.ReceiveToken.CompletionToken.Event);
    FreePool(Client->Socket.ReceiveData.FragmentTable[0].FragmentBuffer);
    FreePool(Client->Socket.TransmitData.FragmentTable[0].FragmentBuffer);

    gBS->CloseEvent(Server->AcceptToken.CompletionToken.Event);
    gBS->CloseEvent(Server->Socket.TransmitToken.CompletionToken.Event);
    gBS->CloseEvent(Server->Socket.ReceiveToken.CompletionToken.Event);
    FreePool(Server->Socket.ReceiveData.FragmentTable[0].FragmentBuffer);
    FreePool(Server->Socket.TransmitData.FragmentTable[0].FragmentBuffer);
}

//
// TCP4 Loopback test Main function
//

static EFI_STATUS Tcp4pLoopbackClientServerTest(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UEFIINFO_TCP4_LOOPBACK_CONTEXT LoopbackContext;
    PUEFIINFO_TCP4_CLIENT Client = &LoopbackContext.Client;
    PUEFIINFO_TCP4_SERVER Server = &LoopbackContext.Server;
    UINTN Index = 0;

    PROTOCOL_INFO TcpClientServer[2] = {
        SB_PROTO(&gEfiTcp4ProtocolGuid,
                 t("EFI_TCP4_PROTOCOL"),
                 &gEfiTcp4ServiceBindingProtocolGuid,
                 t("EFI_TCP4_SERVICE_BINDING_PROTOCOL")),
        SB_PROTO(&gEfiTcp4ProtocolGuid,
                 t("EFI_TCP4_PROTOCOL"),
                 &gEfiTcp4ServiceBindingProtocolGuid,
                 t("EFI_TCP4_SERVICE_BINDING_PROTOCOL")),
    };

    UNREFERENCED_PARAMETER(Session);

    //
    // Create two instance of TCP protocol from each ethernet adapter
    //

    Status = ProtocolGetTcp4ClientServer(&TcpClientServer[0], &TcpClientServer[1]);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ProtocolGetTcp4ClientServer() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Client->Socket.Protocol = TcpClientServer[0].Protocol;
    Server->Socket.Protocol = TcpClientServer[1].Protocol;
    DBG_INFO("Client = 0x%p", Client->Socket.Protocol);
    DBG_INFO("Server = 0x%p", Server->Socket.Protocol);

    if (Client->Socket.Protocol == NULL || Server->Socket.Protocol == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    //
    // Configure TCP instance in passive mode - Server
    //

    Status = Tcp4ConfigureServer(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4ConfigureServer() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Configure TCP instance in active mode - Client
    //

    Status = Tcp4ConfigureClient(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4ConfigureClient() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Fire up the Server
    //

    Status = Tcp4AcceptConnections(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4AcceptConnections() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    while (Server->Socket.State != Tcp4StateListen) {
        Status = Server->Socket.Protocol
                     ->GetModeData(Server->Socket.Protocol, &Server->Socket.State, NULL, NULL, NULL, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetModeData() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }
    }

    //
    // Connect to Server
    //

    Status = Tcp4ConnectToServer(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4ConnectToServer() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Wait until connection is established
    //

    Status = gBS->WaitForEvent(1, &LoopbackContext.WaitForAcceptConnection, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Client->Socket.Protocol
                 ->GetModeData(Client->Socket.Protocol, &Client->Socket.State, NULL, NULL, NULL, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Client TCP instance is in %a(0x%x) state",
             Tcp4StateMap[Client->Socket.State].String,
             Tcp4StateMap[Client->Socket.State].Value);

    Status = Server->Socket.Protocol
                 ->GetModeData(Server->Socket.Protocol, &Server->Socket.State, NULL, NULL, NULL, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Server TCP instance is in %a(0x%x) state",
             Tcp4StateMap[Server->Socket.State].String,
             Tcp4StateMap[Server->Socket.State].Value);

    //
    // Extract the TCP protocol instance from the connected client
    //

    Server->ConnectedHandle = Server->AcceptToken.NewChildHandle;
    Status = gBS->HandleProtocol(Server->ConnectedHandle,
                                 &gEfiTcp4ProtocolGuid,
                                 (VOID**)&Server->ConnectedClientProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Send data to Server
    //

    Status = Tcp4TransmitAndReceiveData(&LoopbackContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Tcp4TransmitAndReceiveData() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:

    Tcp4FreeLoopbackContext(&LoopbackContext);

    return Status;
}

extern EFI_STATUS Tcp4DirectDutHostSendReceiveTest(IN PUEFIINFO_SESSION Session);

extern EFI_STATUS Tcp4DirectDutHostPerfTest(IN PUEFIINFO_SESSION Session);

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("tcp4loopback"),
        .Description = t("TCP 4 Loopback client/server test"),
        .DutTestFn = Tcp4pLoopbackClientServerTest,
    },
};

static UEFIINFO_TEST DutHostTests[] = {
    {
        .Name = t("tcp4directsendreceive"),
        .Description = t("TCP 4 Dut+Host direct send receive test"),
        .DutTestFn = Tcp4DirectDutHostSendReceiveTest,
    },
    {
        .Name = t("tcp4directperf"),
        .Description = t("TCP 4 Dut+Host direct perf test"),
        .DutTestFn = Tcp4DirectDutHostPerfTest,
    },
};

UEFIINFO_TEST_SUITE Tcp4TestSuite = {
    .Description = t("TCP 4 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
    .DutHostTests = DutHostTests,
    .DutHostTestCount = _countof(DutHostTests),
};

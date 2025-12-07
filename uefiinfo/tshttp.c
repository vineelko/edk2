/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tshttp.c

Abstract:

    This module implements http/https related test suite

Author:

    Vineel Kovvuri (vineelko) 06-Nov-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"
#include "strsafe.h"

#include "tshttp.dcat.certs.h"
#include "tshttp.httpbin.certs.h"

//
// Constants/Macros
//

#define HTTP_DEFAULT_RESPONSE_BUFFER_SIZE (0x100000) // 1048576
#define HTTP_REQUEST_WAIT_TIMEOUT         SEC_TO_100_NS(10)
#define HTTP_RESPONSE_WAIT_TIMEOUT        SEC_TO_100_NS(10)
#define HTTP_HEADER_CONTENT_LENGTH        t("Content-Length")
#define HTTP_HEADER_CONTENT_TYPE          t("Content-Type")
#define HTTP_HEADER_HOST                  t("Host")
#define HTTP_HEADER_USER_AGENT            t("User-Agent")
#define HTTP_HEADER_ACCEPT                t("Accept")
#define HEADER_AGENT_VALUE                t("CBMR-Agent")
#define HEADER_ACCEPT_VALUE               t("*/*")
#define HEADER_CONTENT_JSON               t("application/json")

//
// Structs
//

typedef struct _HTTP_CONTEXT {
#if 0
    EFI_HANDLE ParentHandle;

    //
    // DHCP protocol
    //

    DHCP_CONTEXT* Dhcp4Context;
#endif
    //
    // HTTP native protocols.
    //
    EFI_HANDLE HttpHandle;
    EFI_SERVICE_BINDING_PROTOCOL* HttpSvcBindingProtocol;
    EFI_HTTP_PROTOCOL* Http;
} HTTP_CONTEXT, *PHTTP_CONTEXT;

typedef struct _HTTP_REQUEST {
    PWSTR Url;

    BOOLEAN CallbackTriggered;

    EFI_HTTP_REQUEST_DATA Data;
    EFI_HTTP_HEADER Header;
    EFI_HTTP_MESSAGE Message;
    EFI_HTTP_TOKEN Token;
} HTTP_REQUEST, *PHTTP_REQUEST;

typedef struct _HTTP_RESPONSE {
    UINTN ContentLength;
    UINTN ContentDownloaded;

    BOOLEAN CallbackTriggered;

    EFI_HTTP_RESPONSE_DATA Data;
    EFI_HTTP_MESSAGE Message;
    EFI_HTTP_TOKEN Token;

    HTTP_REQUEST* Request;
} HTTP_RESPONSE, *PHTTP_RESPONSE;

// clang-format off
static ENUM_TO_STRING HttpStatusMap[] = {
    {HTTP_STATUS_UNSUPPORTED_STATUS,                STRINGIFY(HTTP_STATUS_UNSUPPORTED_STATUS)},
    {HTTP_STATUS_100_CONTINUE,                      STRINGIFY(HTTP_STATUS_100_CONTINUE)},
    {HTTP_STATUS_101_SWITCHING_PROTOCOLS,           STRINGIFY(HTTP_STATUS_101_SWITCHING_PROTOCOLS)},
    {HTTP_STATUS_200_OK,                            STRINGIFY(HTTP_STATUS_200_OK)},
    {HTTP_STATUS_201_CREATED,                       STRINGIFY(HTTP_STATUS_201_CREATED)},
    {HTTP_STATUS_202_ACCEPTED,                      STRINGIFY(HTTP_STATUS_202_ACCEPTED)},
    {HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION, STRINGIFY(HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION)},
    {HTTP_STATUS_204_NO_CONTENT,                    STRINGIFY(HTTP_STATUS_204_NO_CONTENT)},
    {HTTP_STATUS_205_RESET_CONTENT,                 STRINGIFY(HTTP_STATUS_205_RESET_CONTENT)},
    {HTTP_STATUS_206_PARTIAL_CONTENT,               STRINGIFY(HTTP_STATUS_206_PARTIAL_CONTENT)},
    {HTTP_STATUS_300_MULTIPLE_CHOICES,              STRINGIFY(HTTP_STATUS_300_MULTIPLE_CHOICES)},
    {HTTP_STATUS_301_MOVED_PERMANENTLY,             STRINGIFY(HTTP_STATUS_301_MOVED_PERMANENTLY)},
    {HTTP_STATUS_302_FOUND,                         STRINGIFY(HTTP_STATUS_302_FOUND)},
    {HTTP_STATUS_303_SEE_OTHER,                     STRINGIFY(HTTP_STATUS_303_SEE_OTHER)},
    {HTTP_STATUS_304_NOT_MODIFIED,                  STRINGIFY(HTTP_STATUS_304_NOT_MODIFIED)},
    {HTTP_STATUS_305_USE_PROXY,                     STRINGIFY(HTTP_STATUS_305_USE_PROXY)},
    {HTTP_STATUS_307_TEMPORARY_REDIRECT,            STRINGIFY(HTTP_STATUS_307_TEMPORARY_REDIRECT)},
    {HTTP_STATUS_400_BAD_REQUEST,                   STRINGIFY(HTTP_STATUS_400_BAD_REQUEST)},
    {HTTP_STATUS_401_UNAUTHORIZED,                  STRINGIFY(HTTP_STATUS_401_UNAUTHORIZED)},
    {HTTP_STATUS_402_PAYMENT_REQUIRED,              STRINGIFY(HTTP_STATUS_402_PAYMENT_REQUIRED)},
    {HTTP_STATUS_403_FORBIDDEN,                     STRINGIFY(HTTP_STATUS_403_FORBIDDEN)},
    {HTTP_STATUS_404_NOT_FOUND,                     STRINGIFY(HTTP_STATUS_404_NOT_FOUND)},
    {HTTP_STATUS_405_METHOD_NOT_ALLOWED,            STRINGIFY(HTTP_STATUS_405_METHOD_NOT_ALLOWED)},
    {HTTP_STATUS_406_NOT_ACCEPTABLE,                STRINGIFY(HTTP_STATUS_406_NOT_ACCEPTABLE)},
    {HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED, STRINGIFY(HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED)},
    {HTTP_STATUS_408_REQUEST_TIME_OUT,              STRINGIFY(HTTP_STATUS_408_REQUEST_TIME_OUT)},
    {HTTP_STATUS_409_CONFLICT,                      STRINGIFY(HTTP_STATUS_409_CONFLICT)},
    {HTTP_STATUS_410_GONE,                          STRINGIFY(HTTP_STATUS_410_GONE)},
    {HTTP_STATUS_411_LENGTH_REQUIRED,               STRINGIFY(HTTP_STATUS_411_LENGTH_REQUIRED)},
    {HTTP_STATUS_412_PRECONDITION_FAILED,           STRINGIFY(HTTP_STATUS_412_PRECONDITION_FAILED)},
    {HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE,      STRINGIFY(HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE)},
    {HTTP_STATUS_414_REQUEST_URI_TOO_LARGE,         STRINGIFY(HTTP_STATUS_414_REQUEST_URI_TOO_LARGE)},
    {HTTP_STATUS_415_UNSUPPORTED_MEDIA_TYPE,        STRINGIFY(HTTP_STATUS_415_UNSUPPORTED_MEDIA_TYPE)},
    {HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED, STRINGIFY(HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED)},
    {HTTP_STATUS_417_EXPECTATION_FAILED,            STRINGIFY(HTTP_STATUS_417_EXPECTATION_FAILED)},
    {HTTP_STATUS_500_INTERNAL_SERVER_ERROR,         STRINGIFY(HTTP_STATUS_500_INTERNAL_SERVER_ERROR)},
    {HTTP_STATUS_501_NOT_IMPLEMENTED,               STRINGIFY(HTTP_STATUS_501_NOT_IMPLEMENTED)},
    {HTTP_STATUS_502_BAD_GATEWAY,                   STRINGIFY(HTTP_STATUS_502_BAD_GATEWAY)},
    {HTTP_STATUS_503_SERVICE_UNAVAILABLE,           STRINGIFY(HTTP_STATUS_503_SERVICE_UNAVAILABLE)},
    {HTTP_STATUS_504_GATEWAY_TIME_OUT,              STRINGIFY(HTTP_STATUS_504_GATEWAY_TIME_OUT)},
    {HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED,    STRINGIFY(HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED)},
    {HTTP_STATUS_308_PERMANENT_REDIRECT,            STRINGIFY(HTTP_STATUS_308_PERMANENT_REDIRECT)},
};
// clang-format on

//
// Prototypes
//
static VOID EFIAPI HttpRequestCallback(IN EFI_EVENT Event, IN VOID* Context);
static VOID EFIAPI HttpResponseCallback(IN EFI_EVENT Event, IN VOID* Context);
static EFI_STATUS EFIAPI HttpSendRequest(_In_ PHTTP_CONTEXT Context, _Inout_ PHTTP_REQUEST Request);
static EFI_STATUS EFIAPI HttpGetResponse(_Inout_ PHTTP_CONTEXT Context,
                                         _Inout_ PHTTP_RESPONSE Response);
static EFI_STATUS EFIAPI HttpPoll(_In_ PHTTP_CONTEXT Context,
                                  _In_ BOOLEAN* StateVariable,
                                  _In_ UINTN TimeoutInNs);
static VOID EFIAPI HttpDumpHeaders(_In_ EFI_HTTP_MESSAGE* Message);
static EFI_STATUS EFIAPI HttpReadHeaders(_In_ PHTTP_RESPONSE Response);
static EFI_STATUS EFIAPI HttpInit(_In_ PHTTP_CONTEXT Context);
EFI_STATUS EFIAPI HttpCreate(_Outptr_ HTTP_CONTEXT** Context);
EFI_STATUS EFIAPI HttpConfigure(_Inout_ PHTTP_CONTEXT Context, _In_ BOOLEAN ResetFirst);
EFI_STATUS EFIAPI HttpIssueRequest(_In_ PHTTP_CONTEXT Context,
                                   _In_z_ PWSTR Url,
                                   _In_ EFI_HTTP_METHOD Method,
                                   _In_ EFI_HTTP_HEADER* Headers,
                                   _In_ UINTN HeaderCount,
                                   _In_opt_ VOID* Body,
                                   _In_ UINTN BodySize,
                                   _Outptr_ PHTTP_RESPONSE* Response);
EFI_STATUS EFIAPI HttpGetNext(_In_ PHTTP_CONTEXT Context, _In_ PHTTP_RESPONSE Response);
EFI_STATUS EFIAPI HttpFree(_In_ PHTTP_CONTEXT Context);
VOID EFIAPI HttpFreeHeaderFields(_In_ EFI_HTTP_HEADER* HeaderFields, _In_ UINTN FieldCount);
VOID EFIAPI HttpFreeResponse(_In_ PHTTP_CONTEXT Context, _In_ PHTTP_RESPONSE Response);
UINTN EFIAPI HttpGetContentLength(_In_ PHTTP_RESPONSE Response);
UINTN EFIAPI HttpGetChunkSize(_In_ PHTTP_RESPONSE Response);
UINT8* EFIAPI HttpGetChunk(_In_ PHTTP_RESPONSE Response);

//
// Interfaces
//

static EFI_STATUS EFIAPI HttpPoll(_In_ PHTTP_CONTEXT Context,
                                  _In_ BOOLEAN* StateVariable,
                                  _In_ UINTN TimeoutInNs)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_EVENT TimerEvent = NULL;

    Status = gBS->CreateEvent(EVT_TIMER, TPL_CALLBACK, NULL, NULL, &TimerEvent);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed 0x%zx", Status);
        goto Exit;
    }

    Status = gBS->SetTimer(TimerEvent, TimerRelative, TimeoutInNs);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("SetTimer() failed 0x%zx", Status);
        goto Exit;
    }

    while (*StateVariable == FALSE && gBS->CheckEvent(TimerEvent) == EFI_NOT_READY) {
        Status = Context->Http->Poll(Context->Http);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Poll() failed 0x%zx", Status);
            goto Exit;
        }
    }

Exit:
    if (TimerEvent != NULL) {
        gBS->SetTimer(TimerEvent, TimerCancel, 0);
        gBS->CloseEvent(TimerEvent);
    }
    return Status;
}

static VOID EFIAPI HttpDumpHeaders(_In_ EFI_HTTP_MESSAGE* Message)
{
    if (Message->HeaderCount == 0)
        return;

    DBG_INFO("HTTP Headers:");
    for (UINTN Index = 0; Index < Message->HeaderCount; Index++) {
        DBG_INFO("     %s: %s",
                 Message->Headers[Index].FieldName,
                 Message->Headers[Index].FieldValue);
    }
}

static EFI_STATUS EFIAPI HttpReadHeaders(_In_ PHTTP_RESPONSE Response)
{
    EFI_STATUS Status = EFI_SUCCESS;

    HttpDumpHeaders(&Response->Message);
    if (Response->ContentLength == 0) {
        for (UINTN Index = 0; Index < Response->Message.HeaderCount; Index++) {
            if (AsciiStrCmp((CHAR8*)Response->Message.Headers[Index].FieldName,
                            (CHAR8*)HTTP_HEADER_CONTENT_LENGTH) == 0) {
                Response->ContentLength = (ULONG)AsciiStrDecimalToUintn(
                    (CHAR8*)Response->Message.Headers[Index].FieldValue);
            }
        }
    }

    return Status;
}

static EFI_STATUS EFIAPI HttpInit(_In_ PHTTP_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    // EFI_HANDLE* DeviceHandles = NULL;
    // UINTN HandleCount = 0;

    EFI_SERVICE_BINDING_PROTOCOL* ServiceBinding = NULL;
    EFI_HANDLE Handle = NULL;
    EFI_HTTP_PROTOCOL* HttpProtocol = NULL;

#if 0
    //
    // Locate all DHCP SB handles
    //

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiHttpServiceBindingProtocolGuid,
                                     NULL, // No SearchKey for this search type.
                                     &HandleCount,
                                     &DeviceHandles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to locate DHCP4 service binding protocol handles, 0x%zx", Status);
        goto Exit;
    }

    //
    // Locate DHCP SB handles with HTTP protocol
    //

    for (UINTN Index = 0; Index < HandleCount; Index++) {
        Status = ServiceBindingOpenProtocol(DeviceHandles[Index],
                                            &gEfiHttpServiceBindingProtocolGuid,
                                            &gEfiHttpProtocolGuid,
                                            &Context->HttpSvcBindingProtocol,
                                            &Context->HttpHandle,
                                            (PVOID*)&Context->Http);
        if (!EFI_ERROR(Status)) {
            Context->ParentHandle = DeviceHandles[Index];
            break;
        }
    }
#endif

    Status = gBS->LocateProtocol(&gEfiHttpServiceBindingProtocolGuid, NULL, &ServiceBinding);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Error 0x%zx", Status);
        goto Exit;
    }

    Status = ServiceBinding->CreateChild(ServiceBinding, &Handle);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Error 0x%zx", Status);
        goto Exit;
    }

    Status = gBS->OpenProtocol(Handle,
                               &gEfiHttpProtocolGuid,
                               &HttpProtocol,
                               gImageHandle,
                               NULL,
                               EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Error 0x%zx", Status);
        goto Exit;
    }

    Context->HttpSvcBindingProtocol = ServiceBinding;
    Context->HttpHandle = Handle;
    Context->Http = HttpProtocol;

Exit:
    // gBS->FreePool(DeviceHandles);
    return Status;
}

UINTN EFIAPI HttpGetContentLength(_In_ PHTTP_RESPONSE Response)
{
    return Response->ContentLength;
}

UINTN EFIAPI HttpGetChunkSize(_In_ PHTTP_RESPONSE Response)
{
    return Response->Message.BodyLength;
}

UINT8* EFIAPI HttpGetChunk(_In_ PHTTP_RESPONSE Response)
{
    return Response->Message.Body;
}

EFI_STATUS EFIAPI HttpCreate(_Outptr_ HTTP_CONTEXT** Context)
{
    EFI_STATUS Status = EFI_SUCCESS;
    HTTP_CONTEXT* RetContext = NULL;

    if (Context == NULL) {
        DBG_ERROR("Context is NULL");
        return EFI_INVALID_PARAMETER;
    }

    // Initialize HTTP context
    RetContext = AllocateZeroPool(sizeof(HTTP_CONTEXT));
    if (RetContext == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        DBG_ERROR("Unable to allocate HTTP_CONTEXT structure");
        goto Exit;
    }

    Status = HttpInit(RetContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpInit() failed : 0x%zx", Status);
        goto Exit;
    }

#if 0
    Status = DhcpInit(RetContext->ParentHandle, &RetContext->Dhcp4Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("DhcpInit() failed : 0x%zx", Status);
        goto Exit;
    }
#endif
    Status = HttpConfigure(RetContext, FALSE);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpConfigure() failed 0x%zx", Status);
        goto Exit;
    }

    DBG_INFO("Configured Http module");

    *Context = RetContext;
    return Status;

Exit:
    HttpFree(RetContext);

    return Status;
}

EFI_STATUS EFIAPI HttpConfigure(_Inout_ PHTTP_CONTEXT Context, _In_ BOOLEAN ResetFirst)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HTTP_CONFIG_DATA HttpConfig = {0};
    EFI_HTTPv4_ACCESS_POINT IPv4Node = {0};

#if 0
    // TODO: Add check if DHCP already started, to avoid reentering this path
    // every time.
    Status = DhcpStart(Context->Dhcp4Context);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("DhcpStart() failed : 0x%zx", Status);
        goto Exit;
    }
#endif

    if (ResetFirst) {
        Status = Context->Http->Configure(Context->Http, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("HTTP Configure() to reset failed : 0x%zx", Status);
            goto Exit;
        }
    }

    // Configure Http
    HttpConfig.HttpVersion = HttpVersion11;
    HttpConfig.TimeOutMillisec = 0;
    HttpConfig.LocalAddressIsIPv6 = FALSE;
    ZeroMem(&IPv4Node, sizeof(IPv4Node));
    IPv4Node.UseDefaultAddress = TRUE;
    HttpConfig.AccessPoint.IPv4Node = &IPv4Node;

    Status = Context->Http->Configure(Context->Http, &HttpConfig);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HTTP Configure() failed : 0x%zx", Status);
        goto Exit;
    }

Exit:
    return Status;
}

EFI_STATUS EFIAPI HttpFree(_In_ PHTTP_CONTEXT Context)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (Context == NULL) {
        goto Exit;
    }

    if (Context->HttpHandle != NULL) {
        Status = gBS->CloseProtocol(Context->HttpHandle, &gEfiHttpProtocolGuid, gImageHandle, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("CloseProtocol() failed : 0x%zx", Status);
            goto Exit;
        }

        Status = Context->HttpSvcBindingProtocol->DestroyChild(Context->HttpSvcBindingProtocol,
                                                               Context->HttpHandle);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("DestroyChild() failed : 0x%zx", Status);
            goto Exit;
        }
    }

    FreePool(Context);

Exit:
    return Status;
}

VOID EFIAPI HttpFreeHeaderFields(_In_ EFI_HTTP_HEADER* HeaderFields, _In_ UINTN FieldCount)
{
    UINTN Index;

    if (HeaderFields != NULL) {
        for (Index = 0; Index < FieldCount; Index++) {
            FreePool(HeaderFields[Index].FieldName);
            FreePool(HeaderFields[Index].FieldValue);
        }

        FreePool(HeaderFields);
    }
}

static EFI_STATUS EFIAPI HttpSendRequest(_In_ PHTTP_CONTEXT Context, _Inout_ PHTTP_REQUEST Request)
{
    EFI_STATUS Status = EFI_SUCCESS;

    DBG_INFO_U(L"HTTP request url: %s", Request->Url);

    Request->CallbackTriggered = FALSE;

    //
    // Send request
    //

    Status = Context->Http->Request(Context->Http, &Request->Token);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Request() failed 0x%zx", Status);
        goto Exit;
    }

    //
    // Poll for the request to complete
    //

    Status = HttpPoll(Context, &Request->CallbackTriggered, HTTP_REQUEST_WAIT_TIMEOUT);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpPoll() failed 0x%zx", Status);
        goto Exit;
    }

    if (!Request->CallbackTriggered) {
        DBG_INFO("Cancelling the request 0x%zx", Status);
        Status = Context->Http->Cancel(Context->Http, &Request->Token);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Cancel() failed 0x%zx", Status);
        }
        goto Exit;
    }

Exit:
    return Status;
}

static EFI_STATUS EFIAPI HttpGetResponse(_Inout_ PHTTP_CONTEXT Context,
                                         _Inout_ PHTTP_RESPONSE Response)
{
    EFI_STATUS Status = EFI_SUCCESS;

    Response->Data.StatusCode = HTTP_STATUS_UNSUPPORTED_STATUS;
    Response->Message.HeaderCount = 0;

    //
    // Get response
    //

    Response->CallbackTriggered = FALSE;

    Status = Context->Http->Response(Context->Http, &Response->Token);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Response() failed 0x%zx", Status);
        goto Exit;
    }

    //
    // Poll for the response
    //

    Status = HttpPoll(Context, &Response->CallbackTriggered, HTTP_RESPONSE_WAIT_TIMEOUT);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpPoll() failed 0x%zx", Status);
        goto Exit;
    }

    if (!Response->CallbackTriggered) {
        DBG_INFO("Cancelling the response 0x%zx", Status);
        Status = Context->Http->Cancel(Context->Http, &Response->Token);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Cancel() failed 0x%zx", Status);
        }
        goto Exit;
    }

    // DBG_INFO("HTTP status: %s(%d)",
    //              HttpStatusMap[Response->Data.StatusCode].String,
    //              HttpStatusMap[Response->Data.StatusCode].Value);

    Response->ContentDownloaded += Response->Message.BodyLength;

    // DBG_INFO("HTTP Current Chunk Length %zu bytes", Response->Message.BodyLength);
    // DBG_INFO("HTTP Total Content Downloaded %zu bytes", Response->ContentDownloaded);

    HttpReadHeaders(Response);

    // DBG_INFO("HTTP Response->ContentLength %zu bytes", Response->ContentLength);

    FreePool(Response->Message.Headers);

    if (Response->ContentDownloaded == Response->ContentLength) {
        // Cancel any remaining http transfers
    }

Exit:
    return Status;
}

static EFI_STATUS HttpCreateRequestObject(_Inout_ PHTTP_CONTEXT Context,
                                          _In_ PWSTR Url,
                                          _In_ EFI_HTTP_METHOD Method,
                                          _In_ EFI_HTTP_HEADER* Headers,
                                          _In_ UINTN HeaderCount,
                                          _In_opt_ VOID* Body,
                                          _In_ UINTN BodyLength,
                                          _Outptr_ PHTTP_REQUEST* Request)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_REQUEST RetRequest = NULL;

    UNREFERENCED_PARAMETER(Context);

    if (Url == NULL) {
        DBG_ERROR("Url is NULL");
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    RetRequest = AllocateZeroPool(sizeof(HTTP_REQUEST));
    if (RetRequest == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        DBG_ERROR("AllocatePool() failed to allocate HTTP_REQUEST");
        goto Exit;
    }

    RetRequest->Data.Method = Method;
    RetRequest->Data.Url = Url;

    RetRequest->Message.Data.Request = &RetRequest->Data;
    RetRequest->Message.HeaderCount = HeaderCount;
    RetRequest->Message.Headers = Headers;
    RetRequest->Message.BodyLength = BodyLength;
    RetRequest->Message.Body = Body;

    RetRequest->Token.Message = &RetRequest->Message;
    RetRequest->Token.Event = NULL;
    RetRequest->Token.Status = EFI_SUCCESS;

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              HttpRequestCallback,
                              RetRequest,
                              &RetRequest->Token.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed 0x%zx", Status);
        goto Exit;
    }

    RetRequest->Url = Url;

    *Request = RetRequest;
    return Status;

Exit:
    if (RetRequest && RetRequest->Token.Event) {
        gBS->CloseEvent(RetRequest->Token.Event);
    }

    //
    // Let caller free the HTTP headers
    //

    FreePool(RetRequest);

    return Status;
}

static EFI_STATUS HttpCreateResponseObject(_Inout_ PHTTP_CONTEXT Context,
                                           _In_ EFI_HTTP_METHOD Method,
                                           _Outptr_ PHTTP_RESPONSE* Response)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_RESPONSE RetResponse = NULL;

    UNREFERENCED_PARAMETER(Context);

    RetResponse = AllocateZeroPool(sizeof(HTTP_RESPONSE));
    if (RetResponse == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        DBG_ERROR("AllocatePool() failed to allocate HTTP_RESPONSE");
        goto Exit;
    }

    if (Method == HttpMethodHead) {
        RetResponse->Message.BodyLength = 0;
        RetResponse->Message.Body = NULL;
    } else {
        RetResponse->Message.BodyLength = HTTP_DEFAULT_RESPONSE_BUFFER_SIZE;
        RetResponse->Message.Body = AllocateZeroPool(RetResponse->Message.BodyLength);
        if (RetResponse->Message.Body == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            DBG_ERROR("AllocatePool() failed to allocate %zu bytes for http response",
                      RetResponse->Message.BodyLength);
            goto Exit;
        }
    }

    RetResponse->Data.StatusCode = HTTP_STATUS_UNSUPPORTED_STATUS;
    RetResponse->Message.Data.Response = &RetResponse->Data;
    RetResponse->Message.HeaderCount = 0;
    RetResponse->Message.Headers = NULL;

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              HttpResponseCallback,
                              RetResponse,
                              &RetResponse->Token.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed 0x%zx", Status);
        goto Exit;
    }

    RetResponse->Token.Status = EFI_SUCCESS;
    RetResponse->Token.Message = &RetResponse->Message;

    *Response = RetResponse;
    return Status;

Exit:
    if (RetResponse) {
        FreePool(RetResponse->Message.Body);
        if (RetResponse->Token.Event) {
            gBS->CloseEvent(RetResponse->Token.Event);
        }
    }

    FreePool(RetResponse);

    return Status;
}

EFI_STATUS EFIAPI HttpIssueRequest(_In_ PHTTP_CONTEXT Context,
                                   _In_z_ PWSTR Url,
                                   _In_ EFI_HTTP_METHOD Method,
                                   _In_ EFI_HTTP_HEADER* Headers,
                                   _In_ UINTN HeaderCount,
                                   _In_opt_ VOID* Body,
                                   _In_ UINTN BodyLength,
                                   _Outptr_ PHTTP_RESPONSE* Response)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_REQUEST Request = NULL;
    PHTTP_RESPONSE RetResponse = NULL;

    if (Response == NULL || Url == NULL) {
        Status = EFI_INVALID_PARAMETER;
        DBG_ERROR("Invalid parameters 0x%zx", Status);
        goto Exit;
    }

    //
    // Due to what is seemingly a bug in UEFI Http implementation, we need to manually
    // reset and reconfigure HTTP instance whenever previous URL is different,
    // apparently. Otherwise, the EFI_HTT_PROTOCOL->Request() call fails with
    // EFI_ACCESS_DENIED.
    //

    Status = HttpConfigure(Context, TRUE);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpConfigure() failed 0x%zx", Status);
        goto Exit;
    }

    //
    // Create Request Object
    //

    Status = HttpCreateRequestObject(Context,
                                     Url,
                                     Method,
                                     Headers,
                                     HeaderCount,
                                     Body,
                                     BodyLength,
                                     &Request);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreateRequestObject() failed 0x%zx", Status);
        goto Exit;
    }

    //
    // Send Request
    //

    Status = HttpSendRequest(Context, Request);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpSendRequest() failed 0x%zx", Status);
        goto Exit;
    }

    //
    // Create Response Object
    //

    Status = HttpCreateResponseObject(Context, Method, &RetResponse);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreateResponseObject() failed 0x%zx", Status);
        goto Exit;
    }

    RetResponse->Request = Request;

    //
    // Get Reponse
    //

    Status = HttpGetResponse(Context, RetResponse);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpGetResponse() failed 0x%zx", Status);
        goto Exit;
    }

    *Response = RetResponse;
    return Status;

Exit:
    return Status;
}

EFI_STATUS EFIAPI HttpGetNext(_In_ PHTTP_CONTEXT Context, _In_ PHTTP_RESPONSE Response)
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (Response == NULL) {
        Status = EFI_INVALID_PARAMETER;
        DBG_ERROR("Invalid parameters 0x%zx", Status);
        goto Exit;
    }

    // DBG_INFO("HTTP ContentDownloaded %zu bytes", Response->ContentDownloaded);
    // DBG_INFO("HTTP ContentLength %zu bytes", Response->ContentLength);

    if (Response->ContentDownloaded >= Response->ContentLength) {
        Status = EFI_END_OF_FILE;
        goto Exit;
    }

    //
    // UEFI Spec: ..This allows the client to download a large file in chunks
    // instead of into one contiguous block of memory. Similar to HTTP request,
    // if Body is not NULL and BodyLength is non-zero and all other fields are
    // NULL or 0, the HTTP driver will queue a receive token to underlying TCP
    // instance. If data arrives in the receive buffer, up to BodyLength bytes
    // of data will be copied to Body. The HTTP driver will then update
    // BodyLength with the amount of bytes received and copied to Body.
    //
    // Hence setting below fields to zero
    //

    Response->Message.HeaderCount = 0;
    Response->Message.Headers = NULL;
    Response->Message.Data.Response = NULL;
    Response->Message.BodyLength = HTTP_DEFAULT_RESPONSE_BUFFER_SIZE;
    Status = HttpGetResponse(Context, Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpGetResponse() failed 0x%zx", Status);
        goto Exit;
    }

Exit:
    return Status;
}

static VOID HttpFreeRequest(_In_ PHTTP_CONTEXT Context, _In_ PHTTP_REQUEST Request)
{
    //
    // Cancel any pending transfers
    //

    Context->Http->Cancel(Context->Http, &Request->Token);

    gBS->CloseEvent(Request->Token.Event);

    FreePool(Request);
}

VOID EFIAPI HttpFreeResponse(_In_ PHTTP_CONTEXT Context, _In_ PHTTP_RESPONSE Response)
{
    if (Response != NULL) {
        HttpFreeRequest(Context, Response->Request);

        //
        // Cancel any pending transfers
        //

        Context->Http->Cancel(Context->Http, &Response->Token);

        gBS->CloseEvent(Response->Token.Event);
        FreePool(Response->Message.Body);
        FreePool(Response);
    }
}

//
// Local functions
//

static VOID EFIAPI HttpRequestCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);

    HTTP_REQUEST* Request = (HTTP_REQUEST*)Context;
    Request->CallbackTriggered = TRUE;
}

static VOID EFIAPI HttpResponseCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);

    HTTP_RESPONSE* Response = (HTTP_RESPONSE*)Context;
    Response->CallbackTriggered = TRUE;
}

static EFI_STATUS BuildRequestHeaders(_In_ CHAR8* Url,
                                      _Outptr_result_buffer_(*Count) EFI_HTTP_HEADER** Headers,
                                      _Out_ UINTN* Count)
{
    EFI_STATUS Status = EFI_SUCCESS;
    VOID* UrlParser = NULL;
    CHAR8* Hostname = NULL;
    UINT16 Port = 0;
    CHAR8* FormatString = t("%s:%d"); // Host = hostname[:port]
    EFI_HTTP_HEADER* RequestHeaders;
    UINTN HeaderCount;

    //
    // Note: Currently not adding any special headers besides 'Host'. If more headers get added,
    // updated HeaderCount below.
    //

    HeaderCount = 1;

    RequestHeaders = AllocateZeroPool(sizeof(EFI_HTTP_HEADER) * HeaderCount); // Allocate headers
    if (RequestHeaders == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Status = HttpParseUrl(Url, (UINT32)AsciiStrLen(Url), FALSE, &UrlParser);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpParseUrl() failed 0x%zx", Status);
        goto Exit;
    }

    Status = HttpUrlGetHostName(Url, UrlParser, &Hostname);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpUrlGetHostName() failed 0x%zx", Status);
        goto Exit;
    }

    Status = HttpUrlGetPort(Url, UrlParser, &Port);
    if (EFI_ERROR(Status)) {
        if (Status == EFI_NOT_FOUND) {
            //
            // No port found, reset format specifier to include
            // just hostname and proceed.
            //

            Status = EFI_SUCCESS;
            FormatString = t("%s");
        } else {
            DBG_ERROR("HttpUrlGetPort() failed 0x%zx", Status);
            goto Exit;
        }
    }

    UINTN Result = 0;
    CHAR8 AsciiHostHeaderValue[1024] = {0};

    Result = StringCchPrintfA((STRSAFE_LPSTR)AsciiHostHeaderValue,
                              _countof(AsciiHostHeaderValue),
                              (STRSAFE_LPCSTR)FormatString,
                              Hostname,
                              Port);
    if (FAILED(Result)) {
        DBG_ERROR("StringCchPrintfA failed 0x%zx", Result);
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    RequestHeaders[0].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_HOST) + 1,
                                                   HTTP_HEADER_HOST);
    if (RequestHeaders[0].FieldName == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    RequestHeaders[0].FieldValue = AllocateCopyPool(AsciiStrLen(AsciiHostHeaderValue) + 1,
                                                    AsciiHostHeaderValue);
    if (RequestHeaders[0].FieldValue == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    *Headers = RequestHeaders;
    *Count = HeaderCount;

Exit:

    if (EFI_ERROR(Status)) {
        if (Status == EFI_OUT_OF_RESOURCES) {
            DBG_ERROR("Out of memory");
        }

        HttpFreeHeaderFields(RequestHeaders, HeaderCount);
    }

    HttpUrlFreeParser(UrlParser);
    FreePool(Hostname);
    return Status;
}

static EFI_STATUS EFIAPI DcatBuildRequestHeaders(_In_z_ CHAR8* Url,
                                                 _In_ UINTN BodyLength,
                                                 _In_z_ CHAR8* ContentType,
                                                 _Outptr_result_buffer_(*Count)
                                                     EFI_HTTP_HEADER** Headers,
                                                 _Out_ UINTN* Count)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Result = 0;
    VOID* UrlParser = NULL;
    EFI_HTTP_HEADER* RequestHeaders = NULL;
    UINTN HeaderCount = 0;
    CHAR8 ContentLengthString[21]; // 2**64 is 1.8E19, or 20 digits. +1 for a NULL.

    if (Url == NULL || ContentType == NULL || Headers == NULL || Count == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    if (BodyLength != 0) {
        HeaderCount = 5;
    } else {
        HeaderCount = 3;
    }

    RequestHeaders = AllocateZeroPool(sizeof(EFI_HTTP_HEADER) * HeaderCount); // Allocate headers
    if (NULL == RequestHeaders) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    UrlParser = NULL;

    Status = HttpParseUrl(Url, (UINT32)AsciiStrLen(Url), FALSE, &UrlParser);
    if (EFI_ERROR(Status)) {
        goto Exit;
    }

    RequestHeaders[0].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_HOST) + 1,
                                                   HTTP_HEADER_HOST);
    if (RequestHeaders[0].FieldName == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    RequestHeaders[1].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_USER_AGENT) + 1,
                                                   HTTP_HEADER_USER_AGENT);
    if (RequestHeaders[1].FieldName == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    RequestHeaders[1].FieldValue = AllocateCopyPool(AsciiStrLen(HEADER_AGENT_VALUE) + 1,
                                                    HEADER_AGENT_VALUE);
    if (RequestHeaders[1].FieldValue == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    RequestHeaders[2].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_ACCEPT) + 1,
                                                   HTTP_HEADER_ACCEPT);
    if (RequestHeaders[2].FieldName == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    RequestHeaders[2].FieldValue = AllocateCopyPool(AsciiStrLen(HEADER_ACCEPT_VALUE) + 1,
                                                    HEADER_ACCEPT_VALUE);
    if (RequestHeaders[2].FieldValue == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = HttpUrlGetHostName(Url, UrlParser, (CHAR8**)(VOID**)&RequestHeaders[0].FieldValue);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to get Host Name from URL");
        goto Exit;
    }

    if (0 != BodyLength) {
        RequestHeaders[3].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_CONTENT_LENGTH) + 1,
                                                       HTTP_HEADER_CONTENT_LENGTH);
        if (RequestHeaders[3].FieldName == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Exit;
        }

        Result = StringCchPrintfA((STRSAFE_LPSTR)ContentLengthString,
                                  _countof(ContentLengthString),
                                  (STRSAFE_LPCSTR) "%zu",
                                  BodyLength);
        if (FAILED(Result)) {
            DBG_ERROR("StringCchPrintfA failed 0x%zx", Result);
            Status = EFI_INVALID_PARAMETER;
            goto Exit;
        }

        RequestHeaders[3].FieldValue = AllocateCopyPool(AsciiStrLen(ContentLengthString) + 1,
                                                        ContentLengthString);
        if (RequestHeaders[3].FieldValue == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Exit;
        }

        RequestHeaders[4].FieldName = AllocateCopyPool(AsciiStrLen(HTTP_HEADER_CONTENT_TYPE) + 1,
                                                       HTTP_HEADER_CONTENT_TYPE);
        if (RequestHeaders[4].FieldName == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Exit;
        }

        RequestHeaders[4].FieldValue = AllocateCopyPool(AsciiStrLen(ContentType) + 1, ContentType);
        if (RequestHeaders[4].FieldValue == NULL) {
            Status = EFI_OUT_OF_RESOURCES;
            goto Exit;
        }
    }

    *Headers = RequestHeaders;
    *Count = HeaderCount;

Exit:

    if (EFI_ERROR(Status)) {
        if (Status == EFI_OUT_OF_RESOURCES) {
            DBG_ERROR("Out of memory");
        }

        HttpFreeHeaderFields(RequestHeaders, HeaderCount);
    }

    HttpUrlFreeParser(UrlParser);

    return Status;
}

//
// Constants/Macros
//

#define EDKII_HTTP_TLS_CIPHER_LIST_VARIABLE L"HttpTlsCipherList"
#define EFI_TLS_CA_CERTIFICATE_VARIABLE     L"TlsCaCertificate"
#define ROOT_CA_CERT_FILENAME               L"rootCertificate.cer"
#define INTERMEDIATE_CA_CERT_FILENAME       L"intermediateCertificate.cer"

#define EFI_MS_UEFI_INFO_PROTOCOL_GUID                     \
    {                                                      \
        0x12345678, 0xfa49, 0x4f65,                        \
        {                                                  \
            0xb0, 0x3c, 0x55, 0x1d, 0xb5, 0x3c, 0x8c, 0x23 \
        }                                                  \
    }

//
// Structs
//

#pragma pack(push, 1)
typedef struct _EFI_SIGNATURE_DATA2 {
    //
    // An identifier which identifies the agent which added the signature to the list.
    //
    GUID SignatureOwner;

    //
    // The format of the signature is defined by the SignatureType.
    //
    UINT8 SignatureData[1];
} EFI_SIGNATURE_DATA2;
#pragma pack(pop)

typedef struct _CERT {
    UINT32 Size;
    const UINT8* Buffer;
    BOOLEAN Revoked;
} CERT, *PCERT;

//
// Update this global cert array on an as needed basis only. They should only
// contain intermediate (or more scoped) certs used for cert pinning
// against DCAT and other trusted endpoints.
//

static CERT TlsCaCertArray[] = {
    {.Size = ARRAYSIZE(microsoft_update_secure_server_ca_2_1),
     .Buffer = microsoft_update_secure_server_ca_2_1,
     .Revoked = FALSE},
    {.Size = ARRAYSIZE(httpbin_cert), .Buffer = httpbin_cert, .Revoked = FALSE},
};

//
// Variables
//

EFI_GUID EDKII_HTTP_TLS_CIPHER_LIST_GUID = {0x46ddb415,
                                            0x5244,
                                            0x49c7,
                                            {0x93, 0x74, 0xf0, 0xe2, 0x98, 0xe7, 0xd3, 0x86}};
EFI_GUID EFI_TLS_CA_CERTIFICATE_GUID = {0xfd2340D0,
                                        0x3dab,
                                        0x4349,
                                        {0xa6, 0xc7, 0x3b, 0x4f, 0x12, 0xb4, 0x8e, 0xae}};
static EFI_STATUS TlsSetCACertList()
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN CertCount = 0;
    UINTN TotalCertsSize = 0;
    UINTN CertDatabaseSize = 0;
    EFI_SIGNATURE_LIST* Cert = NULL;
    EFI_SIGNATURE_LIST* LocalCert = NULL;
    EFI_SIGNATURE_DATA2* CertData = NULL;

    CertCount = ARRAYSIZE(TlsCaCertArray);

    for (UINT8 i = 0; i < CertCount; i++) {
        if (!TlsCaCertArray[i].Revoked) {
            TotalCertsSize += TlsCaCertArray[i].Size;
        }
    }

    CertDatabaseSize = CertCount * sizeof(EFI_SIGNATURE_LIST) +
                       CertCount * FIELD_OFFSET(EFI_SIGNATURE_DATA2, SignatureData) +
                       TotalCertsSize;

    Cert = AllocateZeroPool(CertDatabaseSize);
    if (Cert == NULL) {
        DBG_ERROR("Out of memory.");
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    LocalCert = Cert;

    for (UINT8 i = 0; i < CertCount; i++) {
        if (!TlsCaCertArray[i].Revoked) {
            Cert->SignatureListSize = sizeof(EFI_SIGNATURE_LIST) +
                                      FIELD_OFFSET(EFI_SIGNATURE_DATA2, SignatureData) +
                                      (UINT32)TlsCaCertArray[i].Size;
            Cert->SignatureHeaderSize = 0;
            Cert->SignatureSize = FIELD_OFFSET(EFI_SIGNATURE_DATA2, SignatureData) +
                                  (UINT32)TlsCaCertArray[i].Size;
            CopyMem(&Cert->SignatureType, &gEfiCertX509Guid, sizeof(EFI_GUID));

            CertData = (EFI_SIGNATURE_DATA2*)((UINT8*)Cert + sizeof(EFI_SIGNATURE_LIST));
            CopyMem(&CertData->SignatureOwner,
                    &(EFI_GUID)EFI_MS_UEFI_INFO_PROTOCOL_GUID,
                    sizeof(EFI_GUID));
            CopyMem((UINT8*)(CertData->SignatureData),
                    TlsCaCertArray[i].Buffer,
                    TlsCaCertArray[i].Size);

            Cert = (EFI_SIGNATURE_LIST*)((UINT8*)Cert + sizeof(EFI_SIGNATURE_LIST) +
                                         FIELD_OFFSET(EFI_SIGNATURE_DATA2, SignatureData) +
                                         TlsCaCertArray[i].Size);
        }
    }

    Status = gRT->SetVariable(EFI_TLS_CA_CERTIFICATE_VARIABLE,
                              &EFI_TLS_CA_CERTIFICATE_GUID,
                              EFI_VARIABLE_BOOTSERVICE_ACCESS,
                              CertDatabaseSize,
                              LocalCert);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to set TLS certificate(s). 0x%zx", Status);
    }

    FreePool(Cert);
    Cert = NULL;

Exit:

    FreePool(Cert);

    return Status;
}

//
// HTTP/HTTPS test suite
//

static EFI_STATUS HttpGetRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("http://httpbin.org/ip");
    CHAR16* Url = T("http://httpbin.org/ip");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodGet,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpsGetRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("https://httpbin.org/ip");
    CHAR16* Url = T("https://httpbin.org/ip");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = TlsSetCACertList();
    if (EFI_ERROR(Status)) {
        DBG_ERROR("TlsSetCACertList() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodGet,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpHeadRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("http://httpbin.org/ip");
    CHAR16* Url = T("http://httpbin.org/ip");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodHead,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpsHeadRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("https://httpbin.org/ip");
    CHAR16* Url = T("https://httpbin.org/ip");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = TlsSetCACertList();
    if (EFI_ERROR(Status)) {
        DBG_ERROR("TlsSetCACertList() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodHead,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpPostRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("http://httpbin.org/post");
    CHAR16* Url = T("http://httpbin.org/post");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodPost,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpsPostRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t("https://httpbin.org/post");
    CHAR16* Url = T("https://httpbin.org/post");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = TlsSetCACertList();
    if (EFI_ERROR(Status)) {
        DBG_ERROR("TlsSetCACertList() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = BuildRequestHeaders(AsciiUrl, &HttpHeaders, &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodPost,
                              HttpHeaders,
                              HeaderCount,
                              NULL,
                              0,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, ChunkSize);

        Status = HttpGetNext(HttpContext, Response);
        if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
            DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static EFI_STATUS HttpsPostTLSECCRequest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                         _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PHTTP_CONTEXT HttpContext = NULL;
    PHTTP_RESPONSE Response = NULL;
    CHAR8* AsciiUrl = t(
        "https://fe3.delivery.mp.microsoft.com:443/UpdateMetadataService/updates/search/v1/bydeviceinfo/");
    CHAR16* Url = T(
        "https://fe3.delivery.mp.microsoft.com:443/UpdateMetadataService/updates/search/v1/bydeviceinfo/");
    EFI_HTTP_HEADER* HttpHeaders = NULL;
    UINTN HeaderCount = 0;
    UINTN BodyLength = 0;

#define REQUEST_JSON \
    t("{ \"Products\" : \"PN=Client.OS.RS2.amd64&V=10.0.22518.1000\", \"DeviceAttributes\" : \"MediaVersion=10.0.22518.1000;MediaBranch=rs_prerelease;OSSkuId=4;App=Setup360;AppVer=10.0;DUScan=1;DUInternal=0\" }")

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = TlsSetCACertList();
    if (EFI_ERROR(Status)) {
        DBG_ERROR("TlsSetCACertList() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpCreate(&HttpContext);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    BodyLength = AsciiStrLen(REQUEST_JSON);

    Status = DcatBuildRequestHeaders(AsciiUrl,
                                     BodyLength,
                                     HEADER_CONTENT_JSON,
                                     &HttpHeaders,
                                     &HeaderCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("BuildRequestHeaders() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = HttpIssueRequest(HttpContext,
                              Url,
                              HttpMethodPost,
                              HttpHeaders,
                              HeaderCount,
                              REQUEST_JSON,
                              BodyLength,
                              &Response);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HttpIssueRequest() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    do {
        UINTN ChunkSize = HttpGetChunkSize(Response);
        UINT8* Chunk = HttpGetChunk(Response);

        if (ChunkSize == 0) {
            break;
        }

        HexDump(Chunk, MIN(ChunkSize, 0x100));
        break;

        // Status = HttpGetNext(HttpContext, Response);
        // if (EFI_ERROR(Status) && Status != EFI_END_OF_FILE) {
        //     DBG_ERROR("HttpGetNext() failed : %s(0x%zx)", E(Status), Status);
        //     goto Exit;
        // }
    } while (Status != EFI_END_OF_FILE);

    Status = EFI_SUCCESS;

Exit:

    if (HttpHeaders != NULL) {
        HttpFreeHeaderFields(HttpHeaders, HeaderCount);
    }

    if (Response != NULL) {
        HttpFreeResponse(HttpContext, Response);
    }

    if (HttpContext != NULL) {
        HttpFree(HttpContext);
    }

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("httpgetrequest"),
        .Description = t("Make http get request to http://httpbin.org/ip"),
        .DutTestFn = HttpGetRequest,
    },
    {
        .Name = t("httpsgetrequest"),
        .Description = t("Make https get request to https://httpbin.org/ip"),
        .DutTestFn = HttpsGetRequest,
    },
    {
        .Name = t("httpheadrequest"),
        .Description = t("Make http head request to http://httpbin.org/ip"),
        .DutTestFn = HttpHeadRequest,
    },
    {
        .Name = t("httpsheadrequest"),
        .Description = t("Make https head request to https://httpbin.org/ip"),
        .DutTestFn = HttpsHeadRequest,
    },
    {
        .Name = t("httppostrequest"),
        .Description = t("Make http post request to http://httpbin.org/post"),
        .DutTestFn = HttpPostRequest,
    },
    {
        .Name = t("httpspostrequest"),
        .Description = t("Make https post request to https://httpbin.org/post"),
        .DutTestFn = HttpsPostRequest,
    },
    {
        .Name = t("httpsposttlseccrequest"),
        .Description = t("Make https post request to TLS ECC enforce resource(MS DCAT)"),
        .DutTestFn = HttpsPostTLSECCRequest,
    },
};

BM_TEST_SUITE HttpTestSuite = {
    .Description = t("HTTP/HTTPS test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

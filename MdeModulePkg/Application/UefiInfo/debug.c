//
// Global includes
//
#include "common.h"
#include "file.h"
#include "utils.h"
#include "strsafe.h"

#include "windbgserver.h"
#include <Protocol/DebugPort.h>

#define WRITE_TIMEOUT 1000

//
// Variables
//
static EFI_DEBUGPORT_PROTOCOL* gEfiDebugPortProtocol = NULL;
#define LOG_FILE_NAME L"uefiinfo.log"
static EFI_FILE_PROTOCOL* gsLogFile = NULL;

static EFI_MS_WINDBG_SERVER_PROTOCOL* gEfiMsWindbgServerProtocol = NULL;

//
// Prototypes
//
static VOID DebugWriteToSerialPort(IN CHAR8* Buffer, IN UINTN BufferLength);
static VOID DebugWriteToFile(IN CHAR8* Buffer, IN UINTN BufferLength);
static VOID DebugWrite(IN CHAR8* Str, IN UINTN BufferLength);
static EFI_STATUS DebugOpenFile();
static CHAR8* GetDebugFlagStr(DEBUG_FLAGS DebugFlag);
static CHAR16* GetDebugFlagStrU(DEBUG_FLAGS DebugFlag);

//
// Interfaces
//

EFI_STATUS EFIAPI DebugInit()
{
    EFI_STATUS Status = EFI_SUCCESS;

    //
    // Locate Windbg protocol
    //
    Status = gBS->LocateProtocol(&(EFI_GUID)EFI_MS_WINDBG_SERVER_PROTOCOL_GUID,
                                 NULL,
                                 (VOID**)&gEfiMsWindbgServerProtocol);
    if (EFI_ERROR(Status)) {
        Status = EFI_SUCCESS;
        gEfiMsWindbgServerProtocol = NULL;
    } else {
        //
        // Dump .reload command
        //

        gEfiMsWindbgServerProtocol->DumpImageInfo(gEfiMsWindbgServerProtocol, gImageHandle);
    }

    //
    // Open log file
    //

    Status = DebugOpenFile();
    if (EFI_ERROR(Status)) {
        Status = EFI_SUCCESS;
        gsLogFile = NULL;
    }

    //
    // Open debugport/serial port protocol file
    //

    Status = gBS->LocateProtocol(&gEfiDebugPortProtocolGuid, NULL, (VOID**)&gEfiDebugPortProtocol);
    if (EFI_ERROR(Status)) {
        Status = EFI_SUCCESS;
        gEfiDebugPortProtocol = NULL;
        goto Exit;
    }

    gEfiDebugPortProtocol->Reset(gEfiDebugPortProtocol);

Exit:
    return Status;
}

VOID EFIAPI DebugPrintFormatted(IN DEBUG_FLAGS DebugFlag,
                                IN CHAR8* Fmt,
                                ...)
{
    CHAR8 Buffer[512];
    VA_LIST ArgList;

    UNREFERENCED_PARAMETER(DebugFlag);

    VA_START(ArgList, Fmt);
    AsciiVSPrint(Buffer, sizeof(Buffer), Fmt, ArgList);
    VA_END(ArgList);

    if (Buffer) {
        DebugWrite(Buffer, _countof(Buffer));
    }
}

VOID EFIAPI DebugPrintFormattedU(IN DEBUG_FLAGS DebugFlag,
                                 IN CHAR16* FmtW,
                                 ...)
{
    CHAR16 BufferWide[512];
    VA_LIST ArgList;

    UNREFERENCED_PARAMETER(DebugFlag);

    VA_START(ArgList, FmtW);
    UnicodeVSPrint(BufferWide, sizeof(BufferWide), (CHAR16*)FmtW, ArgList);
    VA_END(ArgList);

    if (BufferWide) {
        CHAR8 Buffer[1024];
        UnicodeStrToAsciiStrS(BufferWide, Buffer, _countof(Buffer));
        DebugWrite(Buffer, _countof(Buffer));
    }
}

VOID EFIAPI DebugClose()
{
    if (gsLogFile) {
        gsLogFile->Flush(gsLogFile);
        gsLogFile->Close(gsLogFile);
        gsLogFile = NULL;
    }
}

//
// Local functions
//

static EFI_STATUS DebugOpenFile()
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
    EFI_FILE_PROTOCOL* Root = NULL;
    EFI_LOADED_IMAGE* LoadedImage = NULL;

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Open SIMPLE_FILE_SYSTEM_PROTOCOL for the volume from which the
    // current image is loaded
    Status = gBS->HandleProtocol(LoadedImage->DeviceHandle,
                                 &gEfiSimpleFileSystemProtocolGuid,
                                 (void**)&SimpleFileSystem);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    Status = Root->Open(Root,
                        &gsLogFile,
                        LOG_FILE_NAME,
                        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                        0);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return Status;
}

static VOID DebugWriteToSerialPort(IN CHAR8* Buffer, IN UINTN BufferLength)
{
    UINTN Length;
    EFI_STATUS Status;

    if (gEfiDebugPortProtocol == NULL)
        return;

    //
    // EFI_DEBUGPORT_PROTOCOL.Write is called until all message is sent.
    //

    while (BufferLength > 0) {
        Length = BufferLength;
        Status = gEfiDebugPortProtocol->Write(gEfiDebugPortProtocol,
                                              WRITE_TIMEOUT,
                                              &Length,
                                              (VOID*)Buffer);
        if (EFI_ERROR(Status) || BufferLength < Length)
            break;
        Buffer += Length;
        BufferLength -= Length;
    }
}

static VOID DebugWriteToFile(IN CHAR8* Buffer, IN UINTN BufferLength)
{
    UINTN Length;
    EFI_STATUS Status;

    if (gsLogFile == NULL)
        return;

    while (BufferLength > 0) {
        Length = BufferLength;
        Status = gsLogFile->Write(gsLogFile, &Length, (VOID*)Buffer);
        if (EFI_ERROR(Status) || BufferLength < Length)
            break;
        Buffer += Length;
        BufferLength -= Length;
    }

    gsLogFile->Flush(gsLogFile);
}

static VOID DebugWrite(IN CHAR8* Str, IN UINTN BufferLength)
{
    UINTN StrLength = AsciiStrnLenS(Str, BufferLength);

    if (gEfiMsWindbgServerProtocol != NULL) {
        gEfiMsWindbgServerProtocol->Print(gEfiMsWindbgServerProtocol, Str);
    }

    CHAR16 BufferWide[512];
    AsciiStrToUnicodeStrS(Str, BufferWide, _countof(BufferWide));
    DBG_CMD_RAW_U(BufferWide);

    if (gsLogFile != NULL) {
        DebugWriteToFile(Str, StrLength);
    }

    if (gEfiDebugPortProtocol != NULL) {
        DebugWriteToSerialPort(Str, StrLength);
    }
}

static const struct {
    UINTN BitMask;
    CHAR8* FlagName;
    CHAR16* FlagNameW;
} DebugFlags[DEBUG_MAX] = {
    [DEBUG_ERROR] = {1U << DEBUG_ERROR, t("ERROR"), T("ERROR")},
    [DEBUG_WARNING] = {1U << DEBUG_WARNING, t("WARNING"), T("WARNING")},
    [DEBUG_INFO] = {1U << DEBUG_INFO, t("INFO"), T("INFO")},
    [DEBUG_VERBOSE] = {1U << DEBUG_VERBOSE, t("VERBOSE"), T("VERBOSE")},
};

static CHAR8* GetDebugFlagStr(DEBUG_FLAGS DebugFlag)
{
    if ((DebugFlag >= _countof(DebugFlags)) || (DebugFlag < 0))
        return t("UNKNOWN");

    if (DebugFlags[DebugFlag].BitMask == 0)
        return t("UNKNOWN");

    return DebugFlags[DebugFlag].FlagName;
}

static CHAR16* GetDebugFlagStrU(DEBUG_FLAGS DebugFlag)
{
    if ((DebugFlag >= _countof(DebugFlags)) || (DebugFlag < 0))
        return T("UNKNOWN");

    if (DebugFlags[DebugFlag].BitMask == 0)
        return T("UNKNOWN");

    return DebugFlags[DebugFlag].FlagNameW;
}

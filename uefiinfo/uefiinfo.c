/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    uefiinfo.c

Abstract:

    This module implements the uefiinfo

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"
#include "session.h"
#include "protocols.h"
#include "testsuites.h"

EFI_BOOT_SERVICES* gBS;
EFI_SYSTEM_TABLE* gSystemTable;
EFI_RUNTIME_SERVICES* gRT;
EFI_HANDLE* gImageHandle;

VOID ShowAppInfo(_In_ PBM_SESSION Session)
{
    DBG_INFO("UEFI Info v1.0 - Dump information about UEFI platform");
    DBG_INFO("Copyright (C) 2021-2022 Microsoft Corporation");
    DBG_INFO("UEFI version: %x.%x.%x",
             gSystemTable->Hdr.Revision >> 16,                // Major
             (gSystemTable->Hdr.Revision & 0xFFFF) / 10 % 10, // Minor Upper
             (gSystemTable->Hdr.Revision & 0xFFFF) % 10);
    DBG_INFO("CMD Line: %s", Session->CommandLine);
    DBG_INFO(" ");
}

EFI_STATUS EFIAPI CmdGetCommandline(_Outptr_result_maybenull_z_ CHAR16** CommandLine)
/*++

Routine Description:

    This routine extract the command line passed to the application. The need
    for this method comes from the fact that the bootloader debug library used
    for debugging support is uppercasing the command line. So this method helps
    in copying the actual command line before calling it.

    N.B., Because of the above reason, It is expected to call this function
    before calling DebugInit().

Arguments:

    CommandLine - A point to the copied command line.

Return Value:

    EFI_STATUS. Return EFI_SUCCESS when no error is encountered or
    EFI_* otherwise.

--*/
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    CHAR16* RetCommandLine = NULL;
    CHAR16* Ptr = NULL;

    *CommandLine = NULL;

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        Status = EFI_SUCCESS;
        goto Exit;
    }

    if (LoadedImage->LoadOptionsSize == 0 || LoadedImage->LoadOptions == NULL) {
        goto Exit;
    } else {
        Ptr = LoadedImage->LoadOptions;
    }

    //
    // Copy the command line
    //

    RetCommandLine = AllocateZeroPool((StrLen(Ptr) + 1) * sizeof(CHAR16));
    if (RetCommandLine == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    CopyMem(RetCommandLine, Ptr, StrLen(Ptr) * sizeof(CHAR16));

    *CommandLine = RetCommandLine;

Exit:

    return Status;
}

EFI_STATUS
EFIAPI
Main(_In_ EFI_HANDLE ImageHandle, _In_ EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_SESSION Session = NULL;
    CHAR16* CommandLine = NULL;

    gImageHandle = ImageHandle;
    gSystemTable = SystemTable;
    gBS = SystemTable->BootServices;
    gRT = SystemTable->RuntimeServices;

    CmdGetCommandline(&CommandLine);

    Status = SessionCreate(CommandLine, &Session);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("SessionCreate() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Init debug support
    //

    DebugInit();

    if (Session->ShowHelp == TRUE && Session->TestCase == NULL) {
        DBG_INFO("USAGE:");
        DBG_INFO(" uefiinfo.efi [options]");
        DBG_INFO("");
        DBG_INFO("ARGS:");
        DBG_INFO(" [options]");
        DBG_INFO("  -l List all test cases");
        DBG_INFO("  -t <testcase[,argname1=argval1,argname2=argval2,...]>  Run a test case");
        DBG_INFO("     To know more about test case arguments run -h -t <testcase>");
        DBG_INFO("  -h Display this help.");
        goto Exit;
    }

    ShowAppInfo(Session);

    //
    // Probe all protocols for their existence
    //

    Status = ProtocolProbeAll();
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ProtocolProbeAll() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Start execution of test suites
    //

    Status = DispatchTestSuites(Session);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("DispatchTestSuites() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    SessionDestroy(Session);
    return Status;
}

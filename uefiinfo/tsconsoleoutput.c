/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsconsoleoutput.c

Abstract:

    This module implements console output test suite

Author:

    Vineel Kovvuri (vineelko) 4-Aug-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

typedef struct _BM_CONSOLE_RESOLUTION {
    UINTN Columns;
    UINTN Rows;
} BM_CONSOLE_RESOLUTION, *PBM_CONSOLE_RESOLUTION;

static EFI_STATUS ConsoleOutputProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    SIMPLE_TEXT_OUTPUT_INTERFACE* ConOutProtocol = NULL;
    SIMPLE_TEXT_OUTPUT_MODE* ConOutMode = NULL;
    PBM_CONSOLE_RESOLUTION AllConsoleResolutions = NULL;
    UINT32 CurrentMode = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    ConOutProtocol = ProtocolArray[EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_INDEX].Protocol;

    ConOutMode = ConOutProtocol->Mode;
    CurrentMode = ConOutMode->Mode;
    DBG_INFO("Console Mode(Current):");
    DBG_INFO("         Current Mode: %d", ConOutMode->Mode);
    DBG_INFO("         Max Mode: %d", ConOutMode->MaxMode);
    DBG_INFO("         Cursor Column: %d", ConOutMode->CursorColumn);
    DBG_INFO("         Cursor Row: %d", ConOutMode->CursorRow);
    DBG_INFO("         Attribute: 0x%x", ConOutMode->Attribute);
    DBG_INFO("         Cursor Visible?: %s", ConOutMode->CursorVisible ? "Yes" : "No");

    AllConsoleResolutions = AllocateZeroPool(sizeof(BM_CONSOLE_RESOLUTION) * ConOutMode->MaxMode);
    if (AllConsoleResolutions == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  sizeof(BM_CONSOLE_RESOLUTION) * ConOutMode->MaxMode);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    DBG_INFO("Enumerating all supported console modes:");
    for (INT32 i = 0; i < ConOutMode->MaxMode; i++) {
        Status = ConOutProtocol->QueryMode(ConOutProtocol,
                                           i,
                                           &AllConsoleResolutions[i].Columns,
                                           &AllConsoleResolutions[i].Rows);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO("         Console Mode %d (%zdx%zd)",
                 i,
                 AllConsoleResolutions[i].Columns,
                 AllConsoleResolutions[i].Rows);
    }

    //
    // Disabling below for now, as it will clear the output screen
    //

#if 0
    DBG_INFO("Cycling through all available console modes:");
    for (INT32 i = 0; i < ConOutMode->MaxMode; i++) {
        if (AllConsoleResolutions[i].Columns == 0 &&
            AllConsoleResolutions[i].Rows == 0) {
                continue;
        }

        DBG_INFO_RAW("Setting console mode %d (%dx%d) : ",
                        i,
                        AllConsoleResolutions[i].Columns,
                        AllConsoleResolutions[i].Rows);
        Status = ConOutProtocol->SetMode(ConOutProtocol, i);
        if (EFI_ERROR(Status)) {
            DBG_INFO("Failed : %s(0x%zx)", E(Status), Status);
            DBG_ERROR("Unable to set console mode(%dx%d). Failed : %s(0x%zx)",
                                AllConsoleResolutions[i].Columns,
                                AllConsoleResolutions[i].Rows,
                                E(Status),
                                Status);
        } else {
            DBG_INFO("Succeeded");
        }
    }

    //
    // Restore the original graphics mode
    //

    Status = ConOutProtocol->SetMode(ConOutProtocol, CurrentMode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to restore default graphics mode. Failed : %s(0x%zx)",
                        E(Status),
                        Status);
        goto Exit;
    }
#endif

Exit:

    FreePool(AllConsoleResolutions);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("consoleoutputinfo"),
        .Description = t("Console Output Info"),
        .DutTestFn = ConsoleOutputProbe,
    },
};

BM_TEST_SUITE ConsoleOutputTestSuite = {
    .Description = t("Console Output test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

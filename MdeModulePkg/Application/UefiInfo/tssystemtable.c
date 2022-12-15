/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tssystemtable.c

Abstract:

    This module implements Dumping of EFI System Table info

Author:

    Vineel Kovvuri (vineelko) 14-Dec-2022

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

static EFI_STATUS EfiSystemTableDump(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    // EFI_HANDLE* Handles = NULL;
    // UINTN HandleCount = 0;
    // UINTN i = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);
    UNREFERENCED_PARAMETER(Session);



// Exit:
    // FreePool(Handles);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("systemtabledump"),
        .Description = t("Dump EFI System table information"),
        .DutTestFn = EfiSystemTableDump,
    },
};

BM_TEST_SUITE SystemTableTestSuite = {
    .Description = t("Windbg server related test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

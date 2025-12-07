/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsramdisk.c

Abstract:

    This module implements ramdisk test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS RamDiskProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("ramdiskinfo"),
        .Description = t("Ramdisk Info"),
        .DutTestFn = RamDiskProbe,
    },
};

BM_TEST_SUITE RamdiskTestSuite = {
    .Description = t("Ramdisk test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsip4config2.c

Abstract:

    This module implements ip4 config2 test suite

Author:

    Vineel Kovvuri (vineelko) 18-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Ip4Config2Probe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("ip4config2info"),
        .Description = t("IP 4 Config Info"),
        .DutTestFn = Ip4Config2Probe,
    },
};

BM_TEST_SUITE Ip4ConfigTestSuite = {
    .Description = t("IP 4 Config test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

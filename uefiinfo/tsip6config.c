/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsip6config.c

Abstract:

    This module implements ip6 config test suite

Author:

    Vineel Kovvuri (vineelko) 18-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Ip6ConfigProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("ip6configinfo"),
        .Description = t("IP 6 Config Info"),
        .DutTestFn = Ip6ConfigProbe,
    },
};

BM_TEST_SUITE Ip6ConfigTestSuite = {
    .Description = t("IP 6 Config test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tstcp6.c

Abstract:

    This module implements tcp6 test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Tcp6Probe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("tcp6info"),
        .Description = t("TCP 6 Info"),
        .DutTestFn = Tcp6Probe,
    },
};

BM_TEST_SUITE Tcp6TestSuite = {
    .Description = t("TCP 6 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

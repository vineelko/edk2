/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsudp6.c

Abstract:

    This module implements udp6 test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Udp6Probe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("udp6info"),
        .Description = t("UDP 6 Info"),
        .DutTestFn = Udp6Probe,
    },
};

BM_TEST_SUITE Udp6TestSuite = {
    .Description = t("UDP 6 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

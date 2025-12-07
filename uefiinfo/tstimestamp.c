/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tstimestamp.c

Abstract:

    This module implements timestamp test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS TimestampProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_TIMESTAMP_PROTOCOL* TimestampProtocol = NULL;
    EFI_TIMESTAMP_PROPERTIES Properties = {0};
    UINT64 TimeStamp = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_TIMESTAMP_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    TimestampProtocol = ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX].Protocol;
    Status = TimestampProtocol->GetProperties(&Properties);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Timestamp protocol GetProperties() Api failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Timestamp Frequency: %llu Hz", Properties.Frequency);
    DBG_INFO("Timestamp End Value: 0x%llx", Properties.EndValue);

    TimeStamp = TimestampProtocol->GetTimestamp();
    DBG_INFO("Timestamp: 0x%llu", TimeStamp);

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("timestampinfo"),
        .Description = t("Time Stamp Info"),
        .DutTestFn = TimestampProbe,
    },
};

BM_TEST_SUITE TimestampTestSuite = {
    .Description = t("Time Stamp test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

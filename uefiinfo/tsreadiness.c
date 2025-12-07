/*++

Copyright (c) 2021 Microsoft Corporation

Module Name:

    tsreadiness.c

Abstract:

    This module extends readiness to include all available UEFI protocols as of
    UEFI Spec 2.8

Author:

    Vineel Kovvuri (vineelko) 27-Mar-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

static INTN EFIAPI ProtoInfoComparator(_In_ CONST VOID* Left, _In_ CONST VOID* Right)
{
    PBM_PROTOCOL_INFO ProtocolInfo1;
    PBM_PROTOCOL_INFO ProtocolInfo2;

    ProtocolInfo1 = *(PBM_PROTOCOL_INFO*)Left;
    ProtocolInfo2 = *(PBM_PROTOCOL_INFO*)Right;

    if (ProtocolInfo1->ProtocolGuid == NULL || ProtocolInfo2->ProtocolGuid == NULL) {
        return 0;
    }

    return AsciiStrCmp(ProtocolInfo1->ProtocolName, ProtocolInfo2->ProtocolName);
}

static VOID ReadinessExPrintProtocolInfo(_In_ PBM_PROTOCOL_INFO ProtocolInfo)
{
    if (ProtocolInfo->ProtocolGuid == NULL) {
        return;
    }

    //
    // Display support status
    //

    DBG_INFO("%-45s %s ",
             ProtocolInfo->ProtocolName,
             EFI_ERROR(ProtocolInfo->ProtocolStatus) ? "Not Supported" : "Supported");
    if (ProtocolInfo->ServiceBindingProtocolName != NULL) {
        DBG_INFO("%-45s %s ",
                 ProtocolInfo->ServiceBindingProtocolName,
                 EFI_ERROR(ProtocolInfo->ServiceBindingProtocolStatus) ? "Not Supported" :
                                                                         "Supported");
    }
}

static EFI_STATUS ReadinessProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_PROTOCOL_INFO SortedProtoArray[EFI_MAX_PROTOCOL_INDEX] = {0};

    UNREFERENCED_PARAMETER(Session);

    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        SortedProtoArray[Index] = &ProtocolArray[Index];
    }

    //
    // Sort on protocol name
    //

    PerformQuickSort(SortedProtoArray,
                     EFI_MAX_PROTOCOL_INDEX,
                     sizeof(PBM_PROTOCOL_INFO),
                     ProtoInfoComparator);

    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        ReadinessExPrintProtocolInfo(SortedProtoArray[Index]);
    }

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("readiness"),
        .Description = t("Protocol Presence"),
        .DutTestFn = ReadinessProbe,
    },
};

BM_TEST_SUITE ReadinessTestSuite = {
    .Description = t(
        "Extended readiness test suite to probe for the presence of all of UEFI protocols."),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

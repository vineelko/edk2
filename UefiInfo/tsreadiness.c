#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

static INTN EFIAPI ProtoInfoComparator(IN CONST VOID* Left, IN CONST VOID* Right)
{
    PPROTOCOL_INFO ProtocolInfo1;
    PPROTOCOL_INFO ProtocolInfo2;

    ProtocolInfo1 = *(PPROTOCOL_INFO*)Left;
    ProtocolInfo2 = *(PPROTOCOL_INFO*)Right;

    if (ProtocolInfo1->ProtocolGuid == NULL || ProtocolInfo2->ProtocolGuid == NULL) {
        return 0;
    }

    return AsciiStrCmp(ProtocolInfo1->ProtocolName, ProtocolInfo2->ProtocolName);
}

static VOID ReadinessExPrintProtocolInfo(IN PPROTOCOL_INFO ProtocolInfo)
{
    if (ProtocolInfo->ProtocolGuid == NULL) {
        return;
    }

    //
    // Display support status
    //

    DBG_INFO("%-45a %a ",
             ProtocolInfo->ProtocolName,
             EFI_ERROR(ProtocolInfo->ProtocolStatus) ? "Not Supported" : "Supported");
    if (ProtocolInfo->ServiceBindingProtocolName != NULL) {
        DBG_INFO("%-45a %a ",
                 ProtocolInfo->ServiceBindingProtocolName,
                 EFI_ERROR(ProtocolInfo->ServiceBindingProtocolStatus) ? "Not Supported" :
                                                                         "Supported");
    }
}

static VOID ProtocolProbeAll(VOID)
{
    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        ProtocolGetInfo(&ProtocolArray[Index]);
    }
}

static EFI_STATUS ReadinessProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PPROTOCOL_INFO SortedProtoArray[EFI_MAX_PROTOCOL_INDEX];

    UNREFERENCED_PARAMETER(Session);

    ProtocolProbeAll();

    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        SortedProtoArray[Index] = &ProtocolArray[Index];
    }

    //
    // Sort on protocol name
    //

    PerformQuickSort(SortedProtoArray,
                     EFI_MAX_PROTOCOL_INDEX,
                     sizeof(PPROTOCOL_INFO),
                     ProtoInfoComparator);

    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        ReadinessExPrintProtocolInfo(SortedProtoArray[Index]);
    }

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("readiness"),
        .Description = t("Protocol Presence"),
        .DutTestFn = ReadinessProbe,
    },
};

UEFIINFO_TEST_SUITE ReadinessTestSuite = {
    .Description = t(
        "Extended readiness test suite to probe for the presence of all of UEFI protocols."),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

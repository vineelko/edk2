#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS TimestampProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_TIMESTAMP_PROTOCOL* TimestampProtocol = NULL;
    EFI_TIMESTAMP_PROPERTIES Properties = {0};
    UINT64 TimeStamp = 0;

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_TIMESTAMP_PROTOCOL Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    TimestampProtocol = ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX].Protocol;
    Status = TimestampProtocol->GetProperties(&Properties);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Timestamp protocol GetProperties() Api failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Timestamp Frequency: %llu Hz", Properties.Frequency);
    DBG_INFO("Timestamp End Value: 0x%llx", Properties.EndValue);

    TimeStamp = TimestampProtocol->GetTimestamp();
    DBG_INFO("Timestamp: 0x%llu", TimeStamp);

Exit:

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("timestampinfo"),
        .Description = t("Time Stamp Info"),
        .DutTestFn = TimestampProbe,
    },
};

UEFIINFO_TEST_SUITE TimestampTestSuite = {
    .Description = t("Time Stamp test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};
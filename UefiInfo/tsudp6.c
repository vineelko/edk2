#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Udp6Probe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("udp6info"),
        .Description = t("UDP 6 Info"),
        .DutTestFn = Udp6Probe,
    },
};

UEFIINFO_TEST_SUITE Udp6TestSuite = {
    .Description = t("UDP 6 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};
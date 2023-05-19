#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Dhcp6Probe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("dhcp6info"),
        .Description = t("DHCP 6 Info"),
        .DutTestFn = Dhcp6Probe,
    },
};

UEFIINFO_TEST_SUITE Dhcp6TestSuite = {
    .Description = t("DHCP 6 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

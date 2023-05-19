#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Ip6ConfigProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("ip6configinfo"),
        .Description = t("IP 6 Config Info"),
        .DutTestFn = Ip6ConfigProbe,
    },
};

UEFIINFO_TEST_SUITE Ip6ConfigTestSuite = {
    .Description = t("IP 6 Config test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

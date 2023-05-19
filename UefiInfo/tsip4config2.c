#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Ip4Config2Probe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("ip4config2info"),
        .Description = t("IP 4 Config Info"),
        .DutTestFn = Ip4Config2Probe,
    },
};

UEFIINFO_TEST_SUITE Ip4ConfigTestSuite = {
    .Description = t("IP 4 Config test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

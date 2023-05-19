#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS Tcp6Probe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("tcp6info"),
        .Description = t("TCP 6 Info"),
        .DutTestFn = Tcp6Probe,
    },
};

UEFIINFO_TEST_SUITE Tcp6TestSuite = {
    .Description = t("TCP 6 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

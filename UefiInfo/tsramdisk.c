#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS RamDiskProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Yet to implement");

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("ramdiskinfo"),
        .Description = t("Ramdisk Info"),
        .DutTestFn = RamDiskProbe,
    },
};

UEFIINFO_TEST_SUITE RamdiskTestSuite = {
    .Description = t("Ramdisk test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS ValidateConnectDeviceClassTest(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_BOOT_MANAGER_POLICY_PROTOCOL* BootManager = NULL;

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_BOOT_MANAGER_POLICY_PROTOCOL Protocol not available : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    BootManager = ProtocolArray[EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX].Protocol;
    Status = BootManager->ConnectDeviceClass(BootManager, &gEfiBootManagerPolicyConnectAllGuid);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ConnectDeviceClass() returned : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("bmconnectall"),
        .Description = t("Boot Manager ConnectDeviceClass() API"),
        .DutTestFn = ValidateConnectDeviceClassTest,
    },
};

UEFIINFO_TEST_SUITE BootManagerTestSuite = {
    .Description = t("Boot Manager Suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

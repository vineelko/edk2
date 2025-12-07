/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsbootmanagerpolicy.c

Abstract:

    This module implements boot manager policy test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS ValidateConnectDeviceClassTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                                 _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_BOOT_MANAGER_POLICY_PROTOCOL* BootManager = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_BOOT_MANAGER_POLICY_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    BootManager = ProtocolArray[EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX].Protocol;
    Status = BootManager->ConnectDeviceClass(BootManager, &gEfiBootManagerPolicyConnectAllGuid);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ConnectDeviceClass() returned : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("bmconnectall"),
        .Description = t("Boot Manager ConnectDeviceClass() API"),
        .DutTestFn = ValidateConnectDeviceClassTest,
    },
};

BM_TEST_SUITE BootManagerTestSuite = {
    .Description = t("Boot Manager Suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

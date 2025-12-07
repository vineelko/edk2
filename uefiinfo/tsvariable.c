/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsvariable.c

Abstract:

    This module implements UEFI variable validation test suite

Author:

    Vineel Kovvuri (vineelko) 16-Sep-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

#define EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS 0x80

// clang-format off

//
// Variable Attribute combinations.
//

#define VARIABLE_ATTRIBUTE_AT                   (EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)
#define VARIABLE_ATTRIBUTE_EA                   (EFI_VARIABLE_ENHANCED_AUTHENTICATED_ACCESS)
#define VARIABLE_ATTRIBUTE_BS                   (EFI_VARIABLE_BOOTSERVICE_ACCESS)
#define VARIABLE_ATTRIBUTE_BS_RT                (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS)
#define VARIABLE_ATTRIBUTE_BS_RT_AT             (VARIABLE_ATTRIBUTE_BS_RT | VARIABLE_ATTRIBUTE_AT)
#define VARIABLE_ATTRIBUTE_BS_RT_EA             (VARIABLE_ATTRIBUTE_BS_RT | VARIABLE_ATTRIBUTE_EA)
#define VARIABLE_ATTRIBUTE_NV_BS                (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS)
#define VARIABLE_ATTRIBUTE_NV_BS_RT             (VARIABLE_ATTRIBUTE_BS_RT | EFI_VARIABLE_NON_VOLATILE)
#define VARIABLE_ATTRIBUTE_NV_BS_RT_AT          (VARIABLE_ATTRIBUTE_NV_BS_RT | VARIABLE_ATTRIBUTE_AT)
#define VARIABLE_ATTRIBUTE_NV_BS_RT_EA          (VARIABLE_ATTRIBUTE_NV_BS_RT | VARIABLE_ATTRIBUTE_EA)
#define VARIABLE_ATTRIBUTE_NV_BS_RT_HR          (VARIABLE_ATTRIBUTE_NV_BS_RT | EFI_VARIABLE_HARDWARE_ERROR_RECORD)
#define VARIABLE_ATTRIBUTE_NV_BS_RT_HR_AT       (VARIABLE_ATTRIBUTE_NV_BS_RT_HR | VARIABLE_ATTRIBUTE_AT)
#define VARIABLE_ATTRIBUTE_NV_BS_RT_HR_EA       (VARIABLE_ATTRIBUTE_NV_BS_RT_HR | VARIABLE_ATTRIBUTE_EA)

static ENUM_TO_STRING VariableAttributesMap[] = {
    {VARIABLE_ATTRIBUTE_BS,             STRINGIFY(VARIABLE_ATTRIBUTE_BS)},
    {VARIABLE_ATTRIBUTE_BS_RT,          STRINGIFY(VARIABLE_ATTRIBUTE_BS_RT)},
    {VARIABLE_ATTRIBUTE_BS_RT_AT,       STRINGIFY(VARIABLE_ATTRIBUTE_BS_RT_AT)},
    {VARIABLE_ATTRIBUTE_BS_RT_EA,       STRINGIFY(VARIABLE_ATTRIBUTE_BS_RT_EA)},
    {VARIABLE_ATTRIBUTE_NV_BS,          STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT,       STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT_AT,    STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT_AT)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT_EA,    STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT_EA)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT_HR,    STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT_HR)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT_HR_AT, STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT_HR_AT)},
    {VARIABLE_ATTRIBUTE_NV_BS_RT_HR_EA, STRINGIFY(VARIABLE_ATTRIBUTE_NV_BS_RT_HR_EA)},
};

// clang-format on

static EFI_STATUS GetMaxVariableSize(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    for (UINTN i = 0; i < _countof(VariableAttributesMap); i++) {
        UINT64 MaximumVariableStorageSize = 0;
        UINT64 RemainingVariableStorageSize = 0;
        UINT64 MaximumVariableSize = 0;
        Status = gRT->QueryVariableInfo(VariableAttributesMap[i].Value,
                                        &MaximumVariableStorageSize,
                                        &RemainingVariableStorageSize,
                                        &MaximumVariableSize);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("%-40s : QueryVariableInfo() call failed : %s(0x%zx)",
                      VariableAttributesMap[i].String,
                      E(Status),
                      Status);
        } else {
            DBG_INFO(
                "%-40s : MaximumVariableSize = %4llu%-6s MaximumVariableStorageSize = %4llu%-6s RemainingVariableStorageSize = %4llu%-6s",
                VariableAttributesMap[i].String,
                PrettySize(MaximumVariableSize),
                PrettySizeStr(MaximumVariableSize),
                PrettySize(MaximumVariableStorageSize),
                PrettySizeStr(MaximumVariableStorageSize),
                PrettySize(RemainingVariableStorageSize),
                PrettySizeStr(RemainingVariableStorageSize));
        }
    }

    DBG_INFO("Legend:");
    DBG_INFO("    AT: Time Based Authenticated Write Access");
    DBG_INFO("    BS: Boot Service");
    DBG_INFO("    EA: Enhanced Authenticated Access");
    DBG_INFO("    HR: Hardware Error Record");
    DBG_INFO("    NV: Non Volatile");
    DBG_INFO("    RT: Runtime Service");

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("variablesize"),
        .Description = t("Get max variable size info"),
        .DutTestFn = GetMaxVariableSize,
    },
};

BM_TEST_SUITE UEFIVariableTestSuite = {
    .Description = t("UEFI variables test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

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

static EFI_STATUS GetMaxVariableSize(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    for (UINTN i = 0; i < _countof(VariableAttributesMap); i++) {
        UINT64 MaximumVariableStorageSize = 0;
        UINT64 RemainingVariableStorageSize = 0;
        UINT64 MaximumVariableSize = 0;
        Status = gRT->QueryVariableInfo((UINT32)VariableAttributesMap[i].Value,
                                        &MaximumVariableStorageSize,
                                        &RemainingVariableStorageSize,
                                        &MaximumVariableSize);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("%-40a : QueryVariableInfo() call failed : %a(0x%x)",
                      VariableAttributesMap[i].String,
                      E(Status),
                      Status);
        } else {
            DBG_INFO(
                "%-40a : MaximumVariableSize = %4llu%-6a MaximumVariableStorageSize = %4llu%-6a RemainingVariableStorageSize = %4llu%-6a",
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

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("variablesize"),
        .Description = t("Get max variable size info"),
        .DutTestFn = GetMaxVariableSize,
    },
};

UEFIINFO_TEST_SUITE UEFIVariableTestSuite = {
    .Description = t("UEFI variables test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

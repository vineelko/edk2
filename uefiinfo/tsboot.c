/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsboot.c

Abstract:

    This module implements boot order enumeration

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"
#include "endiannesshelper.h"

#include "protocols.h"
#include "testsuites.h"
#include "boot_options.h"

static EFI_STATUS EnumerateBootOrder(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    UINT8* BootOptions = NULL;
    UINT32 BootOptionsLength = 0;
    UINT32 NumBootOptions = 0;
    UINT32 Offset = 0;
    EFI_STATUS Status = EFI_SUCCESS;
    sUEFI_BOOT_OPTION* Option = NULL;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = BootOptionsEnumerateAll((sUEFI_BOOT_OPTION*)BootOptions,
                                     &BootOptionsLength,
                                     &NumBootOptions);
    if (Status != EFI_BUFFER_TOO_SMALL && EFI_ERROR(Status)) {
        DBG_ERROR("boot_options_enumerate_all failed with error %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    // Call it again with correct size
    BootOptions = AllocateZeroPool(BootOptionsLength);
    if (BootOptions == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", BootOptionsLength);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = BootOptionsEnumerateAll((sUEFI_BOOT_OPTION*)BootOptions,
                                     &BootOptionsLength,
                                     &NumBootOptions);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("boot_options_enumerate_all failed with error %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    // Print out boot option information
    DBG_INFO("Number of boot options %u", NumBootOptions);

    for (UINT32 i = 0; i < NumBootOptions; i++) {
        Option = (sUEFI_BOOT_OPTION*)(BootOptions + Offset);
        DBG_INFO("Index                               : %u", Option->uIndex);
        DBG_INFO("Boot option                         : Boot%04X", GETB16(Option->wBootOption));
        DBG_INFO("Attributes                          : 0x%08X%s%s%s%s",
                 GETB32(Option->dwAttributes),
                 (GETB32(Option->dwAttributes) & LOAD_OPTION_ACTIVE) ? "(LOAD_OPTION_ACTIVE)" : "",
                 (GETB32(Option->dwAttributes) & LOAD_OPTION_FORCE_RECONNECT) ?
                     "(LOAD_OPTION_FORCE_RECONNECT)" :
                     "",
                 (GETB32(Option->dwAttributes) & LOAD_OPTION_HIDDEN) ? "(LOAD_OPTION_HIDDEN)" : "",
                 (GETB32(Option->dwAttributes) & LOAD_OPTION_CATEGORY_APP) ?
                     "(LOAD_OPTION_CATEGORY_APP)" :
                     "(LOAD_OPTION_CATEGORY_BOOT)");
        DBG_INFO_U(L"Description                         : %s",
                   (WCHAR*)(BootOptions + Offset + GETB16(Option->wDescriptionOffset)));
        DBG_INFO_U(L"Device Path                         : %s",
                   (WCHAR*)(BootOptions + Offset + GETB16(Option->wDevicePathOffset)));

        if (GETB16(Option->wCommandLineOffset) != 0) {
            DBG_INFO_U(L"Command Line                        : %s",
                       (WCHAR*)(BootOptions + Offset + GETB16(Option->wCommandLineOffset)));
        }

        Offset += GETB16(Option->wSize);

        DBG_INFO("");
    }

Exit:

    FreePool(BootOptions);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("bootinfo"),
        .Description = t("Boot order info"),
        .DutTestFn = EnumerateBootOrder,
    },
};

BM_TEST_SUITE BootTestSuite = {
    .Description = t("Boot test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsdevicepath.c

Abstract:

    This module implements device path test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

static EFI_STATUS DevicePathDumpAll(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID**)&ToTextPath);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiDevicePathProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &Handles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed: 0x%x", Status);
        goto Exit;
    }

    DBG_INFO("Handle Count: %d", HandleCount);

    for (UINTN i = 0; i < HandleCount; i++) {
        EFI_DEVICE_PATH_PROTOCOL* DevicePath = NULL;
        CHAR16* TextPath = NULL;
        UINTN Length = 0;

        Status = gBS->HandleProtocol(Handles[i], &gEfiDevicePathProtocolGuid, (VOID**)&DevicePath);
        if (EFI_ERROR(Status)) {
            continue;
        }

        TextPath = ToTextPath->ConvertDevicePathToText(DevicePath, FALSE, FALSE);
        if (TextPath == NULL) {
            continue;
        }

        Length = (DevicePath->Length[1] << 8) | DevicePath->Length[0];
        DBG_INFO_U(L"%s %d", TextPath, Length);
        HexDump(DevicePath, Length);
        DBG_INFO_U(L"---------------------------------------");

        FreePool(TextPath);
    }

Exit:
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("devicepathdumpall"),
        .Description = t("Dump all Device Paths"),
        .DutTestFn = DevicePathDumpAll,
    },
};

BM_TEST_SUITE DevicePathTestSuite = {
    .Description = t("Device Path Suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

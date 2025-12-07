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

static EFI_STATUS DevicePathProbeApi(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    CHAR16 Path[1024] = L"FS0:\\do-not-exist.efi";
    EFI_DEVICE_PATH_PROTOCOL* DevicePath = NULL;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
    EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL* FromTextPath = NULL;
    CHAR16* TextPath = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    Status = ProtocolArray[EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DEVICE_PATH_TO_TEXT_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    FromTextPath = ProtocolArray[EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_INDEX].Protocol;
    ToTextPath = ProtocolArray[EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_INDEX].Protocol;

    DevicePath = FromTextPath->ConvertTextToDevicPath(Path);
    if (DevicePath == NULL) {
        DBG_ERROR("ConvertTextToDevicPath() Api failed. Returned NULL");
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    TextPath = ToTextPath->ConvertDevicePathToText(DevicePath, FALSE, FALSE);
    if (TextPath == NULL) {
        DBG_ERROR("ConvertDevicePathToText() Api failed. Returned NULL");
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = StrCmp(Path, TextPath) == 0 ? EFI_SUCCESS : EFI_INVALID_PARAMETER;

    //
    // Todo: Includes tests for EFI_DEVICE_PATH_UTILITIES_PROTOCOL here
    //

Exit:

    FreePool(DevicePath);
    FreePool(TextPath);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("devicepathapi"),
        .Description = t("Device Path To/From/Utility API Test"),
        .DutTestFn = DevicePathProbeApi,
    },
};

BM_TEST_SUITE DevicePathTestSuite = {
    .Description = t("Device Path Suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

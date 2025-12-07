/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsloadedimage.c

Abstract:

    This module implements loadedimage test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS LoadedImageProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathProtocol;
    EFI_HANDLE LoadedImageHandle = NULL;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    //
    // Open the currently loaded image file
    //

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->HandleProtocol(gImageHandle,
                                 &gEfiDevicePathProtocolGuid,
                                 (void**)&DevicePathProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Exercise LoadImage() API by reloading the current image
    //

    Status = gBS->LoadImage(FALSE, gImageHandle, DevicePathProtocol, NULL, 0, &LoadedImageHandle);
    if (EFI_ERROR(Status)) {
        DBG_INFO("HandleProtocol() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("loadimageapi"),
        .Description = t("Loaded Image Api"),
        .DutTestFn = LoadedImageProbe,
    },
};

BM_TEST_SUITE LoadImageTestSuite = {
    .Description = t("Loaded Image test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

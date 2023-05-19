#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS LoadedImageProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathProtocol;
    EFI_HANDLE LoadedImageHandle = NULL;

    UNREFERENCED_PARAMETER(Session);

    //
    // Open the currently loaded image file
    //

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->HandleProtocol(gImageHandle,
                                 &gEfiDevicePathProtocolGuid,
                                 (void**)&DevicePathProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Exercise LoadImage() API by reloading the current image
    //

    Status = gBS->LoadImage(FALSE, gImageHandle, DevicePathProtocol, NULL, 0, &LoadedImageHandle);
    if (EFI_ERROR(Status)) {
        DBG_INFO("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("loadimageapi"),
        .Description = t("Loaded Image Api"),
        .DutTestFn = LoadedImageProbe,
    },
};

UEFIINFO_TEST_SUITE LoadImageTestSuite = {
    .Description = t("Loaded Image test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"
#include "file.h"

static EFI_STATUS LoadImageWithDevicePath(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathProtocol = NULL;
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

static EFI_STATUS LoadImageWithMemoryCopy(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_FILE_PROTOCOL* File = NULL;
    EFI_FILE_PROTOCOL* Root = NULL;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    EFI_HANDLE LoadedFileHandle = NULL;
    CHAR8* FileName = NULL;
    CHAR16 FileNameW[512];
    VOID* Buffer = NULL;
    UINTN FileSize = 0;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;

    if (Session->ShowHelp == TRUE) {
        DBG_INFO("USAGE:");
        DBG_INFO(" uefiinfo.efi -t loadimagewithmemorycopy,file=<filename>");
        goto Exit;
    }

    FileName = GetCmdArgValue(Session->CommandLine, t("file"));
    if (FileName == NULL) {
        DBG_INFO("File name is empty");
        DBG_INFO("USAGE:");
        DBG_INFO(" uefiinfo.efi -t loadimagewithmemorycopy,file=<filename>");
        goto Exit;
    }

    AsciiStrToUnicodeStrS(FileName, FileNameW, _countof(FileNameW));

    //
    // Open the currently loaded image file
    //
    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Open SIMPLE_FILE_SYSTEM_PROTOCOL for the volume from which the
    // current image is loaded
    //
    Status = gBS->HandleProtocol(LoadedImage->DeviceHandle,
                                 &gEfiSimpleFileSystemProtocolGuid,
                                 (void**)&SimpleFileSystem);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("OpenVolume() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Root->Open(Root, &File, FileNameW, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Open() failed. Unable to locate %a %a(0x%x)", FileName, E(Status), Status);
        goto Exit;
    }

    //
    // Get driver size and allocate memory for it
    //

    Status = FileGetSize(File, &FileSize);
    if (EFI_ERROR(Status)) {
        DBG_INFO("FileGetSize() failed %a(0x%x).",  E(Status), Status);
        goto Exit;
    }

    Buffer = AllocateZeroPool(FileSize);
    if (Buffer == NULL) {
        DBG_ERROR("Out of resources");
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = FileRead(File, &FileSize, Buffer);
    if (EFI_ERROR(Status)) {
        DBG_INFO("FileRead() failed %a(0x%x).",  E(Status), Status);
        goto Exit;
    }

    DBG_INFO("File(%a) copied to memory at 0x%x with size %u",
             FileName,
             Buffer,
             FileSize);

    DBG_INFO("Loading file from memory(0x%x)", Buffer);
    Status = gBS->LoadImage(FALSE,
                            gImageHandle,
                            NULL,
                            Buffer,
                            FileSize,
                            &LoadedFileHandle);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LoadImage() failed. %a(0x%x)",  E(Status), Status);
        goto Exit;
    }

    DBG_INFO("File loaded(Handle: 0x%x)", LoadedFileHandle);

    // DBG_INFO("Starting image");
    // Status = gBS->StartImage(LoadedFileHandle, NULL, NULL);
    // if (EFI_ERROR(Status)) {
    //     DBG_ERROR("StartImage() failed. %a(0x%x)",  E(Status), Status);
    //     goto Exit;
    // }

Exit:
    FileClose(File);
    FreePool(Buffer);
    FreePool(FileName);
    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("loadimagewithdevicepath"),
        .Description = t("Load Image with device path"),
        .DutTestFn = LoadImageWithDevicePath,
    },
    {
        .Name = t("loadimagewithmemorycopy"),
        .Description = t("Load Image by copying it to memory"),
        .DutTestFn = LoadImageWithMemoryCopy,
    },
};

UEFIINFO_TEST_SUITE LoadImageTestSuite = {
    .Description = t("Load Image test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tssimplefilesystem.c

Abstract:

    This module implements file system test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS FileInfo(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
    EFI_FILE_INFO* FileInfo = NULL;
    EFI_FILE_PROTOCOL* LoadedImageFile = NULL;
    EFI_FILE_PROTOCOL* Root = NULL;
    EFI_LOADED_IMAGE* LoadedImage = NULL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    CHAR16* BinaryFilePath = NULL;
    UINTN FileInfoSize = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    //
    // Open the currently loaded image file
    //

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to located EFI_LOADED_IMAGE_PROTOCOL protocol on "
                  "image handle. HandleProtocol() failed : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    // Open SIMPLE_FILE_SYSTEM_PROTOCOL for the volume from which the
    // current image is loaded
    Status = gBS->HandleProtocol(LoadedImage->DeviceHandle,
                                 &gEfiSimpleFileSystemProtocolGuid,
                                 (void**)&SimpleFileSystem);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to located EFI_SIMPLE_FILE_SYSTEM_PROTOCOL protocol "
                  "on image handle. HandleProtocol() failed : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("OpenVolume() failed to open device where the "
                  "current image is loaded : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (PVOID*)&ToTextPath);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to located EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID "
                  "protocol failed : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    BinaryFilePath = ToTextPath->ConvertDevicePathToText(LoadedImage->FilePath, FALSE, FALSE);
    if (BinaryFilePath == NULL) {
        DBG_ERROR("ConvertDevicePathToText() returned null");
        goto Exit;
    }

    Status = Root->Open(Root, &LoadedImageFile, BinaryFilePath, EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(Status)) {
        DBG_ERROR_U("EFI_FILE_PROTOCOL.Open() for %s failed : %S(0x%zx)",
                    BinaryFilePath,
                    E(Status),
                    Status);
        goto Exit;
    }

    //
    // Read file attributes
    //

    Status = LoadedImageFile->GetInfo(LoadedImageFile,
                                      &gEfiFileInfoIdGuid,
                                      &FileInfoSize,
                                      FileInfo);
    if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
        DBG_ERROR_U("EFI_FILE_PROTOCOL.GetInfo() for %s failed : %S(0x%zx)",
                    BinaryFilePath,
                    E(Status),
                    Status);
        goto Exit;
    }

    FileInfo = AllocateZeroPool(FileInfoSize);
    if (FileInfo == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd", FileInfoSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = LoadedImageFile->GetInfo(LoadedImageFile,
                                      &gEfiFileInfoIdGuid,
                                      &FileInfoSize,
                                      FileInfo);
    if (EFI_ERROR(Status)) {
        DBG_ERROR_U("EFI_FILE_PROTOCOL.GetInfo() for %s failed : %S(0x%zx)",
                    BinaryFilePath,
                    E(Status),
                    Status);
        goto Exit;
    }

    DBG_INFO_U(L"Name: %s", FileInfo->FileName);
    DBG_INFO("Size: %llu bytes", FileInfo->FileSize);
    DBG_INFO("Physical Size: %llu bytes", FileInfo->PhysicalSize);
    DBG_INFO_RAW("Attributes: ");

    if (FileInfo->Attribute & EFI_FILE_READ_ONLY) {
        DBG_INFO_RAW("EFI_FILE_READ_ONLY|");
    }
    if (FileInfo->Attribute & EFI_FILE_HIDDEN) {
        DBG_INFO_RAW("EFI_FILE_HIDDEN|");
    }
    if (FileInfo->Attribute & EFI_FILE_SYSTEM) {
        DBG_INFO_RAW("EFI_FILE_SYSTEM|");
    }
    if (FileInfo->Attribute & EFI_FILE_DIRECTORY) {
        DBG_INFO_RAW("EFI_FILE_DIRECTORY|");
    }
    if (FileInfo->Attribute & EFI_FILE_ARCHIVE) {
        DBG_INFO_RAW("EFI_FILE_ARCHIVE|");
    }
    if (FileInfo->Attribute & EFI_FILE_VALID_ATTR) {
        DBG_INFO_RAW("EFI_FILE_VALID_ATTR|");
    }

    DBG_INFO(" ");
    DBG_INFO("Created Time: %02u/%02u/%02u %02u:%02u:%02u",
             FileInfo->CreateTime.Month,
             FileInfo->CreateTime.Day,
             (UINT16)(FileInfo->CreateTime.Year % 100),
             FileInfo->CreateTime.Hour,
             FileInfo->CreateTime.Minute,
             FileInfo->CreateTime.Second);
    DBG_INFO("Last Accessed Time: %02u/%02u/%02u %02u:%02u:%02u",
             FileInfo->LastAccessTime.Month,
             FileInfo->LastAccessTime.Day,
             (UINT16)(FileInfo->LastAccessTime.Year % 100),
             FileInfo->LastAccessTime.Hour,
             FileInfo->LastAccessTime.Minute,
             FileInfo->LastAccessTime.Second);
    DBG_INFO("Modification Time: %02u/%02u/%02u %02u:%02u:%02u",
             FileInfo->ModificationTime.Month,
             FileInfo->ModificationTime.Day,
             (UINT16)(FileInfo->ModificationTime.Year % 100),
             FileInfo->ModificationTime.Hour,
             FileInfo->ModificationTime.Minute,
             FileInfo->ModificationTime.Second);

Exit:

    FreePool(FileInfo);
    FreePool(BinaryFilePath);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("fileinfo"),
        .Description = t("File Info"),
        .DutTestFn = FileInfo,
    },
    // {
    //     .Name = t("simplefilesysteminfo"),
    //     .Description = t("Simple File System Info"),
    //     .DutTestFn = SimpleFileSystemProbe,
    // },
};

BM_TEST_SUITE FileSystemTestSuite = {
    .Description = t("File System test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

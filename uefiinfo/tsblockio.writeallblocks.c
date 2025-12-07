/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsblockio.writeallblocks.c

Abstract:

    This module implements blockio write all sectors test case

Author:

    Vineel Kovvuri (vineelko) 13-Aug-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

EFI_STATUS
BlockIoWriteToAllSectors(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    CHAR16* DevicePath = NULL;
    EFI_BLOCK_IO_MEDIA* BlockIoMedia = NULL;
    EFI_BLOCK_IO_PROTOCOL* BlockIoIf = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathIf = NULL;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextIf = NULL;
    EFI_HANDLE* BlockIoHandles = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN HandleCount = 0;
    BOOLEAN IsUSBDriveInVM = FALSE;
    PVOID Data = NULL;
    UINT64 DataSize = 0;
    UINT64 MaxDataSize = 0;
    UINT64 TotalDiskSize = 0;

    UNREFERENCED_PARAMETER(Session);

    DevicePathToTextIf = ProtocolArray[EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_INDEX].Protocol;
    // BLOCK IO handles could be available for multiple devices. Enumerate all of them
    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiBlockIoProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &BlockIoHandles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    MaxDataSize = 100 * MB;
    Data = AllocatePool((UINTN)MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("Unable to allocate memory of size(%llu)", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    for (UINTN i = 0; i < HandleCount; i++) {
        BlockIoIf = NULL;

        Status = gBS->HandleProtocol(BlockIoHandles[i],
                                     &gEfiBlockIoProtocolGuid,
                                     (PVOID*)&BlockIoIf);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        BlockIoMedia = BlockIoIf->Media;
        TotalDiskSize = BlockIoMedia->BlockSize * BlockIoMedia->LastBlock;

        //
        // In a VM, the FAT32 VHD(acting as USB boot disk) cannot be detected as
        // 'Removable' and below check prevent running write test and accidentally
        // making USB drive non-bootable!
        //

        if (IsRunningInVM()) {
            IsUSBDriveInVM = TotalDiskSize < GB;
        }

        if (!BlockIoMedia->RemovableMedia && !BlockIoMedia->LogicalPartition && !IsUSBDriveInVM) {
            DevicePathIf = DevicePathFromHandle(BlockIoHandles[i]);

            if (DevicePathIf != NULL) {
                DevicePath = DevicePathToTextIf->ConvertDevicePathToText(DevicePathIf,
                                                                         FALSE,
                                                                         FALSE);
                DBG_INFO_U(L"DevicePath : %s", DevicePath);
                FreePool(DevicePath);
            }

            DBG_INFO("Disk Block Size: %lld%s",
                     PrettySize(BlockIoMedia->BlockSize),
                     PrettySizeStr(BlockIoMedia->BlockSize));
            DBG_INFO("Total Disk Size: %lld%s",
                     PrettySize(TotalDiskSize),
                     PrettySizeStr(TotalDiskSize));
            DBG_INFO("Number of Blocks: %llu", BlockIoMedia->LastBlock);

            UINT64 RemainingDiskSize = TotalDiskSize;
            DataSize = MaxDataSize;
            for (UINT64 k = 0; k < BlockIoMedia->LastBlock;
                 k += (DataSize / BlockIoMedia->BlockSize)) {
                DataSize = RemainingDiskSize < DataSize ? RemainingDiskSize : DataSize;

                DBG_INFO_RAW("Writing %lld%s start @ block: %llu(%llu%%)\r",
                             PrettySize(DataSize),
                             PrettySizeStr(DataSize),
                             k,
                             ((k * 100) / BlockIoMedia->LastBlock));
                Status = BlockIoIf->WriteBlocks(BlockIoIf,
                                                BlockIoMedia->MediaId,
                                                k,
                                                (UINTN)DataSize,
                                                Data);
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("\nFailed to write to block %llu failed : %s(0x%zx)",
                              k,
                              E(Status),
                              Status);
                    break;
                }

                RemainingDiskSize -= DataSize;
            }

            DBG_INFO("");
        }
    }

    Status = EFI_SUCCESS;

Exit:

    FreePool(BlockIoHandles);
    FreePool(Data);

    return Status;
}

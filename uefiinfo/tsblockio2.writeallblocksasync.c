/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsblockio2.writeallblocksasync.c

Abstract:

    This module implements blockio 2 async write all sectors test case

Author:

    Vineel Kovvuri (vineelko) 13-Aug-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

#define MAX_SYNC_ASYNC_OPERATIONS 200
static volatile LONG AsyncOperationCount = 0;
static EFI_EVENT WaitForAsyncOperation = NULL;

static VOID EFIAPI BlockIo2AsyncWaitCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI BlockIo2AsyncOperationCallback(_In_ EFI_EVENT Event, _In_ PVOID Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    if (InterlockedIncrement(&AsyncOperationCount) >= MAX_SYNC_ASYNC_OPERATIONS) {
        gBS->SignalEvent(WaitForAsyncOperation);
    }
}

static EFI_STATUS UefiInfoBlockIo2WriteToAllSectors(_In_ EFI_BLOCK_IO_PROTOCOL* BlockIoIf,
                                                    _In_ EFI_BLOCK_IO2_PROTOCOL* BlockIo2If)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_BLOCK_IO_MEDIA* BlockIoMedia = NULL;
    PVOID Data = NULL;
    UINT64 DataSize = 0;
    UINT64 MaxDataSize = 0;
    EFI_BLOCK_IO2_TOKEN* Tokens = NULL;
    UINTN Index = 0;
    UINT64 TotalDiskSize = 0;

    if (BlockIoIf == NULL || BlockIo2If == NULL)
        return EFI_INVALID_PARAMETER;

    BlockIoMedia = BlockIoIf->Media;
    TotalDiskSize = BlockIoMedia->BlockSize * BlockIoMedia->LastBlock;

    //
    // In a VM, the FAT32 VHD(acting as USB boot disk) cannot be detected as
    // 'Removable' and below check prevent running write test and accidentally
    // making it unbootable!
    //

    if (IsRunningInVM()) {
        if (TotalDiskSize < GB)
            return Status;
    }

    //
    // Allocate 128 KB Buffer for write operations
    //

    MaxDataSize = 128 * KB;
    Data = AllocatePool((UINTN)MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %lld", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Tokens = AllocateZeroPool(MAX_SYNC_ASYNC_OPERATIONS * sizeof(EFI_BLOCK_IO2_TOKEN));
    if (Tokens == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  MAX_SYNC_ASYNC_OPERATIONS * sizeof(EFI_BLOCK_IO2_TOKEN));
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
        Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                                  TPL_NOTIFY,
                                  BlockIo2AsyncOperationCallback,
                                  &Tokens[i],
                                  &Tokens[i].Event);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("Unable to create Async IO opertion token. CreateEvent() failed : %s(0x%zx)",
                      E(Status),
                      Status);
            goto Exit;
        }
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              BlockIo2AsyncWaitCallback,
                              NULL,
                              &WaitForAsyncOperation);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Write Tests
    //

    //
    // Async write of MAX_SYNC_ASYNC_OPERATIONS number of 128 KB blocks
    //

    DBG_INFO("Disk Block Size: %lld%s",
             PrettySize(BlockIoMedia->BlockSize),
             PrettySizeStr(BlockIoMedia->BlockSize));
    DBG_INFO("Total Disk Size: %lld%s", PrettySize(TotalDiskSize), PrettySizeStr(TotalDiskSize));
    DBG_INFO("Number of Blocks: %llu", BlockIoMedia->LastBlock);
    DataSize = MaxDataSize;
    UINT64 i = 0;
    while (i < BlockIoMedia->LastBlock) {
        AsyncOperationCount = 0;

        //
        // Bounds check for the last batch
        //

        if (i + ((MAX_SYNC_ASYNC_OPERATIONS * DataSize) / BlockIoMedia->BlockSize) >
            BlockIoMedia->LastBlock)
            break;

        for (UINTN j = 0; j < MAX_SYNC_ASYNC_OPERATIONS; j++) {
            DBG_INFO_RAW("Async writing %lld%s start @ block: %llu(%llu%%)\r",
                         PrettySize(DataSize),
                         PrettySizeStr(DataSize),
                         i,
                         ((i * 100) / BlockIoMedia->LastBlock));

            Status = BlockIo2If->WriteBlocksEx(BlockIo2If,
                                               BlockIoMedia->MediaId,
                                               i,
                                               &Tokens[j],
                                               (UINTN)DataSize,
                                               Data);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("WriteBlocksEx() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            i += (DataSize / BlockIoMedia->BlockSize);
        }

        //
        // Wait until block io 2 async operations are done
        //

        Status = gBS->WaitForEvent(1, &WaitForAsyncOperation, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

    DBG_INFO("");

    //
    // For the last batch use block io
    //

    UINT64 RemainingDiskSize = TotalDiskSize - i * BlockIoMedia->BlockSize;
    for (; i < BlockIoMedia->LastBlock; i += (DataSize / BlockIoMedia->BlockSize)) {
        DataSize = RemainingDiskSize < DataSize ? RemainingDiskSize : DataSize;

        DBG_INFO_RAW("Writing %lld%s start @ block: %llu(%llu%%)\r",
                     PrettySize(DataSize),
                     PrettySizeStr(DataSize),
                     i,
                     ((i * 100) / BlockIoMedia->LastBlock));
        Status = BlockIoIf->WriteBlocks(BlockIoIf, BlockIoMedia->MediaId, i, (UINTN)DataSize, Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("\nFailed to write to block %llu failed : %s(0x%zx)", i, E(Status), Status);
            break;
        }

        RemainingDiskSize -= DataSize;
    }

    DBG_INFO("");

Exit:

    if (Tokens != NULL) {
        for (UINT32 k = 0; k < MAX_SYNC_ASYNC_OPERATIONS; k++) {
            gBS->CloseEvent(Tokens[k].Event);
        }
        FreePool(Tokens);
    }

    FreePool(Data);
    return Status;
}

EFI_STATUS
BlockIo2WriteToAllSectors(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    CHAR16* DevicePath = NULL;
    EFI_BLOCK_IO_MEDIA* BlockIoMedia = NULL;
    EFI_BLOCK_IO_PROTOCOL* BlockIoIf = NULL;
    EFI_BLOCK_IO2_PROTOCOL* BlockIo2If = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathIf = NULL;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextIf = NULL;
    EFI_HANDLE* BlockIoHandles = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN HandleCount = 0;
    BOOLEAN IsUSBDriveInVM = FALSE;

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

    for (UINTN i = 0; i < HandleCount; i++) {
        BlockIoIf = NULL;
        BlockIo2If = NULL;

        Status = gBS->HandleProtocol(BlockIoHandles[i],
                                     &gEfiBlockIoProtocolGuid,
                                     (PVOID*)&BlockIoIf);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        // If available, BLOCKIO2 protocol should be installed on same handle that has BLOCKIO
        // protocol
        Status = gBS->HandleProtocol(BlockIoHandles[i],
                                     &gEfiBlockIo2ProtocolGuid,
                                     (PVOID*)&BlockIo2If);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        BlockIoMedia = BlockIo2If->Media;

        //
        // In a VM, the FAT32 VHD(acting as USB boot disk) cannot be detected as
        // 'Removable' and below check prevent running write test and accidentally
        // making it unbootable!
        //

        if (IsRunningInVM()) {
            IsUSBDriveInVM = BlockIoMedia->BlockSize * BlockIoMedia->LastBlock < GB;
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

            Status = UefiInfoBlockIo2WriteToAllSectors(BlockIoIf, BlockIo2If);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("\nUefiInfoBlockIo2WriteToAllSectors() failed : %s(0x%zx)",
                          E(Status),
                          Status);
            }
            DBG_INFO("");
        }
    }

    Status = EFI_SUCCESS;

Exit:

    FreePool(BlockIoHandles);

    return Status;
}

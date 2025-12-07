/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsblockio2.c

Abstract:

    This module implements blockio2 test suite

Author:

    Vineel Kovvuri (vineelko) 02-Jul-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

#define MAX_SYNC_ASYNC_OPERATIONS 20000
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

static EFI_STATUS UefiInfoBlockIo2(_In_ EFI_BLOCK_IO_PROTOCOL* BlockIoIf,
                                   _In_ EFI_BLOCK_IO2_PROTOCOL* BlockIo2If)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_BLOCK_IO_MEDIA* BlockIoMedia = NULL;
    PVOID Data = NULL;
    UINTN DataSize = 0;
    EFI_TIME StartTime = {0};
    EFI_TIME StopTime = {0};
    UINTN Hours = 0;
    UINTN Minutes = 0;
    UINTN Seconds = 0;
    EFI_BLOCK_IO2_TOKEN* Tokens = NULL;
    UINTN Index = 0;

    if (BlockIoIf == NULL || BlockIo2If == NULL)
        return EFI_INVALID_PARAMETER;

    BlockIoMedia = BlockIoIf->Media;

    //
    // In a VM, the FAT32 VHD(acting as USB boot disk) cannot be detected as
    // 'Removable' and below check prevent running write test and accidentally
    // making it unbootable!
    //

    if (IsRunningInVM()) {
        if (BlockIoMedia->BlockSize * BlockIoMedia->LastBlock < GB)
            return Status;
    }

    //
    // Allocate 128 KB Buffer for read/write operations
    //

    DataSize = 128 * KB;
    Data = AllocatePool(DataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %zd", DataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Read Tests
    //

    AsyncOperationCount = 0;

    //
    // Sync read of MAX_SYNC_ASYNC_OPERATIONS number of 128 KB blocks
    //

    DBG_INFO_RAW("[+] Sync Read of 128 KB %u blocks:", MAX_SYNC_ASYNC_OPERATIONS);
    Status = GetTime(&StartTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StartTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
        Status = BlockIoIf->ReadBlocks(BlockIoIf, BlockIoMedia->MediaId, 0, DataSize, Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ReadBlocks() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Print progress @ 5%
        //

        if (i % ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) == 0) {
            DBG_INFO_RAW("..%d", i / ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) * 5);
        }
    }

    DBG_INFO_RAW("..100%%");

    Status = GetTime(&StopTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StopTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    TimeDiff(&StartTime, &StopTime, &Hours, &Minutes, &Seconds);
    DBG_INFO(" : %02uh:%02um:%02us", (int)Hours, (int)Minutes, (int)Seconds);

    //
    // Async read of MAX_SYNC_ASYNC_OPERATIONS number of 128 KB blocks
    //

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

    DBG_INFO_RAW("[+] Async Read of 128 KB %u blocks:", MAX_SYNC_ASYNC_OPERATIONS);
    Status = GetTime(&StartTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StartTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DataSize = 128 * KB;
    for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
        Status = BlockIo2If->ReadBlocksEx(BlockIo2If,
                                          BlockIoMedia->MediaId,
                                          0,
                                          &Tokens[i],
                                          DataSize,
                                          Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ReadBlocksEx() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Print progress @ 5%
        //

        if (i % ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) == 0) {
            DBG_INFO_RAW("..%d", i / ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) * 5);
        }
    }

    DBG_INFO_RAW("..100%%");

    //
    // Wait until block io 2 async operations are done
    //

    Status = gBS->WaitForEvent(1, &WaitForAsyncOperation, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = GetTime(&StopTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StopTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    TimeDiff(&StartTime, &StopTime, &Hours, &Minutes, &Seconds);
    DBG_INFO(" : %02uh:%02um:%02us", (int)Hours, (int)Minutes, (int)Seconds);

    //
    // Write Tests
    //

    AsyncOperationCount = 0;

    //
    // Sync write of MAX_SYNC_ASYNC_OPERATIONS number of 128 KB blocks
    //

    DBG_INFO_RAW("[+] Sync Write of 128 KB %u blocks:", MAX_SYNC_ASYNC_OPERATIONS);
    Status = GetTime(&StartTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StartTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
        Status = BlockIoIf->WriteBlocks(BlockIoIf, BlockIoMedia->MediaId, 0, DataSize, Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WriteBlocks() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Print progress @ 5%
        //

        if (i % ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) == 0) {
            DBG_INFO_RAW("..%d", i / ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) * 5);
        }
    }

    DBG_INFO_RAW("..100%%");

    Status = GetTime(&StopTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StopTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    TimeDiff(&StartTime, &StopTime, &Hours, &Minutes, &Seconds);
    DBG_INFO(" : %02uh:%02um:%02us", (int)Hours, (int)Minutes, (int)Seconds);

    //
    // Async write of MAX_SYNC_ASYNC_OPERATIONS number of 128 KB blocks
    //

    DBG_INFO_RAW("[+] Async Write of 128 KB %u blocks:", MAX_SYNC_ASYNC_OPERATIONS);
    Status = GetTime(&StartTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StartTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DataSize = 128 * KB;
    for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
        Status = BlockIo2If->WriteBlocksEx(BlockIo2If,
                                           BlockIoMedia->MediaId,
                                           0,
                                           &Tokens[i],
                                           DataSize,
                                           Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WriteBlocksEx() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        //
        // Print progress @ 5%
        //

        if (i % ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) == 0) {
            DBG_INFO_RAW("..%d", i / ((MAX_SYNC_ASYNC_OPERATIONS * 5) / 100) * 5);
        }
    }

    DBG_INFO_RAW("..100%%");

    //
    // Wait until block io 2 async operations are done
    //

    Status = gBS->WaitForEvent(1, &WaitForAsyncOperation, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = GetTime(&StopTime);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Querying for StopTime failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    TimeDiff(&StartTime, &StopTime, &Hours, &Minutes, &Seconds);
    DBG_INFO(" : %02uh:%02um:%02us", (int)Hours, (int)Minutes, (int)Seconds);

    if (IsRunningInVM() == TRUE) {
        //
        // Mike Turner: Hyper-V and real hardware behave really different,
        // particularly with BlockIO, is that a the events are scheduled via a
        // timer event on the real hardware. Hyper-V has real hardware interrupt
        // for I/O operations, and the signal to for the completion event
        // doesn't wait for a timer tick interval. Blocking I/O on the real
        // hardware is a cpu spin until I/O complete.
        //
        // So on the real hardware, there is a delay up to the next timer tick
        // boundary before the completion events occur. Therefore, multiple
        // BlockIo2 signals to the Token->Event may occur on one timer tick
        // event to the BlockIo2 driver before the Dispatcher processes the
        // ready events. Eventually BlockIo2AsyncOperationCallback is called.
        // It will only be called only once (ie it doesn't count the signal
        // events) regardless of the number of completion event signals. This is
        // why each BlockIo2 has to use a different event.
        //
        // Vineel: Due to this, on Hyper-V platform, usually Sync read/write are
        // faster compare to async read/write of the test results

        DBG_INFO("[*] VM detected. Results may not be accurate. Double check on real hardware");
    }

Exit:

    if (Tokens != NULL) {
        for (UINT32 i = 0; i < MAX_SYNC_ASYNC_OPERATIONS; i++) {
            gBS->CloseEvent(Tokens[i].Event);
        }
        FreePool(Tokens);
    }

    FreePool(Data);
    return Status;
}

static EFI_STATUS BlockIo2SyncAsync128KReadWriteTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                                     _In_ PBM_SESSION Session)
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

            UefiInfoBlockIo2(BlockIoIf, BlockIo2If);
            DBG_INFO("");
        }
    }

    Status = EFI_SUCCESS;

Exit:

    FreePool(BlockIoHandles);

    return Status;
}

extern EFI_STATUS BlockIo2WriteToAllSectors(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                            _In_ PBM_SESSION Session);

static BM_TEST DutTests[] = {
    {
        .Name = t("blockio2rw"),
        .Description = t("Block IO 2 Sync/Async 128 KB Block Read/Write Test"),
        .DutTestFn = BlockIo2SyncAsync128KReadWriteTest,
    },
    {
        .Name = t("blockio2fullwrite"),
        .Description = t("Block IO 2 write to all sectors"),
        .DutTestFn = BlockIo2WriteToAllSectors,
    },
};

BM_TEST_SUITE BlockIo2TestSuite = {
    .Description = t("Block IO 2 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsblockio.c

Abstract:

    This module implements blockio test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

#define TEST_BOOLEAN(x) (((x) == FALSE) || ((x) == TRUE))
#define PROP(x)         #x

static BOOLEAN TimerTriggered = FALSE;

static VOID EFIAPI TimerCallback(_In_ EFI_EVENT Event, _In_ VOID* BlockIo2RWContext)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(BlockIo2RWContext);
    TimerTriggered = TRUE;
}

static EFI_STATUS UefiInfoBlockIo(_In_ EFI_BLOCK_IO_PROTOCOL* BlockIoIf)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_BLOCK_IO_MEDIA* BlockIoMedia = NULL;
    PVOID Data = NULL;
    UINTN DataSize = 0;
    UINTN MaxDataSize = 0;
    EFI_EVENT TimerEvent = NULL;

    if (BlockIoIf == NULL)
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

    Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                              TPL_NOTIFY,
                              TimerCallback,
                              NULL,
                              &TimerEvent);

    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Preallocate the largest read/write buffer
    //

    MaxDataSize = 256 * MB;
    do {
        MaxDataSize += 50 * MB;
        Data = NULL;
        Data = AllocatePool(MaxDataSize);
        if (Data == NULL) {
            break;
        }
        FreePool(Data);
    } while (Data != NULL && MaxDataSize <= 4 * GB);
    MaxDataSize -= 50 * MB;

    Data = AllocatePool(MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %zd", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Read test
    //

    DBG_INFO_RAW("[+] Read Test:");

    //
    // Start with 256 MB and increment in 50 MB steps until TimeLapsed is 1 sec
    //

    DataSize = 256 * MB;
    for (UINTN Increment = 100 * MB; Increment >= 1 * MB; Increment /= 2) {
        TimerTriggered = FALSE;
        while (DataSize < MaxDataSize) {
            Status = gBS->SetTimer(TimerEvent, TimerRelative, SEC_TO_100_NS(1));
            if (EFI_ERROR(Status)) {
                DBG_ERROR("SetTimer() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            Status = BlockIoIf->ReadBlocks(BlockIoIf, BlockIoMedia->MediaId, 0, DataSize, Data);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("ReadBlocks() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            if (TimerTriggered == TRUE) {
                break;
            }

            DataSize += Increment;
            DBG_INFO_RAW(".");
        }
        DataSize -= 2 * Increment;
    }

    DBG_INFO(" = %lld MBps", DataSize / MB);

    //
    // Write test
    //

    DBG_INFO_RAW("[+] Write Test:");

    DataSize = 256 * MB;
    for (UINTN Increment = 100 * MB; Increment >= 1 * MB; Increment /= 2) {
        TimerTriggered = FALSE;
        while (DataSize < MaxDataSize) {
            Status = gBS->SetTimer(TimerEvent, TimerRelative, SEC_TO_100_NS(1));
            if (EFI_ERROR(Status)) {
                DBG_ERROR("SetTimer() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            Status = BlockIoIf->WriteBlocks(BlockIoIf, BlockIoMedia->MediaId, 0, DataSize, Data);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("WriteBlocks() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            if (TimerTriggered == TRUE) {
                break;
            }

            DataSize += Increment;
            DBG_INFO_RAW(".");
        }
        DataSize -= 2 * Increment;
    }

    DBG_INFO(" = %lld MBps", DataSize / MB);

Exit:

    gBS->CloseEvent(TimerEvent);
    FreePool(Data);
    return Status;
}

static EFI_STATUS BlockIoLargestBlockReadWriteTest(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                                   _In_ PBM_SESSION Session)
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

        Status = gBS->HandleProtocol(BlockIoHandles[i],
                                     &gEfiBlockIoProtocolGuid,
                                     (PVOID*)&BlockIoIf);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        BlockIoMedia = BlockIoIf->Media;

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

            UefiInfoBlockIo(BlockIoIf);
            DBG_INFO("");
        }
    }

    Status = EFI_SUCCESS;

Exit:

    FreePool(BlockIoHandles);

    return Status;
}

static EFI_STATUS BlockIoProbeInfo(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
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
        BlockIoMedia = EFI_ERROR(Status) ? BlockIoIf->Media : BlockIo2If->Media;
        if (!BlockIoMedia->RemovableMedia && !BlockIoMedia->LogicalPartition) {
            DevicePathIf = DevicePathFromHandle(BlockIoHandles[i]);
            if (DevicePathIf != NULL) {
                DevicePath = DevicePathToTextIf->ConvertDevicePathToText(DevicePathIf,
                                                                         FALSE,
                                                                         FALSE);
                DBG_INFO_U(L"DevicePath                           : %s", DevicePath);
                FreePool(DevicePath);
            }

            DBG_INFO("Block IO 2                           : %s",
                     BlockIo2If ? "Supported" : "Not Supported");
            DBG_INFO("MediaId                              : 0x%08x", BlockIoMedia->MediaId);
            DBG_INFO("ReadOnly                             : %u", BlockIoMedia->ReadOnly);
            DBG_INFO("WriteCaching                         : %u", BlockIoMedia->WriteCaching);
            DBG_INFO("BlockSize                            : %u", BlockIoMedia->BlockSize);
            DBG_INFO("IoAlign                              : %u", BlockIoMedia->IoAlign);
            DBG_INFO("LastBlock                            : 0x%016llx", BlockIoMedia->LastBlock);

            if (BlockIoIf->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION2) {
                DBG_INFO("LowestAlignedLba                     : 0x%016llx",
                         BlockIoMedia->LowestAlignedLba);
                DBG_INFO("LogicalBlocksPerPhysicalBlock        : %u",
                         BlockIoMedia->LogicalBlocksPerPhysicalBlock);
            }

            if (BlockIoIf->Revision >= EFI_BLOCK_IO_PROTOCOL_REVISION3) {
                DBG_INFO("OptimalTransferLengthGranularity     : %u",
                         BlockIoMedia->OptimalTransferLengthGranularity);
            }

            DBG_INFO("Size                                 : %lld %s",
                     PrettySize(BlockIoMedia->LastBlock * BlockIoMedia->BlockSize),
                     PrettySizeStr(BlockIoMedia->LastBlock * BlockIoMedia->BlockSize));

            DBG_INFO("");
        }
    }

Exit:

    FreePool(BlockIoHandles);

    return Status;
}

static EFI_STATUS BlockIoAPITest(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_HANDLE* BlockIoHandles = NULL;
    EFI_BLOCK_IO_PROTOCOL* BlockIoIf = NULL;
    UINTN HandleCount = 0;
    EFI_BLOCK_IO_MEDIA* Media = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    BOOLEAN TestPassed = TRUE;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

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

        Status = gBS->HandleProtocol(BlockIoHandles[i],
                                     &gEfiBlockIoProtocolGuid,
                                     (PVOID*)&BlockIoIf);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        //
        // Validate Media property fields
        //

        Media = BlockIoIf->Media;

        if (BlockIoIf->Revision != EFI_BLOCK_IO_PROTOCOL_REVISION &&
            BlockIoIf->Revision != EFI_BLOCK_IO_PROTOCOL_REVISION2 &&
            BlockIoIf->Revision != EFI_BLOCK_IO_PROTOCOL_REVISION3) {
            DBG_INFO("%s property: Expected (0x%zx or 0x%zx or 0x%zx) : Found (0x%llx)",
                     PROP(Revision),
                     EFI_BLOCK_IO_PROTOCOL_REVISION,
                     EFI_BLOCK_IO_PROTOCOL_REVISION2,
                     EFI_BLOCK_IO_PROTOCOL_REVISION3,
                     BlockIoIf->Revision);
            TestPassed = FALSE;
        }

        if (!TEST_BOOLEAN(Media->RemovableMedia)) {
            DBG_INFO("%s property: Expected (TRUE or FALSE) : Found (0x%x)",
                     PROP(RemovableMedia),
                     Media->RemovableMedia);
            TestPassed = FALSE;
        }

        if (!TEST_BOOLEAN(Media->MediaPresent)) {
            DBG_INFO("%s property: Expected (TRUE or FALSE) : Found (0x%x)",
                     PROP(MediaPresent),
                     Media->MediaPresent);
            TestPassed = FALSE;
        }

        if (!TEST_BOOLEAN(Media->LogicalPartition)) {
            DBG_INFO("%s property: Expected (TRUE or FALSE) : Found (0x%x)",
                     PROP(LogicalPartition),
                     Media->LogicalPartition);
            TestPassed = FALSE;
        }

        if (!TEST_BOOLEAN(Media->ReadOnly)) {
            DBG_INFO("%s property: Expected (TRUE or FALSE) : Found (0x%x)",
                     PROP(ReadOnly),
                     Media->ReadOnly);
            TestPassed = FALSE;
        }

        if (!TEST_BOOLEAN(Media->WriteCaching)) {
            DBG_INFO("%s property: Expected (TRUE or FALSE) : Found (0x%x)",
                     PROP(WriteCaching),
                     Media->WriteCaching);
            TestPassed = FALSE;
        }
    }

Exit:
    FreePool(BlockIoHandles);

    return Status;
}

EFI_STATUS
BlockIoWriteToAllSectors(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session);

static BM_TEST DutTests[] = {
    {
        .Name = t("blockioinfo"),
        .Description = t("Block IO Info"),
        .DutTestFn = BlockIoProbeInfo,
    },
    {
        .Name = t("blockioapi"),
        .Description = t("Block IO API Test"),
        .DutTestFn = BlockIoAPITest,
    },
    {
        .Name = t("blockiorw"),
        .Description = t("Block IO Largest Block Read/Write Test"),
        .DutTestFn = BlockIoLargestBlockReadWriteTest,
    },
    {
        .Name = t("blockiofullwrite"),
        .Description = t("Block IO write to all sectors"),
        .DutTestFn = BlockIoWriteToAllSectors,
    },
};

BM_TEST_SUITE BlockIoTestSuite = {
    .Description = t("Block IO Test Suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

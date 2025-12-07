//
// Global includes
//
#include "common.h"

//
// Local includes
//
#include "memory_map.h"

//
// Constants/Macros
//

//
// Structs
//

//
// Variables
//

//
// Prototypes
//
static INTN EFIAPI ComparePageNumDesc(IN CONST VOID* Left, IN CONST VOID* Right);

//
// Interfaces
//
#ifdef _WIN32
#pragma prefast(push)
#pragma prefast(disable : 6101, \
                "False positive - *ppMemoryMapContext is always initialized upon success")
#endif
EFI_STATUS EFIAPI MemoryMapInit(_Outptr_ MEMORYMAP_CONTEXT** MemoryMapContext)
#ifdef _WIN32
#pragma prefast(pop)
#endif
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    MEMORYMAP_CONTEXT* RetMemoryMapContext = NULL;

    UINTN DescriptorSize;
    UINT32 DescriptorVersion;
    UINTN MapKey;
    PVOID MemoryMapBuffer;
    UINTN MemoryMapSize;
    UINTN PagesNeeded;

    if (MemoryMapContext == NULL) {
        DBG_ERROR("ppMemoryMapContext is null");
        return EFI_INVALID_PARAMETER;
    }

    DescriptorSize = 0;
    DescriptorVersion = 0;
    MapKey = 0;
    MemoryMapBuffer = NULL;
    MemoryMapSize = 0;
    PagesNeeded = 0;

    EfiStatus = gBS->GetMemoryMap(&MemoryMapSize,
                                  MemoryMapBuffer,
                                  &MapKey,
                                  &DescriptorSize,
                                  &DescriptorVersion);
    if (EfiStatus != EFI_BUFFER_TOO_SMALL) {
        DBG_ERROR("GetMemoryMap failed with error 0x%zx (expected EFI_BUFFER_TOO_SMALL)",
                  EfiStatus);
        if (!EFI_ERROR(EfiStatus)) {
            EfiStatus = EFI_ABORTED;
        }
        goto Exit;
    }

    // Per UEFI spec, returned memory map size should be padded (although it doesn't suggest by
    // how much....)
    MemoryMapSize += 512;

    PagesNeeded = ALIGN_RANGE_UP(MemoryMapSize, PAGE_SIZE) >> PAGE_SHIFT;

    EfiStatus = gBS->AllocatePages(AllocateAnyPages,
                                   EfiLoaderData,
                                   PagesNeeded,
                                   (EFI_PHYSICAL_ADDRESS*)&MemoryMapBuffer);

    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("AllocatePages failed with error 0x%zx", EfiStatus);
        goto Exit;
    }

    EfiStatus = gBS->GetMemoryMap(&MemoryMapSize,
                                  MemoryMapBuffer,
                                  &MapKey,
                                  &DescriptorSize,
                                  &DescriptorVersion);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("2nd GetMemoryMap failed with error 0x%zx", EfiStatus);
        goto Exit;
    }

    RetMemoryMapContext = AllocateZeroPool(sizeof(MEMORYMAP_CONTEXT));
    if (RetMemoryMapContext == NULL) {
        EfiStatus = EFI_OUT_OF_RESOURCES;
        DBG_ERROR("Failed to allocate MemoryMapContext");
        goto Exit;
    }

    RetMemoryMapContext->MemoryMapSize = MemoryMapSize;
    RetMemoryMapContext->PagesNeeded = PagesNeeded;
    RetMemoryMapContext->MapKey = MapKey;
    RetMemoryMapContext->DescriptorSize = DescriptorSize;
    RetMemoryMapContext->DescriptorVersion = DescriptorVersion;

    RetMemoryMapContext->MemoryMap = (EFI_MEMORY_DESCRIPTOR*)MemoryMapBuffer;
    MemoryMapBuffer = NULL;

    *MemoryMapContext = RetMemoryMapContext;
    RetMemoryMapContext = NULL;

Exit:
    MemoryMapFree(RetMemoryMapContext);

    if (MemoryMapBuffer != NULL) {
        (VOID) gBS->FreePages((EFI_PHYSICAL_ADDRESS)MemoryMapBuffer, PagesNeeded);
    }

    return EfiStatus;
}

VOID EFIAPI MemoryMapFree(_In_opt_ MEMORYMAP_CONTEXT* MemoryMapContext)
{
    if (MemoryMapContext) {
        if (MemoryMapContext->MemoryMap) {
            (VOID) gBS->FreePages((EFI_PHYSICAL_ADDRESS)MemoryMapContext->MemoryMap,
                                  MemoryMapContext->PagesNeeded);
        }

        ZeroMem(MemoryMapContext, sizeof(MEMORYMAP_CONTEXT));
        FreePool(MemoryMapContext);
    }
}

EFI_STATUS EFIAPI MemoryMapGetDescriptors(_In_ MEMORYMAP_CONTEXT* MemoryMapContext,
                                          _Inout_ EFI_MEMORY_DESCRIPTOR* MemoryMapBuffer,
                                          _Inout_ UINTN* MemoryMapBufferLength,
                                          _Out_ UINTN* DescriptorSize)
{
    if (MemoryMapContext == NULL) {
        DBG_ERROR("MemoryMapContext is null");
        return EFI_INVALID_PARAMETER;
    }

    if (*MemoryMapBufferLength < MemoryMapContext->MemoryMapSize) {
        DBG_ERROR(
            "Buffer length too small. Actual: %zd, required: %zd. Please call function with correct buffer length",
            *MemoryMapBufferLength,
            MemoryMapContext->MemoryMapSize);

        *MemoryMapBufferLength = MemoryMapContext->MemoryMapSize;
        return EFI_BUFFER_TOO_SMALL;
    }

    CopyMem(MemoryMapBuffer, MemoryMapContext->MemoryMap, MemoryMapContext->MemoryMapSize);

    *MemoryMapBufferLength = MemoryMapContext->MemoryMapSize;
    *DescriptorSize = MemoryMapContext->DescriptorSize;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI MemoryMapGetLargestRegion(_In_ MEMORYMAP_CONTEXT* MemoryMapContext,
                                            _Out_ UINT64* RegionSize)
{
    EFI_MEMORY_DESCRIPTOR* TempMemoryMap = NULL;
    UINT64 RetRegionSize = 0;
    UINTN NumElements = 0;

    if (MemoryMapContext == NULL) {
        DBG_ERROR("MemoryMapContext is null");
        return EFI_INVALID_PARAMETER;
    }

    if (RegionSize == NULL) {
        DBG_ERROR("pqwRegionSize is NULL");
        return EFI_INVALID_PARAMETER;
    }

    TempMemoryMap = (EFI_MEMORY_DESCRIPTOR*)AllocatePool(MemoryMapContext->MemoryMapSize);
    if (TempMemoryMap == NULL) {
        DBG_ERROR("Unable to allocate buffer");
        return EFI_OUT_OF_RESOURCES;
    }

    CopyMem(TempMemoryMap, MemoryMapContext->MemoryMap, MemoryMapContext->MemoryMapSize);

    NumElements = MemoryMapContext->MemoryMapSize / MemoryMapContext->DescriptorSize;

    PerformQuickSort(TempMemoryMap,
                     NumElements,
                     MemoryMapContext->DescriptorSize,
                     ComparePageNumDesc);

    RetRegionSize = TempMemoryMap[0].NumberOfPages * 4096;

    FreePool(TempMemoryMap);
    TempMemoryMap = NULL;

    *RegionSize = RetRegionSize;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI MemoryMapGetFreePages(_In_ MEMORYMAP_CONTEXT* MemoryMapContext,
                                        _Out_ UINT64* FreePages)
{
    EFI_MEMORY_DESCRIPTOR* EfiDescriptor;
    UINTN MemoryMapSize;
    UINTN DescriptorSize;
    UINT64 NumFreePages;

    if (MemoryMapContext == NULL) {
        DBG_ERROR("MemoryMapContext is null");
        return EFI_INVALID_PARAMETER;
    }

    MemoryMapSize = MemoryMapContext->MemoryMapSize;
    DescriptorSize = MemoryMapContext->DescriptorSize;
    NumFreePages = 0;

    for (EfiDescriptor = (EFI_MEMORY_DESCRIPTOR*)(MemoryMapContext->MemoryMap); MemoryMapSize != 0;
         MemoryMapSize -= DescriptorSize, EfiDescriptor = Add2Ptr(EfiDescriptor, DescriptorSize)) {
        if (EfiDescriptor->Type == EfiConventionalMemory) {
            NumFreePages += EfiDescriptor->NumberOfPages;
        }
    }

    *FreePages = NumFreePages;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI MemoryMapPrintInfo(_In_ MEMORYMAP_CONTEXT* MemoryMapContext)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;

    EFI_MEMORY_DESCRIPTOR* TempMemoryMap;
    UINTN MemoryMapSize;
    UINTN MemoryMapSizeTemp;
    UINTN DescriptorSize;
    UINTN NumElements;
    EFI_MEMORY_DESCRIPTOR* EfiDescriptor;

    UINT32 Regions;
    UINT32 TotalRegions;
    UINT64 LargestRegionSizeInBytes;

    if (MemoryMapContext == NULL) {
        DBG_ERROR("MemoryMapContext is null");
        return EFI_INVALID_PARAMETER;
    }

    TempMemoryMap = NULL;
    MemoryMapSize = MemoryMapContext->MemoryMapSize;
    MemoryMapSizeTemp = MemoryMapSize;
    DescriptorSize = MemoryMapContext->DescriptorSize;
    NumElements = MemoryMapContext->MemoryMapSize / MemoryMapContext->DescriptorSize;

    Regions = 0;
    TotalRegions = 3;
    LargestRegionSizeInBytes = 0;

    DBG_INFO_RAW(
        "Physical Address   Virtual Address    Attributes         (   Type   ) NumberOfPages\r\n");

    for (EfiDescriptor = (EFI_MEMORY_DESCRIPTOR*)(MemoryMapContext->MemoryMap);
         MemoryMapSizeTemp != 0;
         MemoryMapSizeTemp -= DescriptorSize,
        EfiDescriptor = Add2Ptr(EfiDescriptor, DescriptorSize)) {
        DBG_INFO_RAW("0x%016I64x 0x%016I64x 0x%016I64x (0x%08x) 0x%-8I64x\r\n",
                     EfiDescriptor->PhysicalStart,
                     EfiDescriptor->VirtualStart,
                     EfiDescriptor->Attribute,
                     EfiDescriptor->Type,
                     EfiDescriptor->NumberOfPages);
    }

    DBG_INFO_RAW("\r\nTop %u largest contiguous available regions:\r\n", TotalRegions);
    DBG_INFO_RAW(
        "Physical Address   Virtual Address    Attributes         (   Type   ) NumberOfPages SizeInMB\r\n");

    TempMemoryMap = (EFI_MEMORY_DESCRIPTOR*)AllocatePool(MemoryMapSize);
    if (TempMemoryMap == NULL) {
        DBG_ERROR("Unable to allocate buffer");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    CopyMem(TempMemoryMap, MemoryMapContext->MemoryMap, MemoryMapSize);

    PerformQuickSort(TempMemoryMap, NumElements, DescriptorSize, ComparePageNumDesc);

    // Print largest k available regions, where k == TotalRegions
    MemoryMapSizeTemp = MemoryMapSize;
    for (EfiDescriptor = (EFI_MEMORY_DESCRIPTOR*)(TempMemoryMap);
         MemoryMapSizeTemp != 0 && Regions < TotalRegions;
         MemoryMapSizeTemp -= DescriptorSize,
        EfiDescriptor = Add2Ptr(EfiDescriptor, DescriptorSize)) {
        if (EfiDescriptor->Type == EfiConventionalMemory) {
            DBG_INFO_RAW("0x%016I64x 0x%016I64x 0x%016I64x (0x%08x) 0x%-8I64x    %lluMB\r\n",
                         EfiDescriptor->PhysicalStart,
                         EfiDescriptor->VirtualStart,
                         EfiDescriptor->Attribute,
                         EfiDescriptor->Type,
                         EfiDescriptor->NumberOfPages,
                         (EfiDescriptor->NumberOfPages * 4096) / (1024 * 1024));

            Regions++;
        }
    }

    EfiStatus = MemoryMapGetLargestRegion(MemoryMapContext, &LargestRegionSizeInBytes);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR_RAW("MemoryMapGetLargestRegion failed with error 0x%zx\r\n", EfiStatus);
    } else {
        DBG_INFO_RAW("\r\nLargest region size in bytes: %llu\r\n", LargestRegionSizeInBytes);
    }

Exit:
    FreePool(TempMemoryMap);
    TempMemoryMap = NULL;

    return EfiStatus;
}

//
// Local functions
//
static INTN EFIAPI ComparePageNumDesc(IN CONST VOID* Left, IN CONST VOID* Right)
{
    EFI_MEMORY_DESCRIPTOR* MemoryDescriptor1;
    EFI_MEMORY_DESCRIPTOR* MemoryDescriptor2;

    MemoryDescriptor1 = (EFI_MEMORY_DESCRIPTOR*)Left;
    MemoryDescriptor2 = (EFI_MEMORY_DESCRIPTOR*)Right;

    if (MemoryDescriptor1->NumberOfPages > MemoryDescriptor2->NumberOfPages)
        return -1;
    else if (MemoryDescriptor1->NumberOfPages < MemoryDescriptor2->NumberOfPages)
        return 1;

    return 0;
}

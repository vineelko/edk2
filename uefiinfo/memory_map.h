#ifndef _MEMORY_MAP_H_
#define _MEMORY_MAP_H_

typedef struct _MEMORYMAP_CONTEXT {
    UINTN MemoryMapSize;
    UINTN PagesNeeded;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    EFI_MEMORY_DESCRIPTOR* MemoryMap;
} MEMORYMAP_CONTEXT, *PMEMORYMAP_CONTEXT;

EFI_STATUS EFIAPI MemoryMapInit(_Outptr_ MEMORYMAP_CONTEXT** ppMemoryMapContext);
VOID EFIAPI MemoryMapFree(_In_opt_ MEMORYMAP_CONTEXT* pMemoryMapContext);
EFI_STATUS EFIAPI MemoryMapGetDescriptors(_In_ MEMORYMAP_CONTEXT* pMemoryMapContext,
                                          _Inout_ EFI_MEMORY_DESCRIPTOR* pMemoryMapBuffer,
                                          _Inout_ UINTN* punMemoryMapBufferLength,
                                          _Out_ UINTN* punDescriptorSize);
EFI_STATUS EFIAPI MemoryMapGetLargestRegion(_In_ MEMORYMAP_CONTEXT* pMemoryMapContext,
                                            _Out_ UINT64* pqwRegionSize);
EFI_STATUS EFIAPI MemoryMapGetFreePages(_In_ MEMORYMAP_CONTEXT* MemoryMapContext,
                                        _Out_ UINT64* FreePages);
EFI_STATUS EFIAPI MemoryMapPrintInfo(_In_ MEMORYMAP_CONTEXT* pMemoryMapContext);

#endif // _MEMORY_MAP_H_

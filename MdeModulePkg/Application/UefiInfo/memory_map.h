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

EFI_STATUS EFIAPI MemoryMapInit(OUT MEMORYMAP_CONTEXT** ppMemoryMapContext);
VOID EFIAPI MemoryMapFree(IN MEMORYMAP_CONTEXT* pMemoryMapContext);
EFI_STATUS EFIAPI MemoryMapGetDescriptors(IN MEMORYMAP_CONTEXT* pMemoryMapContext,
                                          IN OUT EFI_MEMORY_DESCRIPTOR* pMemoryMapBuffer,
                                          IN OUT UINTN* punMemoryMapBufferLength,
                                          OUT UINTN* punDescriptorSize);
EFI_STATUS EFIAPI MemoryMapGetLargestRegion(IN MEMORYMAP_CONTEXT* pMemoryMapContext,
                                            OUT UINT64* pqwRegionSize);
EFI_STATUS EFIAPI MemoryMapGetFreePages(IN MEMORYMAP_CONTEXT* MemoryMapContext,
                                        OUT UINT64* FreePages);
EFI_STATUS EFIAPI MemoryMapPrintInfo(IN MEMORYMAP_CONTEXT* pMemoryMapContext);

#endif // _MEMORY_MAP_H_

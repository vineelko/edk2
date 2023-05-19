#include "common.h"

#include "protocols.h"
#include "testsuites.h"

// clang-format off
ENUM_TO_STRING MemoryTypeToString[] = {
    {EfiReservedMemoryType,      STRINGIFY(EfiReservedMemoryType)},
    {EfiLoaderCode,              STRINGIFY(EfiLoaderCode)},
    {EfiLoaderData,              STRINGIFY(EfiLoaderData)},
    {EfiBootServicesCode,        STRINGIFY(EfiBootServicesCode)},
    {EfiBootServicesData,        STRINGIFY(EfiBootServicesData)},
    {EfiRuntimeServicesCode,     STRINGIFY(EfiRuntimeServicesCode)},
    {EfiRuntimeServicesData,     STRINGIFY(EfiRuntimeServicesData)},
    {EfiConventionalMemory,      STRINGIFY(EfiConventionalMemory)},
    {EfiUnusableMemory,          STRINGIFY(EfiUnusableMemory)},
    {EfiACPIReclaimMemory,       STRINGIFY(EfiACPIReclaimMemory)},
    {EfiACPIMemoryNVS,           STRINGIFY(EfiACPIMemoryNVS)},
    {EfiMemoryMappedIO,          STRINGIFY(EfiMemoryMappedIO)},
    {EfiMemoryMappedIOPortSpace, STRINGIFY(EfiMemoryMappedIOPortSpace)},
    {EfiPalCode,                 STRINGIFY(EfiPalCode)},
    {EfiPersistentMemory,        STRINGIFY(EfiPersistentMemory)},
    {EfiUnacceptedMemoryType,    STRINGIFY(EfiUnacceptedMemoryType)},
};
// clang-format on

static EFI_STATUS DumpMemoryMap(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN MemoryMapSize = 0;
    UINTN MapKey = 0;
    UINTN DescriptorSize = 0;
    UINT32 DescriptorVersion = 0;
    EFI_MEMORY_DESCRIPTOR* MemoryMap = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->GetMemoryMap(&MemoryMapSize,
                               MemoryMap,
                               &MapKey,
                               &DescriptorSize,
                               &DescriptorVersion);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        MemoryMap = AllocateZeroPool(MemoryMapSize);
    } else {
        DBG_ERROR("GetMemoryMap() call failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->GetMemoryMap(&MemoryMapSize,
                               MemoryMap,
                               &MapKey,
                               &DescriptorSize,
                               &DescriptorVersion);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetMemoryMap() call failed : %a(0x%x)", E(Status), Status);
    }

    DBG_INFO("%26a %16a %16a %16a %16a",
             "Type",
             "PhysicalStart",
             "VirtualStart",
             "NumberOfPages",
             "Attribute");
    DBG_INFO("----------------------------------------------------------------------------------------------");
    for (UINTN i = 0; i < MemoryMapSize / DescriptorSize; i++) {
        EFI_MEMORY_DESCRIPTOR* Entry = (EFI_MEMORY_DESCRIPTOR*)((UINT8*)MemoryMap +
                                                                i * DescriptorSize);
        DBG_INFO("%26a %16x %16x %16x %16x",
                 MemoryTypeToString[Entry->Type].String,
                 Entry->PhysicalStart,
                 Entry->VirtualStart,
                 Entry->NumberOfPages,
                 Entry->Attribute);
    }

Exit:

    FreePool(MemoryMap);
    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("memoryinfo"),
        .Description = t("Memory Map Info"),
        .DutTestFn = DumpMemoryMap,
    },
};

UEFIINFO_TEST_SUITE MemoryTestSuite = {
    .Description = t("Memory test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

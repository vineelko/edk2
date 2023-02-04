/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsmemory.c

Abstract:

    This module implements dumping of memory map information

Author:

    Vineel Kovvuri (vineelko) 17-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

static EFI_STATUS DumpMemoryMap(IN PBM_SESSION Session)
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

    DBG_INFO("%-16a %-16a% -16a %-16a %-16a",
             "Type",
             "PhysicalStart",
             "VirtualStart",
             "NumberOfPages",
             "Attribute");
    DBG_INFO("---------------------------------------------------------------------");
    for (UINTN i = 0; i < MemoryMapSize / DescriptorSize; i++) {
        EFI_MEMORY_DESCRIPTOR* Entry = (EFI_MEMORY_DESCRIPTOR*)((UINT8*)MemoryMap +
                                                                i * DescriptorSize);
        DBG_INFO("%16x %16x %16x %16x %16x",
                 Entry->Type,
                 Entry->PhysicalStart,
                 Entry->VirtualStart,
                 Entry->NumberOfPages,
                 Entry->Attribute);
    }

Exit:

    FreePool(MemoryMap);
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("memoryinfo"),
        .Description = t("Memory Map Info"),
        .DutTestFn = DumpMemoryMap,
    },
};

BM_TEST_SUITE MemoryTestSuite = {
    .Description = t("Memory test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

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
#include "memory_map.h"

static EFI_STATUS DumpMemoryMap(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    MEMORYMAP_CONTEXT* MemoryMapContext = NULL;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = MemoryMapInit(&MemoryMapContext);
    if (!EFI_ERROR(Status)) {
        MemoryMapPrintInfo(MemoryMapContext);
        MemoryMapFree(MemoryMapContext);
    }

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

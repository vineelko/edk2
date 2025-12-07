/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsrng.c

Abstract:

    This module implements random number generator test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

static EFI_STATUS RngProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_RNG_PROTOCOL* RngProtocol = NULL;
    UINTN AlgorithmListSize = 0;
    EFI_RNG_ALGORITHM* AlgorithmList = (EFI_RNG_ALGORITHM*)~0; // HACK: GetInfo do not accept NULL
                                                               // to query the size!
    UINT8 RngData[128] = {0};

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_RNG_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_RNG_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    RngProtocol = ProtocolArray[EFI_RNG_PROTOCOL_INDEX].Protocol;

    Status = RngProtocol->GetInfo(RngProtocol, &AlgorithmListSize, AlgorithmList);
    if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
        DBG_ERROR("GetInfo() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    AlgorithmList = AllocateZeroPool(AlgorithmListSize);
    if (AlgorithmList == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd", AlgorithmListSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = RngProtocol->GetInfo(RngProtocol, &AlgorithmListSize, AlgorithmList);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetInfo() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Found %zu RNG algorithms", AlgorithmListSize / sizeof(EFI_RNG_ALGORITHM));

    for (UINTN i = 0; i < AlgorithmListSize / sizeof(EFI_RNG_ALGORITHM); i++) {
        ZeroMem(RngData, _countof(RngData));
        Status = RngProtocol->GetRNG(RngProtocol, &AlgorithmList[i], _countof(RngData), RngData);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetRNG() call for algorithm %zu failed : %s(0x%zx)", i, E(Status), Status);
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO("Dumping %zu bytes of RNG data", _countof(RngData));
        HexDump(RngData, _countof(RngData));
    }

Exit:

    if (AlgorithmList != (EFI_RNG_ALGORITHM*)~0) {
        FreePool(AlgorithmList);
    }

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("rnginfo"),
        .Description = t("Random Number Generator Info"),
        .DutTestFn = RngProbe,
    },
};

BM_TEST_SUITE RandomNumberGeneratorTestSuite = {
    .Description = t("Random Number Generator test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

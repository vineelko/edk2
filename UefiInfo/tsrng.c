#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

static EFI_STATUS RngProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_RNG_PROTOCOL* RngProtocol = NULL;
    UINTN AlgorithmListSize = 0;
    EFI_RNG_ALGORITHM* AlgorithmList = (EFI_RNG_ALGORITHM*)~0; // HACK: GetInfo do not accept NULL
                                                               // to query the size!
    UINT8 RngData[128];

    UNREFERENCED_PARAMETER(Session);

    ZeroMem(RngData, _countof(RngData));

    ProtocolGetInfo(&ProtocolArray[EFI_RNG_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_RNG_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_RNG_PROTOCOL Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    RngProtocol = ProtocolArray[EFI_RNG_PROTOCOL_INDEX].Protocol;

    Status = RngProtocol->GetInfo(RngProtocol, &AlgorithmListSize, AlgorithmList);
    if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
        DBG_ERROR("GetInfo() call failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    AlgorithmList = AllocateZeroPool(AlgorithmListSize);
    if (AlgorithmList == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", AlgorithmListSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = RngProtocol->GetInfo(RngProtocol, &AlgorithmListSize, AlgorithmList);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetInfo() call failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Found %u RNG algorithms", AlgorithmListSize / sizeof(EFI_RNG_ALGORITHM));

    for (UINTN i = 0; i < AlgorithmListSize / sizeof(EFI_RNG_ALGORITHM); i++) {
        ZeroMem(RngData, _countof(RngData));
        Status = RngProtocol->GetRNG(RngProtocol, &AlgorithmList[i], _countof(RngData), RngData);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetRNG() call for algorithm %u failed : %a(0x%x)", i, E(Status), Status);
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO("Dumping %u bytes of RNG data", _countof(RngData));
        HexDump(RngData, _countof(RngData));
    }

Exit:

    if (AlgorithmList != (EFI_RNG_ALGORITHM*)~0) {
        FreePool(AlgorithmList);
    }

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("rnginfo"),
        .Description = t("Random Number Generator Info"),
        .DutTestFn = RngProbe,
    },
};

UEFIINFO_TEST_SUITE RandomNumberGeneratorTestSuite = {
    .Description = t("Random Number Generator test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

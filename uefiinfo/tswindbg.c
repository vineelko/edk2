/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tswindbg.c

Abstract:

    This module implements Windbg server related test suite

Author:

    Vineel Kovvuri (vineelko) 08-Dec-2022

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

#define EFI_MS_WINDBG_SERVER_PROTOCOL_GUID                 \
    {                                                      \
        0xf409a149, 0xc476, 0x4182,                        \
        {                                                  \
            0xbf, 0x06, 0xf4, 0x76, 0xd9, 0xeb, 0xd7, 0x41 \
        }                                                  \
    }

static EFI_STATUS WindbgUnload(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    UINTN i = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);
    UNREFERENCED_PARAMETER(Session);

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &(EFI_GUID)EFI_MS_WINDBG_SERVER_PROTOCOL_GUID,
                                     NULL,
                                     &HandleCount,
                                     &Handles);
    if (Status == EFI_NOT_FOUND) {
        DBG_INFO("No previous instance of windbg server driver is detected");
        Status = EFI_SUCCESS;
    } else if (Status == EFI_SUCCESS) {
        for (UINTN j = 0; j < HandleCount; j++) {
            Status = gBS->UnloadImage(Handles[i]);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("Unload() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }

            DBG_INFO("Unloaded previous instance of windbg server driver");
        }
    }

Exit:
    FreePool(Handles);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("windbgunload"),
        .Description = t("Unload WinDbg server driver"),
        .DutTestFn = WindbgUnload,
    },
};

BM_TEST_SUITE WindbgTestSuite = {
    .Description = t("Windbg server related test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

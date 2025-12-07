/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tstextinput.c

Abstract:

    This module implements reading input from keyboard test suite

Author:

    Vineel Kovvuri (vineelko) 08-Mar-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

static EFI_STATUS TextInputProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* TextInputProtocol = NULL;
    EFI_KEY_DATA Data;
    UINTN Index = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    TextInputProtocol = ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX].Protocol;

    do {
        Status = gBS->WaitForEvent(1, &TextInputProtocol->WaitForKeyEx, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent failed : %s(0x%zx)", E(Status), Status);
            break;
        }

        Status = TextInputProtocol->ReadKeyStrokeEx(TextInputProtocol, &Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ReadKeyStrokeEx failed : %s(0x%zx)", E(Status), Status);
            break;
        }

        DBG_INFO_U(L"%c", Data.Key.UnicodeChar);
    } while (Data.Key.UnicodeChar != 'X');

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("textinputinfo"),
        .Description = t("Text Input Info"),
        .DutTestFn = TextInputProbe,
    },
};

BM_TEST_SUITE TextInputTestSuite = {
    .Description = t("Text Input test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

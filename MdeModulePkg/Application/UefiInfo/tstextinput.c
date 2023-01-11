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

static EFI_STATUS TextInputProbe(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* TextInputProtocol = NULL;
    EFI_KEY_DATA Data;
    UINTN Index = 0;

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL Protocol not available : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    TextInputProtocol = ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX].Protocol;

    do {
        Status = gBS->WaitForEvent(1, &TextInputProtocol->WaitForKeyEx, &Index);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("WaitForEvent failed : %a(0x%x)", E(Status), Status);
            break;
        }

        Status = TextInputProtocol->ReadKeyStrokeEx(TextInputProtocol, &Data);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ReadKeyStrokeEx failed : %a(0x%x)", E(Status), Status);
            break;
        }

        DBG_INFO_U(L"%c", Data.Key.UnicodeChar);
    } while (Data.Key.UnicodeChar != 'X');

Exit:

    return Status;
}


VOID* gNotifyKeyboardHandle1 = NULL;
VOID* gNotifyKeyboardHandle2 = NULL;
EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* gSimpleInputExProtocol = NULL;

EFI_STATUS
EFIAPI
HandleKeyboardNotifications(IN EFI_KEY_DATA* KeyData)
{
    DBG_INFO("ScanCode:%d UnicodeChar: %d %x %x",
             KeyData->Key.ScanCode,
             KeyData->Key.UnicodeChar,
             KeyData->KeyState.KeyShiftState,
             KeyData->KeyState.KeyToggleState);

    if (KeyData->Key.UnicodeChar == L's' &&
        KeyData->KeyState.KeyShiftState == (EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED)) {
        DBG_INFO("Pressed Ctrl+S");
    }

    if (KeyData->Key.UnicodeChar == 19 && KeyData->KeyState.KeyShiftState == 0) {
        DBG_INFO("Pressed Ctrl+S - Hyper-V");
    }

    return EFI_SUCCESS;
}

VOID EFIAPI UnregisterKeyboardNotifications()
{
    if (gNotifyKeyboardHandle1 != NULL && gSimpleInputExProtocol != NULL) {
        gSimpleInputExProtocol->UnregisterKeyNotify(gSimpleInputExProtocol, gNotifyKeyboardHandle1);
    }

    if (gNotifyKeyboardHandle2 != NULL && gSimpleInputExProtocol != NULL) {
        gSimpleInputExProtocol->UnregisterKeyNotify(gSimpleInputExProtocol, gNotifyKeyboardHandle2);
    }
}

static EFI_STATUS RegisterKeyboardNotifications()
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_KEY_DATA KeyData = {0};

    Status = gBS->HandleProtocol(gSystemTable->ConsoleInHandle,
                                 &gEfiSimpleTextInputExProtocolGuid,
                                 (VOID**)&gSimpleInputExProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed 0x%x", Status);
        goto Exit;
    }

    //
    // For consoles that supports/reports shift state,
    // make sure only CONTROL is pressed.
    //

    KeyData.KeyState.KeyToggleState = 0;
    KeyData.Key.ScanCode = 0;
    KeyData.KeyState.KeyShiftState = EFI_SHIFT_STATE_VALID | EFI_LEFT_CONTROL_PRESSED;
    KeyData.Key.UnicodeChar = L's';
    Status = gSimpleInputExProtocol->RegisterKeyNotify(gSimpleInputExProtocol,
                                                       &KeyData,
                                                       HandleKeyboardNotifications,
                                                       &gNotifyKeyboardHandle1);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("RegisterKeyNotify() failed 0x%x", Status);
        goto Exit;
    }

    //
    // For consoles that don't support/report shift state, Ctrl+A is translated
    // to 1 (UnicodeChar) and Ctrl+S is translated to 19 (UnicodeChar). Hyper-V
    // is one example I know of. In order for this to work in Hyper-V we should
    // also set KeyShiftState to zero
    //

    KeyData.KeyState.KeyShiftState = 0;
    KeyData.Key.UnicodeChar = 19; // s

    Status = gSimpleInputExProtocol->RegisterKeyNotify(gSimpleInputExProtocol,
                                                       &KeyData,
                                                       HandleKeyboardNotifications,
                                                       &gNotifyKeyboardHandle2);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("RegisterKeyNotify() failed 0x%x", Status);
        goto Exit;
    }

Exit:
    return Status;
}

static EFI_STATUS KeyboardRegisterKey(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    RegisterKeyboardNotifications();

    while (TRUE) {
        EfiSleep(SEC_TO_100_NS(4));
    }

    return Status;
}

static EFI_STATUS KeyboardPollKey(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN EventIndex = 0;
    EFI_KEY_DATA KeyData;

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->HandleProtocol(gSystemTable->ConsoleInHandle,
                                 &gEfiSimpleTextInputExProtocolGuid,
                                 (VOID**)&gSimpleInputExProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("HandleProtocol() failed 0x%x", Status);
        goto Exit;
    }

    //
    // use below code to find out how each key is getting captured on a platform
    // and use the value accordingly to configure for RegisterKeyNotify
    //
    while (TRUE) {
        Status = gBS->WaitForEvent(1, &gSimpleInputExProtocol->WaitForKeyEx, &EventIndex);
        Status = gSimpleInputExProtocol->ReadKeyStrokeEx(gSimpleInputExProtocol, &KeyData);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ReadKeyStrokeEx() failed 0x%x", Status);
            goto Exit;
        }

        DBG_INFO("ScanCode:%d UnicodeChar: %d KeyShiftState: %x KeyToggleState: %x",
                 KeyData.Key.ScanCode,
                 KeyData.Key.UnicodeChar,
                 KeyData.KeyState.KeyShiftState,
                 KeyData.KeyState.KeyToggleState);
    }

Exit:
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("textinputinfo"),
        .Description = t("Text Input Info"),
        .DutTestFn = TextInputProbe,
    },
    {
        .Name = t("keyboardregisterctrls"),
        .Description = t("Validate if Ctrl+S can be registered or not"),
        .DutTestFn = KeyboardRegisterKey,
    },
    {
        .Name = t("keyboardpollctrls"),
        .Description = t("Validate if Ctrl+S can be polled or not"),
        .DutTestFn = KeyboardPollKey,
    },
};

BM_TEST_SUITE TextInputTestSuite = {
    .Description = t("Text Input test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

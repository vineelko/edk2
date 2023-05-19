#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

static EFI_STATUS TextInputProbe(IN PUEFIINFO_SESSION Session)
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

//
// clang-format off
//
// | Name              | Ctrl-Char | Dec | Hex | Char | Dec | Hex | Char  | Dec | Hex | Char | Dec | Hex | Char |
// | ----------------- | --------- | --- | --- | ---- | --- | --- | ----- | --- | --- | ---- | --- | --- | ---- |
// | null              | ctrl-@    | 0   | 00  | NUL  | 32  | 20  | Space | 64  | 40  | @    | 96  | 60  | \`   |
// | start of heading  | ctrl-A    | 1   | 01  | SOH  | 33  | 21  | !     | 65  | 41  | A    | 97  | 61  | a    |
// | start of text     | ctrl-B    | 2   | 02  | STX  | 34  | 22  | "     | 66  | 42  | B    | 98  | 62  | b    |
// | end of text       | ctrl-C    | 3   | 03  | ETX  | 35  | 23  | #     | 67  | 43  | C    | 99  | 63  | c    |
// | end of xmit       | ctrl-D    | 4   | 04  | EOT  | 36  | 24  | $     | 68  | 44  | D    | 100 | 64  | d    |
// | enquiry           | ctrl-E    | 5   | 05  | ENQ  | 37  | 25  | %     | 69  | 45  | E    | 101 | 65  | e    |
// | acknowledge       | ctrl-F    | 6   | 06  | ACK  | 38  | 26  | &     | 70  | 46  | F    | 102 | 66  | f    |
// | bell              | ctrl-G    | 7   | 07  | BEL  | 39  | 27  | '     | 71  | 47  | G    | 103 | 67  | g    |
// | backspace         | ctrl-H    | 8   | 08  | BS   | 40  | 28  | (     | 72  | 48  | H    | 104 | 68  | h    |
// | horizontal tab    | ctrl-I    | 9   | 09  | HT   | 41  | 29  | )     | 73  | 49  | I    | 105 | 69  | i    |
// | line feed         | ctrl-J    | 10  | 0A  | LF   | 42  | 2A  | \*    | 74  | 4A  | J    | 106 | 6A  | j    |
// | vertical tab      | ctrl-K    | 11  | 0B  | VT   | 43  | 2B  | +     | 75  | 4B  | K    | 107 | 6B  | k    |
// | form feed         | ctrl-L    | 12  | 0C  | FF   | 44  | 2C  | ,     | 76  | 4C  | L    | 108 | 6C  | l    |
// | carriage feed     | ctrl-M    | 13  | 0D  | CR   | 45  | 2D  | \-    | 77  | 4D  | M    | 109 | 6D  | m    |
// | shift out         | ctrl-N    | 14  | 0E  | SO   | 46  | 2E  | .     | 78  | 4E  | N    | 110 | 6E  | n    |
// | shift in          | ctrl-O    | 15  | 0F  | SI   | 47  | 2F  | /     | 79  | 4F  | O    | 111 | 6F  | o    |
// | data line escape  | ctrl-P    | 16  | 10  | DLE  | 48  | 30  | 0     | 80  | 50  | P    | 112 | 70  | p    |
// | device control 1  | ctrl-Q    | 17  | 11  | DC1  | 49  | 31  | 1     | 81  | 51  | Q    | 113 | 71  | q    |
// | device control 2  | ctrl-R    | 18  | 12  | DC2  | 50  | 32  | 2     | 82  | 52  | R    | 114 | 72  | r    |
// | device control 3  | ctrl-S    | 19  | 13  | DC3  | 51  | 33  | 3     | 83  | 53  | S    | 115 | 73  | s    |
// | device control 4  | ctrl-T    | 20  | 14  | DC4  | 52  | 34  | 4     | 84  | 54  | T    | 116 | 74  | t    |
// | neg acknowledge   | ctrl-U    | 21  | 15  | NAK  | 53  | 35  | 5     | 85  | 55  | U    | 117 | 75  | u    |
// | synchronous idel  | ctrl-V    | 22  | 16  | SYN  | 54  | 36  | 6     | 86  | 56  | V    | 118 | 76  | v    |
// | end of xmit block | ctrl-W    | 23  | 17  | ETB  | 55  | 37  | 7     | 87  | 57  | W    | 119 | 77  | w    |
// | cancel            | ctrl-X    | 24  | 18  | CAN  | 56  | 38  | 8     | 88  | 58  | X    | 120 | 78  | x    |
// | end of medium     | ctrl-Y    | 25  | 19  | EM   | 57  | 39  | 9     | 89  | 59  | Y    | 121 | 79  | y    |
// | substitute        | ctrl-Z    | 26  | 1A  | SUB  | 58  | 3A  | :     | 90  | 5A  | Z    | 122 | 7A  | z    |
// | escape            | ctrl-[    | 27  | 1B  | ESC  | 59  | 3B  | ;     | 91  | 5B  | [    | 123 | 7B  | {    |
// | file separator    | ctrl-\\   | 28  | 1C  | FS   | 60  | 3C  | <     | 92  | 5C  | \\   | 124 | 7C  | |    |
// | group separator   | ctrl-]    | 29  | 1D  | GS   | 61  | 3D  | \=    | 93  | 5D  | ]    | 125 | 7D  | }    |
// | record separator  | ctrl-^    | 30  | 1E  | RS   | 62  | 3E  | \>    | 94  | 5E  | ^    | 126 | 7E  | ~    |
// | unit separator    | ctrl-_    | 31  | 1F  | US   | 63  | 3F  | ?     | 95  | 5F  | _    | 127 | 7F  | DEL  |
//
// clang-format on
//


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

static EFI_STATUS KeyboardRegisterKey(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    RegisterKeyboardNotifications();

    while (TRUE) {
        EfiSleep(SEC_TO_100_NS(4));
    }

    return Status;
}

static EFI_STATUS KeyboardPollKey(IN PUEFIINFO_SESSION Session)
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

static UEFIINFO_TEST DutTests[] = {
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

UEFIINFO_TEST_SUITE TextInputTestSuite = {
    .Description = t("Text Input test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

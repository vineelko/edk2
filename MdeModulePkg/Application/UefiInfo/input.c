
#include "common.h"


EFI_INPUT_KEY GetCharNoEcho()
{
    EFI_INPUT_KEY Key;
    UINTN Index = 0;

    gBS->WaitForEvent(1, &gSystemTable->ConIn->WaitForKey, &Index);
    gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &Key);

    return Key;
}

EFI_INPUT_KEY GetChar()
{
    EFI_INPUT_KEY Key;
    UINTN Index = 0;
    CHAR16 OutString[2] = {0};

    gBS->WaitForEvent(1, &gSystemTable->ConIn->WaitForKey, &Index);
    gSystemTable->ConIn->ReadKeyStroke(gSystemTable->ConIn, &Key);

    OutString[0] = Key.UnicodeChar;
    gSystemTable->ConOut->OutputString(gSystemTable->ConOut, OutString);
    return Key;
}

CHAR16* ReadLineNoEcho()
{
    EFI_INPUT_KEY Key;
    CHAR16 InputString[1024];
    CHAR16* RetString = NULL;
    UINTN i = 0;

    ZeroMem(InputString, sizeof(InputString));

    for (i = 0; i < _countof(InputString) - 1; i++) {
        Key = GetCharNoEcho();
        if (Key.UnicodeChar == L'\n') {
            break;
        }

        InputString[i] = Key.UnicodeChar;
    }

    StrCpy(RetString, InputString);

    return RetString;
}

CHAR16* ReadLine()
{
    EFI_INPUT_KEY Key;
    CHAR16 InputString[1024];
    CHAR16* RetString = NULL;
    UINTN i = 0;

    ZeroMem(InputString, sizeof(InputString));

    for (i = 0; i < _countof(InputString) - 1; i++) {
        Key = GetChar();
        if (Key.UnicodeChar == L'\n') {
            break;
        }

        InputString[i] = Key.UnicodeChar;
    }

    RetString = AllocateZeroPool(sizeof(CHAR16) * (i + 1));

    StrCpy(RetString, InputString);

    return RetString;
}

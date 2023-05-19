#include "session.h"

EFI_STATUS
EFIAPI
SessionCreate(IN CHAR16* CommandLine, OUT PUEFIINFO_SESSION* Session)
{
    PUEFIINFO_SESSION RetSession = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Length = 0;

    RetSession = AllocateZeroPool(sizeof(UEFIINFO_SESSION));
    if (RetSession == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", sizeof(UEFIINFO_SESSION));
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    if (StrStr(CommandLine, L"-l") != NULL) {
        RetSession->ListTestCases = TRUE;
    }

    CHAR16* Ptr = StrStr(CommandLine, L"-t");
    if (Ptr != NULL) {
        Ptr += 2;
        while (*Ptr == L' ')
            Ptr++;

        UINTN Len = StrLen(Ptr);
        RetSession->TestCase = AllocateZeroPool((Len + 1) * sizeof(CHAR8));
        for (UINTN i = 0; *Ptr != L',' && *Ptr != L' ' && *Ptr != 0; Ptr++, i++) {
            RetSession->TestCase[i] = (CHAR8)*Ptr;
        }

        RetSession->Arguments = AllocateZeroPool((Len + 1) * sizeof(CHAR8));
        if (*Ptr == L',') {
            Ptr++;
            for (UINTN i = 0; *Ptr != 0; Ptr++, i++) {
                RetSession->Arguments[i] = (CHAR8)*Ptr;
            }
        }
    }

    if (StrStr(CommandLine, L"-h") != NULL) {
        RetSession->ShowHelp = TRUE;
    }

    //
    // Save the command line in session object
    //

    Length = StrLen(CommandLine);
    RetSession->CommandLine = AllocateZeroPool(sizeof(CHAR8) * (Length + 1));
    if (RetSession->CommandLine == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  sizeof(CHAR8) * (Length + 1));
        return EFI_OUT_OF_RESOURCES;
    }

    UnicodeStrToAsciiStrS(CommandLine, RetSession->CommandLine, Length + 1);

    *Session = RetSession;

Exit:
    return Status;
}

EFI_STATUS
EFIAPI
SessionDestroy(IN PUEFIINFO_SESSION Session)
{
    if (Session == NULL) {
        return EFI_SUCCESS;
    }

    FreePool(Session->TestCase);
    FreePool(Session->CommandLine);
    FreePool(Session);

    return EFI_SUCCESS;
}

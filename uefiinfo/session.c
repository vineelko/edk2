/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    session.c

Abstract:

    This module implements a uefiinfo session. A session is defined as set of
    inputs(test suites to execute etc) and set of outputs(test suite results)
    that the uefiinfo module consumes to complete one round of execution.

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "session.h"

EFI_STATUS
EFIAPI
SessionCreate(_In_z_ CHAR16* CommandLine, _Outptr_ PBM_SESSION* Session)
{
    PBM_SESSION RetSession = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Length = 0;

    RetSession = AllocateZeroPool(sizeof(BM_SESSION));
    if (RetSession == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd", sizeof(BM_SESSION));
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
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  sizeof(CHAR8) * (Length + 1));
        return EFI_OUT_OF_RESOURCES;
    }

    UnicodeStrToAsciiStr(CommandLine, RetSession->CommandLine);

    *Session = RetSession;

Exit:
    return Status;
}

EFI_STATUS
EFIAPI
SessionDestroy(_In_ PBM_SESSION Session)
{
    if (Session == NULL) {
        return EFI_SUCCESS;
    }

    FreePool(Session->TestCase);
    FreePool(Session->CommandLine);
    FreePool(Session);

    return EFI_SUCCESS;
}

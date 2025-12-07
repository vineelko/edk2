#ifndef _BMSESSION_H_
#define _BMSESSION_H_

#include "common.h"

typedef struct _BM_SESSION {
    BOOLEAN ListTestCases;
    CHAR8* TestCase;
    CHAR8* CommandLine;
    BOOLEAN ShowHelp;
    CHAR8* Arguments;
} BM_SESSION, *PBM_SESSION;

EFI_STATUS
EFIAPI
SessionCreate(_In_z_ CHAR16* CommandLine, _Outptr_ PBM_SESSION* Session);

EFI_STATUS
EFIAPI
SessionDestroy(_In_ PBM_SESSION Session);

#endif // _BMSESSION_H_

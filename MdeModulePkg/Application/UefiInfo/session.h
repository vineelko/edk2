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
SessionCreate(IN CHAR16* CommandLine, OUT PBM_SESSION* Session);

EFI_STATUS
EFIAPI
SessionDestroy(IN PBM_SESSION Session);

#endif // _BMSESSION_H_

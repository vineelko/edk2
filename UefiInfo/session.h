#ifndef _SESSION_H_
#define _SESSION_H_

#include "common.h"

typedef struct _UEFIINFO_SESSION {
    BOOLEAN ListTestCases;
    CHAR8* TestCase;
    CHAR8* CommandLine;
    BOOLEAN ShowHelp;
    CHAR8* Arguments;
} UEFIINFO_SESSION, *PUEFIINFO_SESSION;

EFI_STATUS
EFIAPI
SessionCreate(IN CHAR16* CommandLine, OUT PUEFIINFO_SESSION* Session);

EFI_STATUS
EFIAPI
SessionDestroy(IN PUEFIINFO_SESSION Session);

#endif // _SESSION_H_

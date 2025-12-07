/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    common.h

Abstract:

    This header includes the minimum set of efi headers needed and the efiflash
    dependencies.

Author:

    Vineel Kovvuri (vineelko) 23-May-2020

Environment:

    UEFI mode only.

--*/

#ifndef _COMMON_H_
#define _COMMON_H_

////////////////////////////////////////////////////////////////////////////////
// THINK TWICE BEFORE ADDING NEW HEADERS HERE. ADD THEM IN THE .C FILES INSTEAD
////////////////////////////////////////////////////////////////////////////////

#include <bootlib.h>

// below copied from cbmrincludes.h
#define t(x) (_Null_terminated_ CHAR8*)(x)
#define T(x) (_Null_terminated_ CHAR16*)(L##x)

//
// efiflash lib dependencies
//

#include "bmerror.h"
#include "edk2compat.h"
#include "debug.h"

#define EFI_END_OF_MEDIA     EFIERR(28)
#define EFI_END_OF_FILE      EFIERR(29)
#define EFI_INVALID_LANGUAGE EFIERR(30)
#define EFI_COMPROMISED_DATA EFIERR(31)
#define EFI_HTTP_ERROR       EFIERR(32)

#if defined(_X86_) || defined(_AMD64_)
#define GetTickCount() (__rdtsc())
#elif defined(_ARM_)
#define GetTickCount() (__rdpmccntr64())
#elif defined(_ARM64_)
#define GetTickCount() ((unsigned __int64)_ReadStatusReg(ARM64_PMCCNTR_EL0))
#else
#error "Architecture not supported"
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

extern EFI_BOOT_SERVICES* gBS;
extern EFI_SYSTEM_TABLE* gSystemTable;
extern EFI_RUNTIME_SERVICES* gRT;
extern EFI_HANDLE* gImageHandle;

#define STRINGIFY(Name) t(#Name)
typedef struct _ENUM_TO_STRING {
    INT Value;
    CHAR8* String;
} ENUM_TO_STRING;

#define UFP_ERROR(UfpStatus) (UfpStatus != UFP_OK && UfpStatus != UFP_EFI_SUCCESS)

//
// Below pragmas temporarily disable the 'declared but not used' type of
// compiler errors
//

// #pragma warning(disable:4100)
// #pragma warning(disable:4101)
// #pragma warning(disable:4189)

#endif // _COMMON_H_

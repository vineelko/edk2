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

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SortLib.h>
#include <Library/PrintLib.h>
#include <Guid/FileSystemInfo.h>
#include <Guid/FileInfo.h>
#include <Guid/FileSystemVolumeLabelInfo.h>
#include <Guid/GlobalVariable.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DebugPort.h>
#include <Protocol/DevicePathUtilities.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/HiiFont.h>
#include <Protocol/Ip4Config2.h>
#include <Protocol/WiFi.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/PartitionInfo.h>
#include <Protocol/Shell.h>
#include <Protocol/Supplicant.h>
#include <Protocol/Smbios.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/BootManagerPolicy.h>
#include <Protocol/Timestamp.h>
#include <Protocol/Dhcp4.h>
#include <IndustryStandard/Dhcp.h>
#include <Protocol/Eap.h>
#include <Protocol/Rng.h>

#define PWSTR CHAR16*
#define UNREFERENCED_PARAMETER(x)
typedef void* PVOID;
typedef int INT;
#define PUINT8 UINT8*

#define _countof(x) ARRAY_SIZE(x)
// #define va_list     VA_LIST
// #define va_start    VA_START
// #define va_end      VA_END

#define ASSERT(x)

#define StrHexToUintn     StrHexToUintnMsExtension
#define StrDecimalToUintn StrDecimalToUintnMsExtension

#define ConvertTextToDevicPath ConvertTextToDevicePath

// #include <bootlib.h>

// below copied from cbmrincludes.h
#define t(x) (CHAR8*)(x)
#define T(x) (CHAR16*)(L##x)

//
// efiflash lib dependencies
//

#include "bmerror.h"
// #include "edk2compat.h"
#include "debug.h"

// #define EFI_END_OF_MEDIA     EFIERR(28)
// #define EFI_END_OF_FILE      EFIERR(29)
// #define EFI_INVALID_LANGUAGE EFIERR(30)
// #define EFI_COMPROMISED_DATA EFIERR(31)
// #define EFI_HTTP_ERROR       EFIERR(32)

// #if defined(_X86_) || defined(_AMD64_)
// #define GetTickCount() (__rdtsc())
// #elif defined(_ARM_)
// #define GetTickCount() (__rdpmccntr64())
// #elif defined(_ARM64_)
// #define GetTickCount() ((unsigned __int64)_ReadStatusReg(ARM64_PMCCNTR_EL0))
// #else
// #error "Architecture not supported"
// #endif

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


//
// Below pragmas temporarily disable the 'declared but not used' type of
// compiler errors
//

// #pragma warning(disable:4100)
// #pragma warning(disable:4101)
// #pragma warning(disable:4189)

#endif // _COMMON_H_

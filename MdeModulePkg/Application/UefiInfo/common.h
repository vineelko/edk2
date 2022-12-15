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
#include <Protocol/Dns4.h>

#define UNREFERENCED_PARAMETER(x)

#define _countof(x) ARRAY_SIZE(x)

#define t(x) (CHAR8*)(x)
#define T(x) (CHAR16*)(L##x)

#include "bmerror.h"
#include "debug.h"

extern EFI_BOOT_SERVICES* gBS;
extern EFI_SYSTEM_TABLE* gSystemTable;
extern EFI_RUNTIME_SERVICES* gRT;
extern EFI_HANDLE* gImageHandle;

#define STRINGIFY(Name) t(#Name)
typedef struct _ENUM_TO_STRING {
    UINTN Value;
    CHAR8* String;
} ENUM_TO_STRING;

#endif // _COMMON_H_

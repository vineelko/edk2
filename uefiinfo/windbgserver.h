/*++

Copyright (c) 2022 Microsoft Corporation

Module Name:

    windbgserver.h

Abstract:

    This module implements WinDBG Server as a UEFI protocol

Author:

    Vineel Kovvuri (vineelko) 07-Jan-2022

Environment:

    UEFI mode only.

--*/

#ifndef _WINDBGSERVER_H_
#define _WINDBGSERVER_H_

#define EFI_MS_WINDBG_SERVER_PROTOCOL_GUID                 \
    {                                                      \
        0xf409a149, 0xc476, 0x4182,                        \
        {                                                  \
            0xbf, 0x06, 0xf4, 0x76, 0xd9, 0xeb, 0xd7, 0x41 \
        }                                                  \
    }

typedef struct _EFI_MS_WINDBG_SERVER_PROTOCOL* PEFI_MS_WINDBG_SERVER_PROTOCOL;

//
// Below API will route the output string to BlBdPrint() i.e., to Windbg console
//

typedef EFI_STATUS(EFIAPI* EFI_MS_WINDBG_SERVER_PRINT)(_In_ PEFI_MS_WINDBG_SERVER_PROTOCOL This,
                                                       _In_ CHAR8* String);

//
// Below API is a helper API which can be called by the application to know the
// base address of the loaded application and its size.
//
// This information can be used to reload the module in Windbg using,
// .reload cbmr_app_debug.efi=f66b1000,45000
//

typedef EFI_STATUS(EFIAPI* EFI_MS_WINDBG_SERVER_DUMP_IMAGE_INFO)(_In_ PEFI_MS_WINDBG_SERVER_PROTOCOL
                                                                     This,
                                                                 _In_ EFI_HANDLE ImageHandle);

typedef struct _EFI_MS_WINDBG_SERVER_PROTOCOL {
    EFI_MS_WINDBG_SERVER_PRINT Print;
    EFI_MS_WINDBG_SERVER_DUMP_IMAGE_INFO DumpImageInfo;

} EFI_MS_WINDBG_SERVER_PROTOCOL, *PEFI_MS_WINDBG_SERVER_PROTOCOL;

extern EFI_GUID gEfiMsWindbgServerProtocolGuid;

#endif
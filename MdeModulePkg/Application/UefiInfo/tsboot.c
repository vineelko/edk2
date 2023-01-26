/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsboot.c

Abstract:

    This module implements boot order enumeration

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

// Global UEFI variables
#define VAR_BOOT_CURRENT L"BootCurrent"
#define VAR_BOOT_NEXT    L"BootNext"
#define VAR_BOOT_ORDER   L"BootOrder"

#define LOAD_OPTION_ACTIVE          0x00000001
#define LOAD_OPTION_FORCE_RECONNECT 0x00000002
#define LOAD_OPTION_HIDDEN          0x00000008
#define LOAD_OPTION_CATEGORY        0x00001F00

#define LOAD_OPTION_CATEGORY_BOOT 0x00000000
#define LOAD_OPTION_CATEGORY_APP  0x00000100

static EFI_STATUS EnumerateBootOrder(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextIf = NULL;
    UINTN BootOrderBufferSize = 0;
    CHAR8* BootOrderBuffer = NULL;

    Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid,
                                 NULL,
                                 (VOID**)&DevicePathToTextIf);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Failed to locate device path to text protocol, 0x%x", Status);
        goto Exit;
    }

    //
    // Get boot order buffer
    //

    Status = gRT->GetVariable(VAR_BOOT_ORDER,
                              &gEfiGlobalVariableGuid,
                              NULL,
                              &BootOrderBufferSize,
                              NULL);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        BootOrderBuffer = AllocateZeroPool(BootOrderBufferSize);
        Status = gRT->GetVariable(VAR_BOOT_ORDER,
                                  &gEfiGlobalVariableGuid,
                                  NULL,
                                  &BootOrderBufferSize,
                                  BootOrderBuffer);
        if (EFI_ERROR(Status)) {
            goto Exit;
        }
    } else if (EFI_ERROR(Status)) {
        DBG_ERROR("Failed to obtain size for BootOrder variable, 0x%x", Status);
        goto Exit;
    }

    for (UINTN i = 0; i < BootOrderBufferSize / sizeof(CHAR16); i++) {
        UINTN BootEntryBufferSize = 0;
        CHAR8* BootEntryBuffer = NULL;
        CHAR16 BootEntryName[10];
        UINT32 Attribute = 0;
        CHAR16* Description = NULL;
        EFI_DEVICE_PATH_PROTOCOL* FilePath = NULL;
        UINT16 FilePathSize = 0;
        UINT8* OptionalData = NULL;
        UINT32 OptionalDataSize = 0;
        UINT8* Ptr = NULL;
        CHAR16* FilePathString = NULL;

        UnicodeSPrint(BootEntryName,
                      sizeof(BootEntryName),
                      L"Boot%04X",
                      ((CHAR16*)BootOrderBuffer)[i]);
        DBG_INFO_U(L"Boot Entry : %s", BootEntryName);

        //
        // Get boot entry
        //

        Status = gRT->GetVariable(BootEntryName,
                                  &gEfiGlobalVariableGuid,
                                  NULL,
                                  &BootEntryBufferSize,
                                  NULL);
        if (Status == EFI_BUFFER_TOO_SMALL) {
            BootEntryBuffer = AllocateZeroPool(BootEntryBufferSize);
            Status = gRT->GetVariable(BootEntryName,
                                      &gEfiGlobalVariableGuid,
                                      NULL,
                                      &BootEntryBufferSize,
                                      BootEntryBuffer);
            if (EFI_ERROR(Status)) {
                FreePool(BootEntryBuffer);
                continue;
            }
        } else if (EFI_ERROR(Status)) {
            DBG_ERROR("Failed to obtain size for Boot entry variable, 0x%x", Status);
            continue;
        }

        //
        // Get the option attribute
        //
        Ptr = BootEntryBuffer;
        Attribute = ReadUnaligned32((UINT32*)Ptr);
        Ptr += sizeof(UINT32);

        //
        // Get the option's device path size
        //
        FilePathSize = ReadUnaligned16((UINT16*)Ptr);
        Ptr += sizeof(UINT16);

        //
        // Get the option's description string
        //
        Description = (CHAR16*)Ptr;

        //
        // Get the option's description string size
        //
        Ptr += StrSize((CHAR16*)Ptr);

        //
        // Get the option's device path
        //
        FilePath = (EFI_DEVICE_PATH_PROTOCOL*)Ptr;
        Ptr += FilePathSize;

        OptionalDataSize = (UINT32)(BootEntryBufferSize - ((UINTN)Ptr - (UINTN)BootEntryBuffer));
        if (OptionalDataSize == 0) {
            OptionalData = NULL;
        } else {
            OptionalData = Ptr;
        }

        DBG_INFO("Attribute : %x", Attribute);
        DBG_INFO_U("Description : %s", Description);
        FilePathString = DevicePathToTextIf->ConvertDevicePathToText(FilePath, FALSE, FALSE);
        DBG_INFO_U(L"FilePath : %s", FilePathString);
        FreePool(FilePathString);
        if (OptionalDataSize != 0) {
            DBG_INFO("OptionalData : ");
            HexDump(OptionalData, OptionalDataSize);
        }

        DBG_INFO("-------------------------------------------------");

        FreePool(BootEntryBuffer);
    }

Exit:
    FreePool(BootOrderBuffer);
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("bootinfo"),
        .Description = t("Boot order info"),
        .DutTestFn = EnumerateBootOrder,
    },
};

BM_TEST_SUITE BootTestSuite = {
    .Description = t("Boot test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

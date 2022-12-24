/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tssystemtable.c

Abstract:

    This module implements Dumping of EFI System Table info

Author:

    Vineel Kovvuri (vineelko) 14-Dec-2022

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

GUID_NAME TableGuidToNameMapping[] = {
    // clang-format off
    {&(EFI_GUID){0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}, "ACPI_10_TABLE"                              },
    {&(EFI_GUID){0x05ad34ba, 0x6f02, 0x4214, {0x95, 0x2e, 0x4d, 0xa0, 0x39, 0x8e, 0x2b, 0xb9}}, "DXE_SERVICES_TABLE"                         },
    {&(EFI_GUID){0x4e28ca50, 0xd582, 0x44ac, {0xa1, 0x1f, 0xe3, 0xd5, 0x65, 0x26, 0xdb, 0x34}}, "EDKII_PI_SMM_COMMUNICATION_REGION_TABLE"    },
    {&(EFI_GUID){0x6b9fd3f7, 0x16df, 0x45e8, {0xbd, 0x39, 0xb9, 0x4a, 0x66, 0x54, 0x1a, 0x5d}}, "EDKII_PI_SMM_MEMORY_ATTRIBUTES_TABLE"       },
    {&(EFI_GUID){0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}}, "EFI_ACPI_20_TABLE"                          },
    {&(EFI_GUID){0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}, "EFI_CC_FINAL_EVENTS_TABLE"                  },
    {&(EFI_GUID){0x49152e77, 0x1ada, 0x4764, {0xb7, 0xa2, 0x7a, 0xfe, 0xfe, 0xd9, 0x5e, 0x8b}}, "EFI_DEBUG_IMAGE_INFO_TABLE"                 },
    {&(EFI_GUID){0xd719b2cb, 0x3d3a, 0x4596, {0xa3, 0xbc, 0xda, 0xd0, 0x0e, 0x67, 0x65, 0x6f}}, "EFI_IMAGE_SECURITY_DATABASE"                },
    {&(EFI_GUID){0x35e7a725, 0x8dd2, 0x4cac, {0x80, 0x11, 0x33, 0xcd, 0xa8, 0x10, 0x90, 0x56}}, "EFI_JSON_CAPSULE_DATA_TABLE"                },
    {&(EFI_GUID){0xdbc461c3, 0xb3de, 0x422a, {0xb9, 0xb4, 0x98, 0x86, 0xfd, 0x49, 0xa1, 0xe5}}, "EFI_JSON_CAPSULE_RESULT_TABLE"              },
    {&(EFI_GUID){0x87367f87, 0x1119, 0x41ce, {0xaa, 0xec, 0x8b, 0xe0, 0x11, 0x1f, 0x55, 0x8a}}, "EFI_JSON_CONFIG_DATA_TABLE"                 },
    {&(EFI_GUID){0x2CA88B53, 0xD296, 0x4080, {0xA4, 0xA5, 0xCA, 0xD9, 0xBA, 0xE2, 0x4B, 0x09}}, "EFI_LOAD_FIXED_ADDRESS_CONFIGURATION_TABLE" },
    {&(EFI_GUID){0xdcfa911d, 0x26eb, 0x469f, {0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20}}, "EFI_MEMORY_ATTRIBUTES_TABLE"                },
    {&(EFI_GUID){0x4c19049f, 0x4137, 0x4dd3, {0x9c, 0x10, 0x8b, 0x97, 0xa8, 0x3f, 0xfd, 0xfa}}, "EFI_MEMORY_TYPE_INFORMATION"                },
    {&(EFI_GUID){0xeb9d2d2f, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}, "EFI_MPS_TABLE"                              },
    {&(EFI_GUID){0xeb66918a, 0x7eef, 0x402a, {0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9}}, "EFI_RT_PROPERTIES_TABLE"                    },
    {&(EFI_GUID){0xb122a263, 0x3661, 0x4f68, {0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80}}, "EFI_SYSTEM_RESOURCE_TABLE"                  },
    {&(EFI_GUID){0x1e2ed096, 0x30e2, 0x4254, {0xbd, 0x89, 0x86, 0x3b, 0xbe, 0xf8, 0x23, 0x25}}, "EFI_TCG2_FINAL_EVENTS_TABLE"                },
    {&(EFI_GUID){0x8cfdb8c8, 0xd6b2, 0x40f3, {0x8e, 0x97, 0x02, 0x30, 0x7c, 0xc9, 0x8b, 0x7c}}, "EFI_VARIABLE_INDEX_TABLE"                   },
    {&(EFI_GUID){0x996ec11c, 0x5397, 0x4e73, {0xb5, 0x8f, 0x82, 0x7e, 0x52, 0x90, 0x6d, 0xef}}, "EFI_VECTOR_HANDOF_TABLE"                    },
    {&(EFI_GUID){0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0}}, "EFI_DTB_TABLE"                              },
    {&(EFI_GUID){0x7739f24c, 0x93d7, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}, "HOB_LIST"                                   },
    {&(EFI_GUID){0xEE4E5898, 0x3914, 0x4259, {0x9D, 0x6E, 0xDC, 0x7B, 0xD7, 0x94, 0x03, 0xCF}}, "LZMA_CUSTOM_DECOMPRESS"                     },
    {&(EFI_GUID){0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94}}, "SMBIOS3_TABLE"                              },
    {&(EFI_GUID){0xeb9d2d31, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}}, "SMBIOS_TABLE"                               },
    {&(EFI_GUID){0xdba6a7e3, 0xbb57, 0x4be7, {0x8A, 0xF8, 0xD5, 0x78, 0xDB, 0x7E, 0x56, 0x87}}, "EFI_TSC_FREQUENCY"                          },
    {&(EFI_GUID){0x36122546, 0xf7e7, 0x4c8f, {0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b}}, "EFI_CONFORMANCE_PROFILES_TABLE"             },
    {NULL, NULL},

    // clang-format on
};

static EFI_STATUS EfiSystemTableDump(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SYSTEM_TABLE* SystemTable = gSystemTable;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    EFI_BLOCK_IO_PROTOCOL* BlockIo = NULL;

    UNREFERENCED_PARAMETER(ProtocolArray);
    UNREFERENCED_PARAMETER(Session);

    DBG_INFO_U(L"FirmwareVendor = %s", SystemTable->FirmwareVendor);
    DBG_INFO("FirmwareRevision = %d", SystemTable->FirmwareRevision);

    for (UINTN i = 0; i < SystemTable->NumberOfTableEntries; i++) {
        EFI_CONFIGURATION_TABLE* ConfigTable = &SystemTable->ConfigurationTable[i];
        GUID_NAME* Entry = FindGuidNameEntry(TableGuidToNameMapping, &ConfigTable->VendorGuid);
        DBG_INFO("%g %a", &ConfigTable->VendorGuid, Entry->Name);
    }

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiBlockIoProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &Handles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed: 0x%x", Status);
        goto Exit;
    }

    DBG_INFO("Handle Count: %d", HandleCount);

    for (UINTN i = 0; i < HandleCount; i++) {
        BlockIo = NULL;
        Status = gBS->HandleProtocol(Handles[i], &gEfiBlockIoProtocolGuid, (void**)&BlockIo);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("HandleProtocol() failed: 0x%x", Status);
            goto Exit;
        }

        EFI_BLOCK_IO_MEDIA* Media = BlockIo->Media;
        DBG_INFO("Handle: %lx Protocol Instance: %lx %llx", Handles[i], BlockIo, *(UINT64*)BlockIo);
        //    DBG_INFO("OFFSET_OF(Media) %d", OFFSET_OF(EFI_BLOCK_IO_PROTOCOL, Revision));

        HexDump(BlockIo, 16);
        DBG_INFO("  Revision: %lx %lx %lx",
                 BlockIo->Revision,
                 &BlockIo->Revision,
                 *(EFI_BLOCK_IO_PROTOCOL*)(&BlockIo->Revision));
        DBG_INFO("  MediaId: %d", Media->MediaId);
        DBG_INFO("  RemovableMedia: %d", Media->RemovableMedia);
        DBG_INFO("  MediaPresent: %d", Media->MediaPresent);
        DBG_INFO("  LogicalPartition: %d", Media->LogicalPartition);
        DBG_INFO("  ReadOnly: %d", Media->ReadOnly);
        DBG_INFO("  WriteCaching: %d", Media->WriteCaching);
        DBG_INFO("  BlockSize: %d", Media->BlockSize);
        DBG_INFO("  IoAlign: %d", Media->IoAlign);
        DBG_INFO("  LastBlock: %d", Media->LastBlock);
        DBG_INFO("  LowestAlignedLba: %d", Media->LowestAlignedLba);
        DBG_INFO("  LogicalBlocksPerPhysicalBlock: %d", Media->LogicalBlocksPerPhysicalBlock);
        DBG_INFO("  Reset : %llx", BlockIo->Reset);
    }

Exit:

    FreePool(Handles);
    return Status;
}

extern GUID_NAME EfiAllGuidNames[];

static CHAR8* ParseGuidInDevicePath(IN CHAR16* DevicePath)
{
    EFI_STATUS Status = EFI_SUCCESS;
    CHAR16* DummyGuid = L"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";

    for (CHAR16* Ptr = DevicePath; *Ptr; Ptr++) {
        BOOLEAN Found = TRUE;
        for (UINTN i = 0; DummyGuid[i] && Ptr[i]; i++) {
            if (DummyGuid[i] == L'X') {
                if (Ptr[i] >= L'A' && Ptr[i] <= L'F' || Ptr[i] >= L'0' && Ptr[i] <= L'9' ||
                    Ptr[i] >= L'a' && Ptr[i] <= L'f') {
                } else {
                    Found = FALSE;
                    break;
                }
            } else if (Ptr[i] != L'-') {
                Found = FALSE;
                break;
            }
        }

        if (Found == TRUE) {
            GUID Guid;
            Status = StrToGuid(Ptr, &Guid);
            if (!EFI_ERROR(Status)) {
                GUID_NAME* Entry = FindGuidNameEntry(EfiAllGuidNames, &Guid);
                return Entry->Name;
            }
        }
    }

    return "";
}

static VOID PrintAttributes(UINTN Attributes)
{
    BOOLEAN Flag = FALSE;
    DBG_INFO_RAW("         Attributes : ");
    if (Attributes & EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL) {
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL");
        Flag = TRUE;
    }
    if (Attributes & EFI_OPEN_PROTOCOL_GET_PROTOCOL) {
        if (Flag == TRUE)
            DBG_INFO_RAW("|");
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_GET_PROTOCOL");
        Flag = TRUE;
    }
    if (Attributes & EFI_OPEN_PROTOCOL_TEST_PROTOCOL) {
        if (Flag == TRUE)
            DBG_INFO_RAW("|");
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_TEST_PROTOCOL");
        Flag = TRUE;
    }
    if (Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
        if (Flag == TRUE)
            DBG_INFO_RAW("|");
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER");
        Flag = TRUE;
    }
    if (Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) {
        if (Flag == TRUE)
            DBG_INFO_RAW("|");
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_BY_DRIVER");
        Flag = TRUE;
    }
    if (Attributes & EFI_OPEN_PROTOCOL_EXCLUSIVE) {
        if (Flag == TRUE)
            DBG_INFO_RAW("|");
        DBG_INFO_RAW("EFI_OPEN_PROTOCOL_EXCLUSIVE");
    }

    DBG_INFO_RAW("\r\n");
}

static EFI_STATUS EfiDumpAllHandles(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    EFI_GUID** ProtocolGuidArray = NULL;
    UINTN ProtocolGuidArrayCount = 0;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY* ProtocolInfoEntries = NULL;
    UINTN ProtocolInfoEntriesCount = 0;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
    CHAR16* DevicePath = NULL;

    UNREFERENCED_PARAMETER(ProtocolArray);
    UNREFERENCED_PARAMETER(Session);

    Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID**)&ToTextPath);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->LocateHandleBuffer(AllHandles, NULL, NULL, &HandleCount, &Handles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed: 0x%x", Status);
        goto Exit;
    }

    DBG_INFO("Handle Count: %d", HandleCount);

    for (UINTN i = 0; i < HandleCount; i++) {
        EFI_LOADED_IMAGE* LoadedImage = NULL;

        ProtocolGuidArray = NULL;
        ProtocolGuidArrayCount = 0;

        DBG_INFO("%3d. Handle : %p", i + 1, Handles[i]);

        Status = gBS->HandleProtocol(Handles[i], &gEfiLoadedImageProtocolGuid, &LoadedImage);
        if (!EFI_ERROR(Status)) {
            DevicePath = ToTextPath->ConvertDevicePathToText(LoadedImage->FilePath, FALSE, FALSE);
            if (DevicePath != NULL) {
                DBG_INFO_U(L"     Path : %s %a", DevicePath, ParseGuidInDevicePath(DevicePath));
                FreePool(DevicePath);
                DevicePath = NULL;
            }
        }

        Status = gBS->ProtocolsPerHandle(Handles[i], &ProtocolGuidArray, &ProtocolGuidArrayCount);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ProtocolsPerHandle() failed: 0x%x", Status);
            goto Exit;
        }
        DBG_INFO("     Protocol Count : %d", ProtocolGuidArrayCount);

        for (UINTN j = 0; j < ProtocolGuidArrayCount; j++) {
            ProtocolInfoEntries = NULL;
            ProtocolInfoEntriesCount = 0;
            GUID_NAME* Entry = FindGuidNameEntry(EfiAllGuidNames, ProtocolGuidArray[j]);

            DBG_INFO("     - Guid : %g %a", ProtocolGuidArray[j], Entry->Name);

            Status = gBS->OpenProtocolInformation(Handles[i],
                                                  ProtocolGuidArray[j],
                                                  &ProtocolInfoEntries,
                                                  &ProtocolInfoEntriesCount);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("OpenProtocolInformation() failed: 0x%x", Status);
                goto Exit;
            }

            DBG_INFO("       Protocol Agent Count : %d", ProtocolInfoEntriesCount);

            for (UINTN k = 0; k < ProtocolInfoEntriesCount; k++) {
                EFI_OPEN_PROTOCOL_INFORMATION_ENTRY* InfoEntry = &ProtocolInfoEntries[k];
                DBG_INFO("       - Agent(Handle) : %p", InfoEntry->AgentHandle);
                DBG_INFO("         Controller(Handle) : %p", InfoEntry->ControllerHandle);
                DBG_INFO("         OpenCount : %d", InfoEntry->OpenCount);
                PrintAttributes(InfoEntry->Attributes);
            }

            FreePool(ProtocolInfoEntries);
            ProtocolInfoEntries = NULL;
        }

        FreePool(ProtocolGuidArray);
        ProtocolGuidArray = NULL;
    }

Exit:

    FreePool(Handles);
    FreePool(ProtocolGuidArray);
    FreePool(ProtocolInfoEntries);
    FreePool(DevicePath);
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("systemtabledump"),
        .Description = t("Dump EFI System table information"),
        .DutTestFn = EfiSystemTableDump,
    },
    {
        .Name = t("dumpallhandles"),
        .Description = t("Dump All handles information"),
        .DutTestFn = EfiDumpAllHandles,
    },
};

BM_TEST_SUITE SystemTableTestSuite = {
    .Description = t("EFI System table information"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

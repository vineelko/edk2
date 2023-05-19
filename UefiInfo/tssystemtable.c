#include "common.h"
#include <stdint.h>

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"
#include "guids.h"

#include <IndustryStandard\Acpi20.h>
#include <Protocol\AcpiSystemDescriptionTable.h>

static EFI_STATUS EfiDumpSystemTable(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SYSTEM_TABLE* SystemTable = gSystemTable;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO_U(L"FirmwareVendor = %s", SystemTable->FirmwareVendor);
    DBG_INFO("FirmwareRevision = %d", SystemTable->FirmwareRevision);

    for (UINTN i = 0; i < SystemTable->NumberOfTableEntries; i++) {
        EFI_CONFIGURATION_TABLE* ConfigTable = &SystemTable->ConfigurationTable[i];
        GUID_NAME* Entry = FindGuidNameEntry(&ConfigTable->VendorGuid);
        DBG_INFO("%g %a", &ConfigTable->VendorGuid, Entry->Name);
    }

    return Status;
}

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
                GUID_NAME* Entry = FindGuidNameEntry(&Guid);
                if (Entry->Name == NULL) {
                    return "<unable to convert guid to name>";
                }

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

static EFI_STATUS EfiDumpAllHandles(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    EFI_GUID** ProtocolGuidArray = NULL;
    UINTN ProtocolGuidArrayCount = 0;
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY* ProtocolInfoEntries = NULL;
    UINTN ProtocolInfoEntriesCount = 0;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
    EFI_DEVICE_PATH_PROTOCOL* DevicePathProto = NULL;
    CHAR16* DevicePath = NULL;

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

        Status = gBS->HandleProtocol(Handles[i], &gEfiDevicePathProtocolGuid, &DevicePathProto);
        if (!EFI_ERROR(Status)) {
            DevicePath = ToTextPath->ConvertDevicePathToText(DevicePathProto, FALSE, FALSE);
            if (DevicePath != NULL) {
                DBG_INFO_U(L"     Device Path : %s %a",
                           DevicePath,
                           ParseGuidInDevicePath(DevicePath));
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
            GUID_NAME* Entry = FindGuidNameEntry(ProtocolGuidArray[j]);

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

#pragma pack(1)
typedef struct {
    EFI_ACPI_SDT_HEADER Header;
    UINT32 Version;
    UINT32 Reserved;
    UINT32 DataType;
    UINT32 DataReserved;
    UINT32 DataLength;
    CHAR8 Data[30];
} EFI_ACPI_MSDM;
#pragma pack()

static EFI_STATUS EfiDumpMSDMTables(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SYSTEM_TABLE* SystemTable = gSystemTable;
    EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER* RSDPointer = NULL;
    EFI_ACPI_SDT_HEADER* XSDTHeader = NULL;
    UINT64* EntryPtr = NULL;
    UINTN NumEntries = 0;
    BOOLEAN Found = FALSE;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO_U(L"FirmwareVendor = %s", SystemTable->FirmwareVendor);
    DBG_INFO("FirmwareRevision = %d", SystemTable->FirmwareRevision);

    for (UINTN i = 0; i < SystemTable->NumberOfTableEntries; i++) {
        EFI_CONFIGURATION_TABLE* ConfigTable = &SystemTable->ConfigurationTable[i];
        if (CompareGuid(&ConfigTable->VendorGuid, &gUefiInfoEfiAcpi20TableGuid) == TRUE) {
            GUID_NAME* Entry = FindGuidNameEntry(&ConfigTable->VendorGuid);
            DBG_INFO("%g %a", &ConfigTable->VendorGuid, Entry->Name);
            if (AsciiStrnCmp("RSD PTR ", ConfigTable->VendorTable, 8) == 0) {
                RSDPointer = ConfigTable->VendorTable;
                break;
            }
        }
    }

    if (RSDPointer == NULL ||
        RSDPointer->Revision < EFI_ACPI_2_0_ROOT_SYSTEM_DESCRIPTION_POINTER_REVISION) {
        goto Exit;
    }

    // From rsdp jump to EXTENDED_SYSTEM_DESCRIPTION_TABLE(xsdt)
    XSDTHeader = (EFI_ACPI_SDT_HEADER*)(uintptr_t)RSDPointer->XsdtAddress;

    if (XSDTHeader->Signature != SIGNATURE_32('X', 'S', 'D', 'T')) {
        goto Exit;
    }

    // Calculate number of entries by skipping the header and divide the
    // remaining length by 64 bit pointer. Since each of this pointer is of type
    // EFI_ACPI_SDT_HEADER
    NumEntries = (XSDTHeader->Length - sizeof(EFI_ACPI_SDT_HEADER)) / sizeof(UINT64);

    EntryPtr = (UINT64*)(XSDTHeader + 1); // Skip header
    for (UINTN i = 0; i < NumEntries; i++) {
        EFI_ACPI_SDT_HEADER* Header = (EFI_ACPI_SDT_HEADER*)(uintptr_t)(EntryPtr[i]);
        if (Header->Signature == SIGNATURE_32('M', 'S', 'D', 'M')) {
            EFI_ACPI_MSDM* MsdmTable = (EFI_ACPI_MSDM*)Header;
            CHAR8 Buffer[128];
            DBG_INFO("Signature         : MSDM");
            DBG_INFO("Length            : %d", MsdmTable->Header.Length);
            DBG_INFO("Revision          : %d", MsdmTable->Header.Revision);
            DBG_INFO("Checksum          : %d", MsdmTable->Header.Checksum);
            AsciiStrnCpyS(Buffer, _countof(Buffer), (CHAR8*)MsdmTable->Header.OemId, 6);
            DBG_INFO("Oem ID            : %a", Buffer);
            AsciiStrnCpyS(Buffer, _countof(Buffer), (CHAR8*)MsdmTable->Header.OemTableId, 8);
            DBG_INFO("Oem Table ID      : %a", Buffer);
            DBG_INFO("Oem Revision      : %d", MsdmTable->Header.OemRevision);
            AsciiStrnCpyS(Buffer, _countof(Buffer), (CHAR8*)&MsdmTable->Header.CreatorId, 4);
            DBG_INFO("Creator ID        : %a", Buffer);
            DBG_INFO("Creator Revision  : %d", MsdmTable->Header.CreatorRevision);
            DBG_INFO("Version           : %d", MsdmTable->Version);
            DBG_INFO("Reserved          : %d", MsdmTable->Reserved);
            DBG_INFO("Data Type         : %d", MsdmTable->DataType);
            DBG_INFO("Data Reserved     : %d", MsdmTable->DataReserved);
            DBG_INFO("Data Length       : %d", MsdmTable->DataLength);
            AsciiStrnCpyS(Buffer, _countof(Buffer), (CHAR8*)MsdmTable->Data, 29);
            DBG_INFO("Product Key       : %a", Buffer);
            Found = TRUE;
            break;
        }
    }

Exit:
    if (Found == FALSE) {
        DBG_INFO("No Microsoft Data Management(MSDM) table found");
    }

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("dumpsystemtables"),
        .Description = t("Dump EFI System table information"),
        .DutTestFn = EfiDumpSystemTable,
    },
    {
        .Name = t("dumpmsdmtable"),
        .Description = t("Dump Microsoft Data Management(MSDM) Table"),
        .DutTestFn = EfiDumpMSDMTables,
    },
    {
        .Name = t("dumpallhandles"),
        .Description = t("Dump All handles information"),
        .DutTestFn = EfiDumpAllHandles,
    },
};

UEFIINFO_TEST_SUITE SystemTableTestSuite = {
    .Description = t("EFI System table information"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

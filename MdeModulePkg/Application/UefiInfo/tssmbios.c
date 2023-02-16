/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tssmbios.c

Abstract:

    This module implements dumping smbios information

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "guids.h"
#include "utils.h"

static UINTN SmbiosStructureLength(IN EFI_SMBIOS_TABLE_HEADER* SmbiosTableHeader)
{
    UINTN TableLength = 0;
    UINT8* Byte = ((UINT8*)SmbiosTableHeader + SmbiosTableHeader->Length);
    while (Byte[TableLength] != 0 || Byte[TableLength + 1] != 0) {
        TableLength++;
    }

    return SmbiosTableHeader->Length + TableLength;
}

static EFI_STATUS SmbiosDumpTables(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SMBIOS_PROTOCOL* SmbiosProtocol = NULL;
    EFI_SMBIOS_TABLE_HEADER* SmbiosTableHeader = NULL;
    UINTN SmbiosTableLength = 0;

    //
    // TODO: Validate the initial handle value on ARM platforms to see if they
    // still deviate from the PI 1.7 Specification(Vol 5). This was the case in
    // Hololens platform
    //

#if defined(_ARM64_)
    EFI_SMBIOS_HANDLE SmbiosHandle = 0;
#else
    EFI_SMBIOS_HANDLE SmbiosHandle = 0xFFFE;
#endif

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SMBIOS_PROTOCOL_GUID Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    SmbiosProtocol = ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX].Protocol;

    DBG_INFO("SMBIOS version %u.%u", SmbiosProtocol->MajorVersion, SmbiosProtocol->MinorVersion);

    while (TRUE) {
        Status = SmbiosProtocol->GetNext(SmbiosProtocol,
                                         &SmbiosHandle,
                                         NULL,
                                         &SmbiosTableHeader,
                                         NULL);
        if (EFI_ERROR(Status)) {
            break;
        }

        if (SmbiosTableHeader->Type != 0)
            continue;

        DBG_INFO("    Type %u present", SmbiosTableHeader->Type);

        //
        // SMBIOS
        // STRUCTS
        // .-----.      _ ______ _______
        // |     |     / | Type |       |
        // |_____|    /  |__1b__|       |
        // |     |   /   |Length|       |L
        // |_____|  /    |__1b__|       |E
        // |     | /     |Handle|       |N
        // |_____|/      |__2b__|       |G
        // |     |       |Format|--.    |T
        // |_____|       |ted Se|--|-.  |H
        // |     |\      |ction |  | |  |
        // .     . \     .______.__|_|__|
        // .     .  \    |String|  | |
        // .     .   \   |Table |<-' |
        // .     .    \  .      .<---'
        // |     |     \_|__\0__|
        // '-----'
        //

        //
        // Hex dump smbios table
        //

        SmbiosTableLength = SmbiosStructureLength(SmbiosTableHeader);
        HexDump(SmbiosTableHeader, SmbiosTableLength);
    }

    //
    // Reached end of all SMBIOS table. So mark the failure as success!
    //

    if (Status == EFI_NOT_FOUND) {
        Status = EFI_SUCCESS;
    }

Exit:

    return Status;
}

static CHAR8* GetStringByIndex(IN CHAR8* StartAddr, IN UINT8 StringIndex)
{
    CHAR8* String = StartAddr;
    UINT8 CurrIndex = 1;
    UINTN StringLength = 0;

    if (StartAddr == NULL) {
        DBG_ERROR("Invalid StartAddr: 0x%p", StartAddr);
        return NULL;
    }

    if (StringIndex == 0) {
        DBG_ERROR("Invalid StringIndex: %u", StringIndex);
        return NULL;
    }

    while (CurrIndex < StringIndex) {
        if (*String == 0 && 0 == *(String + 1)) {
            DBG_ERROR("Structure terminator found while searching index %u", CurrIndex);
            return NULL;
        }

        StringLength = AsciiStrLen(String) + 1;

        String += StringLength;
        CurrIndex++;
    }

    return String;
}

static EFI_STATUS SmbiosDumpType0Table(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SMBIOS_PROTOCOL* SmbiosProtocol = NULL;
    EFI_SMBIOS_TABLE_HEADER* SmbiosTableHeader = NULL;
    UINTN SmbiosTableLength = 0;
    EFI_SMBIOS_TYPE TypeZero = EFI_SMBIOS_TYPE_BIOS_INFORMATION; // 0

    //
    // TODO: Validate the initial handle value on ARM platforms to see if they
    // still deviate from the PI 1.7 Specification(Vol 5). This was the case in
    // Hololens platform
    //

#if defined(_ARM64_)
    EFI_SMBIOS_HANDLE SmbiosHandle = 0;
#else
    EFI_SMBIOS_HANDLE SmbiosHandle = 0xFFFE;
#endif

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SMBIOS_PROTOCOL_GUID Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    SmbiosProtocol = ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX].Protocol;

    DBG_INFO("SMBIOS version %u.%u", SmbiosProtocol->MajorVersion, SmbiosProtocol->MinorVersion);

    // while (TRUE) {
    Status = SmbiosProtocol->GetNext(SmbiosProtocol,
                                     &SmbiosHandle,
                                     &TypeZero,
                                     &SmbiosTableHeader,
                                     NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetNext() failed: %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Type %u present", SmbiosTableHeader->Type);

    //
    // clang-format off
    //
    // SMBIOS
    // STRUCTS
    // .-----.      _ ______ _______
    // |     |     / | Type |       |
    // |_____|    /  |__1b__|       |
    // |     |   /   |Length|       |L
    // |_____|  /    |__1b__|       |E
    // |     | /     |Handle|       |N
    // |_____|/      |__2b__|       |G
    // |     |       |Format|--.    |T
    // |_____|       |ted Se|--|-.  |H
    // |     |\      |ction |  | |  |
    // .     . \     .______.__|_|__|
    // .     .  \    |String|  | |
    // .     .   \   |Table |<-' |
    // .     .    \  .      .<---'
    // |     |     \_|__\0__|
    // '-----'
    //
    // Formatted section contains string index(not offset) in to the string
    // table
    //
    // clang-format on
    //

    SmbiosTableLength = SmbiosStructureLength(SmbiosTableHeader);
    SMBIOS_TABLE_TYPE0* Type0 = (SMBIOS_TABLE_TYPE0*)SmbiosTableHeader;
    VOID* StringSection = ((CHAR8*)SmbiosTableHeader) + SmbiosTableHeader->Length;

    DBG_INFO("Vendor: %a", GetStringByIndex(StringSection, Type0->Vendor));
    DBG_INFO("BiosVersion: %a", GetStringByIndex(StringSection, Type0->BiosVersion));
    DBG_INFO("BiosReleaseDate: %a", GetStringByIndex(StringSection, Type0->BiosReleaseDate));
    DBG_INFO("SystemBiosMajorRelease: %x", Type0->SystemBiosMajorRelease);
    DBG_INFO("SystemBiosMinorRelease: %x", Type0->SystemBiosMinorRelease);
    DBG_INFO("EmbeddedControllerFirmwareMajorRelease: %x",
             Type0->EmbeddedControllerFirmwareMajorRelease);
    DBG_INFO("EmbeddedControllerFirmwareMinorRelease: %x",
             Type0->EmbeddedControllerFirmwareMinorRelease);

Exit:

    return Status;
}

static EFI_STATUS EfiDumpSystemTable(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SYSTEM_TABLE* SystemTable = gSystemTable;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO_U(L"FirmwareVendor = %s", SystemTable->FirmwareVendor);
    DBG_INFO("FirmwareRevision = %d", SystemTable->FirmwareRevision);

    for (UINTN i = 0; i < SystemTable->NumberOfTableEntries; i++) {
        EFI_CONFIGURATION_TABLE* ConfigTable = &SystemTable->ConfigurationTable[i];
        if (CompareGuid(&ConfigTable->VendorGuid, &gUefiInfoEfiSmbiosTableGuid) == TRUE) {
            UINTN SmbiosTableLength = 0;
            EFI_SMBIOS_TABLE_HEADER* SmbiosTableHeader = ConfigTable->VendorTable;
            SmbiosTableLength = SmbiosStructureLength(SmbiosTableHeader);
            HexDump(ConfigTable->VendorTable, SmbiosTableLength);
        }
    }

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("smbiostables"),
        .Description = t("Dump all available SM BIOS tables"),
        .DutTestFn = SmbiosDumpTables,
    },
    {
        .Name = t("smbiostype0table"),
        .Description = t("Dump smbios Type 0 table"),
        .DutTestFn = SmbiosDumpType0Table,
    },
};

BM_TEST_SUITE SmbiosTestSuite = {
    .Description = t("SM BIOS test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

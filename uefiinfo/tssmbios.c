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

#include "utils.h"

static UINTN SmbiosStructureLength(_In_ EFI_SMBIOS_TABLE_HEADER* SmbiosTableHeader)
{
    UINTN TableLength = 0;
    UINT8* Byte = ((UINT8*)SmbiosTableHeader + SmbiosTableHeader->Length);
    while (Byte[TableLength] != 0 || Byte[TableLength + 1] != 0) {
        TableLength++;
    }

    return SmbiosTableHeader->Length + TableLength;
}

static EFI_STATUS SmbiosDumpTables(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
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

    Status = ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SMBIOS_PROTOCOL_GUID Protocol not available : %s(0x%zx)", E(Status), Status);
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

static BM_TEST DutTests[] = {
    {
        .Name = t("smbiostables"),
        .Description = t("Dump all available SM BIOS tables"),
        .DutTestFn = SmbiosDumpTables,
    },
};

BM_TEST_SUITE SmbiosTestSuite = {
    .Description = t("SM BIOS test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

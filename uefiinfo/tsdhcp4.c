/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsdhcp4.c

Abstract:

    This module implements dhcp4 test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "iputils.h"
#include "utils.h"

#define DHCP_OPTION_PARAMETER_REQUEST_LIST 55
#define DHCP_RETRIES                       4

static ENUM_TO_STRING Dhcp4StateMap[] = {
    {Dhcp4Stopped, STRINGIFY(Dhcp4Stopped)},
    {Dhcp4Init, STRINGIFY(Dhcp4Init)},
    {Dhcp4Selecting, STRINGIFY(Dhcp4Selecting)},
    {Dhcp4Requesting, STRINGIFY(Dhcp4Requesting)},
    {Dhcp4Bound, STRINGIFY(Dhcp4Bound)},
    {Dhcp4Renewing, STRINGIFY(Dhcp4Renewing)},
    {Dhcp4Rebinding, STRINGIFY(Dhcp4Rebinding)},
    {Dhcp4InitReboot, STRINGIFY(Dhcp4InitReboot)},
    {Dhcp4Rebooting, STRINGIFY(Dhcp4Rebooting)},
};

static VOID DumpDhcpPacket(EFI_DHCP4_PACKET* Packet)
{
    DBG_INFO("Size: %u", Packet->Size);
    DBG_INFO("Length: %u", Packet->Length);
    DBG_INFO("OpCode: %u", Packet->Dhcp4.Header.OpCode);
    DBG_INFO("HwType: %u", Packet->Dhcp4.Header.HwType);
    DBG_INFO("HwAddrLen: %u", Packet->Dhcp4.Header.HwAddrLen);
    DBG_INFO("Hops: %u", Packet->Dhcp4.Header.Hops);
    DBG_INFO("Xid: %u", Packet->Dhcp4.Header.Xid);
    DBG_INFO("Seconds: %u", Packet->Dhcp4.Header.Seconds);
    DBG_INFO("Reserved: %u", Packet->Dhcp4.Header.Reserved);
    DBG_INFO_RAW("ClientAddr: ");
    DumpIP4Address(&Packet->Dhcp4.Header.ClientAddr);
    DBG_INFO_RAW("YourAddr: ");
    DumpIP4Address(&Packet->Dhcp4.Header.YourAddr);
    DBG_INFO_RAW("ServerAddr: ");
    DumpIP4Address(&Packet->Dhcp4.Header.ServerAddr);
    DBG_INFO_RAW("GatewayAddr: ");
    DumpIP4Address(&Packet->Dhcp4.Header.GatewayAddr);
    //    UINT8            ClientHwAddr[16];
    DBG_INFO("ServerName: %s", Packet->Dhcp4.Header.ServerName);
    DBG_INFO("BootFileName: %s", Packet->Dhcp4.Header.BootFileName);
}

static EFI_STATUS Dhcp4Probe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    BYTE OptionBuffer[sizeof(EFI_DHCP4_PACKET_OPTION) + 1]; // +1 for Data[1]
    EFI_DHCP4_CONFIG_DATA Config = {0};
    EFI_DHCP4_MODE_DATA Mode = {0};
    EFI_DHCP4_PACKET_OPTION** Options = {0};
    EFI_DHCP4_PACKET_OPTION* Option = {0};
    EFI_DHCP4_PROTOCOL* Dhcp4 = NULL;
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 OptionCount = 0;
    UINT32 Timeout[4] = {4, 8, 16, 32};

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_DHCP4_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DHCP4_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Dhcp4 = ProtocolArray[EFI_DHCP4_PROTOCOL_INDEX].Protocol;

    Status = Dhcp4->GetModeData(Dhcp4, &Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    if (Mode.State == Dhcp4Init || Mode.State == Dhcp4InitReboot || Mode.State == Dhcp4Bound) {
        DBG_ERROR("Dhcp mode is already in one of the expected state %s",
                  Dhcp4StateMap[Mode.State].String);
        goto Exit;
    }

    //
    // Option Codes: https://tools.ietf.org/html/rfc2132#section-3
    // DHCP Packet format: https://tools.ietf.org/html/rfc2131#section-2
    //

    Option = (EFI_DHCP4_PACKET_OPTION*)OptionBuffer;
    Option->OpCode = DHCP_OPTION_PARAMETER_REQUEST_LIST;
    Option->Length = 2;
    Option->Data[0] = DHCP_OPTION_SUBNET;
    Option->Data[1] = DHCP_OPTION_ROUTER;

    Config.DiscoverTryCount = DHCP_RETRIES;
    Config.DiscoverTimeout = Timeout;
    Config.OptionCount = 1;
    Config.OptionList = (EFI_DHCP4_PACKET_OPTION**)&Option;

    Status = Dhcp4->Configure(Dhcp4, &Config);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Dhcp4->GetModeData(Dhcp4, &Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    if (Mode.State == Dhcp4Init) {
        Status = Dhcp4->Start(Dhcp4, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetModeData() failed : %s(0x%zx) Possibly no dhcp server",
                      E(Status),
                      Status);
            goto Exit;
        }
    } else {
        DBG_ERROR("Dhcp is not in expected state %s", Dhcp4StateMap[Mode.State].String);
        goto Exit;
    }

    Status = Dhcp4->GetModeData(Dhcp4, &Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("DHCP 4 State: %s", Dhcp4StateMap[Mode.State].String);
    DBG_INFO_RAW("IP 4 Address:");
    DumpIP4Address(&Mode.ClientAddress);
    DBG_INFO_RAW("Mac Address:");
    DumpMacAddress(&Mode.ClientMacAddress);
    DBG_INFO_RAW("Server Address:");
    DumpIP4Address(&Mode.ServerAddress);
    DBG_INFO_RAW("Router Address:");
    DumpIP4Address(&Mode.RouterAddress);
    DBG_INFO_RAW("Subnet Mask:");
    DumpIP4Address(&Mode.SubnetMask);
    DBG_INFO("Lease Time: %u days", SEC_TO_DAYS(Mode.LeaseTime));

    //
    // Dump Options
    //

    // DumpDhcpPacket(Mode.ReplyPacket);
    Status = Dhcp4->Parse(Dhcp4, Mode.ReplyPacket, &OptionCount, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL && EFI_ERROR(Status)) {
        DBG_ERROR("Parse() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Option Count: %u", OptionCount);
    Options = AllocateZeroPool(sizeof(EFI_DHCP4_PACKET_OPTION*) * OptionCount);
    if (Options == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  sizeof(EFI_DHCP4_PACKET_OPTION*) * OptionCount);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = Dhcp4->Parse(Dhcp4, Mode.ReplyPacket, &OptionCount, Options);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Parse() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    for (UINT32 i = 0; i < OptionCount; i++) {
        DBG_INFO("Option %u OpCode %u Length %u", i, Options[i]->OpCode, Options[i]->Length);
    }

    if (Mode.State == Dhcp4Bound && IsNullAddress(&Mode.ClientAddress) == FALSE) {
        Status = EFI_SUCCESS;
    } else {
        Status = EFI_INVALID_PARAMETER; // TODO: Think twice
    }

    //
    // TODO: Validate Build()/TransmitReceive() API
    //

Exit:

    FreePool(Options);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("dhcp4api"),
        .Description = t("DHCP 4 API Test"),
        .DutTestFn = Dhcp4Probe,
    },
};

BM_TEST_SUITE Dhcp4TestSuite = {
    .Description = t("DHCP 4 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

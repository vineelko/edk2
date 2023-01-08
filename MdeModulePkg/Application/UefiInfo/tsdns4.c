/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsdns4.c

Abstract:

    This module implements DNS 4 test suite

Author:

    Vineel Kovvuri (vineelko) 14-Dec-2022

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"
#include "iputils.h"

static EFI_STATUS Dns4Configure(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_DNS4_PROTOCOL* Protocol = NULL;
    EFI_DNS4_MODE_DATA Mode;
    EFI_DNS4_CONFIG_DATA ConfigData;
    EFI_DNS4_CONFIG_DATA* ConfigDataPtr;
    EFI_IPv4_ADDRESS* DnsServerList = NULL;
    UINTN DnsServerListCount = 1;

    EFI_IP4_CONFIG2_PROTOCOL* Ip4Config2 = NULL;
    EFI_IPv4_ADDRESS* DnsInfo = NULL;
    UINTN Size = 0;

    ZeroMem(&Mode, sizeof(Mode));
    ZeroMem(&ConfigData, sizeof(ConfigData));

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_DNS4_PROTOCOL_INDEX]);
    Status = ProtocolArray[EFI_DNS4_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DNS4_PROTOCOL_INDEX Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Protocol = ProtocolArray[EFI_DNS4_PROTOCOL_INDEX].Protocol;

    DnsServerList = AllocateZeroPool(DnsServerListCount * sizeof(EFI_IPv4_ADDRESS));
    DnsServerList[0].Addr[0] = 8;
    DnsServerList[0].Addr[1] = 8;
    DnsServerList[0].Addr[2] = 8;
    DnsServerList[0].Addr[3] = 8;

    ConfigData.DnsServerListCount = DnsServerListCount;
    ConfigData.DnsServerList = DnsServerList;
    ConfigData.UseDefaultSetting = TRUE;
    ConfigData.EnableDnsCache = TRUE;
    ConfigData.Protocol = 0x11; // DNS as validated in DnsProtocol.c in Dns4Dxe

    Status = Protocol->Configure(Protocol, &ConfigData);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Configure() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Status = Protocol->GetModeData(Protocol, &Mode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetModeData() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    ConfigDataPtr = &Mode.DnsConfigData;

    //
    // Dump Config data
    //

    DBG_INFO("Dumping DNS config data");
    DBG_INFO("Dumping DNS Server list");
    for (UINTN i = 0; i < ConfigDataPtr->DnsServerListCount; i++) {
        EFI_IPv4_ADDRESS* IpAddr = &ConfigDataPtr->DnsServerList[i];
        DumpIP4Address(IpAddr);
    }
    DBG_INFO("UseDefaultSetting: %d", ConfigDataPtr->UseDefaultSetting);
    DBG_INFO("EnableDnsCache: %d", ConfigDataPtr->EnableDnsCache);
    DBG_INFO("Protocol: %d", ConfigDataPtr->Protocol);
    DBG_INFO("StationIp:  %d.%d.%d.%d",
             ConfigDataPtr->StationIp.Addr[0],
             ConfigDataPtr->StationIp.Addr[1],
             ConfigDataPtr->StationIp.Addr[2],
             ConfigDataPtr->StationIp.Addr[3]);
    DBG_INFO("SubnetMask:  %d.%d.%d.%d",
             ConfigDataPtr->SubnetMask.Addr[0],
             ConfigDataPtr->SubnetMask.Addr[1],
             ConfigDataPtr->SubnetMask.Addr[2],
             ConfigDataPtr->SubnetMask.Addr[3]);
    DBG_INFO("LocalPort: %d", ConfigDataPtr->LocalPort);
    DBG_INFO("RetryCount: %d", ConfigDataPtr->RetryCount);
    DBG_INFO("RetryInterval: %d", ConfigDataPtr->RetryInterval);

    DBG_INFO("Dumping DNS Server list");
    for (UINTN i = 0; i < Mode.DnsServerCount; i++) {
        EFI_IPv4_ADDRESS* IpAddr = &Mode.DnsServerList[i];
        DumpIP4Address(IpAddr);
    }

    DBG_INFO("Dumping DNS cache entries");
    for (UINTN i = 0; i < Mode.DnsCacheCount; i++) {
        EFI_DNS4_CACHE_ENTRY* Cache = &Mode.DnsCacheList[i];

        DBG_INFO_U(L"Host Name: %s | IP Address: %d.%d.%d.%d | Timeout: %d",
                   Cache->HostName,
                   Cache->IpAddress->Addr[0],
                   Cache->IpAddress->Addr[1],
                   Cache->IpAddress->Addr[2],
                   Cache->IpAddress->Addr[3],
                   Cache->Timeout);
    }

    Status = gBS->LocateProtocol(&gEfiIp4Config2ProtocolGuid, NULL, (VOID**)&Ip4Config2);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateProtocol() failed to locate EFI_RNG_PROTOCOL with status 0x%zx", Status);
        goto Exit;
    }

    //
    // DNS Server List
    //

    DBG_INFO("Info from Ip4Config2");

    Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeDnsServer, &Size, NULL);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        DnsInfo = AllocateZeroPool(Size);
    } else if (EFI_ERROR(Status)) {
        DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : 0x%zx", Status);
        goto Exit;
    }

    Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeDnsServer, &Size, DnsInfo);

    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : 0x%zx", Status);
        goto Exit;
    }

    for (UINTN j = 0; j < Size / sizeof(EFI_IPv4_ADDRESS); j++) {
        EFI_IPv4_ADDRESS* DnsServer = &DnsInfo[j];
        DumpIP4Address(DnsServer);
    }

Exit:
    FreePool(DnsServerList);
    FreePool(DnsInfo);
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("dns4configure"),
        .Description = t("DNS 4 Configure"),
        .DutTestFn = Dns4Configure,
    },
};

BM_TEST_SUITE Dns4TestSuite = {
    .Description = t("DNS 4 test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

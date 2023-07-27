#include "common.h"

#include "protocols.h"
#include "testsuites.h"

EFI_STATUS Ip4DumpNetworkInfo(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    EFI_IP4_CONFIG2_PROTOCOL* Ip4Config2 = NULL;
    EFI_IP4_CONFIG2_INTERFACE_INFO* InterfaceInfo = NULL;
    EFI_IP4_CONFIG2_POLICY Policy = Ip4Config2PolicyDhcp;
    UINTN Size = 0;
    CHAR8 MacString[32 * 2];
    EFI_IPv4_ADDRESS* DnsInfo = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiIp4ServiceBindingProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &Handles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed : 0x%x", Status);
        goto Exit;
    }

    for (UINTN i = 0; i < HandleCount; i++) {
        Status = gBS->HandleProtocol(Handles[i], &gEfiIp4Config2ProtocolGuid, (VOID**)&Ip4Config2);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        Size = 0;
        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeInterfaceInfo, &Size, NULL);
        if (Status == EFI_BUFFER_TOO_SMALL) {
            InterfaceInfo = AllocateZeroPool(Size);
        } else if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeInterfaceInfo failed : 0x%x", Status);
            goto Exit;
        }

        Status = Ip4Config2->GetData(Ip4Config2,
                                     Ip4Config2DataTypeInterfaceInfo,
                                     &Size,
                                     InterfaceInfo);

        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeInterfaceInfo failed : 0x%x", Status);
            goto Exit;
        }

        Size = sizeof(EFI_IP4_CONFIG2_POLICY);
        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypePolicy, &Size, &Policy);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() failed : 0x%x", Status);
            goto Exit;
        }

        DBG_INFO_U(L"Interface Name: %s", InterfaceInfo->Name);
        DBG_INFO("Interface Type: %u(%a)",
                 InterfaceInfo->IfType,
                 InterfaceInfo->IfType == 1 ? "NET_IFTYPE_ETHERNET" : "UNKNOWN");
        DBG_INFO("Policy: %a", Policy == Ip4Config2PolicyStatic ? "Static" : "DHCP");

        AsciiSPrint(MacString,
                    sizeof(MacString),
                    "%02x-%02x-%02x-%02x-%02x-%02x",
                    InterfaceInfo->HwAddress.Addr[0],
                    InterfaceInfo->HwAddress.Addr[1],
                    InterfaceInfo->HwAddress.Addr[2],
                    InterfaceInfo->HwAddress.Addr[3],
                    InterfaceInfo->HwAddress.Addr[4],
                    InterfaceInfo->HwAddress.Addr[5]);

        DBG_INFO("MAC Address: %a", MacString);

        CHAR8 IpAddressString[25];
        AsciiSPrint(IpAddressString,
                      _countof(IpAddressString),
                      (CHAR8*)"%u.%u.%u.%u",
                      InterfaceInfo->StationAddress.Addr[0],
                      InterfaceInfo->StationAddress.Addr[1],
                      InterfaceInfo->StationAddress.Addr[2],
                      InterfaceInfo->StationAddress.Addr[3]);

        DBG_INFO("IP Address: %a", IpAddressString);

        DBG_INFO("Subnet Mask: %u.%u.%u.%u",
                 InterfaceInfo->SubnetMask.Addr[0],
                 InterfaceInfo->SubnetMask.Addr[1],
                 InterfaceInfo->SubnetMask.Addr[2],
                 InterfaceInfo->SubnetMask.Addr[3]);

        DBG_INFO("Routing Table: ");
        for (UINTN j = 0; j < InterfaceInfo->RouteTableSize; j++) {
            EFI_IP4_ROUTE_TABLE* RoutingTable = &InterfaceInfo->RouteTable[j];

            DBG_INFO("    Subnet Address: %u.%u.%u.%u",
                     RoutingTable->SubnetAddress.Addr[0],
                     RoutingTable->SubnetAddress.Addr[1],
                     RoutingTable->SubnetAddress.Addr[2],
                     RoutingTable->SubnetAddress.Addr[3]);

            DBG_INFO("    Subnet Mask: %u.%u.%u.%u",
                     RoutingTable->SubnetMask.Addr[0],
                     RoutingTable->SubnetMask.Addr[1],
                     RoutingTable->SubnetMask.Addr[2],
                     RoutingTable->SubnetMask.Addr[3]);

            DBG_INFO("    Gateway Address: %u.%u.%u.%u",
                     RoutingTable->GatewayAddress.Addr[0],
                     RoutingTable->GatewayAddress.Addr[1],
                     RoutingTable->GatewayAddress.Addr[2],
                     RoutingTable->GatewayAddress.Addr[3]);
            DBG_INFO("----------------------------------");
        }

        CHAR8 GatewayAddressString[25];
        AsciiSPrint(GatewayAddressString, _countof(GatewayAddressString), (CHAR8*)"NA.NA.NA.NA");
        for (UINTN j = 0; j < InterfaceInfo->RouteTableSize; j++) {
            EFI_IP4_ROUTE_TABLE* RoutingTable = &InterfaceInfo->RouteTable[j];
            if (RoutingTable->GatewayAddress.Addr[0] == 0 &&
                RoutingTable->GatewayAddress.Addr[1] == 0 &&
                RoutingTable->GatewayAddress.Addr[2] == 0 &&
                RoutingTable->GatewayAddress.Addr[3] == 0)
                continue;

            AsciiSPrint(GatewayAddressString,
                          _countof(GatewayAddressString),
                          (CHAR8*)"%u.%u.%u.%u",
                          RoutingTable->GatewayAddress.Addr[0],
                          RoutingTable->GatewayAddress.Addr[1],
                          RoutingTable->GatewayAddress.Addr[2],
                          RoutingTable->GatewayAddress.Addr[3]);
            break;
        }

        FreePool(InterfaceInfo);
        InterfaceInfo = NULL;

        //
        // DNS Server List
        //
        Size = 0;
        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeDnsServer, &Size, NULL);
        if (Status == EFI_BUFFER_TOO_SMALL) {
            DnsInfo = AllocateZeroPool(Size);
        } else if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : 0x%x", Status);
            goto Exit;
        }

        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeDnsServer, &Size, DnsInfo);

        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : 0x%x", Status);
            goto Exit;
        }

        CHAR8 DnsServerAddressString[25];
        for (UINTN j = 0; j < Size / sizeof(EFI_IPv4_ADDRESS); j++) {
            EFI_IPv4_ADDRESS* DnsServer = &DnsInfo[j];
            if (DnsServer->Addr[0] == 0 && DnsServer->Addr[1] == 0 && DnsServer->Addr[2] == 0 &&
                DnsServer->Addr[3] == 0)
                continue;

            AsciiSPrint(DnsServerAddressString,
                          _countof(DnsServerAddressString),
                          (CHAR8*)"%u.%u.%u.%u",
                          DnsServer->Addr[0],
                          DnsServer->Addr[1],
                          DnsServer->Addr[2],
                          DnsServer->Addr[3]);

            DBG_INFO("DNS Server: %a", DnsServerAddressString);
            break;
        }
    }

Exit:
    FreePool(Handles);
    FreePool(InterfaceInfo);
    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("ip4dumpnetworkinfo"),
        .Description = t("IP 4 Dump Network Info"),
        .DutTestFn = Ip4DumpNetworkInfo,
    },
};

UEFIINFO_TEST_SUITE Ip4ConfigTestSuite = {
    .Description = t("IP 4 Config test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

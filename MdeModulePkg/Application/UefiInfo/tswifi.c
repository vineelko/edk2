/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tswifi.c

Abstract:

    This module implements wi-fi test suite

Author:

    Vineel Kovvuri (vineelko) 17-Nov-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"
#include "strsafe.h"

#define OUI_IEEE_80211I  0xAC0F00

typedef enum {
  Ieee80211PairwiseCipherSuiteUseGroupCipherSuite = 0,
  Ieee80211PairwiseCipherSuiteWEP40               = 1,
  Ieee80211PairwiseCipherSuiteTKIP                = 2,
  Ieee80211PairwiseCipherSuiteCCMP                = 4,
  Ieee80211PairwiseCipherSuiteWEP104              = 5,
  Ieee80211PairwiseCipherSuiteBIP                 = 6,
  Ieee80211PairwiseCipherSuiteGCMP                = 8,
  Ieee80211PairwiseCipherSuiteGCMP256             = 9,
  // ...
} IEEE_80211_PAIRWISE_CIPHER_SUITE;

#define IEEE_80211_PAIRWISE_CIPHER_SUITE_USE_GROUP  (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteUseGroupCipherSuite << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_WEP40      (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteWEP40 << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_TKIP       (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteTKIP << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_CCMP       (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteCCMP << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_WEP104     (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteWEP104 << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_BIP        (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteBIP << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_GCMP       (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteGCMP << 24))
#define IEEE_80211_PAIRWISE_CIPHER_SUITE_GCMP256    (OUI_IEEE_80211I | (Ieee80211PairwiseCipherSuiteGCMP256 << 24))

typedef enum {
  Ieee80211AkmSuite8021XOrPMKSA       = 1,
  Ieee80211AkmSuitePSK                = 2,
  Ieee80211AkmSuite8021XOrPMKSASHA256 = 5,
  Ieee80211AkmSuitePSKSHA256          = 6,
  Ieee80211AkmSuiteSAE                = 8,
  Ieee80211AkmSuite8021XSuiteB        = 11,
  Ieee80211AkmSuite8021XSuiteB192     = 12,
  Ieee80211AkmSuiteOWE                = 18,
  // ...
} IEEE_80211_AKM_SUITE;

#define IEEE_80211_AKM_SUITE_8021X_OR_PMKSA         (OUI_IEEE_80211I | (Ieee80211AkmSuite8021XOrPMKSA << 24))
#define IEEE_80211_AKM_SUITE_PSK                    (OUI_IEEE_80211I | (Ieee80211AkmSuitePSK << 24))
#define IEEE_80211_AKM_SUITE_8021X_OR_PMKSA_SHA256  (OUI_IEEE_80211I | (Ieee80211AkmSuite8021XOrPMKSASHA256 << 24))
#define IEEE_80211_AKM_SUITE_PSK_SHA256             (OUI_IEEE_80211I | (Ieee80211AkmSuitePSKSHA256 << 24))
#define IEEE_80211_AKM_SUITE_SAE                    (OUI_IEEE_80211I | (Ieee80211AkmSuiteSAE << 24))
#define IEEE_80211_AKM_SUITE_8021X_SUITE_B          (OUI_IEEE_80211I | (Ieee80211AkmSuite8021XSuiteB << 24))
#define IEEE_80211_AKM_SUITE_8021X_SUITE_B192       (OUI_IEEE_80211I | (Ieee80211AkmSuite8021XSuiteB192 << 24))
#define IEEE_80211_AKM_SUITE_OWE                    (OUI_IEEE_80211I | (Ieee80211AkmSuiteOWE << 24))



static EFI_EVENT WaitForNetworkOperation = NULL;

static ENUM_TO_STRING ConnectionStateMap[] = {
    {ConnectSuccess, STRINGIFY(ConnectSuccess)},
    {ConnectRefused, STRINGIFY(ConnectRefused)},
    {ConnectFailed, STRINGIFY(ConnectFailed)},
    {ConnectFailureTimeout, STRINGIFY(ConnectFailureTimeout)},
    {ConnectFailedReasonUnspecified, STRINGIFY(ConnectFailedReasonUnspecified)},
};

static VOID EFIAPI WifiNetworkOperationWaitCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);

    //
    // Wait callbacks are triggered on every tick until the event is signaled.
    // So don't put anything here. Keep them empty!
    //
}

static VOID EFIAPI WifiGetNetworksCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);
    gBS->SignalEvent(WaitForNetworkOperation);
}

static VOID EFIAPI WifiNetworkConnectCallback(IN EFI_EVENT Event, IN VOID* Context)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(Context);
    gBS->SignalEvent(WaitForNetworkOperation);
}

static INTN EFIAPI NetworkDescriptionCompareFunc(IN CONST VOID* NetWorkDescription1,
                                                 IN CONST VOID* NetWorkDescription2)
{
    return ((EFI_80211_NETWORK_DESCRIPTION*)NetWorkDescription2)->NetworkQuality -
           ((EFI_80211_NETWORK_DESCRIPTION*)NetWorkDescription1)->NetworkQuality;
}

static EFI_STATUS WifiNetworkList(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL* ConMgr2Protocol = NULL;
    EFI_80211_GET_NETWORKS_TOKEN GetNetworksToken;
    EFI_80211_GET_NETWORKS_DATA GetData;
    EFI_80211_GET_NETWORKS_RESULT* NetworkList = NULL;
    UINTN Index = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL Protocol not available : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    ConMgr2Protocol = ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX].Protocol;

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              WifiNetworkOperationWaitCallback,
                              NULL,
                              &WaitForNetworkOperation);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              WifiGetNetworksCallback,
                              &GetNetworksToken,
                              &GetNetworksToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to create get network token's event. CreateEvent() failed : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GetNetworksToken.Data = &GetData;

    Status = ConMgr2Protocol->GetNetworks(ConMgr2Protocol, &GetNetworksToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to get network list. GetNetworks() failed : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    //
    // Wait until get networks operations are done
    //

    Status = gBS->WaitForEvent(1, &WaitForNetworkOperation, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    NetworkList = GetNetworksToken.Result;
    if (NetworkList->NumOfNetworkDesc == 0) {
        DBG_INFO("No wireless networks found!");
        goto Exit;
    }

    PerformQuickSort(NetworkList->NetworkDesc,
                     NetworkList->NumOfNetworkDesc,
                     sizeof(EFI_80211_NETWORK_DESCRIPTION),
                     NetworkDescriptionCompareFunc);

    for (UINTN i = 0; i < NetworkList->NumOfNetworkDesc; i++) {
        EFI_80211_NETWORK_DESCRIPTION* NetworkDesc = &NetworkList->NetworkDesc[i];
        EFI_80211_NETWORK* Network = &NetworkDesc->Network;

        if (Network->SSId.SSIdLen == 0)
            continue;

        DBG_INFO("SSID: %-30a Quality:%3d BSS: %d",
                 Network->SSId.SSId,
                 NetworkDesc->NetworkQuality,
                 Network->BSSType); // Basic service sets

        // Dump Authentication and Key Management(AKM) suites
        for (UINTN j = 0; j < Network->AKMSuite->AKMSuiteCount; j++) {
            EFI_80211_SUITE_SELECTOR* Selector = &Network->AKMSuite->AKMSuiteList[j];
            DBG_INFO("    [AKM] OUI: %02X-%02X-%02X Subtype: %02X",
                     Selector->Oui[0],
                     Selector->Oui[1],
                     Selector->Oui[2],
                     Selector->SuiteType);
        }
        // Dump Cipher suites
        for (UINTN j = 0; j < Network->CipherSuite->CipherSuiteCount; j++) {
            EFI_80211_SUITE_SELECTOR* Selector = &Network->CipherSuite->CipherSuiteList[j];
            DBG_INFO("    [Cipher] OUI: %02X-%02X-%02X Subtype: %02X",
                     Selector->Oui[0],
                     Selector->Oui[1],
                     Selector->Oui[2],
                     Selector->SuiteType);
        }
    }

Exit:

    if (GetNetworksToken.Event != NULL) {
        gBS->CloseEvent(GetNetworksToken.Event);
    }

    if (WaitForNetworkOperation != NULL) {
        gBS->CloseEvent(WaitForNetworkOperation);
    }

    if (NetworkList != NULL) {
        FreePool(NetworkList);
    }

    return Status;
}

static EFI_STATUS WifiConnect(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL* ConMgr2Protocol = NULL;
    EFI_80211_GET_NETWORKS_TOKEN GetNetworksToken;
    EFI_80211_CONNECT_NETWORK_TOKEN NetworkConnectToken;
    EFI_80211_GET_NETWORKS_DATA GetData;
    EFI_80211_CONNECT_NETWORK_DATA ConnectData;
    EFI_80211_GET_NETWORKS_RESULT* NetworkList = NULL;
    EFI_80211_NETWORK Network;
    EFI_SUPPLICANT_PROTOCOL* Suplicant = NULL;
    CHAR8 NetworkName[EFI_MAX_SSID_LEN] = "<snipped>";
    CHAR8 Password[] = "<snipped>";
    EFI_80211_SSID Ssid;
    BOOLEAN Found = FALSE;
    UINTN Index = 0;

    UNREFERENCED_PARAMETER(Session);

    if (Session->ShowHelp == TRUE) {
        DBG_INFO("USAGE:");
        DBG_INFO(" uefiinfo.efi -t wificonnect,ssid=riya-2.4,pwd=xxxxx");
        goto Exit;
    }

    Status = ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL Protocol not available : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    ConMgr2Protocol = ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX].Protocol;

    Status = ProtocolArray[EFI_SUPPLICANT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SUPPLICANT_PROTOCOL Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Suplicant = ProtocolArray[EFI_SUPPLICANT_PROTOCOL_INDEX].Protocol;

    Status = gBS->CreateEvent(EVT_NOTIFY_WAIT,
                              TPL_CALLBACK,
                              WifiNetworkOperationWaitCallback,
                              NULL,
                              &WaitForNetworkOperation);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              WifiGetNetworksCallback,
                              &GetNetworksToken,
                              &GetNetworksToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to create get network token's event. CreateEvent() failed : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GetNetworksToken.Data = &GetData;

    Status = ConMgr2Protocol->GetNetworks(ConMgr2Protocol, &GetNetworksToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to get network list. GetNetworks() failed : %a(0x%x)",
                  E(Status),
                  Status);
        goto Exit;
    }

    //
    // Wait until get networks operations are done
    //

    Status = gBS->WaitForEvent(1, &WaitForNetworkOperation, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    NetworkList = GetNetworksToken.Result;
    if (NetworkList->NumOfNetworkDesc == 0) {
        Status = EFI_NOT_FOUND;
        DBG_ERROR("No wireless networks found!");
        goto Exit;
    }

    PerformQuickSort(NetworkList->NetworkDesc,
                     NetworkList->NumOfNetworkDesc,
                     sizeof(EFI_80211_NETWORK_DESCRIPTION),
                     NetworkDescriptionCompareFunc);

    //
    // Find the network with the SSidName
    //

    UINTN SsidNameLength = AsciiStrLen(NetworkName);
    for (UINTN i = 0; i < NetworkList->NumOfNetworkDesc; i++) {
        EFI_80211_NETWORK_DESCRIPTION* NetworkDesc = &NetworkList->NetworkDesc[i];

        if (NetworkDesc->Network.SSId.SSIdLen == 0)
            continue;

        if (NetworkDesc->Network.SSId.SSIdLen != SsidNameLength)
            continue;

        if (CompareMem(NetworkDesc->Network.SSId.SSId,
                       NetworkName,
                       NetworkDesc->Network.SSId.SSIdLen) == 0) {
            CopyMem(&Network, &NetworkDesc->Network, sizeof(EFI_80211_NETWORK));
            Found = TRUE;
            break;
        }
    }

    //
    // Bailout if we could not find the network object with NetworkName
    //
    if (Found == FALSE) {
        Status = EFI_NOT_FOUND;
        DBG_ERROR("Wireless network with %a not found", NetworkName);
        goto Exit;
    }

    //
    // Prepare the Suplicant with SSid and Password
    //

    Ssid.SSIdLen = (UINT8)AsciiStrLen(NetworkName);
    CopyMem(Ssid.SSId, NetworkName, sizeof(Ssid.SSId));
    Status = Suplicant->SetData(Suplicant,
                                EfiSupplicant80211TargetSSIDName,
                                &Ssid,
                                sizeof(EFI_80211_SSID));
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Suplicant SetData for Ssid failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = Suplicant->SetData(Suplicant,
                                EfiSupplicant80211PskPassword,
                                Password,
                                AsciiStrLen(Password) + 1);
    ZeroMem(Password, AsciiStrLen(Password));
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Suplicant SetData for Password failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = gBS->CreateEvent(EVT_NOTIFY_SIGNAL,
                              TPL_CALLBACK,
                              WifiNetworkConnectCallback,
                              &NetworkConnectToken,
                              &NetworkConnectToken.Event);
    if (EFI_ERROR(Status)) {
        DBG_ERROR(
            "Unable to create network connect token's event. CreateEvent() failed : %a(0x%x)",
            E(Status),
            Status);
        goto Exit;
    }

    //
    // Dump Network object fields
    //

    DBG_INFO("SSID: %-30a BSS: %d", Network.SSId.SSId,
             Network.BSSType); // Basic service sets

    // Dump Authentication and Key Management(AKM) suites
    for (UINTN j = 0; j < Network.AKMSuite->AKMSuiteCount; j++) {
        EFI_80211_SUITE_SELECTOR* Selector = &Network.AKMSuite->AKMSuiteList[j];
        DBG_INFO("    [AKM] OUI: %02X-%02X-%02X Subtype: %02X",
                 Selector->Oui[0],
                 Selector->Oui[1],
                 Selector->Oui[2],
                 Selector->SuiteType);
        if (((*(UINT32*)Selector->Oui) | Selector->SuiteType << 24) == IEEE_80211_AKM_SUITE_PSK) {
            DBG_INFO("        [AKM] IEEE_80211_AKM_SUITE_PSK");
        }
    }

    // Dump Cipher suites
    for (UINTN j = 0; j < Network.CipherSuite->CipherSuiteCount; j++) {
        EFI_80211_SUITE_SELECTOR* Selector = &Network.CipherSuite->CipherSuiteList[j];
        DBG_INFO("    [Cipher] OUI: %02X-%02X-%02X Subtype: %02X",
                 Selector->Oui[0],
                 Selector->Oui[1],
                 Selector->Oui[2],
                 Selector->SuiteType);
        if (((*(UINT32*)Selector->Oui) | Selector->SuiteType << 24) ==
            IEEE_80211_PAIRWISE_CIPHER_SUITE_CCMP) {
            DBG_INFO("        [Cipher] IEEE_80211_PAIRWISE_CIPHER_SUITE_CCMP");
        }
    }

    //
    // Assign Network object to Connect Token
    //
    ConnectData.Network = &Network;
    ConnectData.FailureTimeout = 20; // 20 Sec
    NetworkConnectToken.Data = &ConnectData;
    DBG_INFO("Network name: %a", Network.SSId.SSId);

    //
    // Connect to the Network
    //
    Status = ConMgr2Protocol->ConnectNetwork(ConMgr2Protocol, &NetworkConnectToken);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ConnectNetwork() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    //
    // Wait until ConnectNetwork operations are done
    //

    Status = gBS->WaitForEvent(1, &WaitForNetworkOperation, &Index);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("WaitForEvent() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("NetworkConnectToken.Status = %a(0x%x)",
             E(NetworkConnectToken.Status),
             NetworkConnectToken.Status);

    DBG_INFO("Connection Status : %a(0x%x)",
             ConnectionStateMap[NetworkConnectToken.ResultCode].String,
             ConnectionStateMap[NetworkConnectToken.ResultCode].Value);

Exit:

    if (GetNetworksToken.Event != NULL) {
        gBS->CloseEvent(GetNetworksToken.Event);
    }

    if (NetworkConnectToken.Event != NULL) {
        gBS->CloseEvent(NetworkConnectToken.Event);
    }

    if (WaitForNetworkOperation != NULL) {
        gBS->CloseEvent(WaitForNetworkOperation);
    }

    if (NetworkList != NULL) {
        FreePool(NetworkList);
    }

    return Status;
}

static EFI_STATUS WifiIpInfoDump(IN PBM_PROTOCOL_INFO ProtocolArray, IN PBM_SESSION Session)
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

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->LocateHandleBuffer(ByProtocol,
                                     &gEfiIp4ServiceBindingProtocolGuid,
                                     NULL,
                                     &HandleCount,
                                     &Handles);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateHandleBuffer() failed : %a(0x%x)", E(Status), Status);
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
            DBG_ERROR("GetData() Ip4Config2DataTypeInterfaceInfo failed : %a(0x%x)",
                      E(Status),
                      Status);
            goto Exit;
        }

        Status = Ip4Config2->GetData(Ip4Config2,
                                     Ip4Config2DataTypeInterfaceInfo,
                                     &Size,
                                     InterfaceInfo);

        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeInterfaceInfo failed : %a(0x%x)",
                      E(Status),
                      Status);
            goto Exit;
        }

        Size = sizeof(EFI_IP4_CONFIG2_POLICY);
        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypePolicy, &Size, &Policy);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() failed : %a(0x%x)", E(Status), Status);
            goto Exit;
        }

        DBG_INFO_U(L"Interface Name: %a", InterfaceInfo->Name);
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
        DBG_INFO("IP Address: %u.%u.%u.%u",
                 InterfaceInfo->StationAddress.Addr[0],
                 InterfaceInfo->StationAddress.Addr[1],
                 InterfaceInfo->StationAddress.Addr[2],
                 InterfaceInfo->StationAddress.Addr[3]);
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
            DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : %a(0x%x)",
                      E(Status),
                      Status);
            goto Exit;
        }

        Status = Ip4Config2->GetData(Ip4Config2, Ip4Config2DataTypeDnsServer, &Size, DnsInfo);

        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetData() Ip4Config2DataTypeDnsServer failed : %a(0x%x)",
                      E(Status),
                      Status);
            goto Exit;
        }

        for (UINTN j = 0; j < Size / sizeof(EFI_IPv4_ADDRESS); j++) {
            EFI_IPv4_ADDRESS* DnsServer = &DnsInfo[j];
            DBG_INFO("DNS Server: %u.%u.%u.%u",
                     DnsServer->Addr[0],
                     DnsServer->Addr[1],
                     DnsServer->Addr[2],
                     DnsServer->Addr[3]);
        }
    }

Exit:

    FreePool(Handles);
    FreePool(InterfaceInfo);
    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("wifilist"),
        .Description = t("List all available Wi-Fi networks"),
        .DutTestFn = WifiNetworkList,
    },
    {
        .Name = t("wificonnect"),
        .Description = t("Connect to Wi-Fi network"),
        .DutTestFn = WifiConnect,
    },
    {
        .Name = t("wifiipinfodump"),
        .Description = t("Dump Connected Wi-Fi network IP info"),
        .DutTestFn = WifiIpInfoDump,
    },
};

BM_TEST_SUITE WifiTestSuite = {
    .Description = t("Wi-Fi test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

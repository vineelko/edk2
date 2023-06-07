//
// Global includes
//
#include "common.h"

//
// Local includes
//
#include "network_common.h"

//
// Constants/Macros
//

//
// Structs
//

//
// Variables
//

static EFI_BOOT_MANAGER_POLICY_PROTOCOL* gsBootMgrPolicy = NULL;
EFI_GUID gEfiMsNetworkDelayProtocolGuid = {0xff7d36aa,
                                           0x96a5,
                                           0x46c4,
                                           0xb1,
                                           0x66,
                                           0xfe,
                                           0x18,
                                           0xd2,
                                           0x93,
                                           0x26,
                                           0x06}; // EFI_MS_NETWORK_DELAY_PROTOCOL_GUID

//
// Prototypes
//

//
// Local functions
//

//
// Interfaces
//
EFI_STATUS EFIAPI NetworkCommonInitStack()
{
    EFI_STATUS Status;
    VOID* Interface;
    EFI_HANDLE Handle = NULL;

    Status = gBS->LocateProtocol(&gEfiMsNetworkDelayProtocolGuid, NULL, &Interface);
    if (Status == EFI_NOT_FOUND) {
        Status = gBS->InstallProtocolInterface(&Handle,
                                               &gEfiMsNetworkDelayProtocolGuid,
                                               EFI_NATIVE_INTERFACE,
                                               NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("NetworkCommonInitStack: Unable to install of gsMsNetworkDelayProtocol 0x%x",
                      Status);
            goto Exit;
        }

    } else if (EFI_ERROR(Status)) {
        DBG_ERROR(
            "NetworkCommonInitStack: Unable to locate gsMsNetworkDelayProtocol with status 0x%x",
            Status);
        goto Exit;
    }

    // Connect all UEFI devices
    Status = gBS->LocateProtocol(&gEfiBootManagerPolicyProtocolGuid,
                                 NULL,
                                 (VOID**)&gsBootMgrPolicy);
    if (EFI_ERROR(Status)) {
        Status = EFI_SUCCESS;
    } else {
        Status = gsBootMgrPolicy->ConnectDeviceClass(gsBootMgrPolicy,
                                                     &gEfiBootManagerPolicyConnectAllGuid);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
        }
    }

Exit:
    return Status;
}

BOOLEAN
EFIAPI
NetworkCommonIsEthernetMediaAttached(IN EFI_HANDLE ServiceHandle)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SIMPLE_NETWORK* Snp = NULL;
    UINT32 InterruptStatus = 0;

    //
    // Try to open SNP from ServiceHandle
    //

    Status = gBS->HandleProtocol(ServiceHandle, &gEfiSimpleNetworkProtocolGuid, (VOID**)&Snp);
    if (EFI_ERROR(Status)) {
        return FALSE;
    }

    //
    // Invoke Snp->GetStatus() to refresh MediaPresent field in SNP mode data
    //

    Status = Snp->GetStatus(Snp, &InterruptStatus, NULL);
    if (EFI_ERROR(Status)) {
        return FALSE;
    }

    return Snp->Mode->MediaPresent;
}

BOOLEAN EFIAPI NetworkCommonIsEthernetHandle(IN EFI_HANDLE DeviceHandle)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GUID** ProtocolBuffer = NULL;
    UINTN ProtocolBufferCount = 0;

    //
    // Query all protocols supported on the handle
    //

    Status = gBS->ProtocolsPerHandle(DeviceHandle, &ProtocolBuffer, &ProtocolBufferCount);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ProtocolsPerHandle failed, 0x%x", Status);
        goto Exit;
    }

    //
    // Filter out this device handle if it has Wi-Fi protocols on it. As
    // it cannot have a proper ip address assigned from DHCP server and
    // hence not usable for tcp/ip ufp network transport
    //

    BOOLEAN FoundEthernetNicHandle = TRUE;
    for (UINTN j = 0; j < ProtocolBufferCount; j++) {
        if (CompareGuid((EFI_GUID*)ProtocolBuffer[j], &gEfiEapProtocolGuid) == TRUE ||
            CompareGuid((EFI_GUID*)ProtocolBuffer[j], &gEfiWiFiProtocolGuid) == TRUE ||
            CompareGuid((EFI_GUID*)ProtocolBuffer[j], &gEfiWiFi2ProtocolGuid) == TRUE) {
            FoundEthernetNicHandle = FALSE;
            break;
        }
    }

    for (UINTN j = 0; j < ProtocolBufferCount; j++) {
        FreePool(ProtocolBuffer[j]);
    }

    FreePool(ProtocolBuffer);

    return FoundEthernetNicHandle == TRUE;

Exit:
    return FALSE;
}

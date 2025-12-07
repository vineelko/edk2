/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    protocolhelpers.c

Abstract:

    This module implements protocol handling routines

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"
#include "protocols.h"
#include "utils.h"
#include "network_common.h"
#include "efiusbinitprotocol.h"

//
// List of all UEFI protocols probed for their existence on the current
// platform. As per UEFI Spec 2.8
//

BM_PROTOCOL_INFO ProtocolArray[EFI_MAX_PROTOCOL_INDEX] = {
    // clang-format off
    //
    // BOOT MANAGER PROTOCOLS - Chapter 3
    //

    [EFI_BOOT_MANAGER_POLICY_PROTOCOL_INDEX] = PROTO(&gEfiBootManagerPolicyProtocolGuid, t("EFI_BOOT_MANAGER_POLICY_PROTOCOL")),

    //
    // BOOT SERVICES - Chapter 7
    //

    // [EFI_BOOT_SERVICES_PROTOCOL_INDEX] ==

    //
    // LOADED IMAGE PROTOCOL - Chapter 9
    //

    [EFI_LOADED_IMAGE_PROTOCOL_INDEX] = PROTO(&gEfiLoadedImageProtocolGuid, t("EFI_LOADED_IMAGE_PROTOCOL")),
    [EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL_INDEX] = PROTO(&gEfiLoadedImageDevicePathProtocolGuid, t("EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL")),

    //
    // PROTOCOLS - DEVICE PATH - Chapter 10
    //

    [EFI_DEVICE_PATH_PROTOCOL_INDEX] = PROTO(&gEfiDevicePathProtocolGuid, t("EFI_DEVICE_PATH_PROTOCOL")),
    [EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_INDEX] = PROTO(&gEfiDevicePathToTextProtocolGuid, t("EFI_DEVICE_PATH_TO_TEXT_PROTOCOL")),
    [EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_INDEX] = PROTO(&gEfiDevicePathFromTextProtocolGuid, t("EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL")),
    [EFI_DEVICE_PATH_UTILITIES_PROTOCOL_INDEX] = PROTO(&gEfiDevicePathUtilitiesProtocolGuid, t("EFI_DEVICE_PATH_UTILITIES_PROTOCOL")),

    //
    // PROTOCOLS - DRIVER BINDING - Chapter 11
    //

    [EFI_DRIVER_BINDING_PROTOCOL_INDEX] = PROTO(&gEfiDriverBindingProtocolGuid, t("EFI_DRIVER_BINDING_PROTOCOL")),
    [EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL_INDEX] = PROTO(&gEfiPlatformDriverOverrideProtocolGuid, t("EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL")),
    [EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL_INDEX] = PROTO(&gEfiBusSpecificDriverOverrideProtocolGuid, t("EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL")),
    [EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_INDEX] = PROTO(&gEfiDriverDiagnostics2ProtocolGuid, t("EFI_DRIVER_DIAGNOSTICS2_PROTOCOL")),
    [EFI_COMPONENT_NAME2_PROTOCOL_INDEX] = PROTO(&gEfiComponentName2ProtocolGuid, t("EFI_COMPONENT_NAME2_PROTOCOL")),
    [EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL_INDEX] = PROTO(&gEfiPlatformToDriverConfigurationProtocolGuid, t("EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL")),
    [EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL_INDEX] = PROTO(&gEfiDriverSupportedEfiVersionProtocolGuid, t("EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL")),
    [EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL_INDEX] = PROTO(&gEfiDriverFamilyOverrideProtocolGuid, t("EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL")),
    [EFI_DRIVER_HEALTH_PROTOCOL_INDEX] = PROTO(&gEfiDriverHealthProtocolGuid, t("EFI_DRIVER_HEALTH_PROTOCOL")),
    [EFI_ADAPTER_INFORMATION_PROTOCOL_INDEX] = PROTO(&gEfiAdapterInformationProtocolGuid, t("EFI_ADAPTER_INFORMATION_PROTOCOL")),

    //
    // PROTOCOLS - CONSOLE - Chapter 12
    //

    [EFI_SIMPLE_TEXT_INPUT_PROTOCOL_INDEX] = PROTO(&gEfiSimpleTextInputProtocolGuid, t("EFI_SIMPLE_TEXT_INPUT_PROTOCOL")),
    [EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX] = PROTO(&gEfiSimpleTextInputExProtocolGuid, t("EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL")),
    [EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_INDEX] = PROTO(&gEfiSimpleTextOutputProtocolGuid, t("EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL")),
    [EFI_SIMPLE_POINTER_PROTOCOL_INDEX] = PROTO(&gEfiSimplePointerProtocolGuid, t("EFI_SIMPLE_POINTER_PROTOCOL")),
    [EFI_ABSOLUTE_POINTER_PROTOCOL_INDEX] = PROTO(&gEfiAbsolutePointerProtocolGuid, t("EFI_ABSOLUTE_POINTER_PROTOCOL")),
    [EFI_SERIAL_IO_PROTOCOL_INDEX] = PROTO(&gEfiSerialIoProtocolGuid, t("EFI_SERIAL_IO_PROTOCOL")),
    [EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX] = PROTO(&gEfiGraphicsOutputProtocolGuid, t("EFI_GRAPHICS_OUTPUT_PROTOCOL")),

    //
    // PROTOCOLS - MEDIA ACCESS - Chapter 13
    //

    [EFI_LOAD_FILE_PROTOCOL_INDEX] = PROTO(&gEfiLoadFileProtocolGuid, t("EFI_LOAD_FILE_PROTOCOL")),
    [EFI_LOAD_FILE2_PROTOCOL_INDEX] = PROTO(&gEfiLoadFile2ProtocolGuid, t("EFI_LOAD_FILE2_PROTOCOL")),
    [EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_INDEX] = PROTO(&gEfiSimpleFileSystemProtocolGuid, t("EFI_SIMPLE_FILE_SYSTEM_PROTOCOL")),
    [EFI_FILE_INFO_ID_PROTOCOL_INDEX] = PROTO(&gEfiFileInfoIdGuid, t("EFI_FILE_INFO_ID")), [EFI_TAPE_IO_PROTOCOL_INDEX] = PROTO(&gEfiTapeIoProtocolGuid, t("EFI_TAPE_IO_PROTOCOL")),
    [EFI_DISK_IO_PROTOCOL_INDEX] = PROTO(&gEfiDiskIoProtocolGuid, t("EFI_DISK_IO_PROTOCOL")), [EFI_DISK_IO2_PROTOCOL_INDEX] = PROTO(&gEfiDiskIo2ProtocolGuid, t("EFI_DISK_IO2_PROTOCOL")),
    [EFI_BLOCK_IO_PROTOCOL_INDEX] = PROTO(&gEfiBlockIoProtocolGuid, t("EFI_BLOCK_IO_PROTOCOL")), [EFI_BLOCK_IO2_PROTOCOL_INDEX] = PROTO(&gEfiBlockIo2ProtocolGuid, t("EFI_BLOCK_IO2_PROTOCOL")),
    [EFI_BLOCK_IO_CRYPTO_PROTOCOL_INDEX] = PROTO(&gEfiBlockIoCryptoProtocolGuid, t("EFI_BLOCK_IO_CRYPTO_PROTOCOL")),
    [EFI_ERASE_BLOCK_PROTOCOL_INDEX] = PROTO(&gEfiEraseBlockProtocolGuid, t("EFI_ERASE_BLOCK_PROTOCOL")),
    [EFI_ATA_PASS_THRU_PROTOCOL_INDEX] = PROTO(&gEfiAtaPassThruProtocolGuid, t("EFI_ATA_PASS_THRU_PROTOCOL")),
    [EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_INDEX] = PROTO(&gEfiStorageSecurityCommandProtocolGuid, t("EFI_STORAGE_SECURITY_COMMAND_PROTOCOL")),
    [EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_INDEX] = PROTO(&gEfiNvmExpressPassThruProtocolGuid, t("EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL")),
    [EFI_SD_MMC_PASS_THRU_PROTOCOL_INDEX] = PROTO(&gEfiSdMmcPassThruProtocolGuid,t("EFI_SD_MMC_PASS_THRU_PROTOCOL")),
    [EFI_RAM_DISK_PROTOCOL_INDEX] = PROTO(&gEfiRamDiskProtocolGuid, t("EFI_RAM_DISK_PROTOCOL")),
    [EFI_PARTITION_INFO_PROTOCOL_INDEX] = PROTO(&gEfiPartitionInfoProtocolGuid, t("EFI_PARTITION_INFO_PROTOCOL")),
    [EFI_NVDIMM_LABEL_PROTOCOL_INDEX] = PROTO(&gEfiNvdimmLabelProtocolGuid, t("EFI_NVDIMM_LABEL_PROTOCOL")),
    [EFI_UFS_DEVICE_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiUfsDeviceConfigProtocolGuid, t("EFI_UFS_DEVICE_CONFIG_PROTOCOL")),

    //
    // PROTOCOLS - PCI BUS - Chapter 14
    //

    [EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_INDEX] = PROTO(&gEfiPciRootBridgeIoProtocolGuid, t("EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL")),
    [EFI_PCI_IO_PROTOCOL_INDEX] = PROTO(&gEfiPciIoProtocolGuid, t("EFI_PCI_IO_PROTOCOL")),

    //
    // PROTOCOLS - SCSI Driver - Chapter 15
    //

    [EFI_SCSI_IO_PROTOCOL_INDEX] = PROTO(&gEfiScsiIoProtocolGuid, t("EFI_SCSI_IO_PROTOCOL")),
    [EFI_EXT_SCSI_PASS_THRU_PROTOCOL_INDEX] = PROTO(&gEfiExtScsiPassThruProtocolGuid, t("EFI_EXT_SCSI_PASS_THRU_PROTOCOL")),

    //
    // PROTOCOLS - iSCSI Driver - Chapter 16
    //

    [EFI_ISCSI_INITIATOR_NAME_PROTOCOL_INDEX] = PROTO(&gEfiIscsiInitiatorNameProtocolGuid, t("EFI_ISCSI_INITIATOR_NAME_PROTOCOL")),

    //
    // PROTOCOLS - USB - Chapter 17
    //

    [EFI_USB2_HC_PROTOCOL_INDEX] = PROTO(&gEfiUsb2HcProtocolGuid, t("EFI_USB2_HC_PROTOCOL")),
    [EFI_USB_IO_PROTOCOL_INDEX] = PROTO(&gEfiUsbIoProtocolGuid, t("EFI_USB_IO_PROTOCOL")),
    [EFI_USBFN_IO_PROTOCOL_INDEX] = PROTO(&gEfiUsbfnIoProtocolGuid, t("EFI_USBFN_IO_PROTOCOL")),
    [EFI_USB_INIT_PROTOCOL_INDEX] = PROTO(&gEfiUsbInitProtocolGuid, t("EFI_USB_INIT_PROTOCOL")),

    //
    // PROTOCOLS - DEBUGGER - Chapter 18
    //

    [EFI_DEBUGPORT_PROTOCOL_INDEX] = PROTO(&gEfiDebugPortProtocolGuid, t("EFI_DEBUGPORT_PROTOCOL")),
    [EFI_DEBUG_SUPPORT_PROTOCOL_INDEX] = PROTO(&gEfiDebugSupportProtocolGuid, t("EFI_DEBUG_SUPPORT_PROTOCOL")),

    //
    // PROTOCOLS - COMPRESSION - Chapter 19
    //

    [EFI_DECOMPRESS_PROTOCOL_INDEX] = PROTO(&gEfiDecompressProtocolGuid, t("EFI_DECOMPRESS_PROTOCOL")),

    //
    // PROTOCOLS - ACPI - Chapter 20
    //

    [EFI_ACPI_TABLE_PROTOCOL_INDEX] = PROTO(&gEfiAcpiTableProtocolGuid, t("EFI_ACPI_TABLE_PROTOCOL")),

    //
    // PROTOCOLS - STRING SERVICES - Chapter 21
    //

    [EFI_UNICODE_COLLATION_PROTOCOL_INDEX] = PROTO(&gEfiUnicodeCollationProtocol2Guid, t("EFI_UNICODE_COLLATION_PROTOCOL")),
    [EFI_REGULAR_EXPRESSION_PROTOCOL_INDEX] = PROTO(&gEfiRegularExpressionProtocolGuid, t("EFI_REGULAR_EXPRESSION_PROTOCOL")),

    //
    // PROTOCOLS - BYTE CODE VM - Chapter 22
    //

    //
    // PROTOCOLS - FIRMWARE SERVICES - Chapter 23
    //

    [EFI_SYSTEM_RESOURCE_TABLE_INDEX] = PROTO(&gEfiSystemResourceTableGuid, t("EFI_SYSTEM_RESOURCE_TABLE")),

    //
    // PROTOCOLS - NETWORK - SNP, PXE, BIS and HTTP Boot - Chapter 24
    //

    [EFI_SIMPLE_NETWORK_PROTOCOL_INDEX] = PROTO(&gEfiSimpleNetworkProtocolGuid, t("EFI_SIMPLE_NETWORK_PROTOCOL")),
    [EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_INDEX] = PROTO(&gEfiNetworkInterfaceIdentifierProtocolGuid, t("EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL")),
    [EFI_PXE_BASE_CODE_PROTOCOL_INDEX] = PROTO(&gEfiPxeBaseCodeProtocolGuid, t("EFI_PXE_BASE_CODE_PROTOCOL")),
    [EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL_INDEX] = PROTO(&gEfiPxeBaseCodeCallbackProtocolGuid, t("EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL")),
    [EFI_BIS_PROTOCOL_INDEX] = PROTO(&gEfiBisProtocolGuid, t("EFI_BIS_PROTOCOL")),
    [EFI_HTTP_BOOT_CALLBACK_PROTOCOL_INDEX] = PROTO(&gEfiHttpBootCallbackProtocolGuid, t("EFI_HTTP_BOOT_CALLBACK_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - Managed Network - Chapter 25
    //

    [EFI_MANAGED_NETWORK_PROTOCOL_INDEX] = SB_PROTO(&gEfiManagedNetworkProtocolGuid, t("EFI_MANAGED_NETWORK_PROTOCOL"), &gEfiManagedNetworkServiceBindingProtocolGuid, t("EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - Bluetooth - Chapter 26
    //

    [EFI_BLUETOOTH_HC_PROTOCOL_INDEX] = PROTO(&gEfiBluetoothHcProtocolGuid, t("EFI_BLUETOOTH_HC_PROTOCOL")),
    [EFI_BLUETOOTH_IO_PROTOCOL_INDEX] = SB_PROTO(&gEfiBluetoothIoProtocolGuid, t("EFI_BLUETOOTH_IO_PROTOCOL"), &gEfiBluetoothIoServiceBindingProtocolGuid, t("EFI_BLUETOOTH_IO_SERVICE_BINDING_PROTOCOL")),
    [EFI_BLUETOOTH_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiBluetoothConfigProtocolGuid, t("EFI_BLUETOOTH_CONFIG_PROTOCOL")),
    [EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL_INDEX] = SB_PROTO(&gEfiBluetoothAttributeProtocolGuid, t("EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL"), &gEfiBluetoothAttributeServiceBindingProtocolGuid, t("EFI_BLUETOOTH_ATTRIBUTE_SERVICE_BINDING_PROTOCOL")),
    [EFI_BLUETOOTH_LE_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiBluetoothLeConfigProtocolGuid, t("EFI_BLUETOOTH_LE_CONFIG_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - VLAN, EAP, Wi-Fi and Supplicant - Chapter 27
    //

    [EFI_VLAN_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiVlanConfigProtocolGuid, t("EFI_VLAN_CONFIG_PROTOCOL")),
    [EFI_EAP_PROTOCOL_INDEX] = PROTO(&gEfiEapProtocolGuid, t("EFI_EAP_PROTOCOL")),
    [EFI_EAP_MANAGEMENT_PROTOCOL_INDEX] = PROTO(&gEfiEapManagementProtocolGuid, t("EFI_EAP_MANAGEMENT_PROTOCOL")),
    [EFI_EAP_MANAGEMENT2_PROTOCOL_INDEX] = PROTO(&gEfiEapManagement2ProtocolGuid, t("EFI_EAP_MANAGEMENT2_PROTOCOL")),
    [EFI_EAP_CONFIGURATION_PROTOCOL_INDEX] = PROTO(&gEfiEapConfigurationProtocolGuid, t("EFI_EAP_CONFIGURATION_PROTOCOL")),
    [EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_INDEX] = PROTO(&gEfiWirelessMacConnectionProtocolGuid, t("EFI_WIRELESS_MAC_CONNECTION_PROTOCOL")),
    [EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX] = PROTO(&gEfiWirelessMacConnection2ProtocolGuid, t("EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL")),
    [EFI_SUPPLICANT_PROTOCOL_INDEX] = PROTO(&gEfiSupplicantProtocolGuid, t("EFI_SUPPLICANT_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - TCP, IP, IPsec, FTP, TLS and Configurations - Chapter 28
    //

    [EFI_TCP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiTcp4ProtocolGuid, t("EFI_TCP4_PROTOCOL"), &gEfiTcp4ServiceBindingProtocolGuid, t("EFI_TCP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_TCP6_PROTOCOL_INDEX] = SB_PROTO(&gEfiTcp6ProtocolGuid, t("EFI_TCP6_PROTOCOL"), &gEfiTcp6ServiceBindingProtocolGuid, t("EFI_TCP6_SERVICE_BINDING_PROTOCOL")),
    [EFI_IP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiIp4ProtocolGuid, t("EFI_IP4_PROTOCOL"), &gEfiIp4ServiceBindingProtocolGuid, t("EFI_IP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_IP4_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiIp4ConfigProtocolGuid, t("EFI_IP4_CONFIG_PROTOCOL")),
    [EFI_IP4_CONFIG2_PROTOCOL_INDEX] = PROTO(&gEfiIp4Config2ProtocolGuid, t("EFI_IP4_CONFIG2_PROTOCOL")),
    [EFI_IP6_PROTOCOL_INDEX] = SB_PROTO(&gEfiIp6ProtocolGuid, t("EFI_IP6_PROTOCOL"), &gEfiIp6ServiceBindingProtocolGuid, t("EFI_IP6_SERVICE_BINDING_PROTOCOL")),
    [EFI_IP6_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiIp6ConfigProtocolGuid, t("EFI_IP6_CONFIG_PROTOCOL")),
    [EFI_IPSEC_CONFIG_PROTOCOL_INDEX] = PROTO(&gEfiIpsecConfigProtocolGuid, t("EFI_IPSEC_CONFIG_PROTOCOL")),
    [EFI_IPSEC_PROTOCOL_INDEX] = PROTO(&gEfiIpsecProtocolGuid, t("EFI_IPSEC_PROTOCOL")),
    [EFI_IPSEC2_PROTOCOL_INDEX] = PROTO(&gEfiIpsec2ProtocolGuid, t("EFI_IPSEC2_PROTOCOL")),
    [EFI_FTP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiFtp4ProtocolGuid, t("EFI_FTP4_PROTOCOL"), &gEfiFtp4ServiceBindingProtocolGuid, t("EFI_FTP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_TLS_PROTOCOL_INDEX] = SB_PROTO(&gEfiTlsProtocolGuid, t("EFI_TLS_PROTOCOL"), &gEfiTlsServiceBindingProtocolGuid, t("EFI_TLS_SERVICE_BINDING_PROTOCOL")),
    [EFI_TLS_CONFIGURATION_PROTOCOL_INDEX] = PROTO(&gEfiTlsConfigurationProtocolGuid, t("EFI_TLS_CONFIGURATION_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - ARP, DHCP, DNS, HTTP and REST - Chapter 29
    //

    [EFI_ARP_PROTOCOL_INDEX] = SB_PROTO(&gEfiArpProtocolGuid, t("EFI_ARP_PROTOCOL"), &gEfiArpServiceBindingProtocolGuid, t("EFI_ARP_SERVICE_BINDING_PROTOCOL")),
    [EFI_DHCP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiDhcp4ProtocolGuid, t("EFI_DHCP4_PROTOCOL"), &gEfiDhcp4ServiceBindingProtocolGuid, t("EFI_DHCP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_DHCP6_PROTOCOL_INDEX] = SB_PROTO(&gEfiDhcp6ProtocolGuid, t("EFI_DHCP6_PROTOCOL"), &gEfiDhcp6ServiceBindingProtocolGuid, t("EFI_DHCP6_SERVICE_BINDING_PROTOCOL")),
    [EFI_DNS4_PROTOCOL_INDEX] = SB_PROTO(&gEfiDns4ProtocolGuid, t("EFI_DNS4_PROTOCOL"), &gEfiDns4ServiceBindingProtocolGuid, t("EFI_DNS4_SERVICE_BINDING_PROTOCOL")),
    [EFI_DNS6_PROTOCOL_INDEX] = SB_PROTO(&gEfiDns6ProtocolGuid, t("EFI_DNS6_PROTOCOL"), &gEfiDns6ServiceBindingProtocolGuid, t("EFI_DNS6_SERVICE_BINDING_PROTOCOL")),
    [EFI_HTTP_PROTOCOL_INDEX] = SB_PROTO(&gEfiHttpProtocolGuid, t("EFI_HTTP_PROTOCOL"), &gEfiHttpServiceBindingProtocolGuid, t("EFI_HTTP_SERVICE_BINDING_PROTOCOL")),
    [EFI_HTTP_UTILITIES_PROTOCOL_INDEX] = PROTO(&gEfiHttpUtilitiesProtocolGuid, t("EFI_HTTP_UTILITIES_PROTOCOL")),
    [EFI_REST_PROTOCOL_INDEX] = PROTO(&gEfiRestProtocolGuid, t("EFI_REST_PROTOCOL")),
    [EFI_REST_EX_PROTOCOL_INDEX] = SB_PROTO(&gEfiRestExProtocolGuid, t("EFI_REST_EX_PROTOCOL"), &gEfiRestExServiceBindingProtocolGuid, t("EFI_REST_EX_SERVICE_BINDING_PROTOCOL")),
    [EFI_REST_JSON_STRUCTURE_PROTOCOL_INDEX] = PROTO(&gEfiRestJsonStructureProtocolGuid, t("EFI_REST_JSON_STRUCTURE_PROTOCOL")),

    //
    // PROTOCOLS - NETWORK - UDP and MTFTP - Chapter 30
    //

    [EFI_UDP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiUdp4ProtocolGuid, t("EFI_UDP4_PROTOCOL"), &gEfiUdp4ServiceBindingProtocolGuid, t("EFI_UDP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_UDP6_PROTOCOL_INDEX] = SB_PROTO(&gEfiUdp6ProtocolGuid, t("EFI_UDP6_PROTOCOL"), &gEfiUdp6ServiceBindingProtocolGuid, t("EFI_UDP6_SERVICE_BINDING_PROTOCOL")),
    [EFI_MTFTP4_PROTOCOL_INDEX] = SB_PROTO(&gEfiMtftp4ProtocolGuid, t("EFI_MTFTP4_PROTOCOL"), &gEfiMtftp4ServiceBindingProtocolGuid, t("EFI_MTFTP4_SERVICE_BINDING_PROTOCOL")),
    [EFI_MTFTP6_PROTOCOL_INDEX] = SB_PROTO(&gEfiMtftp6ProtocolGuid, t("EFI_MTFTP6_PROTOCOL"), &gEfiMtftp4ServiceBindingProtocolGuid, t("EFI_MTFTP4_SERVICE_BINDING_PROTOCOL")),

    //
    // PROTOCOLS - HII - Chapter 34
    //

    [EFI_HII_FONT_PROTOCOL_INDEX] = PROTO(&gEfiHiiFontProtocolGuid, t("EFI_HII_FONT_PROTOCOL")),
    [EFI_HII_FONT_EX_PROTOCOL_INDEX] = PROTO(&gEfiHiiFontExProtocolGuid, t("EFI_HII_FONT_EX_PROTOCOL")),
    [EFI_HII_STRING_PROTOCOL_INDEX] = PROTO(&gEfiHiiStringProtocolGuid, t("EFI_HII_STRING_PROTOCOL")),
    [EFI_HII_IMAGE_PROTOCOL_INDEX] = PROTO(&gEfiHiiImageProtocolGuid, t("EFI_HII_IMAGE_PROTOCOL")),
    [EFI_HII_IMAGE_EX_PROTOCOL_INDEX] = PROTO(&gEfiHiiImageExProtocolGuid, t("EFI_HII_IMAGE_EX_PROTOCOL")),
    [EFI_HII_IMAGE_DECODER_PROTOCOL_INDEX] = PROTO(&gEfiHiiImageDecoderProtocolGuid, t("EFI_HII_IMAGE_DECODER_PROTOCOL")),
    [EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL_INDEX] = PROTO(&gEfiHiiFontGlyphGeneratorProtocolGuid, t("EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL")),
    [EFI_HII_DATABASE_PROTOCOL_INDEX] = PROTO(&gEfiHiiDatabaseProtocolGuid, t("EFI_HII_DATABASE_PROTOCOL")),
    [EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_INDEX] = PROTO(&gEfiConfigKeywordHandlerProtocolGuid, t("EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL")),
    [EFI_HII_CONFIG_ROUTING_PROTOCOL_INDEX] = PROTO(&gEfiHiiConfigRoutingProtocolGuid, t("EFI_HII_CONFIG_ROUTING_PROTOCOL")),
    [EFI_HII_CONFIG_ACCESS_PROTOCOL_INDEX] = PROTO(&gEfiHiiConfigAccessProtocolGuid, t("EFI_HII_CONFIG_ACCESS_PROTOCOL")),
    [EFI_FORM_BROWSER2_PROTOCOL_INDEX] = PROTO(&gEfiFormBrowser2ProtocolGuid, t("EFI_FORM_BROWSER2_PROTOCOL")),
    [EFI_HII_POPUP_PROTOCOL_INDEX] = PROTO(&gEfiHiiPopupProtocolGuid, t("EFI_HII_POPUP_PROTOCOL")),
    // [EFI_HII_PACKAGE_LIST_PROTOCOL_INDEX] =

    //
    // PROTOCOLS - Secure Technologies - Chapter 37
    //

#ifndef _ARM64_
    [EFI_HASH_PROTOCOL_INDEX]                             = SB_PROTO(&gEfiHashProtocolGuid, t("EFI_HASH_PROTOCOL"), &gEfiHashServiceBindingProtocolGuid, t("EFI_HASH_SERVICE_BINDING_PROTOCOL")),
    [EFI_HASH2_PROTOCOL_INDEX]                            = SB_PROTO(&gEfiHash2ProtocolGuid, t("EFI_HASH2_PROTOCOL"), &gEfiHash2ServiceBindingProtocolGuid, t("EFI_HASH2_SERVICE_BINDING_PROTOCOL")),
#endif
    [EFI_KEY_MANAGEMENT_SERVICE_PROTOCOL_INDEX] = PROTO(&gEfiKmsProtocolGuid, t("EFI_KEY_MANAGEMENT_SERVICE_PROTOCOL")),
    [EFI_PKCS7_VERIFY_PROTOCOL_INDEX] = PROTO(&gEfiPkcs7VerifyProtocolGuid, t("EFI_PKCS7_VERIFY_PROTOCOL")),
    [EFI_RNG_PROTOCOL_INDEX] = PROTO(&gEfiRngProtocolGuid, t("EFI_RNG_PROTOCOL")),
    [EFI_SMART_CARD_READER_PROTOCOL_INDEX] = PROTO(&gEfiSmartCardReaderProtocolGuid, t("EFI_SMART_CARD_READER_PROTOCOL")),

    //
    // PROTOCOLS - Secure Technologies - Chapter 38
    //

    [EFI_TIMESTAMP_PROTOCOL_INDEX] = PROTO(&gEfiTimeStampProtocolGuid, t("EFI_TIMESTAMP_PROTOCOL")),
    [EFI_RESET_NOTIFICATION_PROTOCOL_INDEX] = PROTO(&gEfiResetNotificationProtocolGuid, t("EFI_RESET_NOTIFICATION_PROTOCOL")),

    //
    // MISCELLANOUS PROTOCOLS
    //

    [EFI_SMBIOS_PROTOCOL_INDEX] = PROTO(&gEfiSmbiosProtocolGuid, t("EFI_SMBIOS_PROTOCOL")),
    [EFI_SHELL_PROTOCOL_INDEX] = PROTO(&gEfiShellProtocolGuid, t("EFI_SHELL_PROTOCOL")),

    //
    // NON STANDARD PROTOCOLS
    //

    [EDKII_VARIABLE_LOCK_PROTOCOL_INDEX] = PROTO(&gEdk2VariableLockProtocolGuid, t("EDKII_VARIABLE_LOCK_PROTOCOL")),
    // clang-format on
};

static EFI_STATUS ProtocolGetInfo(_In_ PBM_PROTOCOL_INFO ProtocolInfo);

EFI_STATUS
ProtocolOpenServiceBinding(_In_ EFI_HANDLE DeviceHandle,
                           _In_ EFI_GUID* ServiceBindingProtocolGuid,
                           _Outptr_ EFI_SERVICE_BINDING_PROTOCOL** ServiceBindingProtocol)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SERVICE_BINDING_PROTOCOL* LocalSericeBindingProtocol = NULL;

    //
    // Get the protocol reference for the Protocolhandle.
    //

    Status = gBS->OpenProtocol(DeviceHandle,
                               ServiceBindingProtocolGuid,
                               (PVOID*)&LocalSericeBindingProtocol,
                               gImageHandle,
                               NULL,
                               EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("OpenProtocol() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    *ServiceBindingProtocol = LocalSericeBindingProtocol;

Exit:
    return Status;
}

EFI_STATUS
ProtocolOpenServiceBindingChildProtocol(_In_ EFI_SERVICE_BINDING_PROTOCOL* ServiceBindingProtocol,
                                        _In_ EFI_GUID* ProtocolGuid,
                                        _Outptr_ PVOID* Protocol,
                                        _Outptr_ EFI_HANDLE* ProtocolHandle)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE ChildHandle = NULL;
    PVOID RetProtocol = NULL;

    if (ServiceBindingProtocol == NULL) {
        DBG_ERROR("ServiceBindingProtocol is null");
        return EFI_INVALID_PARAMETER;
    }

    //
    //  Get protocol child protocol handle.
    //

    Status = ServiceBindingProtocol->CreateChild(ServiceBindingProtocol, &ChildHandle);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("CreateChild() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Get the protocol reference to the child protocol handle.
    //

    Status = gBS->OpenProtocol(ChildHandle,
                               ProtocolGuid,
                               (PVOID*)&RetProtocol,
                               gImageHandle,
                               NULL,
                               EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("OpenProtocol() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    *Protocol = RetProtocol;
    *ProtocolHandle = ChildHandle;
    return Status;

Exit:
    if (ChildHandle != NULL) {
        ServiceBindingProtocol->DestroyChild(ServiceBindingProtocol, &ChildHandle);
    }

    return Status;
}

EFI_STATUS
ProtocolServiceBindingClose(_In_ EFI_HANDLE DeviceHandle,
                            _In_ EFI_GUID* ServiceBindingProtocolGuid,
                            _In_ EFI_SERVICE_BINDING_PROTOCOL* ServiceBindingProtocol,
                            _In_ EFI_GUID* ProtocolGuid,
                            _In_ VOID* Protocol,
                            _In_ EFI_HANDLE ProtocolHandle)
{
    EFI_STATUS Status = EFI_SUCCESS;

    //
    // Close the child protocol first
    //

    if (ProtocolHandle != NULL && Protocol != NULL) {
        Status = gBS->CloseProtocol(ProtocolHandle, ProtocolGuid, gImageHandle, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("CloseProtocol() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

    //
    // Next, Close the child protocol handle
    //

    if (ServiceBindingProtocol != NULL && ProtocolHandle != NULL) {
        Status = ServiceBindingProtocol->DestroyChild(ServiceBindingProtocol, ProtocolHandle);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("DestroyChild() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

    //
    // Next, Close service binding protocol on device handle
    //

    if (DeviceHandle != NULL && ServiceBindingProtocol != NULL) {
        Status = gBS->CloseProtocol(DeviceHandle, ServiceBindingProtocolGuid, gImageHandle, NULL);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("CloseProtocol() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

Exit:
    return Status;
}

EFI_STATUS
EFIAPI
ProtocolProbeAll(VOID)
{
    EFI_STATUS Status = EFI_SUCCESS;

    NetworkCommonInitStack();

    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        ProtocolGetInfo(&ProtocolArray[Index]);
    }

    return Status;
}

static EFI_STATUS ProtocolGetInfo(_In_ PBM_PROTOCOL_INFO ProtocolInfo)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* DeviceHandles = NULL;
    HANDLE ChildHandle = NULL;
    UINTN DeviceHandleCount = 0;

    if (ProtocolInfo->ProtocolGuid == NULL) {
        goto Exit;
    }

    if (ProtocolInfo->ServiceBindingProtocolName == NULL) {
        Status = gBS->LocateProtocol(ProtocolInfo->ProtocolGuid,
                                     NULL,
                                     (PVOID*)&ProtocolInfo->Protocol);
        ProtocolInfo->ProtocolStatus = Status;
        if (EFI_ERROR(Status)) {
            // DBG_ERROR("ProtocolName = %s ProtocolStatus = %s(0x%zx)",
            //           ProtocolInfo->ProtocolName,
            //           E(Status),
            //           Status);
            goto Exit;
        }
    } else {
        Status = gBS->LocateHandleBuffer(ByProtocol,
                                         ProtocolInfo->ServiceBindingProtocolGuid,
                                         NULL,
                                         &DeviceHandleCount,
                                         &DeviceHandles);
        ProtocolInfo->ServiceBindingProtocolStatus = Status;
        if (EFI_ERROR(Status)) {
            // DBG_ERROR("ProtocolName = %s LocateHandleBuffer() failed Status = %s(0x%zx)",
            //           ProtocolInfo->ProtocolName,
            //           E(Status),
            //           Status);
            goto Exit;
        }

        for (UINTN Index = 0; Index < DeviceHandleCount; Index++) {
            ChildHandle = NULL;
            //
            // Open service binding
            //

            Status = ProtocolOpenServiceBinding(DeviceHandles[Index],
                                                ProtocolInfo->ServiceBindingProtocolGuid,
                                                &ProtocolInfo->ServiceBindingProtocol);

            ProtocolInfo->ServiceBindingProtocolStatus = Status;
            if (EFI_ERROR(Status)) {
                // DBG_ERROR(
                //     "ProtocolName = %s ProtocolOpenServiceBinding() failed Status = %s(0x%zx)",
                //     ProtocolInfo->ProtocolName,
                //     E(Status),
                //     Status);
                continue;
            }

            //
            // Create child protocol from service binding
            //

            Status = ProtocolOpenServiceBindingChildProtocol(ProtocolInfo->ServiceBindingProtocol,
                                                             ProtocolInfo->ProtocolGuid,
                                                             &ProtocolInfo->Protocol,
                                                             &ChildHandle);
            ProtocolInfo->ProtocolStatus = Status;
            if (EFI_ERROR(Status)) {
                // DBG_ERROR(
                //     "ProtocolName = %s ProtocolOpenServiceBindingChildProtocol() failed Status = %s(0x%zx)",
                //     ProtocolInfo->ProtocolName,
                //     E(Status),
                //     Status);
                continue;
            }
#if 0
            (VOID) ProtocolServiceBindingClose(DeviceHandles[Index],
                                                 ProtocolInfo->ServiceBindingProtocolGuid,
                                                 ProtocolInfo->ServiceBindingProtocol,
                                                 ProtocolInfo->ProtocolGuid,
                                                 ProtocolInfo->Protocol,
                                                 ChildHandle);
#endif
            break;
        }
    }

Exit:
    if (DeviceHandles) {
        gBS->FreePool(DeviceHandles);
    }
    return Status;
}

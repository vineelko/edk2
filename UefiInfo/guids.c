#include "common.h"

// clang-format off
EFI_GUID gUefiInfoACPIOSFRMfgStringVariableGuid                           = {0x72234213, 0x0fd7, 0x48a1, {0xa5, 0x9f, 0xb4, 0x1b, 0xc1, 0x07, 0xfb, 0xcd}};
EFI_GUID gUefiInfoACPIOSFRModelStringVariableGuid                         = {0xca1bcad9, 0xe021, 0x4547, {0xa1, 0xb0, 0x5b, 0x22, 0xc7, 0xf6, 0x87, 0xf4}};
EFI_GUID gUefiInfoACPIOSFRRefDataBlockVariableGuid                        = {0x72234213, 0x0fd7, 0x48a1, {0xa5, 0x9f, 0xb4, 0x1b, 0xc1, 0x07, 0xfb, 0xcd}};
EFI_GUID gUefiInfoAdapterInfoPlatformSecurityGuid                         = {0x6be272c7, 0x1320, 0x4ccd, {0x90, 0x17, 0xd4, 0x61, 0x2c, 0x01, 0x2b, 0x25}};
EFI_GUID gUefiInfoAmtReadyToBootGuid                                      = {0x40b09b5a, 0xf0ef, 0x4627, {0x93, 0xd5, 0x27, 0xf0, 0x4b, 0x75, 0x4d, 0x05}};
EFI_GUID gUefiInfoAndroidFastbootPlatformProtocolGuid                     = {0x524685a0, 0x89a0, 0x11e3, {0x9d, 0x4d, 0xbf, 0xa9, 0xf6, 0xa4, 0x03, 0x08}};
EFI_GUID gUefiInfoAndroidFastbootTransportProtocolGuid                    = {0x74bd9fe0, 0x8902, 0x11e3, {0xb9, 0xd3, 0xf7, 0x22, 0x38, 0xfc, 0x9a, 0x31}};
EFI_GUID gUefiInfoAppPkgTokenSpaceGuid                                    = {0xe7e1efa6, 0x7607, 0x4a78, {0xa7, 0xdd, 0x43, 0xe4, 0xbd, 0x72, 0xc0, 0x99}};
EFI_GUID gUefiInfoAprioriGuid                                             = {0xfc510ee7, 0xffdc, 0x11d4, {0xbd, 0x41, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoArmBootMonFsFileInfoGuid                                = {0x41e26b9c, 0xada6, 0x45b3, {0x80, 0x8e, 0x23, 0x57, 0xa3, 0x5b, 0x60, 0xd6}};
EFI_GUID gUefiInfoArmGlobalVariableGuid                                   = {0xc3253c90, 0xa24f, 0x4599, {0xa6, 0x64, 0x1f, 0x88, 0x13, 0x77, 0x8f, 0xc9}};
EFI_GUID gUefiInfoArmGlobalVariablePpiGuid                                = {0xab1c1816, 0xd542, 0x4e6f, {0x9b, 0x1e, 0x8e, 0xcd, 0x92, 0x53, 0xe2, 0xe7}};
EFI_GUID gUefiInfoArmJunoTokenSpaceGuid                                   = {0xa1147a20, 0x3144, 0x4f8d, {0x82, 0x95, 0xb4, 0x83, 0x11, 0xc8, 0xe4, 0xa4}};
EFI_GUID gUefiInfoArmMpCoreInfoGuid                                       = {0xa4ee0728, 0xe5d7, 0x4ac5, {0xb2, 0x1e, 0x65, 0x8e, 0xd8, 0x57, 0xe8, 0x34}};
EFI_GUID gUefiInfoArmMpCoreInfoPpiGuid                                    = {0x6847cc74, 0xe9ec, 0x4f8f, {0xa2, 0x9d, 0xab, 0x44, 0xe7, 0x54, 0xa8, 0xfc}};
EFI_GUID gUefiInfoArmPlatformTokenSpaceGuid                               = {0x9c0aaed4, 0x74c5, 0x4043, {0xb4, 0x17, 0xa3, 0x22, 0x38, 0x14, 0xce, 0x76}};
EFI_GUID gUefiInfoArmPlatformUpdateFdtEventGuid                           = {0xaffe115b, 0x8589, 0x456d, {0xba, 0xb5, 0x8f, 0x2e, 0xda, 0x53, 0xae, 0xb7}};
EFI_GUID gUefiInfoArmRealViewEbPkgTokenSpaceGuid                          = {0x44577a0d, 0x361a, 0x45b2, {0xb3, 0x3d, 0xbb, 0x9e, 0xe6, 0x0d, 0x5a, 0x4f}};
EFI_GUID gUefiInfoArmTokenSpaceGuid                                       = {0xbb11ecfe, 0x820f, 0x4968, {0xbb, 0xa6, 0xf7, 0x6a, 0xfe, 0x30, 0x25, 0x96}};
EFI_GUID gUefiInfoArmVExpressTokenSpaceGuid                               = {0x9c0aaed4, 0x74c5, 0x4043, {0xb4, 0x17, 0xa3, 0x22, 0x38, 0x14, 0xce, 0x76}};
EFI_GUID gUefiInfoArmVirtualizationTokenSpaceGuid                         = {0x0b6f5ca7, 0x4f53, 0x445a, {0xb7, 0x6e, 0x2e, 0x36, 0x5b, 0x80, 0x63, 0x66}};
EFI_GUID gUefiInfoBdsLibStringPackageGuid                                 = {0x3b4d9b23, 0x95ac, 0x44f6, {0x9f, 0xcd, 0x0e, 0x95, 0x94, 0x58, 0x6c, 0x72}};
EFI_GUID gUefiInfoBeagleBoardTokenSpaceGuid                               = {0x6834fe45, 0x4aee, 0x4fc6, {0xbc, 0xb5, 0xff, 0x45, 0xb7, 0xa8, 0x71, 0xe2}};
EFI_GUID gUefiInfoBlockIoVendorGuid                                       = {0xcf31fac5, 0xc24e, 0x11d2, {0x85, 0xf3, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}};
EFI_GUID gUefiInfoBlockMmioProtocolGuid                                   = {0x6b558ce3, 0x69e5, 0x4c67, {0xa6, 0x34, 0xf7, 0xfe, 0x72, 0xad, 0xbe, 0x84}};
EFI_GUID gUefiInfoBmpImageGuid                                            = {0x878ac2cc, 0x5343, 0x46f2, {0xb5, 0x63, 0x51, 0xf8, 0x9d, 0xaf, 0x56, 0xba}};
EFI_GUID gUefiInfoBootMaintFormSetGuid                                    = {0x642237c7, 0x35d4, 0x472d, {0x83, 0x65, 0x12, 0xe0, 0xcc, 0xf2, 0x7a, 0x22}};
EFI_GUID gUefiInfoBootManagerFormSetGuid                                  = {0x847bc3fe, 0xb974, 0x446d, {0x94, 0x49, 0x5a, 0xd5, 0x41, 0x2e, 0x99, 0x3b}};
EFI_GUID gUefiInfoBootObjectAuthorizationParmsetGuid                      = {0xedd35e31, 0x07b9, 0x11d2, {0x83, 0xa3, 0x00, 0xa0, 0xc9, 0x1f, 0xad, 0xcf}};
EFI_GUID gUefiInfoConnectConInEventGuid                                   = {0xdb4e8151, 0x57ed, 0x4bed, {0x88, 0x33, 0x67, 0x51, 0xb5, 0xd1, 0xa8, 0xd7}};
EFI_GUID gUefiInfoDeviceManagerFormSetGuid                                = {0x3ebfa8e6, 0x511d, 0x4b5b, {0xa9, 0x5f, 0xfb, 0x38, 0x26, 0x0f, 0x1c, 0x27}};
EFI_GUID gUefiInfoDmiDataGuid                                             = {0x70e56c5e, 0x280c, 0x44b0, {0xa4, 0x97, 0x09, 0x68, 0x1a, 0xbc, 0x37, 0x5e}};
EFI_GUID gUefiInfoDriverHealthFormSetGuid                                 = {0xf76e0a70, 0xb5ed, 0x4c38, {0xac, 0x9a, 0xe5, 0xf5, 0x4b, 0xf1, 0x6e, 0x34}};
EFI_GUID gUefiInfoDriverSampleFormSetGuid                                 = {0xa04a27f4, 0xdf00, 0x4d42, {0xb5, 0x52, 0x39, 0x51, 0x13, 0x02, 0x11, 0x3d}};
EFI_GUID gUefiInfoDriverSampleInventoryGuid                               = {0xb3f56470, 0x6141, 0x4621, {0x8f, 0x19, 0x70, 0x4e, 0x57, 0x7a, 0xa9, 0xe8}};
EFI_GUID gUefiInfoDuetConsoleOutConfigGuid                                = {0xed150714, 0xdf30, 0x407d, {0xb2, 0x4a, 0x4b, 0x74, 0x2f, 0xd5, 0xce, 0xa2}};
EFI_GUID gUefiInfoDxeDebugCmdProtocolGuid                                 = {0xca3b3a50, 0x5698, 0x4551, {0x8b, 0x18, 0xce, 0xae, 0xef, 0x91, 0x7d, 0x50}};
EFI_GUID gUefiInfoDxeDebugDispatchProtocolGuid                            = {0x301af449, 0xe0d7, 0x43a3, {0x8b, 0x1b, 0xbc, 0x16, 0x72, 0x5d, 0x37, 0x4b}};
EFI_GUID gUefiInfoDxeDebugportExtProtocolGuid                             = {0x31a4878f, 0x230d, 0x4fc2, {0x90, 0xbb, 0xda, 0x5f, 0x41, 0xa4, 0x4b, 0x1b}};
EFI_GUID gUefiInfoDxeIchPlatformPolicyProtocolGuid                        = {0xf617b358, 0x12cf, 0x414a, {0xa0, 0x69, 0x60, 0x67, 0x7b, 0xda, 0x13, 0xb3}};
EFI_GUID gUefiInfoDxePchPlatformPolicyProtocolGuid                        = {0x4b0165a9, 0x61d6, 0x4e23, {0xa0, 0xb5, 0x3e, 0xc7, 0x9c, 0x2e, 0x30, 0xd5}};
EFI_GUID gUefiInfoDxePchPolicyUpdateProtocolGuid                          = {0x1a819e49, 0xd8ee, 0x48cb, {0x9a, 0x9c, 0x0a, 0xa0, 0xd2, 0x81, 0x0a, 0x38}};
EFI_GUID gUefiInfoDxePlatformSeCPolicyGuid                                = {0xf8bff014, 0x18fb, 0x4ef9, {0xb1, 0x0c, 0xae, 0x22, 0x73, 0x8d, 0xbe, 0xed}};
EFI_GUID gUefiInfoDxeVlvPlatformPolicyGuid                                = {0x5bab88ba, 0xe0e2, 0x4674, {0xb6, 0xad, 0xb8, 0x12, 0xf6, 0x88, 0x1c, 0xd6}};
EFI_GUID gUefiInfoEarlyPL011BaseAddressGuid                               = {0xb199dea9, 0xfd5c, 0x4a84, {0x80, 0x82, 0x2f, 0x41, 0x70, 0x78, 0x03, 0x05}};
EFI_GUID gUefiInfoEcpPeiPciCfgPpiGuid                                     = {0xb0ee53d4, 0xa049, 0x4a79, {0xb2, 0xff, 0x19, 0xd9, 0xfa, 0xef, 0xaa, 0x94}};
EFI_GUID gUefiInfoEdkiiFaultTolerantWriteGuid                             = {0x1d3e9cb8, 0x43af, 0x490b, {0x83, 0x0a, 0x35, 0x16, 0xaa, 0x53, 0x20, 0x47}};
EFI_GUID gUefiInfoEdkiiFormBrowserEx2ProtocolGuid                         = {0xa770c357, 0xb693, 0x4e6d, {0xa6, 0xcf, 0xd2, 0x1c, 0x72, 0x8e, 0x55, 0x0b}};
EFI_GUID gUefiInfoEdkiiFormDisplayEngineProtocolGuid                      = {0x9bbe29e9, 0xfda1, 0x41ec, {0xad, 0x52, 0x45, 0x22, 0x13, 0x74, 0x2d, 0x2e}};
EFI_GUID gUefiInfoEdkiiMemoryProfileGuid                                  = {0x821c9a09, 0x541a, 0x40f6, {0x9f, 0x43, 0x0a, 0xd1, 0x93, 0xa1, 0x2c, 0xfe}};
EFI_GUID gUefiInfoEdkiiSmmVarCheckProtocolGuid                            = {0xb0d8f3c1, 0xb7de, 0x4c11, {0xbc, 0x89, 0x2f, 0xb5, 0x62, 0xc8, 0xc4, 0x11}};
EFI_GUID gUefiInfoEdkiiStatusCodeDataTypeVariableGuid                     = {0xf6ee6dbb, 0xd67f, 0x4ea0, {0x8b, 0x96, 0x6a, 0x71, 0xb1, 0x9d, 0x84, 0xad}};
EFI_GUID gUefiInfoEdkiiVarCheckProtocolGuid                               = {0xaf23b340, 0x97b4, 0x4685, {0x8d, 0x4f, 0xa3, 0xf2, 0x81, 0x69, 0xb2, 0x1d}};
EFI_GUID gUefiInfoEdkiiVarErrorFlagGuid                                   = {0x04b37fe8, 0xf6ae, 0x480b, {0xbd, 0xd5, 0x37, 0xd9, 0x8c, 0x5e, 0x89, 0xaa}};
EFI_GUID gUefiInfoEdkiiVariableLockProtocolGuid                           = {0xcd3d0a05, 0x9e24, 0x437c, {0xa8, 0x91, 0x1e, 0xe0, 0x53, 0xdb, 0x76, 0x38}};
EFI_GUID gUefiInfoEdkiiWorkingBlockSignatureGuid                          = {0x9e58292b, 0x7c68, 0x497d, {0xa0, 0xce, 0x65, 0x00, 0xfd, 0x9f, 0x1b, 0x95}};
EFI_GUID gUefiInfoEfiAbsolutePointerProtocolGuid                          = {0x8d59d32b, 0xc655, 0x4ae9, {0x9b, 0x15, 0xf2, 0x59, 0x04, 0x99, 0x2a, 0x43}};
EFI_GUID gUefiInfoEfiAcpi10TableGuid                                      = {0xeb9d2d30, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiAcpi20TableGuid                                      = {0x8868e871, 0xe4f1, 0x11d3, {0xbc, 0x22, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiAcpiDescriptionGuid                                  = {0x3c699197, 0x093c, 0x4c69, {0xb0, 0x6b, 0x12, 0x8a, 0xe3, 0x48, 0x1d, 0xc9}};
EFI_GUID gUefiInfoEfiAcpiS3ContextGuid                                    = {0x0ef98d3a, 0x3e33, 0x497a, {0xa4, 0x01, 0x77, 0xbe, 0x3e, 0xb7, 0x4f, 0x38}};
EFI_GUID gUefiInfoEfiAcpiS3SaveProtocolGuid                               = {0x125f2de1, 0xfb85, 0x440c, {0xa5, 0x4c, 0x4d, 0x99, 0x35, 0x8a, 0x8d, 0x38}};
EFI_GUID gUefiInfoEfiAcpiSdtProtocolGuid                                  = {0xeb97088e, 0xcfdf, 0x49c6, {0xbe, 0x4b, 0xd9, 0x06, 0xa5, 0xb2, 0x0e, 0x86}};
EFI_GUID gUefiInfoEfiAcpiSupportProtocolGuid                              = {0xdbff9d55, 0x89b7, 0x46da, {0xbd, 0xdf, 0x67, 0x7d, 0x3d, 0xc0, 0x24, 0x1d}};
EFI_GUID gUefiInfoEfiAcpiTableProtocolGuid                                = {0xffe06bdd, 0x6107, 0x46a6, {0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c}};
EFI_GUID gUefiInfoEfiAcpiTableStorageGuid                                 = {0x7e374e25, 0x8e01, 0x4fee, {0x87, 0xf2, 0x39, 0x0c, 0x23, 0xc6, 0x06, 0xcd}};
EFI_GUID gUefiInfoEfiAcpiVariableCompatiblityGuid                         = {0xc020489e, 0x6db2, 0x4ef2, {0x9a, 0xa5, 0xca, 0x06, 0xfc, 0x11, 0xd3, 0x6a}};
EFI_GUID gUefiInfoEfiAcpiVariableGuid                                     = {0xaf9ffd67, 0xec10, 0x488a, {0x9d, 0xfc, 0x6c, 0xbf, 0x5e, 0xe2, 0x2c, 0x2e}};
EFI_GUID gUefiInfoEfiActiveBiosProtocolGuid                               = {0xebbe2d1b, 0x1647, 0x4bda, {0xab, 0x9a, 0x78, 0x63, 0xe3, 0x96, 0xd4, 0x1a}};
EFI_GUID gUefiInfoEfiAdapterInfoMediaStateGuid                            = {0xd7c74207, 0xa831, 0x4a26, {0xb1, 0xf5, 0xd1, 0x93, 0x06, 0x5c, 0xe8, 0xb6}};
EFI_GUID gUefiInfoEfiAdapterInfoMediaTypeGuid                             = {0x8484472f, 0x71ec, 0x411a, {0xb3, 0x9c, 0x62, 0xcd, 0x94, 0xd9, 0x91, 0x6e}};
EFI_GUID gUefiInfoEfiAdapterInfoNetworkBootGuid                           = {0x1fbd2960, 0x4130, 0x41e5, {0x94, 0xac, 0xd2, 0xcf, 0x03, 0x7f, 0xb3, 0x7c}};
EFI_GUID gUefiInfoEfiAdapterInformationProtocolGuid                       = {0xe5dd1403, 0xd622, 0xc24e, {0x84, 0x88, 0xc7, 0x1b, 0x17, 0xf5, 0xe8, 0x02}};
EFI_GUID gUefiInfoEfiAdapterInfoSanMacAddressGuid                         = {0x114da5ef, 0x2cf1, 0x4e12, {0x9b, 0xbb, 0xc4, 0x70, 0xb5, 0x52, 0x05, 0xd9}};
EFI_GUID gUefiInfoEfiAdapterInfoUndiIpv6SupportGuid                       = {0x4bd56be3, 0x4975, 0x4d8a, {0xa0, 0xad, 0xc4, 0x91, 0x20, 0x4b, 0x5d, 0x4d}};
EFI_GUID gUefiInfoEfiAlertStandardFormatProtocolGuid                      = {0xcc93a70b, 0xec27, 0x49c5, {0x8b, 0x34, 0x13, 0x93, 0x1e, 0xfe, 0xd6, 0xe2}};
EFI_GUID gUefiInfoEfiArpProtocolGuid                                      = {0xf4b427bb, 0xba21, 0x4f16, {0xbc, 0x4e, 0x43, 0xe4, 0x16, 0xab, 0x61, 0x9c}};
EFI_GUID gUefiInfoEfiArpServiceBindingProtocolGuid                        = {0xf44c00ee, 0x1f2c, 0x4a00, {0xaa, 0x09, 0x1c, 0x9f, 0x3e, 0x08, 0x00, 0xa3}};
EFI_GUID gUefiInfoEfiAtaPassThruProtocolGuid                              = {0x1d3de7f0, 0x0807, 0x424f, {0xaa, 0x69, 0x11, 0xa5, 0x4e, 0x19, 0xa4, 0x6f}};
EFI_GUID gUefiInfoEfiAuthenticatedVariableGuid                            = {0xaaf32c78, 0x947b, 0x439a, {0xa1, 0x80, 0x2e, 0x14, 0x4e, 0xc3, 0x77, 0x92}};
EFI_GUID gUefiInfoEfiAuthenticationChapLocalGuid                          = {0xc280c73e, 0x15ca, 0x11da, {0xb0, 0xca, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}};
EFI_GUID gUefiInfoEfiAuthenticationChapRadiusGuid                         = {0xd6062b50, 0x15ca, 0x11da, {0x92, 0x19, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}};
EFI_GUID gUefiInfoEfiAuthenticationInfoProtocolGuid                       = {0x7671d9d0, 0x53db, 0x4173, {0xaa, 0x69, 0x23, 0x27, 0xf2, 0x1f, 0x0b, 0xc7}};
EFI_GUID gUefiInfoEfiBdsArchProtocolGuid                                  = {0x665e3ff6, 0x46cc, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiBiosIdGuid                                           = {0xc3e36d09, 0x8294, 0x4b97, {0xa8, 0x57, 0xd5, 0x28, 0x8f, 0xe3, 0x3e, 0x28}};
EFI_GUID gUefiInfoEfiBisProtocolGuid                                      = {0x0b64aab0, 0x5429, 0x11d4, {0x98, 0x16, 0x00, 0xa0, 0xc9, 0x1f, 0xad, 0xcf}};
EFI_GUID gUefiInfoEfiBlockIo2ProtocolGuid                                 = {0xa77b2472, 0xe282, 0x4e9f, {0xa2, 0x45, 0xc2, 0xc0, 0xe2, 0x7b, 0xbc, 0xc1}};
EFI_GUID gUefiInfoEfiBlockIoCryptoAlgoGuidAesCbcMicrosoftBitlocker        = {0x689e4c62, 0x70bf, 0x4cf3, {0x88, 0xbb, 0x33, 0xb3, 0x18, 0x26, 0x86, 0x70}};
EFI_GUID gUefiInfoEfiBlockIoCryptoAlgoGuidAesXts                          = {0x2f87ba6a, 0x5c04, 0x4385, {0xa7, 0x80, 0xf3, 0xbf, 0x78, 0xa9, 0x7b, 0xec}};
EFI_GUID gUefiInfoEfiBlockIoCryptoProtocolGuid                            = {0xa00490ba, 0x3f1a, 0x4b4c, {0xab, 0x90, 0x4f, 0xa9, 0x97, 0x26, 0xa1, 0xe8}};
EFI_GUID gUefiInfoEfiBlockIoProtocolGuid                                  = {0x964e5b21, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiBluetoothAttributeProtocolGuid                       = {0x898890e9, 0x84b2, 0x4f3a, {0x8c, 0x58, 0xd8, 0x57, 0x78, 0x13, 0xe0, 0xac}};
EFI_GUID gUefiInfoEfiBluetoothAttributeServiceBindingProtocolGuid         = {0x5639867a, 0x8c8e, 0x408d, {0xac, 0x2f, 0x4b, 0x61, 0xbd, 0xc0, 0xbb, 0xbb}};
EFI_GUID gUefiInfoEfiBluetoothConfigProtocolGuid                          = {0x62960cf3, 0x40ff, 0x4263, {0xa7, 0x7c, 0xdf, 0xde, 0xbd, 0x19, 0x1b, 0x4b}};
EFI_GUID gUefiInfoEfiBluetoothHcProtocolGuid                              = {0xb3930571, 0xbeba, 0x4fc5, {0x92, 0x03, 0x94, 0x27, 0x24, 0x2e, 0x6a, 0x43}};
EFI_GUID gUefiInfoEfiBluetoothIoProtocolGuid                              = {0x467313de, 0x4e30, 0x43f1, {0x94, 0x3e, 0x32, 0x3f, 0x89, 0x84, 0x5d, 0xb5}};
EFI_GUID gUefiInfoEfiBluetoothIoServiceBindingProtocolGuid                = {0x388278d3, 0x7b85, 0x42f0, {0xab, 0xa9, 0xfb, 0x4b, 0xfd, 0x69, 0xf5, 0xab}};
EFI_GUID gUefiInfoEfiBluetoothLeConfigProtocolGuid                        = {0x8f76da58, 0x1f99, 0x4275, {0xa4, 0xec, 0x47, 0x56, 0x51, 0x5b, 0x1c, 0xe8}};
EFI_GUID gUefiInfoEfiBoardFeaturesGuid                                    = {0x94b9e8ae, 0x8877, 0x479a, {0x98, 0x42, 0xf5, 0x97, 0x4b, 0x82, 0xce, 0xd3}};
EFI_GUID gUefiInfoEfiBootLogoProtocolGuid                                 = {0xcdea2bd3, 0xfc25, 0x4c1c, {0xb9, 0x7c, 0xb3, 0x11, 0x86, 0x06, 0x49, 0x90}};
EFI_GUID gUefiInfoEfiBootManagerPolicyConnectAllGuid                      = {0x113b2126, 0xfc8a, 0x11e3, {0xbd, 0x6c, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa}};
EFI_GUID gUefiInfoEfiBootManagerPolicyConsoleGuid                         = {0xcab0e94c, 0xe15f, 0x11e3, {0x91, 0x8d, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa}};
EFI_GUID gUefiInfoEfiBootManagerPolicyNetworkGuid                         = {0xd04159dc, 0xe15f, 0x11e3, {0xb2, 0x61, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa}};
EFI_GUID gUefiInfoEfiBootManagerPolicyProtocolGuid                        = {0xfedf8e0c, 0xe147, 0x11e3, {0x99, 0x03, 0xb8, 0xe8, 0x56, 0x2c, 0xba, 0xfa}};
EFI_GUID gUefiInfoEfiBootScriptExecutorContextGuid                        = {0x79cb58c4, 0xac51, 0x442f, {0xaf, 0xd7, 0x98, 0xe4, 0x7d, 0x2e, 0x99, 0x08}};
EFI_GUID gUefiInfoEfiBootScriptExecutorVariableGuid                       = {0x3079818c, 0x46d4, 0x4a73, {0xae, 0xf3, 0xe3, 0xe4, 0x6c, 0xf1, 0xee, 0xdb}};
EFI_GUID gUefiInfoEfiBootScriptSaveProtocolGuid                           = {0x470e1529, 0xb79e, 0x4e32, {0xa0, 0xfe, 0x6a, 0x15, 0x6d, 0x29, 0xf9, 0xb2}};
EFI_GUID gUefiInfoEfiBootStateGuid                                        = {0x60b5e939, 0x0fcf, 0x4227, {0xba, 0x83, 0x6b, 0xbe, 0xd4, 0x5b, 0xc0, 0xe3}};
EFI_GUID gUefiInfoEfiBttAbstractionGuid                                   = {0x18633bfc, 0x1735, 0x4217, {0x8a, 0xc9, 0x17, 0x23, 0x92, 0x82, 0xd3, 0xf8}};
EFI_GUID gUefiInfoEfiBusSpecificDriverOverrideProtocolGuid                = {0x3bc1b285, 0x8a15, 0x4a82, {0xaa, 0xbf, 0x4d, 0x7d, 0x13, 0xfb, 0x32, 0x65}};
EFI_GUID gUefiInfoEfiCacheSubClassGuid                                    = {0x7f0013a7, 0xdc79, 0x4b22, {0x80, 0x99, 0x11, 0xf7, 0x5f, 0xdc, 0x82, 0x9d}};
EFI_GUID gUefiInfoEfiCapsuleArchProtocolGuid                              = {0x5053697e, 0x2cbc, 0x4819, {0x90, 0xd9, 0x05, 0x80, 0xde, 0xee, 0x57, 0x54}};
EFI_GUID gUefiInfoEfiCapsuleCrashGuid                                     = {0x0e1d2972, 0x65af, 0x4ac1, {0xbf, 0xa3, 0xce, 0xf4, 0xab, 0x0c, 0x38, 0xfe}};
EFI_GUID gUefiInfoEfiCapsuleCrashLogVarGuid                               = {0xf3ff1468, 0x04ba, 0x4966, {0x9f, 0xb2, 0xe4, 0xa7, 0x90, 0x05, 0x46, 0x50}};
EFI_GUID gUefiInfoEfiCapsuleGuid                                          = {0x3b6686bd, 0x0d76, 0x4030, {0xb7, 0x0e, 0xb5, 0x51, 0x9e, 0x2f, 0xc5, 0xa0}};
EFI_GUID gUefiInfoEfiCapsuleReportGuid                                    = {0x39b68c46, 0xf7fb, 0x441b, {0xb6, 0xec, 0x16, 0xb0, 0xf6, 0x98, 0x21, 0xf3}};
EFI_GUID gUefiInfoEfiCapsuleVendorGuid                                    = {0x711c703f, 0xc285, 0x4b10, {0xa3, 0xb0, 0x36, 0xec, 0xbd, 0x3c, 0x8b, 0xe2}};
EFI_GUID gUefiInfoEfiCardInfoProtocolGuid                                 = {0x85c1f7d2, 0xbce6, 0x4f31, {0x8f, 0x4d, 0xd3, 0x7e, 0x03, 0xd0, 0x5e, 0xaa}};
EFI_GUID gUefiInfoEfiCertDbGuid                                           = {0xd9bee56e, 0x75dc, 0x49d9, {0xb4, 0xd7, 0xb5, 0x34, 0x21, 0x0f, 0x63, 0x7a}};
EFI_GUID gUefiInfoEfiCertExternalManagementGuid                           = {0x452e8ced, 0xdfff, 0x4b8c, {0xae, 0x01, 0x51, 0x18, 0x86, 0x2e, 0x68, 0x2c}};
EFI_GUID gUefiInfoEfiCertPkcs7Guid                                        = {0x4aafd29d, 0x68df, 0x49ee, {0x8a, 0xa9, 0x34, 0x7d, 0x37, 0x56, 0x65, 0xa7}};
EFI_GUID gUefiInfoEfiCertRsa2048Guid                                      = {0x3c5766e8, 0x269c, 0x4e34, {0xaa, 0x14, 0xed, 0x77, 0x6e, 0x85, 0xb3, 0xb6}};
EFI_GUID gUefiInfoEfiCertRsa2048Sha1Guid                                  = {0x67f8444f, 0x8743, 0x48f1, {0xa3, 0x28, 0x1e, 0xaa, 0xb8, 0x73, 0x60, 0x80}};
EFI_GUID gUefiInfoEfiCertRsa2048Sha256Guid                                = {0xe2b36190, 0x879b, 0x4a3d, {0xad, 0x8d, 0xf2, 0xe7, 0xbb, 0xa3, 0x27, 0x84}};
EFI_GUID gUefiInfoEfiCertSha1Guid                                         = {0x826ca512, 0xcf10, 0x4ac9, {0xb1, 0x87, 0xbe, 0x01, 0x49, 0x66, 0x31, 0xbd}};
EFI_GUID gUefiInfoEfiCertSha224Guid                                       = {0x0b6e5233, 0xa65c, 0x44c9, {0x94, 0x07, 0xd9, 0xab, 0x83, 0xbf, 0xc8, 0xbd}};
EFI_GUID gUefiInfoEfiCertSha256Guid                                       = {0xc1c41626, 0x504c, 0x4092, {0xac, 0xa9, 0x41, 0xf9, 0x36, 0x93, 0x43, 0x28}};
EFI_GUID gUefiInfoEfiCertSha384Guid                                       = {0xff3e5307, 0x9fd0, 0x48c9, {0x85, 0xf1, 0x8a, 0xd5, 0x6c, 0x70, 0x1e, 0x01}};
EFI_GUID gUefiInfoEfiCertSha512Guid                                       = {0x093e0fae, 0xa6c4, 0x4f50, {0x9f, 0x1b, 0xd4, 0x1e, 0x2b, 0x89, 0xc1, 0x9a}};
EFI_GUID gUefiInfoEfiCertTypePkcs7Guid                                    = {0x4aafd29d, 0x68df, 0x49ee, {0x8a, 0xa9, 0x34, 0x7d, 0x37, 0x56, 0x65, 0xa7}};
EFI_GUID gUefiInfoEfiCertTypeRsa2048Sha256Guid                            = {0xa7717414, 0xc616, 0x4977, {0x94, 0x20, 0x84, 0x47, 0x12, 0xa7, 0x35, 0xbf}};
EFI_GUID gUefiInfoEfiCertX509Guid                                         = {0xa5c059a1, 0x94e4, 0x4aa7, {0x87, 0xb5, 0xab, 0x15, 0x5c, 0x2b, 0xf0, 0x72}};
EFI_GUID gUefiInfoEfiCertX509Sha256Guid                                   = {0x3bd2a492, 0x96c0, 0x4079, {0xb4, 0x20, 0xfc, 0xf9, 0x8e, 0xf1, 0x03, 0xed}};
EFI_GUID gUefiInfoEfiCertX509Sha384Guid                                   = {0x7076876e, 0x80c2, 0x4ee6, {0xaa, 0xd2, 0x28, 0xb3, 0x49, 0xa6, 0x86, 0x5b}};
EFI_GUID gUefiInfoEfiCertX509Sha512Guid                                   = {0x446dbf63, 0x2502, 0x4cda, {0xbc, 0xfa, 0x24, 0x65, 0xd2, 0xb0, 0xfe, 0x9d}};
EFI_GUID gUefiInfoEfiCk505ClockPlatformInfoGuid                           = {0x3c485ea4, 0x449a, 0x46ce, {0xbb, 0x08, 0x2a, 0x33, 0x6e, 0xa9, 0x6b, 0x4e}};
EFI_GUID gUefiInfoEfiComponentName2ProtocolGuid                           = {0x6a7a5cff, 0xe8d9, 0x4f70, {0xba, 0xda, 0x75, 0xab, 0x30, 0x25, 0xce, 0x14}};
EFI_GUID gUefiInfoEfiComponentNameProtocolGuid                            = {0x107a772c, 0xd5e1, 0x11d4, {0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiConfigFileNameGuid                                   = {0x98b8d59b, 0xe8ba, 0x48ee, {0x98, 0xdd, 0xc2, 0x95, 0x39, 0x2f, 0x1e, 0xdb}};
EFI_GUID gUefiInfoEfiConfigKeywordHandlerProtocolGuid                     = {0x0a8badd5, 0x03b8, 0x4d19, {0xb1, 0x28, 0x7b, 0x8f, 0x0e, 0xda, 0xa5, 0x96}};
EFI_GUID gUefiInfoEfiConsoleInDeviceGuid                                  = {0xd3b36f2b, 0xd551, 0x11d4, {0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiConsoleOutDeviceGuid                                 = {0xd3b36f2c, 0xd551, 0x11d4, {0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiCPTokenSpaceGuid                                     = {0x918211ce, 0xa1d2, 0x43a0, {0xa0, 0x4e, 0x75, 0xb5, 0xbf, 0x44, 0x50, 0x0e}};
EFI_GUID gUefiInfoEfiCpuArchProtocolGuid                                  = {0x26baccb1, 0x6f42, 0x11d4, {0xbc, 0xe7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiCpuIo2ProtocolGuid                                   = {0xad61f191, 0xae5f, 0x4c0e, {0xb9, 0xfa, 0xe8, 0x69, 0xd2, 0x88, 0xc6, 0x4f}};
EFI_GUID gUefiInfoEfiCpuIoProtocolGuid                                    = {0xb0732526, 0x38c8, 0x4b40, {0x88, 0x77, 0x61, 0xc7, 0xb0, 0x6a, 0xac, 0x45}};
EFI_GUID gUefiInfoEfiCrc32GuidedSectionExtractionGuid                     = {0xfc1bcdb0, 0x7d31, 0x49aa, {0x93, 0x6a, 0xa4, 0x60, 0x0d, 0x9d, 0xd0, 0x83}};
EFI_GUID gUefiInfoEfiCustomModeEnableGuid                                 = {0xc076ec0c, 0x7028, 0x4399, {0xa0, 0x72, 0x71, 0xee, 0x5c, 0x44, 0x8b, 0x9f}};
EFI_GUID gUefiInfoEfiDataHubProtocolGuid                                  = {0xae80d021, 0x618e, 0x11d4, {0xbc, 0xd7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiDataHubStatusCodeRecordGuid                          = {0xd083e94c, 0x6560, 0x42e4, {0xb6, 0xd4, 0x2d, 0xf7, 0x5a, 0xdf, 0x6a, 0x2a}};
EFI_GUID gUefiInfoEfiDebugAgentGuid                                       = {0x865a5a9b, 0xb85d, 0x474c, {0x84, 0x55, 0x65, 0xd1, 0xbe, 0x84, 0x4b, 0xe2}};
EFI_GUID gUefiInfoEfiDebugImageInfoTableGuid                              = {0x49152e77, 0x1ada, 0x4764, {0xb7, 0xa2, 0x7a, 0xfe, 0xfe, 0xd9, 0x5e, 0x8b}};
EFI_GUID gUefiInfoEfiDebugMaskProtocolGuid                                = {0x4c8a2451, 0xc207, 0x405b, {0x96, 0x94, 0x99, 0xea, 0x13, 0x25, 0x13, 0x41}};
EFI_GUID gUefiInfoEfiDebugPortDevicePathGuid                              = {0xeba4e8d2, 0x3858, 0x41ec, {0xa2, 0x81, 0x26, 0x47, 0xba, 0x96, 0x60, 0xd0}};
EFI_GUID gUefiInfoEfiDebugPortProtocolGuid                                = {0xeba4e8d2, 0x3858, 0x41ec, {0xa2, 0x81, 0x26, 0x47, 0xba, 0x96, 0x60, 0xd0}};
EFI_GUID gUefiInfoEfiDebugportProtocolGuid                                = {0xeba4e8d2, 0x3858, 0x41ec, {0xa2, 0x81, 0x26, 0x47, 0xba, 0x96, 0x60, 0xd0}};
EFI_GUID gUefiInfoEfiDebugPortVariableGuid                                = {0xeba4e8d2, 0x3858, 0x41ec, {0xa2, 0x81, 0x26, 0x47, 0xba, 0x96, 0x60, 0xd0}};
EFI_GUID gUefiInfoEfiDebugSupportPeriodicCallbackProtocolGuid             = {0x9546e07c, 0x2cbb, 0x4c88, {0x98, 0x6c, 0xcd, 0x34, 0x10, 0x86, 0xf0, 0x44}};
EFI_GUID gUefiInfoEfiDebugSupportProtocolGuid                             = {0x2755590c, 0x6f3c, 0x42fa, {0x9e, 0xa4, 0xa3, 0xba, 0x54, 0x3c, 0xda, 0x25}};
EFI_GUID gUefiInfoEfiDecompressProtocolGuid                               = {0xd8117cfe, 0x94a6, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiDeferredImageLoadProtocolGuid                        = {0x15853d7c, 0x3ddf, 0x43e0, {0xa1, 0xcb, 0xeb, 0xf8, 0x5b, 0x8f, 0x87, 0x2c}};
EFI_GUID gUefiInfoEfiDeviceIoProtocolGuid                                 = {0xaf6ac311, 0x84c3, 0x11d2, {0x8e, 0x3c, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiDevicePathFromTextProtocolGuid                       = {0x05c99a21, 0xc70f, 0x4ad2, {0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e}};
EFI_GUID gUefiInfoEfiDevicePathProtocolGuid                               = {0x09576e91, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiDevicePathToTextProtocolGuid                         = {0x8b843e20, 0x8132, 0x4852, {0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c}};
EFI_GUID gUefiInfoEfiDevicePathUtilitiesProtocolGuid                      = {0x0379be4e, 0xd706, 0x437d, {0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4}};
EFI_GUID gUefiInfoEfiDFUResultGuid                                        = {0x14a7c46f, 0xbc02, 0x4047, {0x9f, 0x18, 0xa5, 0xd7, 0x25, 0xd8, 0xbd, 0x19}};
EFI_GUID gUefiInfoEfiDFUVerGuid                                           = {0x0dc73aed, 0xcbf6, 0x4a25, {0xa6, 0x8d, 0x59, 0xc8, 0x0f, 0x44, 0xc7, 0xc3}};
EFI_GUID gUefiInfoEfiDhcp4ProtocolGuid                                    = {0x8a219718, 0x4ef5, 0x4761, {0x91, 0xc8, 0xc0, 0xf0, 0x4b, 0xda, 0x9e, 0x56}};
EFI_GUID gUefiInfoEfiDhcp4ServiceBindingProtocolGuid                      = {0x9d9a39d8, 0xbd42, 0x4a73, {0xa4, 0xd5, 0x8e, 0xe9, 0x4b, 0xe1, 0x13, 0x80}};
EFI_GUID gUefiInfoEfiDhcp6ProtocolGuid                                    = {0x87c8bad7, 0x0595, 0x4053, {0x82, 0x97, 0xde, 0xde, 0x39, 0x5f, 0x5d, 0x5b}};
EFI_GUID gUefiInfoEfiDhcp6ServiceBindingProtocolGuid                      = {0x9fb9a8a1, 0x2f4a, 0x43a6, {0x88, 0x9c, 0xd0, 0xf7, 0xb6, 0xc4, 0x7a, 0xd5}};
EFI_GUID gUefiInfoEfiDirectedIoDMArErrorSectionGuid                       = {0x71761d37, 0x32b2, 0x45cd, {0xa7, 0xd0, 0xb0, 0xfe, 0xdd, 0x93, 0xe8, 0xcf}};
EFI_GUID gUefiInfoEfiDiskInfoAhciInterfaceGuid                            = {0x9e498932, 0x4abc, 0x45af, {0xa3, 0x4d, 0x02, 0x47, 0x78, 0x7b, 0xe7, 0xc6}};
EFI_GUID gUefiInfoEfiDiskInfoIdeInterfaceGuid                             = {0x5e948fe3, 0x26d3, 0x42b5, {0xaf, 0x17, 0x61, 0x02, 0x87, 0x18, 0x8d, 0xec}};
EFI_GUID gUefiInfoEfiDiskInfoProtocolGuid                                 = {0xd432a67f, 0x14dc, 0x484b, {0xb3, 0xbb, 0x3f, 0x02, 0x91, 0x84, 0x93, 0x27}};
EFI_GUID gUefiInfoEfiDiskInfoScsiInterfaceGuid                            = {0x08f74baa, 0xea36, 0x41d9, {0x95, 0x21, 0x21, 0xa7, 0x0f, 0x87, 0x80, 0xbc}};
EFI_GUID gUefiInfoEfiDiskInfoUsbInterfaceGuid                             = {0xcb871572, 0xc11a, 0x47b5, {0xb4, 0x92, 0x67, 0x5e, 0xaf, 0xa7, 0x77, 0x27}};
EFI_GUID gUefiInfoEfiDiskIo2ProtocolGuid                                  = {0x151c8eae, 0x7f2c, 0x472c, {0x9e, 0x54, 0x98, 0x28, 0x19, 0x4f, 0x6a, 0x88}};
EFI_GUID gUefiInfoEfiDiskIoProtocolGuid                                   = {0xce345171, 0xba0b, 0x11d2, {0x8e, 0x4f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiDMArGenericErrorSectionGuid                          = {0x5b51fef7, 0xc79d, 0x4434, {0x8f, 0x1b, 0xaa, 0x62, 0xde, 0x3e, 0x2c, 0x64}};
EFI_GUID gUefiInfoEfiDns4ProtocolGuid                                     = {0xae3d28cc, 0xe05b, 0x4fa1, {0xa0, 0x11, 0x7e, 0xb5, 0x5a, 0x3f, 0x14, 0x01}};
EFI_GUID gUefiInfoEfiDns4ServiceBindingProtocolGuid                       = {0xb625b186, 0xe063, 0x44f7, {0x89, 0x05, 0x6a, 0x74, 0xdc, 0x6f, 0x52, 0xb4}};
EFI_GUID gUefiInfoEfiDns6ProtocolGuid                                     = {0xca37bc1f, 0xa327, 0x4ae9, {0x82, 0x8a, 0x8c, 0x40, 0xd8, 0x50, 0x6a, 0x17}};
EFI_GUID gUefiInfoEfiDns6ServiceBindingProtocolGuid                       = {0x7f1647c8, 0xb76e, 0x44b2, {0xa5, 0x65, 0xf7, 0x0f, 0xf1, 0x9c, 0xd1, 0x9e}};
EFI_GUID gUefiInfoEfiDpcProtocolGuid                                      = {0x480f8ae9, 0x0c46, 0x4aa9, {0xbc, 0x89, 0xdb, 0x9f, 0xba, 0x61, 0x98, 0x06}};
EFI_GUID gUefiInfoEfiDriverBindingProtocolGuid                            = {0x18a031ab, 0xb443, 0x4d1a, {0xa5, 0xc0, 0x0c, 0x09, 0x26, 0x1e, 0x9f, 0x71}};
EFI_GUID gUefiInfoEfiDriverConfiguration2ProtocolGuid                     = {0xbfd7dc1d, 0x24f1, 0x40d9, {0x82, 0xe7, 0x2e, 0x09, 0xbb, 0x6b, 0x4e, 0xbe}};
EFI_GUID gUefiInfoEfiDriverConfigurationProtocolGuid                      = {0x107a772b, 0xd5e1, 0x11d4, {0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiDriverDiagnostics2ProtocolGuid                       = {0x4d330321, 0x025f, 0x4aac, {0x90, 0xd8, 0x5e, 0xd9, 0x00, 0x17, 0x3b, 0x63}};
EFI_GUID gUefiInfoEfiDriverDiagnosticsProtocolGuid                        = {0x0784924f, 0xe296, 0x11d4, {0x9a, 0x49, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiDriverFamilyOverrideProtocolGuid                     = {0xb1ee129e, 0xda36, 0x4181, {0x91, 0xf8, 0x04, 0xa4, 0x92, 0x37, 0x66, 0xa7}};
EFI_GUID gUefiInfoEfiDriverHealthProtocolGuid                             = {0x2a534210, 0x9280, 0x41d8, {0xae, 0x79, 0xca, 0xda, 0x01, 0xa2, 0xb1, 0x27}};
EFI_GUID gUefiInfoEfiDriverSupportedEfiVersionProtocolGuid                = {0x5c198761, 0x16a8, 0x4e69, {0x97, 0x2c, 0x89, 0xd6, 0x79, 0x54, 0xf8, 0x1d}};
EFI_GUID gUefiInfoEfiDxeIplPpiGuid                                        = {0x0ae8ce5d, 0xe448, 0x4437, {0xa8, 0xd7, 0xeb, 0xf5, 0xf1, 0x94, 0xf7, 0x31}};
EFI_GUID gUefiInfoEfiDxeServicesTableGuid                                 = {0x05ad34ba, 0x6f02, 0x4214, {0x95, 0x2e, 0x4d, 0xa0, 0x39, 0x8e, 0x2b, 0xb9}};
EFI_GUID gUefiInfoEfiDxeSmmReadyToLockProtocolGuid                        = {0x60ff8964, 0xe906, 0x41d0, {0xaf, 0xed, 0xf2, 0x41, 0xe9, 0x74, 0xe0, 0x8e}};
EFI_GUID gUefiInfoEfiEapConfigurationProtocolGuid                         = {0xe5b58dbb, 0x7688, 0x44b4, {0x97, 0xbf, 0x5f, 0x1d, 0x4b, 0x7c, 0xc8, 0xdb}};
EFI_GUID gUefiInfoEfiEapManagement2ProtocolGuid                           = {0x5e93c847, 0x456d, 0x40b3, {0xa6, 0xb4, 0x78, 0xb0, 0xc9, 0xcf, 0x7f, 0x20}};
EFI_GUID gUefiInfoEfiEapManagementProtocolGuid                            = {0xbb62e663, 0x625d, 0x40b2, {0xa0, 0x88, 0xbb, 0xe8, 0x36, 0x23, 0xa2, 0x45}};
EFI_GUID gUefiInfoEfiEapProtocolGuid                                      = {0x5d9f96db, 0xe731, 0x4caa, {0xa0, 0x0d, 0x72, 0xe1, 0x87, 0xcd, 0x77, 0x62}};
EFI_GUID gUefiInfoEfiEbcProtocolGuid                                      = {0x13ac6dd1, 0x73d0, 0x11d4, {0xb0, 0x6b, 0x00, 0xaa, 0x00, 0xbd, 0x6d, 0xe7}};
EFI_GUID gUefiInfoEfiEbcSimpleDebuggerProtocolGuid                        = {0x2a72d11e, 0x7376, 0x40f6, {0x9c, 0x68, 0x23, 0xfa, 0x2f, 0xe3, 0x63, 0xf1}};
EFI_GUID gUefiInfoEfiEbcVmTestProtocolGuid                                = {0xaaeaccfd, 0xf27b, 0x4c17, {0xb6, 0x10, 0x75, 0xca, 0x1f, 0x2d, 0xfb, 0x52}};
EFI_GUID gUefiInfoEfiEblAddCommandProtocolGuid                            = {0xaeda2428, 0x9a22, 0x4637, {0x9b, 0x21, 0x54, 0x5e, 0x28, 0xfb, 0xb8, 0x29}};
EFI_GUID gUefiInfoEfiEdidActiveProtocolGuid                               = {0xbd8c1056, 0x9f36, 0x44ec, {0x92, 0xa8, 0xa6, 0x33, 0x7f, 0x81, 0x79, 0x86}};
EFI_GUID gUefiInfoEfiEdidDiscoveredProtocolGuid                           = {0x1c0c34f6, 0xd380, 0x41fa, {0xa0, 0x49, 0x8a, 0xd0, 0x6c, 0x1a, 0x66, 0xaa}};
EFI_GUID gUefiInfoEfiEdidOverrideProtocolGuid                             = {0x48ecb431, 0xfb72, 0x45c0, {0xa9, 0x22, 0xf4, 0x58, 0xfe, 0x04, 0x0b, 0xd5}};
EFI_GUID gUefiInfoEfiEdkCompatibilityPkgTokenSpaceGuid                    = {0x2354d320, 0x3eb3, 0x4c81, {0x99, 0xf4, 0xcc, 0x4a, 0xe1, 0x43, 0x46, 0x3e}};
EFI_GUID gUefiInfoEfiEmmcCardInfoProtocolGuid                             = {0x1ebe5ab9, 0x2129, 0x49e7, {0x84, 0xd7, 0xee, 0xb9, 0xfc, 0xe5, 0xde, 0xdd}};
EFI_GUID gUefiInfoEfiEmmcEraseProtocolGuid                                = {0x913620ed, 0x08ea, 0x4ac0, {0x8b, 0xba, 0xd8, 0x8a, 0x9d, 0xaa, 0xb7, 0x51}};
EFI_GUID gUefiInfoEfiEmmcUserPartitionProtocolGuid                        = {0xb615f1f5, 0x5088, 0x43cd, {0x80, 0x9c, 0xa1, 0x6e, 0x52, 0x48, 0x7d, 0x00}};
EFI_GUID gUefiInfoEfiEndOfDxeEventGroupGuid                               = {0x02ce967a, 0xdd7e, 0x4ffc, {0x9e, 0xe7, 0x81, 0x0c, 0xf0, 0x47, 0x08, 0x80}};
EFI_GUID gUefiInfoEfiEndOfPeiSignalPpiGuid                                = {0x605ea650, 0xc65c, 0x42e1, {0xba, 0x80, 0x91, 0xa5, 0x2a, 0xb6, 0x18, 0xc6}};
EFI_GUID gUefiInfoEfiEraseBlockProtocolGuid                               = {0x95a9a93e, 0xa86e, 0x4926, {0xaa, 0xef, 0x99, 0x18, 0xe7, 0x72, 0xd9, 0x87}};
EFI_GUID gUefiInfoEfiEsrtOperationProtocolGuid                            = {0x4549ab47, 0x6e60, 0x4293, {0xb9, 0x1d, 0x31, 0xb6, 0x10, 0xad, 0x80, 0x56}};
EFI_GUID gUefiInfoEfiEventDxeDispatchGuid                                 = {0x7081e22f, 0xcac6, 0x4053, {0x94, 0x68, 0x67, 0x57, 0x82, 0xcf, 0x88, 0xe5}};
EFI_GUID gUefiInfoEfiEventExitBootServicesGuid                            = {0x27abf055, 0xb1b8, 0x4c26, {0x80, 0x48, 0x74, 0x8f, 0x37, 0xba, 0xa2, 0xdf}};
EFI_GUID gUefiInfoEfiEventLegacyBootGuid                                  = {0x2a571201, 0x4966, 0x47f6, {0x8b, 0x86, 0xf3, 0x1e, 0x41, 0xf3, 0x2f, 0x10}};
EFI_GUID gUefiInfoEfiEventMemoryMapChangeGuid                             = {0x78bee926, 0x692f, 0x48fd, {0x9e, 0xdb, 0x01, 0x42, 0x2e, 0xf0, 0xd7, 0xab}};
EFI_GUID gUefiInfoEfiEventNotificationTypeBootGuid                        = {0x3d61a466, 0xab40, 0x409a, {0xa6, 0x98, 0xf3, 0x62, 0xd4, 0x64, 0xb3, 0x8f}};
EFI_GUID gUefiInfoEfiEventNotificationTypeCmcGuid                         = {0x2dce8bb1, 0xbdd7, 0x450e, {0xb9, 0xad, 0x9c, 0xf4, 0xeb, 0xd4, 0xf8, 0x90}};
EFI_GUID gUefiInfoEfiEventNotificationTypeCpeGuid                         = {0x4e292f96, 0xd843, 0x4a55, {0xa8, 0xc2, 0xd4, 0x81, 0xf2, 0x7e, 0xbe, 0xee}};
EFI_GUID gUefiInfoEfiEventNotificationTypeDmarGuid                        = {0x667dd791, 0xc6b3, 0x4c27, {0x8a, 0x6b, 0x0f, 0x8e, 0x72, 0x2d, 0xeb, 0x41}};
EFI_GUID gUefiInfoEfiEventNotificationTypeInitGuid                        = {0xcc5263e8, 0x9308, 0x454a, {0x89, 0xd0, 0x34, 0x0b, 0xd3, 0x9b, 0xc9, 0x8e}};
EFI_GUID gUefiInfoEfiEventNotificationTypeMceGuid                         = {0xe8f56ffe, 0x919c, 0x4cc5, {0xba, 0x88, 0x65, 0xab, 0xe1, 0x49, 0x13, 0xbb}};
EFI_GUID gUefiInfoEfiEventNotificationTypeNmiGuid                         = {0x5bad89ff, 0xb7e6, 0x42c9, {0x81, 0x4a, 0xcf, 0x24, 0x85, 0xd6, 0xe9, 0x8a}};
EFI_GUID gUefiInfoEfiEventNotificationTypePcieGuid                        = {0xcf93c01f, 0x1a16, 0x4dfc, {0xb8, 0xbc, 0x9c, 0x4d, 0xaf, 0x67, 0xc1, 0x04}};
EFI_GUID gUefiInfoEfiEventReadyToBootGuid                                 = {0x7ce88fb3, 0x4bd7, 0x4679, {0x87, 0xa8, 0xa8, 0xd8, 0xde, 0xe5, 0x0d, 0x2b}};
EFI_GUID gUefiInfoEfiEventUserProfileChangedGuid                          = {0xbaf1e6de, 0x209e, 0x4adb, {0x8d, 0x96, 0xfd, 0x8b, 0x71, 0xf3, 0xf6, 0x83}};
EFI_GUID gUefiInfoEfiEventVirtualAddressChangeGuid                        = {0x13fa7698, 0xc831, 0x49c7, {0x87, 0xea, 0x8f, 0x43, 0xfc, 0xc2, 0x51, 0x96}};
EFI_GUID gUefiInfoEfiExtendedSalBaseIoServicesProtocolGuid                = {0x5aea42b5, 0x31e1, 0x4515, {0xbc, 0x31, 0xb8, 0xd5, 0x25, 0x75, 0x65, 0xa6}};
EFI_GUID gUefiInfoEfiExtendedSalBaseServicesProtocolGuid                  = {0xd9e9fa06, 0x0fe0, 0x41c3, {0x96, 0xfb, 0x83, 0x42, 0x5a, 0x33, 0x94, 0xf8}};
EFI_GUID gUefiInfoEfiExtendedSalBootServiceProtocolGuid                   = {0xde0ee9a4, 0x3c7a, 0x44f2, {0xb7, 0x8b, 0xe3, 0xcc, 0xd6, 0x9c, 0x3a, 0xf7}};
EFI_GUID gUefiInfoEfiExtendedSalCacheServicesProtocolGuid                 = {0x0edc9494, 0x2743, 0x4ba5, {0x88, 0x18, 0x0a, 0xef, 0x52, 0x13, 0xf1, 0x88}};
EFI_GUID gUefiInfoEfiExtendedSalFvBlockServicesProtocolGuid               = {0xa2271df1, 0xbcbb, 0x4f1d, {0x98, 0xa9, 0x06, 0xbc, 0x17, 0x2f, 0x07, 0x1a}};
EFI_GUID gUefiInfoEfiExtendedSalMcaLogServicesProtocolGuid                = {0xcb3fd86e, 0x38a3, 0x4c03, {0x9a, 0x5c, 0x90, 0xcf, 0xa3, 0xa2, 0xab, 0x7a}};
EFI_GUID gUefiInfoEfiExtendedSalMcaServicesProtocolGuid                   = {0x2a591128, 0x6cc7, 0x42b1, {0x8a, 0xf0, 0x58, 0x93, 0x3b, 0x68, 0x2d, 0xbb}};
EFI_GUID gUefiInfoEfiExtendedSalMpServicesProtocolGuid                    = {0x697d81a2, 0xcf18, 0x4dc0, {0x9e, 0x0d, 0x06, 0x11, 0x3b, 0x61, 0x8a, 0x3f}};
EFI_GUID gUefiInfoEfiExtendedSalMtcServicesProtocolGuid                   = {0x899afd18, 0x75e8, 0x408b, {0xa4, 0x1a, 0x6e, 0x2e, 0x7e, 0xcd, 0xf4, 0x54}};
EFI_GUID gUefiInfoEfiExtendedSalPalServicesProtocolGuid                   = {0xe1cd9d21, 0x0fc2, 0x438d, {0x97, 0x03, 0x04, 0xe6, 0x6d, 0x96, 0x1e, 0x57}};
EFI_GUID gUefiInfoEfiExtendedSalPciServicesProtocolGuid                   = {0xa46b1a31, 0xad66, 0x4905, {0x92, 0xf6, 0x2b, 0x46, 0x59, 0xdc, 0x30, 0x63}};
EFI_GUID gUefiInfoEfiExtendedSalResetServicesProtocolGuid                 = {0x7d019990, 0x8ce1, 0x46f5, {0xa7, 0x76, 0x3c, 0x51, 0x98, 0x67, 0x6a, 0xa0}};
EFI_GUID gUefiInfoEfiExtendedSalRtcServicesProtocolGuid                   = {0x7e97a470, 0xefdb, 0x4d02, {0x8f, 0xce, 0x61, 0x90, 0xd2, 0x7b, 0xa2, 0x96}};
EFI_GUID gUefiInfoEfiExtendedSalStallServicesProtocolGuid                 = {0x53a58d06, 0xac27, 0x4d8c, {0xb5, 0xe9, 0xf0, 0x8a, 0x80, 0x65, 0x41, 0x70}};
EFI_GUID gUefiInfoEfiExtendedSalStatusCodeServicesProtocolGuid            = {0x00dbd91d, 0x55e9, 0x420f, {0x96, 0x39, 0x5e, 0x9f, 0x84, 0x37, 0xb4, 0x4f}};
EFI_GUID gUefiInfoEfiExtendedSalVariableServicesProtocolGuid              = {0x4ecb6c53, 0xc641, 0x4370, {0x8c, 0xb2, 0x3b, 0x0e, 0x49, 0x6e, 0x83, 0x78}};
EFI_GUID gUefiInfoEfiExtScsiPassThruProtocolGuid                          = {0x143b7632, 0xb81b, 0x4cb7, {0xab, 0xd3, 0xb6, 0x25, 0xa5, 0xb9, 0xbf, 0xfe}};
EFI_GUID gUefiInfoEfiFaultTolerantWriteProtocolGuid                       = {0x3ebd9e82, 0x2c78, 0x4de6, {0x97, 0x86, 0x8d, 0x4b, 0xfc, 0xb7, 0xc8, 0x81}};
EFI_GUID gUefiInfoEfiFileInfoGuid                                         = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiFileInfoIdGuid                                       = {0x09576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiFileSystemInfoGuid                                   = {0x09576e93, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiFileSystemVolumeLabelInfoIdGuid                      = {0xdb47d7d3, 0xfe81, 0x11d3, {0x9a, 0x35, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiFindFvPpiGuid                                        = {0x36164812, 0xa023, 0x44e5, {0xbd, 0x85, 0x05, 0xbf, 0x3c, 0x77, 0x00, 0xaa}};
EFI_GUID gUefiInfoEfiFirmwareClassGuid                                    = {0xb122a262, 0x3551, 0x4f48, {0x88, 0x92, 0x55, 0xf6, 0xc0, 0x61, 0x42, 0x90}};
EFI_GUID gUefiInfoEfiFirmwareContentsSignedGuid                           = {0x0f9d89e8, 0x9259, 0x4f76, {0xa5, 0xaf, 0x0c, 0x89, 0xe3, 0x40, 0x23, 0xdf}};
EFI_GUID gUefiInfoEfiFirmwareErrorSectionGuid                             = {0x81212a96, 0x09ed, 0x4996, {0x94, 0x71, 0x8d, 0x72, 0x9c, 0x8e, 0x69, 0xed}};
EFI_GUID gUefiInfoEfiFirmwareFileSystem2Guid                              = {0x8c8ce578, 0x8a3d, 0x4f1c, {0x99, 0x35, 0x89, 0x61, 0x85, 0xc3, 0x2d, 0xd3}};
EFI_GUID gUefiInfoEfiFirmwareFileSystem3Guid                              = {0x5473c07a, 0x3dcb, 0x4dca, {0xbd, 0x6f, 0x1e, 0x96, 0x89, 0xe7, 0x34, 0x9a}};
EFI_GUID gUefiInfoEfiFirmwareFileSystemGuid                               = {0x7a9354d9, 0x0468, 0x444a, {0x81, 0xce, 0x0b, 0xf6, 0x17, 0xd8, 0x90, 0xdf}};
EFI_GUID gUefiInfoEfiFirmwareManagementCapsuleIdGuid                      = {0x6dcbd5ed, 0xe82d, 0x4c44, {0xbd, 0xa1, 0x71, 0x94, 0x19, 0x9a, 0xd9, 0x2a}};
EFI_GUID gUefiInfoEfiFirmwareManagementProtocolGuid                       = {0x86c77a67, 0x0b97, 0x4633, {0xa1, 0x87, 0x49, 0x10, 0x4d, 0x06, 0x85, 0xc7}};
EFI_GUID gUefiInfoEfiFirmwarePerformanceGuid                              = {0xc095791a, 0x3001, 0x47b2, {0x80, 0xc9, 0xea, 0xc7, 0x31, 0x9f, 0x2f, 0xa4}};
EFI_GUID gUefiInfoEfiFirmwareVolume2ProtocolGuid                          = {0x220e73b6, 0x6bdb, 0x4413, {0x84, 0x05, 0xb9, 0x74, 0xb1, 0x08, 0x61, 0x9a}};
EFI_GUID gUefiInfoEfiFirmwareVolumeBlock2ProtocolGuid                     = {0x8f644fa9, 0xe850, 0x4db1, {0x9c, 0xe2, 0x0b, 0x44, 0x69, 0x8e, 0x8d, 0xa4}};
EFI_GUID gUefiInfoEfiFirmwareVolumeBlockProtocolGuid                      = {0x8f644fa9, 0xe850, 0x4db1, {0x9c, 0xe2, 0x0b, 0x44, 0x69, 0x8e, 0x8d, 0xa4}};
EFI_GUID gUefiInfoEfiFirmwareVolumeProtocolGuid                           = {0x389f751f, 0x1838, 0x4388, {0x83, 0x90, 0xcd, 0x81, 0x54, 0xbd, 0x27, 0xf8}};
EFI_GUID gUefiInfoEfiFirmwareVolumeTopFileGuid                            = {0x1ba0062e, 0xc779, 0x4582, {0x85, 0x66, 0x33, 0x6a, 0xe8, 0xf7, 0x8f, 0x09}};
EFI_GUID gUefiInfoEfiFlashMapHobGuid                                      = {0xb091e7d2, 0x05a0, 0x4198, {0x94, 0xf0, 0x74, 0xb7, 0xb8, 0xc5, 0x54, 0x59}};
EFI_GUID gUefiInfoEfiFmpCapsuleGuid                                       = {0x6dcbd5ed, 0xe82d, 0x4c44, {0xbd, 0xa1, 0x71, 0x94, 0x19, 0x9a, 0xd9, 0x2a}};
EFI_GUID gUefiInfoEfiFormBrowser2ProtocolGuid                             = {0xb9d4c360, 0xbcfb, 0x4f9b, {0x92, 0x98, 0x53, 0xc1, 0x36, 0x98, 0x22, 0x58}};
EFI_GUID gUefiInfoEfiFormBrowserCompatibilityProtocolGuid                 = {0x0fb7c852, 0xadca, 0x4853, {0x8d, 0x0f, 0xfb, 0xa7, 0x1b, 0x1c, 0xe1, 0x1a}};
EFI_GUID gUefiInfoEfiFormBrowserExProtocolGuid                            = {0x1f73b18d, 0x4630, 0x43c1, {0xa1, 0xde, 0x6f, 0x80, 0x85, 0x5d, 0x7d, 0xa4}};
EFI_GUID gUefiInfoEfiFormBrowserProtocolGuid                              = {0xe5a1333e, 0xe1b4, 0x4d55, {0xce, 0xeb, 0x35, 0xc3, 0xef, 0x13, 0x34, 0x43}};
EFI_GUID gUefiInfoEfiFormCallbackProtocolGuid                             = {0xf3e4543d, 0xcf35, 0x6cef, {0x35, 0xc4, 0x4f, 0xe6, 0x34, 0x4d, 0xfc, 0x54}};
EFI_GUID gUefiInfoEfiFtp4ProtocolGuid                                     = {0xeb338826, 0x681b, 0x4295, {0xb3, 0x56, 0x2b, 0x36, 0x4c, 0x75, 0x7b, 0x09}};
EFI_GUID gUefiInfoEfiFtp4ServiceBindingProtocolGuid                       = {0x0faaecb1, 0x226e, 0x4782, {0xaa, 0xce, 0x7d, 0xb9, 0xbc, 0xbf, 0x4d, 0xaf}};
EFI_GUID gUefiInfoEfiFwDisplayCapsuleGuid                                 = {0x3b8c8162, 0x188c, 0x46a4, {0xae, 0xc9, 0xbe, 0x43, 0xf1, 0xd6, 0x56, 0x97}};
EFI_GUID gUefiInfoEfiGenericMemTestProtocolGuid                           = {0x309de7f1, 0x7f5e, 0x4ace, {0xb4, 0x9c, 0x53, 0x1b, 0xe5, 0xaa, 0x95, 0xef}};
EFI_GUID gUefiInfoEfiGenericVariableGuid                                  = {0x59d1c24f, 0x50f1, 0x401a, {0xb1, 0x01, 0xf3, 0x3e, 0x0d, 0xae, 0xd4, 0x43}};
EFI_GUID gUefiInfoEfiGetPcdInfoPpiGuid                                    = {0xa60c6b59, 0xe459, 0x425d, {0x9c, 0x69, 0x0b, 0xcc, 0x9c, 0xb2, 0x7d, 0x81}};
EFI_GUID gUefiInfoEfiGetPcdInfoProtocolGuid                               = {0xfd0f4478, 0x0efd, 0x461d, {0xba, 0x2d, 0xe5, 0x8c, 0x45, 0xfd, 0x5f, 0x5e}};
EFI_GUID gUefiInfoEfiGlobalNvsAreaProtocolGuid                            = {0x074e1e48, 0x8132, 0x47a1, {0x8c, 0x2c, 0x3f, 0x14, 0xad, 0x9a, 0x66, 0xdc}};
EFI_GUID gUefiInfoEfiGlobalVariableGuid                                   = {0x8be4df61, 0x93ca, 0x11d2, {0xaa, 0x0d, 0x00, 0xe0, 0x98, 0x03, 0x2b, 0x8c}};
EFI_GUID gUefiInfoEfiGopDisplayBrightnessProtocolGuid                     = {0x6ff23f1d, 0x877c, 0x4b1b, {0x93, 0xfc, 0xf1, 0x42, 0xb2, 0xee, 0xa6, 0xa7}};
EFI_GUID gUefiInfoEfiGpioOperationProtocolGuid                            = {0x38ddfe8f, 0x8991, 0x44aa, {0x98, 0x89, 0x83, 0xf4, 0x91, 0x84, 0x65, 0xb0}};
EFI_GUID gUefiInfoEfiGraphicsOutputProtocolGuid                           = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
EFI_GUID gUefiInfoEfiHardwareErrorVariableGuid                            = {0x414e6bdd, 0xe47b, 0x47cc, {0xb2, 0x44, 0xbb, 0x61, 0x02, 0x0c, 0xf5, 0x16}};
EFI_GUID gUefiInfoEfiHash2ProtocolGuid                                    = {0x55b1d734, 0xc5e1, 0x49db, {0x96, 0x47, 0xb1, 0x6a, 0xfb, 0x0e, 0x30, 0x5b}};
EFI_GUID gUefiInfoEfiHash2ServiceBindingProtocolGuid                      = {0xda836f8d, 0x217f, 0x4ca0, {0x99, 0xc2, 0x1c, 0xa4, 0xe1, 0x60, 0x77, 0xea}};
EFI_GUID gUefiInfoEfiHashAlgorithmMD5Guid                                 = {0x0af7c79c, 0x65b5, 0x4319, {0xb0, 0xae, 0x44, 0xec, 0x48, 0x4e, 0x4a, 0xd7}};
EFI_GUID gUefiInfoEfiHashAlgorithmMd5Guid                                 = {0x0af7c79c, 0x65b5, 0x4319, {0xb0, 0xae, 0x44, 0xec, 0x48, 0x4e, 0x4a, 0xd7}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha1Guid                                = {0x2ae9d80f, 0x3fb2, 0x4095, {0xb7, 0xb1, 0xe9, 0x31, 0x57, 0xb9, 0x46, 0xb6}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha1NoPadGuid                           = {0x24c5dc2f, 0x53e2, 0x40ca, {0x9e, 0xd6, 0xa5, 0xd9, 0xa4, 0x9f, 0x46, 0x3b}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha1NopadGuid                           = {0x24c5dc2f, 0x53e2, 0x40ca, {0x9e, 0xd6, 0xa5, 0xd9, 0xa4, 0x9f, 0x46, 0x3b}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha224Guid                              = {0x8df01a06, 0x9bd5, 0x4bf7, {0xb0, 0x21, 0xdb, 0x4f, 0xd9, 0xcc, 0xf4, 0x5b}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha256Guid                              = {0x51aa59de, 0xfdf2, 0x4ea3, {0xbc, 0x63, 0x87, 0x5f, 0xb7, 0x84, 0x2e, 0xe9}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha256NoPadGuid                         = {0x8628752a, 0x6cb7, 0x4814, {0x96, 0xfc, 0x24, 0xa8, 0x15, 0xac, 0x22, 0x26}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha256NopadGuid                         = {0x8628752a, 0x6cb7, 0x4814, {0x96, 0xfc, 0x24, 0xa8, 0x15, 0xac, 0x22, 0x26}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha384Guid                              = {0xefa96432, 0xde33, 0x4dd2, {0xae, 0xe6, 0x32, 0x8c, 0x33, 0xdf, 0x77, 0x7a}};
EFI_GUID gUefiInfoEfiHashAlgorithmSha512Guid                              = {0xcaa4381e, 0x750c, 0x4770, {0xb8, 0x70, 0x7a, 0x23, 0xb4, 0xe4, 0x21, 0x30}};
EFI_GUID gUefiInfoEfiHashProtocolGuid                                     = {0xc5184932, 0xdba5, 0x46db, {0xa5, 0xba, 0xcc, 0x0b, 0xda, 0x9c, 0x14, 0x35}};
EFI_GUID gUefiInfoEfiHashServiceBindingProtocolGuid                       = {0x42881c98, 0xa4f3, 0x44b0, {0xa3, 0x9d, 0xdf, 0xa1, 0x86, 0x67, 0xd8, 0xcd}};
EFI_GUID gUefiInfoEfiHeciProtocolGuid                                     = {0xcfb33810, 0x6e87, 0x4284, {0xb2, 0x03, 0xa6, 0x6a, 0xbe, 0x07, 0xf6, 0xe8}};
EFI_GUID gUefiInfoEfiHiiCompatibilityProtocolGuid                         = {0x5542cce1, 0xdf5c, 0x4d1b, {0xab, 0xca, 0x36, 0x4f, 0x77, 0xd3, 0x99, 0xfb}};
EFI_GUID gUefiInfoEfiHiiConfigAccessProtocolGuid                          = {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85}};
EFI_GUID gUefiInfoEfiHiiConfigRoutingProtocolGuid                         = {0x587e72d7, 0xcc50, 0x4f79, {0x82, 0x09, 0xca, 0x29, 0x1f, 0xc1, 0xa1, 0x0f}};
EFI_GUID gUefiInfoEfiHiiDatabaseProtocolGuid                              = {0xef9fc172, 0xa1b2, 0x4693, {0xb3, 0x27, 0x6d, 0x32, 0xfc, 0x41, 0x60, 0x42}};
EFI_GUID gUefiInfoEfiHiiDriverHealthFormsetGuid                           = {0xf22fc20c, 0x8cf4, 0x45eb, {0x8e, 0x06, 0xad, 0x4e, 0x50, 0xb9, 0x5d, 0xd3}};
EFI_GUID gUefiInfoEfiHiiFontExProtocolGuid                                = {0x849e6875, 0xdb35, 0x4df8, {0xb4, 0x1e, 0xc8, 0xf3, 0x37, 0x18, 0x07, 0x3f}};
EFI_GUID gUefiInfoEfiHiiFontGlyphGeneratorProtocolGuid                    = {0xf7102853, 0x7787, 0x4dc2, {0xa8, 0xa8, 0x21, 0xb5, 0xdd, 0x05, 0xc8, 0x9b}};
EFI_GUID gUefiInfoEfiHiiFontProtocolGuid                                  = {0xe9ca4775, 0x8657, 0x47fc, {0x97, 0xe7, 0x7e, 0xd6, 0x5a, 0x08, 0x43, 0x24}};
EFI_GUID gUefiInfoEfiHiiImageDecoderNamePngGuid                           = {0xaf060190, 0x5e3a, 0x4025, {0xaf, 0xbd, 0xe1, 0xf9, 0x05, 0xbf, 0xaa, 0x4c}};
EFI_GUID gUefiInfoEfiHiiImageDecoderProtocolGuid                          = {0x9e66f251, 0x727c, 0x418c, {0xbf, 0xd6, 0xc2, 0xb4, 0x25, 0x28, 0x18, 0xea}};
EFI_GUID gUefiInfoEfiHiiImageExProtocolGuid                               = {0x1a1241e6, 0x8f19, 0x41a9, {0xbc, 0x0e, 0xe8, 0xef, 0x39, 0xe0, 0x65, 0x46}};
EFI_GUID gUefiInfoEfiHiiImageProtocolGuid                                 = {0x31a6406a, 0x6bdf, 0x4e46, {0xb2, 0xa2, 0xeb, 0xaa, 0x89, 0xc4, 0x09, 0x20}};
EFI_GUID gUefiInfoEfiHiiKeyBoardLayoutGuid                                = {0x14982a4f, 0xb0ed, 0x45b8, {0xa8, 0x11, 0x5a, 0x7a, 0x9b, 0xc2, 0x32, 0xdf}};
EFI_GUID gUefiInfoEfiHiiPackageListProtocolGuid                           = {0x6a1ee763, 0xd47a, 0x43b4, {0xaa, 0xbe, 0xef, 0x1d, 0xe2, 0xab, 0x56, 0xfc}};
EFI_GUID gUefiInfoEfiHiiPlatformSetupFormsetGuid                          = {0x93039971, 0x8545, 0x4b04, {0xb4, 0x5e, 0x32, 0xeb, 0x83, 0x26, 0x04, 0x0e}};
EFI_GUID gUefiInfoEfiHiiPopupProtocolGuid                                 = {0x4311edc0, 0x6054, 0x46d4, {0x9e, 0x40, 0x89, 0x3e, 0xa9, 0x52, 0xfc, 0xcc}};
EFI_GUID gUefiInfoEfiHiiProtocolGuid                                      = {0xd7ad636e, 0xb997, 0x459b, {0xbf, 0x3f, 0x88, 0x46, 0x89, 0x79, 0x80, 0xe1}};
EFI_GUID gUefiInfoEfiHiiRestStyleFormsetGuid                              = {0x790217bd, 0xbecf, 0x485b, {0x91, 0x70, 0x5f, 0xf7, 0x11, 0x31, 0x8b, 0x27}};
EFI_GUID gUefiInfoEfiHiiStandardFormGuid                                  = {0x3bd2f4ec, 0xe524, 0x46e4, {0xa9, 0xd8, 0x51, 0x01, 0x17, 0x42, 0x55, 0x62}};
EFI_GUID gUefiInfoEfiHiiStringProtocolGuid                                = {0x0fd96974, 0x23aa, 0x4cdc, {0xb9, 0xcb, 0x98, 0xd1, 0x77, 0x50, 0x32, 0x2a}};
EFI_GUID gUefiInfoEfiHiiUserCredentialFormsetGuid                         = {0x337f4407, 0x5aee, 0x4b83, {0xb2, 0xa7, 0x4e, 0xad, 0xca, 0x30, 0x88, 0xcd}};
EFI_GUID gUefiInfoEfiHobListGuid                                          = {0x7739f24c, 0x93d7, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiHobMemoryAllocBspStoreGuid                           = {0x564b33cd, 0xc92a, 0x4593, {0x90, 0xbf, 0x24, 0x73, 0xe4, 0x3c, 0x63, 0x22}};
EFI_GUID gUefiInfoEfiHobMemoryAllocModuleGuid                             = {0xf8e21975, 0x0899, 0x4f58, {0xa4, 0xbe, 0x55, 0x25, 0xa9, 0xc6, 0xd7, 0x7a}};
EFI_GUID gUefiInfoEfiHobMemoryAllocStackGuid                              = {0x4ed4bf27, 0x4092, 0x42e9, {0x80, 0x7d, 0x52, 0x7b, 0x1d, 0x00, 0xc9, 0xbd}};
EFI_GUID gUefiInfoEfiHttpBootCallbackProtocolGuid                         = {0xba23b311, 0x343d, 0x11e6, {0x91, 0x85, 0x58, 0x20, 0xb1, 0xd6, 0x52, 0x99}};
EFI_GUID gUefiInfoEfiHttpProtocolGuid                                     = {0x7a59b29b, 0x910b, 0x4171, {0x82, 0x42, 0xa8, 0x5a, 0x0d, 0xf2, 0x5b, 0x5b}};
EFI_GUID gUefiInfoEfiHttpServiceBindingProtocolGuid                       = {0xbdc8e6af, 0xd9bc, 0x4379, {0xa7, 0x2a, 0xe0, 0xc4, 0xe7, 0x5d, 0xae, 0x1c}};
EFI_GUID gUefiInfoEfiHttpUtilitiesProtocolGuid                            = {0x3e35c163, 0x4074, 0x45dd, {0x43, 0x1e, 0x23, 0x98, 0x9d, 0xd8, 0x6b, 0x32}};
EFI_GUID gUefiInfoEfiI2cAcpiProtocolGuid                                  = {0xf30c2915, 0x5782, 0x4e6a, {0xa8, 0x46, 0x05, 0xba, 0xbc, 0xe7, 0xb6, 0xa0}};
EFI_GUID gUefiInfoEfiI2cBusConfigurationManagementProtocol2Guid           = {0x75032015, 0xd156, 0x423e, {0xbf, 0xa3, 0x7a, 0x65, 0xab, 0xa4, 0x71, 0x05}};
EFI_GUID gUefiInfoEfiI2cBusConfigurationManagementProtocolGuid            = {0x55b71fb5, 0x17c6, 0x410e, {0xb5, 0xbd, 0x5f, 0xa2, 0xe3, 0xd4, 0x46, 0x6b}};
EFI_GUID gUefiInfoEfiI2cBusProtocolGuid                                   = {0x9fa1b225, 0x3346, 0x461b, {0xa0, 0x69, 0xed, 0x01, 0xb6, 0x73, 0xd2, 0x40}};
EFI_GUID gUefiInfoEfiI2cEnumerateProtocolGuid                             = {0xda8cd7c4, 0x1c00, 0x49e2, {0x80, 0x3e, 0x52, 0x14, 0xe7, 0x01, 0x89, 0x4c}};
EFI_GUID gUefiInfoEfiI2cHostProtocol2Guid                                 = {0x70b221af, 0xfdff, 0x4fde, {0x99, 0x68, 0x1a, 0xf6, 0x23, 0xa9, 0x56, 0xd9}};
EFI_GUID gUefiInfoEfiI2cHostProtocolGuid                                  = {0xa5aab9e3, 0xc727, 0x48cd, {0x8b, 0xbf, 0x42, 0x72, 0x33, 0x85, 0x49, 0x48}};
EFI_GUID gUefiInfoEfiI2cIoProtocolGuid                                    = {0xb60a3e6b, 0x18c4, 0x46e5, {0xa2, 0x9a, 0xc9, 0xa1, 0x06, 0x65, 0xa2, 0x8e}};
EFI_GUID gUefiInfoEfiI2cMasterProtocol2Guid                               = {0x578c315a, 0x68cf, 0x4e81, {0xb5, 0xc6, 0x22, 0xdb, 0x40, 0xd0, 0x10, 0xbc}};
EFI_GUID gUefiInfoEfiI2cMasterProtocolGuid                                = {0xcd72881f, 0x45b5, 0x4feb, {0x98, 0xc8, 0x31, 0x3d, 0xa8, 0x11, 0x74, 0x62}};
EFI_GUID gUefiInfoEfiI2cSlaveProtocolGuid                                 = {0xf2c1910e, 0xf5c9, 0x4b72, {0xb2, 0x43, 0x6d, 0x59, 0x09, 0x6a, 0x79, 0xf0}};
EFI_GUID gUefiInfoEfiIa32X64ErrorTypeBusCheckGuid                         = {0x1cf3f8b3, 0xc5b1, 0x49a2, {0xaa, 0x59, 0x5e, 0xef, 0x92, 0xff, 0xa6, 0x3c}};
EFI_GUID gUefiInfoEfiIa32X64ErrorTypeCacheCheckGuid                       = {0xa55701f5, 0xe3ef, 0x43de, {0xac, 0x72, 0x24, 0x9b, 0x57, 0x3f, 0xad, 0x2c}};
EFI_GUID gUefiInfoEfiIa32X64ErrorTypeMsCheckGuid                          = {0x48ab7f57, 0xdc34, 0x4f6c, {0xa7, 0xd3, 0xb0, 0xb5, 0xb0, 0xa7, 0x43, 0x14}};
EFI_GUID gUefiInfoEfiIa32X64ErrorTypeTlbCheckGuid                         = {0xfc06b535, 0x5e1f, 0x4562, {0x9f, 0x25, 0x0a, 0x3b, 0x9a, 0xdb, 0x63, 0xc3}};
EFI_GUID gUefiInfoEfiIchInfoProtocolGuid                                  = {0xd31f0400, 0x7d16, 0x4316, {0xbf, 0x88, 0x60, 0x65, 0x88, 0x3b, 0x40, 0x2b}};
EFI_GUID gUefiInfoEfiIchTokenSpaceGuid                                    = {0xe38c11e3, 0x968f, 0x47b8, {0xac, 0xef, 0xac, 0xc0, 0x69, 0x3d, 0xb9, 0xff}};
EFI_GUID gUefiInfoEfiIdeControllerInitProtocolGuid                        = {0xa1e37052, 0x80d9, 0x4e65, {0xa3, 0x17, 0x3e, 0x9a, 0x55, 0xc4, 0x3e, 0xc9}};
EFI_GUID gUefiInfoEfiIfrFrameworkGuid                                     = {0x31ca5d1a, 0xd511, 0x4931, {0xb7, 0x82, 0xae, 0x6b, 0x2b, 0x17, 0x8c, 0xd7}};
EFI_GUID gUefiInfoEfiIfrRefreshIdOpGuid                                   = {0xf5e655d9, 0x02a6, 0x46f2, {0x9e, 0x76, 0xb8, 0xbe, 0x8e, 0x60, 0xab, 0x22}};
EFI_GUID gUefiInfoEfiIfrTianoGuid                                         = {0x0f0b1735, 0x87a0, 0x4193, {0xb2, 0x66, 0x53, 0x8c, 0x38, 0xaf, 0x48, 0xce}};
EFI_GUID gUefiInfoEfiImageSecurityDatabaseGuid                            = {0xd719b2cb, 0x3d3a, 0x4596, {0xa3, 0xbc, 0xda, 0xd0, 0x0e, 0x67, 0x65, 0x6f}};
EFI_GUID gUefiInfoEfiIncompatiblePciDeviceSupportProtocolGuid             = {0xeb23f55a, 0x7863, 0x4ac2, {0x8d, 0x3d, 0x95, 0x65, 0x35, 0xde, 0x03, 0x75}};
EFI_GUID gUefiInfoEfiIntelFrameworkModulePkgTokenSpaceGuid                = {0xd3705011, 0xbc19, 0x4af7, {0xbe, 0x16, 0xf6, 0x80, 0x30, 0x37, 0x8c, 0x15}};
EFI_GUID gUefiInfoEfiIommuDMArErrorSectionGuid                            = {0x036f84e1, 0x7f37, 0x428c, {0xa7, 0x9e, 0x57, 0x5f, 0xdf, 0xaa, 0x84, 0xec}};
EFI_GUID gUefiInfoEfiIp4Config2ProtocolGuid                               = {0x5b446ed1, 0xe30b, 0x4faa, {0x87, 0x1a, 0x36, 0x54, 0xec, 0xa3, 0x60, 0x80}};
EFI_GUID gUefiInfoEfiIp4ConfigProtocolGuid                                = {0x3b95aa31, 0x3793, 0x434b, {0x86, 0x67, 0xc8, 0x07, 0x08, 0x92, 0xe0, 0x5e}};
EFI_GUID gUefiInfoEfiIp4ProtocolGuid                                      = {0x41d94cd2, 0x35b6, 0x455a, {0x82, 0x58, 0xd4, 0xe5, 0x13, 0x34, 0xaa, 0xdd}};
EFI_GUID gUefiInfoEfiIp4ServiceBindingProtocolGuid                        = {0xc51711e7, 0xb4bf, 0x404a, {0xbf, 0xb8, 0x0a, 0x04, 0x8e, 0xf1, 0xff, 0xe4}};
EFI_GUID gUefiInfoEfiIp6ConfigProtocolGuid                                = {0x937fe521, 0x95ae, 0x4d1a, {0x89, 0x29, 0x48, 0xbc, 0xd9, 0x0a, 0xd3, 0x1a}};
EFI_GUID gUefiInfoEfiIp6ProtocolGuid                                      = {0x2c8759d5, 0x5c2d, 0x66ef, {0x92, 0x5f, 0xb6, 0x6c, 0x10, 0x19, 0x57, 0xe2}};
EFI_GUID gUefiInfoEfiIp6ServiceBindingProtocolGuid                        = {0xec835dd3, 0xfe0f, 0x617b, {0xa6, 0x21, 0xb3, 0x50, 0xc3, 0xe1, 0x33, 0x88}};
EFI_GUID gUefiInfoEfiIpSec2ProtocolGuid                                   = {0xa3979e64, 0xace8, 0x4ddc, {0xbc, 0x07, 0x4d, 0x66, 0xb8, 0xfd, 0x09, 0x77}};
EFI_GUID gUefiInfoEfiIpSecConfigProtocolGuid                              = {0xce5e5929, 0xc7a3, 0x4602, {0xad, 0x9e, 0xc9, 0xda, 0xf9, 0x4e, 0xbf, 0xcf}};
EFI_GUID gUefiInfoEfiIpSecProtocolGuid                                    = {0xdfb386f7, 0xe100, 0x43ad, {0x9c, 0x9a, 0xed, 0x90, 0xd0, 0x8a, 0x5e, 0x12}};
EFI_GUID gUefiInfoEfiIsaAcpiProtocolGuid                                  = {0x64a892dc, 0x5561, 0x4536, {0x92, 0xc7, 0x79, 0x9b, 0xfc, 0x18, 0x33, 0x55}};
EFI_GUID gUefiInfoEfiIsaIoProtocolGuid                                    = {0x7ee2bd44, 0x3da0, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiIScsiInitiatorNameProtocolGuid                       = {0x59324945, 0xec44, 0x4c0d, {0xb1, 0xcd, 0x9d, 0xb1, 0x39, 0xdf, 0x07, 0x0c}};
EFI_GUID gUefiInfoEfiJsonCapsuleDataTableGuid                             = {0x35e7a725, 0x8dd2, 0x4cac, {0x80, 0x11, 0x33, 0xcd, 0xa8, 0x10, 0x90, 0x56}};
EFI_GUID gUefiInfoEfiJsonCapsuleIdGuid                                    = {0x67d6f4cd, 0xd6b8, 0x4573, {0xbf, 0x4a, 0xde, 0x5e, 0x25, 0x2d, 0x61, 0xae}};
EFI_GUID gUefiInfoEfiJsonCapsuleResultTableGuid                           = {0xdbc461c3, 0xb3de, 0x422a, {0xb9, 0xb4, 0x98, 0x86, 0xfd, 0x49, 0xa1, 0xe5}};
EFI_GUID gUefiInfoEfiJsonConfigDataTableGuid                              = {0x87367f87, 0x1119, 0x41ce, {0xaa, 0xec, 0x8b, 0xe0, 0x11, 0x1f, 0x55, 0x8a}};
EFI_GUID gUefiInfoEfiKmsFormatAescbc128Guid                               = {0xa0e8ee6a, 0x0e92, 0x44d4, {0x86, 0x1b, 0x0e, 0xaa, 0x4a, 0xca, 0x44, 0xa2}};
EFI_GUID gUefiInfoEfiKmsFormatAescbc256Guid                               = {0xd7e69789, 0x1f68, 0x45e8, {0x96, 0xef, 0x3b, 0x64, 0x07, 0xa5, 0xb2, 0xdc}};
EFI_GUID gUefiInfoEfiKmsFormatAescbc_128Guid                              = {0xa0e8ee6a, 0x0e92, 0x44d4, {0x86, 0x1b, 0x0e, 0xaa, 0x4a, 0xca, 0x44, 0xa2}};
EFI_GUID gUefiInfoEfiKmsFormatAescbc_256Guid                              = {0xd7e69789, 0x1f68, 0x45e8, {0x96, 0xef, 0x3b, 0x64, 0x07, 0xa5, 0xb2, 0xdc}};
EFI_GUID gUefiInfoEfiKmsFormatAesxts128Guid                               = {0x4776e33f, 0xdb47, 0x479a, {0xa2, 0x5f, 0xa1, 0xcd, 0x0a, 0xfa, 0xb3, 0x8b}};
EFI_GUID gUefiInfoEfiKmsFormatAesxts256Guid                               = {0xdc7e8613, 0xc4bb, 0x4db0, {0x84, 0x62, 0x13, 0x51, 0x13, 0x57, 0xab, 0xe2}};
EFI_GUID gUefiInfoEfiKmsFormatAesxts_128Guid                              = {0x4776e33f, 0xdb47, 0x479a, {0xa2, 0x5f, 0xa1, 0xcd, 0x0a, 0xfa, 0xb3, 0x8b}};
EFI_GUID gUefiInfoEfiKmsFormatAesxts_256Guid                              = {0xdc7e8613, 0xc4bb, 0x4db0, {0x84, 0x62, 0x13, 0x51, 0x13, 0x57, 0xab, 0xe2}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric1024Guid                             = {0x43be0b44, 0x874b, 0x4ead, {0xb0, 0x9c, 0x24, 0x1a, 0x4f, 0xbd, 0x7e, 0xb3}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric128Guid                              = {0xec8a3d69, 0x6ddf, 0x4108, {0x94, 0x76, 0x73, 0x37, 0xfc, 0x52, 0x21, 0x36}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric160Guid                              = {0xa3b3e6f8, 0xefca, 0x4bc1, {0x88, 0xfb, 0xcb, 0x87, 0x33, 0x9b, 0x25, 0x79}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric2048Guid                             = {0x40093f23, 0x630c, 0x4626, {0x9c, 0x48, 0x40, 0x37, 0x3b, 0x19, 0xcb, 0xbe}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric256Guid                              = {0x70f64793, 0xc323, 0x4261, {0xac, 0x2c, 0xd8, 0x76, 0xf2, 0x7c, 0x53, 0x45}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric3072Guid                             = {0xb9237513, 0x6c44, 0x4411, {0xa9, 0x90, 0x21, 0xe5, 0x56, 0xe0, 0x5a, 0xde}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric512Guid                              = {0x978fe043, 0xd7af, 0x422e, {0x8a, 0x92, 0x2b, 0x48, 0xe4, 0x63, 0xbd, 0xe6}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_1024Guid                            = {0x43be0b44, 0x874b, 0x4ead, {0xb0, 0x9c, 0x24, 0x1a, 0x4f, 0xbd, 0x7e, 0xb3}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_128Guid                             = {0xec8a3d69, 0x6ddf, 0x4108, {0x94, 0x76, 0x73, 0x37, 0xfc, 0x52, 0x21, 0x36}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_160Guid                             = {0xa3b3e6f8, 0xefca, 0x4bc1, {0x88, 0xfb, 0xcb, 0x87, 0x33, 0x9b, 0x25, 0x79}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_2048Guid                            = {0x40093f23, 0x630c, 0x4626, {0x9c, 0x48, 0x40, 0x37, 0x3b, 0x19, 0xcb, 0xbe}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_256Guid                             = {0x70f64793, 0xc323, 0x4261, {0xac, 0x2c, 0xd8, 0x76, 0xf2, 0x7c, 0x53, 0x45}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_3072Guid                            = {0xb9237513, 0x6c44, 0x4411, {0xa9, 0x90, 0x21, 0xe5, 0x56, 0xe0, 0x5a, 0xde}};
EFI_GUID gUefiInfoEfiKmsFormatGeneric_512Guid                             = {0x978fe043, 0xd7af, 0x422e, {0x8a, 0x92, 0x2b, 0x48, 0xe4, 0x63, 0xbd, 0xe6}};
EFI_GUID gUefiInfoEfiKmsFormatGenericDynamicGuid                          = {0x2156e996, 0x66de, 0x4b27, {0x9c, 0xc9, 0xb0, 0x9f, 0xac, 0x4d, 0x02, 0xbe}};
EFI_GUID gUefiInfoEfiKmsFormatMd2128Guid                                  = {0x78be11c4, 0xee44, 0x4a22, {0x9f, 0x05, 0x03, 0x85, 0x2e, 0xc5, 0xc9, 0x78}};
EFI_GUID gUefiInfoEfiKmsFormatMd2_128Guid                                 = {0x78be11c4, 0xee44, 0x4a22, {0x9f, 0x05, 0x03, 0x85, 0x2e, 0xc5, 0xc9, 0x78}};
EFI_GUID gUefiInfoEfiKmsFormatMd4128Guid                                  = {0xd1c17aa1, 0xcac5, 0x400f, {0xbe, 0x17, 0xe2, 0xa2, 0xae, 0x06, 0x67, 0x7c}};
EFI_GUID gUefiInfoEfiKmsFormatMd4_128Guid                                 = {0xd1c17aa1, 0xcac5, 0x400f, {0xbe, 0x17, 0xe2, 0xa2, 0xae, 0x06, 0x67, 0x7c}};
EFI_GUID gUefiInfoEfiKmsFormatMd5128Guid                                  = {0xdcbc3662, 0x9cda, 0x4b52, {0xa0, 0x4c, 0x82, 0xeb, 0x1d, 0x23, 0x48, 0xc7}};
EFI_GUID gUefiInfoEfiKmsFormatMd5_128Guid                                 = {0xdcbc3662, 0x9cda, 0x4b52, {0xa0, 0x4c, 0x82, 0xeb, 0x1d, 0x23, 0x48, 0xc7}};
EFI_GUID gUefiInfoEfiKmsFormatMd5sha128Guid                               = {0x1c178237, 0x6897, 0x459e, {0x9d, 0x36, 0x67, 0xce, 0x8e, 0xf9, 0x4f, 0x76}};
EFI_GUID gUefiInfoEfiKmsFormatMd5Sha_128Guid                              = {0x1c178237, 0x6897, 0x459e, {0x9d, 0x36, 0x67, 0xce, 0x8e, 0xf9, 0x4f, 0x76}};
EFI_GUID gUefiInfoEfiKmsFormatMdc2128Guid                                 = {0xf7ad60f8, 0xefa8, 0x44a3, {0x91, 0x13, 0x23, 0x1f, 0x39, 0x9e, 0xb4, 0xc7}};
EFI_GUID gUefiInfoEfiKmsFormatMdc2_128Guid                                = {0xf7ad60f8, 0xefa8, 0x44a3, {0x91, 0x13, 0x23, 0x1f, 0x39, 0x9e, 0xb4, 0xc7}};
EFI_GUID gUefiInfoEfiKmsFormatMdc4128Guid                                 = {0x3fa4f847, 0xd8eb, 0x4df4, {0xbd, 0x49, 0x10, 0x3a, 0x0a, 0x84, 0x7b, 0xbc}};
EFI_GUID gUefiInfoEfiKmsFormatMdc4_128Guid                                = {0x3fa4f847, 0xd8eb, 0x4df4, {0xbd, 0x49, 0x10, 0x3a, 0x0a, 0x84, 0x7b, 0xbc}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha11024Guid                             = {0x56417bed, 0x6bbe, 0x4882, {0x86, 0xa0, 0x3a, 0xe8, 0xbb, 0x17, 0xf8, 0xf9}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha12048Guid                             = {0xf66447d4, 0x75a6, 0x463e, {0xa8, 0x19, 0x07, 0x7f, 0x2d, 0xda, 0x05, 0xe9}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha1_1024Guid                            = {0x56417bed, 0x6bbe, 0x4882, {0x86, 0xa0, 0x3a, 0xe8, 0xbb, 0x17, 0xf8, 0xf9}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha1_2048Guid                            = {0xf66447d4, 0x75a6, 0x463e, {0xa8, 0x19, 0x07, 0x7f, 0x2d, 0xda, 0x05, 0xe9}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha2562048Guid                           = {0xa477af13, 0x877d, 0x4060, {0xba, 0xa1, 0x25, 0xd1, 0xbe, 0xa0, 0x8a, 0xd3}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha2563072Guid                           = {0x4e1356c2, 0x0eed, 0x463f, {0x81, 0x47, 0x99, 0x33, 0xab, 0xdb, 0xc7, 0xd5}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha256_2048Guid                          = {0xa477af13, 0x877d, 0x4060, {0xba, 0xa1, 0x25, 0xd1, 0xbe, 0xa0, 0x8a, 0xd3}};
EFI_GUID gUefiInfoEfiKmsFormatRsasha256_3072Guid                          = {0x4e1356c2, 0x0eed, 0x463f, {0x81, 0x47, 0x99, 0x33, 0xab, 0xdb, 0xc7, 0xd5}};
EFI_GUID gUefiInfoEfiKmsFormatSha1160Guid                                 = {0x453c5e5a, 0x482d, 0x43f0, {0x87, 0xc9, 0x59, 0x41, 0xf3, 0xa3, 0x8a, 0xc2}};
EFI_GUID gUefiInfoEfiKmsFormatSha1_160Guid                                = {0x453c5e5a, 0x482d, 0x43f0, {0x87, 0xc9, 0x59, 0x41, 0xf3, 0xa3, 0x8a, 0xc2}};
EFI_GUID gUefiInfoEfiKmsFormatSha256256Guid                               = {0x6bb4f5cd, 0x8022, 0x448d, {0xbc, 0x6d, 0x77, 0x1b, 0xae, 0x93, 0x5f, 0xc6}};
EFI_GUID gUefiInfoEfiKmsFormatSha256_256Guid                              = {0x6bb4f5cd, 0x8022, 0x448d, {0xbc, 0x6d, 0x77, 0x1b, 0xae, 0x93, 0x5f, 0xc6}};
EFI_GUID gUefiInfoEfiKmsFormatSha512512Guid                               = {0x2f240e12, 0xe14d, 0x475c, {0x83, 0xb0, 0xef, 0xff, 0x22, 0xd7, 0x7b, 0xe7}};
EFI_GUID gUefiInfoEfiKmsFormatSha512_512Guid                              = {0x2f240e12, 0xe14d, 0x475c, {0x83, 0xb0, 0xef, 0xff, 0x22, 0xd7, 0x7b, 0xe7}};
EFI_GUID gUefiInfoEfiKmsProtocolGuid                                      = {0xec3a978d, 0x7c4e, 0x48fa, {0x9a, 0xbe, 0x6a, 0xd9, 0x1c, 0xc8, 0xf8, 0x11}};
EFI_GUID gUefiInfoEfiLegacy8259ProtocolGuid                               = {0x38321dba, 0x4fe0, 0x4e17, {0x8a, 0xec, 0x41, 0x30, 0x55, 0xea, 0xed, 0xc1}};
EFI_GUID gUefiInfoEfiLegacyBiosGuid                                       = {0x2e3044ac, 0x879f, 0x490f, {0x97, 0x60, 0xbb, 0xdf, 0xaf, 0x69, 0x5f, 0x50}};
EFI_GUID gUefiInfoEfiLegacyBiosPlatformProtocolGuid                       = {0x783658a3, 0x4172, 0x4421, {0xa2, 0x99, 0xe0, 0x09, 0x07, 0x9c, 0x0c, 0xb4}};
EFI_GUID gUefiInfoEfiLegacyBiosProtocolGuid                               = {0xdb9a1e3d, 0x45cb, 0x4abb, {0x85, 0x3b, 0xe5, 0x38, 0x7f, 0xdb, 0x2e, 0x2d}};
EFI_GUID gUefiInfoEfiLegacyDevOrderVariableGuid                           = {0xa56074db, 0x65fe, 0x45f7, {0xbd, 0x21, 0x2d, 0x2b, 0xdd, 0x8e, 0x96, 0x52}};
EFI_GUID gUefiInfoEfiLegacyInterruptProtocolGuid                          = {0x31ce593d, 0x108a, 0x485d, {0xad, 0xb2, 0x78, 0xf2, 0x1f, 0x29, 0x66, 0xbe}};
EFI_GUID gUefiInfoEfiLegacyRegion2ProtocolGuid                            = {0x70101eaf, 0x0085, 0x440c, {0xb3, 0x56, 0x8e, 0xe3, 0x6f, 0xef, 0x24, 0xf0}};
EFI_GUID gUefiInfoEfiLegacyRegionProtocolGuid                             = {0x0fc9013a, 0x0568, 0x4ba9, {0x9b, 0x7e, 0xc9, 0xc3, 0x90, 0xa6, 0x60, 0x9b}};
EFI_GUID gUefiInfoEfiLoadedImageDevicePathProtocolGuid                    = {0xbc62157e, 0x3e33, 0x4fec, {0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf}};
EFI_GUID gUefiInfoEfiLoadedImageProtocolGuid                              = {0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiLoadFile2ProtocolGuid                                = {0x4006c0c1, 0xfcb3, 0x403e, {0x99, 0x6d, 0x4a, 0x6c, 0x87, 0x24, 0xe0, 0x6d}};
EFI_GUID gUefiInfoEfiLoadFileProtocolGuid                                 = {0x56ec3091, 0x954c, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiLoadPeImageProtocolGuid                              = {0x5cb5c776, 0x60d5, 0x45ee, {0x88, 0x3c, 0x45, 0x27, 0x08, 0xcd, 0x74, 0x3f}};
EFI_GUID gUefiInfoEfiLockBoxProtocolGuid                                  = {0xbd445d79, 0xb7ad, 0x4f04, {0x9a, 0xd8, 0x29, 0xbd, 0x20, 0x40, 0xeb, 0x3c}};
EFI_GUID gUefiInfoEfiLpcWpc83627PolicyProtocolGuid                        = {0xd3ecc567, 0x9fd5, 0x44c1, {0x86, 0xcf, 0x5d, 0xa7, 0xa2, 0x4f, 0x4b, 0x5d}};
EFI_GUID gUefiInfoEfiLpcWpce791PolicyProtocolGuid                         = {0xab2bee2f, 0xc1a6, 0x4399, {0x85, 0x3d, 0xc0, 0x7c, 0x77, 0x4f, 0xfd, 0x0d}};
EFI_GUID gUefiInfoEfiManagedNetworkProtocolGuid                           = {0x7ab33a91, 0xace5, 0x4326, {0xb5, 0x72, 0xe7, 0xee, 0x33, 0xd3, 0x9f, 0x16}};
EFI_GUID gUefiInfoEfiManagedNetworkServiceBindingProtocolGuid             = {0xf36ff770, 0xa7e1, 0x42cf, {0x9e, 0xd2, 0x56, 0xf0, 0xf2, 0x71, 0xf4, 0x4c}};
EFI_GUID gUefiInfoEfiMdeModulePkgTokenSpaceGuid                           = {0xa1aff049, 0xfdeb, 0x442a, {0xb3, 0x20, 0x13, 0xab, 0x4c, 0xb7, 0x2b, 0xbc}};
EFI_GUID gUefiInfoEfiMdePkgTokenSpaceGuid                                 = {0x914aebe7, 0x4635, 0x459b, {0xaa, 0x1c, 0x11, 0xe2, 0x19, 0xb0, 0x3a, 0x10}};
EFI_GUID gUefiInfoEfiMemoryAttributesTableGuid                            = {0xdcfa911d, 0x26eb, 0x469f, {0xa2, 0x20, 0x38, 0xb7, 0xdc, 0x46, 0x12, 0x20}};
EFI_GUID gUefiInfoEfiMemoryConfigDataGuid                                 = {0x80dbd530, 0xb74c, 0x4f11, {0x8c, 0x03, 0x41, 0x86, 0x65, 0x53, 0x28, 0x31}};
EFI_GUID gUefiInfoEfiMemoryOverwriteControlDataGuid                       = {0xe20939be, 0x32d4, 0x41be, {0xa1, 0x50, 0x89, 0x7f, 0x85, 0xd4, 0x98, 0x29}};
EFI_GUID gUefiInfoEfiMemoryRangeCapsuleGuid                               = {0x0de9f0ec, 0x88b6, 0x428f, {0x97, 0x7a, 0x25, 0x8f, 0x1d, 0x0e, 0x5e, 0x72}};
EFI_GUID gUefiInfoEfiMemoryRangeRequirementDataGuid                       = {0x0f7d8603, 0xa812, 0x4210, {0x86, 0x1b, 0x1b, 0x32, 0x04, 0xde, 0x56, 0x5b}};
EFI_GUID gUefiInfoEfiMemorySubClassGuid                                   = {0x4e8f4ebb, 0x64b9, 0x4e05, {0x9b, 0x18, 0x4c, 0xfe, 0x49, 0x23, 0x50, 0x97}};
EFI_GUID gUefiInfoEfiMemoryTypeInformationGuid                            = {0x4c19049f, 0x4137, 0x4dd3, {0x9c, 0x10, 0x8b, 0x97, 0xa8, 0x3f, 0xfd, 0xfa}};
EFI_GUID gUefiInfoEfiMetronomeArchProtocolGuid                            = {0x26baccb2, 0x6f42, 0x11d4, {0xbc, 0xe7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiMiscSubClassGuid                                     = {0x772484b2, 0x7482, 0x4b91, {0x9f, 0x9a, 0xad, 0x43, 0xf8, 0x1c, 0x58, 0x81}};
EFI_GUID gUefiInfoEfiMmcHostProtocolGuid                                  = {0x3e591c00, 0x9e4a, 0x11df, {0x92, 0x44, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b}};
EFI_GUID gUefiInfoEfiMmioDeviceProtocolGuid                               = {0x24486226, 0xf8c2, 0x41f5, {0xb9, 0xdd, 0x78, 0x3e, 0x9e, 0x56, 0xde, 0xa0}};
EFI_GUID gUefiInfoEfiMonotonicCounterArchProtocolGuid                     = {0x1da97072, 0xbddc, 0x4b30, {0x99, 0xf1, 0x72, 0xa0, 0xb5, 0x6f, 0xff, 0x2a}};
EFI_GUID gUefiInfoEfiMpServiceProtocolGuid                                = {0x3fdda605, 0xa76e, 0x4f46, {0xad, 0x29, 0x12, 0xf4, 0x53, 0x1b, 0x3d, 0x08}};
EFI_GUID gUefiInfoEfiMpServicesProtocolGuid                               = {0xf33261e7, 0x23cb, 0x11d5, {0xbd, 0x5c, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiMsNetworkDelayProtocolGuid                           = {0xff7d36aa, 0x96a5, 0x46c4, {0xb1, 0x66, 0xfe, 0x18, 0xd2, 0x93, 0x26, 0x06}};
EFI_GUID gUefiInfoEfiMtftp4ProtocolGuid                                   = {0x78247c57, 0x63db, 0x4708, {0x99, 0xc2, 0xa8, 0xb4, 0xa9, 0xa6, 0x1f, 0x6b}};
EFI_GUID gUefiInfoEfiMtftp4ServiceBindingProtocolGuid                     = {0x2fe800be, 0x8f01, 0x4aa6, {0x94, 0x6b, 0xd7, 0x13, 0x88, 0xe1, 0x83, 0x3f}};
EFI_GUID gUefiInfoEfiMtftp6ProtocolGuid                                   = {0xbf0a78ba, 0xec29, 0x49cf, {0xa1, 0xc9, 0x7a, 0xe5, 0x4e, 0xab, 0x6a, 0x51}};
EFI_GUID gUefiInfoEfiMtftp6ServiceBindingProtocolGuid                     = {0xd9760ff3, 0x3cca, 0x4267, {0x80, 0xf9, 0x75, 0x27, 0xfa, 0xfa, 0x42, 0x23}};
EFI_GUID gUefiInfoEfiNetworkInterfaceIdentifierProtocolGuid               = {0xe18541cd, 0xf755, 0x4f73, {0x92, 0x8d, 0x64, 0x3c, 0x8a, 0x79, 0xb2, 0x29}};
EFI_GUID gUefiInfoEfiNetworkPkgTokenSpaceGuid                             = {0x40e064b2, 0x0ae0, 0x48b1, {0xa0, 0x7d, 0xf8, 0xcf, 0x1e, 0x1a, 0x23, 0x10}};
EFI_GUID gUefiInfoEfiNicIp4ConfigVariableGuid                             = {0xd8944553, 0xc4dd, 0x41f4, {0x9b, 0x30, 0xe1, 0x39, 0x7c, 0xfb, 0x26, 0x7b}};
EFI_GUID gUefiInfoEfiNormalSetupGuid                                      = {0xec87d643, 0xeba4, 0x4bb5, {0xa1, 0xe5, 0x3f, 0x3e, 0x36, 0xb2, 0x0d, 0xa9}};
EFI_GUID gUefiInfoEfiNt32PkgTokenSpaceGuid                                = {0x0d79a645, 0x1d91, 0x40a6, {0xa8, 0x1f, 0x61, 0xe6, 0x98, 0x2b, 0x32, 0xb4}};
EFI_GUID gUefiInfoEfiNvdimmLabelProtocolGuid                              = {0xd40b6b80, 0x97d5, 0x4282, {0xbb, 0x1d, 0x22, 0x3a, 0x16, 0x91, 0x80, 0x58}};
EFI_GUID gUefiInfoEfiNvmeProtocolGuid                                     = {0x0a0341d0, 0x0000, 0x0000, {0x01, 0x01, 0x06, 0x00, 0x00, 0x1d, 0x01, 0x01}};
EFI_GUID gUefiInfoEfiNvmExpressPassThruProtocolGuid                       = {0x52c78312, 0x8edc, 0x4233, {0x98, 0xf2, 0x1a, 0x1a, 0xa5, 0xe3, 0x88, 0xa5}};
EFI_GUID gUefiInfoEfiOEMBadgingProtocolGuid                               = {0x170e13c0, 0xbf1b, 0x4218, {0x87, 0x1d, 0x2a, 0xbd, 0xc6, 0xf8, 0x87, 0xbc}};
EFI_GUID gUefiInfoEfiOfflineCrashdumpTableGuid                            = {0x3804cf02, 0x8538, 0x11e2, {0x88, 0x47, 0x8d, 0xf1, 0x60, 0x88, 0x70, 0x9b}};
EFI_GUID gUefiInfoEfiOfflineCrashdumpVariablesGuid                        = {0x77fa9abd, 0x0359, 0x4d32, {0xbd, 0x60, 0x28, 0xf4, 0xe7, 0x8f, 0x78, 0x4b}};
EFI_GUID gUefiInfoEfiPaddingNoneGuid                                      = {0x3629ddb1, 0x228c, 0x452e, {0xb6, 0x16, 0x09, 0xed, 0x31, 0x6a, 0x97, 0x00}};
EFI_GUID gUefiInfoEfiPaddingRsaesOaepGuid                                 = {0xc1e63ac4, 0xd0cf, 0x4ce6, {0x83, 0x5b, 0xee, 0xd0, 0xe6, 0xa8, 0xa4, 0x5b}};
EFI_GUID gUefiInfoEfiPaddingRsaesPkcs1V1P5Guid                            = {0xe1c1d0a9, 0x40b1, 0x4632, {0xbd, 0xcc, 0xd9, 0xd6, 0xe5, 0x29, 0x56, 0x31}};
EFI_GUID gUefiInfoEfiPaddingRsassaPkcs1V1P5Guid                           = {0x9317ec24, 0x7cb0, 0x4d0e, {0x8b, 0x32, 0x2e, 0xd9, 0x20, 0x9c, 0xd8, 0xaf}};
EFI_GUID gUefiInfoEfiPaddingRsassaPssGuid                                 = {0x7b2349e0, 0x522d, 0x4f8e, {0xb9, 0x27, 0x69, 0xd9, 0x7c, 0x9e, 0x79, 0x5f}};
EFI_GUID gUefiInfoEfiPartitionInfoProtocolGuid                            = {0x8cf2f62c, 0xbc9b, 0x4821, {0x80, 0x8d, 0xec, 0x9e, 0xc4, 0x21, 0xa1, 0xa0}};
EFI_GUID gUefiInfoEfiPartitionRecordGuid                                  = {0xfe2555be, 0xd716, 0x4686, {0xb9, 0xd0, 0x79, 0xdb, 0x59, 0x21, 0xb7, 0x0d}};
EFI_GUID gUefiInfoEfiPartTypeLegacyMbrGuid                                = {0x024dee41, 0x33e7, 0x11d3, {0x9d, 0x69, 0x00, 0x08, 0xc7, 0x81, 0xf3, 0x9f}};
EFI_GUID gUefiInfoEfiPartTypeSystemPartGuid                               = {0xc12a7328, 0xf81f, 0x11d2, {0xba, 0x4b, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}};
EFI_GUID gUefiInfoEfiPartTypeUnusedGuid                                   = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
EFI_GUID gUefiInfoEfiPcAnsiGuid                                           = {0xe0c14753, 0xf9be, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiPcdProtocolGuid                                      = {0x13a3f0f6, 0x264a, 0x3ef0, {0xf2, 0xe0, 0xde, 0xc5, 0x12, 0x34, 0x2f, 0x34}};
EFI_GUID gUefiInfoEfiPchExtendedResetProtocolGuid                         = {0xf0bbfca0, 0x684e, 0x48b3, {0xba, 0xe2, 0x6c, 0x84, 0xb8, 0x9e, 0x53, 0x39}};
EFI_GUID gUefiInfoEfiPchInfoProtocolGuid                                  = {0xd31f0400, 0x7d16, 0x4316, {0xbf, 0x88, 0x60, 0x65, 0x88, 0x3b, 0x40, 0x2b}};
EFI_GUID gUefiInfoEfiPchS3SupportProtocolGuid                             = {0xe287d20b, 0xd897, 0x4e1e, {0xa5, 0xd9, 0x97, 0x77, 0x63, 0x93, 0x6a, 0x04}};
EFI_GUID gUefiInfoEfiPchTokenSpaceGuid                                    = {0x89a1b278, 0xa1a1, 0x4df7, {0xb1, 0x37, 0xde, 0x5a, 0xd7, 0xc4, 0x79, 0x13}};
EFI_GUID gUefiInfoEfiPciBusErrorSectionGuid                               = {0xc5753963, 0x3b84, 0x4095, {0xbf, 0x78, 0xed, 0xda, 0xd3, 0xf9, 0xc9, 0xdd}};
EFI_GUID gUefiInfoEfiPciCfg2PpiGuid                                       = {0x057a449a, 0x1fdc, 0x4c06, {0xbf, 0xc9, 0xf5, 0x3f, 0x6a, 0x99, 0xbb, 0x92}};
EFI_GUID gUefiInfoEfiPciCfgPpiInServiceTableGuid                          = {0xe1f2eba0, 0xf7b9, 0x4a26, {0x86, 0x20, 0x13, 0x12, 0x21, 0x64, 0x2a, 0x90}};
EFI_GUID gUefiInfoEfiPciDevErrorSectionGuid                               = {0xeb5e4685, 0xca66, 0x4769, {0xb6, 0xa2, 0x26, 0x06, 0x8b, 0x00, 0x13, 0x26}};
EFI_GUID gUefiInfoEfiPcieErrorSectionGuid                                 = {0xd995e954, 0xbbc1, 0x430f, {0xad, 0x91, 0xb4, 0x4d, 0xcb, 0x3c, 0x6f, 0x35}};
EFI_GUID gUefiInfoEfiPciEnumerationCompleteProtocolGuid                   = {0x30cfe3e7, 0x3de1, 0x4586, {0xbe, 0x20, 0xde, 0xab, 0xa1, 0xb3, 0xb7, 0x93}};
EFI_GUID gUefiInfoEfiPciExpressBaseAddressGuid                            = {0x3677d529, 0x326f, 0x4603, {0xa9, 0x26, 0xea, 0xac, 0xe0, 0x1d, 0xcb, 0xb0}};
EFI_GUID gUefiInfoEfiPciHostBridgeResourceAllocationProtocolGuid          = {0xcf8034be, 0x6768, 0x4d8b, {0xb7, 0x39, 0x7c, 0xce, 0x68, 0x3a, 0x9f, 0xbe}};
EFI_GUID gUefiInfoEfiPciHotPlugInitProtocolGuid                           = {0xaa0e8bc1, 0xdabc, 0x46b0, {0xa8, 0x44, 0x37, 0xb8, 0x16, 0x9b, 0x2b, 0xea}};
EFI_GUID gUefiInfoEfiPciHotPlugRequestProtocolGuid                        = {0x19cb87ab, 0x2cb9, 0x4665, {0x83, 0x60, 0xdd, 0xcf, 0x60, 0x54, 0xf7, 0x9d}};
EFI_GUID gUefiInfoEfiPciIoProtocolGuid                                    = {0x4cf5b200, 0x68b8, 0x4ca5, {0x9e, 0xec, 0xb2, 0x3e, 0x3f, 0x50, 0x02, 0x9a}};
EFI_GUID gUefiInfoEfiPciLanInfoGuid                                       = {0x0d9a1427, 0xe02a, 0x437d, {0x92, 0x6b, 0xaa, 0x52, 0x1f, 0xd7, 0x22, 0xba}};
EFI_GUID gUefiInfoEfiPciOptionRomTableGuid                                = {0x7462660f, 0x1cbd, 0x48da, {0xad, 0x11, 0x91, 0x71, 0x79, 0x13, 0x83, 0x1c}};
EFI_GUID gUefiInfoEfiPciOverrideProtocolGuid                              = {0xb5b35764, 0x460c, 0x4a06, {0x99, 0xfc, 0x77, 0xa1, 0x7c, 0x1b, 0x5c, 0xeb}};
EFI_GUID gUefiInfoEfiPciPlatformProtocolGuid                              = {0x07d75280, 0x27d4, 0x4d69, {0x90, 0xd0, 0x56, 0x43, 0xe2, 0x38, 0xb3, 0x41}};
EFI_GUID gUefiInfoEfiPciRootBridgeIoProtocolGuid                          = {0x2f707ebb, 0x4a1a, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiPei144FloppyBlockIoPpiGuid                           = {0xda6855bd, 0x07b7, 0x4c05, {0x9e, 0xd8, 0xe2, 0x59, 0xfd, 0x36, 0x0e, 0x22}};
EFI_GUID gUefiInfoEfiPeiBootInRecoveryModePpiGuid                         = {0x17ee496a, 0xd8e4, 0x4b9a, {0x94, 0xd1, 0xce, 0x82, 0x72, 0x30, 0x08, 0x50}};
EFI_GUID gUefiInfoEfiPeiBootScriptExecuterPpiGuid                         = {0xabd42895, 0x78cf, 0x4872, {0x84, 0x44, 0x1b, 0x5c, 0x18, 0x0b, 0xfb, 0xff}};
EFI_GUID gUefiInfoEfiPeiCpuIoPpiInstalledGuid                             = {0xe6af1f7b, 0xfc3f, 0x46da, {0xa8, 0x28, 0xa3, 0xb4, 0x57, 0xa4, 0x42, 0x82}};
EFI_GUID gUefiInfoEfiPeiDecompressPpiGuid                                 = {0x1a36e4e7, 0xfab6, 0x476a, {0x8e, 0x75, 0x69, 0x5a, 0x05, 0x76, 0xfd, 0xd7}};
EFI_GUID gUefiInfoEfiPeiDeviceRecoveryModulePpiGuid                       = {0x0de2ce25, 0x446a, 0x45a7, {0xbf, 0xc9, 0x37, 0xda, 0x26, 0x34, 0x4b, 0x37}};
EFI_GUID gUefiInfoEfiPeiFirmwareVolumeInfo2PpiGuid                        = {0xea7ca24b, 0xded5, 0x4dad, {0xa3, 0x89, 0xbf, 0x82, 0x7e, 0x8f, 0x9b, 0x38}};
EFI_GUID gUefiInfoEfiPeiFirmwareVolumeInfoMeasurementExcludedPpiGuid      = {0x6e056ff9, 0xc695, 0x4364, {0x9e, 0x2c, 0x61, 0x26, 0xf5, 0xce, 0xea, 0xae}};
EFI_GUID gUefiInfoEfiPeiFirmwareVolumeInfoPpiGuid                         = {0x49edb1c1, 0xbf21, 0x4761, {0xbb, 0x12, 0xeb, 0x00, 0x31, 0xaa, 0xbb, 0x39}};
EFI_GUID gUefiInfoEfiPeiFvFileLoaderPpiGuid                               = {0x7e1f0d85, 0x04ff, 0x4bb2, {0x86, 0x6a, 0x31, 0xa2, 0x99, 0x6a, 0x48, 0xa8}};
EFI_GUID gUefiInfoEfiPeiI2cMasterPpiGuid                                  = {0xb3bfab9b, 0x9f9c, 0x4e8b, {0xad, 0x37, 0x7f, 0x8c, 0x51, 0xfc, 0x62, 0x80}};
EFI_GUID gUefiInfoEfiPeiIdeBlockIoPpiGuid                                 = {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiPeiLoadedImagePpiGuid                                = {0xc1fcd448, 0x6300, 0x4458, {0xb8, 0x64, 0x28, 0xdf, 0x01, 0x53, 0x64, 0xbc}};
EFI_GUID gUefiInfoEfiPeiLoadFilePpiGuid                                   = {0xb9e0abfe, 0x5979, 0x4914, {0x97, 0x7f, 0x6d, 0xee, 0x78, 0xc2, 0x78, 0xa6}};
EFI_GUID gUefiInfoEfiPeiMasterBootModePpiGuid                             = {0x7408d748, 0xfc8c, 0x4ee6, {0x92, 0x88, 0xc4, 0xbe, 0xc0, 0x92, 0xa4, 0x10}};
EFI_GUID gUefiInfoEfiPeiMemoryDiscoveredPpiGuid                           = {0xf894643d, 0xc449, 0x42d1, {0x8e, 0xa8, 0x85, 0xbd, 0xd8, 0xc6, 0x5b, 0xde}};
EFI_GUID gUefiInfoEfiPeiPcdPpiGuid                                        = {0x01f34d25, 0x4de2, 0x23ad, {0x3f, 0xf3, 0x36, 0x35, 0x3f, 0xf3, 0x23, 0xf1}};
EFI_GUID gUefiInfoEfiPeiPeCoffLoaderGuid                                  = {0xd8117cff, 0x94a6, 0x11d4, {0x9a, 0x3a, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiPeiReadOnlyVariable2PpiGuid                          = {0x2ab86ef5, 0xecb5, 0x4134, {0xb5, 0x56, 0x38, 0x54, 0xca, 0x1f, 0xe1, 0xb4}};
EFI_GUID gUefiInfoEfiPeiReadOnlyVariablePpiGuid                           = {0x3cdc90c6, 0x13fb, 0x4a75, {0x9e, 0x79, 0x59, 0xe9, 0xdd, 0x78, 0xb9, 0xfa}};
EFI_GUID gUefiInfoEfiPeiRecoveryModulePpiGuid                             = {0xfb6d9542, 0x612d, 0x4f45, {0x87, 0x2f, 0x5c, 0xff, 0x52, 0xe9, 0x3d, 0xcf}};
EFI_GUID gUefiInfoEfiPeiResetPpiGuid                                      = {0xef398d58, 0x9dfd, 0x4103, {0xbf, 0x94, 0x78, 0xc6, 0xf4, 0xfe, 0x71, 0x2f}};
EFI_GUID gUefiInfoEfiPeiRscHandlerPpiGuid                                 = {0x0065d394, 0x9951, 0x4144, {0x82, 0xa3, 0x0a, 0xfc, 0x85, 0x79, 0xc2, 0x51}};
EFI_GUID gUefiInfoEfiPeiS3Resume2PpiGuid                                  = {0x6d582dbc, 0xdb85, 0x4514, {0x8f, 0xcc, 0x5a, 0xdf, 0x62, 0x27, 0xb1, 0x47}};
EFI_GUID gUefiInfoEfiPeiS3ResumePpiGuid                                   = {0x4426ccb2, 0xe684, 0x4a8a, {0xae, 0x40, 0x20, 0xd4, 0xb0, 0x25, 0xb7, 0x10}};
EFI_GUID gUefiInfoEfiPeiSectionExtractionPpiGuid                          = {0x4f89e208, 0xe144, 0x4804, {0x9e, 0xc8, 0x0f, 0x89, 0x4f, 0x7e, 0x36, 0xd7}};
EFI_GUID gUefiInfoEfiPeiSecurity2PpiGuid                                  = {0xdcd0be23, 0x9586, 0x40f4, {0xb6, 0x43, 0x06, 0x52, 0x2c, 0xed, 0x4e, 0xde}};
EFI_GUID gUefiInfoEfiPeiSecurityPpiGuid                                   = {0x1388066e, 0x3a57, 0x4efa, {0x98, 0xf3, 0xc1, 0x2f, 0x3a, 0x95, 0x8a, 0x29}};
EFI_GUID gUefiInfoEfiPeiSmbus2PpiGuid                                     = {0x9ca93627, 0xb65b, 0x4324, {0xa2, 0x02, 0xc0, 0xb4, 0x61, 0x76, 0x45, 0x43}};
EFI_GUID gUefiInfoEfiPeiSmbusPpiGuid                                      = {0xabd42895, 0x78cf, 0x4872, {0x84, 0x44, 0x1b, 0x5c, 0x18, 0x0b, 0xfb, 0xda}};
EFI_GUID gUefiInfoEfiPeiSmmCommunicationPpiGuid                           = {0xae933e1c, 0xcc47, 0x4e38, {0x8f, 0x0e, 0xe2, 0xf6, 0x1d, 0x26, 0x05, 0xdf}};
EFI_GUID gUefiInfoEfiPeiStallPpiGuid                                      = {0x1f4c6f90, 0xb06b, 0x48d8, {0xa2, 0x01, 0xba, 0xe5, 0xf1, 0xcd, 0x7d, 0x56}};
EFI_GUID gUefiInfoEfiPeiStatusCodePpiGuid                                 = {0x229832d3, 0x7a30, 0x4b36, {0xb8, 0x27, 0xf4, 0x0c, 0xb7, 0xd4, 0x54, 0x36}};
EFI_GUID gUefiInfoEfiPeiVirtualBlockIoPpiGuid                             = {0x695d8aa1, 0x42ee, 0x4c46, {0x80, 0x5c, 0x6e, 0xa6, 0xbc, 0xe7, 0x99, 0xe3}};
EFI_GUID gUefiInfoEfiPersistentVirtualCdGuid                              = {0x08018188, 0x42cd, 0xbb48, {0x10, 0x0f, 0x53, 0x87, 0xd5, 0x3d, 0xed, 0x3d}};
EFI_GUID gUefiInfoEfiPersistentVirtualDiskGuid                            = {0x5cea02c9, 0x4d07, 0x69d3, {0x26, 0x9f, 0x44, 0x96, 0xfb, 0xe0, 0x96, 0xf9}};
EFI_GUID gUefiInfoEfiPhysicalPresenceGuid                                 = {0x0f6499b1, 0xe9ad, 0x493d, {0xb9, 0xc2, 0x2f, 0x90, 0x81, 0x5c, 0x6c, 0xbc}};
EFI_GUID gUefiInfoEfiPkcs7VerifyProtocolGuid                              = {0x47889fb2, 0xd671, 0x4fab, {0xa0, 0xca, 0xdf, 0x0e, 0x44, 0xdf, 0x70, 0xd6}};
EFI_GUID gUefiInfoEfiPlatformBootModeGuid                                 = {0xce845704, 0x1683, 0x4d38, {0xa4, 0xf9, 0x7d, 0x0b, 0x50, 0x77, 0x57, 0x93}};
EFI_GUID gUefiInfoEfiPlatformCpuInfoGuid                                  = {0xbb9c7ab7, 0xb8d9, 0x4bf3, {0x9c, 0x29, 0x9b, 0xf3, 0x41, 0xe2, 0x17, 0xbc}};
EFI_GUID gUefiInfoEfiPlatformCpuProtocolGuid                              = {0xbd26cdc9, 0xa092, 0x462a, {0x87, 0x7a, 0x5a, 0xb6, 0xad, 0xce, 0x48, 0x12}};
EFI_GUID gUefiInfoEfiPlatformDriverOverrideProtocolGuid                   = {0x6b30c738, 0xa391, 0x11d4, {0x9a, 0x3b, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiPlatformIdeInitProtocolGuid                          = {0x377c66a3, 0x8fe7, 0x4ee8, {0x85, 0xb8, 0xf1, 0xa2, 0x82, 0x56, 0x9e, 0x3b}};
EFI_GUID gUefiInfoEfiPlatformInfoGuid                                     = {0x1e2acc41, 0xe26a, 0x483d, {0xaf, 0xc7, 0xa0, 0x56, 0xc3, 0x4e, 0x08, 0x7b}};
EFI_GUID gUefiInfoEfiPlatformMemoryErrorSectionGuid                       = {0xa5bc1114, 0x6f64, 0x4ede, {0xb8, 0x63, 0x3e, 0x83, 0xed, 0x7c, 0x83, 0xb1}};
EFI_GUID gUefiInfoEfiPlatformToDriverConfigurationClpGuid                 = {0x345ecc0e, 0x0cb6, 0x4b75, {0xbb, 0x57, 0x1b, 0x12, 0x9c, 0x47, 0x33, 0x3e}};
EFI_GUID gUefiInfoEfiPlatformToDriverConfigurationProtocolGuid            = {0x642cd590, 0x8059, 0x4c0a, {0xa9, 0x58, 0xc5, 0xec, 0x07, 0xd2, 0x3c, 0x4b}};
EFI_GUID gUefiInfoEfiPowerOnHobGuid                                       = {0x0468a601, 0xc535, 0x46fd, {0xa9, 0x5d, 0xbb, 0xab, 0x99, 0x1b, 0x17, 0x8c}};
EFI_GUID gUefiInfoEfiPpamManifestTableGuid                                = {0x1878f400, 0xdcdb, 0x4f5e, {0x8b, 0x2d, 0x85, 0x71, 0x4a, 0xca, 0x2c, 0x90}};
EFI_GUID gUefiInfoEfiPrint2ProtocolGuid                                   = {0xf05976ef, 0x83f1, 0x4f3d, {0x86, 0x19, 0xf7, 0x59, 0x5d, 0x41, 0xe5, 0x38}};
EFI_GUID gUefiInfoEfiPrintProtocolGuid                                    = {0xdf2d868e, 0x32fc, 0x4cf0, {0x8e, 0x6b, 0xff, 0xd9, 0x5d, 0x13, 0x43, 0xd0}};
EFI_GUID gUefiInfoEfiProcessorGenericErrorSectionGuid                     = {0x9876ccad, 0x47b4, 0x4bdb, {0xb6, 0x5e, 0x16, 0xf1, 0x93, 0xc4, 0xf3, 0xdb}};
EFI_GUID gUefiInfoEfiProcessorSpecificErrorSectionGuid                    = {0xdc3ea0b0, 0xa144, 0x4797, {0xb9, 0x5b, 0x53, 0xfa, 0x24, 0x2b, 0x6e, 0x1d}};
EFI_GUID gUefiInfoEfiProcessorSubClassGuid                                = {0x26fdeb7e, 0xb8af, 0x4ccf, {0xaa, 0x97, 0x02, 0x63, 0x3c, 0xe4, 0x8c, 0xa7}};
EFI_GUID gUefiInfoEfiPropertiesTableGuid                                  = {0x880aaca3, 0x4adc, 0x4a04, {0x90, 0x79, 0xb7, 0x47, 0x34, 0x08, 0x25, 0xe5}};
EFI_GUID gUefiInfoEfiPs2PolicyProtocolGuid                                = {0x4df19259, 0xdc71, 0x4d46, {0xbe, 0xf1, 0x35, 0x7b, 0xb5, 0x78, 0xc4, 0x18}};
EFI_GUID gUefiInfoEfiPxeBaseCodeCallbackProtocolGuid                      = {0x245dca21, 0xfb7b, 0x11d3, {0x8f, 0x01, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiPxeBaseCodeProtocolGuid                              = {0x03c4e603, 0xac28, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiRamDiskProtocolGuid                                  = {0xab38a0df, 0x6873, 0x44a9, {0x87, 0xe6, 0xd4, 0xeb, 0x56, 0x14, 0x84, 0x49}};
EFI_GUID gUefiInfoEfiRealTimeClockArchProtocolGuid                        = {0x27cfac87, 0x46cc, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiRedfishDiscoverProtocolGuid                          = {0x5db12509, 0x4550, 0x4347, {0x96, 0xb3, 0x73, 0xc0, 0xff, 0x6e, 0x86, 0x9f}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypeEcma_262AsciiGuid                     = {0xb2284a2f, 0x4491, 0x6d9d, {0xea, 0xb7, 0x11, 0xb0, 0x67, 0xd4, 0x9b, 0x9a}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypeEcma_262Guid                          = {0x9a473a4a, 0x4ceb, 0xb95a, {0x41, 0x5e, 0x5b, 0xa0, 0xbc, 0x63, 0x9b, 0x2e}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypePerlAsciiGuid                         = {0x87dfb76d, 0x4b58, 0xef3a, {0xf7, 0xc6, 0x16, 0xa4, 0x2a, 0x68, 0x28, 0x10}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypePerlGuid                              = {0x63e60a51, 0x497d, 0xd427, {0xc4, 0xa5, 0xb8, 0xab, 0xdc, 0x3a, 0xae, 0xb6}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypePosixExtendedAsciiGuid                = {0x3fd32128, 0x4bb1, 0xf632, {0xbe, 0x4f, 0xba, 0xbf, 0x85, 0xc9, 0x36, 0x76}};
EFI_GUID gUefiInfoEfiRegexSyntaxTypePosixExtendedGuid                     = {0x5f05b20f, 0x4a56, 0xc231, {0xfa, 0x0b, 0xa7, 0xb1, 0xf1, 0x10, 0x04, 0x1d}};
EFI_GUID gUefiInfoEfiRegularExpressionProtocolGuid                        = {0xb3f79d9a, 0x436c, 0xdc11, {0xb0, 0x52, 0xcd, 0x85, 0xdf, 0x52, 0x4c, 0xe6}};
EFI_GUID gUefiInfoEfiResetArchProtocolGuid                                = {0x27cfac88, 0x46cc, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiResetNotificationProtocolGuid                        = {0x9da34ae0, 0xeaf9, 0x4bbf, {0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe}};
EFI_GUID gUefiInfoEfiRestExProtocolGuid                                   = {0x55648b91, 0x0e7d, 0x40a3, {0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97}};
EFI_GUID gUefiInfoEfiRestExServiceBindingProtocolGuid                     = {0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59}};
EFI_GUID gUefiInfoEfiRestJsonStructureProtocolGuid                        = {0xa9a048f6, 0x48a0, 0x4714, {0xb7, 0xda, 0xa9, 0xad, 0x87, 0xd4, 0xda, 0xc9}};
EFI_GUID gUefiInfoEfiRestProtocolGuid                                     = {0x0db48a36, 0x4e54, 0xea9c, {0x9b, 0x09, 0x1e, 0xa5, 0xbe, 0x3a, 0x66, 0x0b}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp80090Ctr256Guid                        = {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp80090Hash256Guid                       = {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp80090Hmac256Guid                       = {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp800_90Ctr_256Guid                      = {0x44f0de6e, 0x4d8c, 0x4045, {0xa8, 0xc7, 0x4d, 0xd1, 0x68, 0x85, 0x6b, 0x9e}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp800_90Hash_256Guid                     = {0xa7af67cb, 0x603b, 0x4d42, {0xba, 0x21, 0x70, 0xbf, 0xb6, 0x29, 0x3f, 0x96}};
EFI_GUID gUefiInfoEfiRngAlgorithmSp800_90Hmac_256Guid                     = {0xc5149b43, 0xae85, 0x4f53, {0x99, 0x82, 0xb9, 0x43, 0x35, 0xd3, 0xa9, 0xe7}};
EFI_GUID gUefiInfoEfiRngAlgorithmX9313DesGuid                             = {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46}};
EFI_GUID gUefiInfoEfiRngAlgorithmX931AesGuid                              = {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9}};
EFI_GUID gUefiInfoEfiRngAlgorithmX9_31_3DesGuid                           = {0x63c4785a, 0xca34, 0x4012, {0xa3, 0xc8, 0x0b, 0x6a, 0x32, 0x4f, 0x55, 0x46}};
EFI_GUID gUefiInfoEfiRngAlgorithmX9_31AesGuid                             = {0xacd03321, 0x777e, 0x4d3d, {0xb1, 0xc8, 0x20, 0xcf, 0xd8, 0x88, 0x20, 0xc9}};
EFI_GUID gUefiInfoEfiRngProtocolGuid                                      = {0x3152bca5, 0xeade, 0x433d, {0x86, 0x2e, 0xc0, 0x1c, 0xdc, 0x29, 0x1f, 0x44}};
EFI_GUID gUefiInfoEfiRscHandlerProtocolGuid                               = {0x86212936, 0x0e76, 0x41c8, {0xa0, 0x3a, 0x2a, 0xf2, 0xfc, 0x1c, 0x39, 0xe2}};
EFI_GUID gUefiInfoEfiRuntimeArchProtocolGuid                              = {0xb7dfb4e1, 0x052f, 0x449f, {0x87, 0xbe, 0x98, 0x18, 0xfc, 0x91, 0xb7, 0x33}};
EFI_GUID gUefiInfoEfiRuntimeCryptProtocolGuid                             = {0xe1475e0c, 0x1746, 0x4802, {0x86, 0x2e, 0x01, 0x1c, 0x2c, 0x2d, 0x9d, 0x86}};
EFI_GUID gUefiInfoEfiS3SaveStateProtocolGuid                              = {0xe857caf6, 0xc046, 0x45dc, {0xbe, 0x3f, 0xee, 0x07, 0x65, 0xfb, 0xa8, 0x87}};
EFI_GUID gUefiInfoEfiS3SmmSaveStateProtocolGuid                           = {0x320afe62, 0xe593, 0x49cb, {0xa9, 0xf1, 0xd4, 0xc2, 0xf4, 0xaf, 0x01, 0x4c}};
EFI_GUID gUefiInfoEfiSalMcaInitPmiProtocolGuid                            = {0xb60dc6e8, 0x3b6f, 0x11d5, {0xaf, 0x09, 0x00, 0xa0, 0xc9, 0x44, 0xa0, 0x5b}};
EFI_GUID gUefiInfoEfiSalSystemTableGuid                                   = {0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiSasDevicePathGuid                                    = {0xd487ddb4, 0x008b, 0x11d9, {0xaf, 0xdc, 0x00, 0x10, 0x83, 0xff, 0xca, 0x4d}};
EFI_GUID gUefiInfoEfiScsiIoProtocolGuid                                   = {0x932f47e6, 0x2362, 0x4002, {0x80, 0x3e, 0x3c, 0xd5, 0x4b, 0x13, 0x8f, 0x85}};
EFI_GUID gUefiInfoEfiScsiPassThruProtocolGuid                             = {0xa59e8fcf, 0xbda0, 0x43bb, {0x90, 0xb1, 0xd3, 0x73, 0x2e, 0xca, 0xa8, 0x77}};
EFI_GUID gUefiInfoEfiSdccCardInfoProtocolGuid                             = {0x6ec6ed4f, 0xd958, 0x40be, {0x87, 0x28, 0x6c, 0x59, 0x73, 0x29, 0x66, 0xdf}};
EFI_GUID gUefiInfoEfiSdHostIoProtocolGuid                                 = {0xb63f8ec7, 0xa9c9, 0x4472, {0xa4, 0xc0, 0x4d, 0x8b, 0xf3, 0x65, 0xcc, 0x51}};
EFI_GUID gUefiInfoEfiSdMmcPassThruProtocolGuid                            = {0x716ef0d9, 0xff83, 0x4f69, {0x81, 0xe9, 0x51, 0x8b, 0xd3, 0x9a, 0x8e, 0x70}};
EFI_GUID gUefiInfoEfiSdRemovableProtocolGuid                              = {0xd1531d41, 0x3f80, 0x4091, {0x8d, 0x0a, 0x54, 0x1f, 0x59, 0x23, 0x6d, 0x66}};
EFI_GUID gUefiInfoEfiSecPlatformInformationPpiGuid                        = {0x6f8c2b35, 0xfef4, 0x448d, {0x82, 0x56, 0xe1, 0x1b, 0x19, 0xd6, 0x10, 0x77}};
EFI_GUID gUefiInfoEfiSeCRcInfoProtocolGuid                                = {0x11fbfdfb, 0x10d2, 0x43e6, {0xb5, 0xb1, 0xb4, 0x38, 0x6e, 0xdc, 0xcb, 0x9a}};
EFI_GUID gUefiInfoEfiSectionExtractionProtocolGuid                        = {0x448f5da4, 0x6dd7, 0x4fe1, {0x93, 0x07, 0x69, 0x22, 0x41, 0x92, 0x21, 0x5d}};
EFI_GUID gUefiInfoEfiSecureBootEnableDisableGuid                          = {0xf0a30bc7, 0xaf08, 0x4556, {0x99, 0xc4, 0x00, 0x10, 0x09, 0xc9, 0x3a, 0x44}};
EFI_GUID gUefiInfoEfiSecureElementResetProtocolGuid                       = {0x2df29152, 0x4e9a, 0x4b43, {0x8f, 0xc4, 0x87, 0x30, 0xfd, 0xde, 0xa0, 0x81}};
EFI_GUID gUefiInfoEfiSecurity2ArchProtocolGuid                            = {0x94ab2f58, 0x1438, 0x4ef1, {0x91, 0x52, 0x18, 0x94, 0x1a, 0x3a, 0x0e, 0x68}};
EFI_GUID gUefiInfoEfiSecurityArchProtocolGuid                             = {0xa46423e3, 0x4617, 0x49f1, {0xb9, 0xff, 0xd1, 0xbf, 0xa9, 0x11, 0x58, 0x39}};
EFI_GUID gUefiInfoEfiSecurityPkgTokenSpaceGuid                            = {0x0d3fb176, 0x9569, 0x4d51, {0xa3, 0xef, 0x7d, 0x61, 0xc6, 0x4f, 0xea, 0xba}};
EFI_GUID gUefiInfoEfiSecurityPolicyProtocolGuid                           = {0x78e4d245, 0xcd4d, 0x4a05, {0xa2, 0xba, 0x47, 0x43, 0xe8, 0x6c, 0xfc, 0xab}};
EFI_GUID gUefiInfoEfiSerialIoProtocolGuid                                 = {0xbb25cf6f, 0xf1d4, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0xfd}};
EFI_GUID gUefiInfoEfiSerialPortTokenSpaceGuid                             = {0x5fad2389, 0x2bc7, 0x4bd2, {0x83, 0xd3, 0x42, 0x9f, 0xb6, 0xae, 0xa3, 0x3f}};
EFI_GUID gUefiInfoEfiSerialTerminalDeviceTypeGuid                         = {0x6ad9a60f, 0x5815, 0x4c7c, {0x8a, 0x10, 0x50, 0x53, 0xd2, 0xbf, 0x7a, 0x1b}};
EFI_GUID gUefiInfoEfiSetupVariableGuid                                    = {0xec87d643, 0xeba4, 0x4bb5, {0xa1, 0xe5, 0x3f, 0x3e, 0x36, 0xb2, 0x0d, 0xa9}};
EFI_GUID gUefiInfoEfiShellDynamicCommandProtocolGuid                      = {0x3c7200e9, 0x005f, 0x4ea4, {0x87, 0xde, 0xa3, 0xdf, 0xac, 0x8a, 0x27, 0xc3}};
EFI_GUID gUefiInfoEfiShellEnvironment2ExtGuid                             = {0xd2c18636, 0x40e5, 0x4eb5, {0xa3, 0x1b, 0x36, 0x69, 0x5f, 0xd4, 0x2c, 0x87}};
EFI_GUID gUefiInfoEfiShellEnvironment2Guid                                = {0x47c7b221, 0xc42a, 0x11d2, {0x8e, 0x57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiShellInterfaceGuid                                   = {0x47c7b223, 0xc42a, 0x11d2, {0x8e, 0x57, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiShellParametersProtocolGuid                          = {0x752f3136, 0x4e16, 0x4fdc, {0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca}};
EFI_GUID gUefiInfoEfiShellPkgTokenSpaceGuid                               = {0x171e9188, 0x31d3, 0x40f5, {0xb1, 0x0c, 0x53, 0x9b, 0x2d, 0xb9, 0x40, 0xcd}};
EFI_GUID gUefiInfoEfiShellProtocolGuid                                    = {0x6302d008, 0x7f9b, 0x4f30, {0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e}};
EFI_GUID gUefiInfoEfiSimpleFileSystemProtocolGuid                         = {0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiSimpleNetworkProtocolGuid                            = {0xa19832b9, 0xac25, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiSimplePointerProtocolGuid                            = {0x31878c87, 0x0b75, 0x11d5, {0x9a, 0x4f, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiSimpleTextInProtocolGuid                             = {0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiSimpleTextInputExProtocolGuid                        = {0xdd9e7534, 0x7762, 0x4698, {0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}};
EFI_GUID gUefiInfoEfiSimpleTextInputProtocolGuid                          = {0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiSimpleTextOutProtocolGuid                            = {0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiSimpleTextOutputProtocolGuid                         = {0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoEfiSioProtocolGuid                                      = {0x215fdd18, 0xbd50, 0x4feb, {0x89, 0x0b, 0x58, 0xca, 0x0b, 0x47, 0x39, 0xe9}};
EFI_GUID gUefiInfoEfiSioVariableGuid                                      = {0x560bf58a, 0x1e0d, 0x4d7e, {0x95, 0x3f, 0x29, 0x80, 0xa2, 0x61, 0xe0, 0x31}};
EFI_GUID gUefiInfoEfiSmartCardEdgeProtocolGuid                            = {0xd317f29b, 0xa325, 0x4712, {0x9b, 0xf1, 0xc6, 0x19, 0x54, 0xdc, 0x19, 0x8c}};
EFI_GUID gUefiInfoEfiSmartCardReaderProtocolGuid                          = {0x2a4d1adf, 0x21dc, 0x4b81, {0xa4, 0x2f, 0x8b, 0x8e, 0xe2, 0x38, 0x00, 0x60}};
EFI_GUID gUefiInfoEfiSmbios3TableGuid                                     = {0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94}};
EFI_GUID gUefiInfoEfiSmbiosProtocolGuid                                   = {0x03583ff6, 0xcb36, 0x4940, {0x94, 0x7e, 0xb9, 0xb3, 0x9f, 0x4a, 0xfa, 0xf7}};
EFI_GUID gUefiInfoEfiSmbiosSlotPopulationGuid                             = {0xef7bf7d6, 0xf8ff, 0x4a76, {0x82, 0x47, 0xc0, 0xd0, 0xd1, 0xcc, 0x49, 0xc0}};
EFI_GUID gUefiInfoEfiSmbiosTableGuid                                      = {0xeb9d2d31, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiSmbusArpMapGuid                                      = {0x707be83e, 0x0bf6, 0x40a5, {0xbe, 0x64, 0x34, 0xc0, 0x3a, 0xa0, 0xb8, 0xe2}};
EFI_GUID gUefiInfoEfiSmbusHcProtocolGuid                                  = {0xe49d33ed, 0x513d, 0x4634, {0xb6, 0x98, 0x6f, 0x55, 0xaa, 0x75, 0x1c, 0x1b}};
EFI_GUID gUefiInfoEfiSmmAccess2ProtocolGuid                               = {0xc2702b74, 0x800c, 0x4131, {0x87, 0x46, 0x8f, 0xb5, 0xb8, 0x9c, 0xe4, 0xac}};
EFI_GUID gUefiInfoEfiSmmAccessProtocolGuid                                = {0x3792095a, 0xe309, 0x4c1e, {0xaa, 0x01, 0x85, 0xf5, 0x65, 0x5a, 0x17, 0xf1}};
EFI_GUID gUefiInfoEfiSmmBase2ProtocolGuid                                 = {0xf4ccbfb7, 0xf6e0, 0x47fd, {0x9d, 0xd4, 0x10, 0xa8, 0xf1, 0x50, 0xc1, 0x91}};
EFI_GUID gUefiInfoEfiSmmBaseHelperReadyProtocolGuid                       = {0x910dca07, 0x1f94, 0x4ee7, {0xaf, 0x2f, 0xff, 0x72, 0xf3, 0x15, 0x43, 0x53}};
EFI_GUID gUefiInfoEfiSmmBaseProtocolGuid                                  = {0x1390954d, 0xda95, 0x4227, {0x93, 0x28, 0x72, 0x82, 0xc2, 0x17, 0xda, 0xa8}};
EFI_GUID gUefiInfoEfiSmmBaseThunkCommunicationGuid                        = {0x6568a3d6, 0x015f, 0x4b4a, {0x9c, 0x89, 0x1d, 0x14, 0x63, 0x14, 0x13, 0x0a}};
EFI_GUID gUefiInfoEfiSmmCommunicationProtocolGuid                         = {0xc68ed8e2, 0x9dc6, 0x4cbd, {0x9d, 0x94, 0xdb, 0x65, 0xac, 0xc5, 0xc3, 0x32}};
EFI_GUID gUefiInfoEfiSmmConfigurationProtocolGuid                         = {0x26eeb3de, 0xb689, 0x492e, {0x80, 0xf0, 0xbe, 0x8b, 0xd7, 0xda, 0x4b, 0xa7}};
EFI_GUID gUefiInfoEfiSmmControl2ProtocolGuid                              = {0x843dc720, 0xab1e, 0x42cb, {0x93, 0x57, 0x8a, 0x00, 0x78, 0xf3, 0x56, 0x1b}};
EFI_GUID gUefiInfoEfiSmmControlProtocolGuid                               = {0x8d12e231, 0xc667, 0x4fd1, {0x98, 0xf2, 0x24, 0x49, 0xa7, 0xe7, 0xb2, 0xe5}};
EFI_GUID gUefiInfoEfiSmmCpuIo2ProtocolGuid                                = {0x3242a9d8, 0xce70, 0x4aa0, {0x95, 0x5d, 0x5e, 0x7b, 0x14, 0x0d, 0xe4, 0xd2}};
EFI_GUID gUefiInfoEfiSmmCpuIoGuid                                         = {0x5f439a0b, 0x45d8, 0x4682, {0xa4, 0xf4, 0xf0, 0x57, 0x6b, 0x51, 0x34, 0x41}};
EFI_GUID gUefiInfoEfiSmmCpuProtocolGuid                                   = {0xeb346b97, 0x975f, 0x4a9f, {0x8b, 0x22, 0xf8, 0xe9, 0x2b, 0xb3, 0xd5, 0x69}};
EFI_GUID gUefiInfoEfiSmmCpuSaveStateProtocolGuid                          = {0x21f302ad, 0x6e94, 0x471b, {0x84, 0xbc, 0xb1, 0x48, 0x00, 0x40, 0x3a, 0x1d}};
EFI_GUID gUefiInfoEfiSmmEndOfDxeProtocolGuid                              = {0x24e70042, 0xd5c5, 0x4260, {0x8c, 0x39, 0x0a, 0xd3, 0xaa, 0x32, 0xe9, 0x3d}};
EFI_GUID gUefiInfoEfiSmmFaultTolerantWriteProtocolGuid                    = {0x3868fc3b, 0x7e45, 0x43a7, {0x90, 0x6c, 0x4b, 0xa4, 0x7d, 0xe1, 0x75, 0x4d}};
EFI_GUID gUefiInfoEfiSmmFirmwareVolumeBlockProtocolGuid                   = {0xd326d041, 0xbd31, 0x4c01, {0xb5, 0xa8, 0x62, 0x8b, 0xe8, 0x7f, 0x06, 0x53}};
EFI_GUID gUefiInfoEfiSmmGpiDispatch2ProtocolGuid                          = {0x25566b03, 0xb577, 0x4cbf, {0x95, 0x8c, 0xed, 0x66, 0x3e, 0xa2, 0x43, 0x80}};
EFI_GUID gUefiInfoEfiSmmGpiDispatchProtocolGuid                           = {0xe0744b81, 0x9513, 0x49cd, {0x8c, 0xea, 0xe9, 0x24, 0x5e, 0x70, 0x39, 0xda}};
EFI_GUID gUefiInfoEfiSmmIchnDispatchExProtocolGuid                        = {0x3920405b, 0xc897, 0x44da, {0x88, 0xf3, 0x4c, 0x49, 0x8a, 0x6f, 0xf7, 0x36}};
EFI_GUID gUefiInfoEfiSmmIchnDispatchProtocolGuid                          = {0xc50b323e, 0x9075, 0x4f2a, {0xac, 0x8e, 0xd2, 0x59, 0x6a, 0x10, 0x85, 0xcc}};
EFI_GUID gUefiInfoEfiSmmIoTrapDispatch2ProtocolGuid                       = {0x58dc368d, 0x7bfa, 0x4e77, {0xab, 0xbc, 0x0e, 0x29, 0x41, 0x8d, 0xf9, 0x30}};
EFI_GUID gUefiInfoEfiSmmIoTrapDispatchProtocolGuid                        = {0x58dc368d, 0x7bfa, 0x4e77, {0xab, 0xbc, 0x0e, 0x29, 0x41, 0x8d, 0xf9, 0x30}};
EFI_GUID gUefiInfoEfiSmmLockBoxCommunicationGuid                          = {0x2a3cfebd, 0x27e8, 0x4d0a, {0x8b, 0x79, 0xd6, 0x88, 0xc2, 0xa3, 0xe1, 0xc0}};
EFI_GUID gUefiInfoEfiSmmPciRootBridgeIoProtocolGuid                       = {0x8bc1714d, 0xffcb, 0x41c3, {0x89, 0xdc, 0x6c, 0x74, 0xd0, 0x6d, 0x98, 0xea}};
EFI_GUID gUefiInfoEfiSmmPeiSmramMemoryReserveGuid                         = {0x6dadf1d1, 0xd4cc, 0x4910, {0xbb, 0x6e, 0x82, 0xb1, 0xfd, 0x80, 0xff, 0x3d}};
EFI_GUID gUefiInfoEfiSmmPeriodicTimerDispatch2ProtocolGuid                = {0x4cec368e, 0x8e8e, 0x4d71, {0x8b, 0xe1, 0x95, 0x8c, 0x45, 0xfc, 0x8a, 0x53}};
EFI_GUID gUefiInfoEfiSmmPeriodicTimerDispatchProtocolGuid                 = {0x9cca03fc, 0x4c9e, 0x4a19, {0x9b, 0x06, 0xed, 0x7b, 0x47, 0x9b, 0xde, 0x55}};
EFI_GUID gUefiInfoEfiSmmPowerButtonDispatch2ProtocolGuid                  = {0x1b1183fa, 0x1823, 0x46a7, {0x88, 0x72, 0x9c, 0x57, 0x87, 0x55, 0x40, 0x9d}};
EFI_GUID gUefiInfoEfiSmmPowerButtonDispatchProtocolGuid                   = {0xb709efa0, 0x47a6, 0x4b41, {0xb9, 0x31, 0x12, 0xec, 0xe7, 0xa8, 0xee, 0x56}};
EFI_GUID gUefiInfoEfiSmmReadyToLockProtocolGuid                           = {0x47b7fa8c, 0xf4bd, 0x4af6, {0x82, 0x00, 0x33, 0x30, 0x86, 0xf0, 0xd2, 0xc8}};
EFI_GUID gUefiInfoEfiSmmRscHandlerProtocolGuid                            = {0x2ff29fa7, 0x5e80, 0x4ed9, {0xb3, 0x80, 0x01, 0x7d, 0x3c, 0x55, 0x4f, 0xf4}};
EFI_GUID gUefiInfoEfiSmmSmbusProtocolGuid                                 = {0x72e40094, 0x2ee1, 0x497a, {0x8f, 0x33, 0x4c, 0x93, 0x4a, 0x9e, 0x9c, 0x0c}};
EFI_GUID gUefiInfoEfiSmmSpiProtocolGuid                                   = {0xd9072c35, 0xeb8f, 0x43ad, {0xa2, 0x20, 0x34, 0xd4, 0x0e, 0x2a, 0x82, 0x85}};
EFI_GUID gUefiInfoEfiSmmStandbyButtonDispatch2ProtocolGuid                = {0x7300c4a1, 0x43f2, 0x4017, {0xa5, 0x1b, 0xc8, 0x1a, 0x7f, 0x40, 0x58, 0x5b}};
EFI_GUID gUefiInfoEfiSmmStandbyButtonDispatchProtocolGuid                 = {0x78965b98, 0xb0bf, 0x449e, {0x8b, 0x22, 0xd2, 0x91, 0x4e, 0x49, 0x8a, 0x98}};
EFI_GUID gUefiInfoEfiSmmStatusCodeProtocolGuid                            = {0x6afd2b77, 0x98c1, 0x4acd, {0xa6, 0xf9, 0x8a, 0x94, 0x39, 0xde, 0x0f, 0xb1}};
EFI_GUID gUefiInfoEfiSmmSwapAddressRangeProtocolGuid                      = {0x67c4f112, 0x3385, 0x4e55, {0x9c, 0x5b, 0xc0, 0x5b, 0x71, 0x7c, 0x42, 0x28}};
EFI_GUID gUefiInfoEfiSmmSwDispatch2ProtocolGuid                           = {0x18a3c6dc, 0x5eea, 0x48c8, {0xa1, 0xc1, 0xb5, 0x33, 0x89, 0xf9, 0x89, 0x99}};
EFI_GUID gUefiInfoEfiSmmSwDispatchProtocolGuid                            = {0xe541b773, 0xdd11, 0x420c, {0xb0, 0x26, 0xdf, 0x99, 0x36, 0x53, 0xf8, 0xbf}};
EFI_GUID gUefiInfoEfiSmmSxDispatch2ProtocolGuid                           = {0x456d2859, 0xa84b, 0x4e47, {0xa2, 0xee, 0x32, 0x76, 0xd8, 0x86, 0x99, 0x7d}};
EFI_GUID gUefiInfoEfiSmmSxDispatchProtocolGuid                            = {0x14fc52be, 0x01dc, 0x426c, {0x91, 0xae, 0xa2, 0x3c, 0x3e, 0x22, 0x0a, 0xe8}};
EFI_GUID gUefiInfoEfiSmmUsbDispatch2ProtocolGuid                          = {0xee9b8d90, 0xc5a6, 0x40a2, {0xbd, 0xe2, 0x52, 0x55, 0x8d, 0x33, 0xcc, 0xa1}};
EFI_GUID gUefiInfoEfiSmmUsbDispatchProtocolGuid                           = {0xa05b6ffd, 0x87af, 0x4e42, {0x95, 0xc9, 0x62, 0x28, 0xb6, 0x3c, 0xf3, 0xf3}};
EFI_GUID gUefiInfoEfiSmmVariableProtocolGuid                              = {0xed32d533, 0x99e6, 0x4209, {0x9c, 0xc0, 0x2d, 0x72, 0xcd, 0xd9, 0x98, 0xa7}};
EFI_GUID gUefiInfoEfiSocketProtocolGuid                                   = {0x58e6ed63, 0x1694, 0x440b, {0x93, 0x88, 0xe9, 0x8f, 0xed, 0x6b, 0x65, 0xaf}};
EFI_GUID gUefiInfoEfiSocketServiceBindingProtocolGuid                     = {0x8aaedb2a, 0xa6bb, 0x47c6, {0x94, 0xce, 0x1b, 0x80, 0x96, 0x42, 0x3f, 0x2a}};
EFI_GUID gUefiInfoEfiSourceLevelDebugPkgTokenSpaceGuid                    = {0x865a5aab, 0xb85d, 0x474c, {0x84, 0x55, 0x65, 0xd1, 0xbe, 0x84, 0x4b, 0xe2}};
EFI_GUID gUefiInfoEfiSpeakerInterfaceProtocolGuid                         = {0x400b4476, 0x3081, 0x11d6, {0x87, 0xed, 0x00, 0x06, 0x29, 0x45, 0xc3, 0xb9}};
EFI_GUID gUefiInfoEfiSpiAcpiProtocolGuid                                  = {0x9f49a879, 0x3d71, 0x42b3, {0xa0, 0xad, 0xdd, 0xb1, 0xf3, 0x30, 0x10, 0xa3}};
EFI_GUID gUefiInfoEfiSpiBusProtocolGuid                                   = {0x137b3044, 0xf6d7, 0x473e, {0xa6, 0x25, 0x9f, 0xb9, 0x25, 0x05, 0xc1, 0x80}};
EFI_GUID gUefiInfoEfiSpiHostProtocolGuid                                  = {0x951b65e5, 0x8872, 0x41ed, {0xad, 0x1d, 0xd5, 0x68, 0x1f, 0x4a, 0xf0, 0x33}};
EFI_GUID gUefiInfoEfiSpiProtocolGuid                                      = {0x1156efc6, 0xea32, 0x4396, {0xb5, 0xd5, 0x26, 0x93, 0x2e, 0x83, 0xc3, 0x13}};
EFI_GUID gUefiInfoEfiStandardErrorDeviceGuid                              = {0xd3b36f2d, 0xd551, 0x11d4, {0x9a, 0x46, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiStatusCodeDataTypeDebugGuid                          = {0x9a4e9246, 0xd553, 0x11d5, {0x87, 0xe2, 0x00, 0x06, 0x29, 0x45, 0xc3, 0xb9}};
EFI_GUID gUefiInfoEfiStatusCodeDataTypeStringGuid                         = {0x92d11080, 0x496f, 0x4d95, {0xbe, 0x7e, 0x03, 0x74, 0x88, 0x38, 0x2b, 0x0a}};
EFI_GUID gUefiInfoEfiStatusCodeRuntimeProtocolGuid                        = {0xd2b2b828, 0x0826, 0x48a7, {0xb3, 0xdf, 0x98, 0x3c, 0x00, 0x60, 0x24, 0xf0}};
EFI_GUID gUefiInfoEfiStatusCodeSpecificDataGuid                           = {0x335984bd, 0xe805, 0x409a, {0xb8, 0xf8, 0xd2, 0x7e, 0xce, 0x5f, 0xf7, 0xa6}};
EFI_GUID gUefiInfoEfiStorageSecurityCommandProtocolGuid                   = {0xc88b0b6d, 0x0dfc, 0x49a7, {0x9c, 0xb4, 0x49, 0x07, 0x4b, 0x4c, 0x3a, 0x78}};
EFI_GUID gUefiInfoEfiSupplicantProtocolGuid                               = {0x54fcc43e, 0xaa89, 0x4333, {0x9a, 0x85, 0xcd, 0xea, 0x24, 0x05, 0x1e, 0x9e}};
EFI_GUID gUefiInfoEfiSupplicantServiceBindingProtocolGuid                 = {0x45bcd98e, 0x59ad, 0x4174, {0x95, 0x46, 0x34, 0x4a, 0x07, 0x48, 0x58, 0x98}};
EFI_GUID gUefiInfoEfiSwapAddressRangeProtocolGuid                         = {0x1259f60d, 0xb754, 0x468e, {0xa7, 0x89, 0x4d, 0xb8, 0x5d, 0x55, 0xe8, 0x7e}};
EFI_GUID gUefiInfoEfiSystemNvDataFvGuid                                   = {0xfff12b8d, 0x7696, 0x4c8b, {0xa9, 0x85, 0x27, 0x47, 0x07, 0x5b, 0x4f, 0x50}};
EFI_GUID gUefiInfoEfiSystemPartitionGuid                                  = {0xc12a7328, 0xf81f, 0x11d2, {0xba, 0x4b, 0x00, 0xa0, 0xc9, 0x3e, 0xc9, 0x3b}};
EFI_GUID gUefiInfoEfiSystemResourceTableGuid                              = {0xb122a263, 0x3661, 0x4f68, {0x99, 0x29, 0x78, 0xf8, 0xb0, 0xd6, 0x21, 0x80}};
EFI_GUID gUefiInfoEfiTapeIoProtocolGuid                                   = {0x1e93e633, 0xd65a, 0x459e, {0xab, 0x84, 0x93, 0xd9, 0xec, 0x26, 0x6d, 0x18}};
EFI_GUID gUefiInfoEfiTcgPrivateInterfaceGuid                              = {0x7a28436a, 0xe113, 0x406a, {0xaf, 0xf9, 0x0d, 0xbf, 0x7f, 0x64, 0x3e, 0x02}};
EFI_GUID gUefiInfoEfiTcgProtocolGuid                                      = {0xf541796d, 0xa62e, 0x4954, {0xa7, 0x75, 0x95, 0x84, 0xf6, 0x1b, 0x9c, 0xdd}};
EFI_GUID gUefiInfoEfiTcoResetProtocolGuid                                 = {0xa6a79162, 0xe325, 0x4c30, {0xbc, 0xc3, 0x59, 0x37, 0x30, 0x64, 0xef, 0xb3}};
EFI_GUID gUefiInfoEfiTcp4ProtocolGuid                                     = {0x65530bc7, 0xa359, 0x410f, {0xb0, 0x10, 0x5a, 0xad, 0xc7, 0xec, 0x2b, 0x62}};
EFI_GUID gUefiInfoEfiTcp4ServiceBindingProtocolGuid                       = {0x00720665, 0x67eb, 0x4a99, {0xba, 0xf7, 0xd3, 0xc3, 0x3a, 0x1c, 0x7c, 0xc9}};
EFI_GUID gUefiInfoEfiTcp6ProtocolGuid                                     = {0x46e44855, 0xbd60, 0x4ab7, {0xab, 0x0d, 0xa6, 0x79, 0xb9, 0x44, 0x7d, 0x77}};
EFI_GUID gUefiInfoEfiTcp6ServiceBindingProtocolGuid                       = {0xec20eb79, 0x6c1a, 0x4664, {0x9a, 0x0d, 0xd2, 0xe4, 0xcc, 0x16, 0xd6, 0x64}};
EFI_GUID gUefiInfoEfiTdtOperationProtocolGuid                             = {0xfd301ba4, 0x5e62, 0x4679, {0xa0, 0x6f, 0xe0, 0x9a, 0xab, 0xdd, 0x2a, 0x91}};
EFI_GUID gUefiInfoEfiTdtProtocolGuid                                      = {0x0bf70067, 0xd53b, 0x42df, {0xb7, 0x70, 0xe9, 0x2c, 0x91, 0xc6, 0x14, 0x11}};
EFI_GUID gUefiInfoEfiTemporaryRamDonePpiGuid                              = {0xceab683c, 0xec56, 0x4a2d, {0xa9, 0x06, 0x40, 0x53, 0xfa, 0x4e, 0x9c, 0x16}};
EFI_GUID gUefiInfoEfiTemporaryRamSupportPpiGuid                           = {0xdbe23aa9, 0xa345, 0x4b97, {0x85, 0xb6, 0xb2, 0x26, 0xf1, 0x61, 0x73, 0x89}};
EFI_GUID gUefiInfoEfiTimerArchProtocolGuid                                = {0x26baccb3, 0x6f42, 0x11d4, {0xbc, 0xe7, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiTimestampProtocolGuid                                = {0xafbfde41, 0x2e6e, 0x4262, {0xba, 0x65, 0x62, 0xb9, 0x23, 0x6e, 0x54, 0x95}};
EFI_GUID gUefiInfoEfiTlsConfigurationProtocolGuid                         = {0x1682fe44, 0xbd7a, 0x4407, {0xb7, 0xc7, 0xdc, 0xa3, 0x7c, 0xa3, 0x92, 0x2d}};
EFI_GUID gUefiInfoEfiTlsProtocolGuid                                      = {0x00ca959f, 0x6cfa, 0x4db1, {0x95, 0xbc, 0xe4, 0x6c, 0x47, 0x51, 0x43, 0x90}};
EFI_GUID gUefiInfoEfiTlsServiceBindingProtocolGuid                        = {0x952cb795, 0xff36, 0x48cf, {0xa2, 0x49, 0x4d, 0xf4, 0x86, 0xd6, 0xab, 0x8d}};
EFI_GUID gUefiInfoEfiTpmDeviceInstanceNoneGuid                            = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
EFI_GUID gUefiInfoEfiTpmDeviceInstanceTpm12Guid                           = {0x8b01e5b6, 0x4f19, 0x46e8, {0xab, 0x93, 0x1c, 0x53, 0x67, 0x1b, 0x90, 0xcc}};
EFI_GUID gUefiInfoEfiTpmDeviceInstanceTpm20DtpmGuid                       = {0x286bf25a, 0xc2c3, 0x408c, {0xb3, 0xb4, 0x25, 0xe6, 0x75, 0x8b, 0x73, 0x17}};
EFI_GUID gUefiInfoEfiTpmDeviceSelectedGuid                                = {0x7f4158d3, 0x074d, 0x456d, {0x8c, 0xb2, 0x01, 0xf9, 0xc8, 0xf7, 0x9d, 0xaa}};
EFI_GUID gUefiInfoEfiTpmMpDriverProtocolGuid                              = {0xde161cfe, 0x1e60, 0x42a1, {0x8c, 0xc3, 0xee, 0x7e, 0xf0, 0x73, 0x52, 0x12}};
EFI_GUID gUefiInfoEfiTrEEPhysicalPresenceGuid                             = {0xf24643c2, 0xc622, 0x494e, {0x8a, 0x0d, 0x46, 0x32, 0x57, 0x9c, 0x2d, 0x5b}};
EFI_GUID gUefiInfoEfiTrEEProtocolGuid                                     = {0x607f766c, 0x7455, 0x42be, {0x93, 0x0b, 0xe4, 0xd7, 0x6d, 0xb2, 0x72, 0x0f}};
EFI_GUID gUefiInfoEfiTscFrequencyGuid                                     = {0xdba6a7e3, 0xbb57, 0x4be7, {0x8a, 0xf8, 0xd5, 0x78, 0xdb, 0x7e, 0x56, 0x87}};
EFI_GUID gUefiInfoEfiUartDevicePathGuid                                   = {0x37499a9d, 0x542f, 0x4c89, {0xa0, 0x26, 0x35, 0xda, 0x14, 0x20, 0x94, 0xe4}};
EFI_GUID gUefiInfoEfiUdp4ProtocolGuid                                     = {0x3ad9df29, 0x4501, 0x478d, {0xb1, 0xf8, 0x7f, 0x7f, 0xe7, 0x0e, 0x50, 0xf3}};
EFI_GUID gUefiInfoEfiUdp4ServiceBindingProtocolGuid                       = {0x83f01464, 0x99bd, 0x45e5, {0xb3, 0x83, 0xaf, 0x63, 0x05, 0xd8, 0xe9, 0xe6}};
EFI_GUID gUefiInfoEfiUdp6ProtocolGuid                                     = {0x4f948815, 0xb4b9, 0x43cb, {0x8a, 0x33, 0x90, 0xe0, 0x60, 0xb3, 0x49, 0x55}};
EFI_GUID gUefiInfoEfiUdp6ServiceBindingProtocolGuid                       = {0x66ed4721, 0x3c98, 0x4d3e, {0x81, 0xe3, 0xd0, 0x3d, 0xd3, 0x9a, 0x72, 0x54}};
EFI_GUID gUefiInfoEfiUfsDeviceConfigProtocolGuid                          = {0xb81bfab0, 0x0eb3, 0x4cf9, {0x84, 0x65, 0x7f, 0xa9, 0x86, 0x36, 0x16, 0x64}};
EFI_GUID gUefiInfoEfiUgaDrawProtocolGuid                                  = {0x982c298b, 0xf4fa, 0x41cb, {0xb8, 0x38, 0x77, 0xaa, 0x68, 0x8f, 0xb8, 0x39}};
EFI_GUID gUefiInfoEfiUgaIoProtocolGuid                                    = {0x61a4d49e, 0x6f68, 0x4f1b, {0xb9, 0x22, 0xa8, 0x6e, 0xed, 0x0b, 0x07, 0xa2}};
EFI_GUID gUefiInfoEfiUnicodeCollation2ProtocolGuid                        = {0xa4c751fc, 0x23ae, 0x4c3e, {0x92, 0xe9, 0x49, 0x64, 0xcf, 0x63, 0xf3, 0x49}};
EFI_GUID gUefiInfoEfiUnicodeCollationProtocolGuid                         = {0x1d85cd7f, 0xf43d, 0x11d2, {0x9a, 0x0c, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiUpdateDataFileGuid                                   = {0x283fa2ee, 0x532c, 0x484d, {0x93, 0x83, 0x9f, 0x93, 0xb3, 0x6f, 0x0b, 0x7e}};
EFI_GUID gUefiInfoEfiUsb2HcProtocolGuid                                   = {0x3e745226, 0x9818, 0x45b6, {0xa2, 0xac, 0xd7, 0xcd, 0x0e, 0x8b, 0xa2, 0xbc}};
EFI_GUID gUefiInfoEfiUsbFunctionIoProtocolGuid                            = {0x32d2963a, 0xfe5d, 0x4f30, {0xb6, 0x33, 0x6e, 0x5d, 0xc5, 0x58, 0x03, 0xcc}};
EFI_GUID gUefiInfoEfiUsbHcProtocolGuid                                    = {0xf5089266, 0x1aa0, 0x4953, {0x97, 0xd8, 0x56, 0x2f, 0x8a, 0x73, 0xb5, 0x19}};
EFI_GUID gUefiInfoEfiUsbInitProtocolGuid                                  = {0x2da15ac7, 0x4909, 0x4c4c, {0xb8, 0xc3, 0xa7, 0x42, 0x19, 0x5e, 0xa4, 0x6e}};
EFI_GUID gUefiInfoEfiUsbIoProtocolGuid                                    = {0x2b2f68d6, 0x0cd2, 0x44cf, {0x8e, 0x8b, 0xbb, 0xa2, 0x0b, 0x1b, 0x5b, 0x75}};
EFI_GUID gUefiInfoEfiUsbKeyboardConnectGuid                               = {0xad9c4381, 0x1ede, 0x430c, {0x8d, 0x42, 0x23, 0x76, 0x7c, 0x46, 0x5d, 0x52}};
EFI_GUID gUefiInfoEfiUserCredential2ProtocolGuid                          = {0xe98adb03, 0xb8b9, 0x4af8, {0xba, 0x20, 0x26, 0xe9, 0x11, 0x4c, 0xbc, 0xe5}};
EFI_GUID gUefiInfoEfiUserCredentialClassFingerprintGuid                   = {0x32cba21f, 0xf308, 0x4cbc, {0x9a, 0xb5, 0xf5, 0xa3, 0x69, 0x9f, 0x04, 0x4a}};
EFI_GUID gUefiInfoEfiUserCredentialClassHandprintGuid                     = {0x5917ef16, 0xf723, 0x4bb9, {0xa6, 0x4b, 0xd8, 0xc5, 0x32, 0xf4, 0xd8, 0xb5}};
EFI_GUID gUefiInfoEfiUserCredentialClassPasswordGuid                      = {0xf8e5058c, 0xccb6, 0x4714, {0xb2, 0x20, 0x3f, 0x7e, 0x3a, 0x64, 0x0b, 0xd1}};
EFI_GUID gUefiInfoEfiUserCredentialClassSecureCardGuid                    = {0x8a6b4a83, 0x42fe, 0x45d2, {0xa2, 0xef, 0x46, 0xf0, 0x6c, 0x7d, 0x98, 0x52}};
EFI_GUID gUefiInfoEfiUserCredentialClassSmartCardGuid                     = {0x5f03ba33, 0x8c6b, 0x4c24, {0xaa, 0x2e, 0x14, 0xa2, 0x65, 0x7b, 0xd4, 0x54}};
EFI_GUID gUefiInfoEfiUserCredentialClassUnknownGuid                       = {0x5cf32e68, 0x7660, 0x449b, {0x80, 0xe6, 0x7e, 0xa3, 0x6e, 0x03, 0xf6, 0xa8}};
EFI_GUID gUefiInfoEfiUserCredentialProtocolGuid                           = {0x71ee5e94, 0x65b9, 0x45d5, {0x82, 0x1a, 0x3a, 0x4d, 0x86, 0xcf, 0xe6, 0xbe}};
EFI_GUID gUefiInfoEfiUserInfoAccessSetupAdminGuid                         = {0x85b75607, 0xf7ce, 0x471e, {0xb7, 0xe4, 0x2a, 0xea, 0x5f, 0x72, 0x32, 0xee}};
EFI_GUID gUefiInfoEfiUserInfoAccessSetupNormalGuid                        = {0x1db29ae0, 0x9dcb, 0x43bc, {0x8d, 0x87, 0x5d, 0xa1, 0x49, 0x64, 0xdd, 0xe2}};
EFI_GUID gUefiInfoEfiUserInfoAccessSetupRestrictedGuid                    = {0xbdb38125, 0x4d63, 0x49f4, {0x82, 0x12, 0x61, 0xcf, 0x5a, 0x19, 0x0a, 0xf8}};
EFI_GUID gUefiInfoEfiUserManagerProtocolGuid                              = {0x6fd5b00c, 0xd426, 0x4283, {0x98, 0x87, 0x6c, 0xf5, 0xcf, 0x1c, 0xb1, 0xfe}};
EFI_GUID gUefiInfoEfiVariableArchProtocolGuid                             = {0x1e5668e2, 0x8481, 0x11d4, {0xbc, 0xf1, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiVariableGuid                                         = {0xddcf3616, 0x3275, 0x4164, {0x98, 0xb6, 0xfe, 0x85, 0x70, 0x7f, 0xfe, 0x7d}};
EFI_GUID gUefiInfoEfiVariableIndexTableGuid                               = {0x8cfdb8c8, 0xd6b2, 0x40f3, {0x8e, 0x97, 0x02, 0x30, 0x7c, 0xc9, 0x8b, 0x7c}};
EFI_GUID gUefiInfoEfiVariableWriteArchProtocolGuid                        = {0x6441f818, 0x6362, 0x4e44, {0xb5, 0x70, 0x7d, 0xba, 0x31, 0xdd, 0x24, 0x53}};
EFI_GUID gUefiInfoEfiVectorHandoffInfoPpiGuid                             = {0x3cd652b4, 0x6d33, 0x4dce, {0x89, 0xdb, 0x83, 0xdf, 0x97, 0x66, 0xfc, 0xca}};
EFI_GUID gUefiInfoEfiVectorHandoffTableGuid                               = {0x996ec11c, 0x5397, 0x4e73, {0xb5, 0x8f, 0x82, 0x7e, 0x52, 0x90, 0x6d, 0xef}};
EFI_GUID gUefiInfoEfiVendorKeysNvGuid                                     = {0x9073e4e0, 0x60ec, 0x4b6e, {0x99, 0x03, 0x4c, 0x22, 0x3c, 0x26, 0x0f, 0x3c}};
EFI_GUID gUefiInfoEfiVgaMiniPortProtocolGuid                              = {0xc7735a2f, 0x88f5, 0x4882, {0xae, 0x63, 0xfa, 0xac, 0x8c, 0x8b, 0x86, 0xb3}};
EFI_GUID gUefiInfoEfiVirtualCdGuid                                        = {0x3d5abd30, 0x4175, 0x87ce, {0x6d, 0x64, 0xd2, 0xad, 0xe5, 0x23, 0xc4, 0xbb}};
EFI_GUID gUefiInfoEfiVirtualDiskGuid                                      = {0x77ab535a, 0x45fc, 0x624b, {0x55, 0x60, 0xf7, 0xb2, 0x81, 0xd1, 0xf9, 0x6e}};
EFI_GUID gUefiInfoEfiVlanConfigProtocolGuid                               = {0x9e23d768, 0xd2f3, 0x4366, {0x9f, 0xc3, 0x3a, 0x7a, 0xba, 0x86, 0x43, 0x74}};
EFI_GUID gUefiInfoEfiVlv2VariableGuid                                     = {0x10ba6bbe, 0xa97e, 0x41c3, {0x9a, 0x07, 0x60, 0x7a, 0xd9, 0xbd, 0x60, 0xe5}};
EFI_GUID gUefiInfoEfiVLVTokenSpaceGuid                                    = {0xca452c68, 0xdf0c, 0x45c9, {0x82, 0xfb, 0xea, 0xe4, 0x2b, 0x31, 0x29, 0x46}};
EFI_GUID gUefiInfoEfiVT100Guid                                            = {0xdfa66065, 0xb419, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiVT100PlusGuid                                        = {0x7baec70b, 0x57e0, 0x4c76, {0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43}};
EFI_GUID gUefiInfoEfiVt_100Guid                                           = {0xdfa66065, 0xb419, 0x11d3, {0x9a, 0x2d, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiVt_100PlusGuid                                       = {0x7baec70b, 0x57e0, 0x4c76, {0x8e, 0x87, 0x2f, 0x9e, 0x28, 0x08, 0x83, 0x43}};
EFI_GUID gUefiInfoEfiVTUTF8Guid                                           = {0xad15a0d6, 0x8bec, 0x4acf, {0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88}};
EFI_GUID gUefiInfoEfiVtUtf8Guid                                           = {0xad15a0d6, 0x8bec, 0x4acf, {0xa0, 0x73, 0xd0, 0x1d, 0xe7, 0x7e, 0x2d, 0x88}};
EFI_GUID gUefiInfoEfiWatchdogTimerArchProtocolGuid                        = {0x665e3ff5, 0x46cc, 0x11d4, {0x9a, 0x38, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEfiWatchdogTimerDriverProtocolGuid                      = {0xd5b06d16, 0x2ea1, 0x4def, {0x98, 0xd0, 0xa0, 0x5d, 0x40, 0x72, 0x84, 0x17}};
EFI_GUID gUefiInfoEfiWiFi2ProtocolGuid                                    = {0x1b0fb9bf, 0x699d, 0x4fdd, {0xa7, 0xc3, 0x25, 0x46, 0x68, 0x1b, 0xf6, 0x3b}};
EFI_GUID gUefiInfoEfiWiFiProtocolGuid                                     = {0x0da55bc9, 0x45f8, 0x4bb4, {0x87, 0x19, 0x52, 0x24, 0xf1, 0x8a, 0x4d, 0x45}};
EFI_GUID gUefiInfoEfiWindowsDumpTableGuid                                 = {0x0e1d2972, 0x65af, 0x4ac1, {0xbf, 0xa3, 0xce, 0xf4, 0xab, 0x0c, 0x38, 0xfe}};
EFI_GUID gUefiInfoEfiWinNtConsoleGuid                                     = {0xba73672c, 0xa5d3, 0x11d4, {0xbd, 0x00, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtFileSystemGuid                                  = {0x0c95a935, 0xa006, 0x11d4, {0xbc, 0xfa, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtGopGuid                                         = {0x4e11e955, 0xccca, 0x11d4, {0xbd, 0x0d, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtIoProtocolGuid                                  = {0x96eb4ad6, 0xa32a, 0x11d4, {0xbc, 0xfd, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtPassThroughGuid                                 = {0xcc664eb8, 0x3c24, 0x4086, {0xb6, 0xf6, 0x34, 0xe8, 0x56, 0xbc, 0xe3, 0x6e}};
EFI_GUID gUefiInfoEfiWinNtPhysicalDisksGuid                               = {0x0c95a92f, 0xa006, 0x11d4, {0xbc, 0xfa, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtSerialPortGuid                                  = {0x0c95a93d, 0xa006, 0x11d4, {0xbc, 0xfa, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtSystemConfigGuid                                = {0xb347f047, 0xaf8c, 0x490e, {0xac, 0x07, 0x0a, 0xa9, 0xb7, 0xe5, 0x38, 0x58}};
EFI_GUID gUefiInfoEfiWinNtThunkProtocolGuid                               = {0x58c518b1, 0x76f3, 0x11d4, {0xbc, 0xea, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtUgaGuid                                         = {0xab248e99, 0xabe1, 0x11d4, {0xbd, 0x0d, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiWinNtVirtualDisksGuid                                = {0x0c95a928, 0xa006, 0x11d4, {0xbc, 0xfa, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoEfiXenInfoGuid                                          = {0xd3b46f3b, 0xd441, 0x1244, {0x9a, 0x12, 0x00, 0x12, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoEmbeddedDeviceGuid                                      = {0xbf4b9d10, 0x13ec, 0x43dd, {0x88, 0x80, 0xe9, 0x0b, 0x71, 0x8f, 0x27, 0xde}};
EFI_GUID gUefiInfoEmbeddedExternalDeviceProtocolGuid                      = {0x735f8c64, 0xd696, 0x44d0, {0xbd, 0xf2, 0x44, 0x7f, 0xd0, 0x5a, 0x54, 0x06}};
EFI_GUID gUefiInfoEmbeddedGpioProtocolGuid                                = {0x17a0a3d7, 0xc0a5, 0x4635, {0xbb, 0xd5, 0x07, 0x21, 0x87, 0xdf, 0xe2, 0xee}};
EFI_GUID gUefiInfoEmbeddedTokenSpaceGuid                                  = {0xe0d8ca17, 0x4276, 0x4386, {0xbb, 0x79, 0x48, 0xcb, 0x81, 0x3d, 0x3c, 0x4f}};
EFI_GUID gUefiInfoEmptyGuid                                               = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
EFI_GUID gUefiInfoEmuBlockIoProtocolGuid                                  = {0x6888a4ae, 0xafce, 0xe84b, {0x91, 0x02, 0xf7, 0xb9, 0xda, 0xe6, 0xa0, 0x30}};
EFI_GUID gUefiInfoEmuGraphicsWindowProtocolGuid                           = {0x30fd316a, 0x6728, 0x2e41, {0xa6, 0x90, 0x0d, 0x13, 0x33, 0xd8, 0xca, 0xc1}};
EFI_GUID gUefiInfoEmuIoThunkProtocolGuid                                  = {0x453368f6, 0x7c85, 0x434a, {0xa9, 0x8a, 0x72, 0xd1, 0xb7, 0xff, 0xa9, 0x26}};
EFI_GUID gUefiInfoEmulatorPkgTokenSpaceGuid                               = {0x4f792e68, 0xe8c8, 0x794e, {0xb1, 0xd8, 0x37, 0x03, 0xf3, 0xf2, 0xd5, 0xa5}};
EFI_GUID gUefiInfoEmuPhysicalDisksGuid                                    = {0xf2bdcc96, 0x8985, 0x11db, {0x87, 0x19, 0x00, 0x40, 0xd0, 0x2b, 0x18, 0x35}};
EFI_GUID gUefiInfoEmuSnpProtocolGuid                                      = {0xfd5fbe54, 0x8c35, 0xb345, {0x8a, 0x0f, 0x7a, 0xc8, 0xa5, 0xfd, 0x05, 0x21}};
EFI_GUID gUefiInfoEmuSystemConfigGuid                                     = {0xf8626165, 0x6ceb, 0x924a, {0xba, 0xfc, 0xf1, 0x3a, 0xb9, 0xd6, 0x57, 0x28}};
EFI_GUID gUefiInfoEmuThreadThunkProtocolGuid                              = {0x3b1e4b7c, 0x09d8, 0x944f, {0xa4, 0x08, 0x13, 0x09, 0xeb, 0x8b, 0x44, 0x27}};
EFI_GUID gUefiInfoEmuThunkPpiGuid                                         = {0xe113f896, 0x75cf, 0xf640, {0x81, 0x7f, 0xc8, 0x5a, 0x79, 0xe8, 0xae, 0x67}};
EFI_GUID gUefiInfoEmuThunkProtocolGuid                                    = {0x5cf32e0b, 0x8edf, 0x2e44, {0x9c, 0xda, 0x93, 0x20, 0x5e, 0x99, 0xec, 0x1c}};
EFI_GUID gUefiInfoEmuVirtualDisksGuid                                     = {0xf2ba331a, 0x8985, 0x11db, {0xa4, 0x06, 0x00, 0x40, 0xd0, 0x2b, 0x18, 0x35}};
EFI_GUID gUefiInfoEnhancedSpeedstepProtocolGuid                           = {0x91a1ddcf, 0x5374, 0x4939, {0x89, 0x51, 0xd7, 0x29, 0x3f, 0x1a, 0x78, 0x6f}};
EFI_GUID gUefiInfoEventExitBootServicesFailedGuid                         = {0x4f6c5507, 0x232f, 0x4787, {0xb9, 0x5e, 0x72, 0xf8, 0x62, 0x49, 0x0c, 0xb1}};
EFI_GUID gUefiInfoExitPmAuthProtocolGuid                                  = {0xd088a413, 0x0a70, 0x4217, {0xba, 0x55, 0x9a, 0x3c, 0xb6, 0x5c, 0x41, 0xb3}};
EFI_GUID gUefiInfoFdtTableGuid                                            = {0xb1b621d5, 0xf19c, 0x41a5, {0x83, 0x0b, 0xd9, 0x15, 0x2c, 0x69, 0xaa, 0xe0}};
EFI_GUID gUefiInfoFileExploreFormSetGuid                                  = {0x1f2d63e1, 0xfebd, 0x4dc7, {0x9c, 0xc5, 0xba, 0x2b, 0x1c, 0xef, 0x9c, 0x5b}};
EFI_GUID gUefiInfoFirmwareIdGuid                                          = {0x5e559c23, 0x1faa, 0x4ae1, {0x8d, 0x4a, 0xc6, 0xcf, 0x02, 0x6c, 0x76, 0x6f}};
EFI_GUID gUefiInfoFirmwarePerformanceS3PointerGuid                        = {0x0dc65adc, 0xa973, 0x4130, {0x8d, 0xf0, 0x2a, 0xdb, 0xeb, 0x9e, 0x4a, 0x31}};
EFI_GUID gUefiInfoFramerworkEfiFirmwareVolumeBlockProtocolGuid            = {0xde28bc59, 0x6228, 0x41bd, {0xbd, 0xf6, 0xa3, 0xb9, 0xad, 0xb5, 0x8d, 0xa1}};
EFI_GUID gUefiInfoFrameworkBdsFrontPageFormsetGuid                        = {0x9e0c30bc, 0x3f06, 0x4ba6, {0x82, 0x88, 0x09, 0x17, 0x9b, 0x85, 0x5d, 0xbe}};
EFI_GUID gUefiInfoFrameworkEfiMpServiceProtocolGuid                       = {0xf33261e7, 0x23cb, 0x11d5, {0xbd, 0x5c, 0x00, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
EFI_GUID gUefiInfoFrontPageFormSetGuid                                    = {0x9e0c30bc, 0x3f06, 0x4ba6, {0x82, 0x88, 0x09, 0x17, 0x9b, 0x85, 0x5d, 0xbe}};
EFI_GUID gUefiInfoFspBootLoaderTemporaryMemoryGuid                        = {0xbbcff46c, 0xc8d3, 0x4113, {0x89, 0x85, 0xb9, 0xd4, 0xf3, 0xb3, 0xf6, 0x4e}};
EFI_GUID gUefiInfoFspHeaderFileGuid                                       = {0x912740be, 0x2284, 0x4734, {0xb9, 0x71, 0x84, 0xb0, 0x27, 0x35, 0x3f, 0x0c}};
EFI_GUID gUefiInfoFspInitDonePpiGuid                                      = {0xf5ef05e4, 0xd538, 0x4774, {0x8f, 0x1b, 0xe9, 0x77, 0x30, 0x11, 0xe0, 0x38}};
EFI_GUID gUefiInfoFspNonVolatileStorageHobGuid                            = {0x721acf02, 0x4d77, 0x4c2a, {0xb3, 0xdc, 0x27, 0x0b, 0x7b, 0xa9, 0xe4, 0xb0}};
EFI_GUID gUefiInfoFspReservedMemoryResourceHobGfxGuid                     = {0x9c7c3aa7, 0x5332, 0x4917, {0x82, 0xb9, 0x56, 0xa5, 0xf3, 0xe6, 0x2a, 0x07}};
EFI_GUID gUefiInfoFspReservedMemoryResourceHobGuid                        = {0x69a79759, 0x1373, 0x4367, {0xa6, 0xc4, 0xc7, 0xf5, 0x9e, 0xfd, 0x98, 0x6e}};
EFI_GUID gUefiInfoFspReservedMemoryResourceHobMiscGuid                    = {0x00d6b14b, 0x7dd0, 0x4062, {0x88, 0x21, 0xe5, 0xf9, 0x6a, 0x2a, 0x1b, 0x00}};
EFI_GUID gUefiInfoFspReservedMemoryResourceHobTsegGuid                    = {0xd038747c, 0xd00c, 0x4980, {0xb3, 0x19, 0x49, 0x01, 0x99, 0xa4, 0x7d, 0x55}};
EFI_GUID gUefiInfoFspWrapperTokenSpaceGuid                                = {0x2bc1c74a, 0x122f, 0x40b2, {0xb2, 0x23, 0x08, 0x2b, 0x74, 0x65, 0x22, 0x5d}};
EFI_GUID gUefiInfoGetPcdInfoPpiGuid                                       = {0x4d8b155b, 0xc059, 0x4c8f, {0x89, 0x26, 0x06, 0xfd, 0x43, 0x31, 0xdb, 0x8a}};
EFI_GUID gUefiInfoGetPcdInfoProtocolGuid                                  = {0x5be40f57, 0xfa68, 0x4610, {0xbb, 0xbf, 0xe9, 0xc5, 0xfc, 0xda, 0xd3, 0x65}};
EFI_GUID gUefiInfoHandleParsingHiiGuid                                    = {0xb8969637, 0x81de, 0x43af, {0xbc, 0x9a, 0x24, 0xd9, 0x89, 0x13, 0xf2, 0xf6}};
EFI_GUID gUefiInfoHardwareInterruptProtocolGuid                           = {0x2890b3ea, 0x053d, 0x1643, {0xad, 0x0c, 0xd6, 0x48, 0x08, 0xda, 0x3f, 0xf1}};
EFI_GUID gUefiInfoHdBootDevicePathVariablGuid                             = {0xfab7e9e1, 0x39dd, 0x4f2b, {0x84, 0x08, 0xe2, 0x0e, 0x90, 0x6c, 0xb6, 0xde}};
EFI_GUID gUefiInfoHiiResourceSamleFormSetGuid                             = {0x4f4ef7f0, 0xaa29, 0x4ce9, {0xba, 0x41, 0x64, 0x3e, 0x01, 0x23, 0xa9, 0x9f}};
EFI_GUID gUefiInfoIdccDataHubGuid                                         = {0x788e1d9f, 0x1eab, 0x47d2, {0xa2, 0xf3, 0x78, 0xca, 0xe8, 0x7d, 0x60, 0x12}};
EFI_GUID gUefiInfoIdleLoopEventGuid                                       = {0x3c8d294c, 0x5fc3, 0x4451, {0xbb, 0x31, 0xc4, 0xc0, 0x32, 0x29, 0x5e, 0x6c}};
EFI_GUID gUefiInfoIgdOpRegionProtocolGuid                                 = {0xcdc5dddf, 0xe79d, 0x41ec, {0xa9, 0xb0, 0x65, 0x65, 0x49, 0x0d, 0xb9, 0xd3}};
EFI_GUID gUefiInfoIntelFspPkgTokenSpaceGuid                               = {0x834c0c5f, 0xadb3, 0x4372, {0xae, 0xeb, 0x03, 0xe4, 0xe9, 0xe6, 0xc5, 0x91}};
EFI_GUID gUefiInfoIp4IScsiConfigGuid                                      = {0x6456ed61, 0x3579, 0x41c9, {0x8a, 0x26, 0x0a, 0x0b, 0xd6, 0x2b, 0x78, 0xfc}};
EFI_GUID gUefiInfoIp6ConfigNvDataGuid                                     = {0x02eea107, 0x98db, 0x400e, {0x98, 0x30, 0x46, 0x0a, 0x15, 0x42, 0xd7, 0x99}};
EFI_GUID gUefiInfoIScsiCHAPAuthInfoGuid                                   = {0x786ec0ac, 0x65ae, 0x4d1b, {0xb1, 0x37, 0x0d, 0x11, 0x0a, 0x48, 0x37, 0x97}};
EFI_GUID gUefiInfoIScsiConfigGuid                                         = {0x4b47d616, 0xa8d6, 0x4552, {0x9d, 0x44, 0xcc, 0xad, 0x2e, 0x0f, 0x4c, 0xf9}};
EFI_GUID gUefiInfoItkDataVarGuid                                          = {0x3812723d, 0x7e48, 0x4e29, {0xbc, 0x27, 0xf5, 0xa3, 0x9a, 0xc9, 0x4e, 0xf1}};
EFI_GUID gUefiInfoLastEnumLangGuid                                        = {0x0e8c545b, 0xa2ee, 0x470d, {0x8e, 0x26, 0xbd, 0xa1, 0xa1, 0x3c, 0x0a, 0xa3}};
EFI_GUID gUefiInfoLdrMemoryDescriptorGuid                                 = {0x7701d7e5, 0x7d1d, 0x4432, {0xa4, 0x68, 0x67, 0x3d, 0xab, 0x8a, 0xde, 0x60}};
EFI_GUID gUefiInfoLoadFixedAddressConfigurationTableGuid                  = {0x2ca88b53, 0xd296, 0x4080, {0xa4, 0xa5, 0xca, 0xd9, 0xba, 0xe2, 0x4b, 0x09}};
EFI_GUID gUefiInfoLpssDummyProtocolGuid                                   = {0xaf4cc162, 0xd41c, 0x455a, {0xab, 0x45, 0x6d, 0xbc, 0xc1, 0xcd, 0x32, 0xf3}};
EFI_GUID gUefiInfoLzmaCustomDecompressGuid                                = {0xee4e5898, 0x3914, 0x4259, {0x9d, 0x6e, 0xdc, 0x7b, 0xd7, 0x94, 0x03, 0xcf}};
EFI_GUID gUefiInfoLzmaF86CustomDecompressGuid                             = {0xd42ae6bd, 0x1352, 0x4bfb, {0x90, 0x9a, 0xca, 0x72, 0xa6, 0xea, 0xe8, 0x89}};
EFI_GUID gUefiInfoMeasuredFvHobGuid                                       = {0xb2360b42, 0x7173, 0x420a, {0x86, 0x96, 0x46, 0xca, 0x6b, 0xab, 0x10, 0x60}};
EFI_GUID gUefiInfoMemInfoProtocolGuid                                     = {0x6f20f7c8, 0xe5ef, 0x4f21, {0x8d, 0x19, 0xed, 0xc5, 0xf0, 0xc4, 0x96, 0xae}};
EFI_GUID gUefiInfoMemoryStatusCodeRecordGuid                              = {0x060cc026, 0x4c0d, 0x4dda, {0x8f, 0x41, 0x59, 0x5f, 0xef, 0x00, 0xa5, 0x02}};
EFI_GUID gUefiInfoMfgModeVariableGuid                                     = {0xef14fd78, 0x0793, 0x4e2b, {0xac, 0x6d, 0x06, 0x28, 0x47, 0xe0, 0x17, 0x91}};
EFI_GUID gUefiInfoMpsTableGuid                                            = {0xeb9d2d2f, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoMtcVendorGuid                                           = {0xeb704011, 0x1402, 0x11d3, {0x8e, 0x77, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
EFI_GUID gUefiInfoNicIp4ConfigNvDataGuid                                  = {0x09d5b53f, 0xf4b0, 0x4f59, {0xa0, 0xb1, 0x7b, 0x57, 0xd3, 0x5c, 0x0e, 0x05}};
EFI_GUID gUefiInfoNtFwhPpiGuid                                            = {0x4e76928f, 0x50ad, 0x4334, {0xb0, 0x6b, 0xa8, 0x42, 0x13, 0x10, 0x8a, 0x57}};
EFI_GUID gUefiInfoNtPeiLoadFilePpiGuid                                    = {0xfd0c65eb, 0x0405, 0x4cd2, {0x8a, 0xee, 0xf4, 0x00, 0xef, 0x13, 0xba, 0xc2}};
EFI_GUID gUefiInfoObservableProtocolGuid                                  = {0xe227c522, 0xd5fe, 0x4a53, {0x87, 0xb1, 0x0f, 0xbe, 0x57, 0x0f, 0x98, 0xe9}};
EFI_GUID gUefiInfoOmap35xxTokenSpaceGuid                                  = {0x24b09abe, 0x4e47, 0x481c, {0xa9, 0xad, 0xce, 0xf1, 0x2c, 0x39, 0x23, 0x27}};
EFI_GUID gUefiInfoOptionRomPkgTokenSpaceGuid                              = {0x1e43298f, 0x3478, 0x41a7, {0xb5, 0x77, 0x86, 0x06, 0x46, 0x35, 0xc7, 0x28}};
EFI_GUID gUefiInfoOsSelectionVariableGuid                                 = {0x86843f56, 0x675d, 0x40a5, {0x95, 0x30, 0xbc, 0x85, 0x83, 0x72, 0xf1, 0x03}};
EFI_GUID gUefiInfoOvmfPlatformConfigGuid                                  = {0x7235c51c, 0x0c80, 0x4cab, {0x87, 0xac, 0x3b, 0x08, 0x4a, 0x63, 0x04, 0xb1}};
EFI_GUID gUefiInfoPcAtChipsetPkgTokenSpaceGuid                            = {0x326ae723, 0xae32, 0x4589, {0x98, 0xb8, 0xca, 0xc2, 0x3c, 0xdc, 0xc1, 0xb1}};
EFI_GUID gUefiInfoPcdDataBaseHobGuid                                      = {0xea296d92, 0x0b69, 0x423c, {0x8c, 0x28, 0x33, 0xb4, 0xe0, 0xa9, 0x12, 0x68}};
EFI_GUID gUefiInfoPcdDataBaseSignatureGuid                                = {0x3c7d193c, 0x682c, 0x4c14, {0xa6, 0x8f, 0x55, 0x2d, 0xea, 0x4f, 0x43, 0x7e}};
EFI_GUID gUefiInfoPcdPpiGuid                                              = {0x06e81c58, 0x4ad7, 0x44bc, {0x83, 0x90, 0xf1, 0x02, 0x65, 0xf7, 0x24, 0x80}};
EFI_GUID gUefiInfoPcdProtocolGuid                                         = {0x11b34006, 0xd85b, 0x4d0a, {0xa2, 0x90, 0xd5, 0xa5, 0x71, 0x31, 0x0e, 0xf7}};
EFI_GUID gUefiInfoPchInitPpiGuid                                          = {0x09ea894a, 0xbe0d, 0x4230, {0xa0, 0x03, 0xed, 0xc6, 0x93, 0xb4, 0x8e, 0x95}};
EFI_GUID gUefiInfoPchInitVariableGuid                                     = {0xe6c2f70a, 0xb604, 0x4877, {0x85, 0xba, 0xde, 0xec, 0x89, 0xe1, 0x17, 0xeb}};
EFI_GUID gUefiInfoPchPeiInitPpiGuid                                       = {0xacb93b08, 0x5cdc, 0x4a8f, {0x93, 0xd4, 0x06, 0xe3, 0x42, 0xdf, 0x18, 0x2e}};
EFI_GUID gUefiInfoPchPlatformPolicyPpiGuid                                = {0x15344673, 0xd365, 0x4be2, {0x85, 0x13, 0x14, 0x97, 0xcc, 0x07, 0x61, 0x1d}};
EFI_GUID gUefiInfoPchResetCallbackProtocolGuid                            = {0x3a3300ab, 0xc929, 0x487d, {0xab, 0x34, 0x15, 0x9b, 0xc1, 0x35, 0x62, 0xc0}};
EFI_GUID gUefiInfoPchResetProtocolGuid                                    = {0xdb63592c, 0xb8cc, 0x44c8, {0x91, 0x8c, 0x51, 0xf5, 0x34, 0x59, 0x8a, 0x5a}};
EFI_GUID gUefiInfoPchUsbPolicyPpiGuid                                     = {0xc02b0573, 0x2b4e, 0x4a31, {0xa3, 0x1a, 0x94, 0x56, 0x7b, 0x50, 0x44, 0x2c}};
EFI_GUID gUefiInfoPdmWindowButtonGuid                                     = {0x5f65dfdb, 0xac20, 0x4f43, {0x9b, 0x21, 0x26, 0x9e, 0x81, 0xa0, 0xea, 0x7e}};
EFI_GUID gUefiInfoPdmWindowSpinGuid                                       = {0x60b27e1a, 0xd65e, 0x4db0, {0xb2, 0xbb, 0xc1, 0x6f, 0xa7, 0x1e, 0x44, 0xab}};
EFI_GUID gUefiInfoPeCoffLoaderProtocolGuid                                = {0xb323179b, 0x97fb, 0x477e, {0xb0, 0xfe, 0xd8, 0x85, 0x91, 0xfa, 0x11, 0xab}};
EFI_GUID gUefiInfoPeiAtaControllerPpiGuid                                 = {0xa45e60d1, 0xc719, 0x44aa, {0xb0, 0x7a, 0xaa, 0x77, 0x7f, 0x85, 0x90, 0x6d}};
EFI_GUID gUefiInfoPeiBlockIoPpiGuid                                       = {0xbc5fa650, 0xedbb, 0x4d0d, {0xb3, 0xa3, 0xd9, 0x89, 0x07, 0xf8, 0x47, 0xdf}};
EFI_GUID gUefiInfoPeiCachePpiGuid                                         = {0xc153205a, 0xe898, 0x4c24, {0x86, 0x89, 0xa4, 0xb4, 0xbc, 0xc5, 0xc8, 0xa2}};
EFI_GUID gUefiInfoPeiCapsuleOnDataCdGuid                                  = {0x5cac0099, 0x0dc9, 0x48e5, {0x80, 0x68, 0xbb, 0x95, 0xf5, 0x40, 0x0a, 0x9f}};
EFI_GUID gUefiInfoPeiCapsuleOnFatFloppyDiskGuid                           = {0x2e3d2e75, 0x9b2e, 0x412d, {0xb4, 0xb1, 0x70, 0x41, 0x6b, 0x87, 0x00, 0xff}};
EFI_GUID gUefiInfoPeiCapsuleOnFatIdeDiskGuid                              = {0xb38573b6, 0x6200, 0x4ac5, {0xb5, 0x1d, 0x82, 0xe6, 0x59, 0x38, 0xd7, 0x83}};
EFI_GUID gUefiInfoPeiCapsuleOnFatUsbDiskGuid                              = {0x0ffbce19, 0x324c, 0x4690, {0xa0, 0x09, 0x98, 0xc6, 0xae, 0x2e, 0xb1, 0x86}};
EFI_GUID gUefiInfoPeiCapsulePpiGuid                                       = {0x3acf33ee, 0xd892, 0x40f4, {0xa2, 0xfc, 0x38, 0x54, 0xd2, 0xe1, 0x32, 0x3d}};
EFI_GUID gUefiInfoPeiDebugDispatchPpiGuid                                 = {0xc9737920, 0xc2ad, 0x41c3, {0xb1, 0x33, 0x0f, 0x9c, 0x25, 0x1b, 0x67, 0x43}};
EFI_GUID gUefiInfoPeiHeciPpiGuid                                          = {0xee0ea811, 0xfbd9, 0x4777, {0xb9, 0x5a, 0xba, 0x4f, 0x71, 0x10, 0x1f, 0x74}};
EFI_GUID gUefiInfoPeiLockPhysicalPresencePpiGuid                          = {0xef9aefe5, 0x2bd3, 0x4031, {0xaf, 0x7d, 0x5e, 0xfe, 0x5a, 0xbb, 0x9a, 0x0d}};
EFI_GUID gUefiInfoPeiMfgMemoryTestPpiGuid                                 = {0xab294a92, 0xeaf5, 0x4cf3, {0xab, 0x2b, 0x2d, 0x4b, 0xed, 0x4d, 0xb6, 0x3d}};
EFI_GUID gUefiInfoPeiNtAutoScanPpiGuid                                    = {0x0dce384d, 0x007c, 0x4ba5, {0x94, 0xbd, 0x0f, 0x6e, 0xb6, 0x4d, 0x2a, 0xa9}};
EFI_GUID gUefiInfoPeiNtThunkPpiGuid                                       = {0x98c281e5, 0xf906, 0x43dd, {0xa9, 0x2b, 0xb0, 0x03, 0xbf, 0x27, 0x65, 0xda}};
EFI_GUID gUefiInfoPeiPostBootScriptTablePpiGuid                           = {0x88c9d306, 0x0900, 0x4eb5, {0x82, 0x60, 0x3e, 0x2d, 0xbe, 0xda, 0x1f, 0x89}};
EFI_GUID gUefiInfoPeiPostScriptTablePpiGuid                               = {0x88c9d306, 0x0900, 0x4eb5, {0x82, 0x60, 0x3e, 0x2d, 0xbe, 0xda, 0x1f, 0x89}};
EFI_GUID gUefiInfoPeiSdhcPpiGuid                                          = {0xf4ef9d7a, 0x98c5, 0x4c1a, {0xb4, 0xd9, 0xd8, 0xd8, 0x72, 0x65, 0xbe, 0x0c}};
EFI_GUID gUefiInfoPeiSecPerformancePpiGuid                                = {0x0ecc666b, 0x4662, 0x47f9, {0x9d, 0xd5, 0xd0, 0x96, 0xff, 0x7d, 0xa4, 0x9e}};
EFI_GUID gUefiInfoPeiSeCPlatformPolicyPpiGuid                             = {0x7ae3ceb7, 0x2ee2, 0x48fa, {0xaa, 0x49, 0x35, 0x10, 0xbc, 0x83, 0xca, 0xbf}};
EFI_GUID gUefiInfoPeiSerialPortPpiGuid                                    = {0x490e9d85, 0x8aef, 0x4193, {0x8e, 0x56, 0xf7, 0x34, 0xa9, 0xff, 0xac, 0x8b}};
EFI_GUID gUefiInfoPeiSha256HashPpiGuid                                    = {0x950e191b, 0x8524, 0x4f51, {0x80, 0xa1, 0x5c, 0x4f, 0x1b, 0x03, 0xf3, 0x5c}};
EFI_GUID gUefiInfoPeiSmbusPolicyPpiGuid                                   = {0x63b6e435, 0x32bc, 0x49c6, {0x81, 0xbd, 0xb7, 0xa1, 0xa0, 0xfe, 0x1a, 0x6c}};
EFI_GUID gUefiInfoPeiSmmAccessPpiGuid                                     = {0x268f33a9, 0xcccd, 0x48be, {0x88, 0x17, 0x86, 0x05, 0x3a, 0xc3, 0x2e, 0xd6}};
EFI_GUID gUefiInfoPeiSmmControlPpiGuid                                    = {0x61c68702, 0x4d7e, 0x4f43, {0x8d, 0xef, 0xa7, 0x43, 0x05, 0xce, 0x74, 0xc5}};
EFI_GUID gUefiInfoPeiSpeakerInterfacePpiGuid                              = {0x30ac275e, 0xbb30, 0x4b84, {0xa1, 0xcd, 0x0a, 0xf1, 0x32, 0x2c, 0x89, 0xc0}};
EFI_GUID gUefiInfoPeiSpiPpiGuid                                           = {0xa38c6898, 0x2b5c, 0x4ff6, {0x93, 0x26, 0x2e, 0x63, 0x21, 0x2e, 0x56, 0xc2}};
EFI_GUID gUefiInfoPeiTpmInitializationDonePpiGuid                         = {0xa030d115, 0x54dd, 0x447b, {0x90, 0x64, 0xf2, 0x06, 0x88, 0x3d, 0x7c, 0xcc}};
EFI_GUID gUefiInfoPeiTpmInitializedPpiGuid                                = {0xe9db0d58, 0xd48d, 0x47f6, {0x9c, 0x6e, 0x6f, 0x40, 0xe8, 0x6c, 0x7b, 0x41}};
EFI_GUID gUefiInfoPeiUsb2HostControllerPpiGuid                            = {0xfedd6305, 0xe2d7, 0x4ed5, {0x9f, 0xaa, 0xda, 0x08, 0x0e, 0x33, 0x6c, 0x22}};
EFI_GUID gUefiInfoPeiUsbControllerPpiGuid                                 = {0x3bc1f6de, 0x693e, 0x4547, {0xa3, 0x00, 0x21, 0x82, 0x3c, 0xa4, 0x20, 0xb2}};
EFI_GUID gUefiInfoPeiUsbHostControllerPpiGuid                             = {0x652b38a9, 0x77f4, 0x453f, {0x89, 0xd5, 0xe7, 0xbd, 0xc3, 0x52, 0xfc, 0x53}};
EFI_GUID gUefiInfoPeiUsbIoPpiGuid                                         = {0x7c29785c, 0x66b9, 0x49fc, {0xb7, 0x97, 0x1c, 0xa5, 0x55, 0x0e, 0xf2, 0x83}};
EFI_GUID gUefiInfoPerformanceExProtocolGuid                               = {0x1ea81bec, 0xf01a, 0x4d98, {0xa2, 0x01, 0x4a, 0x61, 0xce, 0x2f, 0xc0, 0x22}};
EFI_GUID gUefiInfoPerformancePkgTokenSpaceGuid                            = {0x669346ef, 0xfdad, 0x4aeb, {0x08, 0xa6, 0x21, 0x46, 0x2d, 0x3f, 0xef, 0x7d}};
EFI_GUID gUefiInfoPerformanceProtocolGuid                                 = {0x76b6bdfa, 0x2acd, 0x4462, {0x9e, 0x3f, 0xcb, 0x58, 0xc9, 0x69, 0xd9, 0x37}};
EFI_GUID gUefiInfoPhoenixDesktopMessageProtocolGuid                       = {0x87dd3539, 0x0667, 0x4bb7, {0x9f, 0xb2, 0x47, 0xd3, 0xc5, 0x0b, 0x02, 0x1b}};
EFI_GUID gUefiInfoPhoenixDesktopWindowProtocolGuid                        = {0x6ffec78d, 0x7dbf, 0x4f8b, {0x96, 0x8d, 0x2f, 0x43, 0xa0, 0x80, 0xc1, 0x3f}};
EFI_GUID gUefiInfoPhoenixEfiSmmSwSmiProtocolGuid                          = {0xff052503, 0x1af9, 0x4aeb, {0x83, 0xc4, 0xc2, 0xd4, 0xce, 0xb1, 0x0c, 0xa3}};
EFI_GUID gUefiInfoPhoenixGdiProtocolGuid                                  = {0x3f5a74b2, 0xbf80, 0x4850, {0x85, 0x91, 0x4f, 0x2d, 0xf5, 0xf9, 0xcb, 0x2b}};
EFI_GUID gUefiInfoPhoenixSmmCoreServicesProtocolGuid                      = {0x177e63c1, 0xaed6, 0x4d88, {0x91, 0x7e, 0x9b, 0x4f, 0xb9, 0xfe, 0x40, 0x92}};
EFI_GUID gUefiInfoPhoenixSmmWatchdogTimerProtocolGuid                     = {0x6fde3af8, 0x37ad, 0x43fc, {0xb7, 0x28, 0xf4, 0xd3, 0x41, 0xf3, 0x92, 0x40}};
EFI_GUID gUefiInfoPlatformGOPPolicyGuid                                   = {0xec2e931b, 0x3281, 0x48a5, {0x81, 0x07, 0xdf, 0x8a, 0x8b, 0xed, 0x3c, 0x5d}};
EFI_GUID gUefiInfoPlatformModuleTokenSpaceGuid                            = {0x69d13bf0, 0xaf91, 0x4d96, {0xaa, 0x9f, 0x21, 0x84, 0xc5, 0xce, 0x3b, 0xc0}};
EFI_GUID gUefiInfoPlatformOverridesManagerGuid                            = {0x8614567d, 0x35be, 0x4415, {0x8d, 0x88, 0xbd, 0x7d, 0x0c, 0x9c, 0x70, 0xc0}};
EFI_GUID gUefiInfoPlatformSeCHookProtocolGuid                             = {0xbc52476e, 0xf67e, 0x4301, {0xb2, 0x62, 0x36, 0x9c, 0x48, 0x78, 0xaa, 0xc2}};
EFI_GUID gUefiInfoPowerManagementAcpiTableStorageGuid                     = {0x161be597, 0xe9c5, 0x49db, {0xae, 0x50, 0xc4, 0x62, 0xab, 0x54, 0xee, 0xda}};
EFI_GUID gUefiInfoPpmPlatformPolicyProtocolGuid                           = {0xddabfeac, 0xef63, 0x452c, {0x8f, 0x39, 0xed, 0x7f, 0xae, 0xd8, 0x26, 0x5e}};
EFI_GUID gUefiInfoProcessorProducerGuid                                   = {0x1bf06aea, 0x5bec, 0x4a8d, {0x95, 0x76, 0x74, 0x9b, 0x09, 0x56, 0x2d, 0x30}};
EFI_GUID gUefiInfoPwdCredentialProviderGuid                               = {0x78b9ec8b, 0xc000, 0x46c5, {0xac, 0x93, 0x24, 0xa0, 0xc1, 0xbb, 0x00, 0xce}};
EFI_GUID gUefiInfoRecoveryOnDataCdGuid                                    = {0x5cac0099, 0x0dc9, 0x48e5, {0x80, 0x68, 0xbb, 0x95, 0xf5, 0x40, 0x0a, 0x9f}};
EFI_GUID gUefiInfoRecoveryOnFatFloppyDiskGuid                             = {0x2e3d2e75, 0x9b2e, 0x412d, {0xb4, 0xb1, 0x70, 0x41, 0x6b, 0x87, 0x00, 0xff}};
EFI_GUID gUefiInfoRecoveryOnFatIdeDiskGuid                                = {0xb38573b6, 0x6200, 0x4ac5, {0xb5, 0x1d, 0x82, 0xe6, 0x59, 0x38, 0xd7, 0x83}};
EFI_GUID gUefiInfoRecoveryOnFatUsbDiskGuid                                = {0x0ffbce19, 0x324c, 0x4690, {0xa0, 0x09, 0x98, 0xc6, 0xae, 0x2e, 0xb1, 0x86}};
EFI_GUID gUefiInfoSalSystemTableGuid                                      = {0xeb9d2d32, 0x2d88, 0x11d3, {0x9a, 0x16, 0x00, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
EFI_GUID gUefiInfoSataControllerDriverGuid                                = {0xbb929da9, 0x68f7, 0x4035, {0xb2, 0x2c, 0xa3, 0xbb, 0x3f, 0x23, 0xda, 0x55}};
EFI_GUID gUefiInfoSctIsaHcPpiGuid                                         = {0x8d48bd70, 0xc8a3, 0x4c06, {0x90, 0x1b, 0x74, 0x79, 0x46, 0xaa, 0xc3, 0x58}};
EFI_GUID gUefiInfoSctIsaHcProtocolGuid                                    = {0x5fac7360, 0xd4f2, 0x4c9e, {0xa7, 0xed, 0xf2, 0x59, 0x5e, 0x67, 0x08, 0x89}};
EFI_GUID gUefiInfoSeCfTPMPolicyPpiGuid                                    = {0x4fd1ba49, 0x8f90, 0x471a, {0xa2, 0xc9, 0x17, 0x3c, 0x7a, 0x73, 0x2f, 0xd0}};
EFI_GUID gUefiInfoSeCfTPMPpiGuid                                          = {0x10e26df1, 0x8775, 0x4ee1, {0xb5, 0x0a, 0x3a, 0xe8, 0x28, 0x93, 0x70, 0x3a}};
EFI_GUID gUefiInfoSeCPlatformReadyToBootGuid                              = {0x03fdf171, 0x1d67, 0x4ace, {0xa9, 0x04, 0x3e, 0x36, 0xd3, 0x38, 0xfa, 0x74}};
EFI_GUID gUefiInfoSeCUmaPpiGuid                                           = {0xcbd86677, 0x362f, 0x4c04, {0x94, 0x59, 0xa7, 0x41, 0x32, 0x6e, 0x05, 0xcf}};
EFI_GUID gUefiInfoSecureBootConfigFormSetGuid                             = {0x5daf50a5, 0xea81, 0x4de2, {0x8f, 0x9b, 0xca, 0xbd, 0xa9, 0xcf, 0x5c, 0x14}};
EFI_GUID gUefiInfoShellAliasGuid                                          = {0x0053d9d6, 0x2659, 0x4599, {0xa2, 0x6b, 0xef, 0x45, 0x36, 0xe6, 0x31, 0xa9}};
EFI_GUID gUefiInfoShellBcfgHiiGuid                                        = {0x5f5f605d, 0x1583, 0x4a2d, {0xa6, 0xb2, 0xeb, 0x12, 0xda, 0xb4, 0xa2, 0xb6}};
EFI_GUID gUefiInfoShellDebug1HiiGuid                                      = {0x25f200aa, 0xd3cb, 0x470a, {0xbf, 0x51, 0xe7, 0xd1, 0x62, 0xd2, 0x2e, 0x6f}};
EFI_GUID gUefiInfoShellDriver1HiiGuid                                     = {0x0af0b742, 0x63ec, 0x45bd, {0x8d, 0xb6, 0x71, 0xad, 0x7f, 0x2f, 0xe8, 0xe8}};
EFI_GUID gUefiInfoShellInstall1HiiGuid                                    = {0x7d574d54, 0xd364, 0x4d4a, {0x95, 0xe3, 0x49, 0x45, 0xdb, 0x7a, 0xd3, 0xee}};
EFI_GUID gUefiInfoShellLevel1HiiGuid                                      = {0xdec5daa4, 0x6781, 0x4820, {0x9c, 0x63, 0xa7, 0xb0, 0xe4, 0xf1, 0xdb, 0x31}};
EFI_GUID gUefiInfoShellLevel2HiiGuid                                      = {0xf95a7ccc, 0x4c55, 0x4426, {0xa7, 0xb4, 0xdc, 0x89, 0x61, 0x95, 0x0b, 0xae}};
EFI_GUID gUefiInfoShellLevel3HiiGuid                                      = {0x4344558d, 0x4ef9, 0x4725, {0xb1, 0xe4, 0x33, 0x76, 0xe8, 0xd6, 0x97, 0x4f}};
EFI_GUID gUefiInfoShellMapGuid                                            = {0x51271e13, 0x7de3, 0x43af, {0x8b, 0xc2, 0x71, 0xad, 0x3b, 0x82, 0x43, 0x25}};
EFI_GUID gUefiInfoShellNetwork1HiiGuid                                    = {0xf3d301bb, 0xf4a5, 0x45a8, {0xb0, 0xb7, 0xfa, 0x99, 0x9c, 0x62, 0x37, 0xae}};
EFI_GUID gUefiInfoShellVariableGuid                                       = {0x158def5a, 0xf656, 0x419c, {0xb0, 0x27, 0x7a, 0x31, 0x92, 0xc0, 0x79, 0xd2}};
EFI_GUID gUefiInfoSmmCommunicateHeaderGuid                                = {0xf328e36c, 0x23b6, 0x4a95, {0x85, 0x4b, 0x32, 0xe1, 0x95, 0x34, 0xcd, 0x75}};
EFI_GUID gUefiInfoSmmPerformanceExProtocolGuid                            = {0x931fc048, 0xc71d, 0x4455, {0x89, 0x30, 0x47, 0x06, 0x30, 0xe3, 0x0e, 0xe5}};
EFI_GUID gUefiInfoSmmPerformanceProtocolGuid                              = {0xf866226a, 0xeaa5, 0x4f5a, {0xa9, 0x0a, 0x6c, 0xfb, 0xa5, 0x7c, 0x58, 0x8e}};
EFI_GUID gUefiInfoSmmVariableWriteGuid                                    = {0x93ba1826, 0xdffb, 0x45dd, {0x82, 0xa7, 0xe7, 0xdc, 0xaa, 0x3b, 0xbd, 0xf3}};
EFI_GUID gUefiInfoStatusCodeCallbackGuid                                  = {0xe701458c, 0x4900, 0x4ca5, {0xb7, 0x72, 0x3d, 0x37, 0x94, 0x9f, 0x79, 0x27}};
EFI_GUID gUefiInfoStdLibTokenSpaceGuid                                    = {0x447559f0, 0xd02e, 0x4cf1, {0x99, 0xbc, 0xca, 0x11, 0x65, 0x40, 0x54, 0xc2}};
EFI_GUID gUefiInfoTcgConfigFormSetGuid                                    = {0xb0f901e4, 0xc424, 0x45de, {0x90, 0x81, 0x95, 0xe2, 0x0b, 0xde, 0x6f, 0xb5}};
EFI_GUID gUefiInfoTcgEventEntryHobGuid                                    = {0x2b9ffb52, 0x1b13, 0x416f, {0xa8, 0x7b, 0xbc, 0x93, 0x0d, 0xef, 0x92, 0xa8}};
EFI_GUID gUefiInfoTianoCustomDecompressGuid                               = {0xa31280ad, 0x481e, 0x41b6, {0x95, 0xe8, 0x12, 0x7f, 0x4c, 0x98, 0x47, 0x79}};
EFI_GUID gUefiInfoTopOfTemporaryRamPpiGuid                                = {0x2f3962b2, 0x57c5, 0x44ec, {0x9e, 0xfc, 0xa6, 0x9f, 0xd3, 0x02, 0x03, 0x2b}};
EFI_GUID gUefiInfoTpmErrorHobGuid                                         = {0xef598499, 0xb25e, 0x473a, {0xbf, 0xaf, 0xe7, 0xe5, 0x7d, 0xce, 0x82, 0xc4}};
EFI_GUID gUefiInfoTrEEConfigFormSetGuid                                   = {0xc54b425f, 0xaa79, 0x48b4, {0x98, 0x1f, 0x99, 0x8b, 0x3c, 0x4b, 0x64, 0x1c}};
EFI_GUID gUefiInfoUefiCpuPkgTokenSpaceGuid                                = {0xac05bf33, 0x995a, 0x4ed4, {0xaa, 0xb8, 0xef, 0x7a, 0xe8, 0x0f, 0x5c, 0xb0}};
EFI_GUID gUefiInfoUefiOvmfPkgTokenSpaceGuid                               = {0x93bb96af, 0xb9f2, 0x4eb8, {0x94, 0x62, 0xe0, 0xba, 0x74, 0x56, 0x42, 0x36}};
EFI_GUID gUefiInfoUsbCredentialProviderGuid                               = {0xd0849ed1, 0xa88c, 0x4ba6, {0xb1, 0xd6, 0xab, 0x50, 0xe2, 0x80, 0xb7, 0xa9}};
EFI_GUID gUefiInfoUsbDeviceProtocolGuid                                   = {0x021bd2ca, 0x51d2, 0x11e3, {0x8e, 0x56, 0xb7, 0x54, 0x17, 0xc7, 0x0b, 0x44}};
EFI_GUID gUefiInfoUsbKeyboardLayoutKeyGuid                                = {0x3a4d7a7c, 0x018a, 0x4b42, {0x81, 0xb3, 0xdc, 0x10, 0xe3, 0xb5, 0x91, 0xbd}};
EFI_GUID gUefiInfoUsbKeyboardLayoutPackageGuid                            = {0x0c0f3b43, 0x44de, 0x4907, {0xb4, 0x78, 0x22, 0x5f, 0x6f, 0x62, 0x89, 0xdc}};
EFI_GUID gUefiInfoUsbPolicyGuid                                           = {0xf617b358, 0x12cf, 0x414a, {0xa0, 0x69, 0x60, 0x67, 0x7b, 0xda, 0x13, 0xb4}};
EFI_GUID gUefiInfoUserIdentifyManagerGuid                                 = {0x3ccd3dd8, 0x8d45, 0x4fed, {0x96, 0x2d, 0x2b, 0x38, 0xcd, 0x82, 0xb3, 0xc4}};
EFI_GUID gUefiInfoUserProfileManagerGuid                                  = {0xc35f272c, 0x97c2, 0x465a, {0xa2, 0x16, 0x69, 0x6b, 0x66, 0x8a, 0x8c, 0xfe}};
EFI_GUID gUefiInfoVirtioDeviceProtocolGuid                                = {0xfa920010, 0x6785, 0x4941, {0xb6, 0xec, 0x49, 0x8c, 0x57, 0x9f, 0x16, 0x0a}};
EFI_GUID gUefiInfoVirtioMmioTransportGuid                                 = {0x837dca9e, 0xe874, 0x4d82, {0xb2, 0x9a, 0x23, 0xfe, 0x0e, 0x23, 0xd1, 0xe2}};
EFI_GUID gUefiInfoVirtualUncachedPagesProtocolGuid                        = {0xad651c7d, 0x3c22, 0x4dbf, {0x92, 0xe8, 0x38, 0xa7, 0xcd, 0xae, 0x87, 0xb2}};
EFI_GUID gUefiInfoVlanConfigFormSetGuid                                   = {0xd79df6b0, 0xef44, 0x43bd, {0x97, 0x97, 0x43, 0xe9, 0x3b, 0xcf, 0x5f, 0xa8}};
EFI_GUID gUefiInfoVlvMmioPolicyPpiGuid                                    = {0xe767bf7f, 0x4db6, 0x5b34, {0x10, 0x11, 0x4f, 0xbe, 0x4c, 0xa7, 0xaf, 0xd2}};
EFI_GUID gUefiInfoVlvPeiInitPpiGuid                                       = {0x09ea8911, 0xbe0d, 0x4230, {0xa0, 0x03, 0xed, 0xc6, 0x93, 0xb4, 0x8e, 0x11}};
EFI_GUID gUefiInfoVlvPolicyPpiGuid                                        = {0x7d84b2c2, 0x22a1, 0x4372, {0xb1, 0x2c, 0xeb, 0xb2, 0x32, 0xd3, 0xa6, 0xa3}};
EFI_GUID gUefiInfoVlvRefCodePkgTokenSpaceGuid                             = {0x85768e4a, 0x6cdc, 0x444e, {0x93, 0xdf, 0x93, 0x66, 0x85, 0xb5, 0xdf, 0xcc}};
EFI_GUID gUefiInfoWinNtBusDriverGuid                                      = {0x0419f582, 0x0625, 0x4531, {0x8a, 0x33, 0x85, 0xa9, 0x96, 0x5c, 0x95, 0xbc}};
EFI_GUID gUefiInfoXenBusProtocolGuid                                      = {0x3d3ca290, 0xb9a5, 0x11e3, {0xb7, 0x5d, 0xb8, 0xac, 0x6f, 0x7d, 0x65, 0xe6}};
EFI_GUID gUefiInfoZeroGuid                                                = {0x00000000, 0x0000, 0x0000, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

EFI_GUID gUefiInfoScsiBusDxeGuid                                    = {0x0167CCC4, 0xD0F7, 0x4F21, {0xA3, 0xEF, 0x9E, 0x64, 0xB7, 0xCD, 0xCE, 0x8B}}; // gUefiInfoScsiBusDxe
EFI_GUID gUefiInfoRamDiskDxeGuid                                    = {0x28A03FF4, 0x12B3, 0x4305, {0xA4, 0x17, 0xBB, 0x1A, 0x4F, 0x94, 0x08, 0x1E}}; // gUefiInfoRamDiskDxe
EFI_GUID gUefiInfoEdkiiPlatformSpecificResetHandlerProtocolGuidGuid = {0x2DF6BA0B, 0x7092, 0x440D, {0xBD, 0x04, 0xFB, 0x09, 0x1E, 0xC3, 0xF3, 0xC1}}; // gUefiInfoEdkiiPlatformSpecificResetHandlerProtocolGuid
EFI_GUID gUefiInfoHiiDatabaseDxeGuid                                = {0x348C4D62, 0xBFBD, 0x4882, {0x9E, 0xCE, 0xC8, 0x0B, 0xB1, 0xC4, 0x78, 0x3B}}; // gUefiInfoHiiDatabaseDxe
EFI_GUID gUefiInfoEdkiiBootLogo2ProtocolGuidGuid                    = {0x4B5DC1DF, 0x1EAA, 0x48B2, {0xA7, 0xE9, 0xEA, 0xC4, 0x89, 0xA0, 0x0B, 0x5C}}; // gUefiInfoEdkiiBootLogo2ProtocolGuid
EFI_GUID gUefiInfoEdkiiPlatformSpecificResetFilterProtocolGuidGuid  = {0x695D7835, 0x8D47, 0x4C11, {0xAB, 0x22, 0xFA, 0x8A, 0xCC, 0xE7, 0xAE, 0x7A}}; // gUefiInfoEdkiiPlatformSpecificResetFilterProtocolGuid
EFI_GUID gUefiInfoUefiPxeBcDxeGuid                                  = {0xB95E9FDA, 0x26DE, 0x48D2, {0x88, 0x07, 0x1F, 0x91, 0x07, 0xAC, 0x5E, 0x3A}}; // gUefiInfoUefiPxeBcDxe
EFI_GUID gUefiInfoFirmwarePerformanceDxeGuid           = {0x00160F8D, 0x2B35, 0x4DF2, {0xBB, 0xE0, 0xB2, 0x72, 0xA8, 0xD6, 0x31, 0xF0}}; // FirmwarePerformanceDxe
EFI_GUID gUefiInfoMnpDxeGuid                           = {0x025BBFC7, 0xE6A9, 0x4B8B, {0x82, 0xAD, 0x68, 0x15, 0xA1, 0xAE, 0xAF, 0x4A}}; // MnpDxe
EFI_GUID gUefiInfoScsiDiskDxeGuid                      = {0x0A66E322, 0x3740, 0x4CCE, {0xAD, 0x62, 0xBD, 0x17, 0x2C, 0xEC, 0xCA, 0x35}}; // ScsiDiskDxe
EFI_GUID gUefiInfoCpuDxeGuid                           = {0x1A1E4886, 0x9517, 0x440E, {0x9F, 0xDE, 0x3B, 0xE4, 0x4C, 0xEE, 0x21, 0x36}}; // CpuDxe
EFI_GUID gUefiInfoTcpDxeGuid                           = {0x1A7E4468, 0x2F55, 0x4A56, {0x90, 0x3C, 0x01, 0x26, 0x5E, 0xB7, 0x62, 0x2B}}; // TcpDxe
EFI_GUID gUefiInfoPartitionDxeGuid                     = {0x1FA1F39E, 0xFEFF, 0x4AAE, {0xBD, 0x7B, 0x38, 0xA0, 0x70, 0xA3, 0xB6, 0x09}}; // PartitionDxe
EFI_GUID gUefiInfoHttpUtilitiesDxeGuid                 = {0x22EA234F, 0xE72A, 0x11E4, {0x91, 0xF9, 0x28, 0xD2, 0x44, 0x7C, 0x48, 0x29}}; // HttpUtilitiesDxe
EFI_GUID gUefiInfoHttpDxeGuid                          = {0x2366C20F, 0xE15A, 0x11E3, {0x8B, 0xF1, 0xE4, 0x11, 0x5B, 0x28, 0xBC, 0x50}}; // HttpDxe
EFI_GUID gUefiInfoPcRtcDxeGuid                         = {0x378D7B65, 0x8DA9, 0x4773, {0xB6, 0xE4, 0xA4, 0x78, 0x26, 0xA8, 0x33, 0xE1}}; // PcRtcDxe
EFI_GUID gUefiInfoTlsDxeGuid                           = {0x3ACEB0C0, 0x3C72, 0x11E4, {0x9A, 0x56, 0x74, 0xD4, 0x35, 0x05, 0x26, 0x46}}; // TlsDxe
EFI_GUID gUefiInfoConSplitterDxeGuid                   = {0x408EDCEC, 0xCF6D, 0x477C, {0xA5, 0xA8, 0xB4, 0x84, 0x4E, 0x3D, 0xE2, 0x81}}; // ConSplitterDxe
EFI_GUID gUefiInfoCapsuleRuntimeDxeGuid                = {0x42857F0A, 0x13F2, 0x4B21, {0x8A, 0x23, 0x53, 0xD3, 0xF7, 0x14, 0xB8, 0x40}}; // CapsuleRuntimeDxe
EFI_GUID gUefiInfoResetSystemRuntimeDxeGuid            = {0x4B28E4C7, 0xFF36, 0x4E10, {0x93, 0xCF, 0xA8, 0x21, 0x59, 0xE7, 0x77, 0xC5}}; // ResetSystemRuntimeDxe
EFI_GUID gUefiInfoConPlatformDxeGuid                   = {0x51CCF399, 0x4FDF, 0x4E55, {0xA4, 0x5B, 0xE1, 0x23, 0xF8, 0x4D, 0x45, 0x6A}}; // ConPlatformDxe
EFI_GUID gUefiInfoArpDxeGuid                           = {0x529D3F93, 0xE8E9, 0x4E73, {0xB1, 0xE1, 0xBD, 0xF6, 0xA9, 0xD5, 0x01, 0x13}}; // ArpDxe
EFI_GUID gUefiInfoNvmExpressDxeGuid                    = {0x5BE3BDF4, 0x53CF, 0x46A3, {0xA6, 0xA9, 0x73, 0xC3, 0x4A, 0x6E, 0x5E, 0xE3}}; // NvmExpressDxe
EFI_GUID gUefiInfoIp6DxeGuid                           = {0x5BEDB5CC, 0xD830, 0x4EB2, {0x87, 0x42, 0x2D, 0x4C, 0xC9, 0xB5, 0x4F, 0x2C}}; // Ip6Dxe
EFI_GUID gUefiInfoHash2DxeCryptoGuid                   = {0x63E3BDCF, 0x2AC7, 0x4AC0, {0x9B, 0x92, 0x03, 0xA7, 0x54, 0x14, 0x22, 0xFF}}; // Hash2DxeCrypto
EFI_GUID gUefiInfoDiskIoDxeGuid                        = {0x6B38F7B4, 0xAD98, 0x40E9, {0x90, 0x93, 0xAC, 0xA2, 0xB5, 0xA2, 0x53, 0xC4}}; // DiskIoDxe
EFI_GUID gUefiInfoBdsDxeGuid                           = {0x6D33944A, 0xEC75, 0x4855, {0xA5, 0x4D, 0x80, 0x9C, 0x75, 0x24, 0x1F, 0x6C}}; // BdsDxe
EFI_GUID gUefiInfoUdp4DxeGuid                          = {0x6D6963AB, 0x906D, 0x4A65, {0xA7, 0xCA, 0xBD, 0x40, 0xE5, 0xD6, 0xAF, 0x2B}}; // Udp4Dxe
EFI_GUID gUefiInfoPcdDxeGuid                           = {0x80CF7257, 0x87AB, 0x47F9, {0xA3, 0xFE, 0xD5, 0x0B, 0x76, 0xD8, 0x95, 0x41}}; // PcdDxe
EFI_GUID gUefiInfoDhcp4DxeGuid                         = {0x94734718, 0x0BBC, 0x47FB, {0x96, 0xA5, 0xEE, 0x7A, 0x5A, 0xE6, 0xA2, 0xAD}}; // Dhcp4Dxe
EFI_GUID gUefiInfoDhcp6DxeGuid                         = {0x95E3669D, 0x34BE, 0x4775, {0xA6, 0x51, 0x7E, 0xA4, 0x1B, 0x69, 0xD8, 0x9E}}; // Dhcp6Dxe
EFI_GUID gUefiInfoFatDxeGuid                           = {0x961578FE, 0xB6B7, 0x44C3, {0xAF, 0x35, 0x6B, 0xC7, 0x05, 0xCD, 0x2B, 0x1F}}; // FatDxe
EFI_GUID gUefiInfoAcpiTableDxeGuid                     = {0x9622E42C, 0x8E38, 0x4A08, {0x9E, 0x8F, 0x54, 0xF7, 0x84, 0x65, 0x2F, 0x6B}}; // AcpiTableDxe
EFI_GUID gUefiInfoNullMemoryTestDxeGuid                = {0x96B5C032, 0xDF4C, 0x4B6E, {0x82, 0x32, 0x43, 0x8D, 0xCF, 0x44, 0x8D, 0x0E}}; // NullMemoryTestDxe
EFI_GUID gUefiInfoMtftp6DxeGuid                        = {0x99F03B99, 0x98D8, 0x49DD, {0xA8, 0xD3, 0x32, 0x19, 0xD0, 0xFF, 0xE4, 0x1E}}; // Mtftp6Dxe
EFI_GUID gUefiInfoDevicePathDxeGuid                    = {0x9B680FCE, 0xAD6B, 0x4F3A, {0xB6, 0x0B, 0xF5, 0x98, 0x99, 0x00, 0x34, 0x43}}; // DevicePathDxe
EFI_GUID gUefiInfoTerminalDxeGuid                      = {0x9E863906, 0xA40F, 0x4875, {0x97, 0x7F, 0x5B, 0x93, 0xFF, 0x23, 0x7F, 0xC6}}; // TerminalDxe
EFI_GUID gUefiInfoIp4DxeGuid                           = {0x9FB1A1F3, 0x3B71, 0x4324, {0xB3, 0x9A, 0x74, 0x5C, 0xBB, 0x01, 0x5F, 0xFF}}; // Ip4Dxe
EFI_GUID gUefiInfoDpcDxeGuid                           = {0xA210F973, 0x229D, 0x4F4D, {0xAA, 0x37, 0x98, 0x95, 0xE6, 0xC9, 0xEA, 0xBA}}; // DpcDxe
EFI_GUID gUefiInfoMonotonicCounterRuntimeDxeGuid       = {0xAD608272, 0xD07F, 0x4964, {0x80, 0x1E, 0x7B, 0xD3, 0xB7, 0x88, 0x86, 0x52}}; // MonotonicCounterRuntimeDxe
EFI_GUID gUefiInfoDnsDxeGuid                           = {0xB219E140, 0xDFFC, 0x11E3, {0xB9, 0x56, 0x00, 0x22, 0x68, 0x1E, 0x69, 0x06}}; // DnsDxe
EFI_GUID gUefiInfoRuntimeDxeGuid                       = {0xB601F8C4, 0x43B7, 0x4784, {0x95, 0xB1, 0xF4, 0x22, 0x6C, 0xB4, 0x0C, 0xEE}}; // RuntimeDxe
EFI_GUID gUefiInfoBootGraphicsResourceTableDxeGuid     = {0xB8E62775, 0xBB0A, 0x43F0, {0xA8, 0x43, 0x5B, 0xE8, 0xB1, 0x4F, 0x8C, 0xCD}}; // BootGraphicsResourceTableDxe
EFI_GUID gUefiInfoRngDxeGuid                           = {0xB981A835, 0x6EE8, 0x4F4C, {0xAE, 0x0B, 0x21, 0x0A, 0xA0, 0xBF, 0xBF, 0x01}}; // RngDxe
EFI_GUID gUefiInfoMetronomeGuid                        = {0xC8339973, 0xA563, 0x4561, {0xB8, 0x58, 0xD8, 0x47, 0x6F, 0x9D, 0xEF, 0xC4}}; // Metronome
EFI_GUID gUefiInfoAcpiPlatformGuid                     = {0xCB933912, 0xDF8F, 0x4305, {0xB1, 0xF9, 0x7B, 0x44, 0xFA, 0x11, 0x39, 0x5C}}; // AcpiPlatform
EFI_GUID gUefiInfoVariableRuntimeDxeGuid               = {0xCBD2E4D5, 0x7068, 0x4FF5, {0xB4, 0x62, 0x98, 0x22, 0xB4, 0xAD, 0x8D, 0x60}}; // VariableRuntimeDxe
EFI_GUID gUefiInfoGraphicsConsoleDxeGuid               = {0xCCCB0C28, 0x4B24, 0x11D5, {0x9A, 0x5A, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D}}; // GraphicsConsoleDxe
EFI_GUID gUefiInfoEnglishDxeGuid                       = {0xCD3BAFB6, 0x50FB, 0x4FE8, {0x8E, 0x4E, 0xAB, 0x74, 0xD2, 0xC1, 0xA6, 0x00}}; // EnglishDxe
EFI_GUID gUefiInfoDxeCoreGuid                          = {0xD6A2CB7F, 0x6A18, 0x4E2F, {0xB4, 0x3B, 0x99, 0x20, 0xA7, 0x33, 0x70, 0x0A}}; // DxeCore
EFI_GUID gUefiInfoUdp6DxeGuid                          = {0xD912C7BC, 0xF098, 0x4367, {0x92, 0xBA, 0xE9, 0x11, 0x08, 0x3C, 0x7B, 0x0E}}; // Udp6Dxe
EFI_GUID gUefiInfoReportStatusCodeRouterRuntimeDxeGuid = {0xD93CE3D8, 0xA7EB, 0x4730, {0x8C, 0x8E, 0xCC, 0x46, 0x6A, 0x9E, 0xCC, 0x3C}}; // ReportStatusCodeRouterRuntimeDxe
EFI_GUID gUefiInfoMtftp4DxeGuid                        = {0xDC3641B8, 0x2FA8, 0x4ED3, {0xBC, 0x1F, 0xF9, 0x96, 0x2A, 0x03, 0x45, 0x4B}}; // Mtftp4Dxe
EFI_GUID gUefiInfoSetupBrowserGuid                     = {0xEBF342FE, 0xB1D3, 0x4EF8, {0x95, 0x7C, 0x80, 0x48, 0x60, 0x6F, 0xF6, 0x71}}; // SetupBrowser
EFI_GUID gUefiInfoSecurityStubDxeGuid                  = {0xF80697E9, 0x7FD6, 0x4665, {0x86, 0x46, 0x88, 0xE3, 0x3E, 0xF7, 0x1D, 0xFC}}; // SecurityStubDxe
EFI_GUID gUefiInfoSmbiosDxeGuid                        = {0xF9D88642, 0x0737, 0x49BC, {0x81, 0xB5, 0x68, 0x89, 0xCD, 0x57, 0xD9, 0xEA}}; // SmbiosDxe
EFI_GUID gUefiInfoSmbiosPlatformGuid  = {0x12FCA5F5, 0x7323, 0x49A9, {0x80, 0xFB, 0xEE, 0x2C, 0xDD, 0x26, 0x75, 0x69}}; // SmbiosPlatform
EFI_GUID gUefiInfoVideoDxeGuid        = {0x1CB52863, 0x97B7, 0x4FCE, {0x89, 0x2B, 0x0E, 0xF2, 0x83, 0x8B, 0xEF, 0xBD}}; // VideoDxe
EFI_GUID gUefiInfoSerialDxeGuid       = {0x23510367, 0x1393, 0x4DF8, {0xA7, 0xC7, 0x4B, 0x86, 0x31, 0x38, 0x29, 0xC5}}; // SerialDxe
EFI_GUID gUefiInfoEventLogDxeGuid     = {0x25C0E0C2, 0xE18D, 0x42A0, {0xAA, 0x05, 0xE8, 0xB0, 0x80, 0x05, 0x41, 0x52}}; // EventLogDxe
EFI_GUID gUefiInfoSynicTimerDxeGuid   = {0x28311F03, 0xDC68, 0x4C06, {0xAB, 0x19, 0x7A, 0x20, 0x88, 0x64, 0x88, 0xA2}}; // SynicTimerDxe
EFI_GUID gUefiInfoEmclDxeGuid         = {0x45386216, 0x9A17, 0x46AE, {0xAD, 0x49, 0x42, 0x31, 0x12, 0xFB, 0xFF, 0xB8}}; // EmclDxe
EFI_GUID gUefiInfoConNullDxeGuid      = {0x50B14875, 0x1A50, 0x49A0, {0xA4, 0x0A, 0x12, 0x8A, 0xB1, 0xED, 0xB2, 0x8F}}; // ConNullDxe
EFI_GUID gUefiInfoStorvscDxeGuid      = {0x6D6AE65A, 0x393E, 0x4E54, {0x95, 0x8F, 0xC1, 0x8E, 0x01, 0x95, 0x6A, 0x00}}; // StorvscDxe
EFI_GUID gUefiInfoSynthKeyDxeGuid     = {0x8D5EA93E, 0xF438, 0x464B, {0xAA, 0x26, 0x00, 0x16, 0x50, 0x28, 0xA7, 0xA6}}; // SynthKeyDxe
EFI_GUID gUefiInfoVmbusDxeGuid        = {0xA6683912, 0x5C39, 0x43CB, {0x9B, 0xE8, 0x2A, 0x1B, 0xC9, 0x03, 0xAB, 0xC8}}; // VmbusDxe
EFI_GUID gUefiInfoVmbfsDxeGuid        = {0xBA0CF5FD, 0x6CFC, 0x4747, {0x83, 0xC6, 0x6A, 0xCF, 0x06, 0x2A, 0x78, 0x1D}}; // VmbfsDxe
EFI_GUID gUefiInfoWatchdogTimerGuid   = {0xBD3C7586, 0xB9A3, 0x4332, {0x9E, 0xEE, 0xE9, 0xF0, 0x2C, 0xF6, 0xA9, 0x31}}; // WatchdogTimer
EFI_GUID gUefiInfoEfiHvDxeGuid        = {0xCA585647, 0x54A9, 0x4879, {0xA8, 0xCD, 0x45, 0xA7, 0x69, 0x24, 0x66, 0x80}}; // EfiHvDxe
EFI_GUID gUefiInfoNetvscDxeGuid       = {0xD2C1389F, 0xE54F, 0x4B33, {0xA4, 0xB3, 0x23, 0x1B, 0x37, 0x3C, 0xA3, 0x7F}}; // NetvscDxe


EFI_GUID gUefiInfoEfiDxeServicesTable                   = {0x05ad34ba, 0x6f02, 0x4214, {0x95, 0x2e, 0x4d, 0xa0, 0x39, 0x8e, 0x2b, 0xb9}}; // DXE_SERVICES_TABLE
EFI_GUID gUefiInfoEfiEdkiiPiSmmCommunicationRegionTable = {0x4e28ca50, 0xd582, 0x44ac, {0xa1, 0x1f, 0xe3, 0xd5, 0x65, 0x26, 0xdb, 0x34}}; // EDKII_PI_SMM_COMMUNICATION_REGION_TABLE
EFI_GUID gUefiInfoEfiEdkiiPiSmmMemoryAttributesTable    = {0x6b9fd3f7, 0x16df, 0x45e8, {0xbd, 0x39, 0xb9, 0x4a, 0x66, 0x54, 0x1a, 0x5d}}; // EDKII_PI_SMM_MEMORY_ATTRIBUTES_TABLE
EFI_GUID gUefiInfoEfiEfiCcFinalEventsTable              = {0xdd4a4648, 0x2de7, 0x4665, {0x96, 0x4d, 0x21, 0xd9, 0xef, 0x5f, 0xb4, 0x46}}; // EFI_CC_FINAL_EVENTS_TABLE
EFI_GUID gUefiInfoEfiEfiRtPropertiesTable               = {0xeb66918a, 0x7eef, 0x402a, {0x84, 0x2e, 0x93, 0x1d, 0x21, 0xc3, 0x8a, 0xe9}}; // EFI_RT_PROPERTIES_TABLE
EFI_GUID gUefiInfoEfiEfiTcg2FinalEventsTable            = {0x1e2ed096, 0x30e2, 0x4254, {0xbd, 0x89, 0x86, 0x3b, 0xbe, 0xf8, 0x23, 0x25}}; // EFI_TCG2_FINAL_EVENTS_TABLE
EFI_GUID gUefiInfoEfiEfiConformanceProfilesTable        = {0x36122546, 0xf7e7, 0x4c8f, {0xbd, 0x9b, 0xeb, 0x85, 0x25, 0xb5, 0x0c, 0x0b}}; // EFI_CONFORMANCE_PROFILES_TABLE


GUID_NAME EfiAllGuidNames[] = {
    {&gUefiInfoACPIOSFRMfgStringVariableGuid,                      "ACPIOSFRMFG_STRING_VARIABLE"},
    {&gUefiInfoACPIOSFRModelStringVariableGuid,                    "ACPIOSFRMODEL_STRING_VARIABLE"},
    {&gUefiInfoACPIOSFRRefDataBlockVariableGuid,                   "ACPIOSFRREF_DATA_BLOCK_VARIABLE"},
    {&gUefiInfoAdapterInfoPlatformSecurityGuid,                    "ADAPTER_INFO_PLATFORM_SECURITY"},
    {&gUefiInfoAmtReadyToBootGuid,                                 "AMT_READY_TO_BOOT"},
    {&gUefiInfoAndroidFastbootPlatformProtocolGuid,                "ANDROID_FASTBOOT_PLATFORM_PROTOCOL"},
    {&gUefiInfoAndroidFastbootTransportProtocolGuid,               "ANDROID_FASTBOOT_TRANSPORT_PROTOCOL"},
    {&gUefiInfoAppPkgTokenSpaceGuid,                               "APP_PKG_TOKEN_SPACE"},
    {&gUefiInfoAprioriGuid,                                        "APRIORI"},
    {&gUefiInfoArmBootMonFsFileInfoGuid,                           "ARM_BOOT_MON_FS_FILE_INFO"},
    {&gUefiInfoArmGlobalVariableGuid,                              "ARM_GLOBAL_VARIABLE"},
    {&gUefiInfoArmGlobalVariablePpiGuid,                           "ARM_GLOBAL_VARIABLE_PPI"},
    {&gUefiInfoArmJunoTokenSpaceGuid,                              "ARM_JUNO_TOKEN_SPACE"},
    {&gUefiInfoArmMpCoreInfoGuid,                                  "ARM_MP_CORE_INFO"},
    {&gUefiInfoArmMpCoreInfoPpiGuid,                               "ARM_MP_CORE_INFO_PPI"},
    {&gUefiInfoArmPlatformTokenSpaceGuid,                          "ARM_PLATFORM_TOKEN_SPACE"},
    {&gUefiInfoArmPlatformUpdateFdtEventGuid,                      "ARM_PLATFORM_UPDATE_FDT_EVENT"},
    {&gUefiInfoArmRealViewEbPkgTokenSpaceGuid,                     "ARM_REAL_VIEW_EB_PKG_TOKEN_SPACE"},
    {&gUefiInfoArmTokenSpaceGuid,                                  "ARM_TOKEN_SPACE"},
    {&gUefiInfoArmVExpressTokenSpaceGuid,                          "ARM_VEXPRESS_TOKEN_SPACE"},
    {&gUefiInfoArmVirtualizationTokenSpaceGuid,                    "ARM_VIRTUALIZATION_TOKEN_SPACE"},
    {&gUefiInfoBdsLibStringPackageGuid,                            "BDS_LIB_STRING_PACKAGE"},
    {&gUefiInfoBeagleBoardTokenSpaceGuid,                          "BEAGLE_BOARD_TOKEN_SPACE"},
    {&gUefiInfoBlockIoVendorGuid,                                  "BLOCK_IO_VENDOR"},
    {&gUefiInfoBlockMmioProtocolGuid,                              "BLOCK_MMIO_PROTOCOL"},
    {&gUefiInfoBmpImageGuid,                                       "BMP_IMAGE"},
    {&gUefiInfoBootMaintFormSetGuid,                               "BOOT_MAINT_FORM_SET"},
    {&gUefiInfoBootManagerFormSetGuid,                             "BOOT_MANAGER_FORM_SET"},
    {&gUefiInfoBootObjectAuthorizationParmsetGuid,                 "BOOT_OBJECT_AUTHORIZATION_PARMSET"},
    {&gUefiInfoConnectConInEventGuid,                              "CONNECT_CON_IN_EVENT"},
    {&gUefiInfoDeviceManagerFormSetGuid,                           "DEVICE_MANAGER_FORM_SET"},
    {&gUefiInfoDmiDataGuid,                                        "DMI_DATA"},
    {&gUefiInfoDriverHealthFormSetGuid,                            "DRIVER_HEALTH_FORM_SET"},
    {&gUefiInfoDriverSampleFormSetGuid,                            "DRIVER_SAMPLE_FORM_SET"},
    {&gUefiInfoDriverSampleInventoryGuid,                          "DRIVER_SAMPLE_INVENTORY"},
    {&gUefiInfoDuetConsoleOutConfigGuid,                           "DUET_CONSOLE_OUT_CONFIG"},
    {&gUefiInfoDxeDebugCmdProtocolGuid,                            "DXE_DEBUG_CMD_PROTOCOL"},
    {&gUefiInfoDxeDebugDispatchProtocolGuid,                       "DXE_DEBUG_DISPATCH_PROTOCOL"},
    {&gUefiInfoDxeDebugportExtProtocolGuid,                        "DXE_DEBUGPORT_EXT_PROTOCOL"},
    {&gUefiInfoDxeIchPlatformPolicyProtocolGuid,                   "DXE_ICH_PLATFORM_POLICY_PROTOCOL"},
    {&gUefiInfoDxePchPlatformPolicyProtocolGuid,                   "DXE_PCH_PLATFORM_POLICY_PROTOCOL"},
    {&gUefiInfoDxePchPolicyUpdateProtocolGuid,                     "DXE_PCH_POLICY_UPDATE_PROTOCOL"},
    {&gUefiInfoDxePlatformSeCPolicyGuid,                           "DXE_PLATFORM_SE_CPOLICY"},
    {&gUefiInfoDxeVlvPlatformPolicyGuid,                           "DXE_VLV_PLATFORM_POLICY"},
    {&gUefiInfoEarlyPL011BaseAddressGuid,                          "EARLY_PL011_BASE_ADDRESS"},
    {&gUefiInfoEcpPeiPciCfgPpiGuid,                                "ECP_PEI_PCI_CFG_PPI"},
    {&gUefiInfoEdkiiFaultTolerantWriteGuid,                        "EDKII_FAULT_TOLERANT_WRITE"},
    {&gUefiInfoEdkiiFormBrowserEx2ProtocolGuid,                    "EDKII_FORM_BROWSER_EX2_PROTOCOL"},
    {&gUefiInfoEdkiiFormDisplayEngineProtocolGuid,                 "EDKII_FORM_DISPLAY_ENGINE_PROTOCOL"},
    {&gUefiInfoEdkiiMemoryProfileGuid,                             "EDKII_MEMORY_PROFILE"},
    {&gUefiInfoEdkiiSmmVarCheckProtocolGuid,                       "EDKII_SMM_VAR_CHECK_PROTOCOL"},
    {&gUefiInfoEdkiiStatusCodeDataTypeVariableGuid,                "EDKII_STATUS_CODE_DATA_TYPE_VARIABLE"},
    {&gUefiInfoEdkiiVarCheckProtocolGuid,                          "EDKII_VAR_CHECK_PROTOCOL"},
    {&gUefiInfoEdkiiVarErrorFlagGuid,                              "EDKII_VAR_ERROR_FLAG"},
    {&gUefiInfoEdkiiVariableLockProtocolGuid,                      "EDKII_VARIABLE_LOCK_PROTOCOL"},
    {&gUefiInfoEdkiiWorkingBlockSignatureGuid,                     "EDKII_WORKING_BLOCK_SIGNATURE"},
    {&gUefiInfoEfiAbsolutePointerProtocolGuid,                     "EFI_ABSOLUTE_POINTER_PROTOCOL"},
    {&gUefiInfoEfiAcpi10TableGuid,                                 "EFI_ACPI10_TABLE"},
    {&gUefiInfoEfiAcpi20TableGuid,                                 "EFI_ACPI20_TABLE"},
    {&gUefiInfoEfiAcpiDescriptionGuid,                             "EFI_ACPI_DESCRIPTION"},
    {&gUefiInfoEfiAcpiS3ContextGuid,                               "EFI_ACPI_S3_CONTEXT"},
    {&gUefiInfoEfiAcpiS3SaveProtocolGuid,                          "EFI_ACPI_S3_SAVE_PROTOCOL"},
    {&gUefiInfoEfiAcpiSdtProtocolGuid,                             "EFI_ACPI_SDT_PROTOCOL"},
    {&gUefiInfoEfiAcpiSupportProtocolGuid,                         "EFI_ACPI_SUPPORT_PROTOCOL"},
    {&gUefiInfoEfiAcpiTableProtocolGuid,                           "EFI_ACPI_TABLE_PROTOCOL"},
    {&gUefiInfoEfiAcpiTableStorageGuid,                            "EFI_ACPI_TABLE_STORAGE"},
    {&gUefiInfoEfiAcpiVariableCompatiblityGuid,                    "EFI_ACPI_VARIABLE_COMPATIBLITY"},
    {&gUefiInfoEfiAcpiVariableGuid,                                "EFI_ACPI_VARIABLE"},
    {&gUefiInfoEfiActiveBiosProtocolGuid,                          "EFI_ACTIVE_BIOS_PROTOCOL"},
    {&gUefiInfoEfiAdapterInfoMediaStateGuid,                       "EFI_ADAPTER_INFO_MEDIA_STATE"},
    {&gUefiInfoEfiAdapterInfoMediaTypeGuid,                        "EFI_ADAPTER_INFO_MEDIA_TYPE"},
    {&gUefiInfoEfiAdapterInfoNetworkBootGuid,                      "EFI_ADAPTER_INFO_NETWORK_BOOT"},
    {&gUefiInfoEfiAdapterInformationProtocolGuid,                  "EFI_ADAPTER_INFORMATION_PROTOCOL"},
    {&gUefiInfoEfiAdapterInfoSanMacAddressGuid,                    "EFI_ADAPTER_INFO_SAN_MAC_ADDRESS"},
    {&gUefiInfoEfiAdapterInfoUndiIpv6SupportGuid,                  "EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT"},
    {&gUefiInfoEfiAlertStandardFormatProtocolGuid,                 "EFI_ALERT_STANDARD_FORMAT_PROTOCOL"},
    {&gUefiInfoEfiArpProtocolGuid,                                 "EFI_ARP_PROTOCOL"},
    {&gUefiInfoEfiArpServiceBindingProtocolGuid,                   "EFI_ARP_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiAtaPassThruProtocolGuid,                         "EFI_ATA_PASS_THRU_PROTOCOL"},
    {&gUefiInfoEfiAuthenticatedVariableGuid,                       "EFI_AUTHENTICATED_VARIABLE"},
    {&gUefiInfoEfiAuthenticationChapLocalGuid,                     "EFI_AUTHENTICATION_CHAP_LOCAL"},
    {&gUefiInfoEfiAuthenticationChapRadiusGuid,                    "EFI_AUTHENTICATION_CHAP_RADIUS"},
    {&gUefiInfoEfiAuthenticationInfoProtocolGuid,                  "EFI_AUTHENTICATION_INFO_PROTOCOL"},
    {&gUefiInfoEfiBdsArchProtocolGuid,                             "EFI_BDS_ARCH_PROTOCOL"},
    {&gUefiInfoEfiBiosIdGuid,                                      "EFI_BIOS_ID"},
    {&gUefiInfoEfiBisProtocolGuid,                                 "EFI_BIS_PROTOCOL"},
    {&gUefiInfoEfiBlockIo2ProtocolGuid,                            "EFI_BLOCK_IO2_PROTOCOL"},
    {&gUefiInfoEfiBlockIoCryptoAlgoGuidAesCbcMicrosoftBitlocker,   "EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER"},
    {&gUefiInfoEfiBlockIoCryptoAlgoGuidAesXts,                     "EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS"},
    {&gUefiInfoEfiBlockIoCryptoProtocolGuid,                       "EFI_BLOCK_IO_CRYPTO_PROTOCOL"},
    {&gUefiInfoEfiBlockIoProtocolGuid,                             "EFI_BLOCK_IO_PROTOCOL"},
    {&gUefiInfoEfiBluetoothAttributeProtocolGuid,                  "EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL"},
    {&gUefiInfoEfiBluetoothAttributeServiceBindingProtocolGuid,    "EFI_BLUETOOTH_ATTRIBUTE_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiBluetoothConfigProtocolGuid,                     "EFI_BLUETOOTH_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiBluetoothHcProtocolGuid,                         "EFI_BLUETOOTH_HC_PROTOCOL"},
    {&gUefiInfoEfiBluetoothIoProtocolGuid,                         "EFI_BLUETOOTH_IO_PROTOCOL"},
    {&gUefiInfoEfiBluetoothIoServiceBindingProtocolGuid,           "EFI_BLUETOOTH_IO_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiBluetoothLeConfigProtocolGuid,                   "EFI_BLUETOOTH_LE_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiBoardFeaturesGuid,                               "EFI_BOARD_FEATURES"},
    {&gUefiInfoEfiBootLogoProtocolGuid,                            "EFI_BOOT_LOGO_PROTOCOL"},
    {&gUefiInfoEfiBootManagerPolicyConnectAllGuid,                 "EFI_BOOT_MANAGER_POLICY_CONNECT_ALL"},
    {&gUefiInfoEfiBootManagerPolicyConsoleGuid,                    "EFI_BOOT_MANAGER_POLICY_CONSOLE"},
    {&gUefiInfoEfiBootManagerPolicyNetworkGuid,                    "EFI_BOOT_MANAGER_POLICY_NETWORK"},
    {&gUefiInfoEfiBootManagerPolicyProtocolGuid,                   "EFI_BOOT_MANAGER_POLICY_PROTOCOL"},
    {&gUefiInfoEfiBootScriptExecutorContextGuid,                   "EFI_BOOT_SCRIPT_EXECUTOR_CONTEXT"},
    {&gUefiInfoEfiBootScriptExecutorVariableGuid,                  "EFI_BOOT_SCRIPT_EXECUTOR_VARIABLE"},
    {&gUefiInfoEfiBootScriptSaveProtocolGuid,                      "EFI_BOOT_SCRIPT_SAVE_PROTOCOL"},
    {&gUefiInfoEfiBootStateGuid,                                   "EFI_BOOT_STATE"},
    {&gUefiInfoEfiBttAbstractionGuid,                              "EFI_BTT_ABSTRACTION"},
    {&gUefiInfoEfiBusSpecificDriverOverrideProtocolGuid,           "EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL"},
    {&gUefiInfoEfiCacheSubClassGuid,                               "EFI_CACHE_SUB_CLASS"},
    {&gUefiInfoEfiCapsuleArchProtocolGuid,                         "EFI_CAPSULE_ARCH_PROTOCOL"},
    {&gUefiInfoEfiCapsuleCrashGuid,                                "EFI_CAPSULE_CRASH"},
    {&gUefiInfoEfiCapsuleCrashLogVarGuid,                          "EFI_CAPSULE_CRASH_LOG_VAR"},
    {&gUefiInfoEfiCapsuleGuid,                                     "EFI_CAPSULE"},
    {&gUefiInfoEfiCapsuleReportGuid,                               "EFI_CAPSULE_REPORT"},
    {&gUefiInfoEfiCapsuleVendorGuid,                               "EFI_CAPSULE_VENDOR"},
    {&gUefiInfoEfiCardInfoProtocolGuid,                            "EFI_CARD_INFO_PROTOCOL"},
    {&gUefiInfoEfiCertDbGuid,                                      "EFI_CERT_DB"},
    {&gUefiInfoEfiCertExternalManagementGuid,                      "EFI_CERT_EXTERNAL_MANAGEMENT"},
    {&gUefiInfoEfiCertPkcs7Guid,                                   "EFI_CERT_PKCS7"},
    {&gUefiInfoEfiCertRsa2048Guid,                                 "EFI_CERT_RSA2048"},
    {&gUefiInfoEfiCertRsa2048Sha1Guid,                             "EFI_CERT_RSA2048_SHA1"},
    {&gUefiInfoEfiCertRsa2048Sha256Guid,                           "EFI_CERT_RSA2048_SHA256"},
    {&gUefiInfoEfiCertSha1Guid,                                    "EFI_CERT_SHA1"},
    {&gUefiInfoEfiCertSha224Guid,                                  "EFI_CERT_SHA224"},
    {&gUefiInfoEfiCertSha256Guid,                                  "EFI_CERT_SHA256"},
    {&gUefiInfoEfiCertSha384Guid,                                  "EFI_CERT_SHA384"},
    {&gUefiInfoEfiCertSha512Guid,                                  "EFI_CERT_SHA512"},
    {&gUefiInfoEfiCertTypePkcs7Guid,                               "EFI_CERT_TYPE_PKCS7"},
    {&gUefiInfoEfiCertTypeRsa2048Sha256Guid,                       "EFI_CERT_TYPE_RSA2048_SHA256"},
    {&gUefiInfoEfiCertX509Guid,                                    "EFI_CERT_X509"},
    {&gUefiInfoEfiCertX509Sha256Guid,                              "EFI_CERT_X509_SHA256"},
    {&gUefiInfoEfiCertX509Sha384Guid,                              "EFI_CERT_X509_SHA384"},
    {&gUefiInfoEfiCertX509Sha512Guid,                              "EFI_CERT_X509_SHA512"},
    {&gUefiInfoEfiCk505ClockPlatformInfoGuid,                      "EFI_CK505_CLOCK_PLATFORM_INFO"},
    {&gUefiInfoEfiComponentName2ProtocolGuid,                      "EFI_COMPONENT_NAME2_PROTOCOL"},
    {&gUefiInfoEfiComponentNameProtocolGuid,                       "EFI_COMPONENT_NAME_PROTOCOL"},
    {&gUefiInfoEfiConfigFileNameGuid,                              "EFI_CONFIG_FILE_NAME"},
    {&gUefiInfoEfiConfigKeywordHandlerProtocolGuid,                "EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL"},
    {&gUefiInfoEfiConsoleInDeviceGuid,                             "EFI_CONSOLE_IN_DEVICE"},
    {&gUefiInfoEfiConsoleOutDeviceGuid,                            "EFI_CONSOLE_OUT_DEVICE"},
    {&gUefiInfoEfiCPTokenSpaceGuid,                                "EFI_CPTOKEN_SPACE"},
    {&gUefiInfoEfiCpuArchProtocolGuid,                             "EFI_CPU_ARCH_PROTOCOL"},
    {&gUefiInfoEfiCpuIo2ProtocolGuid,                              "EFI_CPU_IO2_PROTOCOL"},
    {&gUefiInfoEfiCpuIoProtocolGuid,                               "EFI_CPU_IO_PROTOCOL"},
    {&gUefiInfoEfiCrc32GuidedSectionExtractionGuid,                "EFI_CRC32_GUIDED_SECTION_EXTRACTION"},
    {&gUefiInfoEfiCustomModeEnableGuid,                            "EFI_CUSTOM_MODE_ENABLE"},
    {&gUefiInfoEfiDataHubProtocolGuid,                             "EFI_DATA_HUB_PROTOCOL"},
    {&gUefiInfoEfiDataHubStatusCodeRecordGuid,                     "EFI_DATA_HUB_STATUS_CODE_RECORD"},
    {&gUefiInfoEfiDebugAgentGuid,                                  "EFI_DEBUG_AGENT"},
    {&gUefiInfoEfiDebugImageInfoTableGuid,                         "EFI_DEBUG_IMAGE_INFO_TABLE"},
    {&gUefiInfoEfiDebugMaskProtocolGuid,                           "EFI_DEBUG_MASK_PROTOCOL"},
    {&gUefiInfoEfiDebugPortDevicePathGuid,                         "EFI_DEBUG_PORT_DEVICE_PATH"},
    {&gUefiInfoEfiDebugPortProtocolGuid,                           "EFI_DEBUG_PORT_PROTOCOL"},
    {&gUefiInfoEfiDebugportProtocolGuid,                           "EFI_DEBUGPORT_PROTOCOL"},
    {&gUefiInfoEfiDebugPortProtocolGuid,                           "EFI_DEBUGPORT_PROTOCOL"},
    {&gUefiInfoEfiDebugPortVariableGuid,                           "EFI_DEBUG_PORT_VARIABLE"},
    {&gUefiInfoEfiDebugSupportPeriodicCallbackProtocolGuid,        "EFI_DEBUG_SUPPORT_PERIODIC_CALLBACK_PROTOCOL"},
    {&gUefiInfoEfiDebugSupportProtocolGuid,                        "EFI_DEBUG_SUPPORT_PROTOCOL"},
    {&gUefiInfoEfiDecompressProtocolGuid,                          "EFI_DECOMPRESS_PROTOCOL"},
    {&gUefiInfoEfiDeferredImageLoadProtocolGuid,                   "EFI_DEFERRED_IMAGE_LOAD_PROTOCOL"},
    {&gUefiInfoEfiDeviceIoProtocolGuid,                            "EFI_DEVICE_IO_PROTOCOL"},
    {&gUefiInfoEfiDevicePathFromTextProtocolGuid,                  "EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL"},
    {&gUefiInfoEfiDevicePathProtocolGuid,                          "EFI_DEVICE_PATH_PROTOCOL"},
    {&gUefiInfoEfiDevicePathToTextProtocolGuid,                    "EFI_DEVICE_PATH_TO_TEXT_PROTOCOL"},
    {&gUefiInfoEfiDevicePathUtilitiesProtocolGuid,                 "EFI_DEVICE_PATH_UTILITIES_PROTOCOL"},
    {&gUefiInfoEfiDFUResultGuid,                                   "EFI_DFURESULT"},
    {&gUefiInfoEfiDFUVerGuid,                                      "EFI_DFUVER"},
    {&gUefiInfoEfiDhcp4ProtocolGuid,                               "EFI_DHCP4_PROTOCOL"},
    {&gUefiInfoEfiDhcp4ServiceBindingProtocolGuid,                 "EFI_DHCP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiDhcp6ProtocolGuid,                               "EFI_DHCP6_PROTOCOL"},
    {&gUefiInfoEfiDhcp6ServiceBindingProtocolGuid,                 "EFI_DHCP6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiDirectedIoDMArErrorSectionGuid,                  "EFI_DIRECTED_IO_DMAR_ERROR_SECTION"},
    {&gUefiInfoEfiDiskInfoAhciInterfaceGuid,                       "EFI_DISK_INFO_AHCI_INTERFACE"},
    {&gUefiInfoEfiDiskInfoIdeInterfaceGuid,                        "EFI_DISK_INFO_IDE_INTERFACE"},
    {&gUefiInfoEfiDiskInfoProtocolGuid,                            "EFI_DISK_INFO_PROTOCOL"},
    {&gUefiInfoEfiDiskInfoScsiInterfaceGuid,                       "EFI_DISK_INFO_SCSI_INTERFACE"},
    {&gUefiInfoEfiDiskInfoUsbInterfaceGuid,                        "EFI_DISK_INFO_USB_INTERFACE"},
    {&gUefiInfoEfiDiskIo2ProtocolGuid,                             "EFI_DISK_IO2_PROTOCOL"},
    {&gUefiInfoEfiDiskIoProtocolGuid,                              "EFI_DISK_IO_PROTOCOL"},
    {&gUefiInfoEfiDMArGenericErrorSectionGuid,                     "EFI_DMAR_GENERIC_ERROR_SECTION"},
    {&gUefiInfoEfiDns4ProtocolGuid,                                "EFI_DNS4_PROTOCOL"},
    {&gUefiInfoEfiDns4ServiceBindingProtocolGuid,                  "EFI_DNS4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiDns6ProtocolGuid,                                "EFI_DNS6_PROTOCOL"},
    {&gUefiInfoEfiDns6ServiceBindingProtocolGuid,                  "EFI_DNS6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiDpcProtocolGuid,                                 "EFI_DPC_PROTOCOL"},
    {&gUefiInfoEfiDriverBindingProtocolGuid,                       "EFI_DRIVER_BINDING_PROTOCOL"},
    {&gUefiInfoEfiDriverConfiguration2ProtocolGuid,                "EFI_DRIVER_CONFIGURATION2_PROTOCOL"},
    {&gUefiInfoEfiDriverConfigurationProtocolGuid,                 "EFI_DRIVER_CONFIGURATION_PROTOCOL"},
    {&gUefiInfoEfiDriverDiagnostics2ProtocolGuid,                  "EFI_DRIVER_DIAGNOSTICS2_PROTOCOL"},
    {&gUefiInfoEfiDriverDiagnostics2ProtocolGuid,                  "EFI_DRIVER_DIAGNOSTICS_PROTOCOL"},
    {&gUefiInfoEfiDriverDiagnosticsProtocolGuid,                   "EFI_DRIVER_DIAGNOSTICS_PROTOCOL"},
    {&gUefiInfoEfiDriverFamilyOverrideProtocolGuid,                "EFI_DRIVER_FAMILY_OVERRIDE_PROTOCOL"},
    {&gUefiInfoEfiDriverHealthProtocolGuid,                        "EFI_DRIVER_HEALTH_PROTOCOL"},
    {&gUefiInfoEfiDriverSupportedEfiVersionProtocolGuid,           "EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL"},
    {&gUefiInfoEfiDxeIplPpiGuid,                                   "EFI_DXE_IPL_PPI"},
    {&gUefiInfoEfiDxeServicesTableGuid,                            "EFI_DXE_SERVICES_TABLE"},
    {&gUefiInfoEfiDxeSmmReadyToLockProtocolGuid,                   "EFI_DXE_SMM_READY_TO_LOCK_PROTOCOL"},
    {&gUefiInfoEfiEapConfigurationProtocolGuid,                    "EFI_EAP_CONFIGURATION_PROTOCOL"},
    {&gUefiInfoEfiEapManagement2ProtocolGuid,                      "EFI_EAP_MANAGEMENT2_PROTOCOL"},
    {&gUefiInfoEfiEapManagementProtocolGuid,                       "EFI_EAP_MANAGEMENT_PROTOCOL"},
    {&gUefiInfoEfiEapProtocolGuid,                                 "EFI_EAP_PROTOCOL"},
    {&gUefiInfoEfiEbcProtocolGuid,                                 "EFI_EBC_PROTOCOL"},
    {&gUefiInfoEfiEbcSimpleDebuggerProtocolGuid,                   "EFI_EBC_SIMPLE_DEBUGGER_PROTOCOL"},
    {&gUefiInfoEfiEbcVmTestProtocolGuid,                           "EFI_EBC_VM_TEST_PROTOCOL"},
    {&gUefiInfoEfiEblAddCommandProtocolGuid,                       "EFI_EBL_ADD_COMMAND_PROTOCOL"},
    {&gUefiInfoEfiEdidActiveProtocolGuid,                          "EFI_EDID_ACTIVE_PROTOCOL"},
    {&gUefiInfoEfiEdidDiscoveredProtocolGuid,                      "EFI_EDID_DISCOVERED_PROTOCOL"},
    {&gUefiInfoEfiEdidOverrideProtocolGuid,                        "EFI_EDID_OVERRIDE_PROTOCOL"},
    {&gUefiInfoEfiEdkCompatibilityPkgTokenSpaceGuid,               "EFI_EDK_COMPATIBILITY_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiEmmcCardInfoProtocolGuid,                        "EFI_EMMC_CARD_INFO_PROTOCOL"},
    {&gUefiInfoEfiEmmcEraseProtocolGuid,                           "EFI_EMMC_ERASE_PROTOCOL"},
    {&gUefiInfoEfiEmmcUserPartitionProtocolGuid,                   "EFI_EMMC_USER_PARTITION_PROTOCOL"},
    {&gUefiInfoEfiEndOfDxeEventGroupGuid,                          "EFI_END_OF_DXE_EVENT_GROUP"},
    {&gUefiInfoEfiEndOfPeiSignalPpiGuid,                           "EFI_END_OF_PEI_SIGNAL_PPI"},
    {&gUefiInfoEfiEraseBlockProtocolGuid,                          "EFI_ERASE_BLOCK_PROTOCOL"},
    {&gUefiInfoEfiEsrtOperationProtocolGuid,                       "EFI_ESRT_OPERATION_PROTOCOL"},
    {&gUefiInfoEfiEventDxeDispatchGuid,                            "EFI_EVENT_DXE_DISPATCH"},
    {&gUefiInfoEfiEventExitBootServicesGuid,                       "EFI_EVENT_EXIT_BOOT_SERVICES"},
    {&gUefiInfoEfiEventLegacyBootGuid,                             "EFI_EVENT_LEGACY_BOOT"},
    {&gUefiInfoEfiEventMemoryMapChangeGuid,                        "EFI_EVENT_MEMORY_MAP_CHANGE"},
    {&gUefiInfoEfiEventNotificationTypeBootGuid,                   "EFI_EVENT_NOTIFICATION_TYPE_BOOT"},
    {&gUefiInfoEfiEventNotificationTypeCmcGuid,                    "EFI_EVENT_NOTIFICATION_TYPE_CMC"},
    {&gUefiInfoEfiEventNotificationTypeCpeGuid,                    "EFI_EVENT_NOTIFICATION_TYPE_CPE"},
    {&gUefiInfoEfiEventNotificationTypeDmarGuid,                   "EFI_EVENT_NOTIFICATION_TYPE_DMAR"},
    {&gUefiInfoEfiEventNotificationTypeInitGuid,                   "EFI_EVENT_NOTIFICATION_TYPE_INIT"},
    {&gUefiInfoEfiEventNotificationTypeMceGuid,                    "EFI_EVENT_NOTIFICATION_TYPE_MCE"},
    {&gUefiInfoEfiEventNotificationTypeNmiGuid,                    "EFI_EVENT_NOTIFICATION_TYPE_NMI"},
    {&gUefiInfoEfiEventNotificationTypePcieGuid,                   "EFI_EVENT_NOTIFICATION_TYPE_PCIE"},
    {&gUefiInfoEfiEventReadyToBootGuid,                            "EFI_EVENT_READY_TO_BOOT"},
    {&gUefiInfoEfiEventUserProfileChangedGuid,                     "EFI_EVENT_USER_PROFILE_CHANGED"},
    {&gUefiInfoEfiEventVirtualAddressChangeGuid,                   "EFI_EVENT_VIRTUAL_ADDRESS_CHANGE"},
    {&gUefiInfoEfiExtendedSalBaseIoServicesProtocolGuid,           "EFI_EXTENDED_SAL_BASE_IO_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalBaseServicesProtocolGuid,             "EFI_EXTENDED_SAL_BASE_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalBootServiceProtocolGuid,              "EFI_EXTENDED_SAL_BOOT_SERVICE_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalCacheServicesProtocolGuid,            "EFI_EXTENDED_SAL_CACHE_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalFvBlockServicesProtocolGuid,          "EFI_EXTENDED_SAL_FV_BLOCK_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalMcaLogServicesProtocolGuid,           "EFI_EXTENDED_SAL_MCA_LOG_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalMcaServicesProtocolGuid,              "EFI_EXTENDED_SAL_MCA_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalMpServicesProtocolGuid,               "EFI_EXTENDED_SAL_MP_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalMtcServicesProtocolGuid,              "EFI_EXTENDED_SAL_MTC_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalPalServicesProtocolGuid,              "EFI_EXTENDED_SAL_PAL_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalPciServicesProtocolGuid,              "EFI_EXTENDED_SAL_PCI_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalResetServicesProtocolGuid,            "EFI_EXTENDED_SAL_RESET_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalRtcServicesProtocolGuid,              "EFI_EXTENDED_SAL_RTC_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalStallServicesProtocolGuid,            "EFI_EXTENDED_SAL_STALL_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalStatusCodeServicesProtocolGuid,       "EFI_EXTENDED_SAL_STATUS_CODE_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtendedSalVariableServicesProtocolGuid,         "EFI_EXTENDED_SAL_VARIABLE_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiExtScsiPassThruProtocolGuid,                     "EFI_EXT_SCSI_PASS_THRU_PROTOCOL"},
    {&gUefiInfoEfiFaultTolerantWriteProtocolGuid,                  "EFI_FAULT_TOLERANT_WRITE_PROTOCOL"},
    {&gUefiInfoEfiFileInfoGuid,                                    "EFI_FILE_INFO"},
    {&gUefiInfoEfiFileInfoIdGuid,                                  "EFI_FILE_INFO_ID"},
    {&gUefiInfoEfiFileSystemInfoGuid,                              "EFI_FILE_SYSTEM_INFO"},
    {&gUefiInfoEfiFileSystemInfoGuid,                              "EFI_FILE_SYSTEM_INFO_ID"},
    {&gUefiInfoEfiFileSystemVolumeLabelInfoIdGuid,                 "EFI_FILE_SYSTEM_VOLUME_LABEL_ID"},
    {&gUefiInfoEfiFileSystemVolumeLabelInfoIdGuid,                 "EFI_FILE_SYSTEM_VOLUME_LABEL_INFO_ID"},
    {&gUefiInfoEfiFindFvPpiGuid,                                   "EFI_FIND_FV_PPI"},
    {&gUefiInfoEfiFirmwareClassGuid,                               "EFI_FIRMWARE_CLASS"},
    {&gUefiInfoEfiFirmwareContentsSignedGuid,                      "EFI_FIRMWARE_CONTENTS_SIGNED"},
    {&gUefiInfoEfiFirmwareErrorSectionGuid,                        "EFI_FIRMWARE_ERROR_SECTION"},
    {&gUefiInfoEfiFirmwareFileSystem2Guid,                         "EFI_FIRMWARE_FILE_SYSTEM2"},
    {&gUefiInfoEfiFirmwareFileSystem3Guid,                         "EFI_FIRMWARE_FILE_SYSTEM3"},
    {&gUefiInfoEfiFirmwareFileSystemGuid,                          "EFI_FIRMWARE_FILE_SYSTEM"},
    {&gUefiInfoEfiFirmwareManagementCapsuleIdGuid,                 "EFI_FIRMWARE_MANAGEMENT_CAPSULE_ID"},
    {&gUefiInfoEfiFirmwareManagementProtocolGuid,                  "EFI_FIRMWARE_MANAGEMENT_PROTOCOL"},
    {&gUefiInfoEfiFirmwarePerformanceGuid,                         "EFI_FIRMWARE_PERFORMANCE"},
    {&gUefiInfoEfiFirmwareVolume2ProtocolGuid,                     "EFI_FIRMWARE_VOLUME2_PROTOCOL"},
    {&gUefiInfoEfiFirmwareVolumeBlock2ProtocolGuid,                "EFI_FIRMWARE_VOLUME_BLOCK2_PROTOCOL"},
    {&gUefiInfoEfiFirmwareVolumeBlockProtocolGuid,                 "EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL"},
    {&gUefiInfoEfiFirmwareVolumeProtocolGuid,                      "EFI_FIRMWARE_VOLUME_PROTOCOL"},
    {&gUefiInfoEfiFirmwareVolumeTopFileGuid,                       "EFI_FIRMWARE_VOLUME_TOP_FILE"},
    {&gUefiInfoEfiFlashMapHobGuid,                                 "EFI_FLASH_MAP_HOB"},
    {&gUefiInfoEfiFmpCapsuleGuid,                                  "EFI_FMP_CAPSULE"},
    {&gUefiInfoEfiFormBrowser2ProtocolGuid,                        "EFI_FORM_BROWSER2_PROTOCOL"},
    {&gUefiInfoEfiFormBrowserCompatibilityProtocolGuid,            "EFI_FORM_BROWSER_COMPATIBILITY_PROTOCOL"},
    {&gUefiInfoEfiFormBrowserExProtocolGuid,                       "EFI_FORM_BROWSER_EX_PROTOCOL"},
    {&gUefiInfoEfiFormBrowserProtocolGuid,                         "EFI_FORM_BROWSER_PROTOCOL"},
    {&gUefiInfoEfiFormCallbackProtocolGuid,                        "EFI_FORM_CALLBACK_PROTOCOL"},
    {&gUefiInfoEfiFtp4ProtocolGuid,                                "EFI_FTP4_PROTOCOL"},
    {&gUefiInfoEfiFtp4ServiceBindingProtocolGuid,                  "EFI_FTP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiFwDisplayCapsuleGuid,                            "EFI_FW_DISPLAY_CAPSULE"},
    {&gUefiInfoEfiGenericMemTestProtocolGuid,                      "EFI_GENERIC_MEM_TEST_PROTOCOL"},
    {&gUefiInfoEfiGenericVariableGuid,                             "EFI_GENERIC_VARIABLE"},
    {&gUefiInfoEfiGetPcdInfoPpiGuid,                               "EFI_GET_PCD_INFO_PPI"},
    {&gUefiInfoEfiGetPcdInfoProtocolGuid,                          "EFI_GET_PCD_INFO_PROTOCOL"},
    {&gUefiInfoEfiGlobalNvsAreaProtocolGuid,                       "EFI_GLOBAL_NVS_AREA_PROTOCOL"},
    {&gUefiInfoEfiGlobalVariableGuid,                              "BOOT_ORDER"},
    {&gUefiInfoEfiGlobalVariableGuid,                              "EFI_GLOBAL_VARIABLE"},
    {&gUefiInfoEfiGopDisplayBrightnessProtocolGuid,                "EFI_GOP_DISPLAY_BRIGHTNESS_PROTOCOL"},
    {&gUefiInfoEfiGpioOperationProtocolGuid,                       "EFI_GPIO_OPERATION_PROTOCOL"},
    {&gUefiInfoEfiGraphicsOutputProtocolGuid,                      "EFI_GRAPHICS_OUTPUT_PROTOCOL"},
    {&gUefiInfoEfiHardwareErrorVariableGuid,                       "EFI_HARDWARE_ERROR_VARIABLE"},
    {&gUefiInfoEfiHash2ProtocolGuid,                               "EFI_HASH2_PROTOCOL"},
    {&gUefiInfoEfiHash2ServiceBindingProtocolGuid,                 "EFI_HASH2_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiHashAlgorithmMD5Guid,                            "EFI_HASH_ALGORITHM_MD5"},
    {&gUefiInfoEfiHashAlgorithmMd5Guid,                            "EFI_HASH_ALGORITHM_MD5"},
    {&gUefiInfoEfiHashAlgorithmSha1Guid,                           "EFI_HASH_ALGORITHM_SHA1"},
    {&gUefiInfoEfiHashAlgorithmSha1NoPadGuid,                      "EFI_HASH_ALGORITHM_SHA1_NO_PAD"},
    {&gUefiInfoEfiHashAlgorithmSha1NopadGuid,                      "EFI_HASH_ALGORITHM_SHA1_NOPAD"},
    {&gUefiInfoEfiHashAlgorithmSha224Guid,                         "EFI_HASH_ALGORITHM_SHA224"},
    {&gUefiInfoEfiHashAlgorithmSha256Guid,                         "EFI_HASH_ALGORITHM_SHA256"},
    {&gUefiInfoEfiHashAlgorithmSha256NoPadGuid,                    "EFI_HASH_ALGORITHM_SHA256_NO_PAD"},
    {&gUefiInfoEfiHashAlgorithmSha256NopadGuid,                    "EFI_HASH_ALGORITHM_SHA256_NOPAD"},
    {&gUefiInfoEfiHashAlgorithmSha384Guid,                         "EFI_HASH_ALGORITHM_SHA384"},
    {&gUefiInfoEfiHashAlgorithmSha512Guid,                         "EFI_HASH_ALGORITHM_SHA512"},
    {&gUefiInfoEfiHashProtocolGuid,                                "EFI_HASH_PROTOCOL"},
    {&gUefiInfoEfiHashServiceBindingProtocolGuid,                  "EFI_HASH_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiHeciProtocolGuid,                                "EFI_HECI_PROTOCOL"},
    {&gUefiInfoEfiHiiCompatibilityProtocolGuid,                    "EFI_HII_COMPATIBILITY_PROTOCOL"},
    {&gUefiInfoEfiHiiConfigAccessProtocolGuid,                     "EFI_HII_CONFIG_ACCESS_PROTOCOL"},
    {&gUefiInfoEfiHiiConfigRoutingProtocolGuid,                    "EFI_HII_CONFIG_ROUTING_PROTOCOL"},
    {&gUefiInfoEfiHiiDatabaseProtocolGuid,                         "EFI_HII_DATABASE_PROTOCOL"},
    {&gUefiInfoEfiHiiDriverHealthFormsetGuid,                      "EFI_HII_DRIVER_HEALTH_FORMSET"},
    {&gUefiInfoEfiHiiFontExProtocolGuid,                           "EFI_HII_FONT_EX_PROTOCOL"},
    {&gUefiInfoEfiHiiFontGlyphGeneratorProtocolGuid,               "EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL"},
    {&gUefiInfoEfiHiiFontProtocolGuid,                             "EFI_HII_FONT_PROTOCOL"},
    {&gUefiInfoEfiHiiImageDecoderNamePngGuid,                      "EFI_HII_IMAGE_DECODER_NAME_PNG"},
    {&gUefiInfoEfiHiiImageDecoderProtocolGuid,                     "EFI_HII_IMAGE_DECODER_PROTOCOL"},
    {&gUefiInfoEfiHiiImageExProtocolGuid,                          "EFI_HII_IMAGE_EX_PROTOCOL"},
    {&gUefiInfoEfiHiiImageProtocolGuid,                            "EFI_HII_IMAGE_PROTOCOL"},
    {&gUefiInfoEfiHiiKeyBoardLayoutGuid,                           "EFI_HII_KEY_BOARD_LAYOUT"},
    {&gUefiInfoEfiHiiKeyBoardLayoutGuid,                           "EFI_HII_SET_KEYBOARD_LAYOUT_EVENT"},
    {&gUefiInfoEfiHiiPackageListProtocolGuid,                      "EFI_HII_PACKAGE_LIST_PROTOCOL"},
    {&gUefiInfoEfiHiiPlatformSetupFormsetGuid,                     "EFI_HII_PLATFORM_SETUP_FORMSET"},
    {&gUefiInfoEfiHiiPopupProtocolGuid,                            "EFI_HII_POPUP_PROTOCOL"},
    {&gUefiInfoEfiHiiProtocolGuid,                                 "EFI_HII_PROTOCOL"},
    {&gUefiInfoEfiHiiRestStyleFormsetGuid,                         "EFI_HII_REST_STYLE_FORMSET"},
    {&gUefiInfoEfiHiiStandardFormGuid,                             "EFI_HII_STANDARD_FORM"},
    {&gUefiInfoEfiHiiStringProtocolGuid,                           "EFI_HII_STRING_PROTOCOL"},
    {&gUefiInfoEfiHiiUserCredentialFormsetGuid,                    "EFI_HII_USER_CREDENTIAL_FORMSET"},
    {&gUefiInfoEfiHobListGuid,                                     "EFI_HOB_LIST"},
    {&gUefiInfoEfiHobMemoryAllocBspStoreGuid,                      "EFI_HOB_MEMORY_ALLOC_BSP_STORE"},
    {&gUefiInfoEfiHobMemoryAllocModuleGuid,                        "EFI_HOB_MEMORY_ALLOC_MODULE"},
    {&gUefiInfoEfiHobMemoryAllocStackGuid,                         "EFI_HOB_MEMORY_ALLOC_STACK"},
    {&gUefiInfoEfiHttpBootCallbackProtocolGuid,                    "EFI_HTTP_BOOT_CALLBACK_PROTOCOL"},
    {&gUefiInfoEfiHttpProtocolGuid,                                "EFI_HTTP_PROTOCOL"},
    {&gUefiInfoEfiHttpServiceBindingProtocolGuid,                  "EFI_HTTP_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiHttpUtilitiesProtocolGuid,                       "EFI_HTTP_UTILITIES_PROTOCOL"},
    {&gUefiInfoEfiI2cAcpiProtocolGuid,                             "EFI_I2C_ACPI_PROTOCOL"},
    {&gUefiInfoEfiI2cBusConfigurationManagementProtocol2Guid,      "EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL2"},
    {&gUefiInfoEfiI2cBusConfigurationManagementProtocolGuid,       "EFI_I2C_BUS_CONFIGURATION_MANAGEMENT_PROTOCOL"},
    {&gUefiInfoEfiI2cBusProtocolGuid,                              "EFI_I2C_BUS_PROTOCOL"},
    {&gUefiInfoEfiI2cEnumerateProtocolGuid,                        "EFI_I2C_ENUMERATE_PROTOCOL"},
    {&gUefiInfoEfiI2cHostProtocol2Guid,                            "EFI_I2C_HOST_PROTOCOL2"},
    {&gUefiInfoEfiI2cHostProtocolGuid,                             "EFI_I2C_HOST_PROTOCOL"},
    {&gUefiInfoEfiI2cIoProtocolGuid,                               "EFI_I2C_IO_PROTOCOL"},
    {&gUefiInfoEfiI2cMasterProtocol2Guid,                          "EFI_I2C_MASTER_PROTOCOL2"},
    {&gUefiInfoEfiI2cMasterProtocolGuid,                           "EFI_I2C_MASTER_PROTOCOL"},
    {&gUefiInfoEfiI2cSlaveProtocolGuid,                            "EFI_I2C_SLAVE_PROTOCOL"},
    {&gUefiInfoEfiIa32X64ErrorTypeBusCheckGuid,                    "EFI_IA32_X64_ERROR_TYPE_BUS_CHECK"},
    {&gUefiInfoEfiIa32X64ErrorTypeCacheCheckGuid,                  "EFI_IA32_X64_ERROR_TYPE_CACHE_CHECK"},
    {&gUefiInfoEfiIa32X64ErrorTypeMsCheckGuid,                     "EFI_IA32_X64_ERROR_TYPE_MS_CHECK"},
    {&gUefiInfoEfiIa32X64ErrorTypeTlbCheckGuid,                    "EFI_IA32_X64_ERROR_TYPE_TLB_CHECK"},
    {&gUefiInfoEfiIchInfoProtocolGuid,                             "EFI_ICH_INFO_PROTOCOL"},
    {&gUefiInfoEfiIchTokenSpaceGuid,                               "EFI_ICH_TOKEN_SPACE"},
    {&gUefiInfoEfiIdeControllerInitProtocolGuid,                   "EFI_IDE_CONTROLLER_INIT_PROTOCOL"},
    {&gUefiInfoEfiIfrFrameworkGuid,                                "EFI_IFR_FRAMEWORK"},
    {&gUefiInfoEfiIfrRefreshIdOpGuid,                              "EFI_IFR_REFRESH_ID_OP"},
    {&gUefiInfoEfiIfrTianoGuid,                                    "EFI_IFR_TIANO"},
    {&gUefiInfoEfiImageSecurityDatabaseGuid,                       "EFI_IMAGE_SECURITY_DATABASE"},
    {&gUefiInfoEfiIncompatiblePciDeviceSupportProtocolGuid,        "EFI_INCOMPATIBLE_PCI_DEVICE_SUPPORT_PROTOCOL"},
    {&gUefiInfoEfiIntelFrameworkModulePkgTokenSpaceGuid,           "EFI_INTEL_FRAMEWORK_MODULE_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiIommuDMArErrorSectionGuid,                       "EFI_IOMMU_DMAR_ERROR_SECTION"},
    {&gUefiInfoEfiIp4Config2ProtocolGuid,                          "EFI_IP4_CONFIG2_PROTOCOL"},
    {&gUefiInfoEfiIp4ConfigProtocolGuid,                           "EFI_IP4_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiIp4ProtocolGuid,                                 "EFI_IP4_PROTOCOL"},
    {&gUefiInfoEfiIp4ServiceBindingProtocolGuid,                   "EFI_IP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiIp6ConfigProtocolGuid,                           "EFI_IP6_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiIp6ProtocolGuid,                                 "EFI_IP6_PROTOCOL"},
    {&gUefiInfoEfiIp6ServiceBindingProtocolGuid,                   "EFI_IP6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiIpSec2ProtocolGuid,                              "EFI_IP_SEC2_PROTOCOL"},
    {&gUefiInfoEfiIpSec2ProtocolGuid,                              "EFI_IPSEC2_PROTOCOL"},
    {&gUefiInfoEfiIpSecConfigProtocolGuid,                         "EFI_IP_SEC_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiIpSecConfigProtocolGuid,                         "EFI_IPSEC_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiIpSecProtocolGuid,                               "EFI_IP_SEC_PROTOCOL"},
    {&gUefiInfoEfiIpSecProtocolGuid,                               "EFI_IPSEC_PROTOCOL"},
    {&gUefiInfoEfiIsaAcpiProtocolGuid,                             "EFI_ISA_ACPI_PROTOCOL"},
    {&gUefiInfoEfiIsaIoProtocolGuid,                               "EFI_ISA_IO_PROTOCOL"},
    {&gUefiInfoEfiIScsiInitiatorNameProtocolGuid,                  "EFI_ISCSI_INITIATOR_NAME_PROTOCOL"},
    {&gUefiInfoEfiJsonCapsuleDataTableGuid,                        "EFI_JSON_CAPSULE_DATA_TABLE"},
    {&gUefiInfoEfiJsonCapsuleIdGuid,                               "EFI_JSON_CAPSULE_ID"},
    {&gUefiInfoEfiJsonCapsuleResultTableGuid,                      "EFI_JSON_CAPSULE_RESULT_TABLE"},
    {&gUefiInfoEfiJsonConfigDataTableGuid,                         "EFI_JSON_CONFIG_DATA_TABLE"},
    {&gUefiInfoEfiKmsFormatAescbc128Guid,                          "EFI_KMS_FORMAT_AESCBC128"},
    {&gUefiInfoEfiKmsFormatAescbc256Guid,                          "EFI_KMS_FORMAT_AESCBC256"},
    {&gUefiInfoEfiKmsFormatAescbc_128Guid,                         "EFI_KMS_FORMAT_AESCBC_128"},
    {&gUefiInfoEfiKmsFormatAescbc_256Guid,                         "EFI_KMS_FORMAT_AESCBC_256"},
    {&gUefiInfoEfiKmsFormatAesxts128Guid,                          "EFI_KMS_FORMAT_AESXTS128"},
    {&gUefiInfoEfiKmsFormatAesxts256Guid,                          "EFI_KMS_FORMAT_AESXTS256"},
    {&gUefiInfoEfiKmsFormatAesxts_128Guid,                         "EFI_KMS_FORMAT_AESXTS_128"},
    {&gUefiInfoEfiKmsFormatAesxts_256Guid,                         "EFI_KMS_FORMAT_AESXTS_256"},
    {&gUefiInfoEfiKmsFormatGeneric1024Guid,                        "EFI_KMS_FORMAT_GENERIC1024"},
    {&gUefiInfoEfiKmsFormatGeneric128Guid,                         "EFI_KMS_FORMAT_GENERIC128"},
    {&gUefiInfoEfiKmsFormatGeneric160Guid,                         "EFI_KMS_FORMAT_GENERIC160"},
    {&gUefiInfoEfiKmsFormatGeneric2048Guid,                        "EFI_KMS_FORMAT_GENERIC2048"},
    {&gUefiInfoEfiKmsFormatGeneric256Guid,                         "EFI_KMS_FORMAT_GENERIC256"},
    {&gUefiInfoEfiKmsFormatGeneric3072Guid,                        "EFI_KMS_FORMAT_GENERIC3072"},
    {&gUefiInfoEfiKmsFormatGeneric512Guid,                         "EFI_KMS_FORMAT_GENERIC512"},
    {&gUefiInfoEfiKmsFormatGeneric_1024Guid,                       "EFI_KMS_FORMAT_GENERIC_1024"},
    {&gUefiInfoEfiKmsFormatGeneric_128Guid,                        "EFI_KMS_FORMAT_GENERIC_128"},
    {&gUefiInfoEfiKmsFormatGeneric_160Guid,                        "EFI_KMS_FORMAT_GENERIC_160"},
    {&gUefiInfoEfiKmsFormatGeneric_2048Guid,                       "EFI_KMS_FORMAT_GENERIC_2048"},
    {&gUefiInfoEfiKmsFormatGeneric_256Guid,                        "EFI_KMS_FORMAT_GENERIC_256"},
    {&gUefiInfoEfiKmsFormatGeneric_3072Guid,                       "EFI_KMS_FORMAT_GENERIC_3072"},
    {&gUefiInfoEfiKmsFormatGeneric_512Guid,                        "EFI_KMS_FORMAT_GENERIC_512"},
    {&gUefiInfoEfiKmsFormatGenericDynamicGuid,                     "EFI_KMS_FORMAT_GENERIC_DYNAMIC"},
    {&gUefiInfoEfiKmsFormatMd2128Guid,                             "EFI_KMS_FORMAT_MD2128"},
    {&gUefiInfoEfiKmsFormatMd2_128Guid,                            "EFI_KMS_FORMAT_MD2_128"},
    {&gUefiInfoEfiKmsFormatMd4128Guid,                             "EFI_KMS_FORMAT_MD4128"},
    {&gUefiInfoEfiKmsFormatMd4_128Guid,                            "EFI_KMS_FORMAT_MD4_128"},
    {&gUefiInfoEfiKmsFormatMd5128Guid,                             "EFI_KMS_FORMAT_MD5128"},
    {&gUefiInfoEfiKmsFormatMd5_128Guid,                            "EFI_KMS_FORMAT_MD5_128"},
    {&gUefiInfoEfiKmsFormatMd5sha128Guid,                          "EFI_KMS_FORMAT_MD5SHA128"},
    {&gUefiInfoEfiKmsFormatMd5Sha_128Guid,                         "EFI_KMS_FORMAT_MD5SHA_128"},
    {&gUefiInfoEfiKmsFormatMdc2128Guid,                            "EFI_KMS_FORMAT_MDC2128"},
    {&gUefiInfoEfiKmsFormatMdc2_128Guid,                           "EFI_KMS_FORMAT_MDC2_128"},
    {&gUefiInfoEfiKmsFormatMdc4128Guid,                            "EFI_KMS_FORMAT_MDC4128"},
    {&gUefiInfoEfiKmsFormatMdc4_128Guid,                           "EFI_KMS_FORMAT_MDC4_128"},
    {&gUefiInfoEfiKmsFormatRsasha11024Guid,                        "EFI_KMS_FORMAT_RSASHA11024"},
    {&gUefiInfoEfiKmsFormatRsasha12048Guid,                        "EFI_KMS_FORMAT_RSASHA12048"},
    {&gUefiInfoEfiKmsFormatRsasha1_1024Guid,                       "EFI_KMS_FORMAT_RSASHA1_1024"},
    {&gUefiInfoEfiKmsFormatRsasha1_2048Guid,                       "EFI_KMS_FORMAT_RSASHA1_2048"},
    {&gUefiInfoEfiKmsFormatRsasha2562048Guid,                      "EFI_KMS_FORMAT_RSASHA2562048"},
    {&gUefiInfoEfiKmsFormatRsasha2563072Guid,                      "EFI_KMS_FORMAT_RSASHA2563072"},
    {&gUefiInfoEfiKmsFormatRsasha256_2048Guid,                     "EFI_KMS_FORMAT_RSASHA256_2048"},
    {&gUefiInfoEfiKmsFormatRsasha256_3072Guid,                     "EFI_KMS_FORMAT_RSASHA256_3072"},
    {&gUefiInfoEfiKmsFormatSha1160Guid,                            "EFI_KMS_FORMAT_SHA1160"},
    {&gUefiInfoEfiKmsFormatSha1_160Guid,                           "EFI_KMS_FORMAT_SHA1_160"},
    {&gUefiInfoEfiKmsFormatSha256256Guid,                          "EFI_KMS_FORMAT_SHA256256"},
    {&gUefiInfoEfiKmsFormatSha256_256Guid,                         "EFI_KMS_FORMAT_SHA256_256"},
    {&gUefiInfoEfiKmsFormatSha512512Guid,                          "EFI_KMS_FORMAT_SHA512512"},
    {&gUefiInfoEfiKmsFormatSha512_512Guid,                         "EFI_KMS_FORMAT_SHA512_512"},
    {&gUefiInfoEfiKmsProtocolGuid,                                 "EFI_KMS_PROTOCOL"},
    {&gUefiInfoEfiLegacy8259ProtocolGuid,                          "EFI_LEGACY8259_PROTOCOL"},
    {&gUefiInfoEfiLegacyBiosGuid,                                  "EFI_LEGACY_BIOS"},
    {&gUefiInfoEfiLegacyBiosPlatformProtocolGuid,                  "EFI_LEGACY_BIOS_PLATFORM_PROTOCOL"},
    {&gUefiInfoEfiLegacyBiosProtocolGuid,                          "EFI_LEGACY_BIOS_PROTOCOL"},
    {&gUefiInfoEfiLegacyDevOrderVariableGuid,                      "EFI_LEGACY_DEV_ORDER_VARIABLE"},
    {&gUefiInfoEfiLegacyInterruptProtocolGuid,                     "EFI_LEGACY_INTERRUPT_PROTOCOL"},
    {&gUefiInfoEfiLegacyRegion2ProtocolGuid,                       "EFI_LEGACY_REGION2_PROTOCOL"},
    {&gUefiInfoEfiLegacyRegionProtocolGuid,                        "EFI_LEGACY_REGION_PROTOCOL"},
    {&gUefiInfoEfiLoadedImageDevicePathProtocolGuid,               "EFI_LOADED_IMAGE_DEVICE_PATH_PROTOCOL"},
    {&gUefiInfoEfiLoadedImageProtocolGuid,                         "EFI_LOADED_IMAGE_PROTOCOL"},
    {&gUefiInfoEfiLoadFile2ProtocolGuid,                           "EFI_LOAD_FILE2_PROTOCOL"},
    {&gUefiInfoEfiLoadFileProtocolGuid,                            "EFI_LOAD_FILE_PROTOCOL"},
    {&gUefiInfoEfiLoadPeImageProtocolGuid,                         "EFI_LOAD_PE_IMAGE_PROTOCOL"},
    {&gUefiInfoEfiLockBoxProtocolGuid,                             "EFI_LOCK_BOX_PROTOCOL"},
    {&gUefiInfoEfiLpcWpc83627PolicyProtocolGuid,                   "EFI_LPC_WPC83627_POLICY_PROTOCOL"},
    {&gUefiInfoEfiLpcWpce791PolicyProtocolGuid,                    "EFI_LPC_WPCE791_POLICY_PROTOCOL"},
    {&gUefiInfoEfiManagedNetworkProtocolGuid,                      "EFI_MANAGED_NETWORK_PROTOCOL"},
    {&gUefiInfoEfiManagedNetworkServiceBindingProtocolGuid,        "EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiMdeModulePkgTokenSpaceGuid,                      "EFI_MDE_MODULE_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiMdePkgTokenSpaceGuid,                            "EFI_MDE_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiMemoryAttributesTableGuid,                       "EFI_MEMORY_ATTRIBUTES_TABLE"},
    {&gUefiInfoEfiMemoryConfigDataGuid,                            "EFI_MEMORY_CONFIG_DATA"},
    {&gUefiInfoEfiMemoryOverwriteControlDataGuid,                  "EFI_MEMORY_OVERWRITE_CONTROL_DATA"},
    {&gUefiInfoEfiMemoryRangeCapsuleGuid,                          "EFI_MEMORY_RANGE_CAPSULE"},
    {&gUefiInfoEfiMemoryRangeRequirementDataGuid,                  "EFI_MEMORY_RANGE_REQUIREMENT_DATA"},
    {&gUefiInfoEfiMemorySubClassGuid,                              "EFI_MEMORY_SUB_CLASS"},
    {&gUefiInfoEfiMemoryTypeInformationGuid,                       "EFI_MEMORY_TYPE_INFORMATION"},
    {&gUefiInfoEfiMetronomeArchProtocolGuid,                       "EFI_METRONOME_ARCH_PROTOCOL"},
    {&gUefiInfoEfiMiscSubClassGuid,                                "EFI_MISC_SUB_CLASS"},
    {&gUefiInfoEfiMmcHostProtocolGuid,                             "EFI_MMC_HOST_PROTOCOL"},
    {&gUefiInfoEfiMmioDeviceProtocolGuid,                          "EFI_MMIO_DEVICE_PROTOCOL"},
    {&gUefiInfoEfiMonotonicCounterArchProtocolGuid,                "EFI_MONOTONIC_COUNTER_ARCH_PROTOCOL"},
    {&gUefiInfoEfiMpServiceProtocolGuid,                           "EFI_MP_SERVICE_PROTOCOL"},
    {&gUefiInfoEfiMpServicesProtocolGuid,                          "EFI_MP_SERVICES_PROTOCOL"},
    {&gUefiInfoEfiMsNetworkDelayProtocolGuid,                      "EFI_MS_NETWORK_DELAY_PROTOCOL"},
    {&gUefiInfoEfiMtftp4ProtocolGuid,                              "EFI_MTFTP4_PROTOCOL"},
    {&gUefiInfoEfiMtftp4ServiceBindingProtocolGuid,                "EFI_MTFTP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiMtftp6ProtocolGuid,                              "EFI_MTFTP6_PROTOCOL"},
    {&gUefiInfoEfiMtftp6ServiceBindingProtocolGuid,                "EFI_MTFTP6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiNetworkInterfaceIdentifierProtocolGuid,          "EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL"},
    {&gUefiInfoEfiNetworkInterfaceIdentifierProtocolGuid,          "EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL_GUID_31"},
    {&gUefiInfoEfiNetworkPkgTokenSpaceGuid,                        "EFI_NETWORK_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiNicIp4ConfigVariableGuid,                        "EFI_NIC_IP4_CONFIG_VARIABLE"},
    {&gUefiInfoEfiNormalSetupGuid,                                 "EFI_NORMAL_SETUP"},
    {&gUefiInfoEfiNt32PkgTokenSpaceGuid,                           "EFI_NT32_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiNvdimmLabelProtocolGuid,                         "EFI_NVDIMM_LABEL_PROTOCOL"},
    {&gUefiInfoEfiNvmeProtocolGuid,                                "EFI_NVME_PROTOCOL"},
    {&gUefiInfoEfiNvmExpressPassThruProtocolGuid,                  "EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL"},
    {&gUefiInfoEfiOEMBadgingProtocolGuid,                          "EFI_OEMBADGING_PROTOCOL"},
    {&gUefiInfoEfiOfflineCrashdumpTableGuid,                       "EFI_OFFLINE_CRASHDUMP_TABLE"},
    {&gUefiInfoEfiOfflineCrashdumpVariablesGuid,                   "EFI_OFFLINE_CRASHDUMP_VARIABLES"},
    {&gUefiInfoEfiPaddingNoneGuid,                                 "EFI_PADDING_NONE"},
    {&gUefiInfoEfiPaddingRsaesOaepGuid,                            "EFI_PADDING_RSAES_OAEP"},
    {&gUefiInfoEfiPaddingRsaesPkcs1V1P5Guid,                       "EFI_PADDING_RSAES_PKCS1V1P5"},
    {&gUefiInfoEfiPaddingRsassaPkcs1V1P5Guid,                      "EFI_PADDING_RSASSA_PKCS1V1P5"},
    {&gUefiInfoEfiPaddingRsassaPssGuid,                            "EFI_PADDING_RSASSA_PSS"},
    {&gUefiInfoEfiPartitionInfoProtocolGuid,                       "EFI_PARTITION_INFO_PROTOCOL"},
    {&gUefiInfoEfiPartitionRecordGuid,                             "EFI_PARTITION_RECORD"},
    {&gUefiInfoEfiPartTypeLegacyMbrGuid,                           "EFI_PART_TYPE_LEGACY_MBR"},
    {&gUefiInfoEfiPartTypeSystemPartGuid,                          "EFI_PART_TYPE_SYSTEM_PART"},
    {&gUefiInfoEfiPartTypeUnusedGuid,                              "EFI_PART_TYPE_UNUSED"},
    {&gUefiInfoEfiPcAnsiGuid,                                      "EFI_PC_ANSI"},
    {&gUefiInfoEfiPcdProtocolGuid,                                 "EFI_PCD_PROTOCOL"},
    {&gUefiInfoEfiPchExtendedResetProtocolGuid,                    "EFI_PCH_EXTENDED_RESET_PROTOCOL"},
    {&gUefiInfoEfiPchInfoProtocolGuid,                             "EFI_PCH_INFO_PROTOCOL"},
    {&gUefiInfoEfiPchS3SupportProtocolGuid,                        "EFI_PCH_S3_SUPPORT_PROTOCOL"},
    {&gUefiInfoEfiPchTokenSpaceGuid,                               "EFI_PCH_TOKEN_SPACE"},
    {&gUefiInfoEfiPciBusErrorSectionGuid,                          "EFI_PCI_BUS_ERROR_SECTION"},
    {&gUefiInfoEfiPciCfg2PpiGuid,                                  "EFI_PCI_CFG2_PPI"},
    {&gUefiInfoEfiPciCfgPpiInServiceTableGuid,                     "EFI_PCI_CFG_PPI_IN_SERVICE_TABLE"},
    {&gUefiInfoEfiPciDevErrorSectionGuid,                          "EFI_PCI_DEV_ERROR_SECTION"},
    {&gUefiInfoEfiPcieErrorSectionGuid,                            "EFI_PCIE_ERROR_SECTION"},
    {&gUefiInfoEfiPciEnumerationCompleteProtocolGuid,              "EFI_PCI_ENUMERATION_COMPLETE_PROTOCOL"},
    {&gUefiInfoEfiPciExpressBaseAddressGuid,                       "EFI_PCI_EXPRESS_BASE_ADDRESS"},
    {&gUefiInfoEfiPciHostBridgeResourceAllocationProtocolGuid,     "EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL"},
    {&gUefiInfoEfiPciHotPlugInitProtocolGuid,                      "EFI_PCI_HOT_PLUG_INIT_PROTOCOL"},
    {&gUefiInfoEfiPciHotPlugRequestProtocolGuid,                   "EFI_PCI_HOT_PLUG_REQUEST_PROTOCOL"},
    {&gUefiInfoEfiPciIoProtocolGuid,                               "EFI_PCI_IO_PROTOCOL"},
    {&gUefiInfoEfiPciLanInfoGuid,                                  "EFI_PCI_LAN_INFO"},
    {&gUefiInfoEfiPciOptionRomTableGuid,                           "EFI_PCI_OPTION_ROM_TABLE"},
    {&gUefiInfoEfiPciOverrideProtocolGuid,                         "EFI_PCI_OVERRIDE_PROTOCOL"},
    {&gUefiInfoEfiPciPlatformProtocolGuid,                         "EFI_PCI_PLATFORM_PROTOCOL"},
    {&gUefiInfoEfiPciRootBridgeIoProtocolGuid,                     "EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL"},
    {&gUefiInfoEfiPei144FloppyBlockIoPpiGuid,                      "EFI_PEI144_FLOPPY_BLOCK_IO_PPI"},
    {&gUefiInfoEfiPeiBootInRecoveryModePpiGuid,                    "EFI_PEI_BOOT_IN_RECOVERY_MODE_PPI"},
    {&gUefiInfoEfiPeiBootScriptExecuterPpiGuid,                    "EFI_PEI_BOOT_SCRIPT_EXECUTER_PPI"},
    {&gUefiInfoEfiPeiCpuIoPpiInstalledGuid,                        "EFI_PEI_CPU_IO_PPI_INSTALLED"},
    {&gUefiInfoEfiPeiDecompressPpiGuid,                            "EFI_PEI_DECOMPRESS_PPI"},
    {&gUefiInfoEfiPeiDeviceRecoveryModulePpiGuid,                  "EFI_PEI_DEVICE_RECOVERY_MODULE_PPI"},
    {&gUefiInfoEfiPeiFirmwareVolumeInfo2PpiGuid,                   "EFI_PEI_FIRMWARE_VOLUME_INFO2_PPI"},
    {&gUefiInfoEfiPeiFirmwareVolumeInfoMeasurementExcludedPpiGuid, "EFI_PEI_FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_PPI"},
    {&gUefiInfoEfiPeiFirmwareVolumeInfoPpiGuid,                    "EFI_PEI_FIRMWARE_VOLUME_INFO_PPI"},
    {&gUefiInfoEfiPeiFvFileLoaderPpiGuid,                          "EFI_PEI_FV_FILE_LOADER_PPI"},
    {&gUefiInfoEfiPeiI2cMasterPpiGuid,                             "EFI_PEI_I2C_MASTER_PPI"},
    {&gUefiInfoEfiPeiIdeBlockIoPpiGuid,                            "EFI_PEI_IDE_BLOCK_IO_PPI"},
    {&gUefiInfoEfiPeiLoadedImagePpiGuid,                           "EFI_PEI_LOADED_IMAGE_PPI"},
    {&gUefiInfoEfiPeiLoadFilePpiGuid,                              "EFI_PEI_LOAD_FILE_PPI"},
    {&gUefiInfoEfiPeiMasterBootModePpiGuid,                        "EFI_PEI_MASTER_BOOT_MODE_PPI"},
    {&gUefiInfoEfiPeiMemoryDiscoveredPpiGuid,                      "EFI_PEI_MEMORY_DISCOVERED_PPI"},
    {&gUefiInfoEfiPeiPcdPpiGuid,                                   "EFI_PEI_PCD_PPI"},
    {&gUefiInfoEfiPeiPeCoffLoaderGuid,                             "EFI_PEI_PE_COFF_LOADER"},
    {&gUefiInfoEfiPeiReadOnlyVariable2PpiGuid,                     "EFI_PEI_READ_ONLY_VARIABLE2_PPI"},
    {&gUefiInfoEfiPeiReadOnlyVariablePpiGuid,                      "EFI_PEI_READ_ONLY_VARIABLE_PPI"},
    {&gUefiInfoEfiPeiRecoveryModulePpiGuid,                        "EFI_PEI_RECOVERY_MODULE_PPI"},
    {&gUefiInfoEfiPeiResetPpiGuid,                                 "EFI_PEI_RESET_PPI"},
    {&gUefiInfoEfiPeiRscHandlerPpiGuid,                            "EFI_PEI_RSC_HANDLER_PPI"},
    {&gUefiInfoEfiPeiS3Resume2PpiGuid,                             "EFI_PEI_S3_RESUME2_PPI"},
    {&gUefiInfoEfiPeiS3ResumePpiGuid,                              "EFI_PEI_S3_RESUME_PPI"},
    {&gUefiInfoEfiPeiSectionExtractionPpiGuid,                     "EFI_PEI_SECTION_EXTRACTION_PPI"},
    {&gUefiInfoEfiPeiSecurity2PpiGuid,                             "EFI_PEI_SECURITY2_PPI"},
    {&gUefiInfoEfiPeiSecurityPpiGuid,                              "EFI_PEI_SECURITY_PPI"},
    {&gUefiInfoEfiPeiSmbus2PpiGuid,                                "EFI_PEI_SMBUS2_PPI"},
    {&gUefiInfoEfiPeiSmbusPpiGuid,                                 "EFI_PEI_SMBUS_PPI"},
    {&gUefiInfoEfiPeiSmmCommunicationPpiGuid,                      "EFI_PEI_SMM_COMMUNICATION_PPI"},
    {&gUefiInfoEfiPeiStallPpiGuid,                                 "EFI_PEI_STALL_PPI"},
    {&gUefiInfoEfiPeiStatusCodePpiGuid,                            "EFI_PEI_STATUS_CODE_PPI"},
    {&gUefiInfoEfiPeiVirtualBlockIoPpiGuid,                        "EFI_PEI_VIRTUAL_BLOCK_IO_PPI"},
    {&gUefiInfoEfiPersistentVirtualCdGuid,                         "EFI_PERSISTENT_VIRTUAL_CD"},
    {&gUefiInfoEfiPersistentVirtualDiskGuid,                       "EFI_PERSISTENT_VIRTUAL_DISK"},
    {&gUefiInfoEfiPhysicalPresenceGuid,                            "EFI_PHYSICAL_PRESENCE"},
    {&gUefiInfoEfiPkcs7VerifyProtocolGuid,                         "EFI_PKCS7_VERIFY_PROTOCOL"},
    {&gUefiInfoEfiPlatformBootModeGuid,                            "EFI_PLATFORM_BOOT_MODE"},
    {&gUefiInfoEfiPlatformCpuInfoGuid,                             "EFI_PLATFORM_CPU_INFO"},
    {&gUefiInfoEfiPlatformCpuProtocolGuid,                         "EFI_PLATFORM_CPU_PROTOCOL"},
    {&gUefiInfoEfiPlatformDriverOverrideProtocolGuid,              "EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL"},
    {&gUefiInfoEfiPlatformIdeInitProtocolGuid,                     "EFI_PLATFORM_IDE_INIT_PROTOCOL"},
    {&gUefiInfoEfiPlatformInfoGuid,                                "EFI_PLATFORM_INFO"},
    {&gUefiInfoEfiPlatformMemoryErrorSectionGuid,                  "EFI_PLATFORM_MEMORY_ERROR_SECTION"},
    {&gUefiInfoEfiPlatformToDriverConfigurationClpGuid,            "EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP"},
    {&gUefiInfoEfiPlatformToDriverConfigurationProtocolGuid,       "EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL"},
    {&gUefiInfoEfiPowerOnHobGuid,                                  "EFI_POWER_ON_HOB"},
    {&gUefiInfoEfiPpamManifestTableGuid,                           "EFI_PPAM_MANIFEST_TABLE"},
    {&gUefiInfoEfiPrint2ProtocolGuid,                              "EFI_PRINT2_PROTOCOL"},
    {&gUefiInfoEfiPrintProtocolGuid,                               "EFI_PRINT_PROTOCOL"},
    {&gUefiInfoEfiProcessorGenericErrorSectionGuid,                "EFI_PROCESSOR_GENERIC_ERROR_SECTION"},
    {&gUefiInfoEfiProcessorSpecificErrorSectionGuid,               "EFI_PROCESSOR_SPECIFIC_ERROR_SECTION"},
    {&gUefiInfoEfiProcessorSubClassGuid,                           "EFI_PROCESSOR_SUB_CLASS"},
    {&gUefiInfoEfiPropertiesTableGuid,                             "EFI_PROPERTIES_TABLE"},
    {&gUefiInfoEfiPs2PolicyProtocolGuid,                           "EFI_PS2_POLICY_PROTOCOL"},
    {&gUefiInfoEfiPxeBaseCodeCallbackProtocolGuid,                 "EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL"},
    {&gUefiInfoEfiPxeBaseCodeProtocolGuid,                         "EFI_PXE_BASE_CODE_PROTOCOL"},
    {&gUefiInfoEfiRamDiskProtocolGuid,                             "EFI_RAM_DISK_PROTOCOL"},
    {&gUefiInfoEfiRealTimeClockArchProtocolGuid,                   "EFI_REAL_TIME_CLOCK_ARCH_PROTOCOL"},
    {&gUefiInfoEfiRedfishDiscoverProtocolGuid,                     "EFI_REDFISH_DISCOVER_PROTOCOL"},
    {&gUefiInfoEfiRegexSyntaxTypeEcma_262AsciiGuid,                "EFI_REGEX_SYNTAX_TYPE_ECMA_262_ASCII"},
    {&gUefiInfoEfiRegexSyntaxTypeEcma_262Guid,                     "EFI_REGEX_SYNTAX_TYPE_ECMA_262"},
    {&gUefiInfoEfiRegexSyntaxTypePerlAsciiGuid,                    "EFI_REGEX_SYNTAX_TYPE_PERL_ASCII"},
    {&gUefiInfoEfiRegexSyntaxTypePerlGuid,                         "EFI_REGEX_SYNTAX_TYPE_PERL"},
    {&gUefiInfoEfiRegexSyntaxTypePosixExtendedAsciiGuid,           "EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED_ASCII"},
    {&gUefiInfoEfiRegexSyntaxTypePosixExtendedGuid,                "EFI_REGEX_SYNTAX_TYPE_POSIX_EXTENDED"},
    {&gUefiInfoEfiRegularExpressionProtocolGuid,                   "EFI_REGULAR_EXPRESSION_PROTOCOL"},
    {&gUefiInfoEfiResetArchProtocolGuid,                           "EFI_RESET_ARCH_PROTOCOL"},
    {&gUefiInfoEfiResetNotificationProtocolGuid,                   "EFI_RESET_NOTIFICATION_PROTOCOL"},
    {&gUefiInfoEfiRestExProtocolGuid,                              "EFI_REST_EX_PROTOCOL"},
    {&gUefiInfoEfiRestExServiceBindingProtocolGuid,                "EFI_REST_EX_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiRestJsonStructureProtocolGuid,                   "EFI_REST_JSON_STRUCTURE_PROTOCOL"},
    {&gUefiInfoEfiRestProtocolGuid,                                "EFI_REST_PROTOCOL"},
    {&gUefiInfoEfiRngAlgorithmSp80090Ctr256Guid,                   "EFI_RNG_ALGORITHM_SP80090_CTR256"},
    {&gUefiInfoEfiRngAlgorithmSp80090Hash256Guid,                  "EFI_RNG_ALGORITHM_SP80090_HASH256"},
    {&gUefiInfoEfiRngAlgorithmSp80090Hmac256Guid,                  "EFI_RNG_ALGORITHM_SP80090_HMAC256"},
    {&gUefiInfoEfiRngAlgorithmSp800_90Ctr_256Guid,                 "EFI_RNG_ALGORITHM_SP800_90_CTR_256"},
    {&gUefiInfoEfiRngAlgorithmSp800_90Hash_256Guid,                "EFI_RNG_ALGORITHM_SP800_90_HASH_256"},
    {&gUefiInfoEfiRngAlgorithmSp800_90Hmac_256Guid,                "EFI_RNG_ALGORITHM_SP800_90_HMAC_256"},
    {&gUefiInfoEfiRngAlgorithmX9313DesGuid,                        "EFI_RNG_ALGORITHM_X9313_DES"},
    {&gUefiInfoEfiRngAlgorithmX931AesGuid,                         "EFI_RNG_ALGORITHM_X931_AES"},
    {&gUefiInfoEfiRngAlgorithmX9_31_3DesGuid,                      "EFI_RNG_ALGORITHM_X9_31_3DES"},
    {&gUefiInfoEfiRngAlgorithmX9_31AesGuid,                        "EFI_RNG_ALGORITHM_X9_31_AES"},
    {&gUefiInfoEfiRngProtocolGuid,                                 "EFI_RNG_PROTOCOL"},
    {&gUefiInfoEfiRscHandlerProtocolGuid,                          "EFI_RSC_HANDLER_PROTOCOL"},
    {&gUefiInfoEfiRuntimeArchProtocolGuid,                         "EFI_RUNTIME_ARCH_PROTOCOL"},
    {&gUefiInfoEfiRuntimeCryptProtocolGuid,                        "EFI_RUNTIME_CRYPT_PROTOCOL"},
    {&gUefiInfoEfiS3SaveStateProtocolGuid,                         "EFI_S3_SAVE_STATE_PROTOCOL"},
    {&gUefiInfoEfiS3SmmSaveStateProtocolGuid,                      "EFI_S3_SMM_SAVE_STATE_PROTOCOL"},
    {&gUefiInfoEfiSalMcaInitPmiProtocolGuid,                       "EFI_SAL_MCA_INIT_PMI_PROTOCOL"},
    {&gUefiInfoEfiSalSystemTableGuid,                              "EFI_SAL_SYSTEM_TABLE"},
    {&gUefiInfoEfiSasDevicePathGuid,                               "EFI_SAS_DEVICE_PATH"},
    {&gUefiInfoEfiScsiIoProtocolGuid,                              "EFI_SCSI_IO_PROTOCOL"},
    {&gUefiInfoEfiScsiPassThruProtocolGuid,                        "EFI_SCSI_PASS_THRU_PROTOCOL"},
    {&gUefiInfoEfiSdccCardInfoProtocolGuid,                        "EFI_SDCC_CARDINFO_PROTOCOL"},
    {&gUefiInfoEfiSdHostIoProtocolGuid,                            "EFI_SD_HOST_IO_PROTOCOL"},
    {&gUefiInfoEfiSdMmcPassThruProtocolGuid,                       "EFI_SD_MMC_PASS_THRU_PROTOCOL"},
    {&gUefiInfoEfiSdRemovableProtocolGuid,                         "EFI_SD_REMOVABLE_PROTOCOL"},
    {&gUefiInfoEfiSecPlatformInformationPpiGuid,                   "EFI_SEC_PLATFORM_INFORMATION_PPI"},
    {&gUefiInfoEfiSeCRcInfoProtocolGuid,                           "EFI_SE_CRC_INFO_PROTOCOL"},
    {&gUefiInfoEfiSectionExtractionProtocolGuid,                   "EFI_SECTION_EXTRACTION_PROTOCOL"},
    {&gUefiInfoEfiSecureBootEnableDisableGuid,                     "EFI_SECURE_BOOT_ENABLE_DISABLE"},
    {&gUefiInfoEfiSecureElementResetProtocolGuid,                  "EFI_SECURE_ELEMENT_RESET_PROTOCOL"},
    {&gUefiInfoEfiSecurity2ArchProtocolGuid,                       "EFI_SECURITY2_ARCH_PROTOCOL"},
    {&gUefiInfoEfiSecurityArchProtocolGuid,                        "EFI_SECURITY_ARCH_PROTOCOL"},
    {&gUefiInfoEfiSecurityPkgTokenSpaceGuid,                       "EFI_SECURITY_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiSecurityPolicyProtocolGuid,                      "EFI_SECURITY_POLICY_PROTOCOL"},
    {&gUefiInfoEfiSerialIoProtocolGuid,                            "EFI_SERIAL_IO_PROTOCOL"},
    {&gUefiInfoEfiSerialPortTokenSpaceGuid,                        "EFI_SERIAL_PORT_TOKEN_SPACE"},
    {&gUefiInfoEfiSerialTerminalDeviceTypeGuid,                    "EFI_SERIAL_TERMINAL_DEVICE_TYPE"},
    {&gUefiInfoEfiSetupVariableGuid,                               "EFI_SETUP_VARIABLE"},
    {&gUefiInfoEfiShellDynamicCommandProtocolGuid,                 "EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL"},
    {&gUefiInfoEfiShellEnvironment2ExtGuid,                        "EFI_SHELL_ENVIRONMENT2_EXT"},
    {&gUefiInfoEfiShellEnvironment2Guid,                           "EFI_SHELL_ENVIRONMENT2"},
    {&gUefiInfoEfiShellInterfaceGuid,                              "EFI_SHELL_INTERFACE"},
    {&gUefiInfoEfiShellParametersProtocolGuid,                     "EFI_SHELL_PARAMETERS_PROTOCOL"},
    {&gUefiInfoEfiShellPkgTokenSpaceGuid,                          "EFI_SHELL_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiShellProtocolGuid,                               "EFI_SHELL_PROTOCOL"},
    {&gUefiInfoEfiSimpleFileSystemProtocolGuid,                    "EFI_SIMPLE_FILE_SYSTEM_PROTOCOL"},
    {&gUefiInfoEfiSimpleNetworkProtocolGuid,                       "EFI_SIMPLE_NETWORK_PROTOCOL"},
    {&gUefiInfoEfiSimplePointerProtocolGuid,                       "EFI_SIMPLE_POINTER_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextInProtocolGuid,                        "EFI_SIMPLE_TEXT_IN_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextInProtocolGuid,                        "EFI_SIMPLE_TEXT_INPUT_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextInputExProtocolGuid,                   "EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextInputProtocolGuid,                     "EFI_SIMPLE_TEXT_INPUT_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextOutProtocolGuid,                       "EFI_SIMPLE_TEXT_OUT_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextOutProtocolGuid,                       "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL"},
    {&gUefiInfoEfiSimpleTextOutputProtocolGuid,                    "EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL"},
    {&gUefiInfoEfiSioProtocolGuid,                                 "EFI_SIO_PROTOCOL"},
    {&gUefiInfoEfiSioVariableGuid,                                 "EFI_SIO_VARIABLE"},
    {&gUefiInfoEfiSmartCardEdgeProtocolGuid,                       "EFI_SMART_CARD_EDGE_PROTOCOL"},
    {&gUefiInfoEfiSmartCardReaderProtocolGuid,                     "EFI_SMART_CARD_READER_PROTOCOL"},
    {&gUefiInfoEfiSmbios3TableGuid,                                "EFI_SMBIOS3_TABLE"},
    {&gUefiInfoEfiSmbiosProtocolGuid,                              "EFI_SMBIOS_PROTOCOL"},
    {&gUefiInfoEfiSmbiosSlotPopulationGuid,                        "EFI_SMBIOS_SLOT_POPULATION"},
    {&gUefiInfoEfiSmbiosTableGuid,                                 "EFI_SMBIOS_TABLE"},
    {&gUefiInfoEfiSmbusArpMapGuid,                                 "EFI_SMBUS_ARP_MAP"},
    {&gUefiInfoEfiSmbusHcProtocolGuid,                             "EFI_SMBUS_HC_PROTOCOL"},
    {&gUefiInfoEfiSmmAccess2ProtocolGuid,                          "EFI_SMM_ACCESS2_PROTOCOL"},
    {&gUefiInfoEfiSmmAccessProtocolGuid,                           "EFI_SMM_ACCESS_PROTOCOL"},
    {&gUefiInfoEfiSmmBase2ProtocolGuid,                            "EFI_SMM_BASE2_PROTOCOL"},
    {&gUefiInfoEfiSmmBaseHelperReadyProtocolGuid,                  "EFI_SMM_BASE_HELPER_READY_PROTOCOL"},
    {&gUefiInfoEfiSmmBaseProtocolGuid,                             "EFI_SMM_BASE_PROTOCOL"},
    {&gUefiInfoEfiSmmBaseThunkCommunicationGuid,                   "EFI_SMM_BASE_THUNK_COMMUNICATION"},
    {&gUefiInfoEfiSmmCommunicationProtocolGuid,                    "EFI_SMM_COMMUNICATION_PROTOCOL"},
    {&gUefiInfoEfiSmmConfigurationProtocolGuid,                    "EFI_SMM_CONFIGURATION_PROTOCOL"},
    {&gUefiInfoEfiSmmControl2ProtocolGuid,                         "EFI_SMM_CONTROL2_PROTOCOL"},
    {&gUefiInfoEfiSmmControlProtocolGuid,                          "EFI_SMM_CONTROL_PROTOCOL"},
    {&gUefiInfoEfiSmmCpuIo2ProtocolGuid,                           "EFI_SMM_CPU_IO2_PROTOCOL"},
    {&gUefiInfoEfiSmmCpuIoGuid,                                    "EFI_SMM_CPU_IO"},
    {&gUefiInfoEfiSmmCpuProtocolGuid,                              "EFI_SMM_CPU_PROTOCOL"},
    {&gUefiInfoEfiSmmCpuSaveStateProtocolGuid,                     "EFI_SMM_CPU_SAVE_STATE_PROTOCOL"},
    {&gUefiInfoEfiSmmEndOfDxeProtocolGuid,                         "EFI_SMM_END_OF_DXE_PROTOCOL"},
    {&gUefiInfoEfiSmmFaultTolerantWriteProtocolGuid,               "EFI_SMM_FAULT_TOLERANT_WRITE_PROTOCOL"},
    {&gUefiInfoEfiSmmFirmwareVolumeBlockProtocolGuid,              "EFI_SMM_FIRMWARE_VOLUME_BLOCK_PROTOCOL"},
    {&gUefiInfoEfiSmmGpiDispatch2ProtocolGuid,                     "EFI_SMM_GPI_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmGpiDispatchProtocolGuid,                      "EFI_SMM_GPI_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmIchnDispatchExProtocolGuid,                   "EFI_SMM_ICHN_DISPATCH_EX_PROTOCOL"},
    {&gUefiInfoEfiSmmIchnDispatchProtocolGuid,                     "EFI_SMM_ICHN_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmIoTrapDispatch2ProtocolGuid,                  "EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmIoTrapDispatchProtocolGuid,                   "EFI_SMM_IO_TRAP_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmLockBoxCommunicationGuid,                     "EFI_SMM_LOCK_BOX_COMMUNICATION"},
    {&gUefiInfoEfiSmmPciRootBridgeIoProtocolGuid,                  "EFI_SMM_PCI_ROOT_BRIDGE_IO_PROTOCOL"},
    {&gUefiInfoEfiSmmPeiSmramMemoryReserveGuid,                    "EFI_SMM_PEI_SMRAM_MEMORY_RESERVE"},
    {&gUefiInfoEfiSmmPeriodicTimerDispatch2ProtocolGuid,           "EFI_SMM_PERIODIC_TIMER_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmPeriodicTimerDispatchProtocolGuid,            "EFI_SMM_PERIODIC_TIMER_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmPowerButtonDispatch2ProtocolGuid,             "EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmPowerButtonDispatchProtocolGuid,              "EFI_SMM_POWER_BUTTON_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmReadyToLockProtocolGuid,                      "EFI_SMM_READY_TO_LOCK_PROTOCOL"},
    {&gUefiInfoEfiSmmRscHandlerProtocolGuid,                       "EFI_SMM_RSC_HANDLER_PROTOCOL"},
    {&gUefiInfoEfiSmmSmbusProtocolGuid,                            "EFI_SMM_SMBUS_PROTOCOL"},
    {&gUefiInfoEfiSmmSpiProtocolGuid,                              "EFI_SMM_SPI_PROTOCOL"},
    {&gUefiInfoEfiSmmStandbyButtonDispatch2ProtocolGuid,           "EFI_SMM_STANDBY_BUTTON_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmStandbyButtonDispatchProtocolGuid,            "EFI_SMM_STANDBY_BUTTON_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmStatusCodeProtocolGuid,                       "EFI_SMM_STATUS_CODE_PROTOCOL"},
    {&gUefiInfoEfiSmmSwapAddressRangeProtocolGuid,                 "EFI_SMM_SWAP_ADDRESS_RANGE_PROTOCOL"},
    {&gUefiInfoEfiSmmSwDispatch2ProtocolGuid,                      "EFI_SMM_SW_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmSwDispatchProtocolGuid,                       "EFI_SMM_SW_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmSxDispatch2ProtocolGuid,                      "EFI_SMM_SX_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmSxDispatchProtocolGuid,                       "EFI_SMM_SX_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmUsbDispatch2ProtocolGuid,                     "EFI_SMM_USB_DISPATCH2_PROTOCOL"},
    {&gUefiInfoEfiSmmUsbDispatchProtocolGuid,                      "EFI_SMM_USB_DISPATCH_PROTOCOL"},
    {&gUefiInfoEfiSmmVariableProtocolGuid,                         "EFI_SMM_VARIABLE_PROTOCOL"},
    {&gUefiInfoEfiSocketProtocolGuid,                              "EFI_SOCKET_PROTOCOL"},
    {&gUefiInfoEfiSocketServiceBindingProtocolGuid,                "EFI_SOCKET_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiSourceLevelDebugPkgTokenSpaceGuid,               "EFI_SOURCE_LEVEL_DEBUG_PKG_TOKEN_SPACE"},
    {&gUefiInfoEfiSpeakerInterfaceProtocolGuid,                    "EFI_SPEAKER_INTERFACE_PROTOCOL"},
    {&gUefiInfoEfiSpiAcpiProtocolGuid,                             "EFI_SPI_ACPI_PROTOCOL"},
    {&gUefiInfoEfiSpiBusProtocolGuid,                              "EFI_SPI_BUS_PROTOCOL"},
    {&gUefiInfoEfiSpiHostProtocolGuid,                             "EFI_SPI_HOST_PROTOCOL"},
    {&gUefiInfoEfiSpiProtocolGuid,                                 "EFI_SPI_PROTOCOL"},
    {&gUefiInfoEfiStandardErrorDeviceGuid,                         "EFI_STANDARD_ERROR_DEVICE"},
    {&gUefiInfoEfiStatusCodeDataTypeDebugGuid,                     "EFI_STATUS_CODE_DATA_TYPE_DEBUG"},
    {&gUefiInfoEfiStatusCodeDataTypeStringGuid,                    "EFI_STATUS_CODE_DATA_TYPE_STRING"},
    {&gUefiInfoEfiStatusCodeRuntimeProtocolGuid,                   "EFI_STATUS_CODE_RUNTIME_PROTOCOL"},
    {&gUefiInfoEfiStatusCodeSpecificDataGuid,                      "EFI_STATUS_CODE_SPECIFIC_DATA"},
    {&gUefiInfoEfiStorageSecurityCommandProtocolGuid,              "EFI_STORAGE_SECURITY_COMMAND_PROTOCOL"},
    {&gUefiInfoEfiSupplicantProtocolGuid,                          "EFI_SUPPLICANT_PROTOCOL"},
    {&gUefiInfoEfiSupplicantServiceBindingProtocolGuid,            "EFI_SUPPLICANT_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiSwapAddressRangeProtocolGuid,                    "EFI_SWAP_ADDRESS_RANGE_PROTOCOL"},
    {&gUefiInfoEfiSystemNvDataFvGuid,                              "EFI_SYSTEM_NV_DATA_FV"},
    {&gUefiInfoEfiSystemPartitionGuid,                             "PARTITION_SYSTEM"},
    {&gUefiInfoEfiSystemResourceTableGuid,                         "EFI_SYSTEM_RESOURCE_TABLE"},
    {&gUefiInfoEfiTapeIoProtocolGuid,                              "EFI_TAPE_IO_PROTOCOL"},
    {&gUefiInfoEfiTcgPrivateInterfaceGuid,                         "EFI_TCG_PRIVATE_INTERFACE"},
    {&gUefiInfoEfiTcgProtocolGuid,                                 "EFI_TCG_PROTOCOL"},
    {&gUefiInfoEfiTcoResetProtocolGuid,                            "EFI_TCO_RESET_PROTOCOL"},
    {&gUefiInfoEfiTcp4ProtocolGuid,                                "EFI_TCP4_PROTOCOL"},
    {&gUefiInfoEfiTcp4ServiceBindingProtocolGuid,                  "EFI_TCP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiTcp6ProtocolGuid,                                "EFI_TCP6_PROTOCOL"},
    {&gUefiInfoEfiTcp6ServiceBindingProtocolGuid,                  "EFI_TCP6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiTdtOperationProtocolGuid,                        "EFI_TDT_OPERATION_PROTOCOL"},
    {&gUefiInfoEfiTdtProtocolGuid,                                 "EFI_TDT_PROTOCOL"},
    {&gUefiInfoEfiTemporaryRamDonePpiGuid,                         "EFI_TEMPORARY_RAM_DONE_PPI"},
    {&gUefiInfoEfiTemporaryRamSupportPpiGuid,                      "EFI_TEMPORARY_RAM_SUPPORT_PPI"},
    {&gUefiInfoEfiTimerArchProtocolGuid,                           "EFI_TIMER_ARCH_PROTOCOL"},
    {&gUefiInfoEfiTimestampProtocolGuid,                           "EFI_TIMESTAMP_PROTOCOL"},
    {&gUefiInfoEfiTlsConfigurationProtocolGuid,                    "EFI_TLS_CONFIGURATION_PROTOCOL"},
    {&gUefiInfoEfiTlsProtocolGuid,                                 "EFI_TLS_PROTOCOL"},
    {&gUefiInfoEfiTlsServiceBindingProtocolGuid,                   "EFI_TLS_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiTpmDeviceInstanceNoneGuid,                       "EFI_TPM_DEVICE_INSTANCE_NONE"},
    {&gUefiInfoEfiTpmDeviceInstanceTpm12Guid,                      "EFI_TPM_DEVICE_INSTANCE_TPM12"},
    {&gUefiInfoEfiTpmDeviceInstanceTpm20DtpmGuid,                  "EFI_TPM_DEVICE_INSTANCE_TPM20_DTPM"},
    {&gUefiInfoEfiTpmDeviceSelectedGuid,                           "EFI_TPM_DEVICE_SELECTED"},
    {&gUefiInfoEfiTpmMpDriverProtocolGuid,                         "EFI_TPM_MP_DRIVER_PROTOCOL"},
    {&gUefiInfoEfiTrEEPhysicalPresenceGuid,                        "EFI_TR_EEPHYSICAL_PRESENCE"},
    {&gUefiInfoEfiTrEEProtocolGuid,                                "EFI_TR_EEPROTOCOL"},
    {&gUefiInfoEfiTscFrequencyGuid,                                "EFI_TSC_FREQUENCY"},
    {&gUefiInfoEfiUartDevicePathGuid,                              "EFI_UART_DEVICE_PATH"},
    {&gUefiInfoEfiUdp4ProtocolGuid,                                "EFI_UDP4_PROTOCOL"},
    {&gUefiInfoEfiUdp4ServiceBindingProtocolGuid,                  "EFI_UDP4_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiUdp6ProtocolGuid,                                "EFI_UDP6_PROTOCOL"},
    {&gUefiInfoEfiUdp6ServiceBindingProtocolGuid,                  "EFI_UDP6_SERVICE_BINDING_PROTOCOL"},
    {&gUefiInfoEfiUfsDeviceConfigProtocolGuid,                     "EFI_UFS_DEVICE_CONFIG"},
    {&gUefiInfoEfiUgaDrawProtocolGuid,                             "EFI_UGA_DRAW_PROTOCOL"},
    {&gUefiInfoEfiUgaIoProtocolGuid,                               "EFI_UGA_IO_PROTOCOL"},
    {&gUefiInfoEfiUnicodeCollation2ProtocolGuid,                   "EFI_UNICODE_COLLATION2_PROTOCOL"},
    {&gUefiInfoEfiUnicodeCollation2ProtocolGuid,                   "EFI_UNICODE_COLLATION_PROTOCOL2"},
    {&gUefiInfoEfiUnicodeCollationProtocolGuid,                    "EFI_UNICODE_COLLATION_PROTOCOL"},
    {&gUefiInfoEfiUpdateDataFileGuid,                              "EFI_UPDATE_DATA_FILE"},
    {&gUefiInfoEfiUsb2HcProtocolGuid,                              "EFI_USB2_HC_PROTOCOL"},
    {&gUefiInfoEfiUsbFunctionIoProtocolGuid,                       "EFI_USBFN_IO_PROTOCOL"},
    {&gUefiInfoEfiUsbHcProtocolGuid,                               "EFI_USB_HC_PROTOCOL"},
    {&gUefiInfoEfiUsbInitProtocolGuid,                             "EFI_USB_INIT_PROTOCOL"},
    {&gUefiInfoEfiUsbIoProtocolGuid,                               "EFI_USB_IO_PROTOCOL"},
    {&gUefiInfoEfiUsbKeyboardConnectGuid,                          "EFI_USB_KEYBOARD_CONNECT"},
    {&gUefiInfoEfiUserCredential2ProtocolGuid,                     "EFI_USER_CREDENTIAL2_PROTOCOL"},
    {&gUefiInfoEfiUserCredentialClassFingerprintGuid,              "EFI_USER_CREDENTIAL_CLASS_FINGERPRINT"},
    {&gUefiInfoEfiUserCredentialClassHandprintGuid,                "EFI_USER_CREDENTIAL_CLASS_HANDPRINT"},
    {&gUefiInfoEfiUserCredentialClassPasswordGuid,                 "EFI_USER_CREDENTIAL_CLASS_PASSWORD"},
    {&gUefiInfoEfiUserCredentialClassSecureCardGuid,               "EFI_USER_CREDENTIAL_CLASS_SECURE_CARD"},
    {&gUefiInfoEfiUserCredentialClassSmartCardGuid,                "EFI_USER_CREDENTIAL_CLASS_SMART_CARD"},
    {&gUefiInfoEfiUserCredentialClassUnknownGuid,                  "EFI_USER_CREDENTIAL_CLASS_UNKNOWN"},
    {&gUefiInfoEfiUserCredentialProtocolGuid,                      "EFI_USER_CREDENTIAL_PROTOCOL"},
    {&gUefiInfoEfiUserInfoAccessSetupAdminGuid,                    "EFI_USER_INFO_ACCESS_SETUP_ADMIN"},
    {&gUefiInfoEfiUserInfoAccessSetupNormalGuid,                   "EFI_USER_INFO_ACCESS_SETUP_NORMAL"},
    {&gUefiInfoEfiUserInfoAccessSetupRestrictedGuid,               "EFI_USER_INFO_ACCESS_SETUP_RESTRICTED"},
    {&gUefiInfoEfiUserManagerProtocolGuid,                         "EFI_USER_MANAGER_PROTOCOL"},
    {&gUefiInfoEfiVariableArchProtocolGuid,                        "EFI_VARIABLE_ARCH_PROTOCOL"},
    {&gUefiInfoEfiVariableGuid,                                    "EFI_VARIABLE"},
    {&gUefiInfoEfiVariableIndexTableGuid,                          "EFI_VARIABLE_INDEX_TABLE"},
    {&gUefiInfoEfiVariableWriteArchProtocolGuid,                   "EFI_VARIABLE_WRITE_ARCH_PROTOCOL"},
    {&gUefiInfoEfiVectorHandoffInfoPpiGuid,                        "EFI_VECTOR_HANDOFF_INFO_PPI"},
    {&gUefiInfoEfiVectorHandoffTableGuid,                          "EFI_VECTOR_HANDOFF_TABLE"},
    {&gUefiInfoEfiVendorKeysNvGuid,                                "EFI_VENDOR_KEYS_NV"},
    {&gUefiInfoEfiVgaMiniPortProtocolGuid,                         "EFI_VGA_MINI_PORT_PROTOCOL"},
    {&gUefiInfoEfiVirtualCdGuid,                                   "EFI_VIRTUAL_CD"},
    {&gUefiInfoEfiVirtualDiskGuid,                                 "EFI_VIRTUAL_DISK"},
    {&gUefiInfoEfiVlanConfigProtocolGuid,                          "EFI_VLAN_CONFIG_PROTOCOL"},
    {&gUefiInfoEfiVlv2VariableGuid,                                "EFI_VLV2_VARIABLE"},
    {&gUefiInfoEfiVLVTokenSpaceGuid,                               "EFI_VLVTOKEN_SPACE"},
    {&gUefiInfoEfiVT100Guid,                                       "EFI_VT100"},
    {&gUefiInfoEfiVT100PlusGuid,                                   "EFI_VT100_PLUS"},
    {&gUefiInfoEfiVt_100Guid,                                      "EFI_VT_100"},
    {&gUefiInfoEfiVt_100PlusGuid,                                  "EFI_VT_100_PLUS"},
    {&gUefiInfoEfiVtUtf8Guid,                                      "EFI_VT_UTF8"},
    {&gUefiInfoEfiVTUTF8Guid,                                      "EFI_VTUTF8"},
    {&gUefiInfoEfiWatchdogTimerArchProtocolGuid,                   "EFI_WATCHDOG_TIMER_ARCH_PROTOCOL"},
    {&gUefiInfoEfiWatchdogTimerDriverProtocolGuid,                 "EFI_WATCHDOG_TIMER_DRIVER_PROTOCOL"},
    {&gUefiInfoEfiWiFi2ProtocolGuid,                               "EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL"},
    {&gUefiInfoEfiWiFiProtocolGuid,                                "EFI_WIRELESS_MAC_CONNECTION_PROTOCOL"},
    {&gUefiInfoEfiWindowsDumpTableGuid,                            "EFI_WINDOWS_DUMP_TABLE"},
    {&gUefiInfoEfiWinNtConsoleGuid,                                "EFI_WIN_NT_CONSOLE"},
    {&gUefiInfoEfiWinNtFileSystemGuid,                             "EFI_WIN_NT_FILE_SYSTEM"},
    {&gUefiInfoEfiWinNtGopGuid,                                    "EFI_WIN_NT_GOP"},
    {&gUefiInfoEfiWinNtIoProtocolGuid,                             "EFI_WIN_NT_IO_PROTOCOL"},
    {&gUefiInfoEfiWinNtPassThroughGuid,                            "EFI_WIN_NT_PASS_THROUGH"},
    {&gUefiInfoEfiWinNtPhysicalDisksGuid,                          "EFI_WIN_NT_PHYSICAL_DISKS"},
    {&gUefiInfoEfiWinNtSerialPortGuid,                             "EFI_WIN_NT_SERIAL_PORT"},
    {&gUefiInfoEfiWinNtSystemConfigGuid,                           "EFI_WIN_NT_SYSTEM_CONFIG"},
    {&gUefiInfoEfiWinNtThunkProtocolGuid,                          "EFI_WIN_NT_THUNK_PROTOCOL"},
    {&gUefiInfoEfiWinNtUgaGuid,                                    "EFI_WIN_NT_UGA"},
    {&gUefiInfoEfiWinNtVirtualDisksGuid,                           "EFI_WIN_NT_VIRTUAL_DISKS"},
    {&gUefiInfoEfiXenInfoGuid,                                     "EFI_XEN_INFO"},
    {&gUefiInfoEmbeddedDeviceGuid,                                 "EMBEDDED_DEVICE"},
    {&gUefiInfoEmbeddedExternalDeviceProtocolGuid,                 "EMBEDDED_EXTERNAL_DEVICE_PROTOCOL"},
    {&gUefiInfoEmbeddedGpioProtocolGuid,                           "EMBEDDED_GPIO_PROTOCOL"},
    {&gUefiInfoEmbeddedTokenSpaceGuid,                             "EMBEDDED_TOKEN_SPACE"},
    {&gUefiInfoEmptyGuid,                                          "EMPTY"},
    {&gUefiInfoEmuBlockIoProtocolGuid,                             "EMU_BLOCK_IO_PROTOCOL"},
    {&gUefiInfoEmuGraphicsWindowProtocolGuid,                      "EMU_GRAPHICS_WINDOW_PROTOCOL"},
    {&gUefiInfoEmuIoThunkProtocolGuid,                             "EMU_IO_THUNK_PROTOCOL"},
    {&gUefiInfoEmulatorPkgTokenSpaceGuid,                          "EMULATOR_PKG_TOKEN_SPACE"},
    {&gUefiInfoEmuPhysicalDisksGuid,                               "EMU_PHYSICAL_DISKS"},
    {&gUefiInfoEmuSnpProtocolGuid,                                 "EMU_SNP_PROTOCOL"},
    {&gUefiInfoEmuSystemConfigGuid,                                "EMU_SYSTEM_CONFIG"},
    {&gUefiInfoEmuThreadThunkProtocolGuid,                         "EMU_THREAD_THUNK_PROTOCOL"},
    {&gUefiInfoEmuThunkPpiGuid,                                    "EMU_THUNK_PPI"},
    {&gUefiInfoEmuThunkProtocolGuid,                               "EMU_THUNK_PROTOCOL"},
    {&gUefiInfoEmuVirtualDisksGuid,                                "EMU_VIRTUAL_DISKS"},
    {&gUefiInfoEnhancedSpeedstepProtocolGuid,                      "ENHANCED_SPEEDSTEP_PROTOCOL"},
    {&gUefiInfoEventExitBootServicesFailedGuid,                    "EVENT_EXIT_BOOT_SERVICES_FAILED"},
    {&gUefiInfoExitPmAuthProtocolGuid,                             "EXIT_PM_AUTH_PROTOCOL"},
    {&gUefiInfoFdtTableGuid,                                       "FDT_TABLE"},
    {&gUefiInfoFileExploreFormSetGuid,                             "FILE_EXPLORE_FORM_SET"},
    {&gUefiInfoFirmwareIdGuid,                                     "FIRMWARE_ID"},
    {&gUefiInfoFirmwarePerformanceS3PointerGuid,                   "FIRMWARE_PERFORMANCE_S3_POINTER"},
    {&gUefiInfoFramerworkEfiFirmwareVolumeBlockProtocolGuid,       "FRAMERWORK_EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL"},
    {&gUefiInfoFrameworkBdsFrontPageFormsetGuid,                   "FRAMEWORK_BDS_FRONT_PAGE_FORMSET"},
    {&gUefiInfoFrameworkEfiMpServiceProtocolGuid,                  "FRAMEWORK_EFI_MP_SERVICE_PROTOCOL"},
    {&gUefiInfoFrontPageFormSetGuid,                               "FRONT_PAGE_FORM_SET"},
    {&gUefiInfoFspBootLoaderTemporaryMemoryGuid,                   "FSP_BOOT_LOADER_TEMPORARY_MEMORY"},
    {&gUefiInfoFspHeaderFileGuid,                                  "FSP_HEADER_FILE"},
    {&gUefiInfoFspInitDonePpiGuid,                                 "FSP_INIT_DONE_PPI"},
    {&gUefiInfoFspNonVolatileStorageHobGuid,                       "FSP_NON_VOLATILE_STORAGE_HOB"},
    {&gUefiInfoFspReservedMemoryResourceHobGfxGuid,                "FSP_RESERVED_MEMORY_RESOURCE_HOB_GFX"},
    {&gUefiInfoFspReservedMemoryResourceHobGuid,                   "FSP_RESERVED_MEMORY_RESOURCE_HOB"},
    {&gUefiInfoFspReservedMemoryResourceHobMiscGuid,               "FSP_RESERVED_MEMORY_RESOURCE_HOB_MISC"},
    {&gUefiInfoFspReservedMemoryResourceHobTsegGuid,               "FSP_RESERVED_MEMORY_RESOURCE_HOB_TSEG"},
    {&gUefiInfoFspWrapperTokenSpaceGuid,                           "FSP_WRAPPER_TOKEN_SPACE"},
    {&gUefiInfoGetPcdInfoPpiGuid,                                  "GET_PCD_INFO_PPI"},
    {&gUefiInfoGetPcdInfoProtocolGuid,                             "GET_PCD_INFO_PROTOCOL"},
    {&gUefiInfoHandleParsingHiiGuid,                               "HANDLE_PARSING_HII"},
    {&gUefiInfoHardwareInterruptProtocolGuid,                      "HARDWARE_INTERRUPT_PROTOCOL"},
    {&gUefiInfoHdBootDevicePathVariablGuid,                        "HD_BOOT_DEVICE_PATH_VARIABL"},
    {&gUefiInfoHiiResourceSamleFormSetGuid,                        "HII_RESOURCE_SAMLE_FORM_SET"},
    {&gUefiInfoIdccDataHubGuid,                                    "IDCC_DATA_HUB"},
    {&gUefiInfoIdleLoopEventGuid,                                  "IDLE_LOOP_EVENT"},
    {&gUefiInfoIgdOpRegionProtocolGuid,                            "IGD_OP_REGION_PROTOCOL"},
    {&gUefiInfoIntelFspPkgTokenSpaceGuid,                          "INTEL_FSP_PKG_TOKEN_SPACE"},
    {&gUefiInfoIp4IScsiConfigGuid,                                 "IP4_ISCSI_CONFIG"},
    {&gUefiInfoIp6ConfigNvDataGuid,                                "IP6_CONFIG_NV_DATA"},
    {&gUefiInfoIScsiCHAPAuthInfoGuid,                              "ISCSI_CHAPAUTH_INFO"},
    {&gUefiInfoIScsiConfigGuid,                                    "ISCSI_CONFIG"},
    {&gUefiInfoItkDataVarGuid,                                     "ITK_DATA_VAR"},
    {&gUefiInfoLastEnumLangGuid,                                   "LAST_ENUM_LANG"},
    {&gUefiInfoLdrMemoryDescriptorGuid,                            "LDR_MEMORY_DESCRIPTOR"},
    {&gUefiInfoLoadFixedAddressConfigurationTableGuid,             "LOAD_FIXED_ADDRESS_CONFIGURATION_TABLE"},
    {&gUefiInfoLpssDummyProtocolGuid,                              "LPSS_DUMMY_PROTOCOL"},
    {&gUefiInfoLzmaCustomDecompressGuid,                           "LZMA_CUSTOM_DECOMPRESS"},
    {&gUefiInfoLzmaF86CustomDecompressGuid,                        "LZMA_F86_CUSTOM_DECOMPRESS"},
    {&gUefiInfoMeasuredFvHobGuid,                                  "MEASURED_FV_HOB"},
    {&gUefiInfoMemInfoProtocolGuid,                                "MEM_INFO_PROTOCOL"},
    {&gUefiInfoMemoryStatusCodeRecordGuid,                         "MEMORY_STATUS_CODE_RECORD"},
    {&gUefiInfoMfgModeVariableGuid,                                "MFG_MODE_VARIABLE"},
    {&gUefiInfoMpsTableGuid,                                       "MPS_TABLE"},
    {&gUefiInfoMtcVendorGuid,                                      "MTC_VENDOR"},
    {&gUefiInfoNicIp4ConfigNvDataGuid,                             "NIC_IP4_CONFIG_NV_DATA"},
    {&gUefiInfoNtFwhPpiGuid,                                       "NT_FWH_PPI"},
    {&gUefiInfoNtPeiLoadFilePpiGuid,                               "NT_PEI_LOAD_FILE_PPI"},
    {&gUefiInfoObservableProtocolGuid,                             "OBSERVABLE_PROTOCOL"},
    {&gUefiInfoOmap35xxTokenSpaceGuid,                             "OMAP35XX_TOKEN_SPACE"},
    {&gUefiInfoOptionRomPkgTokenSpaceGuid,                         "OPTION_ROM_PKG_TOKEN_SPACE"},
    {&gUefiInfoOsSelectionVariableGuid,                            "OS_SELECTION_VARIABLE"},
    {&gUefiInfoOvmfPlatformConfigGuid,                             "OVMF_PLATFORM_CONFIG"},
    {&gUefiInfoPcAtChipsetPkgTokenSpaceGuid,                       "PC_AT_CHIPSET_PKG_TOKEN_SPACE"},
    {&gUefiInfoPcdDataBaseHobGuid,                                 "PCD_DATA_BASE_HOB"},
    {&gUefiInfoPcdDataBaseSignatureGuid,                           "PCD_DATA_BASE_SIGNATURE"},
    {&gUefiInfoPcdPpiGuid,                                         "PCD_PPI"},
    {&gUefiInfoPcdProtocolGuid,                                    "PCD_PROTOCOL"},
    {&gUefiInfoPchInitPpiGuid,                                     "PCH_INIT_PPI"},
    {&gUefiInfoPchInitVariableGuid,                                "PCH_INIT_VARIABLE"},
    {&gUefiInfoPchPeiInitPpiGuid,                                  "PCH_PEI_INIT_PPI"},
    {&gUefiInfoPchPlatformPolicyPpiGuid,                           "PCH_PLATFORM_POLICY_PPI"},
    {&gUefiInfoPchResetCallbackProtocolGuid,                       "PCH_RESET_CALLBACK_PROTOCOL"},
    {&gUefiInfoPchResetProtocolGuid,                               "PCH_RESET_PROTOCOL"},
    {&gUefiInfoPchUsbPolicyPpiGuid,                                "PCH_USB_POLICY_PPI"},
    {&gUefiInfoPdmWindowButtonGuid,                                "PDM_WINDOW_BUTTON"},
    {&gUefiInfoPdmWindowSpinGuid,                                  "PDM_WINDOW_SPIN"},
    {&gUefiInfoPeCoffLoaderProtocolGuid,                           "PE_COFF_LOADER_PROTOCOL"},
    {&gUefiInfoPeiAtaControllerPpiGuid,                            "PEI_ATA_CONTROLLER_PPI"},
    {&gUefiInfoPeiBlockIoPpiGuid,                                  "PEI_BLOCK_IO_PPI"},
    {&gUefiInfoPeiCachePpiGuid,                                    "PEI_CACHE_PPI"},
    {&gUefiInfoPeiCapsuleOnDataCdGuid,                             "PEI_CAPSULE_ON_DATA_CD"},
    {&gUefiInfoPeiCapsuleOnFatFloppyDiskGuid,                      "PEI_CAPSULE_ON_FAT_FLOPPY_DISK"},
    {&gUefiInfoPeiCapsuleOnFatIdeDiskGuid,                         "PEI_CAPSULE_ON_FAT_IDE_DISK"},
    {&gUefiInfoPeiCapsuleOnFatUsbDiskGuid,                         "PEI_CAPSULE_ON_FAT_USB_DISK"},
    {&gUefiInfoPeiCapsulePpiGuid,                                  "PEI_CAPSULE_PPI"},
    {&gUefiInfoPeiDebugDispatchPpiGuid,                            "PEI_DEBUG_DISPATCH_PPI"},
    {&gUefiInfoPeiHeciPpiGuid,                                     "PEI_HECI_PPI"},
    {&gUefiInfoPeiLockPhysicalPresencePpiGuid,                     "PEI_LOCK_PHYSICAL_PRESENCE_PPI"},
    {&gUefiInfoPeiMfgMemoryTestPpiGuid,                            "PEI_MFG_MEMORY_TEST_PPI"},
    {&gUefiInfoPeiNtAutoScanPpiGuid,                               "PEI_NT_AUTO_SCAN_PPI"},
    {&gUefiInfoPeiNtThunkPpiGuid,                                  "PEI_NT_THUNK_PPI"},
    {&gUefiInfoPeiPostBootScriptTablePpiGuid,                      "PEI_POST_BOOT_SCRIPT_TABLE_PPI"},
    {&gUefiInfoPeiPostScriptTablePpiGuid,                          "PEI_POST_SCRIPT_TABLE_PPI"},
    {&gUefiInfoPeiSdhcPpiGuid,                                     "PEI_SDHC_PPI"},
    {&gUefiInfoPeiSecPerformancePpiGuid,                           "PEI_SEC_PERFORMANCE_PPI"},
    {&gUefiInfoPeiSeCPlatformPolicyPpiGuid,                        "PEI_SE_CPLATFORM_POLICY_PPI"},
    {&gUefiInfoPeiSerialPortPpiGuid,                               "PEI_SERIAL_PORT_PPI"},
    {&gUefiInfoPeiSha256HashPpiGuid,                               "PEI_SHA256_HASH_PPI"},
    {&gUefiInfoPeiSmbusPolicyPpiGuid,                              "PEI_SMBUS_POLICY_PPI"},
    {&gUefiInfoPeiSmmAccessPpiGuid,                                "PEI_SMM_ACCESS_PPI"},
    {&gUefiInfoPeiSmmControlPpiGuid,                               "PEI_SMM_CONTROL_PPI"},
    {&gUefiInfoPeiSpeakerInterfacePpiGuid,                         "PEI_SPEAKER_INTERFACE_PPI"},
    {&gUefiInfoPeiSpiPpiGuid,                                      "PEI_SPI_PPI"},
    {&gUefiInfoPeiTpmInitializationDonePpiGuid,                    "PEI_TPM_INITIALIZATION_DONE_PPI"},
    {&gUefiInfoPeiTpmInitializedPpiGuid,                           "PEI_TPM_INITIALIZED_PPI"},
    {&gUefiInfoPeiUsb2HostControllerPpiGuid,                       "PEI_USB2_HOST_CONTROLLER_PPI"},
    {&gUefiInfoPeiUsbControllerPpiGuid,                            "PEI_USB_CONTROLLER_PPI"},
    {&gUefiInfoPeiUsbHostControllerPpiGuid,                        "PEI_USB_HOST_CONTROLLER_PPI"},
    {&gUefiInfoPeiUsbIoPpiGuid,                                    "PEI_USB_IO_PPI"},
    {&gUefiInfoPerformanceExProtocolGuid,                          "PERFORMANCE_EX_PROTOCOL"},
    {&gUefiInfoPerformancePkgTokenSpaceGuid,                       "PERFORMANCE_PKG_TOKEN_SPACE"},
    {&gUefiInfoPerformanceProtocolGuid,                            "PERFORMANCE_PROTOCOL"},
    {&gUefiInfoPhoenixDesktopMessageProtocolGuid,                  "PHOENIX_DESKTOP_MESSAGE_PROTOCOL"},
    {&gUefiInfoPhoenixDesktopWindowProtocolGuid,                   "PHOENIX_DESKTOP_WINDOW_PROTOCOL"},
    {&gUefiInfoPhoenixEfiSmmSwSmiProtocolGuid,                     "PHOENIX_EFI_SMM_SW_SMI_PROTOCOL"},
    {&gUefiInfoPhoenixGdiProtocolGuid,                             "PHOENIX_GDI_PROTOCOL"},
    {&gUefiInfoPhoenixSmmCoreServicesProtocolGuid,                 "PHOENIX_SMM_CORE_SERVICES_PROTOCOL"},
    {&gUefiInfoPhoenixSmmWatchdogTimerProtocolGuid,                "PHOENIX_SMM_WATCHDOG_TIMER_PROTOCOL"},
    {&gUefiInfoPlatformGOPPolicyGuid,                              "PLATFORM_GOPPOLICY"},
    {&gUefiInfoPlatformModuleTokenSpaceGuid,                       "PLATFORM_MODULE_TOKEN_SPACE"},
    {&gUefiInfoPlatformOverridesManagerGuid,                       "PLATFORM_OVERRIDES_MANAGER"},
    {&gUefiInfoPlatformSeCHookProtocolGuid,                        "PLATFORM_SE_CHOOK_PROTOCOL"},
    {&gUefiInfoPowerManagementAcpiTableStorageGuid,                "POWER_MANAGEMENT_ACPI_TABLE_STORAGE"},
    {&gUefiInfoPpmPlatformPolicyProtocolGuid,                      "PPM_PLATFORM_POLICY_PROTOCOL"},
    {&gUefiInfoProcessorProducerGuid,                              "PROCESSOR_PRODUCER"},
    {&gUefiInfoPwdCredentialProviderGuid,                          "PWD_CREDENTIAL_PROVIDER"},
    {&gUefiInfoRecoveryOnDataCdGuid,                               "RECOVERY_ON_DATA_CD"},
    {&gUefiInfoRecoveryOnFatFloppyDiskGuid,                        "RECOVERY_ON_FAT_FLOPPY_DISK"},
    {&gUefiInfoRecoveryOnFatIdeDiskGuid,                           "RECOVERY_ON_FAT_IDE_DISK"},
    {&gUefiInfoRecoveryOnFatUsbDiskGuid,                           "RECOVERY_ON_FAT_USB_DISK"},
    {&gUefiInfoSalSystemTableGuid,                                 "SAL_SYSTEM_TABLE"},
    {&gUefiInfoSataControllerDriverGuid,                           "SATA_CONTROLLER_DRIVER"},
    {&gUefiInfoSctIsaHcPpiGuid,                                    "SCT_ISA_HC_PPI"},
    {&gUefiInfoSctIsaHcProtocolGuid,                               "SCT_ISA_HC_PROTOCOL"},
    {&gUefiInfoSeCfTPMPolicyPpiGuid,                               "SE_CF_TPMPOLICY_PPI"},
    {&gUefiInfoSeCfTPMPpiGuid,                                     "SE_CF_TPMPPI"},
    {&gUefiInfoSeCPlatformReadyToBootGuid,                         "SE_CPLATFORM_READY_TO_BOOT"},
    {&gUefiInfoSeCUmaPpiGuid,                                      "SE_CUMA_PPI"},
    {&gUefiInfoSecureBootConfigFormSetGuid,                        "SECURE_BOOT_CONFIG_FORM_SET"},
    {&gUefiInfoShellAliasGuid,                                     "SHELL_ALIAS"},
    {&gUefiInfoShellBcfgHiiGuid,                                   "SHELL_BCFG_HII"},
    {&gUefiInfoShellDebug1HiiGuid,                                 "SHELL_DEBUG1_HII"},
    {&gUefiInfoShellDriver1HiiGuid,                                "SHELL_DRIVER1_HII"},
    {&gUefiInfoShellInstall1HiiGuid,                               "SHELL_INSTALL1_HII"},
    {&gUefiInfoShellLevel1HiiGuid,                                 "SHELL_LEVEL1_HII"},
    {&gUefiInfoShellLevel2HiiGuid,                                 "SHELL_LEVEL2_HII"},
    {&gUefiInfoShellLevel3HiiGuid,                                 "SHELL_LEVEL3_HII"},
    {&gUefiInfoShellMapGuid,                                       "SHELL_MAP"},
    {&gUefiInfoShellNetwork1HiiGuid,                               "SHELL_NETWORK1_HII"},
    {&gUefiInfoShellVariableGuid,                                  "SHELL_VARIABLE"},
    {&gUefiInfoSmmCommunicateHeaderGuid,                           "SMM_COMMUNICATE_HEADER"},
    {&gUefiInfoSmmPerformanceExProtocolGuid,                       "SMM_PERFORMANCE_EX_PROTOCOL"},
    {&gUefiInfoSmmPerformanceProtocolGuid,                         "SMM_PERFORMANCE_PROTOCOL"},
    {&gUefiInfoSmmVariableWriteGuid,                               "SMM_VARIABLE_WRITE"},
    {&gUefiInfoStatusCodeCallbackGuid,                             "STATUS_CODE_CALLBACK"},
    {&gUefiInfoStdLibTokenSpaceGuid,                               "STD_LIB_TOKEN_SPACE"},
    {&gUefiInfoTcgConfigFormSetGuid,                               "TCG_CONFIG_FORM_SET"},
    {&gUefiInfoTcgEventEntryHobGuid,                               "TCG_EVENT_ENTRY_HOB"},
    {&gUefiInfoTianoCustomDecompressGuid,                          "TIANO_CUSTOM_DECOMPRESS"},
    {&gUefiInfoTopOfTemporaryRamPpiGuid,                           "TOP_OF_TEMPORARY_RAM_PPI"},
    {&gUefiInfoTpmErrorHobGuid,                                    "TPM_ERROR_HOB"},
    {&gUefiInfoTrEEConfigFormSetGuid,                              "TR_EECONFIG_FORM_SET"},
    {&gUefiInfoUefiCpuPkgTokenSpaceGuid,                           "UEFI_CPU_PKG_TOKEN_SPACE"},
    {&gUefiInfoUefiOvmfPkgTokenSpaceGuid,                          "UEFI_OVMF_PKG_TOKEN_SPACE"},
    {&gUefiInfoUsbCredentialProviderGuid,                          "USB_CREDENTIAL_PROVIDER"},
    {&gUefiInfoUsbDeviceProtocolGuid,                              "USB_DEVICE_PROTOCOL"},
    {&gUefiInfoUsbKeyboardLayoutKeyGuid,                           "USB_KEYBOARD_LAYOUT_KEY"},
    {&gUefiInfoUsbKeyboardLayoutPackageGuid,                       "USB_KEYBOARD_LAYOUT_PACKAGE"},
    {&gUefiInfoUsbPolicyGuid,                                      "USB_POLICY"},
    {&gUefiInfoUserIdentifyManagerGuid,                            "USER_IDENTIFY_MANAGER"},
    {&gUefiInfoUserProfileManagerGuid,                             "USER_PROFILE_MANAGER"},
    {&gUefiInfoVirtioDeviceProtocolGuid,                           "VIRTIO_DEVICE_PROTOCOL"},
    {&gUefiInfoVirtioMmioTransportGuid,                            "VIRTIO_MMIO_TRANSPORT"},
    {&gUefiInfoVirtualUncachedPagesProtocolGuid,                   "VIRTUAL_UNCACHED_PAGES_PROTOCOL"},
    {&gUefiInfoVlanConfigFormSetGuid,                              "VLAN_CONFIG_FORM_SET"},
    {&gUefiInfoVlvMmioPolicyPpiGuid,                               "VLV_MMIO_POLICY_PPI"},
    {&gUefiInfoVlvPeiInitPpiGuid,                                  "VLV_PEI_INIT_PPI"},
    {&gUefiInfoVlvPolicyPpiGuid,                                   "VLV_POLICY_PPI"},
    {&gUefiInfoVlvRefCodePkgTokenSpaceGuid,                        "VLV_REF_CODE_PKG_TOKEN_SPACE"},
    {&gUefiInfoWinNtBusDriverGuid,                                 "WIN_NT_BUS_DRIVER"},
    {&gUefiInfoXenBusProtocolGuid,                                 "XEN_BUS_PROTOCOL"},
    {&gUefiInfoZeroGuid,                                           "ZERO"},


    {&gUefiInfoScsiBusDxeGuid, "ScsiBusDxe"},
    {&gUefiInfoRamDiskDxeGuid, "RamDiskDxe"},
    {&gUefiInfoEdkiiPlatformSpecificResetHandlerProtocolGuidGuid, "EDKII_PLATFORM_SPECIFIC_RESET_HANDLER_PROTOCOL"},
    {&gUefiInfoHiiDatabaseDxeGuid, "HiiDatabaseDxe"},
    {&gUefiInfoEdkiiBootLogo2ProtocolGuidGuid, "EDKII_BOOT_LOGO2_PROTOCOL"},
    {&gUefiInfoEdkiiPlatformSpecificResetFilterProtocolGuidGuid, "EDKII_PLATFORM_SPECIFIC_RESET_FILTER_PROTOCOL"},
    {&gUefiInfoUefiPxeBcDxeGuid, "UefiPxeBcDxe"},
    {&gUefiInfoFirmwarePerformanceDxeGuid, "FirmwarePerformanceDxe"},
    {&gUefiInfoMnpDxeGuid, "MnpDxe"},
    {&gUefiInfoScsiDiskDxeGuid, "ScsiDiskDxe"},
    {&gUefiInfoCpuDxeGuid, "CpuDxe"},
    {&gUefiInfoTcpDxeGuid, "TcpDxe"},
    {&gUefiInfoPartitionDxeGuid, "PartitionDxe"},
    {&gUefiInfoHttpUtilitiesDxeGuid, "HttpUtilitiesDxe"},
    {&gUefiInfoHttpDxeGuid, "HttpDxe"},
    {&gUefiInfoPcRtcDxeGuid, "PcRtcDxe"},
    {&gUefiInfoTlsDxeGuid, "TlsDxe"},
    {&gUefiInfoConSplitterDxeGuid, "ConSplitterDxe"},
    {&gUefiInfoCapsuleRuntimeDxeGuid, "CapsuleRuntimeDxe"},
    {&gUefiInfoResetSystemRuntimeDxeGuid, "ResetSystemRuntimeDxe"},
    {&gUefiInfoConPlatformDxeGuid, "ConPlatformDxe"},
    {&gUefiInfoArpDxeGuid, "ArpDxe"},
    {&gUefiInfoNvmExpressDxeGuid, "NvmExpressDxe"},
    {&gUefiInfoIp6DxeGuid, "Ip6Dxe"},
    {&gUefiInfoHash2DxeCryptoGuid, "Hash2DxeCrypto"},
    {&gUefiInfoDiskIoDxeGuid, "DiskIoDxe"},
    {&gUefiInfoBdsDxeGuid, "BdsDxe"},
    {&gUefiInfoUdp4DxeGuid, "Udp4Dxe"},
    {&gUefiInfoPcdDxeGuid, "PcdDxe"},
    {&gUefiInfoDhcp4DxeGuid, "Dhcp4Dxe"},
    {&gUefiInfoDhcp6DxeGuid, "Dhcp6Dxe"},
    {&gUefiInfoFatDxeGuid, "FatDxe"},
    {&gUefiInfoAcpiTableDxeGuid, "AcpiTableDxe"},
    {&gUefiInfoNullMemoryTestDxeGuid, "NullMemoryTestDxe"},
    {&gUefiInfoMtftp6DxeGuid, "Mtftp6Dxe"},
    {&gUefiInfoDevicePathDxeGuid, "DevicePathDxe"},
    {&gUefiInfoTerminalDxeGuid, "TerminalDxe"},
    {&gUefiInfoIp4DxeGuid, "Ip4Dxe"},
    {&gUefiInfoDpcDxeGuid, "DpcDxe"},
    {&gUefiInfoMonotonicCounterRuntimeDxeGuid, "MonotonicCounterRuntimeDxe"},
    {&gUefiInfoDnsDxeGuid, "DnsDxe"},
    {&gUefiInfoRuntimeDxeGuid, "RuntimeDxe"},
    {&gUefiInfoBootGraphicsResourceTableDxeGuid, "BootGraphicsResourceTableDxe"},
    {&gUefiInfoRngDxeGuid, "RngDxe"},
    {&gUefiInfoMetronomeGuid, "Metronome"},
    {&gUefiInfoAcpiPlatformGuid, "AcpiPlatform"},
    {&gUefiInfoVariableRuntimeDxeGuid, "VariableRuntimeDxe"},
    {&gUefiInfoGraphicsConsoleDxeGuid, "GraphicsConsoleDxe"},
    {&gUefiInfoEnglishDxeGuid, "EnglishDxe"},
    {&gUefiInfoDxeCoreGuid, "DxeCore"},
    {&gUefiInfoUdp6DxeGuid, "Udp6Dxe"},
    {&gUefiInfoReportStatusCodeRouterRuntimeDxeGuid, "ReportStatusCodeRouterRuntimeDxe"},
    {&gUefiInfoMtftp4DxeGuid, "Mtftp4Dxe"},
    {&gUefiInfoSetupBrowserGuid, "SetupBrowser"},
    {&gUefiInfoSecurityStubDxeGuid, "SecurityStubDxe"},
    {&gUefiInfoSmbiosDxeGuid, "SmbiosDxe"},
    {&gUefiInfoSmbiosPlatformGuid, "SmbiosPlatform"},
    {&gUefiInfoVideoDxeGuid, "VideoDxe"},
    {&gUefiInfoSerialDxeGuid, "SerialDxe"},
    {&gUefiInfoEventLogDxeGuid, "EventLogDxe"},
    {&gUefiInfoSynicTimerDxeGuid, "SynicTimerDxe"},
    {&gUefiInfoEmclDxeGuid, "EmclDxe"},
    {&gUefiInfoConNullDxeGuid, "ConNullDxe"},
    {&gUefiInfoStorvscDxeGuid, "StorvscDxe"},
    {&gUefiInfoSynthKeyDxeGuid, "SynthKeyDxe"},
    {&gUefiInfoVmbusDxeGuid, "VmbusDxe"},
    {&gUefiInfoVmbfsDxeGuid, "VmbfsDxe"},
    {&gUefiInfoWatchdogTimerGuid, "WatchdogTimer"},
    {&gUefiInfoEfiHvDxeGuid, "EfiHvDxe"},
    {&gUefiInfoNetvscDxeGuid, "NetvscDxe"},

    {&gUefiInfoEfiDxeServicesTable, "DXE_SERVICES_TABLE"},
    {&gUefiInfoEfiEdkiiPiSmmCommunicationRegionTable, "EDKII_PI_SMM_COMMUNICATION_REGION_TABLE"},
    {&gUefiInfoEfiEdkiiPiSmmMemoryAttributesTable, "EDKII_PI_SMM_MEMORY_ATTRIBUTES_TABLE"},
    {&gUefiInfoEfiEfiCcFinalEventsTable, "EFI_CC_FINAL_EVENTS_TABLE"},
    {&gUefiInfoEfiEfiRtPropertiesTable, "EFI_RT_PROPERTIES_TABLE"},
    {&gUefiInfoEfiEfiTcg2FinalEventsTable, "EFI_TCG2_FINAL_EVENTS_TABLE"},
    {&gUefiInfoEfiEfiConformanceProfilesTable, "EFI_CONFORMANCE_PROFILES_TABLE"},
    {NULL, NULL},
};

// clang-format on

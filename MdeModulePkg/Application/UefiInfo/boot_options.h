#ifndef _BOOT_OPTIONS_H_
#define _BOOT_OPTIONS_H_

typedef struct {
    UINT8 uIndex;
    UINT8 dwAttributes[4];
    UINT8 wBootOption[2];
    UINT8 wDescriptionOffset[2];
    UINT8 wDevicePathOffset[2];
    UINT8 wCommandLineOffset[2];
    UINT8 wSize[2];
} sUEFI_BOOT_OPTION;

// Global UEFI variables
#define VAR_BOOT_CURRENT L"BootCurrent"
#define VAR_BOOT_NEXT    L"BootNext"
#define VAR_BOOT_ORDER   L"BootOrder"

#define LOAD_OPTION_ACTIVE          0x00000001
#define LOAD_OPTION_FORCE_RECONNECT 0x00000002
#define LOAD_OPTION_HIDDEN          0x00000008
#define LOAD_OPTION_CATEGORY        0x00001F00

#define LOAD_OPTION_CATEGORY_BOOT 0x00000000
#define LOAD_OPTION_CATEGORY_APP  0x00000100

EFI_STATUS EFIAPI BootOptionsEnumerateAll(_Inout_opt_ sUEFI_BOOT_OPTION* pBootOptionsBuffer,
                                          IN OUT UINT32* pdwBootOptionsBufferLength,
                                          OUT UINT32* pdwNumOptions);
EFI_STATUS EFIAPI BootOptionsSetOneTimeBootSequence(IN UINT16 wBootOption);
EFI_STATUS EFIAPI BootOptionsSetFirst(IN UINT16 wBootOption);
EFI_STATUS EFIAPI BootOptionsSetLast(IN UINT16 wBootOption);
EFI_STATUS EFIAPI BootOptionsGetCurrent(OUT UINT16* pwCurrentBootOption);
EFI_STATUS EFIAPI BootOptionsSetBootEntryOptionalData(IN UINT16 wBootOption,
                                                      _In_opt_z_ CHAR16* pCommandLine);
#endif // _BOOT_OPTIONS_H_

//
// Global includes
//
#include "common.h"

#include "strsafe.h"

//
// Local includes
//
#include "boot_options.h"
#include "endiannesshelper.h"

//
// Constants/Macros
//

//
// Structs
//

//
// Variables
//

//
// Prototypes
//
static EFI_STATUS EFIAPI EnumerateBootOptionsInternal(IN OUT sUEFI_BOOT_OPTION* BootOptionsBuffer,
                                                      OUT UINT32* BootOptionsBufferLength,
                                                      OUT UINT32* NumOptions);

//
// Interfaces
//
EFI_STATUS EFIAPI BootOptionsEnumerateAll(IN OUT sUEFI_BOOT_OPTION* BootOptionsBuffer,
                                          IN OUT UINT32* BootOptionsBufferLength,
                                          OUT UINT32* NumOptions)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    UINT32 BufferLength = 0;
    UINT32 RetNumOptions = 0;

    // Pre-calculate necessary size for BootOptionsBuffer
    EfiStatus = EnumerateBootOptionsInternal(NULL, &BufferLength, &RetNumOptions);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain boot options buffer length, 0x%x", EfiStatus);
        goto Exit;
    }

    if (*BootOptionsBufferLength < BufferLength) {
        DBG_ERROR(
            "Buffer length too small. Actual: %u, required: %u. Please call function with correct buffer length",
            *BootOptionsBufferLength,
            BufferLength);
        EfiStatus = EFI_BUFFER_TOO_SMALL;

        *BootOptionsBufferLength = BufferLength;
        goto Exit;
    }

    BufferLength = *BootOptionsBufferLength;

    // Actually fill in BootOptionsBuffer
    EfiStatus = EnumerateBootOptionsInternal(BootOptionsBuffer, &BufferLength, &RetNumOptions);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain boot options, 0x%x", EfiStatus);
        goto Exit;
    }

    *BootOptionsBufferLength = BufferLength;
    *NumOptions = RetNumOptions;

Exit:
    return EfiStatus;
}

EFI_STATUS EFIAPI EFIAPI BootOptionsSetOneTimeBootSequence(IN UINT16 BootOption)
{
    return gRT->SetVariable(VAR_BOOT_NEXT,
                            &gEfiGlobalVariableGuid,
                            EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                EFI_VARIABLE_RUNTIME_ACCESS,
                            sizeof(UINT16),
                            &BootOption);
}

EFI_STATUS EFIAPI BootOptionsSetBootEntryOptionalData(IN UINT16 BootOption, IN CHAR16* CommandLine)
/*++

Routine Description:

    This routine updates the optional data field for a chosen boot entry
    (EFI_LOAD_OPTION) to provide command line arguments capability for efi apps
    baked in to UEFI BIOS.

    Refer UEFI Spec Version 2.8 Section 3.1.3 "Load Options" for more details.
    Idea:
        From: %SDXROOT%\minkernel\boot\environ\lib\firmware\efi\efiinit.c

        An EFI Application could have been loaded from the EFI Shell or loaded
        by the EFI Boot Manager. The meaning and value of LoadOptions depends on
        this load technique. When loaded from the EFI Boot Manager, LoadOptions
        is a pointer to the OptionalData[] of the NVRAM EFI_LOAD_OPTION.  When
        loaded from the Shell, this consists of the command line arguments.

    We are already making use of LoadOptions in cmdparse.c as shown below to get
    the command line for side loaded apps ran through UEFI Shell.

    gBS->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, &LoadedImage);
    CommandLine = LoadedImage->LoadOptions;

Arguments:

    BootOption - Boot entry number

    CommandLine - Null terminated string data containing the command line. If
                    empty the existing optional data field will be removed. In
                    other words, existing command line will be removed

Return Value:

    EFI_STATUS. Return EFI_SUCCESS when no error is encountered or
    EFI_* otherwise.

--*/
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    EFI_LOAD_OPTION* BootOptionPtr = NULL;
    UINT8* NewBootOption = NULL;
    const CHAR16 BootXXXXFmt[] = L"BootXXXX";
    CHAR16 BootXXXX[_countof(BootXXXXFmt)] = {0};
    UINTN NewBootOptionSize = 0;
    UINTN CommandLineLength = 0;
    CHAR16* EfiDescription = NULL;
    UINTN EfiCommandLineOffset = 0;
    UINTN EfiDescriptionSize = 0;
    UINTN BootOptionSize = 0;
    CHAR16 CommandLineTemp[1024] = {0};

    DBG_INFO("Boot option %u", BootOption);

    UnicodeSPrint(BootXXXX, sizeof(BootXXXX), L"Boot%04X", BootOption);
    EfiStatus = gRT->GetVariable(BootXXXX, &gEfiGlobalVariableGuid, NULL, &BootOptionSize, NULL);
    if (EfiStatus == EFI_BUFFER_TOO_SMALL) {
        // This is good. It means the variable exists
        EfiStatus = EFI_SUCCESS;
    }

    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain variable size for variable %S, 0x%x", BootXXXX, EfiStatus);
        goto Exit;
    }

    BootOptionPtr = AllocateZeroPool(BootOptionSize);
    if (BootOptionPtr == NULL) {
        DBG_ERROR("Unable to allocate pool for boot option");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    EfiStatus = gRT->GetVariable(BootXXXX,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOptionSize,
                                 BootOptionPtr);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain %S value, 0x%x", BootXXXX, EfiStatus);
        goto Exit;
    }

    //
    // Append command line as Optional Data to EFI Load Option
    //

    if (CommandLine != NULL) {
        CommandLineLength = (StrLen(CommandLine) + 1) * sizeof(CHAR16);
    }

    UINTN DescriptionFieldOffset = sizeof(UINT32) + sizeof(UINT16);
    EfiDescription = (CHAR16*)(((UINT8*)BootOptionPtr) + DescriptionFieldOffset);
    EfiDescriptionSize = (UINT16)(StrLen(EfiDescription) + 1) * sizeof(CHAR16);
    EfiCommandLineOffset = DescriptionFieldOffset + EfiDescriptionSize +
                           BootOptionPtr->FilePathListLength;

    NewBootOptionSize = EfiCommandLineOffset + CommandLineLength;

    NewBootOption = AllocateZeroPool(NewBootOptionSize);
    if (NewBootOption == NULL) {
        DBG_ERROR("Unable to allocate pool for new boot option");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Copy existing EFI_LOAD_OPTION fields excluding Optional Data
    //

    CopyMem(NewBootOption, BootOptionPtr, EfiCommandLineOffset);

    //
    // Append Command line as Optional Data
    //

    if (CommandLine != NULL) {
        CopyMem((UINT8*)NewBootOption + EfiCommandLineOffset, CommandLineTemp, CommandLineLength);
    }

    //
    // Save it back to BootXXXX entry
    //

    EfiStatus = gRT->SetVariable(BootXXXX,
                                 &gEfiGlobalVariableGuid,
                                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                     EFI_VARIABLE_RUNTIME_ACCESS,
                                 NewBootOptionSize,
                                 NewBootOption);

Exit:
    FreePool(BootOptionPtr);
    FreePool(NewBootOption);
    return EfiStatus;
}

EFI_STATUS EFIAPI BootOptionsSetFirst(IN UINT16 BootOption)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    UINTN BootOrderSize = 0;
    UINT16* BootOrder = NULL;
    UINT32 NumOptions = 0;

    // Get the BootOrder list.
    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 NULL);
    if (EfiStatus == EFI_BUFFER_TOO_SMALL) {
        // This is good. It means the variable exists
        EfiStatus = EFI_SUCCESS;
    }

    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain variable size for BootOrder variable, 0x%x", EfiStatus);
        goto Exit;
    }

    // Calculate number of options.
    NumOptions = ((UINT32)BootOrderSize) / sizeof(UINT16);
    BootOrder = AllocateZeroPool(BootOrderSize);
    if (BootOrder == NULL) {
        DBG_ERROR("Unable to allocate pool for BootOrder variable");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 BootOrder);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain BootOrder variable value, 0x%x", EfiStatus);
        goto Exit;
    }

    // Check if BootOption in BootOrder list. If not, fail out.
    EfiStatus = EFI_NOT_FOUND;
    UINT32 BootOptionIndex = 0;
    for (UINT32 i = 0; i < NumOptions; i++) {
        if (BootOrder[i] == BootOption) {
            EfiStatus = EFI_SUCCESS;
            BootOptionIndex = i;
            break;
        }
    }

    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Did not find Boot%04X option", BootOption);
        goto Exit;
    }

    UINT32 CurrentIndex = BootOptionIndex;

    // Bubble up desired option to the front of the list, maintaining order of other options.
    while (CurrentIndex > 0) {
        UINT16 Temp = BootOrder[CurrentIndex];
        BootOrder[CurrentIndex] = BootOrder[CurrentIndex - 1];
        BootOrder[CurrentIndex - 1] = Temp;
        CurrentIndex--;
    }

    // Set updated BootOrder list.
    EfiStatus = gRT->SetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                     EFI_VARIABLE_RUNTIME_ACCESS,
                                 BootOrderSize,
                                 BootOrder);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to set BootOrder value, 0x%x", EfiStatus);
        goto Exit;
    }

Exit:
    FreePool(BootOrder);

    return EfiStatus;
}

EFI_STATUS EFIAPI BootOptionsSetLast(IN UINT16 BootOption)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    UINTN BootOrderSize = 0;
    UINT16* BootOrder = NULL;
    UINT32 NumOptions = 0;

    // Get the BootOrder list.
    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 NULL);
    if (EfiStatus == EFI_BUFFER_TOO_SMALL) {
        // This is good. It means the variable exists
        EfiStatus = EFI_SUCCESS;
    }
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain variable size for BootOrder variable, 0x%x", EfiStatus);
        goto Exit;
    }

    // Calculate number of options.
    NumOptions = ((UINT32)BootOrderSize) / sizeof(UINT16);
    BootOrder = AllocateZeroPool(BootOrderSize);
    if (BootOrder == NULL) {
        DBG_ERROR("Unable to allocate pool for BootOrder variable");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 BootOrder);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain BootOrder variable value, 0x%x", EfiStatus);
        goto Exit;
    }

    // Check if BootOption in BootOrder list. If not, fail out.
    EfiStatus = EFI_NOT_FOUND;
    UINT32 BootOptionIndex = 0;
    for (UINT32 i = 0; i < NumOptions; i++) {
        if (BootOrder[i] == BootOption) {
            EfiStatus = EFI_SUCCESS;
            BootOptionIndex = i;
            break;
        }
    }

    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Did not find Boot%04X option", BootOption);
        goto Exit;
    }

    // Bubble desired option to the back of the list, maintaining order of other options.
    UINT32 FinalIndex = NumOptions - 1;
    for (UINT32 CurrentIndex = BootOptionIndex; CurrentIndex < FinalIndex; CurrentIndex++) {
        UINT16 Temp = BootOrder[CurrentIndex];
        BootOrder[CurrentIndex] = BootOrder[CurrentIndex + 1];
        BootOrder[CurrentIndex + 1] = Temp;
    }

    // Set updated BootOrder list.
    EfiStatus = gRT->SetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                                     EFI_VARIABLE_RUNTIME_ACCESS,
                                 BootOrderSize,
                                 BootOrder);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to set BootOrder value, 0x%x", EfiStatus);
        goto Exit;
    }

Exit:
    FreePool(BootOrder);

    return EfiStatus;
}

EFI_STATUS EFIAPI BootOptionsGetCurrent(OUT UINT16* CurrentBootOption)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    UINT16 RetCurrentBootOption = 0;
    UINTN VariableSize = sizeof(UINT16);

    EfiStatus = gRT->GetVariable(VAR_BOOT_CURRENT,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &VariableSize,
                                 &RetCurrentBootOption);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Unable to retrieve BootCurrent variable, 0x%x", EfiStatus);
        goto Exit;
    }

    *CurrentBootOption = RetCurrentBootOption;

Exit:
    return EfiStatus;
}

//
// Local functions
//

static EFI_STATUS EFIAPI EnumerateBootOptionsInternal(IN OUT sUEFI_BOOT_OPTION* BootOptionsBuffer,
                                                      OUT UINT32* BootOptionsBufferLength,
                                                      OUT UINT32* NumOptions)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* DevicePathToTextIf = NULL;
    UINTN BootOrderSize = 0;
    UINTN BootOptionSize = 0;
    UINT32 RetNumOptions = 0;
    UINT32 Offset = 0;
    UINT16* BootOrder = NULL;
    EFI_LOAD_OPTION* BootOption = NULL;
    sUEFI_BOOT_OPTION* BufferOffset = NULL;
    const CHAR16 BootXXXXFmt[] = L"BootXXXX";
    CHAR16 BootXXXX[_countof(BootXXXXFmt)] = {0};
    UINT16* EfiCommandLine = NULL;
    UINT16 EfiDescriptionSize = 0;
    UINT16 EfiDevicePathSize = 0;
    UINT16 EfiCommandLineSize = 0;
    UINT16 DescriptionOffset = 0;
    UINT16 DevicePathOffset = 0;
    UINT16 CommandLineOffset = 0;

    EfiStatus = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid,
                                    NULL,
                                    (VOID**)&DevicePathToTextIf);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to locate device path to text protocol, 0x%x", EfiStatus);
        goto Exit;
    }

    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 NULL);
    if (EfiStatus == EFI_BUFFER_TOO_SMALL) {
        // This is good. It means the variable exists
        EfiStatus = EFI_SUCCESS;
    }
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain variable size for BootOrder variable, 0x%x", EfiStatus);
        goto Exit;
    }

    RetNumOptions = ((UINT32)BootOrderSize) / sizeof(UINT16);

    BootOrder = AllocateZeroPool(BootOrderSize);
    if (BootOrder == NULL) {
        DBG_ERROR("Unable to allocate pool for BootOrder variable");
        EfiStatus = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    EfiStatus = gRT->GetVariable(VAR_BOOT_ORDER,
                                 &gEfiGlobalVariableGuid,
                                 NULL,
                                 &BootOrderSize,
                                 BootOrder);
    if (EFI_ERROR(EfiStatus)) {
        DBG_ERROR("Failed to obtain BootOrder variable value, 0x%x", EfiStatus);
        goto Exit;
    }

    for (UINT8 i = 0; i < RetNumOptions; i++) {
        UINT16 Option = BootOrder[i];
        EfiCommandLine = NULL;
        EfiDescriptionSize = 0;
        EfiDevicePathSize = 0;
        EfiCommandLineSize = 0;
        DescriptionOffset = 0;
        DevicePathOffset = 0;
        CommandLineOffset = 0;

        DBG_INFO("Boot option %u", Option);

        UnicodeSPrint(BootXXXX, sizeof(BootXXXX), L"Boot%04X", Option);

        EfiStatus = gRT->GetVariable(BootXXXX,
                                     &gEfiGlobalVariableGuid,
                                     NULL,
                                     &BootOptionSize,
                                     NULL);
        if (EfiStatus == EFI_BUFFER_TOO_SMALL) {
            // This is good. It means the variable exists
            EfiStatus = EFI_SUCCESS;
        }

        if (EFI_ERROR(EfiStatus)) {
            DBG_ERROR("Failed to obtain variable size for variable %S, 0x%x", BootXXXX, EfiStatus);
            break;
        }

        BootOption = AllocateZeroPool(BootOptionSize);
        if (BootOption == NULL) {
            DBG_ERROR("Unable to allocate pool for boot option");
            EfiStatus = EFI_OUT_OF_RESOURCES;
            break;
        }

        EfiStatus = gRT->GetVariable(BootXXXX,
                                     &gEfiGlobalVariableGuid,
                                     NULL,
                                     &BootOptionSize,
                                     BootOption);
        if (EFI_ERROR(EfiStatus)) {
            DBG_ERROR("Failed to obtain %S value, 0x%x", BootXXXX, EfiStatus);
            break;
        }

        //
        // Description Offset. Begins immediately after the end of sUEFI_BOOT_OPTION
        //

        UINTN DescriptionFieldOffset = sizeof(UINT32) + sizeof(UINT16);
        CHAR16* EfiDescription = (CHAR16*)(((UINT8*)BootOption) + DescriptionFieldOffset);
        EfiDescriptionSize = (UINT16)(StrLen(EfiDescription) + 1) * sizeof(CHAR16);
        DescriptionOffset = sizeof(sUEFI_BOOT_OPTION);

        //
        // DevicePath Offset. Begins immediately after Description string
        //

        EFI_DEVICE_PATH_PROTOCOL*
            DevicePath = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)(EfiDescription) + EfiDescriptionSize);
        CHAR16* EfiDevicePathString = DevicePathToTextIf->ConvertDevicePathToText(DevicePath,
                                                                                  FALSE,
                                                                                  FALSE);
        EfiDevicePathSize = (UINT16)(StrLen(EfiDevicePathString) + 1) * sizeof(CHAR16);
        DevicePathOffset = DescriptionOffset + EfiDescriptionSize;

        //
        // OptionalData Offset. Begins immediately after DevicePath string.
        // But first make sure OptionalData is present in EFI_LOAD_OPTION.
        // If the size of BootXXXX variable is greater than the offset of
        // OptionalData in EFI_LOAD_OPTION then it means OptionalData is
        // present
        //

        DescriptionFieldOffset = sizeof(UINT32) + sizeof(UINT16);
        EfiDescription = (CHAR16*)(((UINT8*)BootOption) + DescriptionFieldOffset);
        EfiDescriptionSize = (UINT16)(StrLen(EfiDescription) + 1) * sizeof(CHAR16);
        UINTN EfiCommandLineOffset = DescriptionFieldOffset + EfiDescriptionSize +
                                     BootOption->FilePathListLength;

        if (EfiCommandLineOffset < BootOptionSize) {
            EfiCommandLine = (UINT16*)((UINT8*)(BootOption) + EfiCommandLineOffset);

            //
            // we only read UFP specific command lines. Don't touch Windows
            // boot manager WINDOWS_OS_OPTIONS or other structures
            //

            if (StrStr(EfiCommandLine, L"{UFP}") != NULL) {
                EfiCommandLineSize = (UINT16)(StrLen(EfiCommandLine) + 1) * sizeof(CHAR16);
                CommandLineOffset = DevicePathOffset + EfiDevicePathSize;
            }
        }

        if (BootOptionsBuffer != NULL) {
            BufferOffset = (sUEFI_BOOT_OPTION*)(((UINT8*)BootOptionsBuffer) + Offset);
            BufferOffset->uIndex = i;
            PUTB32(BufferOffset->dwAttributes, BootOption->Attributes);
            PUTB16(BufferOffset->wBootOption, Option);
            PUTB16(BufferOffset->wDescriptionOffset, DescriptionOffset);
            PUTB16(BufferOffset->wDevicePathOffset, DevicePathOffset);
            PUTB16(BufferOffset->wCommandLineOffset, CommandLineOffset);

            //
            // Copy Description string
            //

            CopyMem((UINT8*)BufferOffset + DescriptionOffset, EfiDescription, EfiDescriptionSize);

            //
            // Copy DevicePath string
            //

            CopyMem((UINT8*)BufferOffset + DevicePathOffset,
                    EfiDevicePathString,
                    EfiDevicePathSize);

            //
            // Copy Command Line string if present
            //

            if (EfiCommandLineSize > 0) {
                CopyMem((UINT8*)BufferOffset + CommandLineOffset,
                        EfiCommandLine,
                        EfiCommandLineSize);
            }

            PUTB16(BufferOffset->wSize,
                   (UINT32)sizeof(sUEFI_BOOT_OPTION) + EfiDescriptionSize + EfiDevicePathSize +
                       EfiCommandLineSize);
        }

        Offset += (UINT32)(sizeof(sUEFI_BOOT_OPTION) + EfiDescriptionSize + EfiDevicePathSize +
                           EfiCommandLineSize);

        FreePool(EfiDevicePathString);
        FreePool(BootOption);
        BootOption = NULL;
    }

    *NumOptions = RetNumOptions;
    *BootOptionsBufferLength = Offset;

Exit:
    FreePool(BootOrder);
    FreePool(BootOption);

    BootOrder = NULL;
    BootOption = NULL;

    return EfiStatus;
}

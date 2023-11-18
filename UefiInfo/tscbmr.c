#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "file.h"
#include "utils.h"

#define EFI_MS_CBMR_PROTOCOL_GUID                          \
    {                                                      \
        0x887481f5, 0xfa49, 0x4f65,                        \
        {                                                  \
            0xb0, 0x3c, 0x55, 0x1d, 0xb5, 0x3c, 0x8c, 0x23 \
        }                                                  \
    }

#define EFI_MS_CBMR_VARIABLES_INTERNAL_GUID                 \
    {                                                       \
        0xCA787F2E, 0x4D68, 0x4883,                         \
        {                                                   \
            0xB9, 0x9E, 0x7F, 0xB1, 0x2E, 0xB3, 0x49, 0xCD  \
        }                                                   \
    }
static VOID ReadinessPrintProtocolInfo(IN PPROTOCOL_INFO ProtocolInfo)
{
    if (ProtocolInfo->ProtocolGuid == NULL) {
        return;
    }

    //
    // Display support status
    //

    DBG_INFO("%-45a %a ",
             ProtocolInfo->ProtocolName,
             EFI_ERROR(ProtocolInfo->ProtocolStatus) ? "Not Supported" : "Supported");
    if (ProtocolInfo->ServiceBindingProtocolName != NULL) {
        DBG_INFO("%-45a %a ",
                 ProtocolInfo->ServiceBindingProtocolName,
                 EFI_ERROR(ProtocolInfo->ServiceBindingProtocolStatus) ? "Not Supported" :
                                                                         "Supported");
    }
}

static VOID ProtocolProbeAll(VOID)
{
    for (UINTN Index = 0; Index < EFI_MAX_PROTOCOL_INDEX; Index++) {
        ProtocolGetInfo(&ProtocolArray[Index]);
    }
}

static EFI_STATUS CbmrReadiness(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;

    UNREFERENCED_PARAMETER(Session);

    ProtocolProbeAll();

    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEVICE_PATH_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEVICE_PATH_UTILITIES_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DRIVER_BINDING_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_LOADED_IMAGE_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HTTP_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_IP4_CONFIG2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_IP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_TCP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_TLS_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_TLS_CONFIGURATION_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_II_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SUPPLICANT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_RAM_DISK_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HASH2_PROTOCOL_INDEX]);

#if 0
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SIMPLE_TEXT_INPUT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SIMPLE_POINTER_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_ABSOLUTE_POINTER_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_LOAD_FILE_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_LOAD_FILE2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_FILE_INFO_ID_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DISK_IO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DISK_IO2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLOCK_IO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLOCK_IO2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLOCK_IO_CRYPTO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_ERASE_BLOCK_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_ATA_PASS_THRU_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SD_MMC_PASS_THRU_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_USBFN_IO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_USB_IO_PROTOCOL_INDEX]);
#if defined(_X86_) || defined(_AMD64_)
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_USB_INIT_PROTOCOL_INDEX]);
#else // Qualcomm
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_USB_INIT_PROTOCOL_INDEX]);
#endif
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_IP6_CONFIG_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DHCP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DHCP6_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_TCP6_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_UDP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_UDP6_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DNS4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DNS6_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_EAP_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_EAP_MANAGEMENT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_EAP_MANAGEMENT2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_EAP_CONFIGURATION_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_WIRELESS_MAC_CONNECTION_PROTOCOL_INDEX]);

    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLUETOOTH_HC_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLUETOOTH_IO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLUETOOTH_CONFIG_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLUETOOTH_ATTRIBUTE_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_BLUETOOTH_LE_CONFIG_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_FTP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_MTFTP4_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_MTFTP6_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HTTP_UTILITIES_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HTTP_BOOT_CALLBACK_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_REST_EX_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_REST_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HASH_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_RNG_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_FONT_EX_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_STRING_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_IMAGE_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_IMAGE_EX_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_IMAGE_DECODER_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_FONT_GLYPH_GENERATOR_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_DATABASE_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_CONFIG_ROUTING_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_CONFIG_ACCESS_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_FORM_BROWSER2_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_HII_POPUP_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SERIAL_IO_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEBUG_SUPPORT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_DEBUGPORT_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_SMBIOS_PROTOCOL_INDEX]);
    ReadinessPrintProtocolInfo(&ProtocolArray[EFI_TIMESTAMP_PROTOCOL_INDEX]);
#endif

    return Status;
}

#define EFI_MS_CBMR_RELEASE_PROTOCOL_GUID                  \
    {                                                      \
        0x887481f5, 0xfa49, 0x4f65,                        \
        {                                                  \
            0xb0, 0x3c, 0x55, 0x1d, 0xb5, 0x3c, 0x8c, 0x23 \
        }                                                  \
    }
#define EFI_MS_CBMR_DEBUG_PROTOCOL_GUID                    \
    {                                                      \
        0xcdd7e25c, 0xdbee, 0x423c,                        \
        {                                                  \
            0xb2, 0x5f, 0xe3, 0xa3, 0x5c, 0x6b, 0xdd, 0x7b \
        }                                                  \
    }

//
// Unload existing driver. This helps in trying newer version of the side
// loaded driver easy without rebooting the machine
//

static EFI_STATUS CbmrUnload(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HANDLE* Handles = NULL;
    UINTN HandleCount = 0;
    EFI_GUID CbmrProtocolGuids[2] = {EFI_MS_CBMR_RELEASE_PROTOCOL_GUID,
                                     EFI_MS_CBMR_DEBUG_PROTOCOL_GUID};

    UNREFERENCED_PARAMETER(Session);

    for (UINTN i = 0; i < _countof(CbmrProtocolGuids); i++) {
        Status = gBS->LocateHandleBuffer(ByProtocol,
                                         &CbmrProtocolGuids[i],
                                         NULL,
                                         &HandleCount,
                                         &Handles);
        if (Status == EFI_NOT_FOUND) {
            DBG_INFO("No previous instance of cbmr %a driver is detected",
                     i == 0 ? "release" : "debug");
            Status = EFI_SUCCESS;
        } else if (Status == EFI_SUCCESS) {
            for (UINTN j = 0; j < HandleCount; j++) {
                Status = gBS->UnloadImage(Handles[j]);
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("Unload() of cbmr %a driver failed for handle(%d) : %a(0x%x)",
                              i == 0 ? "release" : "debug",
                              j,
                              E(Status),
                              Status);
                    continue;
                }

                DBG_INFO("Unloaded previous instance of cbmr %a driver for handle(%d)",
                         i == 0 ? "release" : "debug",
                         j);
            }
            FreePool(Handles);
        }
    }

    return EFI_SUCCESS;
}

static EFI_STATUS CbmrLocate(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    VOID* CbmrProtocol = NULL;
    EFI_GUID CbmrProtocolGuids[2] = {EFI_MS_CBMR_RELEASE_PROTOCOL_GUID,
                                     EFI_MS_CBMR_DEBUG_PROTOCOL_GUID};

    UNREFERENCED_PARAMETER(Session);

    for (UINTN i = 0; i < _countof(CbmrProtocolGuids); i++) {
        Status = gBS->LocateProtocol(&CbmrProtocolGuids[i], NULL, (VOID**)&CbmrProtocol);
        if (!EFI_ERROR(Status)) {
            DBG_INFO("Found cbmr %a driver instance", i == 0 ? "release" : "debug");
        } else {
            DBG_INFO("No previous instance of cbmr %a driver is found",
                     i == 0 ? "release" : "debug");
        }
    }

    return EFI_SUCCESS;
}

static EFI_STATUS CbmrWriteSI(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_FILE_PROTOCOL* SiWimFile = NULL;
    UINT64 SiWimFileSize = 0;
    VOID* SiWimFileBuffer = NULL;
    UINT32 Attributes = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS |
                        EFI_VARIABLE_RUNTIME_ACCESS;
    CHAR16* SiWimFileName = L"si.wim";
    CHAR16* SiVariableName = L"SoftwareInventory";

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO_U(L"Locating %s", SiWimFileName);
    Status = FileLocateAndOpen(SiWimFileName, EFI_FILE_MODE_READ, &SiWimFile);
    if (EFI_ERROR(Status)) {
        DBG_ERROR_U(L"FileLocateAndOpen() Failed 0x%x %s", Status, SiWimFileName);
        goto Exit;
    }

    Status = FileGetSize(SiWimFile, &SiWimFileSize);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FileGetSize() failed : 0x%x", Status);
        goto Exit;
    }

    DBG_INFO_U(L"Getting %s file size: %llu", SiWimFileName, SiWimFileSize);

    SiWimFileBuffer = AllocateZeroPool((UINTN)SiWimFileSize);
    if (SiWimFileBuffer == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %llu", SiWimFileSize);
        goto Exit;
    }

    DBG_INFO_U(L"Reading %s", SiWimFileName);
    Status = FileRead(SiWimFile, (UINTN*)&SiWimFileSize, SiWimFileBuffer);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FileRead() failed : 0x%x", Status);
        goto Exit;
    }

    DBG_INFO_U(L"file read: %llu", SiWimFileSize);

    DBG_INFO_U(L"Storing %s in to SoftwareInventory UEFI variable", SiWimFileName);
    Status = gRT->SetVariable(SiVariableName,
                              &(EFI_GUID)EFI_MS_CBMR_VARIABLES_INTERNAL_GUID,
                              Attributes,
                              (UINTN)SiWimFileSize,
                              SiWimFileBuffer);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("SetVariable() failed : 0x%x", Status);
        goto Exit;
    }

    DBG_INFO_U(L"Successfully stored %s into Software Inventory UEFI variable", SiWimFileName);

Exit:
    FileClose(SiWimFile);
    FreePool(SiWimFileBuffer);

    return Status;
}

static EFI_STATUS CbmrDumpSI(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_FILE_PROTOCOL* WimFile = NULL;
    CHAR16* SiWimFileName = L"si_dump.wim";
    CHAR16* SiVariableName = L"SoftwareInventory";
    UINTN SoftwareInventorySize = 0;
    VOID* SoftwareInventory = NULL;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
    EFI_FILE_PROTOCOL* Root = NULL;
    EFI_LOADED_IMAGE* LoadedImage = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = gRT->GetVariable(SiVariableName,
                              &(EFI_GUID)EFI_MS_CBMR_VARIABLES_INTERNAL_GUID,
                              NULL,
                              &SoftwareInventorySize,
                              NULL);
    if (Status == EFI_NOT_FOUND) {
        DBG_ERROR_U(L"GetVariable() failed. Unable to locate %s variable", SiVariableName);
        goto Exit;
    }

    if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
        goto Exit;
    }

    SoftwareInventory = AllocateZeroPool(SoftwareInventorySize);
    if (SoftwareInventory == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %u", SoftwareInventorySize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Status = gRT->GetVariable(SiVariableName,
                              &(EFI_GUID)EFI_MS_CBMR_VARIABLES_INTERNAL_GUID,
                              NULL,
                              &SoftwareInventorySize,
                              SoftwareInventory);
    if (EFI_ERROR(Status)) {
        goto Exit;
    }

    //
    // Save the in memory SI.WIM blob as si.wim
    //

    Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);
    if (EFI_ERROR(Status)) {
        goto Exit;
    }

    // Open SIMPLE_FILE_SYSTEM_PROTOCOL for the volume from which the
    // current image is loaded
    Status = gBS->HandleProtocol(LoadedImage->DeviceHandle,
                                 &gEfiSimpleFileSystemProtocolGuid,
                                 (void**)&SimpleFileSystem);
    if (EFI_ERROR(Status)) {
        goto Exit;
    }

    Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
    if (EFI_ERROR(Status)) {
        goto Exit;
    }

    Status = Root->Open(Root,
                        &WimFile,
                        SiWimFileName,
                        EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
                        0);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Open() failed 0x%x", Status);
        goto Exit;
    }

    Status = FileWrite(WimFile, &SoftwareInventorySize, SoftwareInventory);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FileWrite() failed 0x%x", Status);
        goto Exit;
    }

    DBG_INFO_U(L"Successfully stored Software Inventory UEFI variable contents to %s",
               SiWimFileName);

Exit:
    FileClose(WimFile);

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("cbmrunload"),
        .Description = t("Unload CBMR driver"),
        .DutTestFn = CbmrUnload,
    },
    {
        .Name = t("cbmrlocate"),
        .Description = t("Locate CBMR protocol"),
        .DutTestFn = CbmrLocate,
    },
    {
        .Name = t("cbmrreadiness"),
        .Description = t("Dump status of protocols required for CBMR"),
        .DutTestFn = CbmrReadiness,
    },
    {
        .Name = t("cbmrwritesi"),
        .Description = t("Write software inventory UEFI variable from si.wim file"),
        .DutTestFn = CbmrWriteSI,
    },
    {
        .Name = t("cbmrdumpsi"),
        .Description = t("Write software inventory UEFI variable contents to si_dump.wim file"),
        .DutTestFn = CbmrDumpSI,
    },
};

UEFIINFO_TEST_SUITE CBMRTestSuite = {
    .Description = t("CBMR related test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

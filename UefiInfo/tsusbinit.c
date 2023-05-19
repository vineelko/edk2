#include "common.h"

#include "protocols.h"
#include "efiusbinitprotocol.h"
#include "testsuites.h"

static EFI_STATUS UsbInitProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PPROTOCOL_INFO UsbInitProtocolInfo = &ProtocolArray[EFI_USB_INIT_PROTOCOL_INDEX];
    EFI_USB_INIT_PROTOCOL* UsbInitProtocol = UsbInitProtocolInfo->Protocol;
    USB_CORE_INFO UsbCoreInfo = {0};
    UINT8 USBPort = 0;

    UNREFERENCED_PARAMETER(Session);

    if (EFI_ERROR(UsbInitProtocolInfo->ProtocolStatus)) {
        DBG_INFO("USB INIT Protocol not found %a(0x%x)",
                 E(UsbInitProtocolInfo->ProtocolStatus),
                 UsbInitProtocolInfo->ProtocolStatus);
        Status = UsbInitProtocolInfo->ProtocolStatus;
        goto Exit;
    }

    Status = UsbInitProtocol->QueryCoreInfo(UsbInitProtocol, &USBPort, &UsbCoreInfo);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("QueryCoreInfo() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("                    Number of Cores : %u", UsbCoreInfo.CoreNum);
    Status = UsbInitProtocol->StartController(UsbInitProtocol,
                                              UsbCoreInfo.CoreNum,
                                              EFI_USB_PERIPHERAL_MODE);
    DBG_INFO("                         Controller : %a",
             EFI_ERROR(Status) ? "Failed to start" : "Started");

    //(VOID)usbfnIo->StopController(usbfnIo);

Exit:

    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("usbinitinfo"),
        .Description = t("USB Init IO Info"),
        .DutTestFn = UsbInitProbe,
    },
};

UEFIINFO_TEST_SUITE UsbInitTestSuite = {
    .Description = t("USB Init test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

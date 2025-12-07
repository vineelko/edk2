/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsusbinit.c

Abstract:

    This module implements usb init(qualcomm) test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "efiusbinitprotocol.h"
#include "testsuites.h"

static EFI_STATUS UsbInitProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_PROTOCOL_INFO UsbInitProtocolInfo = &ProtocolArray[EFI_USB_INIT_PROTOCOL_INDEX];
    EFI_USB_INIT_PROTOCOL* UsbInitProtocol = UsbInitProtocolInfo->Protocol;
    USB_CORE_INFO UsbCoreInfo = {0};
    UINT8 USBPort = 0;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    if (EFI_ERROR(UsbInitProtocolInfo->ProtocolStatus)) {
        DBG_INFO("USB INIT Protocol not found %s(0x%zx)",
                 E(UsbInitProtocolInfo->ProtocolStatus),
                 UsbInitProtocolInfo->ProtocolStatus);
        Status = UsbInitProtocolInfo->ProtocolStatus;
        goto Exit;
    }

    Status = UsbInitProtocol->QueryCoreInfo(UsbInitProtocol, &USBPort, &UsbCoreInfo);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("QueryCoreInfo() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("                    Number of Cores : %u", UsbCoreInfo.CoreNum);
    Status = UsbInitProtocol->StartController(UsbInitProtocol,
                                              UsbCoreInfo.CoreNum,
                                              EFI_USB_PERIPHERAL_MODE);
    DBG_INFO("                         Controller : %s",
             EFI_ERROR(Status) ? "Failed to start" : "Started");

    //(VOID)usbfnIo->StopController(usbfnIo);

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("usbinitinfo"),
        .Description = t("USB Init IO Info"),
        .DutTestFn = UsbInitProbe,
    },
};

BM_TEST_SUITE UsbInitTestSuite = {
    .Description = t("USB Init test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

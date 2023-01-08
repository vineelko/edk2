/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsusbfnio.c

Abstract:

    This module implements usb function protocol test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"
#include <Protocol/UsbFunctionIo.h>

static ENUM_TO_STRING UsbBusSpeed[] = {
    {UsbBusSpeedUnknown, STRINGIFY(UsbBusSpeedUnknown)},
    {UsbBusSpeedLow, STRINGIFY(UsbBusSpeedLow)},
    {UsbBusSpeedFull, STRINGIFY(UsbBusSpeedFull)},
    {UsbBusSpeedHigh, STRINGIFY(UsbBusSpeedHigh)},
    {UsbBusSpeedSuper, STRINGIFY(UsbBusSpeedSuper)},
};

static ENUM_TO_STRING UsbEndPointType[] = {
    {UsbEndpointControl, STRINGIFY(UsbEndpointControl)},
    // {UsbEndpointIsochronous, STRINGIFY(UsbEndpointIsochronous)},
    {UsbEndpointBulk, STRINGIFY(UsbEndpointBulk)},
    // {UsbEndpointInterrupt, STRINGIFY(UsbEndpointInterrupt)},
};

static ENUM_TO_STRING UsbEndPointDirection[] = {
    {EfiUsbEndpointDirectionDeviceTx, STRINGIFY(EfiUsbEndpointDirectionDeviceTx)},
    {EfiUsbEndpointDirectionDeviceRx, STRINGIFY(EfiUsbEndpointDirectionDeviceRx)},
};

static ENUM_TO_STRING UsbDeviceInfoId[] = {
    {EfiUsbDeviceInfoUnknown, STRINGIFY(EfiUsbDeviceInfoUnknown)},
    {EfiUsbDeviceInfoSerialNumber, STRINGIFY(EfiUsbDeviceInfoSerialNumber)},
    {EfiUsbDeviceInfoManufacturerName, STRINGIFY(EfiUsbDeviceInfoManufacturerName)},
    {EfiUsbDeviceInfoProductName, STRINGIFY(EfiUsbDeviceInfoProductName)},
};

static EFI_STATUS UsbfnIoProbe(IN PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_USBFN_IO_PROTOCOL* UsbFnIoProtocol = NULL;
    UINTN BufferSize = 0;
    UINTN MaxSingleTransferSize = 0;
    UINTN MaxTransactionSize = 0;
    UINT16 MaxPacketSize = 0;
    CHAR16 Buffer[1024];
    UINT16 Vid = 0;
    UINT16 Pid = 0;

    UNREFERENCED_PARAMETER(Session);

    ZeroMem(Buffer, _countof(Buffer));

    ProtocolGetInfo(&ProtocolArray[EFI_USBFN_IO_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_USBFN_IO_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("USB FN IO Protocol is not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    UsbFnIoProtocol = ProtocolArray[EFI_USBFN_IO_PROTOCOL_INDEX].Protocol;

    //
    // USB FN IO Version
    //

    DBG_INFO("USB FN IO Version: 0x%x", UsbFnIoProtocol->Revision);

    //
    // USB FN IO Max Transfer Size
    //

    Status = UsbFnIoProtocol->GetMaxTransferSize(UsbFnIoProtocol, &MaxSingleTransferSize);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetMaxTransferSize() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Max Transfer Size : %d bytes(%lld%a)",
             MaxSingleTransferSize,
             PrettySize(MaxSingleTransferSize),
             PrettySizeStr(MaxSingleTransferSize));

    //
    // USB FN IO Max Packet Size
    //

    DBG_INFO("Max packet size:");
    for (UINTN EndPointType = UsbEndpointControl; EndPointType <= UsbEndpointBulk; EndPointType++) {
        DBG_INFO("    End point type %a:", UsbEndPointType[EndPointType].String);
        for (UINTN Speed = UsbBusSpeedLow; Speed <= UsbBusSpeedSuper; Speed++) {
            MaxPacketSize = 0;
            Status = UsbFnIoProtocol->GetEndpointMaxPacketSize(UsbFnIoProtocol,
                                                               UsbEndpointControl,
                                                               Speed,
                                                               &MaxPacketSize);
            if (EFI_ERROR(Status)) {
                DBG_ERROR(
                    "GetEndpointMaxPacketSize() failed @ end point type %a @ speed %a : %a(0x%x)",
                    UsbEndPointType[EndPointType].String,
                    UsbBusSpeed[Speed].String,
                    E(Status),
                    Status);
                Status = EFI_SUCCESS;
                continue;
            }

            DBG_INFO("        @ %a is %d bytes(%lld%a)",
                     UsbBusSpeed[Speed].String,
                     MaxPacketSize,
                     PrettySize(MaxPacketSize),
                     PrettySizeStr(MaxPacketSize));
        }
    }

    //
    // USB FN IO End point policies
    //

    for (UINT8 EndPoint = 0; EndPoint < 2; EndPoint++) {
        for (UINTN Direction = EfiUsbEndpointDirectionDeviceRx;
             Direction <= EfiUsbEndpointDirectionDeviceTx;
             Direction++) {
            BufferSize = sizeof(MaxTransactionSize);
            Status = UsbFnIoProtocol->GetEndpointPolicy(UsbFnIoProtocol,
                                                        EndPoint,
                                                        Direction,
                                                        EfiUsbPolicyMaxTransactionSize,
                                                        &BufferSize,
                                                        &MaxTransactionSize);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("GetEndpointPolicy() failed. EP%u %a : %a(0x%x)",
                          EndPoint,
                          UsbEndPointDirection[Direction].String,
                          E(Status),
                          Status);
                Status = EFI_SUCCESS;
                continue;
            }

            DBG_INFO("Max Transaction Size (EP%u %a): %d bytes(%lld%a)",
                     EndPoint,
                     UsbEndPointDirection[Direction].String,
                     MaxTransactionSize,
                     PrettySize(MaxTransactionSize),
                     PrettySizeStr(MaxTransactionSize));
        }
    }

    //
    // USB FN IO Device Info
    //

    for (UINTN InfoId = EfiUsbDeviceInfoSerialNumber; InfoId <= EfiUsbDeviceInfoProductName;
         InfoId++) {
        BufferSize = _countof(Buffer);
        Status = UsbFnIoProtocol->GetDeviceInfo(UsbFnIoProtocol, InfoId, &BufferSize, Buffer);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("GetDeviceInfo() failed to query %d %a : %a(0x%x)",
                      BufferSize,
                      UsbDeviceInfoId[InfoId].String,
                      E(Status),
                      Status);
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO_U(L"%S: %s", UsbDeviceInfoId[InfoId].String, Buffer);
    }

    //
    // USB FN IO Vendor ID / Product ID
    //

    Status = UsbFnIoProtocol->GetVendorIdProductId(UsbFnIoProtocol, &Vid, &Pid);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetVendorIdProductId() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Vendor ID: 0x%x Product ID: 0x%x", Vid, Pid);

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("usbfnioinfo"),
        .Description = t("USB Function IO Info"),
        .DutTestFn = UsbfnIoProbe,
    },
};

BM_TEST_SUITE UsbFnIoTestSuite = {
    .Description = t("USB Function IO test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

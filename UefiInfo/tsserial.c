#include "common.h"

#include "protocols.h"
#include "testsuites.h"
#include "utils.h"

static EFI_STATUS SerialProbe(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SERIAL_IO_PROTOCOL* SerialIoProtocol = NULL; 
    UINTN BufferSize = 10;
    CHAR8 Buffer[100]; // = "VineelKovvuriasdfasdfasdfasd";

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_SERIAL_IO_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_SERIAL_IO_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_SERIAL_IO_PROTOCOL Protocol not available : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    SerialIoProtocol = ProtocolArray[EFI_SERIAL_IO_PROTOCOL_INDEX].Protocol;
    EFI_SERIAL_IO_MODE *Mode = SerialIoProtocol->Mode;

    DBG_INFO("ControlMask = %u", Mode->ControlMask);
    DBG_INFO("Timeout = %u", Mode->Timeout);
    DBG_INFO("BaudRate = %lu", Mode->BaudRate);
    DBG_INFO("ReceiveFifoDepth = %u", Mode->ReceiveFifoDepth);
    DBG_INFO("DataBits = %u", Mode->DataBits);
    DBG_INFO("Parity = %u", Mode->Parity);
    DBG_INFO("StopBits = %u", Mode->StopBits);
    DumpGuid(SerialIoProtocol->DeviceTypeGuid);

    Status = SerialIoProtocol->Reset(SerialIoProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Reset failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    // Status = SerialIoProtocol->SetControl(SerialIoProtocol, EFI_SERIAL_REQUEST_TO_SEND);
    // if (EFI_ERROR(Status)) {
    //     DBG_ERROR("SetControl failed : %a(0x%x)", E(Status), Status);
    //     goto Exit;
    // }

    UINT32 Control = 0;
    Status = SerialIoProtocol->GetControl(SerialIoProtocol, &Control);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("SetControl failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    DBG_INFO("Control = %u", Control);

    Status = SerialIoProtocol->Write(SerialIoProtocol, &BufferSize, Buffer);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Write failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

Exit:
    return Status;
}

static UEFIINFO_TEST DutTests[] = {
    {
        .Name = t("serinfo"),
        .Description = t("Serial Port Info"),
        .DutTestFn = SerialProbe,
    },
};

UEFIINFO_TEST_SUITE SerialPortTestSuite = {
    .Description = t("Serial Port test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

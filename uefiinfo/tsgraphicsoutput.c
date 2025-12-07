/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsgraphicsoutput.c

Abstract:

    This module implements graphics output test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

static ENUM_TO_STRING PixelFormatMap[] = {
    {PixelRedGreenBlueReserved8BitPerColor, STRINGIFY(PixelRedGreenBlueReserved8BitPerColor)},
    {PixelBlueGreenRedReserved8BitPerColor, STRINGIFY(PixelBlueGreenRedReserved8BitPerColor)},
    {PixelBitMask, STRINGIFY(PixelBitMask)},
    {PixelBltOnly, STRINGIFY(PixelBltOnly)},
    {PixelFormatMax, STRINGIFY(PixelFormatMax)},
};

static EFI_STATUS GraphicsOutputProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                      _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* GraphicsMode = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* GraphicsModeInfo = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** AllGraphicModes = NULL;
    PVOID FrameBufferContent = NULL;
    UINT32 CurrentMode = 0;

    UNREFERENCED_PARAMETER(Session);

    DBG_INFO("Graphics GraphicsOutputProbe");

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GraphicsProtocol = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].Protocol;

    GraphicsMode = GraphicsProtocol->Mode;
    GraphicsModeInfo = GraphicsMode->Info;
    CurrentMode = GraphicsMode->Mode;
    DBG_INFO("Graphics Mode(Current):");
    DBG_INFO("         Current Mode: %d", GraphicsMode->Mode);
    DBG_INFO("         Max Mode: %d", GraphicsMode->MaxMode);
    DBG_INFO("         Frame Buffer Base: 0x%llx", GraphicsMode->FrameBufferBase);
    DBG_INFO("         Frame Buffer Size: 0x%zx", GraphicsMode->FrameBufferSize);
    DBG_INFO("         Graphics Mode Info:");
    DBG_INFO("                Horizontal Resolution: %d", GraphicsModeInfo->HorizontalResolution);
    DBG_INFO("                Vertical Resolution: %d", GraphicsModeInfo->VerticalResolution);
    DBG_INFO("                Pixel Format: %s",
             PixelFormatMap[GraphicsModeInfo->PixelFormat].String);
    DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
             GraphicsModeInfo->PixelInformation.RedMask,
             GraphicsModeInfo->PixelInformation.GreenMask,
             GraphicsModeInfo->PixelInformation.BlueMask);
    DBG_INFO("                Pixels Per Scan Line: %d", GraphicsModeInfo->PixelsPerScanLine);

    AllGraphicModes = AllocateZeroPool(sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*) *
                                       GraphicsMode->MaxMode);
    if (AllGraphicModes == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*) * GraphicsMode->MaxMode);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    DBG_INFO("Enumerating all supported graphics modes:");
    for (UINT32 i = 0; i < GraphicsMode->MaxMode; i++) {
        UINTN SizeOfInfo = 0;
        Status = GraphicsProtocol->QueryMode(GraphicsProtocol, i, &SizeOfInfo, &AllGraphicModes[i]);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO("         Graphics Mode %d Info:", i);
        DBG_INFO("                Horizontal Resolution: %d",
                 AllGraphicModes[i]->HorizontalResolution);
        DBG_INFO("                Vertical Resolution: %d", AllGraphicModes[i]->VerticalResolution);
        DBG_INFO("                Pixel Format: %s",
                 PixelFormatMap[AllGraphicModes[i]->PixelFormat].String);
        DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
                 AllGraphicModes[i]->PixelInformation.RedMask,
                 AllGraphicModes[i]->PixelInformation.GreenMask,
                 AllGraphicModes[i]->PixelInformation.BlueMask);
        DBG_INFO("                Pixels Per Scan Line: %d", AllGraphicModes[i]->PixelsPerScanLine);
    }

    //
    // Before cycling through all the available graphics modes. Copy the
    // framebuffer to restore it back
    //

    FrameBufferContent = AllocateZeroPool(GraphicsMode->FrameBufferSize);
    if (FrameBufferContent == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  GraphicsMode->FrameBufferSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    CopyMem(FrameBufferContent,
            (PVOID)(UINTN)GraphicsMode->FrameBufferBase,
            GraphicsMode->FrameBufferSize);

    //
    // Since we change the graphics mode below prints will not be visible!
    // Redirect the out to a file for the success/failure status
    //

    DBG_INFO("Cycling through all available graphics modes:");
    for (UINT32 i = 0; i < GraphicsMode->MaxMode; i++) {
        DBG_INFO_RAW("Setting graphics mode(%dx%d) : ",
                     AllGraphicModes[i]->HorizontalResolution,
                     AllGraphicModes[i]->VerticalResolution);
        Status = GraphicsProtocol->SetMode(GraphicsProtocol, i);
        if (EFI_ERROR(Status)) {
            DBG_INFO("Failed : %s(0x%zx)", E(Status), Status);
            DBG_ERROR("Unable to set graphics mode(%dx%d). Failed : %s(0x%zx)",
                      AllGraphicModes[i]->HorizontalResolution,
                      AllGraphicModes[i]->VerticalResolution,
                      E(Status),
                      Status);
        } else {
            DBG_INFO("Succeeded");
        }
    }

    //
    // Restore the original graphics mode
    //

    Status = GraphicsProtocol->SetMode(GraphicsProtocol, CurrentMode);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to restore default graphics mode. Failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Restore the original graphics mode frame buffer content.
    //
    // TODO: In Hyper-V below copy hangs for ever for large buffers. Hence
    // disabling for now in VMs
    //

    if (!IsRunningInVM()) {
        CopyMem((PVOID)(UINTN)GraphicsMode->FrameBufferBase,
                FrameBufferContent,
                GraphicsMode->FrameBufferSize);
    }

Exit:

    FreePool(FrameBufferContent);

    if (AllGraphicModes != NULL) {
        for (UINTN i = 0; i < GraphicsMode->MaxMode; i++) {
            FreePool(AllGraphicModes[i]);
        }
        FreePool(AllGraphicModes);
    }

    return Status;
}

extern EFI_STATUS GraphicsOutputRGB(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session);

static BM_TEST DutTests[] = {
    {
        .Name = t("graphicsoutputinfo"),
        .Description = t("Graphics Info"),
        .DutTestFn = GraphicsOutputProbe,
    },
    {
        .Name = t("graphicsoutputrgb"),
        .Description = t("RGB Test"),
        .DutTestFn = GraphicsOutputRGB,
    },
};

BM_TEST_SUITE GraphicsOutputTestSuite = {
    .Description = t("Graphics test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

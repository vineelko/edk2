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

static ENUM_TO_STRING PixelFormatMap[] = {
    {PixelRedGreenBlueReserved8BitPerColor, STRINGIFY(PixelRedGreenBlueReserved8BitPerColor)},
    {PixelBlueGreenRedReserved8BitPerColor, STRINGIFY(PixelBlueGreenRedReserved8BitPerColor)},
    {PixelBitMask, STRINGIFY(PixelBitMask)},
    {PixelBltOnly, STRINGIFY(PixelBltOnly)},
    {PixelFormatMax, STRINGIFY(PixelFormatMax)},
};

EFI_STATUS
GfxDrawCircle(_In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent,
              _In_ UINTN X,
              _In_ UINTN Y,
              _In_ UINTN Radius,
              _In_ UINTN HRes,
              _In_ UINTN VRes,
              _In_ UINTN RGB)
{
    if (X < Radius || X + Radius > HRes || Y < Radius || Y + Radius > VRes) {
        return EFI_INVALID_PARAMETER;
    }

    for (UINTN i = Y - Radius; i < Y + Radius; i++) {
        for (UINTN j = X - Radius; j < X + Radius; j++) {
            UINTN dx = j - X;
            UINTN dy = i - Y;
            if (dx * dx + dy * dy <= Radius * Radius) {
                FrameBufferContent[i * HRes + j].Red = (RGB >> 16) & 0xFF;
                FrameBufferContent[i * HRes + j].Green = (RGB >> 8) & 0xFF;
                FrameBufferContent[i * HRes + j].Blue = (RGB >> 0) & 0xFF;
            }
        }
    }

    return EFI_SUCCESS;
}

static EFI_STATUS GfxDrawRectangle(_In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent,
                                   _In_ UINTN X,
                                   _In_ UINTN Y,
                                   _In_ UINTN Length,
                                   _In_ UINTN Breadth,
                                   _In_ UINTN HRes,
                                   _In_ UINTN VRes,
                                   _In_ UINTN RGB)
{
    if (X + Length > HRes || Y + Breadth > VRes) {
        return EFI_INVALID_PARAMETER;
    }

    for (UINTN i = Y; i < Y + Breadth; i++) {
        for (UINTN j = X; j < X + Length; j++) {
            FrameBufferContent[i * HRes + j].Red = (RGB >> 16) & 0xFF;
            FrameBufferContent[i * HRes + j].Green = (RGB >> 8) & 0xFF;
            FrameBufferContent[i * HRes + j].Blue = (RGB >> 0) & 0xFF;
        }
    }

    return EFI_SUCCESS;
}

// EFI_STATUS
// GraphicsClear (
//     _In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL *FrameBufferContent,
//     _In_ UINTN HRes,
//     _In_ UINTN VRes
//     )
// {
//     for (UINTN i = 0; i < VRes; i++) {
//         for (UINTN j = 0; j < HRes; j++) {
//             FrameBufferContent[i * HRes + j].Red = 0;
//             FrameBufferContent[i * HRes + j].Green = 0;
//             FrameBufferContent[i * HRes + j].Blue = 0;
//         }
//     }

//     return EFI_SUCCESS;
// }

EFI_STATUS
GraphicsOutputRGB(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* GraphicsMode = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* GraphicsModeInfo = NULL;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent = NULL;
    UINT32 FrameBufferSize = 0;
    UINT32 CurrentMode = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GraphicsProtocol = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].Protocol;
    GraphicsMode = GraphicsProtocol->Mode;

    DBG_INFO("Enumerating all supported graphics modes:");
    for (UINT32 i = 0; i < GraphicsMode->MaxMode; i++) {
        UINTN SizeOfInfo = 0;
        Status = GraphicsProtocol->QueryMode(GraphicsProtocol, i, &SizeOfInfo, &GraphicsModeInfo);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO("         Graphics Mode %d Info:", i);
        DBG_INFO("                Horizontal Resolution: %d",
                 GraphicsModeInfo->HorizontalResolution);
        DBG_INFO("                Vertical Resolution: %d", GraphicsModeInfo->VerticalResolution);
        DBG_INFO("                Pixel Format: %s",
                 PixelFormatMap[GraphicsModeInfo->PixelFormat].String);
        DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
                 GraphicsModeInfo->PixelInformation.RedMask,
                 GraphicsModeInfo->PixelInformation.GreenMask,
                 GraphicsModeInfo->PixelInformation.BlueMask);
        DBG_INFO("                Pixels Per Scan Line: %d", GraphicsModeInfo->PixelsPerScanLine);
    }

    Status = GraphicsProtocol->SetMode(GraphicsProtocol, 2);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to restore default graphics mode. Failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    // Status = GraphicsProtocol->QueryMode(GraphicsProtocol, 2, &ModeInfoSize, &GraphicsModeInfo);
    // if (EFI_ERROR(Status)) {
    //     DBG_ERROR("Unable to restore default graphics mode. Failed : %s(0x%zx)",
    //                     E(Status),
    //                     Status);
    //     goto Exit;
    // }

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

    FrameBufferSize = GraphicsModeInfo->HorizontalResolution *
                      GraphicsModeInfo->VerticalResolution * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    FrameBufferContent = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)
                             (UINTN)GraphicsMode->FrameBufferBase; // AllocateZeroPool(FrameBufferSize);
    // if (FrameBufferContent == NULL) {
    //     DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
    //     GraphicsMode->FrameBufferSize); Status = EFI_OUT_OF_RESOURCES; goto Exit;
    // }

    UINTN HRes = GraphicsModeInfo->HorizontalResolution;
    UINTN VRes = GraphicsModeInfo->VerticalResolution;
    UINTN X = 0;
    UINTN Color = 0XFF0000;
    for (UINTN i = 0; i < 3; i++) {
        GfxDrawRectangle(FrameBufferContent, X, 0, HRes / 3, VRes, HRes, VRes, Color);
        X += HRes / 3;
        Color >>= 8;
    }

    GfxDrawCircle(FrameBufferContent, HRes / 2, VRes / 2, 100, HRes, VRes, 0xFFFFFF);

    // GraphicsProtocol->Blt(GraphicsProtocol,
    //                     (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)FrameBufferContent,
    //                     EfiBltBufferToVideo,
    //                     0,
    //                     0,
    //                     0,
    //                     0,
    //                     GraphicsModeInfo->HorizontalResolution,
    //                     GraphicsModeInfo->VerticalResolution,
    //                     0);

Exit:

    FreePool(FrameBufferContent);

    return Status;
}

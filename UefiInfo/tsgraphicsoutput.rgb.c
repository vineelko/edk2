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
GfxDrawCircle(IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent,
              IN UINTN X,
              IN UINTN Y,
              IN UINTN Radius,
              IN UINTN HRes,
              IN UINTN VRes,
              IN UINTN RGB)
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

static EFI_STATUS GfxDrawRectangle(IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent,
                                   IN UINTN X,
                                   IN UINTN Y,
                                   IN UINTN Length,
                                   IN UINTN Breadth,
                                   IN UINTN HRes,
                                   IN UINTN VRes,
                                   IN UINTN RGB)
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

static BOOLEAN GfxPixelsDisplayed(IN EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol)
{

    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Buffer1[10] = {0};
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Buffer2[10] = {0};
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL Buffer3[10] = {0};

    //
    // Save pixel from video first before modifying it
    //

    GraphicsProtocol->Blt(GraphicsProtocol,
                        (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)Buffer1,
                        EfiBltVideoToBltBuffer,
                        0,
                        0,
                        0,
                        0,
                        10,
                        1,
                        GraphicsProtocol->Mode->Info->PixelsPerScanLine *
                                        sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

    //
    // Prep the sample pixels(White)
    //

    for (UINTN i = 0; i < 10; i++) {
        Buffer2[i].Red = 0xFF;
        Buffer2[i].Green = 0xFF;
        Buffer2[i].Blue = 0xFF;
    }

    //
    // Write the pixels to video
    //

    GraphicsProtocol->Blt(GraphicsProtocol,
                        (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)Buffer2,
                        EfiBltBufferToVideo,
                        0,
                        0,
                        0,
                        0,
                        10,
                        1,
                        GraphicsProtocol->Mode->Info->PixelsPerScanLine *
                                        sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

    //
    // Read the pixels from video
    //

    GraphicsProtocol->Blt(GraphicsProtocol,
                        (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)Buffer3,
                        EfiBltVideoToBltBuffer,
                        0,
                        0,
                        0,
                        0,
                        10,
                        1,
                        GraphicsProtocol->Mode->Info->PixelsPerScanLine *
                                        sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

    //
    // Compare Buffer2 and Buffer3
    //
    for (UINTN i = 0; i < 10; i++) {
        if (Buffer2[i].Red != Buffer3[i].Red ||
            Buffer2[i].Green != Buffer3[i].Green ||
            Buffer2[i].Blue != Buffer3[i].Blue) {
            return FALSE;
        }
    }

    return TRUE;
}


// EFI_STATUS
// GraphicsClear (
//     IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL *FrameBufferContent,
//     IN UINTN HRes,
//     IN UINTN VRes
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
GraphicsOutputRGB(IN PUEFIINFO_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* GraphicsMode = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* GraphicsModeInfo = NULL;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* FrameBufferContent = NULL;
    // UINT32 FrameBufferSize = 0;
    // UINT32 CurrentMode = 0;

    UNREFERENCED_PARAMETER(Session);

    ProtocolGetInfo(&ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX]);

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL Protocol not available : %a(0x%x)",
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
        DBG_INFO("                Pixel Format: %a",
                 PixelFormatMap[GraphicsModeInfo->PixelFormat].String);
        DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
                 GraphicsModeInfo->PixelInformation.RedMask,
                 GraphicsModeInfo->PixelInformation.GreenMask,
                 GraphicsModeInfo->PixelInformation.BlueMask);
        DBG_INFO("                Pixels Per Scan Line: %d", GraphicsModeInfo->PixelsPerScanLine);
    }

    Status = GraphicsProtocol->SetMode(GraphicsProtocol, 3);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to restore default graphics mode. Failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    // Status = GraphicsProtocol->QueryMode(GraphicsProtocol, 2, &ModeInfoSize, &GraphicsModeInfo);
    // if (EFI_ERROR(Status)) {
    //     DBG_ERROR("Unable to restore default graphics mode. Failed : %a(0x%x)",
    //                     E(Status),
    //                     Status);
    //     goto Exit;
    // }

    GraphicsModeInfo = GraphicsMode->Info;
    // CurrentMode = GraphicsMode->Mode;
    DBG_INFO("Graphics Mode(Updated):");
    DBG_INFO("         Current Mode: %d", GraphicsMode->Mode);
    DBG_INFO("         Max Mode: %d", GraphicsMode->MaxMode);
    DBG_INFO("         Frame Buffer Base: 0x%llx", GraphicsMode->FrameBufferBase);
    DBG_INFO("         Frame Buffer Size: 0x%x", GraphicsMode->FrameBufferSize);
    DBG_INFO("         Graphics Mode Info:");
    DBG_INFO("                Horizontal Resolution: %d", GraphicsModeInfo->HorizontalResolution);
    DBG_INFO("                Vertical Resolution: %d", GraphicsModeInfo->VerticalResolution);
    DBG_INFO("                Pixel Format: %a",
             PixelFormatMap[GraphicsModeInfo->PixelFormat].String);
    DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
             GraphicsModeInfo->PixelInformation.RedMask,
             GraphicsModeInfo->PixelInformation.GreenMask,
             GraphicsModeInfo->PixelInformation.BlueMask);
    DBG_INFO("                Pixels Per Scan Line: %d", GraphicsModeInfo->PixelsPerScanLine);

    // FrameBufferSize = GraphicsModeInfo->HorizontalResolution *
    //                   GraphicsModeInfo->VerticalResolution * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
    FrameBufferContent = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)(UINTN)
                             GraphicsMode->FrameBufferBase; // AllocateZeroPool(FrameBufferSize);
    // if (FrameBufferContent == NULL) {
    //     DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
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

    GraphicsProtocol->Blt(GraphicsProtocol,
                        (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)FrameBufferContent,
                        EfiBltBufferToVideo,
                        0,
                        0,
                        0,
                        0,
                        GraphicsModeInfo->HorizontalResolution,
                        GraphicsModeInfo->VerticalResolution,
                        GraphicsModeInfo->PixelsPerScanLine *
                                        sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

    if (GfxPixelsDisplayed(GraphicsProtocol)) {
        DBG_INFO("Resolution can be displayed");
    } else {
        DBG_INFO("Resolution cannot be displayed");
    }

Exit:

    FreePool(FrameBufferContent);

    return Status;
}

#ifndef _UI_COMMON_H_
#define _UI_COMMON_H_

typedef struct _BM_FRAMEBUFFER {
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Bitmap;
    UINTN Width;
    UINTN Height;
} BM_FRAMEBUFFER, *PBM_FRAMEBUFFER;

typedef struct _BM_FONT_INFO {
    EFI_HII_FONT_PROTOCOL* FontProtocol;
    EFI_FONT_DISPLAY_INFO* Font;
} BM_FONT_INFO, *PBM_FONT_INFO;

typedef struct _BM_RECT {
    UINTN X;
    UINTN Y;
    UINTN Width;
    UINTN Height;
} BM_RECT, *PBM_RECT;

//
// General 2D-Graphics utility functions
//

VOID SetColor(IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Pixel, IN UINT32 ARGB);

BM_RECT
GetClipRectangle(IN PBM_RECT Source, IN PBM_RECT Destination);

EFI_STATUS
ClearFrameBuffer(IN PBM_FRAMEBUFFER FrameBuffer);

EFI_STATUS
GraphicsFillColor(IN PBM_FRAMEBUFFER FrameBuffer,
                  IN PBM_RECT Rect,
                  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL SamplePixel);

//
// Font/Raster utility functions
//

#define RASTER_ATTRIBUTE_BG_BLUE  0x00000001
#define RASTER_ATTRIBUTE_BG_WHITE 0x00000002
#define RASTER_ATTRIBUTE_INVERT   0x00000004

EFI_STATUS
RasterCharacter(IN BM_FRAMEBUFFER* FrameBuffer,
                IN PBM_FONT_INFO FontInfo,
                IN CHAR16 Char,
                IN UINTN X,
                IN UINTN Y,
                IN UINTN Attributes);

//
// Wi-Fi Connection Manager Main function
//

EFI_STATUS
WifiCmUIMain(IN PBM_FRAMEBUFFER FrameBuffer, IN PBM_FONT_INFO FontInfo);
#endif // _UI_COMMON_H_

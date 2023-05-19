#ifndef _UI_COMMON_H_
#define _UI_COMMON_H_

typedef struct _UEFIINFO_FRAMEBUFFER {
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Bitmap;
    UINTN Width;
    UINTN Height;
} UEFIINFO_FRAMEBUFFER, *PUEFIINFO_FRAMEBUFFER;

typedef struct _UEFIINFO_FONT_INFO {
    EFI_HII_FONT_PROTOCOL* FontProtocol;
    EFI_FONT_DISPLAY_INFO* Font;
} UEFIINFO_FONT_INFO, *PUEFIINFO_FONT_INFO;

typedef struct _UEFIINFO_RECT {
    UINTN X;
    UINTN Y;
    UINTN Width;
    UINTN Height;
} UEFIINFO_RECT, *PUEFIINFO_RECT;

//
// General 2D-Graphics utility functions
//

VOID SetColor(IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Pixel, IN UINT32 ARGB);

UEFIINFO_RECT
GetClipRectangle(IN PUEFIINFO_RECT Source, IN PUEFIINFO_RECT Destination);

EFI_STATUS
ClearFrameBuffer(IN PUEFIINFO_FRAMEBUFFER FrameBuffer);

EFI_STATUS
GraphicsFillColor(IN PUEFIINFO_FRAMEBUFFER FrameBuffer,
                  IN PUEFIINFO_RECT Rect,
                  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL SamplePixel);

//
// Font/Raster utility functions
//

#define RASTER_ATTRIBUTE_BG_BLUE  0x00000001
#define RASTER_ATTRIBUTE_BG_WHITE 0x00000002
#define RASTER_ATTRIBUTE_INVERT   0x00000004

EFI_STATUS
RasterCharacter(IN UEFIINFO_FRAMEBUFFER* FrameBuffer,
                IN PUEFIINFO_FONT_INFO FontInfo,
                IN CHAR16 Char,
                IN UINTN X,
                IN UINTN Y,
                IN UINTN Attributes);

//
// Wi-Fi Connection Manager Main function
//

EFI_STATUS
WifiCmUIMain(IN PUEFIINFO_FRAMEBUFFER FrameBuffer, IN PUEFIINFO_FONT_INFO FontInfo);
#endif // _UI_COMMON_H_

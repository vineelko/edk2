#ifndef _GRAPHICS_COMMON_H_
#define _GRAPHICS_COMMON_H_

#define GLYPH_WIDTH  0x8
#define GLYPH_HEIGHT 0x13

#define DEFAULT_PROGRESS_BAR_HEIGHT 20
#define DEFAULT_LABEL_HEIGHT        GLYPH_HEIGHT

#define WHITE_COLOR 0x00FFFFFF
#define BLACK_COLOR 0x00000000

typedef struct _GFX_FRAMEBUFFER {
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Bitmap;
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL* BackBuffer; // Used to restore the original framebuffer content
    UINTN Width;
    UINTN Height;
} GFX_FRAMEBUFFER, *PGFX_FRAMEBUFFER;

typedef struct _GFX_FONT_INFO {
    EFI_HII_FONT_PROTOCOL* FontProtocol;
    EFI_FONT_DISPLAY_INFO* Font;
} GFX_FONT_INFO, *PGFX_FONT_INFO;

typedef struct _GFX_RECT {
    UINTN X;
    UINTN Y;
    UINTN Width;
    UINTN Height;
} GFX_RECT, *PGFX_RECT;

typedef struct _GFX_PROGRESS_BAR {
    GFX_RECT Bounds;
    UINTN Percentage;
} GFX_PROGRESS_BAR, *PGFX_PROGRESS_BAR;

typedef struct _GFX_LABEL {
    GFX_RECT Bounds;
    CHAR16* Text;
} GFX_LABEL, *PGFX_LABEL;

//
// Low level 2D Drawing functions
//

EFI_STATUS
GfxFillRectangle(_In_ PGFX_FRAMEBUFFER FrameBuffer, _In_ PGFX_RECT Rect, _In_ UINT32 RGB);

EFI_STATUS
GfxDrawRectangle(_In_ PGFX_FRAMEBUFFER FrameBuffer, _In_ PGFX_RECT Rect, _In_ UINT32 RGB);

//
// UI component functions
//

EFI_STATUS GfxDrawProgressBar(_In_ PGFX_FRAMEBUFFER FrameBuffer,
                              _In_ PGFX_PROGRESS_BAR ProgressBar,
                              _In_ UINT32 RGB);

EFI_STATUS GfxDrawLabel(_In_ PGFX_FRAMEBUFFER FrameBuffer,
                        _In_ PGFX_LABEL Label,
                        _In_ PGFX_FONT_INFO FontInfo,
                        _In_ UINT32 RGB);

//
// Direct screen rendering utility functions
//

EFI_STATUS GfxUpdateFrameBufferToScreen(_In_ PGFX_FRAMEBUFFER FrameBuffer);

EFI_STATUS GfxClearScreen(_In_ PGFX_FRAMEBUFFER FrameBuffer, _In_ UINT32 RGB);

//
// Color utility functions
//

VOID GfxInitRectangle(_In_ PGFX_RECT Rect,
                      _In_ UINTN X,
                      _In_ UINTN Y,
                      _In_ UINTN Width,
                      _In_ UINTN Height);

VOID GfxSetColor(_In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL* Pixel, _In_ UINT32 ARGB);

EFI_GRAPHICS_OUTPUT_BLT_PIXEL
GfxInvertColor(_In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL Pixel);

//
// Frame buffer utility functions
//

EFI_STATUS GfxSetGraphicsResolution(_Out_ UINT32* PreviousMode);

EFI_STATUS GfxAllocateFrameBuffer(_In_ PGFX_FRAMEBUFFER FrameBuffer);

EFI_STATUS
GfxFillColor(_In_ PGFX_FRAMEBUFFER FrameBuffer,
             _In_ PGFX_RECT Rect,
             _In_ EFI_GRAPHICS_OUTPUT_BLT_PIXEL SamplePixel);

EFI_STATUS GfxClearFrameBuffer(_In_ PGFX_FRAMEBUFFER FrameBuffer);

//
// General 2D utility functions
//

GFX_RECT
GfxGetClipRectangle(_In_ PGFX_RECT Source, _In_ PGFX_RECT Destination);

//
// Font utility functions
//
// TODO: Generalize below macros
#define RASTER_ATTRIBUTE_BG_BLUE  0x00000001
#define RASTER_ATTRIBUTE_BG_WHITE 0x00000002
#define RASTER_ATTRIBUTE_INVERT   0x00000004

EFI_STATUS
GfxGetFontGlyph(_In_ PGFX_FONT_INFO FontInfo,
                _In_ CHAR16 Char,
                _Inout_ EFI_IMAGE_OUTPUT** CharImageOut);

EFI_STATUS
GfxRasterCharacter(_In_ GFX_FRAMEBUFFER* FrameBuffer,
                   _In_ PGFX_FONT_INFO FontInfo,
                   _In_ CHAR16 Char,
                   _In_ UINTN X,
                   _In_ UINTN Y,
                   _In_ UINTN Attributes);

EFI_STATUS GfxGetSystemFont(_In_ PGFX_FONT_INFO FontInfo);

#endif // _GRAPHICS_COMMON_H_

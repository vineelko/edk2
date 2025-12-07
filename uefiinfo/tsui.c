/*++

Copyright (c) 2021 Microsoft Corporation

Module Name:

    tsui.c

Abstract:

    This module implements a simple Wi-Fi Connection Manager UI test case

Author:

    Vineel Kovvuri (vineelko) 10-Mar-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"
#include "graphics_common.h"
// #include "wifi_cm.h"

#include "font.h"

static ENUM_TO_STRING PixelFormatMap[] = {
    {PixelRedGreenBlueReserved8BitPerColor, STRINGIFY(PixelRedGreenBlueReserved8BitPerColor)},
    {PixelBlueGreenRedReserved8BitPerColor, STRINGIFY(PixelBlueGreenRedReserved8BitPerColor)},
    {PixelBitMask, STRINGIFY(PixelBitMask)},
    {PixelBltOnly, STRINGIFY(PixelBltOnly)},
    {PixelFormatMax, STRINGIFY(PixelFormatMax)},
};

#define HORIZONTAL_RESOLUTION 800
#define VERTICAL_RESOLUTION   600
#define MAX_COLUMNS           100 // HORIZONTAL_RESOLUTION/FONT_WIDTH
#define MAX_ROWS              37  // VERTICAL_RESOLUTION/FONT_WIDTH

#define COLOR_BLACK   0x00000000
#define COLOR_WHITE   0x00FFFFFF
#define COLOR_RED     0x00FF0000
#define COLOR_LIME    0x0000FF00
#define COLOR_BLUE    0x000000FF
#define COLOR_YELLOW  0x00FFFF00
#define COLOR_CYAN    0x0000FFFF
#define COLOR_MAGENTA 0x00FF00FF
#define COLOR_SILVER  0x00C0C0C0
#define COLOR_GRAY    0x00808080
#define COLOR_MAROON  0x00800000
#define COLOR_OLIVE   0x00808000
#define COLOR_GREEN   0x00008000
#define COLOR_PURPLE  0x00800080
#define COLOR_TEAL    0x00008080
#define COLOR_NAVY    0x00000080

#define COLOR_PALE_WHITE   0x00CCCCCC
#define COLOR_BRIGHT_GREEN 0x0016C60C

#define PROGRESS_BAR_BACKGROUND_COLOR COLOR_PALE_WHITE
#define PROGRESS_BAR_FOREGROUND_COLOR COLOR_BRIGHT_GREEN

#define DEFAULT_FOREGROUND_COLOR COLOR_PALE_WHITE
#define DEFAULT_BACKGROUND_COLOR COLOR_BLACK

static EFI_GRAPHICS_OUTPUT_PROTOCOL* gsGraphicsProtocol = NULL;
static EFI_GRAPHICS_OUTPUT_MODE_INFORMATION gsGraphicsMode = {0};
static UINT32 gsForegroundColor = DEFAULT_FOREGROUND_COLOR;
static UINT32 gsBackgroundColor = DEFAULT_BACKGROUND_COLOR;

typedef enum _LABEL_NAME {
    // Label: Value
    LABEL_TIME_NAME,
    LABEL_TIME_VALUE,
    LABEL_FILE_NAME,
    LABEL_FILE_VALUE,
    LABEL_DOWNLOADED_NAME,
    LABEL_DOWNLOADED_VALUE,
    LABEL_STAGE_NAME,
    LABEL_STAGE_VALUE,
    LABEL_NETWORK_NAME,
    LABEL_NETWORK_VALUE,
    LABEL_SSID_NAME,
    LABEL_SSID_VALUE,
    LABEL_IPADDRESS_NAME,
    LABEL_IPADDRESS_VALUE,
    LABEL_DNSSERVER_NAME,
    LABEL_DNSSERVER_VALUE,

    LABEL_DOWNLOAD_URL_NAME,
    LABEL_DOWNLOAD_URL_VALUE,

    LABEL_MAX
} LABEL_NAME;

typedef struct _CBMR_UI_LABEL {
    UINTN Row;
    UINTN Column;
    UINTN NumColumns;
    CHAR* String;
} CBMR_UI_LABEL, *PCBMR_UI_LABEL;

typedef enum _PROGRESS_BAR_NAME {
    PROGRESS_BAR_PER_FILE,
    PROGRESS_BAR_ALL_FILES,

    PROGRESS_BAR_MAX
} PROGRESS_BAR_NAME;

typedef struct _CBMR_UI_PROGRESS_BAR {
    // ██████████░░░░░░░░░      Label
    struct {
        UINTN Row;
        UINTN Column;
        UINTN NumColumns;
        UINTN Percentage;
    } Progress;
    CBMR_UI_LABEL Label;
} CBMR_UI_PROGRESS_BAR, *PCBMR_UI_PROGRESS_BAR;

typedef struct _CBMR_UI {
    CBMR_UI_LABEL Labels[LABEL_MAX];
    CBMR_UI_PROGRESS_BAR ProgressBars[PROGRESS_BAR_MAX];
} CBMR_UI, *PCBMR_UI;

CBMR_UI CbmrUi = {
    // clang-format off
    .Labels = {
        [LABEL_TIME_NAME]       = {2,  10,       15, "Time: "},
        [LABEL_TIME_VALUE]      = {2,  10 + 15,  20, "01:12"},
        [LABEL_FILE_NAME]       = {3,  10,       15, "File: "},
        [LABEL_FILE_VALUE]      = {3,  10 + 15,  20, "winre.wim"},
        [LABEL_DOWNLOADED_NAME]   = {4,  10,       15, "Downloaded: "},
        [LABEL_DOWNLOADED_VALUE]  = {4,  10 + 15,  20, "120MB/450MB"},
        [LABEL_STAGE_NAME]      = {5,  10,       15, "Stage: "},
        [LABEL_STAGE_VALUE]     = {5,  10 + 15,  25, "Downloading Collaterals"},
        [LABEL_NETWORK_NAME]    = {2,  67,      15, "Network: "},
        [LABEL_NETWORK_VALUE]   = {2,  67 + 15, 20, "Connected"},
        [LABEL_SSID_NAME]       = {3,  67,      15, "SSID: "},
        [LABEL_SSID_VALUE]      = {3,  67 + 15, 20, "N/A(Ethernet)"},
        [LABEL_IPADDRESS_NAME]  = {4,  67,      15, "IP Address: "},
        [LABEL_IPADDRESS_VALUE] = {4,  67 + 15, 20, "192.168.1.2"},
        [LABEL_DNSSERVER_NAME]  = {5,  67,      15, "DNS Server: "},
        [LABEL_DNSSERVER_VALUE] = {5,  67 + 15, 20, "192.168.1.1"},
        [LABEL_DOWNLOAD_URL_NAME] = {9,  1, 14, "Downloading: "},
        [LABEL_DOWNLOAD_URL_VALUE] = {9,  1 + 14, 80, "winre.wim from http://tlu.dl.delivery.mp.microsoft.com"},
    },
    .ProgressBars = {
        [PROGRESS_BAR_PER_FILE]  = {{10, 1, (MAX_COLUMNS - 20), 50}, {10, 1 + (MAX_COLUMNS - 20) + 1, 20, "50% 145MB"}},
        [PROGRESS_BAR_ALL_FILES] = {{12, 1, (MAX_COLUMNS - 20), 40}, {10, 1 + (MAX_COLUMNS - 20) + 1, 20, "40% 450MB"}},
    }
    // clang-format on
};

static VOID SetGraphicsMode()
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = gsGraphicsProtocol;
    UINT32 i = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION BestMode = {.HorizontalResolution = UINTN_MAX,
                                                     .VerticalResolution = UINTN_MAX};
    UINT32 BestModeIndex = 0;

    for (i = 0; i < GraphicsProtocol->Mode->MaxMode; i++) {
        UINTN SizeOfInfo = 0;
        EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Mode = NULL;
        UINTN HorizontalResolution = 0;
        UINTN VerticalResolution = 0;

        Status = GraphicsProtocol->QueryMode(GraphicsProtocol, i, &SizeOfInfo, &Mode);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        HorizontalResolution = Mode->HorizontalResolution;
        VerticalResolution = Mode->VerticalResolution;

        // Find the lowest resolution closest to HORIZONTAL_RESOLUTION x
        // VERTICAL_RESOLUTION
        if (Mode->HorizontalResolution >= HORIZONTAL_RESOLUTION &&
            Mode->VerticalResolution >= VERTICAL_RESOLUTION) {
            if (Mode->HorizontalResolution < BestMode.HorizontalResolution) {
                CopyMem(&BestMode, Mode, SizeOfInfo);
                BestModeIndex = i;
            }
        }
        FreePool(Mode);
    }

    if (BestMode.HorizontalResolution == UINTN_MAX) {
        DBG_ERROR("Unable to find any suitable resolution");
        goto Exit;
    }

    Status = GraphicsProtocol->SetMode(GraphicsProtocol, BestModeIndex);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to set resolution of %ux%u",
                  BestMode.HorizontalResolution,
                  BestMode.VerticalResolution);
        goto Exit;
    }

    CopyMem(&gsGraphicsMode, &BestMode, sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));

    DBG_INFO("Successfully set resolution of %ux%u",
             BestMode.HorizontalResolution,
             BestMode.VerticalResolution);

Exit:
    return;
}

static VOID SetForegroundColor(_In_ UINT32 Color)
{
    gsForegroundColor = Color;
}

static VOID SetBackgroundColor(_In_ UINT32 Color)
{
    gsBackgroundColor = Color;
}

static VOID PutChar(_In_ UINTN Row, _In_ UINTN Column, _In_ UINT16 CharCode)
{
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = gsGraphicsProtocol;
    UINT8* FB = (UINT8*)(uintptr_t)GraphicsProtocol->Mode->FrameBufferBase;
    UINT32 PixelsPerScanLine = gsGraphicsMode.PixelsPerScanLine;

    // The key here is casting FB to UINT32* which makes advancing pixel by
    // pixel arithmetic much easier
    UINT32* PixelStart = (UINT32*)FB + FONT_WIDTH * Column + FONT_HEIGHT * Row * PixelsPerScanLine;
    for (UINTN i = 0; i < FONT_HEIGHT; i++) {
        UINT8 PixelData = FontData[CharCode & 0xffff][i];
        for (UINTN j = 0; j < FONT_WIDTH; j++) {
            PixelStart[j] = PixelData & 0x80 ? gsForegroundColor : gsBackgroundColor;
            PixelData <<= 1;
        }

        PixelStart += PixelsPerScanLine;
    }
}

static VOID PutString(_In_ UINTN Row, _In_ UINTN Column, _In_z_ CHAR* String)
{
    while (*String) {
        PutChar(Row, Column++, *String++);
    }
}

static VOID DrawBorder()
{
    for (UINTN x = 1; x < MAX_COLUMNS - 1; x++) {
        PutChar(0, x, FONT_HORIZONTAL_LINE);
    }

    for (UINTN x = 1; x < MAX_COLUMNS - 1; x++) {
        PutChar(MAX_ROWS - 1, x, FONT_HORIZONTAL_LINE);
    }

    for (UINTN y = 1; y < MAX_ROWS - 1; y++) {
        PutChar(y, 0, FONT_VERTICAL_LINE);
    }

    for (UINTN y = 1; y < MAX_ROWS - 1; y++) {
        PutChar(y, MAX_COLUMNS - 1, FONT_VERTICAL_LINE);
    }

    PutChar(0, 0, FONT_TOP_LEFT_CORNER);
    PutChar(0, MAX_COLUMNS - 1, FONT_TOP_RIGHT_CORNER);
    PutChar(MAX_ROWS - 1, 0, FONT_BOTTOM_LEFT_CORNER);
    PutChar(MAX_ROWS - 1, MAX_COLUMNS - 1, FONT_BOTTOM_RIGHT_CORNER);
}

static VOID ClearScreen(UINTN Row, UINTN Column, UINTN NumRows, UINTN NumColumns)
{
    for (UINTN i = 0; i < NumRows; i++) {
        for (UINTN j = 0; j < NumColumns; j++) {
            PutChar(Row + i, Column + j, ' ');
        }
    }
}

static VOID DrawWindowsLogo()
{
    UINTN Column = 2;
    UINTN Row = 2;

    UINT32 ForeGroundColor = gsForegroundColor;
    UINT32 BackGroundColor = gsBackgroundColor;
    SetForegroundColor(COLOR_WHITE);
    SetBackgroundColor(COLOR_BLACK);

    // Top left block
    PutChar(Row, Column, FONT_SOLID_BLOCK_BOTTOM);
    PutChar(Row, Column + 1, FONT_SOLID_BLOCK_BOTTOM);
    PutChar(Row + 1, Column, FONT_SOLID_BLOCK);
    PutChar(Row + 1, Column + 1, FONT_SOLID_BLOCK);

    // Top right block
    PutChar(Row, Column + 3, FONT_SOLID_BLOCK_BOTTOM);
    PutChar(Row, Column + 4, FONT_SOLID_BLOCK_BOTTOM);
    PutChar(Row + 1, Column + 3, FONT_SOLID_BLOCK);
    PutChar(Row + 1, Column + 4, FONT_SOLID_BLOCK);

    // Bottom left block
    PutChar(Row + 3, Column, FONT_SOLID_BLOCK);
    PutChar(Row + 3, Column + 1, FONT_SOLID_BLOCK);
    PutChar(Row + 4, Column, FONT_SOLID_BLOCK_TOP);
    PutChar(Row + 4, Column + 1, FONT_SOLID_BLOCK_TOP);

    // Bottom right block
    PutChar(Row + 3, Column + 3, FONT_SOLID_BLOCK);
    PutChar(Row + 3, Column + 4, FONT_SOLID_BLOCK);
    PutChar(Row + 4, Column + 3, FONT_SOLID_BLOCK_TOP);
    PutChar(Row + 4, Column + 4, FONT_SOLID_BLOCK_TOP);

    SetForegroundColor(COLOR_BLACK);
    SetBackgroundColor(COLOR_WHITE);
    PutChar(Row + 0, Column + 2, FONT_WINDOWS_LOGO_TOP_MIDDLE_GLYPH);
    PutChar(Row + 1, Column + 2, FONT_VERTICAL_LINE);
    PutChar(Row + 2, Column + 2, FONT_PLUS);
    PutChar(Row + 3, Column + 2, FONT_VERTICAL_LINE);
    PutChar(Row + 4, Column + 2, FONT_WINDOWS_LOGO_BOTTOM_MIDDLE_GLYPH);

    PutChar(Row + 2, Column + 0, FONT_HORIZONTAL_LINE);
    PutChar(Row + 2, Column + 1, FONT_HORIZONTAL_LINE);
    PutChar(Row + 2, Column + 2, FONT_PLUS);
    PutChar(Row + 2, Column + 3, FONT_HORIZONTAL_LINE);
    PutChar(Row + 2, Column + 4, FONT_HORIZONTAL_LINE);

    SetForegroundColor(ForeGroundColor);
    SetBackgroundColor(BackGroundColor);
}

static VOID DrawSections()
{
    for (UINTN y = 1; y < 7; y++) {
        PutChar(y, (2 * MAX_COLUMNS) / 3, FONT_VERTICAL_LINE);
    }

    for (UINTN y = 1; y < 7; y++) {
        PutChar(y, 9, FONT_VERTICAL_LINE);
    }

    for (UINTN x = 0; x < MAX_COLUMNS; x++) {
        PutChar(7, x, FONT_HORIZONTAL_LINE);
    }

    // PutChar(7, 0, FONT_T_90_ANTI_CLOCKWISE);
    // PutChar(7, MAX_COLUMNS - 1, FONT_T_90_CLOCKWISE);
    PutChar(7, 9, FONT_INVERTED_T);
    PutChar(7, (2 * MAX_COLUMNS) / 3, FONT_INVERTED_T);
}

static VOID DrawApplicationHeader()
{
    // PutChar(0, 0, FONT_SOLID_BLOCK_RIGHT);
    for (UINTN x = 0; x < MAX_COLUMNS; x++) {
        PutChar(0, x, FONT_SOLID_BLOCK);
    }
    // PutChar(0, MAX_COLUMNS - 1, FONT_SOLID_BLOCK_LEFT);

    UINT32 ForeGroundColor = gsForegroundColor;
    UINT32 BackGroundColor = gsBackgroundColor;
    SetForegroundColor(COLOR_BLACK);
    SetBackgroundColor(COLOR_PALE_WHITE);
    PutString(0, 35, "Cloud Bare Metal Recovery");
    SetForegroundColor(ForeGroundColor);
    SetBackgroundColor(BackGroundColor);
}

static VOID DrawApplicationFooter()
{
    // PutChar(MAX_ROWS - 1, 0, FONT_SOLID_BLOCK_RIGHT);
    for (UINTN x = 0; x < MAX_COLUMNS; x++) {
        PutChar(MAX_ROWS - 1, x, FONT_SOLID_BLOCK);
    }
    // PutChar(MAX_ROWS - 1, MAX_COLUMNS - 1, FONT_SOLID_BLOCK_LEFT);

    UINT32 ForeGroundColor = gsForegroundColor;
    UINT32 BackGroundColor = gsBackgroundColor;
    SetBackgroundColor(COLOR_PALE_WHITE);
    SetForegroundColor(COLOR_RED);
    PutString(MAX_ROWS - 1, 10, "ESC");
    SetForegroundColor(COLOR_BLACK);
    PutString(MAX_ROWS - 1, 14, "Exit");

    SetForegroundColor(COLOR_RED);
    PutString(MAX_ROWS - 1, 21, "F2");
    SetForegroundColor(COLOR_BLACK);
    PutString(MAX_ROWS - 1, 24, "Wi-Fi");

    SetForegroundColor(ForeGroundColor);
    SetBackgroundColor(BackGroundColor);
}

static VOID DrawLabel(CBMR_UI_LABEL* Label)
{
    PutString(Label->Row, Label->Column, Label->String);
}

static VOID DrawProgressBar(CBMR_UI_PROGRESS_BAR* ProgressBar)
{
    UINT32 ForeGroundColor = gsForegroundColor;
    UINT32 BackGroundColor = gsBackgroundColor;

    SetForegroundColor(PROGRESS_BAR_BACKGROUND_COLOR);
    for (UINTN i = 0; i < ProgressBar->Progress.NumColumns; i++) {
        PutChar(ProgressBar->Progress.Row, ProgressBar->Progress.Column + i, FONT_SOLID_BLOCK);
    }

    SetForegroundColor(PROGRESS_BAR_FOREGROUND_COLOR);
    UINTN NumColumns = (ProgressBar->Progress.Percentage * 100) / ProgressBar->Progress.NumColumns;
    for (UINTN i = 0; i < NumColumns; i++) {
        PutChar(ProgressBar->Progress.Row, ProgressBar->Progress.Column + i, FONT_SOLID_BLOCK);
        // Draw Percentage conversion and label drawing
        // EfiSleep(SEC_TO_100_NS(1));
    }
    SetForegroundColor(ForeGroundColor);
    SetBackgroundColor(BackGroundColor);
    PutString(ProgressBar->Label.Row, ProgressBar->Label.Column, ProgressBar->Label.String);
}

static VOID DrawComponents()
{
    // Draw all labels
    for (UINTN i = 0; i < LABEL_MAX; i++) {
        CBMR_UI_LABEL* Label = &CbmrUi.Labels[i];
        DrawLabel(Label);
    }

    // Draw progress bars
    for (UINTN i = 0; i < PROGRESS_BAR_MAX; i++) {
        CBMR_UI_PROGRESS_BAR* ProgressBar = &CbmrUi.ProgressBars[i];
        DrawProgressBar(ProgressBar);
    }
}

static VOID DrawCbmrUi()
{
    ClearScreen(0, 0, MAX_ROWS, MAX_COLUMNS);
    // DrawBorder();
    DrawApplicationHeader();
    DrawWindowsLogo();
    DrawSections();
    DrawComponents();
    DrawApplicationFooter();
}

static VOID PrintBoxCharacters()
{
    ENUM_TO_STRING BoxCharMap[] = {
        {BOXDRAW_HORIZONTAL, STRINGIFY(BOXDRAW_HORIZONTAL)},
        {BOXDRAW_VERTICAL, STRINGIFY(BOXDRAW_VERTICAL)},
        {BOXDRAW_DOWN_RIGHT, STRINGIFY(BOXDRAW_DOWN_RIGHT)},
        {BOXDRAW_DOWN_LEFT, STRINGIFY(BOXDRAW_DOWN_LEFT)},
        {BOXDRAW_UP_RIGHT, STRINGIFY(BOXDRAW_UP_RIGHT)},
        {BOXDRAW_UP_LEFT, STRINGIFY(BOXDRAW_UP_LEFT)},
        {BOXDRAW_VERTICAL_RIGHT, STRINGIFY(BOXDRAW_VERTICAL_RIGHT)},
        {BOXDRAW_VERTICAL_LEFT, STRINGIFY(BOXDRAW_VERTICAL_LEFT)},
        {BOXDRAW_DOWN_HORIZONTAL, STRINGIFY(BOXDRAW_DOWN_HORIZONTAL)},
        {BOXDRAW_UP_HORIZONTAL, STRINGIFY(BOXDRAW_UP_HORIZONTAL)},
        {BOXDRAW_VERTICAL_HORIZONTAL, STRINGIFY(BOXDRAW_VERTICAL_HORIZONTAL)},
        {BOXDRAW_DOUBLE_HORIZONTAL, STRINGIFY(BOXDRAW_DOUBLE_HORIZONTAL)},
        {BOXDRAW_DOUBLE_VERTICAL, STRINGIFY(BOXDRAW_DOUBLE_VERTICAL)},
        {BOXDRAW_DOWN_RIGHT_DOUBLE, STRINGIFY(BOXDRAW_DOWN_RIGHT_DOUBLE)},
        {BOXDRAW_DOWN_DOUBLE_RIGHT, STRINGIFY(BOXDRAW_DOWN_DOUBLE_RIGHT)},
        {BOXDRAW_DOUBLE_DOWN_RIGHT, STRINGIFY(BOXDRAW_DOUBLE_DOWN_RIGHT)},
        {BOXDRAW_DOWN_LEFT_DOUBLE, STRINGIFY(BOXDRAW_DOWN_LEFT_DOUBLE)},
        {BOXDRAW_DOWN_DOUBLE_LEFT, STRINGIFY(BOXDRAW_DOWN_DOUBLE_LEFT)},
        {BOXDRAW_DOUBLE_DOWN_LEFT, STRINGIFY(BOXDRAW_DOUBLE_DOWN_LEFT)},
        {BOXDRAW_UP_RIGHT_DOUBLE, STRINGIFY(BOXDRAW_UP_RIGHT_DOUBLE)},
        {BOXDRAW_UP_DOUBLE_RIGHT, STRINGIFY(BOXDRAW_UP_DOUBLE_RIGHT)},
        {BOXDRAW_DOUBLE_UP_RIGHT, STRINGIFY(BOXDRAW_DOUBLE_UP_RIGHT)},
        {BOXDRAW_UP_LEFT_DOUBLE, STRINGIFY(BOXDRAW_UP_LEFT_DOUBLE)},
        {BOXDRAW_UP_DOUBLE_LEFT, STRINGIFY(BOXDRAW_UP_DOUBLE_LEFT)},
        {BOXDRAW_DOUBLE_UP_LEFT, STRINGIFY(BOXDRAW_DOUBLE_UP_LEFT)},
        {BOXDRAW_VERTICAL_RIGHT_DOUBLE, STRINGIFY(BOXDRAW_VERTICAL_RIGHT_DOUBLE)},
        {BOXDRAW_VERTICAL_DOUBLE_RIGHT, STRINGIFY(BOXDRAW_VERTICAL_DOUBLE_RIGHT)},
        {BOXDRAW_DOUBLE_VERTICAL_RIGHT, STRINGIFY(BOXDRAW_DOUBLE_VERTICAL_RIGHT)},
        {BOXDRAW_VERTICAL_LEFT_DOUBLE, STRINGIFY(BOXDRAW_VERTICAL_LEFT_DOUBLE)},
        {BOXDRAW_VERTICAL_DOUBLE_LEFT, STRINGIFY(BOXDRAW_VERTICAL_DOUBLE_LEFT)},
        {BOXDRAW_DOUBLE_VERTICAL_LEFT, STRINGIFY(BOXDRAW_DOUBLE_VERTICAL_LEFT)},
        {BOXDRAW_DOWN_HORIZONTAL_DOUBLE, STRINGIFY(BOXDRAW_DOWN_HORIZONTAL_DOUBLE)},
        {BOXDRAW_DOWN_DOUBLE_HORIZONTAL, STRINGIFY(BOXDRAW_DOWN_DOUBLE_HORIZONTAL)},
        {BOXDRAW_DOUBLE_DOWN_HORIZONTAL, STRINGIFY(BOXDRAW_DOUBLE_DOWN_HORIZONTAL)},
        {BOXDRAW_UP_HORIZONTAL_DOUBLE, STRINGIFY(BOXDRAW_UP_HORIZONTAL_DOUBLE)},
        {BOXDRAW_UP_DOUBLE_HORIZONTAL, STRINGIFY(BOXDRAW_UP_DOUBLE_HORIZONTAL)},
        {BOXDRAW_DOUBLE_UP_HORIZONTAL, STRINGIFY(BOXDRAW_DOUBLE_UP_HORIZONTAL)},
        {BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE, STRINGIFY(BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE)},
        {BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL, STRINGIFY(BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL)},
        {BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL, STRINGIFY(BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL)},
    };
    CHAR16 Char[2] = {0};

    for (UINTN i = 0; i < _countof(BoxCharMap); i++) {
        DBG_INFO_RAW_U(L" %S: ", BoxCharMap[i].String);
        Char[0] = (CHAR16)BoxCharMap[i].Value;
        gSystemTable->ConOut->OutputString(gSystemTable->ConOut, Char);
    }

    DBG_INFO(" ");
}

EFI_STATUS UI(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* ModeInfo = NULL;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** AllGraphicModes = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* GraphicsMode = NULL;
    UINT32 CurrentMode = 0;

    UNREFERENCED_PARAMETER(Session);

    //
    // Get hold of Graphics protocol
    //

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GraphicsProtocol = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].Protocol;
    gsGraphicsProtocol = GraphicsProtocol;
    ModeInfo = GraphicsProtocol->Mode->Info;

    GraphicsMode = GraphicsProtocol->Mode;
    ModeInfo = GraphicsMode->Info;

    CurrentMode = GraphicsMode->Mode;
    DBG_INFO("Graphics Mode(Current):");
    DBG_INFO("         Current Mode: %d", GraphicsMode->Mode);
    DBG_INFO("         Max Mode: %d", GraphicsMode->MaxMode);
    DBG_INFO("         Frame Buffer Base: 0x%llx", GraphicsMode->FrameBufferBase);
    DBG_INFO("         Frame Buffer Size: 0x%zx", GraphicsMode->FrameBufferSize);
    DBG_INFO("         Graphics Mode Info:");
    DBG_INFO("                Horizontal Resolution: %d", ModeInfo->HorizontalResolution);
    DBG_INFO("                Vertical Resolution: %d", ModeInfo->VerticalResolution);
    DBG_INFO("                Pixel Format: %s", PixelFormatMap[ModeInfo->PixelFormat].String);
    DBG_INFO("                Pixel Mask Information: R=0x%lx,G=0x%lx,B=0x%lx",
             ModeInfo->PixelInformation.RedMask,
             ModeInfo->PixelInformation.GreenMask,
             ModeInfo->PixelInformation.BlueMask);
    DBG_INFO("                Pixels Per Scan Line: %d", ModeInfo->PixelsPerScanLine);

    AllGraphicModes = AllocateZeroPool(sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*) *
                                       GraphicsMode->MaxMode);
    if (AllGraphicModes == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %zd",
                  sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION*) * GraphicsMode->MaxMode);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    DBG_INFO("Enumerating all supported graphics modes:");
    for (UINT32 i = 0; i < GraphicsProtocol->Mode->MaxMode; i++) {
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

    SetGraphicsMode();

    DrawCbmrUi();

Exit:

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("uitest"),
        .Description = t("UI Test"),
        .DutTestFn = UI,
    },
};

BM_TEST_SUITE UITestSuite = {
    .Description = t("UI test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

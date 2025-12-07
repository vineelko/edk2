/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tsfont.c

Abstract:

    This module implements UEFI HII Font test suite

Author:

    Vineel Kovvuri (vineelko) 11-Feb-2021

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"

typedef struct _BM_FONT_NODE {
    EFI_FONT_DISPLAY_INFO* Font;
    struct _BM_FONT_NODE* Next;
} BM_FONT_NODE, *PBM_FONT_NODE;

static EFI_STATUS FontFreeFonts(PBM_FONT_NODE FontList);

static EFI_STATUS FontEnumerateInstalledFonts(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                              PBM_FONT_NODE* FontList);

static EFI_STATUS FontEnumerateInstalledFonts(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                              PBM_FONT_NODE* FontList)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_FONT_HANDLE FontHandle = NULL;
    EFI_FONT_DISPLAY_INFO FontInfoIn = {0};
    EFI_FONT_DISPLAY_INFO* FontInfoOut = NULL;
    EFI_HII_FONT_PROTOCOL* FontProtocol = NULL;
    PBM_FONT_NODE RetFontList = NULL;

    Status = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HII_FONT_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    FontProtocol = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].Protocol;

    //
    // Get System default font
    //

    Status = FontProtocol->GetFontInfo(FontProtocol, &FontHandle, NULL, &FontInfoOut, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetFontInfo() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    RetFontList = AllocateZeroPool(sizeof(BM_FONT_NODE));
    RetFontList->Font = FontInfoOut; // Head will always point to 'sysdefault' font

    //
    // Get non System fonts
    //

    PBM_FONT_NODE PrevNode = RetFontList;
    FontInfoIn.FontInfoMask = EFI_FONT_INFO_ANY_FONT | EFI_FONT_INFO_ANY_SIZE |
                              EFI_FONT_INFO_ANY_STYLE;
    while (TRUE) {
        FontInfoOut = NULL;
        Status = FontProtocol->GetFontInfo(FontProtocol,
                                           &FontHandle,
                                           &FontInfoIn,
                                           &FontInfoOut,
                                           NULL);
        if (EFI_ERROR(Status)) {
            if (Status == EFI_NOT_FOUND) {
                Status = EFI_SUCCESS;
                break;
            }
            DBG_ERROR("GetFontInfo() call failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }

        FontInfoOut->ForegroundColor.Red = 152;
        FontInfoOut->ForegroundColor.Green = 152;
        FontInfoOut->ForegroundColor.Blue = 152;
        // FontInfoOut->BackgroundColor.Red = 152;
        // FontInfoOut->BackgroundColor.Green = 152;
        // FontInfoOut->BackgroundColor.Blue = 152;

        FontInfoOut->FontInfoMask = EFI_FONT_INFO_RESIZE | EFI_FONT_INFO_RESTYLE;

        PBM_FONT_NODE Node = AllocateZeroPool(sizeof(BM_FONT_NODE));
        Node->Font = FontInfoOut;
        PrevNode->Next = Node;

        PrevNode = Node;
    }

    *FontList = RetFontList;
    return Status;
Exit:
    FontFreeFonts(RetFontList);
    return Status;
}

static EFI_STATUS FontFreeFonts(PBM_FONT_NODE FontList)
{
    PBM_FONT_NODE Node = FontList;

    while (Node) {
        PBM_FONT_NODE FreeNode = Node;
        Node = Node->Next;
        FreePool(FreeNode->Font);
        FreePool(FreeNode);
    }

    return EFI_SUCCESS;
}

//
// Test cases
//

static EFI_STATUS FontRasterString(_In_ EFI_FONT_DISPLAY_INFO* Font,
                                   _In_ EFI_HII_FONT_PROTOCOL* FontProtocol,
                                   _In_ EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol,
                                   _In_ CHAR16* String,
                                   _In_ UINTN X,
                                   _In_ UINTN Y)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_IMAGE_OUTPUT* StringImageOut = NULL;
    EFI_HII_ROW_INFO* RowInfo = NULL;
    UINTN RowInfoSize = 0;

    //
    // Raster the string to bitmap
    //

    Status = FontProtocol->StringToImage(FontProtocol,
                                         EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_IGNORE_LINE_BREAK,
                                         String,
                                         Font,
                                         &StringImageOut,
                                         0,
                                         0,
                                         &RowInfo,
                                         &RowInfoSize,
                                         NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("StringToImage() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Show the rastered string a.k.a bitmap image to screen
    //

    Status = GraphicsProtocol->Blt(GraphicsProtocol,
                                   (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)StringImageOut->Image.Bitmap,
                                   EfiBltBufferToVideo,
                                   0,
                                   0,
                                   X,
                                   Y,
                                   RowInfo[0].LineWidth,
                                   RowInfo[0].LineHeight,
                                   (StringImageOut->Width) *
                                       sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)); // But sub-rectangle
                                                                               // from blt buffer
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Blt() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    FreePool(StringImageOut);
    FreePool(RowInfo);
    return Status;
}

static EFI_STATUS FontRasterCharacter(_In_ EFI_FONT_DISPLAY_INFO* Font,
                                      _In_ EFI_HII_FONT_PROTOCOL* FontProtocol,
                                      _In_ EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol,
                                      _In_ CHAR16 Char,
                                      _In_ UINTN X,
                                      _In_ UINTN Y)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_IMAGE_OUTPUT* CharImageOut = NULL;

    //
    // Get the Glyph corresponding to the character
    //

    Status = FontProtocol->GetGlyph(FontProtocol, Char, Font, &CharImageOut, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetGlyph() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Show the rastered Character to screen
    //

    Status = GraphicsProtocol->Blt(GraphicsProtocol,
                                   (EFI_GRAPHICS_OUTPUT_BLT_PIXEL*)CharImageOut->Image.Bitmap,
                                   EfiBltBufferToVideo,
                                   0,
                                   0,
                                   X,
                                   Y,
                                   CharImageOut->Width,
                                   CharImageOut->Height,
                                   0);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Blt() call failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

Exit:
    FreePool(CharImageOut);
    return Status;
}

static EFI_STATUS FontListFontsProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PBM_FONT_NODE FontList = NULL;
    UINTN i = 0;

    UNREFERENCED_PARAMETER(Session);

    Status = FontEnumerateInstalledFonts(ProtocolArray, &FontList);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FontEnumerateInstalledFonts() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Dump all font info
    //

    for (PBM_FONT_NODE Node = FontList; Node; Node = Node->Next, i++) {
        DBG_INFO("Font %zd", i);
        DBG_INFO_U(L"    Font Name: %s", Node->Font->FontInfo.FontName);
        DBG_INFO("    Font Size(cell height): %upx", Node->Font->FontInfo.FontSize);
        DBG_INFO("    Font Style: 0x%x", Node->Font->FontInfo.FontStyle);
        DBG_INFO("    Font Info Mask: 0x%x", Node->Font->FontInfoMask);
        DBG_INFO("    Foreground RGB:(%u, %u, %u)",
                 Node->Font->ForegroundColor.Red,
                 Node->Font->ForegroundColor.Green,
                 Node->Font->ForegroundColor.Blue);
        DBG_INFO("    Background RGB:(%u, %u, %u)",
                 Node->Font->BackgroundColor.Red,
                 Node->Font->BackgroundColor.Green,
                 Node->Font->BackgroundColor.Blue);
    }

Exit:

    FontFreeFonts(FontList);

    return Status;
}

static EFI_STATUS FontRasterStringProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                        _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HII_FONT_PROTOCOL* FontProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    PBM_FONT_NODE FontList = NULL;

    UNREFERENCED_PARAMETER(Session);

    //
    // Get hold of Font and Graphics protocols
    //

    Status = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HII_FONT_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    FontProtocol = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].Protocol;

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GraphicsProtocol = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].Protocol;

    Status = FontEnumerateInstalledFonts(ProtocolArray, &FontList);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FontEnumerateInstalledFonts() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Render string(font name) in all available fonts
    //

    UINTN X = 1;
    UINTN Y = 200;
    for (PBM_FONT_NODE Node = FontList; Node; Node = Node->Next, Y += 80) {
        Status = FontRasterString(Node->Font,
                                  FontProtocol,
                                  GraphicsProtocol,
                                  Node->Font->FontInfo.FontName,
                                  X,
                                  Y);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("FontRasterString() failed : %s(0x%zx)", E(Status), Status);
            goto Exit;
        }
    }

Exit:

    FontFreeFonts(FontList);
    return Status;
}

static EFI_STATUS FontRasterCharacterProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                           _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HII_FONT_PROTOCOL* FontProtocol = NULL;
    EFI_GRAPHICS_OUTPUT_PROTOCOL* GraphicsProtocol = NULL;
    PBM_FONT_NODE FontList = NULL;

    UNREFERENCED_PARAMETER(Session);

    //
    // Get hold of Font and Graphics protocols
    //

    Status = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HII_FONT_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    FontProtocol = ProtocolArray[EFI_HII_FONT_PROTOCOL_INDEX].Protocol;

    Status = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX Protocol not available : %s(0x%zx)",
                  E(Status),
                  Status);
        goto Exit;
    }

    GraphicsProtocol = ProtocolArray[EFI_GRAPHICS_OUTPUT_PROTOCOL_INDEX].Protocol;

    Status = FontEnumerateInstalledFonts(ProtocolArray, &FontList);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("FontEnumerateInstalledFonts() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Render a character in all available fonts
    //
    UINTN X = 1;
    UINTN Y = 240;
    // CHAR16 *AlphaNum =
    // L"!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    CHAR16* AlphaNum = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (PBM_FONT_NODE Node = FontList; Node; Node = Node->Next, Y += 80) {
        X = 1;
        for (CHAR16* Char = AlphaNum; *Char; Char++, X += 30) {
            Status = FontRasterCharacter(Node->Font, FontProtocol, GraphicsProtocol, *Char, X, Y);
            if (EFI_ERROR(Status)) {
                DBG_ERROR("FontRasterCharacter() failed : %s(0x%zx)", E(Status), Status);
                goto Exit;
            }
        }
    }

Exit:

    FontFreeFonts(FontList);
    return Status;
}

#if 0
static
EFI_STATUS
FontListFontPackageProbe (
    _In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session
    )
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HII_DATABASE_PROTOCOL *DBProtocol = NULL;
    UINTN HandleBufferSize = 0;
    EFI_HII_HANDLE *HandleArray = NULL;


    UNREFERENCED_PARAMETER(Session);


    Status = ProtocolArray[EFI_HII_DATABASE_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HII_DATABASE_PROTOCOL Protocol not available : %s(0x%zx)",
                           E(Status),
                           Status);
        goto Exit;
    }

    DBProtocol = ProtocolArray[EFI_HII_DATABASE_PROTOCOL_INDEX].Protocol;

    Status = DBProtocol->ListPackageLists(DBProtocol, EFI_HII_PACKAGE_FONTS, NULL, &HandleBufferSize, HandleArray);
    if (Status == EFI_BUFFER_TOO_SMALL) {
        HandleArray = AllocateZeroPool(HandleBufferSize);
        Status = EFI_SUCCESS;
    } else if (EFI_ERROR(Status)) {
        DBG_ERROR("ListPackageLists() call failed : %s(0x%zx)",
                        E(Status),
                        Status);
        goto Exit;
    }

    Status = DBProtocol->ListPackageLists(DBProtocol, EFI_HII_PACKAGE_FONTS, NULL, &HandleBufferSize, HandleArray);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("ListPackageLists() call failed : %s(0x%zx)",
                        E(Status),
                        Status);
        goto Exit;
    }

    //
    // Dump package info
    //

    for (UINTN i = 0; i < HandleBufferSize/sizeof(EFI_HII_HANDLE); i++) {
        EFI_HII_PACKAGE_LIST_HEADER *PackageListBuffer = NULL;
        UINTN PackageListBufferSize = 0;

        Status = DBProtocol->ExportPackageLists(DBProtocol, HandleArray[i], &PackageListBufferSize, PackageListBuffer);
        if (Status == EFI_BUFFER_TOO_SMALL) {
            PackageListBuffer = AllocateZeroPool(PackageListBufferSize);
            Status = EFI_SUCCESS;
        } else if (EFI_ERROR(Status)) {
            DBG_ERROR("ExportPackageLists() call failed : %s(0x%zx)",
                            E(Status),
                            Status);
            FreePool(PackageListBuffer);
            goto Exit;
        }

        Status = DBProtocol->ExportPackageLists(DBProtocol, HandleArray[i], &PackageListBufferSize, PackageListBuffer);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("ExportPackageLists() call failed : %s(0x%zx)",
                            E(Status),
                            Status);
            FreePool(PackageListBuffer);
            goto Exit;
        }

        DBG_INFO("#########################");
        for (EFI_HII_PACKAGE_LIST_HEADER *PackageListHeader = PackageListBuffer;
            PackageListHeader != NULL && ((CHAR8*)PackageListHeader) < (((CHAR8*)PackageListBuffer) + PackageListBufferSize);
            PackageListHeader = (EFI_HII_PACKAGE_LIST_HEADER*)(((CHAR8*)PackageListHeader) + PackageListHeader->PackageLength)) {

            DBG_INFO("%p PackageListLength %d", PackageListHeader, PackageListHeader->PackageLength);
            for (EFI_HII_PACKAGE_HEADER *PackageHeader = (EFI_HII_PACKAGE_HEADER*)(((CHAR8*)(PackageListHeader)) + sizeof(EFI_HII_PACKAGE_LIST_HEADER));
                PackageHeader != NULL && ((CHAR8*)PackageHeader) < (((CHAR8*)PackageListBuffer) + PackageListBufferSize) && PackageHeader->Type != EFI_HII_PACKAGE_END;
                PackageHeader = (EFI_HII_PACKAGE_HEADER*)(((CHAR8*)PackageHeader) + PackageHeader->Length)) {
                if (PackageHeader->Type != EFI_HII_PACKAGE_FONTS)
                    continue;

                DBG_INFO("    Package Length %d", PackageHeader->Length);
                DBG_INFO("    Package Type %d", PackageHeader->Type);

                //__debugbreak();
                EFI_HII_FONT_PACKAGE_HDR *FontPackage = (EFI_HII_FONT_PACKAGE_HDR *)PackageHeader;
                DBG_INFO_U(L"    Font Family %s", FontPackage->FontFamily);
            }
        }

        // DBG_INFO_U(L"    Font Name: %s", FontInfoOut->FontInfo.FontName);
        FreePool(PackageListBuffer);
    }

Exit:
    return Status;
}

#endif

static BM_TEST DutTests[] = {
    {
        .Name = t("listfont"),
        .Description = t("List all fonts"),
        .DutTestFn = FontListFontsProbe,
    },
    {
        .Name = t("rastercharacter"),
        .Description = t("Raster a character"),
        .DutTestFn = FontRasterCharacterProbe,
    },
    {
        .Name = t("rasterstring"),
        .Description = t("Raster a string"),
        .DutTestFn = FontRasterStringProbe,
    },
    // {
    //     .Name = t("listfontpackges"),
    //     .Description = t("List all fonts"),
    //     .DutTestFn = FontListFontPackageProbe,
    // },
};

BM_TEST_SUITE FontTestSuite = {
    .Description = t("Font test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

#ifndef _DEBUG_H_
#define _DEBUG_H_

typedef enum _DEBUG_FLAGS {
    DEBUG_ERROR,
    DEBUG_WARNING,
    DEBUG_INFO,
    DEBUG_VERBOSE,

    DEBUG_MAX,
} DEBUG_FLAGS;

EFI_STATUS EFIAPI DebugInit();
VOID EFIAPI DebugPrintFormatted(_In_opt_ DEBUG_FLAGS DebugFlag,
                                _In_z_ _Printf_format_string_ CHAR8* Fmt,
                                ...);
VOID EFIAPI DebugPrintFormattedU(_In_opt_ DEBUG_FLAGS DebugFlag,
                                 _In_z_ _Printf_format_string_ CHAR16* FmtW,
                                 ...);
VOID EFIAPI DebugClose();

// clang-format off

#define DBG_ERROR(Format, ...)            DebugPrintFormatted(DEBUG_ERROR,       (CHAR8 *)Format  "\r\n",  __VA_ARGS__)
#define DBG_WARNING(Format, ...)          DebugPrintFormatted(DEBUG_WARNING,     (CHAR8 *)Format  "\r\n",  __VA_ARGS__)
#define DBG_INFO(Format, ...)             DebugPrintFormatted(DEBUG_INFO,        (CHAR8 *)Format  "\r\n",  __VA_ARGS__)
#define DBG_VERBOSE(Format, ...)          DebugPrintFormatted(DEBUG_VERBOSE,     (CHAR8 *)Format  "\r\n",  __VA_ARGS__)

#define DBG_ERROR_U(Format, ...)          DebugPrintFormattedU(DEBUG_ERROR,      (CHAR16 *)Format  L"\r\n", __VA_ARGS__)
#define DBG_WARNING_U(Format, ...)        DebugPrintFormattedU(DEBUG_WARNING,    (CHAR16 *)Format  L"\r\n", __VA_ARGS__)
#define DBG_INFO_U(Format, ...)           DebugPrintFormattedU(DEBUG_INFO,       (CHAR16 *)Format  L"\r\n", __VA_ARGS__)
#define DBG_VERBOSE_U(Format, ...)        DebugPrintFormattedU(DEBUG_VERBOSE,    (CHAR16 *)Format  L"\r\n", __VA_ARGS__)

#define DBG_ERROR_RAW(Format, ...)        DebugPrintFormatted(DEBUG_ERROR,       (CHAR8 *)Format,          __VA_ARGS__)
#define DBG_WARNING_RAW(Format, ...)      DebugPrintFormatted(DEBUG_WARNING,     (CHAR8 *)Format,          __VA_ARGS__)
#define DBG_INFO_RAW(Format, ...)         DebugPrintFormatted(DEBUG_INFO,        (CHAR8 *)Format,          __VA_ARGS__)
#define DBG_VERBOSE_RAW(Format, ...)      DebugPrintFormatted(DEBUG_VERBOSE,     (CHAR8 *)Format,          __VA_ARGS__)

#define DBG_ERROR_RAW_U(Format, ...)      DebugPrintFormattedU(DEBUG_ERROR,      (CHAR16 *)Format,          __VA_ARGS__)
#define DBG_WARNING_RAW_U(Format, ...)    DebugPrintFormattedU(DEBUG_WARNING,    (CHAR16 *)Format,          __VA_ARGS__)
#define DBG_INFO_RAW_U(Format, ...)       DebugPrintFormattedU(DEBUG_INFO,       (CHAR16 *)Format,          __VA_ARGS__)
#define DBG_VERBOSE_RAW_U(Format, ...)    DebugPrintFormattedU(DEBUG_VERBOSE,    (CHAR16 *)Format,          __VA_ARGS__)

#define DBG_CMD_U(str) gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str L"\r\n");
#define DBG_CMD_RAW_U(str) gSystemTable->ConOut->OutputString(gSystemTable->ConOut, str);

// clang-format on

#endif // _DEBUG_H_

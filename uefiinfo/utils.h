#ifndef _UTILS_H_
#define _UTILS_H_
#include "common.h"

#define KB (1024ULL)
#define MB (KB * 1024ULL)
#define GB (MB * 1024ULL)
#define TB (GB * 1024ULL)

#define SEC_TO_DAYS(Sec) ((Sec) / 60 / 60 / 24)

#define NANOSECONDS        1000000000ULL
#define SEC_TO_100_NS(Sec) ((NANOSECONDS * Sec) / 100)

//
//  Time related functions
//

UINT64
TimeDiff(_In_ EFI_TIME* StartTime,
         _In_ EFI_TIME* EndTime,
         _Inout_ UINTN* Hours,
         _Inout_ UINTN* Minutes,
         _Inout_ UINTN* Seconds);

EFI_STATUS
GetTime(_In_ EFI_TIME* Time);
//
//  Size related functions
//

UINT64
PrettySize(_In_ UINT64 Size);

CHAR8* PrettySizeStr(_In_ UINT64 Size);

//
// String functions
//

BOOLEAN
CSVListContains(_In_ const CHAR8* CSVList, _In_ const CHAR8* SearchString);

EFI_STATUS
GetHostArgument(_In_ const CHAR8* HostArguments,
                _In_ const CHAR8* Key,
                _Outptr_result_maybenull_z_ CHAR8** Value);

//
// VM Detection Utils
//

BOOLEAN
IsRunningInVM(VOID);

//
// General Utils
//

VOID HexDump(_In_ PVOID Buffer, _In_ UINTN Length);

//
// Miscellaneous Utils
//

EFI_STATUS
GetLoadedImageFileSummary(_Outptr_result_maybenull_z_ CHAR8** FilePath,
                          _Outptr_result_maybenull_z_ CHAR8** FileSize,
                          _Outptr_result_maybenull_z_ CHAR8** CreatedTime,
                          _Outptr_result_maybenull_z_ CHAR8** LastAccessedTime,
                          _Outptr_result_maybenull_z_ CHAR8** ModifiedTime,
                          _Outptr_result_maybenull_z_ CHAR8** SHA256Hash);

CHAR8* GetCmdArgValue(IN CHAR8* CommandLine, IN CHAR8* ArgName);
#endif // _UTILS_H_

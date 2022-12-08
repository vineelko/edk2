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
TimeDiff(IN EFI_TIME* StartTime,
         IN EFI_TIME* EndTime,
         IN OUT UINTN* Hours,
         IN OUT UINTN* Minutes,
         IN OUT UINTN* Seconds);

EFI_STATUS
GetTime(IN EFI_TIME* Time);
//
//  Size related functions
//

UINT64
PrettySize(IN UINT64 Size);

CHAR8* PrettySizeStr(IN UINT64 Size);

//
// String functions
//

BOOLEAN
CSVListContains(IN const CHAR8* CSVList, IN const CHAR8* SearchString);

EFI_STATUS
GetHostArgument(IN const CHAR8* HostArguments,
                IN const CHAR8* Key,
                OUT CHAR8** Value);

//
// VM Detection Utils
//

BOOLEAN
IsRunningInVM(VOID);

//
// General Utils
//

VOID HexDump(IN PVOID Buffer, IN UINTN Length);

//
// Miscellaneous Utils
//

EFI_STATUS
GetLoadedImageFileSummary(OUT CHAR8** FilePath,
                          OUT CHAR8** FileSize,
                          OUT CHAR8** CreatedTime,
                          OUT CHAR8** LastAccessedTime,
                          OUT CHAR8** ModifiedTime,
                          OUT CHAR8** SHA256Hash);

#endif // _UTILS_H_

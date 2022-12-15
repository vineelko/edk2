/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    utils.c

Abstract:

    This module implements common utility functions

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "utils.h"
#include "common.h"

// #include <mincrypl.h>
#include <strsafe.h>

//
//  Time related functions
//

UINT64
TimeDiff(IN EFI_TIME* StartTime,
         IN EFI_TIME* EndTime,
         IN OUT UINTN* Hours,
         IN OUT UINTN* Minutes,
         IN OUT UINTN* Seconds)
{
    UINT64 Result = 0;
    UINT64 RetResult = 0;

    Result += (EndTime->Hour - StartTime->Hour) * 60 * 60; // * NANOSECONDS;
    Result += (EndTime->Minute - StartTime->Minute) * 60;  // * NANOSECONDS;
    Result += (EndTime->Second - StartTime->Second);       // * NANOSECONDS;
    //    Result += ABS(EndTime->Nanosecond, StartTime->Nanosecond);

    RetResult = Result;
    *Hours = (UINTN)(Result / 3600);
    Result %= 3600;
    *Minutes = (UINTN)(Result / 60);
    Result %= 60;
    *Seconds = (UINTN)Result;
    return RetResult;
}

EFI_STATUS
GetTime(IN EFI_TIME* Time)
{
    EFI_STATUS Status = EFI_SUCCESS;

    Status = gRT->GetTime(Time, NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("GetTime() failed : %a(0x%x)", E(Status), Status);
    }

    return Status;
}

//
//  Size related functions
//

UINT64
PrettySize(IN UINT64 Size)
{
    if (Size > TB)
        return Size / TB;
    else if (Size > GB)
        return Size / GB;
    else if (Size > MB)
        return Size / MB;
    else if (Size > KB)
        return Size / KB;
    return Size;
}

CHAR8* PrettySizeStr(IN UINT64 Size)
{
    static CHAR8* Str[5] = {
        t("Bytes"),
        t("KB"),
        t("MB"),
        t("GB"),
        t("TB"),
    };

    if (Size > TB)
        return Str[4];
    else if (Size > GB)
        return Str[3];
    else if (Size > MB)
        return Str[2];
    else if (Size > KB)
        return Str[1];
    return Str[0];
}

//
// String functions
//

EFI_STATUS
GetHostArgument(IN const CHAR8* HostArguments, IN const CHAR8* Key, OUT CHAR8** Value)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN Length = 0;
    CHAR8* Found = NULL;
    CHAR8* Key2 = NULL;
    CHAR8* RetValue = NULL;
    UINTN ValueLength = 0;

    if (HostArguments == NULL || Key == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    *Value = NULL;

    Length = AsciiStrLen(Key);
    Key2 = AllocateZeroPool(sizeof(CHAR8) * (Length + 2)); // include =
    if (Key2 == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  sizeof(CHAR8) * (Length + 2));
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    AsciiSPrint(Key2, Length + 2, (CHAR8*)"%a=", Key); // append =

    Found = AsciiStrStr(HostArguments, Key2);
    if (Found == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    Found += Length + 1; // skip over =
    for (CHAR8* Ptr = Found; *Ptr != 0 && *Ptr != ';'; Ptr++) {
        ValueLength++;
    }

    RetValue = AllocateZeroPool(sizeof(CHAR8) * (ValueLength + 1));
    if (RetValue == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
                  sizeof(CHAR8) * (ValueLength + 1));
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    CopyMem(RetValue, Found, ValueLength);
    RetValue[ValueLength + 1] = 0;
    *Value = RetValue;
Exit:
    FreePool(Key2);
    return Status;
}

//
// General Utils
//

VOID HexDump(IN VOID* Buffer, IN UINTN Length)
{
    CHAR8* Byte = Buffer;
    UINTN Index = 0;
    UINTN Remaining = Length;
    UINTN ByteIndex = 0;
    UINTN LineLength = 0;

    //
    // Skip any non printable characters. Also sanitize (<,>,&,',") to make XML
    // parsing sane!
    //

#define PRINTABLE(x)                                                                         \
    (((x) < 0x20 || (x) >= 0x7F) || (x) == '<' || (x) == '>' || (x) == '&' || (x) == '\'' || \
             (x) == '"' ?                                                                    \
         '.' :                                                                               \
         x)
    while (Remaining > 0) {
        ByteIndex = 0;
        LineLength = MIN(16, Remaining);

        for (ByteIndex = 0; ByteIndex < LineLength; ByteIndex++) {
            DBG_INFO_RAW("%02x ", Byte[Index + ByteIndex] & 0xff);
        }

        for (; ByteIndex < 16; ByteIndex++) {
            DBG_INFO_RAW("   ");
        }

        DBG_INFO_RAW("|");

        for (ByteIndex = 0; ByteIndex < LineLength; ByteIndex++) {
            DBG_INFO_RAW("%1c", PRINTABLE(Byte[Index + ByteIndex]));
        }

        for (; ByteIndex < 16; ByteIndex++) {
            DBG_INFO_RAW(".");
        }

        DBG_INFO_RAW("|\n");

        Remaining -= LineLength;
        Index += LineLength;
    }
#undef PRINTABLE
}

//
// Miscellaneous Utils
//

// EFI_STATUS
// GetLoadedImageFileSummary(OUT CHAR8** FilePath,
//                             OUT CHAR8** FileSize,
//                             OUT CHAR8** CreatedTime,
//                             OUT CHAR8** LastAccessedTime,
//                             OUT CHAR8** ModifiedTime,
//                             OUT CHAR8** SHA256Hash)
// {
//     UINT8 CalculatedHash[RTL_MAX_HASH_LEN_V2] = {0};
//     CHAR16* BinaryFilePath = NULL;
//     CHAR8* FileBuffer = NULL;
//     CRYPT_DER_BLOB Blobs[1] = {0};
//     EFI_DEVICE_PATH_TO_TEXT_PROTOCOL* ToTextPath = NULL;
//     EFI_FILE_INFO* FileInfo = NULL;
//     EFI_FILE_PROTOCOL* LoadedImageFile = NULL;
//     EFI_FILE_PROTOCOL* Root = NULL;
//     EFI_LOADED_IMAGE* LoadedImage = NULL;
//     EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* SimpleFileSystem = NULL;
//     EFI_STATUS Status = EFI_SUCCESS;
//     HRESULT Hr = S_OK;
//     NTSTATUS NtStatus;
//     UINTN FileBufferSize = 0;
//     UINTN FileInfoSize = 0;
//     ULONG HashSize = 0;
//     UINTN Length = 0;
//     CHAR8* RetFilePath = NULL;
//     CHAR8* RetFileSize = NULL;
//     CHAR8* RetCreatedTime = NULL;
//     CHAR8* RetLastAccessedTime = NULL;
//     CHAR8* RetModifiedTime = NULL;
//     CHAR8* RetSHA256Hash = NULL;

// #define MAX_FILE_SUMMARY_FIELD_SIZE 256

//     *FilePath = NULL;
//     *FileSize = NULL;
//     *CreatedTime = NULL;
//     *LastAccessedTime = NULL;
//     *ModifiedTime = NULL;
//     *SHA256Hash = NULL;

//     //
//     // Open the currently loaded image file
//     //

//     Status = gBS->HandleProtocol(gImageHandle, &gEfiLoadedImageProtocolGuid,
//     (void**)&LoadedImage); if (EFI_ERROR(Status)) {
//         DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     // Open SIMPLE_FILE_SYSTEM_PROTOCOL for the volume from which the
//     // current image is loaded
//     Status = gBS->HandleProtocol(LoadedImage->DeviceHandle,
//                                  &gEfiSimpleFileSystemProtocolGuid,
//                                  (void**)&SimpleFileSystem);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR("HandleProtocol() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     Status = SimpleFileSystem->OpenVolume(SimpleFileSystem, &Root);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR("OpenVolume() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     Status = gBS->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (VOID**)&ToTextPath);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR("LocateProtocol() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     BinaryFilePath = ToTextPath->ConvertDevicePathToText(LoadedImage->FilePath, FALSE, FALSE);
//     if (BinaryFilePath == NULL) {
//         DBG_ERROR("BinaryFilePath is null");
//         goto Exit;
//     }

//     Status = Root->Open(Root, &LoadedImageFile, BinaryFilePath, EFI_FILE_MODE_READ, 0);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR_U(L"Open() failed : for %s = %S(0x%x)", BinaryFilePath, E(Status), Status);
//         goto Exit;
//     }

//     //
//     // Read file attributes
//     //

//     Status = LoadedImageFile->GetInfo(LoadedImageFile,
//                                       &(EFI_GUID)EFI_FILE_INFO_ID,
//                                       &FileInfoSize,
//                                       FileInfo);
//     if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
//         DBG_ERROR("GetInfo() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     FileInfo = AllocateZeroPool(FileInfoSize);
//     if (FileInfo == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", FileInfoSize);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Status = LoadedImageFile->GetInfo(LoadedImageFile,
//                                       &(EFI_GUID)EFI_FILE_INFO_ID,
//                                       &FileInfoSize,
//                                       FileInfo);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR("GetInfo() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     //
//     // Write down file summary
//     //

//     Length = StrLen(BinaryFilePath);
//     RetFilePath = AllocateZeroPool(sizeof(CHAR8) * (Length + 1));
//     if (RetFilePath == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   sizeof(CHAR8) * (Length + 1));
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     UnicodeStrToAsciiStrS(BinaryFilePath, RetFilePath, Length + 1);

//     RetFileSize = AllocateZeroPool(MAX_FILE_SUMMARY_FIELD_SIZE);
//     if (RetFileSize == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   MAX_FILE_SUMMARY_FIELD_SIZE);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Hr = AsciiSPrint(RetFileSize,
//                           MAX_FILE_SUMMARY_FIELD_SIZE,
//                            "%llu bytes",
//                           FileInfo->FileSize);
//     if (FAILED(Hr)) {
//         DBG_ERROR("AsciiSPrint failed 0x%x", Hr);
//         Status = EFI_INVALID_PARAMETER;
//         goto Exit;
//     }

//     RetCreatedTime = AllocateZeroPool(MAX_FILE_SUMMARY_FIELD_SIZE);
//     if (RetCreatedTime == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   MAX_FILE_SUMMARY_FIELD_SIZE);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Hr = AsciiSPrint(RetCreatedTime,
//                           MAX_FILE_SUMMARY_FIELD_SIZE,
//                            "%02u/%02u/%02u %02u:%02u:%02u",
//                           FileInfo->CreateTime.Month,
//                           FileInfo->CreateTime.Day,
//                           (UINT16)(FileInfo->CreateTime.Year % 100),
//                           FileInfo->CreateTime.Hour,
//                           FileInfo->CreateTime.Minute,
//                           FileInfo->CreateTime.Second);
//     if (FAILED(Hr)) {
//         DBG_ERROR("AsciiSPrint failed 0x%x", Hr);
//         Status = EFI_INVALID_PARAMETER;
//         goto Exit;
//     }

//     RetLastAccessedTime = AllocateZeroPool(MAX_FILE_SUMMARY_FIELD_SIZE);
//     if (RetLastAccessedTime == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   MAX_FILE_SUMMARY_FIELD_SIZE);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Hr = AsciiSPrint(RetLastAccessedTime,
//                           MAX_FILE_SUMMARY_FIELD_SIZE,
//                            "%02u/%02u/%02u %02u:%02u:%02u",
//                           FileInfo->LastAccessTime.Month,
//                           FileInfo->LastAccessTime.Day,
//                           (UINT16)(FileInfo->LastAccessTime.Year % 100),
//                           FileInfo->LastAccessTime.Hour,
//                           FileInfo->LastAccessTime.Minute,
//                           FileInfo->LastAccessTime.Second);
//     if (FAILED(Hr)) {
//         DBG_ERROR("AsciiSPrint failed 0x%x", Hr);
//         Status = EFI_INVALID_PARAMETER;
//         goto Exit;
//     }

//     RetModifiedTime = AllocateZeroPool(MAX_FILE_SUMMARY_FIELD_SIZE);
//     if (RetModifiedTime == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   MAX_FILE_SUMMARY_FIELD_SIZE);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Hr = AsciiSPrint(RetModifiedTime,
//                           MAX_FILE_SUMMARY_FIELD_SIZE,
//                            "%02u/%02u/%02u %02u:%02u:%02u",
//                           FileInfo->ModificationTime.Month,
//                           FileInfo->ModificationTime.Day,
//                           (UINT16)(FileInfo->ModificationTime.Year % 100),
//                           FileInfo->ModificationTime.Hour,
//                           FileInfo->ModificationTime.Minute,
//                           FileInfo->ModificationTime.Second);
//     if (FAILED(Hr)) {
//         DBG_ERROR("AsciiSPrint failed 0x%x", Hr);
//         Status = EFI_INVALID_PARAMETER;
//         goto Exit;
//     }

//     //
//     // Read file content to buffer to Mincrypt hash
//     //

//     FileBufferSize = (UINTN)FileInfo->FileSize;
//     FileBuffer = AllocateZeroPool(FileBufferSize);
//     if (FileBuffer == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", FileBufferSize);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     Status = LoadedImageFile->Read(LoadedImageFile, &FileBufferSize, FileBuffer);
//     if (EFI_ERROR(Status)) {
//         DBG_ERROR("Read() failed : %a(0x%x)", E(Status), Status);
//         goto Exit;
//     }

//     //
//     // Calculate SHA256 hash of the loaded image from disk
//     //

//     Blobs[0].pbData = FileBuffer;
//     Blobs[0].cbData = (ULONG)FileBufferSize;

//     NtStatus = MinCrypL_HashMemory(CALG_SHA_256, 1, Blobs, CalculatedHash, &HashSize);
//     if (!NT_SUCCESS(NtStatus)) {
//         DBG_ERROR("MinCrypL_HashMemory() failed 0x%x", NtStatus);
//         Status = EFI_INVALID_PARAMETER;
//         goto Exit;
//     }

//     //
//     // Write SHA256 hash to file summary
//     //

//     RetSHA256Hash = AllocateZeroPool(MAX_FILE_SUMMARY_FIELD_SIZE);
//     if (RetSHA256Hash == NULL) {
//         DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d",
//                   MAX_FILE_SUMMARY_FIELD_SIZE);
//         Status = EFI_OUT_OF_RESOURCES;
//         goto Exit;
//     }

//     for (UINTN i = 0; i < HashSize; i++) {
//         Hr = AsciiSPrint(&RetSHA256Hash[2 * i],
//                               MAX_FILE_SUMMARY_FIELD_SIZE,
//                                "%02x",
//                               CalculatedHash[i] & 0xff);
//         if (FAILED(Hr)) {
//             DBG_ERROR("AsciiSPrint failed 0x%x", Hr);
//             Status = EFI_INVALID_PARAMETER;
//             goto Exit;
//         }
//     }

//     //
//     // Success
//     //

//     *FilePath = RetFilePath;
//     *FileSize = RetFileSize;
//     *CreatedTime = RetCreatedTime;
//     *LastAccessedTime = RetLastAccessedTime;
//     *ModifiedTime = RetModifiedTime;
//     *SHA256Hash = RetSHA256Hash;

// Exit:
//     FreePool(BinaryFilePath);
//     FreePool(FileInfo);
//     FreePool(FileBuffer);

//     if (EFI_ERROR(Status)) {
//         FreePool(RetFilePath);
//         FreePool(RetFileSize);
//         FreePool(RetCreatedTime);
//         FreePool(RetLastAccessedTime);
//         FreePool(RetModifiedTime);
//         FreePool(RetSHA256Hash);
//     }

//     return Status;
// }

//
// VM detection utils
//

static CHAR8* StringByIndex(IN CHAR8* StartAddrPtr, IN UINT8 StringIndex)
{
    CHAR8* StringPtr = StartAddrPtr;
    UINT8 Index = 1;
    UINTN StringLength = 0;

    if (StartAddrPtr == NULL) {
        DBG_ERROR("Invalid pcStartAddrPtr: 0x%p", StartAddrPtr);
        return NULL;
    }

    if (StringIndex == 0) {
        DBG_ERROR("Invalid StringIndex: %u", StringIndex);
        return NULL;
    }

    while (Index < StringIndex) {
#pragma prefast(push)
#pragma prefast(disable : 26018)
#pragma prefast(disable : 26007)
        if (*StringPtr == 0 && *(StringPtr + 1) == 0) {
            DBG_ERROR("Structure terminator found while searching index %u", Index);
            return NULL;
        }
#pragma prefast(pop)

        StringLength = AsciiStrLen(StringPtr) + 1;
        StringPtr += StringLength;
        Index++;
    }

    return StringPtr;
}

BOOLEAN
IsRunningInVM(VOID)
{
    static BOOLEAN IsRunningInVM = FALSE;

    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SMBIOS_PROTOCOL* SmbiosProtocol = NULL;
    EFI_SMBIOS_HANDLE SmbiosHandle = 0;
    EFI_SMBIOS_TYPE SmbiosType = EFI_SMBIOS_TYPE_SYSTEM_INFORMATION;
    SMBIOS_TABLE_TYPE1* SmbiosTableType1Ptr = NULL;
    CHAR8* StringPtr = NULL;
    CHAR8* ProductName = NULL;
    CHAR8* Version = NULL;
    CHAR8* Family = NULL;

    if (IsRunningInVM == TRUE) {
        return IsRunningInVM;
    }

    Status = gBS->LocateProtocol(&gEfiSmbiosProtocolGuid, NULL, (VOID**)&SmbiosProtocol);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("LocateProtocol() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    Status = SmbiosProtocol->GetNext(SmbiosProtocol,
                                     &SmbiosHandle,
                                     &SmbiosType,
                                     (EFI_SMBIOS_TABLE_HEADER**)&SmbiosTableType1Ptr,
                                     NULL);
    if (EFI_ERROR(Status)) {
        DBG_ERROR("Smbios GetNext() failed : %a(0x%x)", E(Status), Status);
        goto Exit;
    }

    StringPtr = ((CHAR8*)SmbiosTableType1Ptr) + SmbiosTableType1Ptr->Hdr.Length;

    ProductName = StringByIndex(StringPtr, SmbiosTableType1Ptr->ProductName);
    Version = StringByIndex(StringPtr, SmbiosTableType1Ptr->Version);
    Family = StringByIndex(StringPtr, SmbiosTableType1Ptr->Family);

    if (AsciiStrStr(ProductName, t("Virtual Machine")) != NULL ||
        AsciiStrStr(Version, t("Hyper-V")) != NULL ||
        AsciiStrStr(Family, t("Virtual Machine")) != NULL) {
        IsRunningInVM = TRUE;
    }

Exit:
    return IsRunningInVM;
}

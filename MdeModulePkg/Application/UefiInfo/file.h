#ifndef _FILE_H_
#define _FILE_H_

#include "common.h"

#define FILE_OFFSET_EOF           0xFFFFFFFFFFFFFFFF
#define MAX_PARTITION_NAME_LENGTH 36

#define DPP_PARTITION_NAME              L"DPP"
#define OPP_PARTITION_NAME              L"OPP"
#define WINDOWS_SYSTEM_PARTITION_NAME   L"EFIESP"
#define BOOTSTRAP_EFIESP_PARTITION_NAME L"BS_EFIESP"

#ifndef UEFI_BUILD_SYSTEM
// #if defined(_X86_) // TODO: Handle below arch specific cases more appropriately [Sources.ARCH] in
// inf #define BOOTMGR_NAME       L"bootia32.efi" #define BOOTMGR_NAME_ASCII "bootia32.efi" #elif
// defined(_AMD64_)
#define BOOTMGR_NAME       L"bootx64.efi"
#define BOOTMGR_NAME_ASCII "bootx64.efi"
// #elif defined(_ARM_)
// #define BOOTMGR_NAME       L"bootarm.efi"
// #define BOOTMGR_NAME_ASCII "bootarm.efi"
// #elif defined(_ARM64_)
// #define BOOTMGR_NAME       L"bootaa64.efi"
// #define BOOTMGR_NAME_ASCII "bootaa64.efi"
// #else
// #error Architecture not supported.
// #endif
#endif

#define BOOTMGR_PATH       L"\\EFI\\Boot\\" BOOTMGR_NAME
#define BOOTMGR_PATH_ASCII "\\EFI\\Boot\\" BOOTMGR_NAME_ASCII

EFI_STATUS EFIAPI FileOpen(IN CHAR16* PartitionName,
                           IN CHAR16* FileName,
                           IN UINT64 OpenMode,
                           IN UINT64 Attributes,
                           OUT EFI_FILE_PROTOCOL** EfiFileProtocol);
EFI_STATUS EFIAPI FileOpenEx(IN EFI_FILE_PROTOCOL* Directory,
                             IN CHAR16* FileName,
                             IN UINT64 OpenMode,
                             IN UINT64 Attributes,
                             OUT EFI_FILE_PROTOCOL** EfiFileProtocol);
EFI_STATUS EFIAPI FileClose(IN EFI_FILE_PROTOCOL* EfiFileProtocol);
EFI_STATUS EFIAPI FileDelete(IN EFI_FILE_PROTOCOL* EfiFileProtocol);
EFI_STATUS EFIAPI FileRead(IN EFI_FILE_PROTOCOL* EfiFileProtocol,
                           IN OUT UINTN* ReadSize,
                           OUT UINT8* OutBuf);
EFI_STATUS EFIAPI FileReadLine(IN EFI_FILE_PROTOCOL* EfiFileProtocol,
                               IN OUT UINTN* ReadSize,
                               OUT CHAR8* OutBuf,
                               OUT BOOLEAN* EndOfFile);
EFI_STATUS EFIAPI FileWrite(IN EFI_FILE_PROTOCOL* EfiFileProtocol,
                            IN UINTN* BufferSize,
                            IN VOID* Buffer);
EFI_STATUS EFIAPI FileSetPosition(IN EFI_FILE_PROTOCOL* EfiFileProtocol, IN UINT64 Position);
EFI_STATUS EFIAPI FileGetPosition(IN EFI_FILE_PROTOCOL* EfiFileProtocol, OUT UINT64* Position);
EFI_STATUS EFIAPI FileGetInfo(IN EFI_FILE_PROTOCOL* EfiFileProtocol, OUT EFI_FILE_INFO** FileInfo);
EFI_STATUS EFIAPI FileGetFileSystemInfo(IN EFI_FILE_PROTOCOL* EfiFileProtocol,
                                        OUT EFI_FILE_SYSTEM_INFO** FileInfo);
EFI_STATUS EFIAPI FileSetInfo(IN EFI_FILE_PROTOCOL* EfiFileProtocol, IN EFI_FILE_INFO* FileInfo);
EFI_STATUS EFIAPI FileFlush(IN EFI_FILE_PROTOCOL* EfiFileProtocol);

EFI_STATUS EFIAPI FileGetSize(IN EFI_FILE_PROTOCOL* EfiFileProtocol, OUT UINT64* FileSize);
EFI_STATUS EFIAPI FileSetSize(IN EFI_FILE_PROTOCOL* EfiFileProtocol, IN UINT64 FileSize);
EFI_STATUS EFIAPI FileGetFreeSpace(IN EFI_FILE_PROTOCOL* EfiFileProtocol, OUT UINT64* FreeSpace);
EFI_STATUS EFIAPI FileGetVolumeSize(IN EFI_FILE_PROTOCOL* EfiFileProtocol, OUT UINT64* VolumeSize);

EFI_STATUS EFIAPI FileDoesPartitionExist(IN CHAR16* PartitionName, OUT BOOLEAN* IsExist);

EFI_STATUS EFIAPI FileGetSizeEx(IN CHAR16* PartitionName,
                                IN CHAR16* FileName,
                                OUT UINT64* FileSize);
EFI_STATUS EFIAPI FileGetDirEntriesSize(IN CHAR16* PartitionName,
                                        IN CHAR16* DirectoryName,
                                        OUT UINT64* DirectorySize);
EFI_STATUS EFIAPI FileGetDirEntriesSizeEx(IN EFI_FILE_PROTOCOL* Directory,
                                          OUT UINT64* DirectorySize);
EFI_STATUS EFIAPI FileGetDirEntries(IN CHAR16* PartitionName,
                                    IN CHAR16* DirectoryName,
                                    IN OUT UINT32* ReadSize,
                                    OUT UINT8* OutBuf,
                                    IN UINT64 Position);
EFI_STATUS EFIAPI FileGetDirEntriesEx(IN EFI_FILE_PROTOCOL* Directory,
                                      IN OUT UINT32* ReadSize,
                                      OUT UINT8* OutBuf,
                                      IN UINT64 Position);
EFI_STATUS EFIAPI FileReadEx(IN CHAR16* PartitionName,
                             IN CHAR16* FileName,
                             IN OUT UINT32* ReadSize,
                             OUT UINT8* OutBuf,
                             IN UINT64 Position);
EFI_STATUS EFIAPI FileWriteEx(IN CHAR16* PartitionName,
                              IN CHAR16* FileName,
                              IN OUT UINT32* WriteSize,
                              IN VOID* InBuf,
                              IN UINT64 Position,
                              IN BOOLEAN Overwrite);
EFI_STATUS EFIAPI FileGetSfsVolumes(OUT EFI_FILE_PROTOCOL*** SfsVolumes,
                                    OUT UINTN* VolumeCount,
                                    IN EFI_HANDLE** VolumeHandles,
                                    IN BOOLEAN RemovableOnly);
EFI_STATUS EFIAPI FileGetDevicePath(IN CHAR16* PartitionName,
                                    IN CHAR16* FileName,
                                    OUT EFI_DEVICE_PATH_PROTOCOL** DevicePathProtocol);
EFI_STATUS EFIAPI FileLocateAndOpen(IN CHAR16* FileName,
                                    IN UINT64 OpenMode,
                                    OUT EFI_FILE_PROTOCOL** EfiFileProtocol);
EFI_STATUS EFIAPI FileCreateSubdirectories(IN CHAR16* PartitionName,
                                           IN CHAR16* DirectoryPath,
                                           IN UINTN DirectoryPathLength,
                                           OUT EFI_FILE_PROTOCOL** EfiFileProtocol);
EFI_STATUS EFIAPI FileCreateSubdirectoriesAndFile(IN CHAR16* PartitionName,
                                                  IN CHAR16* FileName,
                                                  OUT EFI_FILE_PROTOCOL** EfiFileProtocol);
EFI_STATUS EFIAPI FileDuplicate(IN EFI_FILE_PROTOCOL* SourceFile,
                                IN UINTN SourceOffset,
                                IN UINTN ByteCount,
                                IN CHAR16* PartitionName,
                                IN CHAR16* DestinationFilePath,
                                OUT EFI_FILE_PROTOCOL** DestinationFile);
EFI_STATUS EFIAPI FileFindFirst(IN EFI_FILE_PROTOCOL* Directory);
EFI_STATUS EFIAPI FileFindNext(IN EFI_FILE_PROTOCOL* Directory, OUT EFI_FILE_INFO** FileInfo);
EFI_STATUS EFIAPI FileCreateDirectory(IN EFI_FILE_PROTOCOL* DestDirectory,
                                      IN CHAR16* DirectoryName);
EFI_STATUS EFIAPI FileCopy(IN EFI_FILE_PROTOCOL* Source, IN EFI_FILE_PROTOCOL* Destination);

#endif // _FILE_H_

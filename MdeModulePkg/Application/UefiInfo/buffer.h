#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "common.h"

typedef struct _BUFFER BUFFER;

EFI_STATUS EFIAPI BufferCreate(IN UINT32 Capacity, OUT BUFFER** Buffer);
EFI_STATUS EFIAPI BufferAppendContent(IN BUFFER* Buffer, IN PVOID Content, IN UINT32 Size);
PVOID EFIAPI BufferGetContent(IN BUFFER* Buffer);
UINT32 EFIAPI BufferGetSize(IN BUFFER* Buffer);
VOID EFIAPI BufferSetSize(IN BUFFER* Buffer, IN UINT32 Size);
UINT32 EFIAPI BufferGetCapacity(IN BUFFER* Buffer);
EFI_STATUS EFIAPI BufferEnsureCapacity(IN BUFFER* Buffer, IN UINT32 NewCapacity);
VOID EFIAPI BufferClear(IN BUFFER* Buffer);
VOID EFIAPI BufferFree(IN BUFFER* Buffer);

#endif // _BUFFER_H_

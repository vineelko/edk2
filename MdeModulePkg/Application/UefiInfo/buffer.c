#include "buffer.h"

typedef struct _BUFFER {
    VOID* Content;
    UINT32 Capacity;
    UINT32 Size;
} BUFFER, *PBUFFER;

EFI_STATUS EFIAPI BufferCreate(IN UINT32 Capacity, OUT BUFFER** Buffer)
{
    BUFFER* RetBuffer = NULL;

    RetBuffer = AllocateZeroPool(sizeof(BUFFER));
    if (!RetBuffer) {
        return EFI_OUT_OF_RESOURCES;
    }

    RetBuffer->Size = 0;
    RetBuffer->Capacity = Capacity;
    RetBuffer->Content = AllocateZeroPool(Capacity);
    if (!RetBuffer->Content) {
        FreePool(RetBuffer);
        return EFI_OUT_OF_RESOURCES;
    }

    *Buffer = RetBuffer;
    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI BufferAppendContent(IN BUFFER* Buffer, IN VOID* Content, IN UINT32 Size)
{
    EFI_STATUS Status = EFI_SUCCESS;

    Status = BufferEnsureCapacity(Buffer, Buffer->Size + Size);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    CopyMem((CHAR8*)(Buffer->Content) + Buffer->Size, Content, Size);
    Buffer->Size += Size;
    return Status;
}

VOID* EFIAPI BufferGetContent(IN BUFFER* Buffer)
{
    return Buffer->Content;
}

UINT32 EFIAPI BufferGetSize(IN BUFFER* Buffer)
{
    return Buffer->Size;
}

VOID EFIAPI BufferSetSize(IN BUFFER* Buffer, IN UINT32 Size)
{
    Buffer->Size = Size;
}

UINT32 EFIAPI BufferGetCapacity(IN BUFFER* Buffer)
{
    return Buffer->Capacity;
}

EFI_STATUS EFIAPI BufferEnsureCapacity(IN BUFFER* Buffer, IN UINT32 NewCapacity)
{
    VOID* NewBuffer = NULL;

    if (Buffer->Capacity >= NewCapacity) {
        return EFI_SUCCESS;
    }

    NewBuffer = ReallocatePool(Buffer->Size, NewCapacity, Buffer->Content);
    if (NewBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Buffer->Content = NewBuffer;
    Buffer->Capacity = NewCapacity;

    return EFI_SUCCESS;
}

VOID EFIAPI BufferClear(IN BUFFER* Buffer)
{
    Buffer->Size = 0;
}

VOID EFIAPI BufferFree(IN BUFFER* Buffer)
{
    if (Buffer != NULL) {
        FreePool(Buffer->Content);
        FreePool(Buffer);
    }
}

#include "buffer.h"

typedef struct _BUFFER {
    PVOID Content;
    UINT32 Capacity;
    UINT32 Size;
} BUFFER, *PBUFFER;

EFI_STATUS EFIAPI BufferCreate(_In_ UINT32 Capacity, _Outptr_ BUFFER** Buffer)
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

EFI_STATUS EFIAPI BufferAppendContent(_In_ BUFFER* Buffer, _In_ PVOID Content, _In_ UINT32 Size)
{
    EFI_STATUS EfiStatus = EFI_SUCCESS;

    EfiStatus = BufferEnsureCapacity(Buffer, Buffer->Size + Size);
    if (EFI_ERROR(EfiStatus)) {
        return EfiStatus;
    }

    CopyMem((CHAR8*)(Buffer->Content) + Buffer->Size, Content, Size);
    Buffer->Size += Size;
    return EfiStatus;
}

PVOID EFIAPI BufferGetContent(_In_ BUFFER* Buffer)
{
    return Buffer->Content;
}

UINT32 EFIAPI BufferGetSize(_In_ BUFFER* Buffer)
{
    return Buffer->Size;
}

VOID EFIAPI BufferSetSize(_In_ BUFFER* Buffer, _In_ UINT32 Size)
{
    Buffer->Size = Size;
}

UINT32 EFIAPI BufferGetCapacity(_In_ BUFFER* Buffer)
{
    return Buffer->Capacity;
}

EFI_STATUS EFIAPI BufferEnsureCapacity(_In_ BUFFER* Buffer, _In_ UINT32 NewCapacity)
{
    VOID* NewBuffer = NULL;

    if (Buffer->Capacity >= NewCapacity) {
        return EFI_SUCCESS;
    }

    NewBuffer = ReallocatePool(Buffer->Content, Buffer->Size, NewCapacity);
    if (NewBuffer == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }

    Buffer->Content = NewBuffer;
    Buffer->Capacity = NewCapacity;

    return EFI_SUCCESS;
}

VOID EFIAPI BufferClear(_In_ BUFFER* Buffer)
{
    Buffer->Size = 0;
}

VOID EFIAPI BufferFree(_In_ BUFFER* Buffer)
{
    if (Buffer != NULL) {
        FreePool(Buffer->Content);
        FreePool(Buffer);
    }
}

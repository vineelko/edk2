/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    tshash2.c

Abstract:

    This module implements hash2 test suite

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "common.h"

#include "protocols.h"
#include "testsuites.h"

#include "utils.h"
#include <mincrypl.h>

typedef enum _HASH_ALGORITHM_ID {
    HASH_ALGORITHM_MD5,
    HASH_ALGORITHM_SHA1,
    HASH_ALGORITHM_SHA224,
    HASH_ALGORITHM_SHA256,
    HASH_ALGORITHM_SHA384,
    HASH_ALGORITHM_SHA512,
    //    HASH_ALGORITHM_SHA1_NOPAD,
    //    HASH_ALGORITHM_SHA256_NOPAD,
} HASH_ALGORITHM_ID;

typedef struct _HASH_ALGORITHM {
    HASH_ALGORITHM_ID Id;
    EFI_GUID* Guid;
    CHAR8* Name;

    //
    // Below is the expected hash when a 512 block of 0xFE is hashed.
    // At max the hash will be 64 bytes long for SHA256
    //

    UINT8 ExpectedHash[64];

} HASH_ALGORITHM;

static HASH_ALGORITHM HashAlgorithmsMap[] = {
    {HASH_ALGORITHM_SHA256,
     &gEfiHashAlgorithmSha256Guid,
     t("SHA256"),
     {0x34, 0x11, 0xbf, 0xb1, 0xda, 0x2c, 0x50, 0x89, 0xd0, 0xb3, 0x08,
      0x63, 0x0a, 0x90, 0x2f, 0xf5, 0xc0, 0x09, 0xb4, 0x38, 0xa7, 0xdc,
      0xfb, 0x13, 0xc6, 0xdf, 0xb7, 0x7e, 0x2c, 0x28, 0xbe, 0x60}},

//
// Blocking below Hash algorithms for now to reduce noise in the output, And
// also we only use SHA256 in efiflash
//

#if 0
    {HASH_ALGORITHM_MD5, EFI_HASH_ALGORITHM_MD5_GUID, t("MD5"), {0x4d, 0x02, 0xf9, 0x03, 0x19, 0x0f, 0x88, 0x66, 0xce, 0xae, 0x6a, 0x8f, 0xc3, 0x1f, 0xc6, 0xd6}},
    {HASH_ALGORITHM_SHA1, EFI_HASH_ALGORITHM_SHA1_GUID, t("SHA1"), {0x7a, 0x3e, 0x63, 0x70, 0x44, 0x11, 0x73, 0xb6, 0x28, 0x92, 0xb0, 0xf5, 0x2e, 0xf3, 0x8d, 0x60, 0x13, 0x9a, 0x75, 0xe4}},
    {HASH_ALGORITHM_SHA224, EFI_HASH_ALGORITHM_SHA224_GUID, t("SHA224"), {0xf8, 0x8a, 0x94, 0xbb, 0x5c, 0xb3, 0x2f, 0x16, 0xbf, 0xe8, 0x46, 0x12, 0xb7, 0x0b, 0x90, 0xf7, 0xb9, 0x1a, 0x98, 0x78, 0x94, 0xb9, 0x24, 0x96, 0xfd, 0x43, 0xb9, 0x40}},
    {HASH_ALGORITHM_SHA384, EFI_HASH_ALGORITHM_SHA384_GUID, t("SHA384"), {0xa6, 0xbe, 0x95, 0xfc, 0xa2, 0x77, 0x03, 0xc1, 0x1f, 0xcc, 0x50, 0x71, 0xfc, 0x9a, 0xe5, 0xa4, 0x84, 0x82, 0x3c, 0xdc, 0xa4, 0x2e, 0x27, 0xa0, 0xd2, 0x6e, 0x56, 0xb6, 0x2a, 0xe1, 0x87, 0x18, 0x10, 0xdf, 0xda, 0x53, 0x7a, 0xe5, 0x9c, 0x26, 0x0c, 0x2d, 0x45, 0x9b, 0xc7, 0x6e, 0xe0, 0x6a}},
    {HASH_ALGORITHM_SHA512, EFI_HASH_ALGORITHM_SHA512_GUID, t("SHA512"), {0x8c, 0xe9, 0x79, 0x6e, 0xca, 0x37, 0xd6, 0x01, 0x82, 0xfd, 0x33, 0x72, 0x7d, 0x80, 0xb2, 0xc3, 0x2e, 0xfe, 0xb9, 0xd5, 0xb0, 0x93, 0xa1, 0xa0, 0xb5, 0x95, 0x46, 0x04, 0xf6, 0xf3, 0xaf, 0xf9, 0xa8, 0xed, 0x90, 0xc1, 0xa9, 0x1a, 0x8f, 0x33, 0x9c, 0x1e, 0xf7, 0x64, 0x96, 0x68, 0xff, 0x1e, 0xed, 0x8e, 0xc6, 0x7a, 0xdd, 0x62, 0xc2, 0x94, 0x21, 0xab, 0xf9, 0x08, 0x0f, 0xaa, 0xe7, 0x6f}},
    {HASH_ALGORITHM_SHA1_NOPAD, EFI_HASH_ALGORITHM_SHA1_NOPAD_GUID, t("SHA1_NOPAD")},
    {HASH_ALGORITHM_SHA256_NOPAD, EFI_HASH_ALGORITHM_SHA256_NOPAD_GUID, t("SHA256_NOPAD")},
#endif
};

#define HASH_INPUT_SIZE 512

static EFI_STATUS HashEquals(_In_reads_(Size) UINT8* Input,
                             _In_reads_(Size) UINT8* Expected,
                             _In_ UINTN Size)
{
    for (UINTN i = 0; i < Size; i++) {
        if (Input[i] != Expected[i]) {
            return EFI_INVALID_PARAMETER;
        }
    }

    return EFI_SUCCESS;
}

static EFI_STATUS HashProbe(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HASH_PROTOCOL* HashProtocol = NULL;
    EFI_HASH2_PROTOCOL* Hash2Protocol = NULL;
    UINT8* Input = NULL;
    EFI_HASH_OUTPUT Output = {0};
    EFI_HASH2_OUTPUT Output2 = {0};
    BOOLEAN HashAlgorithmsSupported = FALSE;
    BYTE HashBuffer[128] = {0};

    UNREFERENCED_PARAMETER(Session);

    //
    // Validate Hash 1 support
    //

    Status = ProtocolArray[EFI_HASH_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HASH_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    HashProtocol = (EFI_HASH_PROTOCOL*)ProtocolArray[EFI_HASH_PROTOCOL_INDEX].Protocol;
    Input = AllocateZeroPool(HASH_INPUT_SIZE);
    if (Input == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", HASH_INPUT_SIZE);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Sample input of 512 bytes of 0xFE
    //

    SetMem(Input, HASH_INPUT_SIZE, 0xFE);
    Output.Md5Hash = (EFI_MD5_HASH*)HashBuffer;
    Output.Sha1Hash = (EFI_SHA1_HASH*)HashBuffer;
    Output.Sha224Hash = (EFI_SHA224_HASH*)HashBuffer;
    Output.Sha256Hash = (EFI_SHA256_HASH*)HashBuffer;
    Output.Sha384Hash = (EFI_SHA384_HASH*)HashBuffer;
    Output.Sha512Hash = (EFI_SHA512_HASH*)HashBuffer;
    for (UINTN i = 0; i < _countof(HashAlgorithmsMap); i++) {
        UINTN HashSize = 0;

        Status = HashProtocol->GetHashSize(HashProtocol, HashAlgorithmsMap[i].Guid, &HashSize);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("[-] %s is not supported error %s(0x%zx)",
                      HashAlgorithmsMap[i].Name,
                      E(Status),
                      Status);
            Status = EFI_SUCCESS;
            continue;
        }

        ZeroMem(HashBuffer, sizeof(HashBuffer));
        Status = HashProtocol->Hash(HashProtocol,
                                    HashAlgorithmsMap[i].Guid,
                                    0,
                                    Input,
                                    HASH_INPUT_SIZE,
                                    &Output);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("[-] %s Hash function failed : %s(0x%zx)",
                      HashAlgorithmsMap[i].Name,
                      E(Status),
                      Status);
            Status = EFI_SUCCESS;
            continue;
        }

        if (EFI_ERROR(HashEquals((UINT8*)Output.Sha512Hash,
                                 HashAlgorithmsMap[i].ExpectedHash,
                                 HashSize))) {
            DBG_INFO("[+] %s is supported", HashAlgorithmsMap[i].Name);
        } else {
            DBG_INFO("[+] %s is supported", HashAlgorithmsMap[i].Name);
        }

        HashAlgorithmsSupported = TRUE;
    }

    //
    // Validate Hash 2 support
    //

    Status = ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HASH2_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Hash2Protocol = (EFI_HASH2_PROTOCOL*)ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].Protocol;
    Input = AllocateZeroPool(HASH_INPUT_SIZE);
    if (Input == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", HASH_INPUT_SIZE);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Sample input of 512 bytes of 0xFE
    //

    SetMem(Input, HASH_INPUT_SIZE, 0xFE);

    for (UINTN i = 0; i < _countof(HashAlgorithmsMap); i++) {
        UINTN HashSize = 0;

        Status = Hash2Protocol->GetHashSize(Hash2Protocol, HashAlgorithmsMap[i].Guid, &HashSize);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("[-] %s is not supported error %s(0x%zx)",
                      HashAlgorithmsMap[i].Name,
                      E(Status),
                      Status);
            Status = EFI_SUCCESS;
            continue;
        }

        ZeroMem(&Output2, sizeof(EFI_HASH2_OUTPUT));
        Status = Hash2Protocol->Hash(Hash2Protocol,
                                     HashAlgorithmsMap[i].Guid,
                                     Input,
                                     HASH_INPUT_SIZE,
                                     &Output2);
        if (EFI_ERROR(Status)) {
            DBG_ERROR("[-] %s Hash function failed : %s(0x%zx)",
                      HashAlgorithmsMap[i].Name,
                      E(Status),
                      Status);
            Status = EFI_SUCCESS;
            continue;
        }

        if (EFI_ERROR(
                HashEquals(Output2.Sha512Hash, HashAlgorithmsMap[i].ExpectedHash, HashSize))) {
            DBG_INFO("[+] %s is supported", HashAlgorithmsMap[i].Name);
        } else {
            DBG_INFO("[+] %s is supported", HashAlgorithmsMap[i].Name);
        }

        HashAlgorithmsSupported = TRUE;
    }

Exit:

    FreePool(Input);

    return Status;
}

static EFI_STATUS Hash2Twice(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HASH2_PROTOCOL* Hash2Protocol = NULL;
    UINT8* Input = NULL;
    EFI_HASH2_OUTPUT Output;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HASH2_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Hash2Protocol = (EFI_HASH2_PROTOCOL*)ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].Protocol;
    Input = AllocateZeroPool(HASH_INPUT_SIZE);
    if (Input == NULL) {
        DBG_ERROR("AllocateZeroPool() failed to allocate buffer of size %d", HASH_INPUT_SIZE);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    //
    // Sample input of 512 bytes of 0xFE
    //

    SetMem(Input, HASH_INPUT_SIZE, 0xFE);

    for (UINTN i = 0; i < _countof(HashAlgorithmsMap); i++) {
        UINTN HashSize = 0;

        Status = Hash2Protocol->GetHashSize(Hash2Protocol, HashAlgorithmsMap[i].Guid, &HashSize);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        for (UINTN j = 0; j < 2; j++) {
            ZeroMem(&Output, sizeof(EFI_HASH2_OUTPUT));
            Status = Hash2Protocol->Hash(Hash2Protocol,
                                         HashAlgorithmsMap[i].Guid,
                                         Input,
                                         HASH_INPUT_SIZE,
                                         &Output);

            //
            // If we fail on first attempt it means, The algorithm is not
            // supported on the current platform
            //

            if (EFI_ERROR(Status) && j == 0) {
                Status = EFI_SUCCESS;
                break;
            }

            //
            // If we fail on 2nd attempt it means, we hit the double hash
            // problem we saw on Asus Precog uefi implementation
            //

            if (EFI_ERROR(Status) && j == 1) {
                DBG_INFO("[+] %s double hashing failed with %s(0x%zx)",
                         HashAlgorithmsMap[i].Name,
                         E(Status),
                         Status);
            }

            if (EFI_ERROR(
                    HashEquals(Output.Sha512Hash, HashAlgorithmsMap[i].ExpectedHash, HashSize))) {
                DBG_INFO("[+] %s double hashing failed", HashAlgorithmsMap[i].Name);
                break;
            } else if (j == 1) {
                DBG_INFO("[+] %s double hashing passed", HashAlgorithmsMap[i].Name);
            }
        }
    }

Exit:

    FreePool(Input);

    return Status;
}

static BOOLEAN TimerTriggered = FALSE;

static VOID EFIAPI TimerCallback(_In_ EFI_EVENT Event, _In_ VOID* BlockIo2RWContext)
{
    UNREFERENCED_PARAMETER(Event);
    UNREFERENCED_PARAMETER(BlockIo2RWContext);
    TimerTriggered = TRUE;
}

static EFI_STATUS Hash1Performance(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HASH_PROTOCOL* HashProtocol = NULL;
    EFI_HASH_OUTPUT Output;
    BYTE HashBuffer[128] = {0};
    PVOID Data = NULL;
    UINTN DataSize = 0;
    UINTN MaxDataSize = 0;
    EFI_EVENT TimerEvent = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_HASH_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HASH_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    HashProtocol = (EFI_HASH_PROTOCOL*)ProtocolArray[EFI_HASH_PROTOCOL_INDEX].Protocol;

    Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                              TPL_NOTIFY,
                              TimerCallback,
                              NULL,
                              &TimerEvent);

    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Preallocate the largest read/write buffer
    //

    MaxDataSize = 256 * MB;
    do {
        MaxDataSize += 50 * MB;
        Data = NULL;
        Data = AllocatePool(MaxDataSize);
        if (Data == NULL) {
            break;
        }
        FreePool(Data);
    } while (Data != NULL && MaxDataSize <= 4 * GB);
    MaxDataSize -= 50 * MB;

    Data = AllocatePool(MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %zd", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    Output.Md5Hash = (EFI_MD5_HASH*)HashBuffer;
    Output.Sha1Hash = (EFI_SHA1_HASH*)HashBuffer;
    Output.Sha224Hash = (EFI_SHA224_HASH*)HashBuffer;
    Output.Sha256Hash = (EFI_SHA256_HASH*)HashBuffer;
    Output.Sha384Hash = (EFI_SHA384_HASH*)HashBuffer;
    Output.Sha512Hash = (EFI_SHA512_HASH*)HashBuffer;
    for (UINTN i = 0; i < _countof(HashAlgorithmsMap); i++) {
        UINTN HashSize = 0;

        Status = HashProtocol->GetHashSize(HashProtocol, HashAlgorithmsMap[i].Guid, &HashSize);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO_RAW("[+] Hash Perf Test(%s):", HashAlgorithmsMap[i].Name);

        //
        // Start with 256 MB and increment in 50 MB steps until TimeLapsed is 1 sec
        //

        DataSize = 256 * MB;
        for (UINTN Increment = 100 * MB; Increment >= 1 * MB; Increment /= 2) {
            TimerTriggered = FALSE;
            while (DataSize < MaxDataSize) {
                Status = gBS->SetTimer(TimerEvent, TimerRelative, SEC_TO_100_NS(1));
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("SetTimer() failed : %s(0x%zx)", E(Status), Status);
                    Status = EFI_SUCCESS;
                    goto HashAlgoExit;
                }

                ZeroMem(HashBuffer, sizeof(HashBuffer));
                Status = HashProtocol->Hash(HashProtocol,
                                            HashAlgorithmsMap[i].Guid,
                                            0,
                                            Data,
                                            DataSize,
                                            &Output);
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("Hash algorithm not supported %s(0x%zx)", E(Status), Status);
                    Status = EFI_SUCCESS;
                    goto HashAlgoExit;
                }

                if (TimerTriggered == TRUE) {
                    break;
                }

                DataSize += Increment;
                DBG_INFO_RAW(".");
            }
            DataSize -= 2 * Increment;
        }

        DBG_INFO(" = %lld MBps", DataSize / MB);
    HashAlgoExit:;
    }

Exit:

    gBS->CloseEvent(TimerEvent);
    FreePool(Data);

    return Status;
}

static EFI_STATUS Hash2Performance(_In_ PBM_PROTOCOL_INFO ProtocolArray, _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HASH2_PROTOCOL* Hash2Protocol = NULL;
    EFI_HASH2_OUTPUT Output;
    PVOID Data = NULL;
    UINTN DataSize = 0;
    UINTN MaxDataSize = 0;
    EFI_EVENT TimerEvent = NULL;

    UNREFERENCED_PARAMETER(Session);

    Status = ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].ProtocolStatus;
    if (EFI_ERROR(Status)) {
        DBG_ERROR("EFI_HASH2_PROTOCOL Protocol not available : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    Hash2Protocol = (EFI_HASH2_PROTOCOL*)ProtocolArray[EFI_HASH2_PROTOCOL_INDEX].Protocol;

    Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                              TPL_NOTIFY,
                              TimerCallback,
                              NULL,
                              &TimerEvent);

    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Preallocate the largest read/write buffer
    //

    MaxDataSize = 256 * MB;
    do {
        MaxDataSize += 50 * MB;
        Data = NULL;
        Data = AllocatePool(MaxDataSize);
        if (Data == NULL) {
            break;
        }
        FreePool(Data);
    } while (Data != NULL && MaxDataSize <= 4 * GB);
    MaxDataSize -= 50 * MB;

    Data = AllocatePool(MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %zd", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    for (UINTN i = 0; i < _countof(HashAlgorithmsMap); i++) {
        UINTN HashSize = 0;

        Status = Hash2Protocol->GetHashSize(Hash2Protocol, HashAlgorithmsMap[i].Guid, &HashSize);
        if (EFI_ERROR(Status)) {
            Status = EFI_SUCCESS;
            continue;
        }

        DBG_INFO_RAW("[+] Hash Perf Test(%s):", HashAlgorithmsMap[i].Name);

        //
        // Start with 256 MB and increment in 50 MB steps until TimeLapsed is 1 sec
        //

        DataSize = 256 * MB;
        for (UINTN Increment = 100 * MB; Increment >= 1 * MB; Increment /= 2) {
            TimerTriggered = FALSE;
            while (DataSize < MaxDataSize) {
                Status = gBS->SetTimer(TimerEvent, TimerRelative, SEC_TO_100_NS(1));
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("SetTimer() failed : %s(0x%zx)", E(Status), Status);
                    Status = EFI_SUCCESS;
                    goto HashAlgoExit;
                }

                ZeroMem(&Output, sizeof(EFI_HASH2_OUTPUT));
                Status = Hash2Protocol->Hash(Hash2Protocol,
                                             HashAlgorithmsMap[i].Guid,
                                             Data,
                                             DataSize,
                                             &Output);
                if (EFI_ERROR(Status)) {
                    DBG_ERROR("Hash algorithm not supported %s(0x%zx)", E(Status), Status);
                    Status = EFI_SUCCESS;
                    goto HashAlgoExit;
                }

                if (TimerTriggered == TRUE) {
                    break;
                }

                DataSize += Increment;
                DBG_INFO_RAW(".");
            }
            DataSize -= 2 * Increment;
        }

        DBG_INFO(" = %lld MBps", DataSize / MB);
    HashAlgoExit:;
    }

Exit:

    gBS->CloseEvent(TimerEvent);
    FreePool(Data);

    return Status;
}

static EFI_STATUS HashSoftwarePerformance(_In_ PBM_PROTOCOL_INFO ProtocolArray,
                                          _In_ PBM_SESSION Session)
{
    EFI_STATUS Status = EFI_SUCCESS;
    PVOID Data = NULL;
    UINTN DataSize = 0;
    UINTN MaxDataSize = 0;
    EFI_EVENT TimerEvent = NULL;
    BYTE CalculatedHash[RTL_MAX_HASH_LEN_V2] = {0};
    CRYPT_DER_BLOB Blobs[1] = {0};
    ULONG HashSize = 0;
    NTSTATUS NtStatus;

    UNREFERENCED_PARAMETER(ProtocolArray);

    UNREFERENCED_PARAMETER(Session);

    Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL,
                              TPL_NOTIFY,
                              TimerCallback,
                              NULL,
                              &TimerEvent);

    if (EFI_ERROR(Status)) {
        DBG_ERROR("Unable to CreateEvent() failed : %s(0x%zx)", E(Status), Status);
        goto Exit;
    }

    //
    // Preallocate the largest read/write buffer
    //

    MaxDataSize = 256 * MB;
    do {
        MaxDataSize += 50 * MB;
        Data = NULL;
        Data = AllocatePool(MaxDataSize);
        if (Data == NULL) {
            break;
        }
        FreePool(Data);
    } while (Data != NULL && MaxDataSize <= 4 * GB);
    MaxDataSize -= 50 * MB;

    Data = AllocatePool(MaxDataSize);
    if (Data == NULL) {
        DBG_ERROR("AllocatePool() failed to allocate buffer of size %zd", MaxDataSize);
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    DBG_INFO_RAW("[+] Hash Software Based Perf Test(CALG_SHA_256):");

    //
    // Start with 256 MB and increment in 50 MB steps until TimeLapsed is 1 sec
    //

    DataSize = 256 * MB;
    for (UINTN Increment = 100 * MB; Increment >= 1 * MB; Increment /= 2) {
        TimerTriggered = FALSE;
        while (DataSize < MaxDataSize) {
            Status = gBS->SetTimer(TimerEvent, TimerRelative, SEC_TO_100_NS(1));
            if (EFI_ERROR(Status)) {
                DBG_ERROR("SetTimer() failed : %s(0x%zx)", E(Status), Status);
                Status = EFI_SUCCESS;
                goto Exit;
            }

            ZeroMem(&CalculatedHash, sizeof(CalculatedHash));

            //
            // Calculate SHA256 hash of the loaded image from disk
            //

            Blobs[0].pbData = Data;
            Blobs[0].cbData = (ULONG)DataSize;

            NtStatus = MinCrypL_HashMemory(CALG_SHA_256, 1, Blobs, CalculatedHash, &HashSize);
            if (!NT_SUCCESS(NtStatus)) {
                DBG_ERROR("MinCrypL_HashMemory() failed 0x%x", NtStatus);
                Status = EFI_INVALID_PARAMETER;
                goto Exit;
            }

            if (TimerTriggered == TRUE) {
                break;
            }

            DataSize += Increment;
            DBG_INFO_RAW(".");
        }
        DataSize -= 2 * Increment;
    }

    DBG_INFO(" = %lld MBps", DataSize / MB);

Exit:

    gBS->CloseEvent(TimerEvent);
    FreePool(Data);

    return Status;
}

static BM_TEST DutTests[] = {
    {
        .Name = t("hashinfo"),
        .Description = t("Hash Info"),
        .DutTestFn = HashProbe,
    },
    {
        .Name = t("hash1perf"),
        .Description = t("Hash 1 performance(Hardware)"),
        .DutTestFn = Hash1Performance,
    },
    {
        .Name = t("hash2perf"),
        .Description = t("Hash 2 performance(Hardware)"),
        .DutTestFn = Hash2Performance,
    },
    {
        .Name = t("softwarehash"),
        .Description = t("Hash performance(Software)"),
        .DutTestFn = HashSoftwarePerformance,
    },
#if 0
    {
        .Name = t("doublehash2"),
        .Description = t("Hash same block twice(512 bytes with 0xFE)"),
        .DutTestFn = Hash2Twice,
    },
#endif
};

BM_TEST_SUITE HashTestSuite = {
    .Description = t("Hash test suite"),
    .DutTests = DutTests,
    .DutTestCount = _countof(DutTests),
};

/*++

Copyright (c) Microsoft Corporation

Module Name:

    EndiannessHelper.h

Abstract:

    Header file to define endianness conversions

--*/

#pragma once

#ifndef __ENDIANESS_CONVERSIONS_H__
#define __ENDIANESS_CONVERSIONS_H__

#define PUTB8(p, v) (*(UINT8*)(p)) = ((UINT8)(v))
#define PUTB16(p, v)              \
    PUTB8((p), (UINT16)(v) >> 8); \
    PUTB8((UINT8*)(p) + 1, v)
#define PUTB32(p, v)                \
    PUTB16((p), (UINT32)(v) >> 16); \
    PUTB16((UINT8*)(p) + 2, (UINT32)(v))
#define PUTB64(p, v)                \
    PUTB32((p), (UINT64)(v) >> 32); \
    PUTB32((UINT8*)(p) + 4, (UINT64)(v))

#define PUTL8(p, v) (*(UINT8*)(p)) = ((UINT8)(v))
#define PUTL16(p, v) \
    PUTL8((p), (v)); \
    PUTL8((UINT8*)(p) + 1, (UINT16)(v) >> 8)
#define PUTL32(p, v)          \
    PUTL16((p), (UINT32)(v)); \
    PUTL16((UINT8*)(p) + 2, (UINT32)(v) >> 16)
#define PUTL64(p, v)          \
    PUTL32((p), (UINT64)(v)); \
    PUTL32((UINT8*)(p) + 4, (UINT64)(v) >> 32)

#define GETB8(p)  (*(UINT8*)(p))
#define GETB16(p) (((UINT16)GETB8(p) << 8) | (UINT16)GETB8((UINT8*)(p) + 1))
#define GETB32(p) (((UINT32)GETB16(p) << 16) | (UINT32)GETB16((UINT8*)(p) + 2))
#define GETB64(p) (((UINT64)GETB32(p) << 32) | (UINT64)GETB32((UINT8*)(p) + 4))

#define GETL8(p)  (*(UINT8*)(p))
#define GETL16(p) (((UINT16)GETL8((UINT8*)(p) + 1) << 8) | GETL8(p))
#define GETL32(p) (((UINT32)GETL16((UINT8*)(p) + 2) << 16) | (UINT32)GETL16(p))
#define GETL64(p) (((UINT64)GETL32((UINT8*)(p) + 4) << 32) | (UINT64)GETL32(p))

#endif // __ENDIANESS_CONVERSIONS_H__

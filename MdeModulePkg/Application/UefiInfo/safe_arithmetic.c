//
// Global includes
//
#include "common.h"
#include "safe_arithmetic.h"

//
// Variables
//

//
// Prototypes
//

//
// Interfaces
//

EFI_STATUS EFIAPI UintnAdd(IN UINTN Arg1, IN UINTN Arg2, OUT UINTN* Sum)
{
    if (Sum == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Integer overflow check
    //

    if (MAX_UINTN - Arg1 < Arg2) {
        return EFI_INVALID_PARAMETER;
    }

    *Sum = Arg1 + Arg2;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI Uint32Add(IN UINT32 Arg1, IN UINT32 Arg2, OUT UINT32* Sum)
{
    if (Sum == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Integer overflow check
    //

    if (MAX_UINT32 - Arg1 < Arg2) {
        return EFI_INVALID_PARAMETER;
    }

    *Sum = Arg1 + Arg2;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI UintnMult(IN UINTN Arg1, IN UINTN Arg2, OUT UINTN* Product)
{
    UINTN Result = 0;

    if (Product == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Integer overflow check
    //

    Result = Arg1 * Arg2;

    if (Arg1 != 0 && Result / Arg1 != Arg2) {
        return EFI_INVALID_PARAMETER;
    }

    *Product = Result;

    return EFI_SUCCESS;
}

EFI_STATUS EFIAPI Uint32Mult(IN UINT32 Arg1, IN UINT32 Arg2, OUT UINT32* Product)
{
    UINT32 Result = 0;

    if (Product == NULL) {
        return EFI_INVALID_PARAMETER;
    }

    //
    // Integer overflow check
    //

    Result = Arg1 * Arg2;

    if (Arg1 != 0 && Result / Arg1 != Arg2) {
        return EFI_INVALID_PARAMETER;
    }

    *Product = Result;

    return EFI_SUCCESS;
}

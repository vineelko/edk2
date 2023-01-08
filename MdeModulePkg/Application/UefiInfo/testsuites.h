#ifndef _TESTSUITES_H_
#define _TESTSUITES_H_

#include "common.h"
#include "protocols.h"
#include "session.h"

EFI_STATUS
EFIAPI
DispatchTestSuites(IN PBM_SESSION Session);

typedef EFI_STATUS (*BM_DUT_TEST_FN)(IN PBM_SESSION Session);

typedef struct _BM_TEST {
    //
    // Test case name. Example: "bioread". This is used with -r parameter when
    // invoking the test case
    //

    CHAR8* Name;

    //
    // Test description. Example: "10MB Block read test"
    //

    CHAR8* Description;

    //
    // Actual test function
    //

    BM_DUT_TEST_FN DutTestFn;
} BM_TEST, *PBM_TEST;

typedef struct _BM_TEST_SUITE {
    //
    // Test suite description. Example: "Block IO Test Suite"
    //

    CHAR8* Description;

    //
    // Individual tests to probe the capabilities of the implementation. For
    // example: Performing various read/write tests on a block device. This
    // member can be optional as not all test suites need to run tests(For
    // example: SmBios etc)
    //

    PBM_TEST DutTests;
    UINTN DutTestCount;

    //
    // Dut + host test definition
    //

    PBM_TEST DutHostTests;
    UINTN DutHostTestCount;
} BM_TEST_SUITE, *PBM_TEST_SUITE;

#endif // _TESTSUITES_H_

/*++

Copyright (c) 2020  Microsoft Corporation

Module Name:

    testsuites.c

Abstract:

    This module implements test suites management

Author:

    Vineel Kovvuri (vineelko) 19-May-2020

Environment:

    UEFI mode only.

--*/

#include "testsuites.h"
#include "session.h"
#include "protocols.h"
#include "utils.h"
#include "strsafe.h"

extern BM_PROTOCOL_INFO ProtocolArray[EFI_MAX_PROTOCOL_INDEX];

//
// List of UEFI tests that are registered to test/uefiinfo one or more protocol
//

extern BM_TEST_SUITE ReadinessTestSuite;
extern BM_TEST_SUITE BlockIoTestSuite;
extern BM_TEST_SUITE BlockIo2TestSuite;
extern BM_TEST_SUITE BootTestSuite;
extern BM_TEST_SUITE BootManagerTestSuite;
extern BM_TEST_SUITE DevicePathTestSuite;
extern BM_TEST_SUITE TextInputTestSuite;
extern BM_TEST_SUITE ConsoleOutputTestSuite;
extern BM_TEST_SUITE GraphicsOutputTestSuite;
extern BM_TEST_SUITE FontTestSuite;
extern BM_TEST_SUITE HashTestSuite;
extern BM_TEST_SUITE LoadImageTestSuite;
extern BM_TEST_SUITE MemoryTestSuite;
extern BM_TEST_SUITE RamdiskTestSuite;
extern BM_TEST_SUITE RandomNumberGeneratorTestSuite;
extern BM_TEST_SUITE CBMRTestSuite;
extern BM_TEST_SUITE FileSystemTestSuite;
extern BM_TEST_SUITE SmbiosTestSuite;
extern BM_TEST_SUITE TimestampTestSuite;
extern BM_TEST_SUITE Dhcp4TestSuite;
extern BM_TEST_SUITE Dhcp6TestSuite;
extern BM_TEST_SUITE Ip4ConfigTestSuite;
extern BM_TEST_SUITE Ip6ConfigTestSuite;
extern BM_TEST_SUITE Tcp4TestSuite;
extern BM_TEST_SUITE Tcp6TestSuite;
extern BM_TEST_SUITE Udp4TestSuite;
extern BM_TEST_SUITE Udp6TestSuite;
extern BM_TEST_SUITE UEFIVariableTestSuite;
extern BM_TEST_SUITE UsbFnIoTestSuite;
extern BM_TEST_SUITE UsbInitTestSuite;
extern BM_TEST_SUITE UITestSuite;
extern BM_TEST_SUITE WifiTestSuite;
extern BM_TEST_SUITE HttpTestSuite;
extern BM_TEST_SUITE WindbgTestSuite;

PBM_TEST_SUITE TestSuites[] = {

    //
    // Readiness is the first test suite to replicate existing readiness
    // functionality
    //

    &ReadinessTestSuite,
    &SmbiosTestSuite,
    &MemoryTestSuite,
    &BlockIoTestSuite,
    &BlockIo2TestSuite,
    &BootTestSuite,
    &BootManagerTestSuite,
    &DevicePathTestSuite,
    &TextInputTestSuite,
    &ConsoleOutputTestSuite,
    &GraphicsOutputTestSuite,
    &FontTestSuite,
    &HashTestSuite,
    &LoadImageTestSuite,
    &RamdiskTestSuite,
    &RandomNumberGeneratorTestSuite,
    &CBMRTestSuite,
    &FileSystemTestSuite,
    &Dhcp4TestSuite,
    //    &Dhcp6TestSuite,
    //    &Ip4ConfigTestSuite,
    //    &Ip6ConfigTestSuite,
    &Tcp4TestSuite,
    //    &Tcp6TestSuite,
    &Udp4TestSuite,
    //    &Udp6TestSuite,
    &TimestampTestSuite,
    &UEFIVariableTestSuite,
    &UsbFnIoTestSuite,
    &UsbInitTestSuite,
    &UITestSuite,
    &WifiTestSuite,
    &HttpTestSuite,
    &WindbgTestSuite,
};

VOID TestSuitePopulateAppInfoNode(_In_ PBM_SESSION Session);

EFI_STATUS
EFIAPI
DispatchTestSuites(_In_ PBM_SESSION Session)
/*++

Routine Description:

    This routine executes the tests based on the session configuration.

Arguments:

    Session - Supplies a pointer to session object which contain test
              suites/tests to be executed by this routines.

Return Value:

    EFI_STATUS. Return EFI_SUCCESS when no error is encountered or
    EFI_* otherwise.

--*/
{
    EFI_STATUS Status = EFI_SUCCESS;

    if (Session->ListTestCases == TRUE) {
        if (Session->ListTestCases) {
            for (UINTN i = 0; i < _countof(TestSuites); i++) {
                DBG_INFO("[%s]", TestSuites[i]->Description);
                for (UINTN j = 0; j < TestSuites[i]->DutTestCount; j++) {
                    if (TestSuites[i]->DutTests[j].Name == NULL) {
                        continue;
                    }

                    DBG_INFO(" %-30s - %s",
                             TestSuites[i]->DutTests[j].Name,
                             TestSuites[i]->DutTests[j].Description);
                }

                for (UINTN j = 0; j < TestSuites[i]->DutHostTestCount; j++) {
                    if (TestSuites[i]->DutHostTests[j].Name == NULL) {
                        continue;
                    }

                    DBG_INFO(" %-30s - %s [HOST+DUT]",
                             TestSuites[i]->DutHostTests[j].Name,
                             TestSuites[i]->DutHostTests[j].Description);
                }
            }
        }

        goto Exit;
    }

    if (Session->TestCase != NULL) {
        for (UINTN i = 0; i < _countof(TestSuites); i++) {
            PBM_TEST_SUITE TestSuite = TestSuites[i];

            for (UINTN j = 0; j < TestSuite->DutTestCount; j++) {
                PBM_TEST Test = &TestSuite->DutTests[j];

                if (AsciiStriCmp(Test->Name, Session->TestCase) == 0) {
                    if (Test->Description != NULL) {
                        DBG_INFO("%s", Test->Description);
                    }

                    if (Test->DutTestFn != NULL) {
                        Status = Test->DutTestFn(ProtocolArray, Session);
                    }

                    goto Exit;
                }
            }
        }
    }

Exit:
    return Status;
}

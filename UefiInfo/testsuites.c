#include "testsuites.h"
#include "session.h"
#include "protocols.h"
#include "utils.h"
// #include "strsafe.h"

extern PROTOCOL_INFO ProtocolArray[EFI_MAX_PROTOCOL_INDEX];

//
// List of UEFI tests that are registered to test/uefiinfo one or more protocol
//

extern UEFIINFO_TEST_SUITE ReadinessTestSuite;
extern UEFIINFO_TEST_SUITE BlockIoTestSuite;
extern UEFIINFO_TEST_SUITE BlockIo2TestSuite;
extern UEFIINFO_TEST_SUITE BootTestSuite;
extern UEFIINFO_TEST_SUITE BootManagerTestSuite;
extern UEFIINFO_TEST_SUITE DevicePathTestSuite;
extern UEFIINFO_TEST_SUITE TextInputTestSuite;
extern UEFIINFO_TEST_SUITE ConsoleOutputTestSuite;
extern UEFIINFO_TEST_SUITE GraphicsOutputTestSuite;
extern UEFIINFO_TEST_SUITE FontTestSuite;
extern UEFIINFO_TEST_SUITE HashTestSuite;
extern UEFIINFO_TEST_SUITE LoadImageTestSuite;
extern UEFIINFO_TEST_SUITE MemoryTestSuite;
extern UEFIINFO_TEST_SUITE RamdiskTestSuite;
extern UEFIINFO_TEST_SUITE RandomNumberGeneratorTestSuite;
extern UEFIINFO_TEST_SUITE CBMRTestSuite;
extern UEFIINFO_TEST_SUITE FileSystemTestSuite;
extern UEFIINFO_TEST_SUITE SmbiosTestSuite;
extern UEFIINFO_TEST_SUITE TimestampTestSuite;
extern UEFIINFO_TEST_SUITE Dhcp4TestSuite;
extern UEFIINFO_TEST_SUITE Dhcp6TestSuite;
extern UEFIINFO_TEST_SUITE Ip4ConfigTestSuite;
extern UEFIINFO_TEST_SUITE Ip6ConfigTestSuite;
extern UEFIINFO_TEST_SUITE Tcp4TestSuite;
extern UEFIINFO_TEST_SUITE Tcp6TestSuite;
extern UEFIINFO_TEST_SUITE Udp4TestSuite;
extern UEFIINFO_TEST_SUITE Udp6TestSuite;
extern UEFIINFO_TEST_SUITE UEFIVariableTestSuite;
extern UEFIINFO_TEST_SUITE UsbFnIoTestSuite;
// extern UEFIINFO_TEST_SUITE UsbInitTestSuite;
extern UEFIINFO_TEST_SUITE UITestSuite;
extern UEFIINFO_TEST_SUITE WifiTestSuite;
extern UEFIINFO_TEST_SUITE HttpTestSuite;
extern UEFIINFO_TEST_SUITE Dns4TestSuite;
extern UEFIINFO_TEST_SUITE SystemTableTestSuite;
extern UEFIINFO_TEST_SUITE SerialPortTestSuite;

PUEFIINFO_TEST_SUITE TestSuites[] = {
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
    &Dhcp6TestSuite,
    &Ip4ConfigTestSuite,
    &Ip6ConfigTestSuite,
    &Tcp4TestSuite,
    &Tcp6TestSuite,
    &Udp4TestSuite,
    &Udp6TestSuite,
    &TimestampTestSuite,
    &UEFIVariableTestSuite,
    &UsbFnIoTestSuite,
    // &UsbInitTestSuite,
    &UITestSuite,
    &WifiTestSuite,
    &HttpTestSuite,
    &Dns4TestSuite,
    &SystemTableTestSuite,
    &SerialPortTestSuite,
};

VOID TestSuitePopulateAppInfoNode(IN PUEFIINFO_SESSION Session);

EFI_STATUS
EFIAPI
DispatchTestSuites(IN PUEFIINFO_SESSION Session)
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
                DBG_INFO("[%a]", TestSuites[i]->Description);
                for (UINTN j = 0; j < TestSuites[i]->DutTestCount; j++) {
                    if (TestSuites[i]->DutTests[j].Name == NULL) {
                        continue;
                    }

                    DBG_INFO(" %-30a - %a",
                             TestSuites[i]->DutTests[j].Name,
                             TestSuites[i]->DutTests[j].Description);
                }

                for (UINTN j = 0; j < TestSuites[i]->DutHostTestCount; j++) {
                    if (TestSuites[i]->DutHostTests[j].Name == NULL) {
                        continue;
                    }

                    DBG_INFO(" %-30a - %a [HOST+DUT]",
                             TestSuites[i]->DutHostTests[j].Name,
                             TestSuites[i]->DutHostTests[j].Description);
                }
            }
        }

        goto Exit;
    }

    if (Session->TestCase != NULL) {
        for (UINTN i = 0; i < _countof(TestSuites); i++) {
            PUEFIINFO_TEST_SUITE TestSuite = TestSuites[i];

            for (UINTN j = 0; j < TestSuite->DutTestCount; j++) {
                PUEFIINFO_TEST Test = &TestSuite->DutTests[j];

                if (AsciiStriCmp(Test->Name, Session->TestCase) == 0) {
                    if (Test->Description != NULL) {
                        DBG_INFO("--TEST: %a--", Test->Description);
                        DBG_INFO("");
                    }

                    if (Test->DutTestFn != NULL) {
                        Status = Test->DutTestFn(Session);
                    }

                    goto Exit;
                }
            }
        }
    }

Exit:
    return Status;
}

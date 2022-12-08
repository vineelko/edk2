#ifndef _BMERROR_H_
#define _BMERROR_H_

static const CHAR8* ErrorStrings[] = {
    [0] = t("EFI_SUCCESS"),               // 0x0
    [1] = t("EFI_LOAD_ERROR"),            // 0x1
    [2] = t("EFI_INVALID_PARAMETER"),     // 0x2
    [3] = t("EFI_UNSUPPORTED"),           // 0x3
    [4] = t("EFI_BAD_BUFFER_SIZE"),       // 0x4
    [5] = t("EFI_BUFFER_TOO_SMALL"),      // 0x5
    [6] = t("EFI_NOT_READY"),             // 0x6
    [7] = t("EFI_DEVICE_ERROR"),          // 0x7
    [8] = t("EFI_WRITE_PROTECTED"),       // 0x8
    [9] = t("EFI_OUT_OF_RESOURCES"),      // 0x9
    [10] = t("EFI_VOLUME_CORRUPTED"),     // 0xA
    [11] = t("EFI_VOLUME_FULL"),          // 0xB
    [12] = t("EFI_NO_MEDIA"),             // 0xC
    [13] = t("EFI_MEDIA_CHANGED"),        // 0xD
    [14] = t("EFI_NOT_FOUND"),            // 0xE
    [15] = t("EFI_ACCESS_DENIED"),        // 0xF
    [16] = t("EFI_NO_RESPONSE"),          // 0x10
    [17] = t("EFI_NO_MAPPING"),           // 0x11
    [18] = t("EFI_TIMEOUT"),              // 0x12
    [19] = t("EFI_NOT_STARTED"),          // 0x13
    [20] = t("EFI_ALREADY_STARTED"),      // 0x14
    [21] = t("EFI_ABORTED"),              // 0x15
    [22] = t("EFI_ICMP_ERROR"),           // 0x16
    [23] = t("EFI_TFTP_ERROR"),           // 0x17
    [24] = t("EFI_PROTOCOL_ERROR"),       // 0x18
    [25] = t("EFI_INCOMPATIBLE_VERSION"), // 0x19
    [26] = t("EFI_SECURITY_VIOLATION"),   // 0x1A
    [27] = t("EFI_CRC_ERROR"),            // 0x1B
    [28] = t("EFI_END_OF_MEDIA"),         // 0x1C
    [29] = t("EFI_END_OF_FILE"),          // 0x1D
    [30] = t("EFI_INVALID_LANGUAGE"),     // 0x1E
    [31] = t("EFI_COMPROMISED_DATA"),     // 0x1F
    [32] = t("EFI_HTTP_ERROR"),           // 0x20

    //
    // ICMP error definitions
    //

    [100] = t("EFI_NETWORK_UNREACHABLE"),  // 0x64
    [101] = t("EFI_HOST_UNREACHABLE"),     // 0x65
    [102] = t("EFI_PROTOCOL_UNREACHABLE"), // 0x66
    [103] = t("EFI_PORT_UNREACHABLE"),     // 0x67

    //
    // Tcp connection status definitions
    //

    [104] = t("EFI_CONNECTION_FIN"),     // 0x68
    [105] = t("EFI_CONNECTION_RESET"),   // 0x69
    [106] = t("EFI_CONNECTION_REFUSED"), // 0x6A
};

#define MASK (~0x8000000000000000ULL)
#define E(Status)                                                                 \
    ((((Status)&MASK) < _countof(ErrorStrings)) ? ErrorStrings[(Status)&MASK] ?   \
                                                  ErrorStrings[(Status)&MASK] :   \
                                                  t("Error string not defined") : \
                                                  t("Status to error string conversion failed"))

#endif // _BMERROR_H_

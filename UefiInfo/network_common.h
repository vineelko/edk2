#ifndef _NETWORK_COMMON_H_
#define _NETWORK_COMMON_H_

#define DUMP_IP4_PORT(message, ip, port)              \
    {                                                 \
        {                                             \
            DBG_INFO("%a: IPv4:%u.%u.%u.%u, Port:%u", \
                     message,                         \
                     ip.Addr[0],                      \
                     ip.Addr[1],                      \
                     ip.Addr[2],                      \
                     ip.Addr[3],                      \
                     port);                           \
        }                                             \
    }

EFI_STATUS EFIAPI NetworkCommonInitStack();
BOOLEAN EFIAPI NetworkCommonIsEthernetHandle(IN EFI_HANDLE DeviceHandle);
BOOLEAN EFIAPI NetworkCommonIsEthernetMediaAttached(IN EFI_HANDLE DeviceHandle);
#endif // _NETWORK_COMMON_H_

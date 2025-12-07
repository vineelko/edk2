#ifndef _IPUTILS_H_
#define _IPUTILS_H_

#include "common.h"
#include "ntefidef.h"

inline static VOID DumpIP4Address(EFI_IPv4_ADDRESS* IP4Address)
{
    DBG_INFO("%d.%d.%d.%d",
             IP4Address->Addr[0],
             IP4Address->Addr[1],
             IP4Address->Addr[2],
             IP4Address->Addr[3]);
}

inline static VOID DumpMacAddress(EFI_MAC_ADDRESS* MacAddress)
{
    DBG_INFO("%02x-%02x-%02x-%02x-%02x-%02x",
             MacAddress->Addr[0],
             MacAddress->Addr[1],
             MacAddress->Addr[2],
             MacAddress->Addr[3],
             MacAddress->Addr[4],
             MacAddress->Addr[5]);
}

inline static BOOLEAN IsNullAddress(EFI_IPv4_ADDRESS* IP4Address)
{
    return IP4Address->Addr[0] == 0 && IP4Address->Addr[1] == 0 && IP4Address->Addr[2] == 0 &&
           IP4Address->Addr[3] == 0;
}

#endif // _IPUTILS_H_

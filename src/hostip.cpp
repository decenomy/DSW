// Copyright (C) 2000-2010  Daniel Ryde
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

#include "hostip.h"
#include "chainparams.h"
#include "tinyformat.h"
#include "guiinterface.h"
#include "guiinterfaceutil.h"

HostIP hostip;

bool HostIP::init(std::string bindAddr)
{
    if (bindAddr.empty()) return false;

    std::string strHost;
    int nDefaultPort = Params().GetDefaultPort();
    int port = 0;
    SplitHostPort(bindAddr, port, strHost);
    service = CService();
// only to allow bitcoind rpc port to listen on 0.0.0.0
//    if (port == 0) port = nDefaultPort;
    if (!Lookup(strHost.c_str(), service, port, true))
    {
        return UIError(strprintf(_("HostIP: invalid bindAddr %s\n"), bindAddr));
    }
    hostipport = htons((unsigned short)port);

    std::string strError = "";
    socklen_t len = sizeof(sockaddr);

    if (!service.GetSockAddr((struct sockaddr*)&local_sockaddr, &len))
    {
        return UIError(strprintf(_("Error: Address family for %s not supported\n"), service.ToString()));
    }

    if (service.IsIPv4())
    {
        inaddr_any_saddr = htonl (INADDR_ANY);
        len = sizeof(struct sockaddr_in);
        struct sockaddr_in *paddrin = (struct sockaddr_in*) &local_sockaddr;
        memset(paddrin, 0, len);
        if (!service.GetInAddr(&paddrin->sin_addr))
        {
            return UIError(strprintf(_("Error: Invalid address\n"), service.ToString()));
        }
        fHostIP = true;
        paddrin->sin_family = AF_INET;
        paddrin->sin_port = htons(0);
    } else {	// is IPv
        len = sizeof(struct sockaddr_in6);
        struct sockaddr_in6 *paddrin6 = (struct sockaddr_in6*) &local_sockaddr;
        memset(paddrin6, 0, len);
        if (!service.GetIn6Addr(&paddrin6->sin6_addr))
        {
            return UIError(strprintf(_("Error: Invalid address\n"), service.ToString()));
        }
        fHostIP = true;
        fIsIPv4 = false;
        paddrin6->sin6_scope_id = 0;
        paddrin6->sin6_family = AF_INET6;
        paddrin6->sin6_port = htons(0);
    }
}

// substitute this for ::bind in net.cpp
int HostIP::altbind(SOCKET ufd, struct sockaddr * sk, socklen_t sl)
{
    static struct sockaddr_in *lsk_in;
    static struct sockaddr_in6 *lsk6_in;
    static struct in6_addr addr6;

    if (fIsIPv4)
    {
        lsk_in = (struct sockaddr_in *)sk;
        unsigned long int addr;
        if (fHostIP
            && (lsk_in->sin_family == AF_INET)
            && (lsk_in->sin_port != hostipport)
            && (lsk_in->sin_addr.s_addr == inaddr_any_saddr)
            && service.GetInAddr((in_addr*)&addr))
        {
            lsk_in->sin_addr.s_addr = addr;
        }
    }
    else 
    { // is IPv6
        lsk6_in = (struct sockaddr_in6 *)sk;

        if (fHostIP
            && (lsk6_in->sin6_family == AF_INET6)
            && (lsk6_in->sin6_port != hostipport)
            && IsInAddrAny6(lsk6_in)
            && service.GetIn6Addr(&addr6))
        {
            memcpy(&(lsk6_in->sin6_addr), &addr6, 16);
        }
    }
    return ::bind(ufd, sk, sl);
}

// insert this just before for "connect" in netbase.cpp
int HostIP::alteraddr(SOCKET ufd, struct sockaddr * sk, socklen_t sl)
{
    static struct sockaddr_in *rsk_in;
    static struct sockaddr_in6 *rsk6_in;

    if (fIsIPv4)
    {
        rsk_in = (struct sockaddr_in *)sk;
        if (fHostIP
            && (rsk_in->sin_family == AF_INET)
            && (rsk_in->sin_port != hostipport))
        {
            ::bind(ufd, (struct sockaddr *)&local_sockaddr, sizeof(struct sockaddr));
        }
    }
    else 
    { // is IPv6
        rsk6_in = (struct sockaddr_in6 *)sk;

        if (fHostIP
            && (rsk6_in->sin6_family == AF_INET6)
            && (rsk6_in->sin6_port != hostipport))
        {
            ::bind(ufd, (struct sockaddr *)&local_sockaddr, sizeof(struct sockaddr));
        }
    }
}

bool HostIP::IsInAddrAny6(struct sockaddr_in6 * sin6)
{
    int i;
    uint32_t * pa = reinterpret_cast<uint32_t*>(sin6);
    for(i = 0; i < 4; ++i)
    {
        if (*pa != 0)
            return false;
        *pa++;
    }
    return true;
}

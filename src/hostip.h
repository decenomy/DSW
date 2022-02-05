//
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef HOSTIP_H
#define HOSTIP_H

#if defined(HAVE_CONFIG_H)
#include "config/pivx-config.h"
#endif

#include "compat.h"
#include "serialize.h"
#include "netaddress.h"
#include "netbase.h"

#include <stdint.h>
#include <string>

class HostIP;

extern HostIP hostip;

class HostIP {
private:
    bool fHostIP = false;
    bool fIsIPv4 = true;
    unsigned long int inaddr_any_saddr;
    unsigned short hostipport = 0;
    struct sockaddr_storage local_sockaddr;

public:
    CService service;
    int altbind(SOCKET sock, struct sockaddr * sk, socklen_t sl);
    int alteraddr(SOCKET sock, struct sockaddr * sk, socklen_t sl);
    bool init(std::string bindAddr);
    bool IsInAddrAny6(struct sockaddr_in6 * sin6);
};

#endif // HOSTIP_H

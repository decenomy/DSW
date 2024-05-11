// Copyright (c) 2024 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#define APPLE_CA_PATH "/etc/ssl/cert.pem"

class CBootstrap
{
public:
    static bool DownloadAndApply();
};

#endif

// Copyright (c) 2017-2020 The Bitcoin Core developers
// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "fs.h"

#include <boost/filesystem.hpp>
#include <openssl/sha.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#ifndef _WIN32
#include <sys/stat.h>
#endif 

namespace fsbridge {

    FILE *fopen(const fs::path& p, const char *mode)
    {
        return ::fopen(p.string().c_str(), mode);
    }

    FILE *freopen(const fs::path& p, const char *mode, FILE *stream)
    {
        return ::freopen(p.string().c_str(), mode, stream);
    }

} // fsbridge

bool GrantWritePermissions(const fs::path& path) {

#ifdef _WIN32
    try {
        // Get the current permissions
        fs::perms current_perms = fs::status(path).permissions();

        // Add write permissions for owner, group, and others
        fs::perms new_perms = current_perms
                              | fs::perms::owner_write
                              | fs::perms::group_write
                              | fs::perms::others_write;

        // Set the new permissions
        fs::permissions(path, new_perms);

        LogPrintf("%s: write permissions granted to: %s \n", __func__, path);
        return true;
    } catch (const fs::filesystem_error& e) {
        LogPrintf("%s: Error updating permissions: %s\n", __func__, e.what());
        return false;
    }  
#else
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        LogPrintf("%s: Error reading path stat\n", __func__);
        return false;
    }

    mode_t new_mode = info.st_mode | S_IWUSR | S_IWGRP | S_IWOTH;
    if (chmod(path.c_str(), new_mode) != 0) {
        LogPrintf("%s: Error granting permissions chmod: %d\n", __func__, new_mode);
    } else {
        LogPrintf("%s: write permissions granted to: %s \n", __func__, path);
        return true;
    }
#endif
    return false;
}

std::string File_SHA256(const std::string& path){
      
    std::ifstream fp(path, std::ios::in | std::ios::binary);

    if (not fp.good()) {
        LogPrintf("-SHA256::%s: Error: %s, Cannot open: %s\n",__func__, std::strerror(errno),path);
        return "";
    }

    constexpr const std::size_t buffer_size { 1 << 12 };
    char buffer[buffer_size];

    unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    while (fp.good()) {
        fp.read(buffer, buffer_size);
        SHA256_Update(&ctx, buffer, fp.gcount());
    }

    SHA256_Final(hash, &ctx);
    fp.close();

    std::ostringstream os;
    os << std::hex << std::setfill('0');

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        os << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }

return os.str();
}
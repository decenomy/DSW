// Copyright (c) 2017-2020 The Bitcoin Core developers
// Copyright (c) 2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "fs.h"

#include <boost/filesystem.hpp>

#include <regex>

namespace fsbridge {

FILE *fopen(const fs::path& p, const char *mode)
{
    return ::fopen(p.string().c_str(), mode);
}

FILE *fopen(const fs::path& p, const char *mode, size_t *fileSize)
{
    const char* home = getenv("HOME");
    std::string pathStr = p.string();
    if (p.string()[0] == '~' && home != nullptr) {
        pathStr = std::regex_replace(pathStr, std::regex("~"), home, std::regex_constants::format_first_only);
    }

    fs::path absolutePath = fs::canonical(pathStr);

    if (fileSize != nullptr) {
        *fileSize = fs::file_size(absolutePath);
    }

    return ::fopen(absolutePath.string().c_str(), mode);
}

FILE *freopen(const fs::path& p, const char *mode, FILE *stream)
{
    return ::freopen(p.string().c_str(), mode, stream);
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream)
{
    return ::fread(buffer, size, count, stream);
}

int fclose(FILE *stream)
{
    return ::fclose(stream);
}

} // fsbridge

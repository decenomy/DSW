// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "crypto/google_authenticator.h"
#include "crypto/hmac_sha1.h"

#include <cmath>
#include <ctime>
#include <cstring>

int GoogleAuthenticator::GeneratePin() {

    int64_t currentInterval = std::time(NULL) / INTERVAL_LENGHT;
    
    unsigned char counterBytes[8];
                
    counterBytes[0] = (int)((currentInterval >> 56) & 0xFF);
    counterBytes[1] = (int)((currentInterval >> 48) & 0xFF);
    counterBytes[2] = (int)((currentInterval >> 40) & 0XFF);
    counterBytes[3] = (int)((currentInterval >> 32) & 0XFF);
    counterBytes[4] = (int)((currentInterval >> 24) & 0xFF);
    counterBytes[5] = (int)((currentInterval >> 16) & 0xFF);
    counterBytes[6] = (int)((currentInterval >>  8) & 0XFF);
    counterBytes[7] = (int)(currentInterval         & 0XFF);

    CHMAC_SHA1 h(key, len);
    h.Write(counterBytes, 8);
    unsigned char hash[20];
    h.Finalize(hash);

    unsigned char selectBytes[4];
    std::memcpy(selectBytes, hash + (hash[19] & 0xF), 4);

    int pin = 
        (selectBytes[0] << 24) + 
        (selectBytes[1] << 16) +
        (selectBytes[2] << 8) +
         selectBytes[3];

    pin &= 0x7FFFFFFF;
    pin %= (int) std::pow(10, PIN_LENGHT);

    return pin;
}
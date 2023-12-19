// Copyright (c) 2023 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ebf/ebfstate.h"

static const char DB_STATE_ENTRY = 'S';

namespace
{

struct CEBFStateEntry {
    char recordKey;
    EBFContracts contract;
    std::vector<uint8_t> key;

    explicit CEBFStateEntry(EBFContracts contract, const std::vector<uint8_t>& key)
        : recordKey(DB_STATE_ENTRY), contract(contract), key(key) {}

    template <typename Stream>
    void Serialize(Stream& s) const
    {
        s << recordKey;
        s << static_cast<uint8_t>(this->contract);
        s << key;
    }

    template <typename Stream>
    void Unserialize(Stream& s)
    {
        s >> recordKey;
        uint8_t contract;
        s >> contract;
        this->contract = static_cast<EBFContracts>(contract);
        s >> key;
    }
};

} // namespace
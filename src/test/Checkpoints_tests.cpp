// Copyright (c) 2011-2013 The Bitcoin Core developers
// Copyright (c) 2017-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Unit tests for block-chain checkpoints
//

#include "checkpoints.h"

#include "uint256.h"
#include "test_pivx.h"

#include <boost/test/unit_test.hpp>


BOOST_FIXTURE_TEST_SUITE(Checkpoints_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(sanity)
{
    uint256 p75023 = uint256S("0xadb7e529be2222a0b5aeee7c1a9ddd2bf6a1aacb5770526581b94a00a5c16cc3");
    uint256 p293843 = uint256S("0xdd2019a18aa2c9b4c55d2ea572115f562149da78502d4f5794a54fe9a35edc48");
    BOOST_CHECK(Checkpoints::CheckBlock(75023, p75023));
    BOOST_CHECK(Checkpoints::CheckBlock(293843, p293843));


    // Wrong hashes at checkpoints should fail:
    BOOST_CHECK(!Checkpoints::CheckBlock(75023, p293843));
    BOOST_CHECK(!Checkpoints::CheckBlock(293843, p75023));

    // ... but any hash not at a checkpoint should succeed:
    BOOST_CHECK(Checkpoints::CheckBlock(75023+1, p293843));
    BOOST_CHECK(Checkpoints::CheckBlock(293843+1, p75023));

    BOOST_CHECK(Checkpoints::GetTotalBlocksEstimate() >= 293843);
}

BOOST_AUTO_TEST_SUITE_END()

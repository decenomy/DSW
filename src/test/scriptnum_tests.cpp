// Copyright (c) 2012-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/script.h"
#include "test/test_pivx.h"

#include <boost/test/unit_test.hpp>
#include <limits.h>
#include <stdint.h>

BOOST_FIXTURE_TEST_SUITE(scriptnum_tests, BasicTestingSetup)

static const long values[] = \
{ 0, 1, CHAR_MIN, CHAR_MAX, UCHAR_MAX, SHRT_MIN, USHRT_MAX, INT_MIN, INT_MAX, static_cast<long>UINT_MAX, LONG_MIN, LONG_MAX };
static const long offsets[] = { 1, 0x79, 0x80, 0x81, 0xFF, 0x7FFF, 0x8000, 0xFFFF, 0x10000};

static void RunCreate(const long& num)
{
    CheckCreateInt(num);
    CScriptNum scriptnum(num);
    if (scriptnum.getvch().size() <= CScriptNum::nDefaultMaxNumSize)
        CheckCreateVch(num);
    else
    {
        BOOST_CHECK_THROW (CheckCreateVch(num), scriptnum_error);
    }
}

static void RunOperators(const long& num1, const int64_t& num2)
{
    CheckAdd(num1, num2);
    CheckSubtract(num1, num2);
    CheckNegate(num1);
    CheckCompare(num1, num2);
}

BOOST_AUTO_TEST_CASE(creation)
{
    for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        for(size_t j = 0; j < sizeof(offsets) / sizeof(offsets[0]); ++j)
        {
            RunCreate(values[i]);
            RunCreate(values[i] + offsets[j]);
            RunCreate(values[i] - offsets[j]);
        }
    }
}

BOOST_AUTO_TEST_CASE(operators)
{
    for(size_t i = 0; i < sizeof(values) / sizeof(values[0]); ++i)
    {
        for(size_t j = 0; j < sizeof(offsets) / sizeof(offsets[0]); ++j)
        {
            RunOperators(values[i], values[i]);
            RunOperators(values[i], -values[i]);
            RunOperators(values[i], values[j]);
            RunOperators(values[i], -values[j]);
            RunOperators(values[i] + values[j], values[j]);
            RunOperators(values[i] + values[j], -values[j]);
            RunOperators(values[i] - values[j], values[j]);
            RunOperators(values[i] - values[j], -values[j]);
            RunOperators(values[i] + values[j], values[i] + values[j]);
            RunOperators(values[i] + values[j], values[i] - values[j]);
            RunOperators(values[i] - values[j], values[i] + values[j]);
            RunOperators(values[i] - values[j], values[i] - values[j]);
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()

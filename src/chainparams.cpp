// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <stdio.h>

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "util.h"
#include "utilstrencodings.h"

#include <boost/assign/list_of.hpp>

#include <assert.h>

#define DISABLED 0x7FFFFFFE;

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Soverain's blockchain #init";
    const CScript genesisOutputScript = CScript() << ParseHex("04dbc25a9a48add73d7f65d1ff4ae6a1fc80d2089fcdc78dc8e5088c6d27df962f393a07cad6fc632f6b891f5c81f970bf282679c39e581f856d6a94c9f814cc68") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256S("000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"))
    (31080, uint256S("14c9fe85721aa0b5f304bb3b3b8707f36f2dfbd8f37aa941dc49337d327ec5b5"))
    (62161, uint256S("785fe60d1dd9cd0821aad6bf1af03a1b51e1425c11378c738e6f72aa71d3450b"))
    (93242, uint256S("132b68be5e128306a3269c006b952c6ea6b546dbdeab500d48844d4ed56c1a6e"))
    (124323, uint256S("77077dd1577fb3af4d76daf12f57a5d16e1f75f7138481c32264dd0982798759"))
    (155404, uint256S("b278133fb327676e8aa51eeae6eba667b35df12b198bb97dcf12219bf78f8bde"))
    (186485, uint256S("d60f34d22e504240234d5bf50192d1c8e6f35f8c2b92106cd50f4ef6273db129"))
    (217566, uint256S("53c3b41f37618acbeb8a183eca3de0f75d4db1dd6bb940f3573cdcdc79c983c7"))
    (248647, uint256S("e620309b625d30e53542dfa195e6617159ce918e9e5b0b6ea93336ba01c9d862"))
    (279728, uint256S("bd3c6acbbb1b8fdd277a4bbf312b90664d0f496628a597d4ecaa47af886872ec"))
    (310809, uint256S("259f07fb48d2632ff641905413e5e4100f8784ebc2c7fe24570decf9e9b51e20"))
    (341890, uint256S("622fef7cd0b7c049cce9e081cfc71a622f6101e25da4bc20484f7c2dc24fb3dc"))
    (372971, uint256S("154d111f1f95de87cd1cf6f8a496e6e21e9ab668815a2149ede2a5ca6859ab69"))
    (404052, uint256S("0c2ff8d98da85fd7883023042f15236b2596cdcdb3249d9ec0e2e7aa88e62f80"))
    (435133, uint256S("4c120c620a6b2c8855e95896a519e6d3c15bbb78b9350bff627c29adaf44d5ed"))
    (466214, uint256S("253d4c154b1b55b5c680390f6c694d8515c4c13bf980dbe8f7d2055e163a6fb0"))
    (497295, uint256S("dad99c3cdb1f058faaf2f5b3a3507cab1cd0bf6a15e31b8b3bd81c6b2ca131ce"))
    (528376, uint256S("5c821e6a9ef76bb8383cf303c7abe958f295ee6d56a44252df968336b6458ed9"))
    (559457, uint256S("c535de7abfa46174b85f4b3ec6e275659effb575d4352aa92c43fbb9637e0e7f"))
    (590538, uint256S("9d5e5b3ff1f786816250af94de4452516cf40b4f016231b8dfcfb1ef31d68961"))
    (621619, uint256S("3b22baedf64311eb8a4b31174e8171dec0eec1217122a197bfa7f64dc71d9ef0"))
    (652700, uint256S("7d6506527300a00c0ee08ee6dd7c6e150f88158c1f2dd08ea063157a61275ad9"))
    (683781, uint256S("939e77bf9e57e2db43e5106e5da9669fc232f62653d60485f88e7a893e2b1ffd"))
    (714862, uint256S("d01a1ff5f83a32d45da4cc74d24c00c73b50ba6a250d5a929c03468eb2f721f6"))
    (745943, uint256S("24d43bc22122946807eddb4ddf67a9ed80731ac84d5af1a1b0a9c92195f98923"))
    (777024, uint256S("39f7719ec5a66dcc6e707e65c0ab75ea631268cb3f5fbd00bedb7e0bdc96610a"))
    (808105, uint256S("303a750139a35d91e55988817c3ca90517ad274e74f507a11840d907459a2fbc"))
    (839186, uint256S("cfbe433b3b173a587547a29dc45de0c354601caab1fad57d60ec48fad7a5a008"))
    (870267, uint256S("0f477b297b5d1f6e6cf3d3673c30de0541bad80223d7744c9f06afb49c581db8"))
    (901348, uint256S("c1feb3d8e4733057d3f4061f5674fb20e1bcd1571ac6d160f3e9917c7d645e69"))
    (932429, uint256S("7e2d2d89f9a11a390d3adb077d7312c932ac2ca9c901e381e4188fbed4fec3ad"))
    (963510, uint256S("13a6c4c333975addff840215daab07cd0744e00a60d375b0593b465863881639"))
    (994591, uint256S("b1ebac79dfd1dfe2012f4a2ee0a4a74af655ca8b1a46cece9cb484efd4dc1292"))
    (1025672, uint256S("7013d6f3e2897e77ee6fa6c48fce4e696c738fc2b13507955aba5164563b9e7b"))
    (1056753, uint256S("fb40ecf3febb3f6cf4373f1a69daff406fb4b336b89b605188b227e7931deac1"))
    (1087834, uint256S("0c56bb33bd252fd215fafea3b4050fcc3f47712e6839ebe21a1da0cbd0f47ff6"))
    (1118915, uint256S("cfdc04956452a02d800f78ca4e3daae89fdc45cde11f29a44e541c78f2338ae4"))
    (1149996, uint256S("a3302693a2a10c2a099e9dbcc41ccbbbf3f7b1b14adca78092b591dc7733056a"))
    (1181077, uint256S("30391433e5fac5a1a551bae7545e049bce13a1a479748422456e2276dcb88916"))
    (1212158, uint256S("fd84714403811a1e882a0cca437c02645701a6681ca2e67c80cccfe56e312203"))
    (1243239, uint256S("c255eab5f272ab775513796645929830aa21ec7ab86ed44442d7b5e6965bb857"))
    (1274320, uint256S("4c5b8e1814f6f691d5dcaa16c054679686ceed5ccffb821d81846058765ad2eb"))
    (1305401, uint256S("59974e81dabb44b67e6ce77a449d1cee8c7e90bb5e4a4947e6d31219ab0c98fc"))
    (1336482, uint256S("d2998137038124cb0790dd5aad65b83f69697b916ba17ebc489573fc599123af"))
    (1367563, uint256S("18d5c7be0f896852621c7a234cf396da18c66e490119977e60026f8a8dec0be5"))
    (1398644, uint256S("fbbc1bb0b212344f79458f1bd4f264b934d982d718b56bc414a0d1ca030a8018"))
    (1429725, uint256S("2d4063a6b1c312d2d84b7863b91a87324aae4113462ff02bfb7c633bc365da84"))
    (1460806, uint256S("37c8a73bfa8bdc0bee2a6532ed133f873e249ca2401510b8b9921954f57a239a"))
    (1491887, uint256S("c8fb0b2d981462ed1309caf6814ccf5b8a94d83464b289c0ba9b6d9de67271d6"))
    (1522968, uint256S("29b63e558530228d1a81eafaeea38e35960e4841a390299a9b7e30647f58c611"))
    (1554049, uint256S("5ad8829b61fd5175b396433690f68a4c47dade2c6391978851e872e9432c9144"))
    (1585130, uint256S("687179a00c79a61109135e4fc39a0c9d4c3f1a7e31ce6edcec7ad62c3201dba9"))
    (1616211, uint256S("316707e5c651c2ad49427849a24a3818c609f0f45e7257a1f30775d8a98bf4f4"))
    (1647292, uint256S("a8c4ef0fe8db26dd4790f0cf5f2418092f598d0a4daba054f15d5f64232951d4"))
    (1678373, uint256S("f6c12d02f6d05111d1201c328f00a2cc501028375bf8f56ac8ce5207f438f3f1"))
    (1709454, uint256S("db7a6cb0878685c0d5e64c101b7c1658a15134948a264068a2801a8737b179f7"))
    (1740535, uint256S("50b8115303b7aa464476f1533c789c0c252569e2a464fdc19975d34b6fe37c89"))
    (1771616, uint256S("e71aa5509617d91f7487a7c9a9b5c1473231b05007150bb6f5679bf1e9208ecf"))
    (1802697, uint256S("0cb2dfbb69dcc06b666c8108d6bde8b7fae40e250117fb6c6ff782b15a6e876f"))
    (1833778, uint256S("e3ca7056b10fd18a32a3edd0544db42737c06e7309ac894f22adcda3a6423aef"))
    (1864859, uint256S("07470f71ee8cd8ce69e3dfb9f2ef13f362901ce682b2a8cbde533c6b2860bf94"))
    (1895940, uint256S("34129490996d184d1425be5f50c8f190770c6b9dc9de85b341b9d74bcdee5c10"))
    (1927021, uint256S("4d164d0c7c7f8f64ff4bfb1cbd9c17517115029e44a3be74853660edf54853f7"))
    (1958102, uint256S("89b61b497dc217a47850f859286b5af5a5189306c38db56b495fd8844a75e5fa"))
    (1989183, uint256S("e7cdfb1fac253e479e22b67d8ea6a98a2387db5a6149cecf600a6ad41119f81e"))
    (2020264, uint256S("bfd91ea9539b1fbe99ed8141f9b0b9a457bdae6d752c77ab0a7205de5dc6d79e"))
    (2051345, uint256S("27ff668013565847b062f707a0c0354795106a88fa4e413100aaec17b447fda3"))
    (2082426, uint256S("d88a51987911c65c876687718999798c9cef4389ec006851bd5aa23cdb415f14"))
    (2113507, uint256S("c1335e9069ac92db655c23571e4a5e93041d68913acf06081ba144eaee2b4e67"))
    (2144588, uint256S("78f5a2f11f8cf7278ec059979eaf22c1f6d96a283c05042864de26847ca6609c"))
    (2175669, uint256S("c82056fde435ccc4afa874110bca6824c508890e27865a31a9192cdbca5796f6"))
    (2206750, uint256S("fb42edf3441d8f42d8639cf7089c53e9ec20c1ce8a37a972ce47d6bef8fe39df"))
    (2237831, uint256S("91dfc5adabe85ccef4d0b94292e4ce7eedcf67567f25b363ed64875d0ed6ea3b"))
    (2268912, uint256S("52ffe5b300b4effeaf14ca0592fc36773bdf3149b9109156b8b941d13d9a495d"))
    (2299993, uint256S("e3c197e5d7c8f583e2c148ac7a0443c2ccc6f72467ea4147646b86f3b43faccb"))
    (2331074, uint256S("a123dbcd2a546e9175e501e78525383afc6add27b1bea479573f134f84cdf409"))
    (2362155, uint256S("0038671df7651db1d2e3f2cb7c03635debadf24dc460e6d0b30d84eeb81b5027"))
    (2393236, uint256S("cec51da5ef68181c9960511e37b1592efdba4e717a34461a40a01b4b1553e84d"))
    (2424317, uint256S("0c10b543065925a37ba047134d04efc35ba20afb309b6f8ff44a929c4be6471a"))
    (2455398, uint256S("e5eb3adc65fd966b68fb8e23036ca56c212f6bc1d78f10f09c7de4ac7a9cfd83"))
    (2486479, uint256S("21896ec8f2302eb606bbfc42c7a2843d3b4f91c779ad004a5693e41d46dc10db"))
    (2517560, uint256S("f6805e8e4ea902d3210b218a8a8a464f00e00ef9eb334efc830f90e87e42e502"))
    (2548641, uint256S("5baad0dc0289ecbc96cfb656a3eb7e7e1af9bb384f7c098bd3d788e4ec5d81d6"))
    (2579722, uint256S("a0e0589bdafca57abfeac8e27d769c833eaa64bcc6ee7bdfe64dfb4691945432"))
    (2610803, uint256S("c9aa9bdf22773bf815ed347cc76f3dfe22c98efab73ac4bf3e408a6bab813233"))
    (2641884, uint256S("d4e291e86e65f44d9625975cdd48c89a4340d201feaad417c86d335d4a5b7300"))
    (2672965, uint256S("8f019afa932fd25cceae901fa0f0ec2cbe1ed30b6bf87b7f6203e2dd5c283c57"))
    (2704046, uint256S("e22ea8d7c82217ecdb3fd558ec3946bde52e1d46f94d47e2bb6988258cd9cf87"))
    (2735127, uint256S("00d12f048388a8363bb28eaddd2204271223ab6cc84cb933ddb4acc58090faef"))
    (2766208, uint256S("636581f3910c63f00f9ffe91e013a2d1e13113dacfde3f4bf2f4a89da0e8c43a"))
    (2797289, uint256S("6415ce09e70e0dba1a0447acf49651b3c86ae8eb470204f79ef1ce6de3d5e118"))
    (2828370, uint256S("13354260db5ef494a5cfada64479a55c2240fedbc38665951ce7a658c30b190a"))
    (2859451, uint256S("66b540a586a6d0f85a1592637c8f16e1b84a9884dcbf9138625e4909107ceb59"))
    (2890532, uint256S("d06a3f37b7e5b61e46292f597e42a18cd56ed16d71dfb1f2ea0a74119d8d98eb"))
    (2921613, uint256S("2b5f7261c112cd1b11c48afa909e7eca3e2113e61b7b7f6ee148bfcc44c3f34f"))
    (2952694, uint256S("0b7537a1fdb9e94b84b0b10e33bb47b24ff6f8773e8ef000a61c0ee1087dafd5"))
    (2983775, uint256S("c495050aa98545fb61ffc81287e70c1c5f4f14be1790dae116507f6200a81e25"))
    (3014856, uint256S("0e6cbd09e645fd537933464b89e65ad7cf185b501dadc28481fc31ded3dea4c0"))
    (3045937, uint256S("fc0f0a1b56d7cf12ac73966b5bb13fbb44215efed88812e8f00edd8f6823dbce"))
    (3077018, uint256S("08a898b1838e6c4d46f3da5da9aff1145362508de0ba9c6215a7e63598b9a0f6"))
    (3108099, uint256S("7f60e20eab6ae64d0bcb101ad0e542854f7f1f9e5c6aac577223381d8d32fb74"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1693004460, // * UNIX timestamp of last checkpoint block
    7955534,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2812        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1612360301; // 2021-02-03T13:51:41+00:00

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1e0ffff0, 1, 0 * COIN);
        //     //genesis.hashPrevBlock = TempHashHolding;
        //     consensus.hashGenesisBlock = genesis.GetHash();

        //     arith_uint256 BestBlockHashArith = UintToArith256(BestBlockHash);
        //     if (UintToArith256(consensus.hashGenesisBlock) < BestBlockHashArith) {
        //         BestBlockHash = consensus.hashGenesisBlock;
        //         std::cout << BestBlockHash.GetHex() << " Nonce: " << i << "\n";
        //         std::cout << "   PrevBlockHash: " << genesis.hashPrevBlock.GetHex() << "\n";
        //     }

        //     TempHashHolding = consensus.hashGenesisBlock;

        //     if (BestBlockHashArith < test) {
        //         genesisNonce = i - 1;
        //         break;
        //     }
        //     //std::cout << consensus.hashGenesisBlock.GetHex() << "\n";
        // }
        // std::cout << "\n";
        // std::cout << "\n";
        // std::cout << "\n";

        // std::cout << "hashGenesisBlock to 0x" << BestBlockHash.GetHex() << std::endl;
        // std::cout << "Genesis Nonce to " << genesisNonce << std::endl;
        // std::cout << "Genesis Merkle 0x" << genesis.hashMerkleRoot.GetHex() << std::endl;

        // exit(0);

        // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1563924366, 694507, 0x1e0fffff, 1, 1 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000007cabcfba44b7a728f1746bdec842c9fefab32e8e9df3e18d28ecc265eb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x79b352ef6aa3a1994a4c3d711e2d460385b53cce065611049a9a3c55e49b53e1"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 120;
        consensus.nCoinbaseMaturityV2 = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 3 * 60 * 60; // 3h
        consensus.nStakeMinDepth = 120;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 20 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 30;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "03061929edbb05141eef4ce4c9fc5c944c0ee67aaebcca5defaced677769bcc871";
        consensus.strSporkPubKeyOld = "04c90538206b7c4921e1e96e93e83dcc39f4351b997fc57934f5beddf916563497b99a315a772b626e072c9a903209c85172cec7052a54739dc392e27cda0d581f";
        consensus.nTime_EnforceNewSporkKey = 1625615999;
        consensus.nTime_RejectOldSporkKey = 1625788799;

        // burn addresses
        consensus.mBurnAddresses = {
           { "SXXXXXXXXXXXXXXXXXXXXXXXXXXXXFdBi4", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 2012001;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 2012101;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 2012201;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 2012301;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 2012401;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 2024001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("7aeb48ba5038096a31dba0b0a274236297eaab809ef24fe48d58eec821ebbffa");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("e679be7f6b3ea1e379280ee7f0d52f16d57e7c59bdde6e741ac716002f0d887d");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("24975d012582291480d6604d469acd18b09acd87068f9f1a8309338c708dcda9");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("ea1031ff14a7c59c7df9291d347cbf1c72bb1a9b4aafbf3c215314a14aaeaae7");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("cbf48bacc3e1c8d843fe43be3baf7732c7ac4282f57e171980a2b50d18fb141f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("99552707f5e6815ac9c4bdf764817c21cd72dd095f44a1268c373bec8cb1648a");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("a538111ace7e59b635beac76a113d3a99592215f5063fae161a67bc1176e137d");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x56;
        pchMessageStart[3] = 0x45;
        nDefaultPort = 18976;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.suvcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.suvcoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.suvcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4C).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main)); // added
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }

};
static CMainParams mainParams;

/**
 * Testnet (v1)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
        consensus.nCoinbaseMaturityV2 = 10;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 200;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 201;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 1841;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  =uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x45;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
        nDefaultPort = 18980;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.suvcoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet suvereno addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet suvereno script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet suvereno BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet suvereno BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1454124731, 2402015, 0x1e0ffff0, 1, 250 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));
        //assert(genesis.hashMerkleRoot == uint256S("0x1b2ef6e2f28be914103a277377ae7729dcd125dfeb8bf97bd5964ba72b6dc39b"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // suvereno starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nCoinbaseMaturityV2 = 80;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTargetSpacingV2 = 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
            Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
            Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight
            = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight
            = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight
            = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 18984;

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }

    void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
    {
        assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
        consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
    }
};
static CRegTestParams regTestParams;

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    regTestParams.UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}

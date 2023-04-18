// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
	// pszTimestamp = Headline: https://cointelegraph.com/news/another-defi-exit-scam-just-made-off-with-20m-in-investor-funds
    const char* pszTimestamp = "COINTELEGRAPH 10/Sep/2020 Another DeFi exit scam just made off with $20M in investor funds";
    const CScript genesisOutputScript = CScript() << ParseHex("0448790ec8f49697a1b0089fd998e932231ba4728c8c3edc2b50b65821e58b441117036ff66337ea5021baf94e29ea83117e885d67018654d0869bbe2eb1d74dd6") << OP_CHECKSIG;
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
    (0, uint256S("00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"))
    (8801, uint256S("c68cecb66ed4a695386b8b341558743b0fe46a6a737953be0c63cc25aaeedf98"))
    (17603, uint256S("bcbfe193798fadf04087beb34be7a662c7c82f9a1b364951d9cee7dc3cfa7183"))
    (26405, uint256S("7df0e9cf86fde310efd2f4b656d9151c1a5bcfe4f775d254b5e0d086b1f70868"))
    (35207, uint256S("404e9271442863998d5f1f20eae15b2db425e4cafd268c01eb0bdbcada1c9cd2"))
    (44009, uint256S("46e762eda110dba4fea08cb10fe05d06d3c16fe5002f30d4ba588b35028631ad"))
    (52811, uint256S("0ad54130b6b242c300151b1f18333ec755d95631ba52ad9fd1eb52a00bf01125"))
    (61613, uint256S("880585c4bcc4fd8d4880153ed9b2b648a3ad58329d1ad8823efbee706ff88c91"))
    (70415, uint256S("468e078ae77ff4f0aaeb8be4b8312228af05834b4951b8d5427d33d1d99dceac"))
    (79217, uint256S("c4c7e769608b86ab42f6cf1fd51bab3ca6a825c8d8ddbfc089d47602d64176cc"))
    (88019, uint256S("ad6cfb7ecc391c825d6d9ce210da0a58d9f6bf01d4010af1998e8430c2d5fdad"))
    (96821, uint256S("270a7a7f099548130e9385a7537f0f923796ff42204fa9755ddf35f5650978fc"))
    (105623, uint256S("eb0830d2b50ba49bc16d155948cd9f04ee11a2352bb6d7cb64b1f3ddf77bd407"))
    (114425, uint256S("8ae5a1d00c9d37748e4260c902f77365d80e7de623ab4ec984ada2ac4bec93ea"))
    (123227, uint256S("26407c2095f2fe2e778c76c3e83264040ded533b26536475ef3f7abda15fb118"))
    (132029, uint256S("c6cf449449bcb5cb1d265fc6aed17abc600b8f67d92d36884d329e858c09701e"))
    (140831, uint256S("1798fd73cb667b88682da29360a46aae62ab9a6e63ee39590999ff7f319cd06f"))
    (149633, uint256S("cce89c4782b7a9e8192ecbd2b91f17829227906f77673009001926ca1eb90862"))
    (158435, uint256S("6d36777cfb0d12e530672236fcdad12a5a25c794686c8a8eb59603d2e096f4e2"))
    (167237, uint256S("4c2ac6768fce8b5d2908afc0c78d05e183a6c0880ec0d46fce1424552ac136b6"))
    (176039, uint256S("1d9c0a3fab8a20ed7ec8349c887a375703889b00d3112eeda166c45def9e5d91"))
    (184841, uint256S("7b54a8d518d70ffa3a94ad491a7aa01cabe28dd55d0fd09def22d871e01fa9ae"))
    (193643, uint256S("40a1a37a42e91e45124b612e3db722081b1ba98239fd7b892df4c7c7df3dba03"))
    (202445, uint256S("f7ba0c95f51730dcdbdc83bbefdcd612f7992f4567d2bbbb2ef51a03632efa30"))
    (211247, uint256S("3e09b57ee2c3c7727105921d247b27f1e1ac60c6e1ee3b99a94b0d11eba52c48"))
    (220049, uint256S("25cbe95aaba5993e0487399e3ec63b689e5bf582f9c3a70a67842d9166bf1e20"))
    (228851, uint256S("0ef99a79e81f35e82bcbd47bd404ee1cf916d9204d7109b74f147c1f4762a189"))
    (237653, uint256S("eab9a6bf3324f8492a93124f07f91b98bffd7d03d6f7b62512c9b4f9e8fa414e"))
    (246455, uint256S("5b7037d0542ac3c6f34e143ba870669dfa035c38317190f007020d36bc38ec1f"))
    (255257, uint256S("0fc2646fe850d6e6f37e82095a918e059da942961142fabe6b2e87ab5b5816ec"))
    (264059, uint256S("63e276c17080cee40ae65b45f9faa2eb5482a5d57ebaa28e0729e77b04f20653"))
    (272861, uint256S("53923e9409cb2035152c491df49f311771d3481dcf4d3b4b57f61f7756181d83"))
    (281663, uint256S("bc26527c60be7acc0ba67b999cf478a31cb1065c1ded0819c6f5b28f19a794c0"))
    (290465, uint256S("949e05d1d6b515a991ae1d56638d4d9e762d99cda7379ddc19c51d6cf6040d8c"))
    (299267, uint256S("d28dfddd411b0de295831362bfb8c6f15248edf62b087b16b5f508b5c51be2a3"))
    (308069, uint256S("962d06531c987b51beab51227ed2822857c2af25ca975da3bdc25830d71cef29"))
    (316871, uint256S("c292a6aaced34fdc9e1ba8fc28e726f2a9981582dd498116a329181518052582"))
    (325673, uint256S("68e7425ac3b04596f67c07179edc8a41aca01086b4b6929c1d8f39dd9a40248f"))
    (334475, uint256S("b4a362357155feee6e16cc70fe2370a186699adf8867d5f11d7179102fde68bd"))
    (343277, uint256S("f585a4af1c681f08f1d36507bd9d1f42217b31cd011ed36450052639219fbe54"))
    (352079, uint256S("d0e80a136fab97348c2511b13344bd474fca0e25106c402b64bea16b848649b4"))
    (360881, uint256S("11b0eabc571ff9cbd310f3234b7f8b34e3614b3a4bd6f8e697f9bb797437c0d8"))
    (369683, uint256S("45f82698154fb47b87047ff256b953ed7059bc8fa369b77260f36ada9d871756"))
    (378485, uint256S("e945a0b7a8a123e7fc021ab4491c545fc2c848902a005bd127479bf0550cffd1"))
    (387287, uint256S("76c93c19acd991e6048be1e46024efd0a14f95783b0f4230c059fee6640d4af6"))
    (396089, uint256S("362aa35df8dd30c44b9443602ea505fbea5b0f8deef64d0ba0d5996dd9e550d9"))
    (404891, uint256S("4597ccad585ed967c12216279ca591204885807c9305bb2a4c1cb4bc841f4fca"))
    (413693, uint256S("90dcaefc1a4270351a0ce94466e30f45517364aaca57617161c4a89b6a179103"))
    (422495, uint256S("fd661d93a3fa8e2db6cd1a7c12eada7d9ff1737db0b379f2bfb7e17aee459583"))
    (431297, uint256S("d4e62364ef1467757ac00b4fbabf1c32a8b3567061008a9566c43bcd536c2755"))
    (440099, uint256S("4c552a72eea913ae35841152f90c51895465c11f4989f33f63af697df2fbf1a7"))
    (448901, uint256S("a1ee8f7ef73a2cdb39275a236e5c076962063d49c068945c1aefc5a920967fbb"))
    (457703, uint256S("ab0182794de8b9f3ace7927b703f9842d73fa4082023a7de01a9c19b8d03dd7a"))
    (466505, uint256S("fa028ed5f8b15cb298aea5152ed120cb24c6781070f28194abf3b020041a0255"))
    (475307, uint256S("9dab90beeda796000e2f288fae1b0f669bb75308440c70f998b41049c45136b4"))
    (484109, uint256S("3a28bf09519384463a928b3193a6f216f98d6c848eb68b45ea0580e9a3e2f12b"))
    (492911, uint256S("394122531449fd84fe53bc944a6220a6447227b78896fb72d6c78fa2ed99290e"))
    (501713, uint256S("b7321c791d4369e9d1216c0740e313b1b3490c2994df799d411206dbcb567608"))
    (510515, uint256S("4de7a08296b31e84ca3ec7909aece9f213816a14a3b093f345023f8729fbf33f"))
    (519317, uint256S("20adfcaa190b1a7a4c56ccdcb9680d1d879add9b0e6a297aef3319446f775103"))
    (528119, uint256S("5e630db86768427547d6d31c287735eb6d97405adf172adf0c5ea33b9dad84d5"))
    (536921, uint256S("67390c28f601a0976a53919bd7616f49f55f7d9ade07bd1271f9e8b30509fc9e"))
    (545723, uint256S("6cb9f5fe934a7b52761cf4425092d10ba868331107bafcdca3cb1397987a9e3f"))
    (554525, uint256S("846d67d904912b8a92d3eeca8c93026fabd6d1473bec864e4930f637913f44f5"))
    (563327, uint256S("f3fa992fb546634b8d6e74c4a3c27b1b33b4234c3210d4f9bce853a9dd6407b9"))
    (572129, uint256S("26745351e6469d656e2bdfd04226eb6236575285a67886198f12d081a8f2f32c"))
    (580931, uint256S("6ea38fb9093fb812c499f40e8583578f1a2e2ca860b7480ab78df6385fe13798"))
    (589733, uint256S("4dd405c0dd4aeb7363ad9002e2228fa2b0f00123dc2e6d8296b8042f8425b84d"))
    (598535, uint256S("2df0fc07b74359afe59d6374dfccf89be6284db499bae2c590dda269e1707188"))
    (607337, uint256S("5df81821d3d12f59803ac4f166607523607fe2c3f34cba9ba5449698f8c3fe4c"))
    (616139, uint256S("2d6a57a02d99954763485a04b2c0b68587f28420edb95967ad1f82f93c6ce112"))
    (624941, uint256S("16cfe96da17b903950229f2ecc1e63fbff32296278b0b2959ab4fec503a9cec3"))
    (633743, uint256S("4335ff34fceee45a3c8eb1b41e9f6bff329c2f368052fb3f0890ba1e14877ff7"))
    (642545, uint256S("097bada853b11d166c0d1c0b5f2b71341e7054b3ac35c2c635f7d916d042e634"))
    (651347, uint256S("b035f8f1dfb370775a8c598ab229f54129aa253554b25f4b5680c13017ad731c"))
    (660149, uint256S("c4d89b9ddf5ad9a498f6b1a4720f10ef9f96e8297afa38fac307f2e5e89506fc"))
    (668951, uint256S("95c04dbf992566815e73509a5f548414f3f7525adcf09407d08544434401eb3b"))
    (677753, uint256S("6e9b064274080eafd031adfe767d27bc401115589eeb6c84ffeee1a238bd4d69"))
    (686555, uint256S("bedf9a3eaf2c80e56264f5d0052e672ac5bfe15bb65d7e1a4758f2aa149d0ca5"))
    (695357, uint256S("6e295122908926c1cb15b1e2e175c1cad56921ca263d6a9a24a4d578e1a596f0"))
    (704159, uint256S("cfbcbacb1d170d44dfde752c44e15f74fb9190dd6b72eb89ab82dc94a4d51219"))
    (712961, uint256S("66be682cfd2c41b042eef072277660b07dc62622f115b1cb16a566d8592c5a81"))
    (721763, uint256S("ad0cbbcaafef7fda4e8175cfef454d641bbca4af4e24ab1f625518112f5b5a90"))
    (730565, uint256S("1f807c717da2f8b7b36a631ec26e88e8425dacb652d67aa01b838152b1b46eef"))
    (739367, uint256S("d8378a5aee0f217a3bd73f4dafdbd8ef0d472d4b16b98bdf096b2411d508b3f3"))
    (748169, uint256S("ca844fa08b4c28dffef94d73459db9d7ce233796b3817ed46cde8416689a5e9a"))
    (756971, uint256S("cc10c1f825bb0e57268c1e266bf7b16eeebc07e9f251f40d8b09fd8263b7ddf8"))
    (765773, uint256S("e335429d3175f4df032342e04cae678b13568ab0d4c96627b3146ab625157f13"))
    (774575, uint256S("0bb80d484776979f390b376a650b7fe438d6a541f1555fe5241f50c5cdb18929"))
    (783377, uint256S("1928f3c03c8d7bf3381e11c83861628d50dd36daecda35671403ebb06601f141"))
    (792179, uint256S("4772f055e5ce5d4197c346229ca174f2c45203a296df4c2e0d53f4c2e21b84ca"))
    (800981, uint256S("784c10e98de38a135559a176a2a661622eda2c53889bf58aede255520d154508"))
    (809783, uint256S("d00f292a0b2210b46c86acda7bb60a5255d494b94ef64490f305aa1768b319f6"))
    (818585, uint256S("12d600d51e13d1751b9527d522fc56f8c14abe5d8dcd68dd155a126a7eef1b01"))
    (827387, uint256S("9c9f132702026e6b11cbb25e721f10e670b561116fa9c6200533be937cdd406c"))
    (836189, uint256S("068a87a83d61df83ed35d4ebad8eda2ae53afc24d533aa5f16205e4fbf8a44d3"))
    (844991, uint256S("e5cc8d109de72ef13947a342472c9c21edb407ad6fc7003d99e00b66c1382721"))
    (853793, uint256S("2fdb245f4ec1afc3d224b8023de9bf74e966a0e3a77a76e409d118a404cf8406"))
    (862595, uint256S("92eda41886a10f53f04526c4a643a20a9ba68e207db335eb6998cb49040ff3a1"))
    (871397, uint256S("80faf6e0a55fabfce75e8d37ea23cb20e6c527a1ddb40b5bea152a3a8dcd7641"))
    (880199, uint256S("e1f663f01d7af15a1c24638965fd3362b2444216ce7504eaf029f75c01f5be65"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1681836510, // * UNIX timestamp of last checkpoint block
    1900999,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2838        // * estimated number of transactions per day after checkpoint. 2000 for 10 minutes of bitcoin blockchain (1M block size). With 2M of block size and 1 minute of block time, this field should be around 4000 * 10 * 6 * 24 = 5760000
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x000000313693c8b25165dbdc8498b8c0084fa24ffea6a02765733700fbcf7467"))
;

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1599766365,
    0,
    2000};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of
    (0, uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"))
;

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1625312841,
    0,
    2000};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        /**
         * Salute to old Kyanite code based on DASH code base.
         * Original chain launch was made on 10th of September, 2020 as the pszTimestamp headline.
         * Genesis block creation timestamp (1599766364) is reflecting that day.
         * Original chain consensus.hashGenesisBlock: 0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1
         * Original chain genesis.hashMerkleRoot: 0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71
         * We keep both consensus.hashGenesisBlock and genesis.hashMerkleRoot of the original chain in the new DSW code base.
         */
        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 9999999999 * COIN;
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 600;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.strSporkPubKeyOld = "035d8e6fdf6e463bc59d4efe4339de96b8274a911526348de46963511f5e6d6170";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "KXBURNXXXXXXXXXXXXXXXXXXXXXXWJmF2X", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("a68286b8dd2d7730ab2025201b38020fa68592010ac3e4bcbeaf066b40533802");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("09daf9665ae60b0dbcef4d60ac4af43bf83837e3d8a89198d82e53fac00010fc");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6b369beb95e63b6dab9c5f52e26339aaf5bfdccce0bad968c21267464829c904");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("4278660ffb8d8d12cc070eea2f8390aa84132fef799675a865717e444d5722e1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("2123647f29f91a35aa429913db96e666d7de476f1fc109a8298bf6f291b36584");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("04721c90cd55aa14dbf5cf0b24de60311b37b2deb0e98004b01b2e90c4d3b031");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("8f7c1d65300983dbf2d99c70051d20470f0088275d6bca9a69fbb2b8597585b7");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa6;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0xf9;
        nDefaultPort = 7757;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.kyancoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.kyancoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.kyancoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 46); // K
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 43);  // 7 or X
        // Kyan BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // Kyan BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x42).convert_to_container<std::vector<unsigned char> >();

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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1599766365; // 2021-02-03T13:51:41+00:00

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

        genesis = CreateGenesisBlock(1599766364, 112122, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000551e93eb0749d40dfafd54b092e78d6612b47bd40de8d099818f65f53c1"));
        assert(genesis.hashMerkleRoot == uint256S("0x17c6d46ee4758572534f6dec116f61268fe883caa99062c1efd764bbbc975d71"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1000M KYAN
        consensus.nPoolMaxTransactions = 3;
        consensus.nStakeMinAge = 60 * 60; // 1h
        consensus.nStakeMinDepth = 100;
        consensus.nStakeMinDepthV2 = 10;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        // spork keys
        consensus.strSporkPubKey = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.strSporkPubKeyOld = "037c650e8f2e175727a69c50d5fb459f09891e8f6d113105033dfa7af472a229e2";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "kBURNXXXXXXXXXXXXXXXXXXXXXXXUwNvtS", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 5001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 3001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("0x0");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0x0");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0x6a;
        pchMessageStart[1] = 0x9a;
        pchMessageStart[2] = 0x6f;
        pchMessageStart[3] = 0x9f;
        nDefaultPort = 8757;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.kyancoin.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 107); // Testnet kyanite addresses start with 'k'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
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

        // // This is used inorder to mine the genesis block. Once found, we can use the nonce and block hash found to create a valid genesis block
        // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1625312841; // 2021-02-03T13:51:41+00:00

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x207fffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i=0;i<40000000;i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x207fffff, 1, 1000 * COIN);
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

        genesis = CreateGenesisBlock(1625312841, 1, 0x207fffff, 1, 1000 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x430fbdf677d8bd836bc104377a7ab86d62051d927c80315d30e2df6b09df8e7b"));
        assert(genesis.hashMerkleRoot == uint256S("0xa50c4f55f3df2d2ecf33f0248f631ca20935c49dccad9bf2107911d94c5ab0fe"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // kyanite starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;       // num of MN we allow the see-saw payments to be off by
        consensus.nMaxMoneyOut = 1000000000 * COIN; // 1 billion KYAN
        consensus.nPoolMaxTransactions = 2;
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 2;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.strSporkPubKeyOld = "043969b1b0e6f327de37f297a015d37e2235eaaeeb3933deecd8162c075cee0207b13537618bde640879606001a8136091c62ec272dd0133424a178704e6e75bb7";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 251;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 251;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight          = 251;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight       = 300;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */

        pchMessageStart[0] = 0xd6;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0x6d;
        pchMessageStart[3] = 0x9d;
        nDefaultPort = 9757;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 140); // Regtest kyanite addresses start with 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Regtest kyanite script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        // Regtest kyanite BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest Kyaninte BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Regtest mode doesn't have any DNS seeds.
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

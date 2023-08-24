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
    const char* pszTimestamp = "Is Bitcoin a Good Investment: Analyst Predicts High Institutional Demand Post Covid-19";
    const CScript genesisOutputScript = CScript() << ParseHex("04b3fa9f648a6b1f477db94dc72db5df018b5539f081fa32258d6c7ba47a6b47b48187909c1fa62b2087d9e17e115fbfb20b042ff7c9c34f35c5d17f76c458e7f4") << OP_CHECKSIG;
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
    (0, uint256S("000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"))
    (7935, uint256S("30efd11e7a9bea41ebb2a1cb7d1a946dbc1eafab9ac29b5d6c15ba4bf5699b05"))
    (15871, uint256S("1c11da12aec52d711a95e88f7b14fcc923ba3ba7ae812174f292d61b91d2f316"))
    (23807, uint256S("d93bc1794bde25ee9d8ee73285d3b2cf2230cb7259844219bec705157bde7dce"))
    (31743, uint256S("bd2784e17fbb5b62604b755ccb7b25044bed572241d1cdd148bb0d552e9167be"))
    (39679, uint256S("98b4a6d839e9d870ae12a16227992754489f8d074f692d61a02dbfbaf4471b74"))
    (47615, uint256S("cf00657b8f9917ad85ecdd5b6a12def64a5801258a93c849591f47ac18a6bf9e"))
    (55551, uint256S("ed35253b2a57ff7c726d1ee5924594c27da562ab20ed09ac67a1954c1bbeb698"))
    (63487, uint256S("f6120bd0c1f2a4b5105d8cc437acbea8189c5937e281ccf9062e3e5f266b8743"))
    (71423, uint256S("359bfec7b28e0ec6f0181fcc6b09a8e53fac33800a52e577fa853ab0cc3f4445"))
    (79359, uint256S("b7fb6f78a4bcc7585770e9f4ccd6e02659c44f58f0855a87d26c1267867e8fa5"))
    (87295, uint256S("1c604a0b2880be4643d6cdf89f65a47445565a600ca7c8aa65a91d8cd425974c"))
    (95231, uint256S("0e5c0f2d0a68e728431193e2e75e072b242d0ea6604c21058c3511c83662d41d"))
    (103167, uint256S("f355ec76a5c9e92fee70d5408415735bb6e3da00d318de4fb0469023e40ae557"))
    (111103, uint256S("298d0d0d820796c4ab30fce2866a60ebdb426c9dd9a2e35ad20b6d6aa5d87f94"))
    (119039, uint256S("0dc519c06c779a61aa991508324e4742c57ff8d151eca328821a6dc03f53b653"))
    (126975, uint256S("b7e40b6e17b499a9a08148f750a2896845c4fc799f0536e4b2e0d055fbdbf873"))
    (134911, uint256S("08be0051456fac15ef3bdbdfcd8adb0548c867cd222099c9375611ca2cbacfe8"))
    (142847, uint256S("e6947f65f1183cde43eb6a07ff52002ec732f2988424737e73b014f09d6d6eb1"))
    (150783, uint256S("bf9c5631dad6e4e8ae642d3c5c6c435f881973d10efb99483f1a51fc13354456"))
    (158719, uint256S("49108855f9c281d20b4a40504159a734550df3df5577688b15d24579c6de361d"))
    (166655, uint256S("bf3cea1136834c2118f1b7abab084abba6297d38234c85bab8379bef9ae972a5"))
    (174591, uint256S("8131118f0755c0b2b632b566db6e5d9b1f459cdbf0144be7383a703ae39f553a"))
    (182527, uint256S("bc8e587c72db8eb80b888072237a894de9b05f59ebae31971a2865cdcd136d47"))
    (190463, uint256S("11f5bbac0edb4d9b22bc9d315bcc6c749725ed1a9631fe44bab5a539eb80cebb"))
    (198399, uint256S("5a0d27864de8200d4a4d8ba2fa7c26038722070fd269c55ec837356d8932c16a"))
    (206335, uint256S("ece6182d225370c3a4b56f7f4cbb1ed773159c7f5998cf7b57f49f9f5587a9ea"))
    (214271, uint256S("6c91a2e73722529c71270014894e2b1a1a799240802f0444ca8b5bb2b6c7caed"))
    (222207, uint256S("bbb293225839af557b7f89a0425cb1cf1946c75af6a16f5a1a7f207d7fec4303"))
    (230143, uint256S("d17c226085bbc8c861a0f5816d145252823f1d8cfebba34449cbc2e4d992f96a"))
    (238079, uint256S("00b558a3d3339ab6f1e6edbd14658c0b1b8485034094a3650ac2136ff2c62e5a"))
    (246015, uint256S("e1d9fa535feb9a56be0eb032cbdd55810301386efd0d0d9e7f0a228ee801944f"))
    (253951, uint256S("39a55e270184c38a4e87d8ddc5aee6ad723df7ae48f2e962a7e29dc08fc95fae"))
    (261887, uint256S("e4dd3baf569d6918e20e8044e1783ce12bce46d00ffcd93fe50a1b988c3aef62"))
    (269823, uint256S("9b0ff4d701433939364a13f7c7886c5bd1bdfe2b30a8a0ea26ac4a2721f7a9a0"))
    (277759, uint256S("52559ea303c494294a757f52cbbbb3be5fdf684edf67abae621552a5c9c3124e"))
    (285695, uint256S("0b48a237f9414aea8b9b909a87f8b18aa9bacb4eee788f592d5d3aab3332b0bf"))
    (293631, uint256S("9b81e39c08d37352094e27ec74c2c66b1e22a9b2457b045572bdd7f2c9e18ec3"))
    (301567, uint256S("831c67ce68e925c6e41ee7f469138aa6dad00c4b29265ef9b541959a9e1dbdc6"))
    (309503, uint256S("a1e2718f9d70d0dee92b25c4bd74ee81c9bf6b8244259ad31a7d0b22c37dcccf"))
    (317439, uint256S("256e969272aded577dad3de898d8f52cb58fdd166e0ea5156c772e35c1208bd4"))
    (325375, uint256S("b8684b7cde518bb3d8edd34f5f263887e09ef60595b8b722e52056e16a6474f6"))
    (333311, uint256S("aaf53dbb48f5f25b9812a4db40ce443a6569183f0bf3ee461c4fa9618b73a61c"))
    (341247, uint256S("259732f539751c3ef8323c63cc703f19f95a763bb22a0f8a4f0b834f04b4a976"))
    (349183, uint256S("b2c3be455b80313674f2d8fbb714316d589b004b699ca9c7982095202f81b90e"))
    (357119, uint256S("8968ab56d4a6d65850d9b21179cd040bae31c9b2661a98c08ea24e52d0db1cdb"))
    (365055, uint256S("d0ccbc26d9373db1f69fe2c13586467f4d7df30bb1a1356ec4efdd07952e86a5"))
    (372991, uint256S("6f930d1467d0b0638f3deb31e61ece38b76c1c982c3927960956e3592a30a53a"))
    (380927, uint256S("00b637a1c31985c275fb421dc1b7e196abe26dbddf6bb63b4d0346fdfb11666a"))
    (388863, uint256S("19639315e52f1ebccfc74b21718c6565f34efb3dd82ed224d5c60eb0b4ee6e24"))
    (396799, uint256S("331807a889047bed0540c09804be5e707cee87f1b1f3fe3b96ad90fe522356e2"))
    (404735, uint256S("f2cb8c9f3eac22e639ac487a98218b422eccbc0f42f7fe801d2e4f5951a9699b"))
    (412671, uint256S("57b64d2a457a476a6e2cf8bd3e44e776bd9a1ba4a40fe1953a1adf7563d2beb1"))
    (420607, uint256S("0af016cf55ecc01c44663bc94d296ac344f3a667b20b225854cddeeb3ee6d4ec"))
    (428543, uint256S("955e26434889fd535f90af0a8dd1984d1174cc11c6bd4fe4a52e0c1a6431c2ca"))
    (436479, uint256S("117dda7cdd827227b79eacc262a7636ad78e193d1f8579a7da3fdd685b1f0bff"))
    (444415, uint256S("8a1800100fcaaf79fb7409c0d0da7aa7efa797c26884700ad3c70e340ea254f0"))
    (452351, uint256S("092cf2c03d86ae558c262b74be1fa8eae9f95f533d399c0fd01d418c337b0af0"))
    (460287, uint256S("c88729aeb4fa24baed82abddfd4a3062b56c8ff084fd823b6504579a1e228363"))
    (468223, uint256S("93e4101af1c376befde05c3fb1e93ff1f8c3f5e13fd27a7cbe1b0cfba79eaa9c"))
    (476159, uint256S("09010b838aaca947aad7040cd54412e0218c39a47d8d136e94b7d7272031135e"))
    (484095, uint256S("ab9f824da825c23faea032ad984fc654939a3d8df1a5573910ca597b9b1423aa"))
    (492031, uint256S("bd23af68be64b364be9ddbb101d407e1da24678b2e5a077876f46fe7d3818e69"))
    (499967, uint256S("71f0ad15ffa267727243dac8379278323fcd023a14c87012150d3e9af808aa93"))
    (507903, uint256S("6971305424978766634ddb74ee62686075795e83ef18c85bdf726c87d3ea29b1"))
    (515839, uint256S("5c5b0148da97d0d8e73aedd34045fc5ac2a3d0483bcc1be5ca10caa6c0327d6b"))
    (523775, uint256S("2f7d30ea024291e5183e9b4421fff31bc685fd0235d6ac2d5203afab19dce173"))
    (531711, uint256S("ecdad8ae65b2a89698d83adc4168c6beaeca6d1732a9b9114809e0ec56da925a"))
    (539647, uint256S("eaecd79ecf484613a7612c7002deb13f349edac494154281f6d68f6ca876ee55"))
    (547583, uint256S("65a64224f2148fc6639087890f3f83fe0e3910901b052ac6721e04d2f886f41f"))
    (555519, uint256S("99b28a4e497147c3dd463bbec0f7b34243422f9de9f3021ce197281f44d4e25e"))
    (563455, uint256S("5baef52ec0e8c26b51ba16f5913f42d12bfff9477582d7e5f1a84c73c28d3e02"))
    (571391, uint256S("12cd9b83012a2e21eb23fc688cca6176b70ccddf352b24cd83f0ba6a6880dd1e"))
    (579327, uint256S("af2b87675adf4725d1dde0119b1c754f1b13554ab0a0b0a6632435666b6606cd"))
    (587263, uint256S("3966fc4a0494bd6d2587db3343b78ef9f5b5396efc313faae886b40a3f9eebae"))
    (595199, uint256S("c4f21f90fa72b3603d6f9ad7003709c922e671f7e565567142d2686a4abb26e8"))
    (603135, uint256S("fab80a71b117029597adb707e69b590b241a3112681ea2db0c9dac3b3b823e30"))
    (611071, uint256S("3f271d65261ba0339ad53aeeb6e45138d1da38592d9cd9bffe95360258c77881"))
    (619007, uint256S("f496bc657a2503f573d11b79e231803c8d5afee0589daccfd750c67939bfd0db"))
    (626943, uint256S("377f6c476e63e5d0f243072e376d889ff1b289589efa1d28e7f6f0f2a5ff3b2d"))
    (634879, uint256S("2d5795d2f1b554dfcf6902100deee97d6bf331b5ebf9d89ec86a3e17fbf093b7"))
    (642815, uint256S("f4498188ecb973d7f5763342bbd12532d5ecc2d1488d6d987ae821da1ca82e1a"))
    (650751, uint256S("172dc01775ecee69495ee69afb243c77af84ef5598d8df30c4c93bf11a8c4e85"))
    (658687, uint256S("f648f94521f99c42b1bfaecbcf716a864abf0bb2b59c55ec6f7c6ae06805e667"))
    (666623, uint256S("de83cf56306e464a5fa72fb14661e4abdb5892cdd8dd84f7070c50c5b50b5731"))
    (674559, uint256S("ad4c48ffb126e5e9852311e24c46cb2afb9bee0d7d9c0f46ad793549250c5edc"))
    (682495, uint256S("3cd143df03c9e24af5e3bebbed0a00a405ec9b598a8fe4529aa67bbdab965c34"))
    (690431, uint256S("13ca3c7964aaf3acc5412986625d4cd38d1050c91c8357b5bbe3d0328926b861"))
    (698367, uint256S("57bcd3cd225f1ad814c6a734e2db6e7ea03dcf2001bf05cdffb412360e690e02"))
    (706303, uint256S("819e90f7dd115230d29af5f87878ceb3e930aa3dd4866466de44089982272f4d"))
    (714239, uint256S("41d5aee9820d1d5324d5e2219a7aab1168bae5a978eda9967c21da32ffb3abea"))
    (722175, uint256S("11a9f90bad2a994fda6222e5fb2e80139a87eddda9e53b0e66c9973f7e742e42"))
    (730111, uint256S("80a982a69e7a81b7ce093ffec4d695d9c64dd907a1e61c626a5788164a38eeb3"))
    (738047, uint256S("74f5bc5c92570d479cf2e79431a40d7ccf31e6ed73089facbe12510c6e9eac8b"))
    (745983, uint256S("81adeb1e4d669538354559e53488d1a79c640bbde0ecd41bbbccb782603538c7"))
    (753919, uint256S("b77b7fbacf60619b9f0197b7d4b74874aaa5939688e5d29cffcf62adf1bf402a"))
    (761855, uint256S("4b6799c08f0b1d55cf956c168ed8de296dbd431e3784c9f16736171becdba144"))
    (769791, uint256S("1eb2e5554d3a39a2f28b596b3fa0e1bfccded61bc835f75d46a75ca827ed6a81"))
    (777727, uint256S("86cb89732e0fa83b78e0f7784945c4ac9178f54c1d088e52eb23615e410956f4"))
    (785663, uint256S("ede79874c98d5e898609bcb603180726d101d902eb5112d506c50b2bb2500305"))
    (793599, uint256S("7d6c4fe20f2f2595489d098389fc398df769de2a893d45c96b33fe9aa98e7eeb"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692851190, // * UNIX timestamp of last checkpoint block
    1764756,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2834        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256S("0x0"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1587772800,
    0,
    2880};

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

        genesis = CreateGenesisBlock(1587772800, 548987, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004cd0b7e3f050671ae041632a1a7c9578b3ef55da7d08da9695f7ea44e0a"));
        assert(genesis.hashMerkleRoot == uint256S("0x24c4359abe6d653e1a86916a0326cfe84cf959fdc9cc60659d3c5901b3181df0"));

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
        consensus.strSporkPubKey = "038da032fea63c7f54c820e600ce4f568a63a013570a76770ff71401871ce7c748";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "MbURNXXXXXXXXXXXXXXXXXXXXXXXTCG195", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 1101;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 1301;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 1401;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 1501;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 1601;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 1701;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("2e320a2062fec37665c7b1c33442a1aeedc887fef37a2ba208df8d136330448f");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("818dac1349e48c56c9beda5ef0015908a17ee35545febba405c5827496e981d1");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("d7777b62abf541e637ea76f2bfce77c3a878354174223bdb43d3776a7e567f31");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("00ed73543b2a555a7154421143399250e6044c93380caa9a8a722a28ad4da5d1");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("a297d00abf468b3eee50f0f80a347029691e9cd46f2a0a1f69bff8e1a099975a");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("5165a4bd37eacd57e7c61e5a3c7264fe0a50787fb30b2e97cfde7258f7a74a28");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("594bbd3655b3a2d00f16820b8637ccfaa43c83100d7cac97886ff6350fd75030");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("0b38649f5de753f137830a3c38a3785c0fd5f33439bd306240771861b8a0a34c");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x6c;
        pchMessageStart[1] = 0x79;
        pchMessageStart[2] = 0x6e;
        pchMessageStart[3] = 0x78;
        nDefaultPort = 22487;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed1",  "seed1.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed2",  "seed2.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed3",  "seed3.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed4",  "seed4.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed5",  "seed5.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed6",  "seed6.mobic.net"));
        vSeeds.push_back(CDNSSeedData("seed7",  "seed7.mobic.net"));
	    vSeeds.push_back(CDNSSeedData("seed8",  "seed8.mobic.net"));

        base58Prefixes[PUBKEY_ADDRESS]  = std::vector<unsigned char>(1, 51);
        base58Prefixes[SCRIPT_ADDRESS]  = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY]      = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY]  = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY]  = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x51).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 15;
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
        nDefaultPort = 32487;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.__decenomy.net__", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet mobic addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet mobic script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet mobic BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet mobic BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // mobic starting difficulty is 1 / 2^12
        consensus.posLimitV1 = ~UINT256_ZERO >> 24;
        consensus.posLimitV2 = ~UINT256_ZERO >> 20;
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
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
        consensus.strSporkPubKeyOld = "";
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

        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 42487;

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

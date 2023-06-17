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
    (30096, uint256S("d00d24490d3e4dbea4d52763d3adec6864deb90a42a72b63ed207f38f3a703d3"))
    (60193, uint256S("f7dd7e87c4b9d70dd5cfe334978ceb9327c81339f4d8f1ae51796cd89d3c02bf"))
    (90290, uint256S("cf7e7b93d16231e95b2d47cd03e8945a3b30759e10b37fc46bd95af7ae5ca406"))
    (120387, uint256S("fd2fc1b778ff467032ed63627c92edde499553a3c785adc34d99429964120a05"))
    (150484, uint256S("6b0173d3d6c2317b6dede507b886c40da8e8b3c32c85cb4a62f8a03fd1164dbb"))
    (180581, uint256S("dde59de82b9835182896b504e87bc668aa71ed6356fb6ccd71ff1bf7fdd74892"))
    (210678, uint256S("5c6856d469e3e5f8cfd09480a87b5c09b6a0ea4a8a565de08e916b3d523f333c"))
    (240775, uint256S("e61770bd8eda93d46fb2634b2b85eab3d5a2a30a8e8fb09b6d9dbb304e01bf96"))
    (270872, uint256S("748f1a8918324ea2b6afd60e7cf8930702f6b8ddfb98f6306794dbe92442abf5"))
    (300969, uint256S("edfffa58d09decfdfcb5bb27326585e387c15ba19c4b45f921096ec576e77c6e"))
    (331066, uint256S("78cf48cfcb899a346336be3d4376a3c821356e419ff7a23697c411bde95400ae"))
    (361163, uint256S("fb869bb1c1bd289928a302c3060df2673cffb5f897b65bf738eda89cfd5324cb"))
    (391260, uint256S("65653ef2348f0fcc5ab635caff69eedb7d645fd93e557dedfb814101efd19d21"))
    (421357, uint256S("ddf3651286124b3ebedb833e604b8185e362d45fd00b60c360b75465bfd69fa8"))
    (451454, uint256S("e995f0b85cb0b2a49a56b74ec769b1591867b135bb68f3ca4ea4ad1bec1b5ff8"))
    (481551, uint256S("776e383a156b9fd40ea89183dc9b06b8242af34ec326c9fd4c0b8356dfcf7520"))
    (511648, uint256S("2dde10d78fbb2007c4f11d9b9421bbf61c0968504356f1da79b68a0439e65d7a"))
    (541745, uint256S("046a088edd8aef9ebdcaddf6835df084dc5c7ea418b4337fa4f247c09a8d3c88"))
    (571842, uint256S("b2c8a888e4f544339b6475e44a80e79f840e8cabccab2283134e6f837fc64fa1"))
    (601939, uint256S("ff5ec0a7962c1d3f09c63b67d334f57552fe94d4b307e3cac6cc014dcfa67ff1"))
    (632036, uint256S("987e85fcfcf1f58d43575b332c612b57d3c19e4e3c0326e2f4666aa2dcea4ec7"))
    (662133, uint256S("1daa1ac1af04401dfe6a15a5b63d9b86f9ecb114e1674998ad9fea90371f2894"))
    (692230, uint256S("c551ea413eaa127725fbb18c9cdc4bc5715dd9add366e79a3a9e153ca1b12527"))
    (722327, uint256S("397681ec8a8badc80e833e1067d26ae3bf1e8235f5a6f0ab0620b932edcf5d81"))
    (752424, uint256S("824a09ed71f9c37ce304a7a31bfd53ef012a84857574c5f404b0179b60250955"))
    (782521, uint256S("cfea27172abe8728cb1da2e2a930f59b56774eef94b582f98e15e3238b2e6ded"))
    (812618, uint256S("2c0ffd4adff8c64f33a704c9e46d45adfcc2bd55307d68bbfacec608a95dd71c"))
    (842715, uint256S("a3c9de9f2b73231bd95635d97ff06315481fc923e367929e376754a7815e561b"))
    (872812, uint256S("0c49e066789ee3023747a96bfb2fa8a9fc6e61e3ecfc296c32f1e9aa88c58f4e"))
    (902909, uint256S("b54e3fe2702714af89a631e9f12ef9893f151f5e3098c540cf5e6b08ab6c0d50"))
    (933006, uint256S("dc1a70fffb18fee6361f123a2a0f7d7d2e0f355db0c3e0db21ba814dc4218ded"))
    (963103, uint256S("189ca2b6a4631daa7b2d4dfc83b28829dcab2c35ceb611ae6d324adf464034bb"))
    (993200, uint256S("3a903b0da909b46bedc2d646a229f73ee6c185c03b29f190dff7f63a6bb3de27"))
    (1023297, uint256S("bb361ec0e5fc967493ba8f312d05574bd1c1dbd4b5bac1fa833e1e755689e3f1"))
    (1053394, uint256S("9d27ad8683cc721f8a15034ee5aefcaf4da11e54bc05f65858338a09efd59968"))
    (1083491, uint256S("489f589e154172a4a0a705baceb761cfe3524c8dfafef68a765de28824e013e6"))
    (1113588, uint256S("01b559a13ea806d3bef912c7b563548beee5e78a2eeee7e746f73bc62f633048"))
    (1143685, uint256S("e6d332699b3db9669533bdfb69d81587303fb63096a526cd0434ba82a320114f"))
    (1173782, uint256S("33973f8beaf25eea1952bd5ebcd8865ba6b706271738aa6ea6ad32c1a3293dec"))
    (1203879, uint256S("6eaaad390da52966b702319213f9a9e557b3d2a2afd0db28ef6406647826454c"))
    (1233976, uint256S("6d90a02a706f1b6dd37bc5b239b7407beb39c4cca81e7c9cffe0d5870630604f"))
    (1264073, uint256S("79369181cd0078f0bd6056b1f89fafb34a204fe0d03db495dfe789bb78d930af"))
    (1294170, uint256S("b7f72671ebec08f49f773d241fff695a3956cb94628d777bb6b392c270741507"))
    (1324267, uint256S("1d8693b25576c9abe9a31362d68176f39e5b33dfa15d401d78e9d6f2d3b9d10b"))
    (1354364, uint256S("679a168a11cb5a37769df4d23f5b3afc33ebfb2f170147b56623292cc9e0e9b1"))
    (1384461, uint256S("a31c03072eef6fdf4b24e2b9db2aba7561d65981a5fdecfeb6cb7c53b315030e"))
    (1414558, uint256S("f2d64ab768511ca32ec3ac0bf0381e2e9bd9e6d5ead8b0e1d7e57d5dad956c4f"))
    (1444655, uint256S("67c98a360e4c6737f45be45047f47eeb7de7051abf0a9f62001bb37f01bbce09"))
    (1474752, uint256S("930a5c51140a06f366fdfe7ef5ae33187aa74fc762201c2b804bcfe45e99c38b"))
    (1504849, uint256S("c3f9a4a2032f54bfa97e2e02623c02c05e958fcf8caccc73b57c8bbdf1f33472"))
    (1534946, uint256S("ea99b1cc2d6836d67fd8a3dc452227d5463220fa8eb18bf9640523092abb6cb9"))
    (1565043, uint256S("3d3aecb86d98c447c47ae49d90712323c8ca19dd15af9e30f66e526a8689494d"))
    (1595140, uint256S("2869cdbd788d02b9ee951e9b9663c336627e6a20febd8d01b8dcfb7240e2ee11"))
    (1625237, uint256S("7bde046182e528365612ce296bdc6abddb44219e8cd77e24b2a42cfe6a444bf0"))
    (1655334, uint256S("c0621ee05b5fcb60a3a8fd8eddcec53fae8a1513be675ca9ef3a8a34a0821a83"))
    (1685431, uint256S("610dc2777f399d6e4829cee9bc4d9ead155f4ef6b8aa3e83de8e8486dabb41d6"))
    (1715528, uint256S("8c1acb3f73cfbf830564eafbc5e12624b30dadf74452de17b22dbfec2e9dff82"))
    (1745625, uint256S("249fd39cfe6182dc207d828f2d7a6b6645f8b8d8dc18347e3c87083f6fa92258"))
    (1775722, uint256S("8064539c3e678e6e5a33357a89e1d443a772832afc40cfdcf00669fc914bb8f5"))
    (1805819, uint256S("4e7af681096722aeaf97609d17d40a3eece09a0aed8e87dafa63d299365c2678"))
    (1835916, uint256S("3ac303b26c08e1f3e167588a545e00cb6e9e586d04b53f6d5cdd19aaf2f7e7df"))
    (1866013, uint256S("cf8d0aa2a1e24d39d6a5090c1d10782d1d47857d2cb72a6dc4d792f6bb49c4bc"))
    (1896110, uint256S("9c63e630fadc9b0ebfdc09d3d5158631cf5be2ee39809b948798c2ac03a545b6"))
    (1926207, uint256S("7f73226974b6744e52057a327e05a0481123678b195d80ce456dbaf7581c31e9"))
    (1956304, uint256S("23c2aeb5a0b79eb8e2c13614adfa49756b3e2f2e7136cf4cd8b3b70c61d537e1"))
    (1986401, uint256S("8dbbdde3a5e3a04e5284e5d05adad0733b04a2e4528361cf1d17239778e16422"))
    (2016498, uint256S("7eaea226fb9c310e19463aaf6e5154e6221c2d01fb7b352704b932b1d7e17a8a"))
    (2046595, uint256S("eaec01b90c3c808ec48982f321222529e65759c0011e92708fc413226d4b7a98"))
    (2076692, uint256S("cedd3a013df0d87419aff81286ef761959884b16937427ec5336f7f8c38284b5"))
    (2106789, uint256S("79965e3d3b9714a1d7b1413b310e9ca6ea1f5d0dda45557fb1f0bd56e6f2f706"))
    (2136886, uint256S("85b8a576212cf4bd6f1d38cc43965b9f96bbef9938eac436e5355234ff486b53"))
    (2166983, uint256S("00fa5c3b2a61fad829ecfc92704a3c019c63f29ce1809b79fdb81ca507eda6e9"))
    (2197080, uint256S("4efdba5e6ba0b3c5df935d2c2f55d572afa0f14095bcc53d62688f1457b77935"))
    (2227177, uint256S("818cd4f127dc5282f96edbe80dcc012bd3930e3e0084c202269f24ca0ee11163"))
    (2257274, uint256S("da698558d2f9bae96ddd4dadfada9f99e21e96f7568102db7f9136697ce38ac7"))
    (2287371, uint256S("2461422b5158c09df6f6d497b1352a41ccd2196c009fa2cc6824241e19d89d00"))
    (2317468, uint256S("c79436c5a914d850f7a38272c161a54a2cba576a621077443a5f36f60857315c"))
    (2347565, uint256S("72fcbfd609d0b7d5b3038e0d45649656f93b3c24e5245becca32bf6bca505cf4"))
    (2377662, uint256S("91266a5d078a486171b2b928f8720364d819ee31c1a9a375a834f504762dc0bb"))
    (2407759, uint256S("2586522bd6c573be489f14c4dd7d3610925af42f01492950ce555e0d1406e3ab"))
    (2437856, uint256S("d929b41be132d64331660b6d53261b19e5222c4ed869c787d1e74d502c9dc617"))
    (2467953, uint256S("4bc52bbcc13521953a18c4f854358f728db90edbcbd395ce7de5dbf9ad48c474"))
    (2498050, uint256S("f0bedff29ff16e12255bfd06b75bdc25a27636c904ffe630a26fa6bca0a30ac4"))
    (2528147, uint256S("9927d808ed15198f580c74a23a3fe008a88abbbfe549ae2645491db55a02e156"))
    (2558244, uint256S("2b7d4ce276f44fca5658a9a14576f7296cc49bc1cd24a1a66a1856eaa0844ca3"))
    (2588341, uint256S("3a50a32f75f94bbb700a866a9326b663693953480e68f97f9e4883021e899ea1"))
    (2618438, uint256S("5ace8f206a879ee5ee85df6d5809d32b0c9abe5ceb1ef26e66f1ff24a4f7fff6"))
    (2648535, uint256S("d3baec56fdc1d6495f74f8668470cc12600ec9ced2bb15f3729c824b2208696a"))
    (2678632, uint256S("695252e3db2c930b389138d60ffbb22cd3e8ac2d155dac349ad03f6a78d35908"))
    (2708729, uint256S("dab3fd4308f00fb89713c541d37d1502505ec6ef65c47af3aac6d3d69ba05803"))
    (2738826, uint256S("3b82f91302cc28ee831b4b3ae6dd84717246f249b5915e0fe0f46a2f32f962c8"))
    (2768923, uint256S("c30d120e25bbe900a45230e86c5480d45330a87d29e7f0ed3ca4ca786461ff5f"))
    (2799020, uint256S("65895a7065cce1e452a7c5a0c00380c0bd33c150a93abe02910edd26855fc396"))
    (2829117, uint256S("9dfde4efd0044ca08e8a64867b6d53f7e67e8ed1b38e0731272a12e636d94b4f"))
    (2859214, uint256S("822bfb5921dc027d1d79014ee9388b0ad2dca1a2313e5cf882151eda3fca3ce9"))
    (2889311, uint256S("c98e868cad35f6a3256ba40e6aa400e6a3f983baa72f2690e771dbe4e8cd2923"))
    (2919408, uint256S("cac7954718e4e09207cbb2f14b3c6823d05ebc5e65adb01657f5fb1d9b1bab84"))
    (2949505, uint256S("7de92eeb0acd58217d7c13eb052b0515f3e02b1608f44a40e9018c2a41f09032"))
    (2979602, uint256S("4470e2776be4e7bbec859cb4ffe872afd9005cb24e0df40fb8178bb093cff054"))
    (3009699, uint256S("f691300c8b3ca028f5e5e022dc6b368b4e9af665cc7ef0069d758506f082874b"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1686959925, // * UNIX timestamp of last checkpoint block
    7753822,    // * total number of transactions between genesis and last checkpoint
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

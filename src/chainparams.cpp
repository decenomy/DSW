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
    const char* pszTimestamp = "Another 50% daily gain for Dogecoin confirms 'alt season' as Bitcoin slumps, 05/05/2021, COINTELEGRAPH";
    const CScript genesisOutputScript = CScript() << ParseHex("0478505c5bc438e08c0c8de26a661bc5a4453378d0b149fbf17cb3e1499b1d3e552fe5faaa253673c5349b461bd964a2ee860c114e9d2b9fdb0328f37ed356ed54") << OP_CHECKSIG;
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
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (0, uint256S("00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"))
    (10327, uint256S("cb5ac68e75a2910800af6f9bfa9f3670d97b7d330619cc1ab9d80b48118a905f"))
    (20655, uint256S("c323ed4275fc88ba8755682455c59806046d222bbfe26fc097d245418b14dd07"))
    (30983, uint256S("ee5eba76d6de51a0d50f45de98671421eaa252bb1729e54f5bde3458dbfc532f"))
    (41311, uint256S("e247d5d9d58aa7910eb3a6521922b98e35d9355c0dfc31d0e2f4a87d28db5113"))
    (51639, uint256S("d69ff4361cfe49f40669d2ef1282b24f95ecbf2f501cc53a25011d1858261c78"))
    (61967, uint256S("907dfe24568810b5b239233bd3c17317ed34f16a605677480adc71fb73317ec4"))
    (72295, uint256S("db392411b984ba7b5bbafbd744f378ed9c10716ab887d1205724e4d1e346bd1d"))
    (82623, uint256S("ad8643273506befe7d8b15e1dafb8af52590f65fb60e2696c85a26e19dc63ad1"))
    (92951, uint256S("8543f1464970ba4e1adf2a052216dd95786debb843d6e00910485b28de9f6701"))
    (103279, uint256S("5eeeb95ea895841618df563d8e8f26947830a3f2206219be5ca388b5bf10ce4f"))
    (113607, uint256S("a55995e87b8b7e06ade552151f45b37655b2abbb2a47f94b05b6558f68918b9d"))
    (123935, uint256S("c2e787487eb637f6b6a07ee31db35573bcfed6e9cc597674f14518db650328ff"))
    (134263, uint256S("c874249e5876ed2514cb44ecaeb71071d228279cd564e53696020e621958a54e"))
    (144591, uint256S("524b3f9dfaaa381844e9312f8ca8e11fbe08e78d06c95ac9367b6336e94e844b"))
    (154919, uint256S("ec4bc8a50075495b28ee06d83f8c496158301733787219f5535db6ea314e28e7"))
    (165247, uint256S("66b505007dbb32c66906000f07c148f9c0842dc9b10fd0561dfacac61060a8c3"))
    (175575, uint256S("a6a8605c8ac02e102639a524b3a4966c62d12e61a7b96dd879f31a8c50695759"))
    (185903, uint256S("bb883e4edd24465f1eef9786d8c3ef73a6c4f4d60ec4391d6aaeb5a6596b968a"))
    (196231, uint256S("5b4dace0f92f074be10d5f3b4744f734d9907479fd04039092c9b76a576af9f0"))
    (206559, uint256S("56226c3d183e67405ac67e66871cfccb10ee6ab28195592386f2cce0c08263d6"))
    (216887, uint256S("37848f1d5714718d53ce8283856f72ce0762b27634f3bbd6920daec0eb1c7f63"))
    (227215, uint256S("6e19e1d66174676b0a176fbe25185934019379025bd3d685b19f1c35f1b2b9f1"))
    (237543, uint256S("3471d9c280f9caef9eff67ffa6eeae39e58fabe4f73b3cc777451d9cf84bfc1f"))
    (247871, uint256S("0a3c7073241ac0af1ac72d9acff25e501459427da3dc4abadc64439f3632ce70"))
    (258199, uint256S("b101896d6b31608587629587b62d90fd3072fa469d06f03f14791e37a67b2657"))
    (268527, uint256S("ecaf67b71ae5bef40b4e3ec5c5b7181776214666f88cf84c9c1aeafc8124af5c"))
    (278855, uint256S("4d0a433aaa4afb3f30a92ca830c05e038e18c995bfa253077896f252cb7fb95a"))
    (289183, uint256S("1f76eb8b3ce413483298c616e00cfb96ebf7d0349cdecee8793adfd5cd52eed6"))
    (299511, uint256S("98dcc3e3b94308505c49f29d83e4006a8e1ad3bc053640d94cb07b01e73613c5"))
    (309839, uint256S("53794a491106676466e8eb089788db49e430b145e243912c06748b0b0f013cbc"))
    (320167, uint256S("0709f7de6cd5b02b6636148093655cde30c096b5ecafb79b258f4548d3bfb6ec"))
    (330495, uint256S("efc891b4a2adfdefab0fdf4ea6582e9a05c09d5952734bc83d0e87f8d6215a32"))
    (340823, uint256S("24f7c34515f4ba15cb20a40074c2d9d844c8cf5a6b1f662c0e6282b1ec7af369"))
    (351151, uint256S("2f6e9b8e18a6e04a00a1a0677032b85bcbdf04e509e7fca16514dcc259b69c48"))
    (361479, uint256S("d953a90b71326d07abc75db6ae6d3c62913874c06f00bb69e0236f9e48b94c20"))
    (371807, uint256S("6bb1ec14515e63662d8c0ee05bef4ba37be01277e0d110fc14544923259e6283"))
    (382135, uint256S("177dd9e9facedd65fdfae9d70aa7984c6c9417356f6692534c4a2d555bda676a"))
    (392463, uint256S("c528ab5bfa2c48415321fd16cb2daee874c7f57afada412b23aaaf8856d359b5"))
    (402791, uint256S("26865f1d2c448443f7fcd955d27e70d4b1785eb8eb02db27568ccd0c9f7f2449"))
    (413119, uint256S("0809af8e7506c102b23e1196aa5adcafa60b0939561175e39e4d3ac984de4a71"))
    (423447, uint256S("7289a7c5808b2cd1b41676eff976e5c3d39f75ba41b3235665d3c2e240b6cbed"))
    (433775, uint256S("7baaf85f8343f945ce8f4c085d086338d40ab2a119dcc853c00e183365369e26"))
    (444103, uint256S("c4b90e9636817aa7a4f0663450a4275da0aeec25d010448f9f0f971f5f358433"))
    (454431, uint256S("4957709add68f0f5876f7707023383350dfb3f965a35258dfbeef65c82fb9fc6"))
    (464759, uint256S("fc4026d849231a1afb9e27fce47a5385b1c3b77f51a7fa6180822a92df52631a"))
    (475087, uint256S("5425e8b7b37130bf0726772f9317de7f7a349432d0223fc788854254ae8347a9"))
    (485415, uint256S("79924d727a97037a9e4d6c220b362a79635febf5f5661f55c69236a9d1fe09e7"))
    (495743, uint256S("fce3a46feb6ca4bf723ac939cde133ae519bd40876599bb860339d35965ff0fd"))
    (506071, uint256S("e28c5a67913782737c847660784fa832c44ebd1bd6e400239e3e0ac8bd67adde"))
    (516399, uint256S("be6504451f8ef635cbf085e83e0cfa375d44dc6d381d78fefe01a94d3a615c51"))
    (526727, uint256S("465ecc9205c409908b0bbbd9c52ab3922cf8b3eed0b4ee951101f1f7688eeb78"))
    (537055, uint256S("eae1a9a5ab312bbad2218ee598031925197ec63ca47515e47a1a58576596ad33"))
    (547383, uint256S("9bb542f45331836ece79e1893155ddc8237d1086cd5fd61eeaee4ce25e7b7808"))
    (557711, uint256S("44d495dadfdbdbeed269c83988f93622fa599bb1e5667540ce44550d37b09758"))
    (568039, uint256S("ed7091eab757f8568c0e13e2555fffde239abeea1bee57034f298d8401d87c01"))
    (578367, uint256S("8acfc7bf524297f4ff21fc96e761d62dbc4bd85a064a0de5b0afbc028fde7328"))
    (588695, uint256S("565b1bfde7b12db2a2f68b0e04a046f401f96c13d5bcdfd08d59af2404d0082e"))
    (599023, uint256S("81aeae06933e90b9934bfd7b5dd7f0d72744e53e6c8359fc74cae751838f08ac"))
    (609351, uint256S("9a306c71094706157dd9ae82a91a12240fba5f9c2f3a94218f299461d52dc9b8"))
    (619679, uint256S("2d4ba310742101d5519b4248349f8570a41b7a3a4d44ede8e000ac885840e849"))
    (630007, uint256S("f716d4ec3a74607f72c3a7069c47f8156e367981e4f6a197a579cc0be2614f48"))
    (640335, uint256S("05e4d5d6da3c7a3c28ef3cf2a74c415b02d3a91ccda836231536a0910d9b4ecc"))
    (650663, uint256S("f0618fc245c6a3ece6afab5d0872fec40bd8a801400c57cfe730e202bb339d59"))
    (660991, uint256S("ab0d3fda021e0d566796375774acb6c4850078470c882775496d52e90cc17b4c"))
    (671319, uint256S("1e8988afa7f7d4f42fa826d0ec6fdf99752a4205c384b09ec47c55379942dd8e"))
    (681647, uint256S("2a3caa3539a6039e4eb67cbd231ff24f3a4c8383cdf4471d9a33eb5b38fdea0b"))
    (691975, uint256S("84f46381597382ff85758e3529230c291dc9e3be81591b09d11352040ed30beb"))
    (702303, uint256S("ae1cc0d98bd5ccae3edaa76ba72357bb80f11a9e11fc77f535afd8e0d0d98049"))
    (712631, uint256S("9a9a252233f55d32ccf99ac47409df0ff98fed1692320a79cef0b02ecc2f91a4"))
    (722959, uint256S("98b773c03a236c5396482f10992aa2e5f7ee7e7c1a385a64d584f6c5e52b2f42"))
    (733287, uint256S("d75c5bb158b21b9843670d42c61013549a88e854feecfbff976b22e9d38ab6ce"))
    (743615, uint256S("7ab8e1528f594e373cda97adc1ba4b1f5a4d9f91baa4b638425f23aa6d8d8e11"))
    (753943, uint256S("7516110ebd1119d694838f6d8d5c8aaf7ad59394ed0bf5dec662acdb9887ec80"))
    (764271, uint256S("ee3199c274a163edd990d8fef549feaadef54ee1e2af1b51edc1d53632e7b0c0"))
    (774599, uint256S("bbf1105ec250875b4db4faa1f7cab11b598a04edbb776e249c1564d6edb88ffd"))
    (784927, uint256S("9ff75c741c13ec2729e22cdfb6fc16f674e235d7f6c0e39c59df862912d9979e"))
    (795255, uint256S("d145e63ac85ffe599871018cb56195d72abd8909ab10c08064ebdc8a0e23b7d7"))
    (805583, uint256S("7c13cacf8f2f935c1f7dd8fc9f3562451ad6eb6045189f8f7fe29902d0dcb1ae"))
    (815911, uint256S("95182153524751c60886c4f2d620abc332fb51be55b2d96d66ea43c3e5ce3e81"))
    (826239, uint256S("e1bfe5d29562f29243fdc536f3ea0714fc6e3504c48104dee11e6ee2121eeb86"))
    (836567, uint256S("ee98c4b9c0414c36d38e3a551f3ac0ae005ad5b08f049e97bca195c9d7ff41e8"))
    (846895, uint256S("b4dfb651b61418060f9b811b4efc0a02174322e400b6051494016b9983a61351"))
    (857223, uint256S("9e5b5a6673b88142a5aaace774bb4b3111aba4101c03cd13331af8d1a2d0b363"))
    (867551, uint256S("87baa1f2dfb7c9c11b039e0ae7295fd3b9b4196c6f6d51e8e3a8e9826c2056d8"))
    (877879, uint256S("58f926af94d9749bae0a2b7efd221846dd52cc778f51981ede3fe50b78fc68d6"))
    (888207, uint256S("7b07060e1010a16473773d99e7b988e9c730f9792ad0e539c468ee65acb83c30"))
    (898535, uint256S("85cf3031488e6a348fa39a3f257f7df15afd58a8d1ee44eb30fcdc6fcf957b14"))
    (908863, uint256S("10f32ffdcc8e60d0c9ebd55e1da49012852f5c0eb4693cbb6d7f4f7ed14ab39d"))
    (919191, uint256S("05d44fd607efc20906b5d912d8e5d71559a805a44036ac2dde56999c4a9f9981"))
    (929519, uint256S("46019417173bddab64bd20a034f9b4e328ccaf0542bf14bb4689bd9d82806518"))
    (939847, uint256S("9f87bff96226bf2aa0a42510406fdb9f148fce7b6f20dac8151e36073e07f74c"))
    (950175, uint256S("da739b3c56c334540689c99109f46fbd16f6df8a1d8f6c908f837eabdbe74514"))
    (960503, uint256S("1daaf740adffa26f59dd9d6898e2e32b67022b3980a62f88f66eedb363883331"))
    (970831, uint256S("18b51611350f0652c9a43981dc4b2f6cd3bababe8cc32297a23451afc4113da2"))
    (981159, uint256S("23163be2f95d034c5fdd8bd8304abc33c19b36fa35026c37f69ae1b73dd0a36b"))
    (991487, uint256S("8b7936a6d0a62e2d5634f1e8384393d80e46a053d4d80f52fcd9ff501ee3b1c1"))
    (1001815, uint256S("b6bd8ef4a3d9ca8bfb3f1bad1308926a42d1851f5ac452d4c6300c9afa152fec"))
    (1012143, uint256S("77b281c54750913f867114c667f1517504d6674f3156eec3689ee81ad664267d"))
    (1022471, uint256S("38563e4bf7cfd92c3145243c9d5bcfb46fb91184e815418397c2732d9f6b5f8f"))
    (1032799, uint256S("4644ec08125589d34213dac694dc816a0fdd5cf5b59f477d6a8d85cad7b301e4"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683729435, // * UNIX timestamp of last checkpoint block
    2196262,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2828        // * estimated number of transactions per day after checkpoint
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

        // uint32_t nGenesisTime = 1620224091; // Wed May 05 2021 14:14:51 GMT+0000
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

        genesis = CreateGenesisBlock(1620224091, 1077816, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000cba6292e19e08414e173011e3d8939487d66c161805d321d65567031f19"));
        assert(genesis.hashMerkleRoot == uint256S("0x5322195c37996cc752786ab95a76b328f2f8e03d3a9b5ffb465173613d4f97ab"));

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
        consensus.strSporkPubKey = "0273914d51723890516e319ecf24d71749da673c76606941290a0db4842389d693";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "bXXXXXXXXXXXXXXXXXXXXXXXXXXXZEYRfd", 0 },
           { "bXXXXXXXXBURNXXXXXXXXXXXXXXXZ7L2xb", 0 },
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 115000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("f4f586f27b0af2d9307015d45b7ff3ba72821ce54bf45110c0e034bda22a98cf");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("18f9f894e0be014ce81844f863c4844e4f05f4845c3744665393f1bd6ca2b043");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("c33e160f767be68f93c57e2c5af5d77e7d1c83bb82a345f6f2d4ea968a3f5d95");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("70ce131e9bc06cca48bcf8bd0f0f8efff93fe6e34ce9caaaad984c66616f7245");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("b13b0ac7e05c537438198d3e181c2e9796d0fbe9139e2ab3f33352fadd25dd35");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3e2e44e642974c48c9c2e1b6efd5fbb88b253decc6878a9ee64e7242abd5ed5c");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("9ce29639f18a952d53bb4aaa2600279c1aef9bce52089b1c970da24be993ae3a");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0x2a;
        pchMessageStart[3] = 0xc7;
        nDefaultPort = 36552;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 85); // b
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 25); // B
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 213);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x49).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                  = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight             = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                   = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                 = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight                  = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight                  = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight              = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight    = 1841;

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
        nDefaultPort = __PORT_TESTNET__;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed1", "tseed1.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed2", "tseed2.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed3", "tseed3.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed4", "tseed4.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed5", "tseed5.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed6", "tseed6.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed7", "tseed7.beaconcoin.net"));
        vSeeds.push_back(CDNSSeedData("tseed8", "tseed8.beaconcoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet beacon addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet beacon script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet beacon BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet beacon BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // beacon starting difficulty is 1 / 2^12
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
        nDefaultPort = __PORT_REGTEST__;

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
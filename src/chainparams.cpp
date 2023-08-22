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
    const char* pszTimestamp = "13/Sep/2019 The EskaCoin Launched, It is fantastic!";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
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
    (0, uint256S("0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"))
    (20073, uint256S("fa600daa8f13d0a5554c213a2da83b511036e04957d4dde3d2e9d4e3238f8b82"))
    (40147, uint256S("6eff9ab273866a3e5804beb842c436cd6caa97bd01367d3007474a5d35bf3d1e"))
    (60221, uint256S("233bedb36ca0ddc669ef07ad07d9926027de023140e9351808aefe43f119ca3d"))
    (80295, uint256S("4a82520962b33ef8823166471ae789f8d84ad6f346f2b1f46b25de1af5897c58"))
    (100369, uint256S("d4f7447aa63d2ac5a8af4ce00f6ee5ff9e197bc6d7374a0014d04e0b913b7ee6"))
    (120443, uint256S("ee15feb6003d5184a922173d35d3b34d0c5403617a22261b7bcfb457763335f6"))
    (140517, uint256S("e825c902d4d0c343d0219cab886bfe2fa4700c6e007d531d3d0392f14424c3d0"))
    (160591, uint256S("56e68322de3ad917b8e3fd631dc29b4b4454f0dfe8b653b2665930af11010e1d"))
    (180665, uint256S("63360d95c4d3de0bef30a47be244ed7bba901e7c5578aad0244d42e205d3709e"))
    (200739, uint256S("0b3fb90e9985a731710b49666a64027ae5ee31cc8f01ba8f4701adf65860d0c4"))
    (220813, uint256S("6dc987e8c289405fb9b7c2338eb3ed9168ef25ab2c7793388453f9d34c7ad865"))
    (240887, uint256S("5cbcda7385ff9dcbc021093882148d104dd3633d148503327b21f2e2c21d0f90"))
    (260961, uint256S("6b91597e7bf3a6e34f1a3661fd1d26cca4ec5fe1bd05ad06db3ffca52d162ddb"))
    (281035, uint256S("5aa48ddf6172b2d91eaa96988cd43742a70c6af2c696a8e0e7456499da459e89"))
    (301109, uint256S("251b0c7fd478e017d98e4c3e83d30e4ac50d4975c0f39165f207daad96ba7ce1"))
    (321183, uint256S("8437caaf38d0682f94d92fdb84bd134383b96e0e9bebab1474f228cea5c844f2"))
    (341257, uint256S("b5d2da3e53381460311390ef590ede76da77a037842bb1ba930394f6db89ff81"))
    (361331, uint256S("ed659709b29ea7247f602a3047be50af77319e2d381b0dd4a62c0dad3161a501"))
    (381405, uint256S("f94f9149dbebcc55d299bdbaabd7b4a602592419b86036858e0bd65df7e29f75"))
    (401479, uint256S("8f4641096176ca71dd4a1b13dd19b39ae6abdcbf1c777b66f8a63f544d93a1c8"))
    (421553, uint256S("8912fa18e49e0070dafe74c9f33d5cc502f8caed4db768f5952ad2668ffdf28b"))
    (441627, uint256S("2989b9838930086080a0cef0fd2bc8723076006cdf178ab9da64418f9ae79fd4"))
    (461701, uint256S("91921b0c7f96cb8916824f63dc798f1e4abbfeb467e760aca077f0dce005dd95"))
    (481775, uint256S("30db6d69e7f99520f9325e3f539d75d14b0c5c063263b5f62d30531b16aa9275"))
    (501849, uint256S("1062a673b0f7e34a64d4e5d158f49ee98c712369ce32aa2d9f6f7f6ad305c63f"))
    (521923, uint256S("50ad3fff9c82da796c78ed4c6f1d3b5886da2a7815a5e0d3da98da9095bf9618"))
    (541997, uint256S("046a865a492ce5f979b09cec9ba07d9eacec06f115d42dc921d524a24f3529fa"))
    (562071, uint256S("4030d4150e7ab653e48e0add61a439cf8dc213db45b1de21fec8333bdddd9360"))
    (582145, uint256S("9bd0f394548bff63ba5d8d13c65f4563ef23ec7a2b5fd8e9a09af592acffec5a"))
    (602219, uint256S("e1bbe9175f15002aa6cea5096350bc7dc8bb89b035de6d4803c12d7a1a0d4152"))
    (622293, uint256S("33e9943ce92c887e4f4c0329e7bb70b4fb9c942d5c86a85cf98104ea438b0602"))
    (642367, uint256S("89cab068f50616c97f08b18ceda88d41419912c542810498551a5e59448c15f0"))
    (662441, uint256S("cc374e51c6ad0fa338df360d67b053bf2d6b31d12f5821f4aca187106be01cec"))
    (682515, uint256S("9d748dffcad7b213ae7cf3536439078eadefefb989b6a77e8c354173062b2de8"))
    (702589, uint256S("2b0f093b87c07481ea4a3c480d051aa55bbc5c706bde4f6c615b3ed0d1eb68ae"))
    (722663, uint256S("dc8fc65d5d96a456d785de7c8b76ad5ccd8f119e538afdc473a303f87bc37a6f"))
    (742737, uint256S("81105aa547c77d17b0d32930d8eca50f0b0e41488806facee0b831c86e947821"))
    (762811, uint256S("ce38286956caca0ee860b5490441ea4f011e2444e6208ad844dace63bb5d3f4f"))
    (782885, uint256S("1a1e8cef6c01963274ab611c8daf59f107cc8876666c481d5af5aca4ea8f7239"))
    (802959, uint256S("75a570cbf1809a6b0fb270d77f8f238a425ef97587413e7d837057b228c2f08c"))
    (823033, uint256S("1b23a7a80c4cf63f59de9abdd4fd152fda03a7b47706c9e7e9ccd166314357ce"))
    (843107, uint256S("072e381bc5635d5f6f250620a562c9daa10b4deb9da12857035514cbfe61b8f3"))
    (863181, uint256S("1de8e770a077a36ffa2e7bb1f0c511e852f375422820863186e93f39d97b5321"))
    (883255, uint256S("33f202c918c63f70567997b0e3e425d87ff328e355eceb10ba9c2a1afa01f340"))
    (903329, uint256S("f2d20bc76ed6d0fc99902e10de08140f7c8abe97ce32c8cb9042219b93f677e3"))
    (923403, uint256S("ec6c5e1d4e42099fcfc75b73cd1384191d70c05488c7edf72c394b4cfdeda7fb"))
    (943477, uint256S("90b93b6fde6c625c9597802379f5283f094b28767c0811993dfa420309926961"))
    (963551, uint256S("d57ad33898c10b7ffd31baddd6bf7a790dbd5567993c2fc3bdaa8492549c8eea"))
    (983625, uint256S("d271eb86755667ac9d2fc2aed5582a36a0b6e4770d1250e7b53e89abf9d7674d"))
    (1003699, uint256S("8311e1c9c48bf0d1a6380340263adfccc4bf6449984d75ae4b315dd0bec013a8"))
    (1023773, uint256S("e3994594baf41c1312318e8adbee7365556cef1e53cf64e39dbfb9a31ec2b2ff"))
    (1043847, uint256S("824e3f83876293164774c6fb4e41f78d42c1f4e4bef068f2ba6c5962e62c7a46"))
    (1063921, uint256S("5896661216557e7f6e70187da8a0f1aa1deabdb470b1e5e6e8731d2f3b1b63e2"))
    (1083995, uint256S("28964546ab67486ec7306b97485403e7fc2d8d2d7ce80eb116966a3584c1cdaa"))
    (1104069, uint256S("9baba3596d789ac022d95fab289be8695b399f43440209f90a021d7df2fa3991"))
    (1124143, uint256S("eb829908a25819270043ef75549256b5f1b936bcc216be391c6d2962ec95ea42"))
    (1144217, uint256S("2f96e990db90d0e7f1e2f559c2627b14f4bea5cc241bdf7b5d380dcb64a404a7"))
    (1164291, uint256S("2c812c22397de88e1ec0c9af171769eecb6e9e1f50345cce0a17b7a72c65ba62"))
    (1184365, uint256S("999591188c35e30441f605277e2790352c1a2a459b14ef2f191687e6e6506f23"))
    (1204439, uint256S("aaa2169b37306733b6e3ac420426c053e2342dbaa85fd65ea4bb9324f07971c5"))
    (1224513, uint256S("a423c4de51af94a52eee57ee4ed5d6e3388fab4bd7bddcbea13fae4f63549204"))
    (1244587, uint256S("da860783ff921e123d16d87765213bb2f9e1e27f980d71e383590cfa722d826d"))
    (1264661, uint256S("26a3b8425784b715f737fd6912050e2585a73fed80693968fffdadc881c95007"))
    (1284735, uint256S("d79539ed85fbd4d758b51c2e1e162d860697b5ec457f613cc0dd1237462cf222"))
    (1304809, uint256S("8544515b386b4c08c6b2548bba2cc7e3933c8efc2ab66a36a5f50a9c9f81aac2"))
    (1324883, uint256S("33d5ce1ae6359c37fe4d46fafd313a1225ed613a0ff27d1cb3fb8b95632cdc5a"))
    (1344957, uint256S("1f8fe49c1ed5814aa14ab3b20f298d1bc6251f41be0e9275995154fec57c7a09"))
    (1365031, uint256S("5db19ace7ffed25e43e404d3a937290e799b6a6286942f8b5ddde0e768a7740b"))
    (1385105, uint256S("9b2c9fe7a3cbd081e258f41a8e22257d3cd536780e7249d8f3c4e7ce8cf168ad"))
    (1405179, uint256S("f87bc7e17833639d0cae3333e0ef7f89e29b190f87ef831fa8238e34f1ee99e8"))
    (1425253, uint256S("c1455f19018dabb95c9954c9554eaf92b57d5e4606caaf8092a4631e761ec815"))
    (1445327, uint256S("8c663b490752f17adf8efe465b0528eb8a652c917bfc13c0d86f6ac8c09270d0"))
    (1465401, uint256S("f5256fd2ea18cd7cdf97d173dce4ce7a9acf7504e4fbb6c1d7e788fdc9ad71a9"))
    (1485475, uint256S("3813b198509c395fdc715aebabc9555993512227957b6f1de2b76a6c123de0c8"))
    (1505549, uint256S("4b4976c20e3297416da6bc55bb226648ea09e97256a14761243de1d1044a2c29"))
    (1525623, uint256S("80745ca0106e578ea7ba61c8e0cdd362bdb8f2a490a30c4685546adea3e57aab"))
    (1545697, uint256S("e5abc0a716b8993cbd743002333a61e659dd9b37e3c923e1e3a02673a48ca460"))
    (1565771, uint256S("dab5376847d465e8bc6db6f89a9935c94703924a5a5b8bcb423cdd6d5ed67167"))
    (1585845, uint256S("e0007f693dc1938f8f862a598fd7516f118b42ab89c2016d3e83187a28ac91be"))
    (1605919, uint256S("177c69a4b3892f91c93655c35e58e94dc90fe9215570e88c42c53c3dcb3faa56"))
    (1625993, uint256S("93d38c0af0b5311ffd4f817f89137869cc3ff268a9cc234fc508bd2427079d96"))
    (1646067, uint256S("98ea126c29032480fee2ddb48d8554d8bbd976e6871e4d3a19d8b4cd1b2f1f4f"))
    (1666141, uint256S("be927711aceae348c0aab507d54f3f652ee264effdb0db1e1c5d959f5bf4b959"))
    (1686215, uint256S("de301149ece2ca197eb8707b2fe1469f1a32d350309113881363246fa8214d22"))
    (1706289, uint256S("854b96a8a2ca9e5b5a774e3786f1d06351ad346760e0abcdab0d08d7667cfc5e"))
    (1726363, uint256S("c7d38f8455a168b063cff34cb1a721f26c10e34b9d29e562a34e6df053f5123a"))
    (1746437, uint256S("ae135ddd7c261d495ed57f4a56e71b0339fbb62868d38398ff86fa60d95fe07d"))
    (1766511, uint256S("5790a12c2d3836bef56e9aa6e98a6d5bda4dcd6f8ddcacf5ca0d88a4e572b76b"))
    (1786585, uint256S("30503f33dde80a3ee5dd31486af27a7a02b1027989e568c756a1917b60f972be"))
    (1806659, uint256S("806259e794cc1d0b45e3711e5ad66d716c91f28ca96dfd3206a348da4b134b48"))
    (1826733, uint256S("1385c974c6580e86f0a42cb043e29a8b47004b37188858d10e64d2fe5f63ab43"))
    (1846807, uint256S("e5ab0252f3801f4e01125823b32e28cb965d7b3222317fa2f0380d6f7c349583"))
    (1866881, uint256S("d82b8d3882d3d56cee87c07773140e1c66992a83660cf040f3ea081cd1a2af62"))
    (1886955, uint256S("05514185dd34fdc0db52af77a68ed2b71009189ac38e6f73d07a20135626a8d3"))
    (1907029, uint256S("147839121ae0f180fb50856ff085f61f83534c3ff5995d6f3e75304e3a23d645"))
    (1927103, uint256S("79bbd0420c15f0b0899b9109b8398d9279c5a87b8a01099ef05c162a794bb830"))
    (1947177, uint256S("671c7741410f79b2f9a9920c46531dddd55d751ea303d4513c2fd7d4052d09f5"))
    (1967251, uint256S("15ca838a6187883cd7d66187ebb36db42f77e9edafaf6f138e63db2640316bfb"))
    (1987325, uint256S("54456065244ff216e591b52cd38baa855973a7485dbef43dab8b9810b90bf8de"))
    (2007399, uint256S("9661ba0903f557765092a108fb3b359503198e07183b61c411c47e57c7e695c4"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1692670155, // * UNIX timestamp of last checkpoint block
    4675514,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2826        // * estimated number of transactions per day after checkpoint
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

        genesis = CreateGenesisBlock(1568452814, 7414, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000046879caeeaee24cbe95250a677cd08b0cc920e1f1bcac32f19e7256e92a"));
        assert(genesis.hashMerkleRoot == uint256S("0x036399fee1c5e4dcfa9c8c4f2458899d6de3a1ba0df04e77b7ac10bd09847b12"));

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
        consensus.strSporkPubKey = "02aeefc7f24b3919ff05a7d2661aefba6c37ca77c263a20e8516dea630fa74e9bb";
        consensus.strSporkPubKeyOld = "043B44A0D5F6BFA822208E19096A6F71A144EA1034A5ABB99E458DF1463CF98E72FEA9E5C5038EF7716765D248DAA709A23746606AF41CAC59DC071E89624C9FA2";
        consensus.nTime_EnforceNewSporkKey = 1626393600;
        consensus.nTime_RejectOldSporkKey = 1626480000;

        // burn addresses
        consensus.mBurnAddresses = {
           { "EbURNXXXXXXXXXXXXXXXXXXXXXXXYdqMFj", 0 }
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                   = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight              = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                    = 252;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                 = 930001;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                  = 1;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight      = 300;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight       = 930101;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight = 930201;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight     = 930301;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 930401;

        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("00000d59619662288595b3e38ab67f243e60fa47be9b8bc49ee36d835cf1d2b1");
        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("4f223b064bf7ec695c08bb41701ac4e59cea14169e86a2c5f802c8c6c29508f5");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("0a10b03f191d41ea4d7c8f2170b2b5a57a193b77270e83185c60d0ab98ea82ec");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("6124f4600579296b9dd3973c13b6a24ff84aa0fd06e66b35356cb229eab8a6d1");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("aa274bbdbea34da289250e73078a5912e6edf6e93977bd8474be1527993ca09a");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("537221a9b3179f9d95c4d84c6c28321fe7cc1d4a1cf2329e1dde87643ed39187");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("dc97bc8e643eaddf4b0b0726abf437f39ffc7df5eaa646957bf7b03bf817c5dc");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x34;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x1a;
        nDefaultPort = 14215;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed1", "seed1.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.eskacoin.com"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed5", "seed5.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed6", "seed6.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed7", "seed7.eskacoin.com"));
	vSeeds.push_back(CDNSSeedData("seed8", "seed8.eskacoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 33); // E
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13); // 6
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 145);  // 2
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4D).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14216;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.eskacoin.com", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet eskacoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet eskacoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet eskacoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet eskacoin BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // eskacoin starting difficulty is 1 / 2^12
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
        nDefaultPort = 14217;

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

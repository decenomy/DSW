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
    const char* pszTimestamp = "China to socially blacklist Bitcoin miners in Inner Mongolia region. COINTELEGRAPH, 2021/05/26";
    const CScript genesisOutputScript = CScript() << ParseHex("04cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda03241a96752373dd49edef35f384368993d65afab7214bb870bd95be32606c477b7c") << OP_CHECKSIG;
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
    (0, uint256S("00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"))
    (9987, uint256S("381f7dc7dd566780dfb2d066ad67697a9d77f6ae464d1599339d21ae02943ac8"))
    (19975, uint256S("a0b0b6161a13cfe74ec953e5c252fc13ce8afb02d9877b67d46e565b30dacbf2"))
    (29963, uint256S("f3fcf3c35c854abf77025e050d20bb4594c1037c8f357353e3ea87dd527c1619"))
    (39951, uint256S("5f761f63c2803c7320f5028306f7773ddc9d016cbe0fa32258bd4f9c93b92fde"))
    (49939, uint256S("425da350ab36cd7823d39fab8c0394ccca257260e7be99fca360003c502aff2d"))
    (59927, uint256S("955166b4c3e1570758a29da1544ae9a300205d75fc38f4fddd01138ecf3585d8"))
    (69915, uint256S("73f07584f0bee2a2f8b60fb0e1d1ce7086123d97a9d564d6b8de67bfefeeadf1"))
    (79903, uint256S("44048a0f6b14ada53d7d29c462449a4c61a9df53a6373df6db136a493c2e5b4e"))
    (89891, uint256S("70645c3caf36cecd25e7c701b2f2f0264eb55f46b40ef00037a95afddad5844d"))
    (99879, uint256S("5c632011af6161fff60d5f8ed0aa49b392c9da74752bea30250738a5ea438323"))
    (109867, uint256S("98942ef2539d3cf9e97fd8f88c58376e657b2284d3b809e0e4887ab72bf09ad6"))
    (119855, uint256S("ce987d5aa47422c4ab6fbe34eb9d85b218e95c62e6bd74390b5e192fdbaa09de"))
    (129843, uint256S("77f0ccf8520095ba33db1b6b2606b47935d9067b372fd1cbdb672072e238429c"))
    (139831, uint256S("03baef4db6efdf17ead1c29fa28e9fa466e08bd075255fb3a314c835d97d8c4f"))
    (149819, uint256S("9ac36b795641790b21ea3cdec921e147ed35b48ab4a4fc37454d9f72cf6d59f3"))
    (159807, uint256S("b7a74829965cd5cdc13e3bdcfb454c01fcc37f29e094d39e42c592224c3c1e5c"))
    (169795, uint256S("de04381ae7ef5bddfe6c33266d9f09fd0710918b74e6639bee5d40cb8d3b13f8"))
    (179783, uint256S("39ec563e8a0b4eabb35048bd2a03e38f4b5bb7b42f1252229b2cb0fa32736067"))
    (189771, uint256S("5bbd12ca6bc48074c026e067695a4a38bc0dbf28bbca7ddbaddc49797b0d4a8c"))
    (199759, uint256S("5578e4d4e6aa538032fc040d0b7050fb0c0bc0db5b4d51c384653e7da29a9b65"))
    (209747, uint256S("dc53cc877d3d657ff6804527541ffe43ffe980e1f91ff7213df2125859de35a1"))
    (219735, uint256S("ed7aa87fbc3f1231d8f842d057058ca6b5e088181ccf67702076070eb3020e64"))
    (229723, uint256S("fb56df243f6d32ab6ffd73b1fb368fc3312ea6ea3d05a46ecef7f060429466a0"))
    (239711, uint256S("d1e703c2847b39d63b56bd14609b49665ffaa1ec4c9b33a82a9ead1e05565d13"))
    (249699, uint256S("ac1ac77182e65e5192d28a867d263d574793282de2f66e0cdd6d0eb13f5bdf89"))
    (259687, uint256S("a7ae4c791ae608888f4d48e65d26ca815d9d5074a4910f83e0b49e094568de7a"))
    (269675, uint256S("9882462a847d6ca82ce9f1fa240cc18a3078bb73819ecf8301f096866d4b500b"))
    (279663, uint256S("4bc31f3a3eac334190dae84687acfd785a8534e29df717934dc9fb9396c9c13f"))
    (289651, uint256S("8767ab08229569d0ec04e98a9100c66e5aae7dd9fd4d6c59b66ca3d0281acca2"))
    (299639, uint256S("bed3f01b2114307b352e9dbe8c9577454d204367e61d7bf51314ad82f97b4f17"))
    (309627, uint256S("0b4e3b6178d9955b20bbc05c92759ca093544e4cb01bde4e3dda1e1f16edb342"))
    (319615, uint256S("0bc25b49b56d864a8c7e0cd63549c260b5e3f04aaed3e2ba8b16b5e799f0cd57"))
    (329603, uint256S("7fd77ded71caeea677b8f409de9d8e6fb0ea2ef88959b5a71800583f6a5e4bcf"))
    (339591, uint256S("6016d58675eccd705a64e8332ef76d53b649f5e0e17827375472d836fa55cd1f"))
    (349579, uint256S("001529bdf4dc8f9f1c471b344305ea6da5fd9c2a8aac25fec5b6447a3c7a8af2"))
    (359567, uint256S("e8fa5fac8eafccfe978e815c533296c241c5e64aff37152477eba73d43778430"))
    (369555, uint256S("8598674d860f880393f211bf9d16f89db90a1968040fc511057596183fbc079f"))
    (379543, uint256S("80c169a2fa1411da75e0bf591df2ebd5f91a0a8a508f14c7d5a9d4777d636066"))
    (389531, uint256S("e050be6a0135c1beafa2595954b0f25d90e9f9411745d060330ef082e6dc7f9f"))
    (399519, uint256S("ae1642e218b8e6e6139d41425b85ddcffb9d82954e091f3ad04e1d42533a14c6"))
    (409507, uint256S("ad4c13dabd4158f5b77299178e3aae7209013db027acb0d4a09b2257f4c219d1"))
    (419495, uint256S("854bfc268df9e263de41076cfcd21423c85c3ee2a88a20038b209c5e3e771226"))
    (429483, uint256S("9b18d71c5302df666d9f38a061bc0b7e05bcbe39305ddf791bc116b1b722f7e6"))
    (439471, uint256S("91ef09275ce5f86863558194e8adf4291bf50ad457fd2918a0afd7c3911824f1"))
    (449459, uint256S("7beb1f077ce6acf54c118f6dd4e4b7966abae7dd9658014c16c6d117626c474b"))
    (459447, uint256S("1d08fe5cb12e1add6e99d115f172d1911377f62c231a2baaf3a7444005604f4a"))
    (469435, uint256S("48d5c0d9201d85a9e4c3b01a063d6adbfce539a73c2c8e39b913ed8b4df00547"))
    (479423, uint256S("0bd11b075c89ef5697897d800836f1ea826185240b63dadd928276d4c2c8340b"))
    (489411, uint256S("e42aef65891c0d035b3cd867674e0cb910e4bd93af100b98f568b889d713fb6a"))
    (499399, uint256S("3f4428db3b6a53585c0bb91ac031469176a80481703f2b36fc8816164dcbd775"))
    (509387, uint256S("022df4c28d55ea78605f634b38067e862e99e6f7f89184c060f67971bf81b3ac"))
    (519375, uint256S("9eaa1f1aadec0a32f45cab604ec71029fb2692294ed2b8e7cdf875f952e7d768"))
    (529363, uint256S("6ec453963c1e21c33ce5d68dc1a2da9d315098482ae13e55dfdf5e5d2cba84d8"))
    (539351, uint256S("c304611890a6bdfc37d19ebbb5a9c30826d52eba2dbf6df52f1daf2ce54c9297"))
    (549339, uint256S("b34e3cedc0450f370e1efea7cad6fa02cc39bd2680b930ecfb8deb183b937384"))
    (559327, uint256S("ec658a49181d0f17f61be2244736554f6fcceed421271fafbf343833e1c35f92"))
    (569315, uint256S("c1d90692ae5500d71980cba21f1a26c46191ec16920807413b4ca5ca871b7e3d"))
    (579303, uint256S("18b59dcbba1cda2484a71cf469afeb5965b5c1cfaa780d7098e0f72a911a589a"))
    (589291, uint256S("9ad05e1b95080ce117452959a756217db568c5376c54fc7797624afba5031d9e"))
    (599279, uint256S("ad4ec6b62a76d19b6ff139abacb1bbeafd43e3a316205ccbde2fb598f513e516"))
    (609267, uint256S("dccbbaf81d5feae041d0d45c36aeadd27fd7ac8ef9621bd70117785e7e48fe9b"))
    (619255, uint256S("925033830264e5ea584f3b36f27fd125e8b0e35c8344e1afeb53cbcf8e472f20"))
    (629243, uint256S("d7a97511225ef195f564d8f437bd49d45f0b243d97664de47457b11c7904dc89"))
    (639231, uint256S("3510814aa16a26aac67aeaa76e21b72a9eab92a43d20af1e76f9ca601b5f0adf"))
    (649219, uint256S("fa8f7a913486074465da23d095a24debfe227d10c1ab3a66aeb66dce98fdb22d"))
    (659207, uint256S("267ef12ef9d6308e90859084265a6e3b43117a516abfd2524c9a48642949d140"))
    (669195, uint256S("88b6fcf42ce50d91982f799bbe437d7973f4ce21f9eaf57f694b880fa3599394"))
    (679183, uint256S("e6de877fa5673df29d85c779bdf1cfc121ba0b8fcc3d8be48257606938b9575a"))
    (689171, uint256S("67e74ad2b4d2fb90dc1ee9d88a99e5e3a564a911c86ca7c26a88227941cddd9e"))
    (699159, uint256S("07d5767b05285a2527f3aa95704399a80536101efcc8c2a172298615ea792160"))
    (709147, uint256S("741c253d9886d98ee754f5d824dc016a2015fbb7bd2810263bcc9d2751220254"))
    (719135, uint256S("3eaf0478218b256ee825c3a1799727bb22367666c0cef358778a7b6072c118d4"))
    (729123, uint256S("acfe16fb97e11fe26977655d32862bfb2d086e113e8175ae97f8fa3ed5c6e359"))
    (739111, uint256S("35e83b0081990417689750866badcf1ae1fe5be0f121ca4229c77febee3cf513"))
    (749099, uint256S("5e4cb8efa5ad0d046764a2beb6f8299436d572cde16ef2220557f255649cb65d"))
    (759087, uint256S("544ad349c02069bdf92abfc81ca296efef1c1e46a052d8e5df9ae6955095412b"))
    (769075, uint256S("c8ae6cdca037eeb3a7cca748f5961ff3b4a32aaa14afcf9eca50aaa34be30818"))
    (779063, uint256S("837a1b166e87bb7493bbdb9b4049d7e3cac9553de16ff79a03435d6b8c668890"))
    (789051, uint256S("6b3cc0e78611997d961b26ad671a0ca1f6d633c74160f4514259f3ca019c2063"))
    (799039, uint256S("a074c4dec571d5f04efed49caa76e8f96f125d2915f1aeaf1cf196d1d4634b87"))
    (809027, uint256S("f7ba78fe870105e05eb04c635576456173a09232d1ef5447d891d43033b92678"))
    (819015, uint256S("4d375e6b14254db310228a83d3c9c42ca228aa704c4fa17230c7f47bee444acf"))
    (829003, uint256S("fa0ba1779ece17cd7dab1fe7c87b6c4ad50beddd0defe6e5854f5f06a0f50140"))
    (838991, uint256S("52731aa3648a043ed95298119190345bd57b6f5fb4cfcf2c2dabe7e274755fe6"))
    (848979, uint256S("3567ea85c1c52076f970d05642c1e5064bccf8987c09f78d421ccd7d15783191"))
    (858967, uint256S("5391cdd7757c3eda34f6a2853c37f82ad4e966a6c86df31d4997a71912775f18"))
    (868955, uint256S("5258e4a123a22882870e7bd2532e8f1f5aa83745ea355d107df85bc4ac88d188"))
    (878943, uint256S("9bc5d970b25ba4f92f07628120327d93a876fbb0b2778362d809c14c40914d7a"))
    (888931, uint256S("9d4f5b741a91310a3f5595127d7952f37da2ef78c66d1743bc91e9f36a573751"))
    (898919, uint256S("90e1ec362f34947324e639d68116174d224f9fec19799729eb7e86bbdd8477ee"))
    (908907, uint256S("9a521949ed68ed2bcdef28173621ebe6b4f4d63a4968d6400f3d2148cc8e0e17"))
    (918895, uint256S("1336e0b5beacf97b188566949b138139c9d928d5c66d575c85e69cb6ca3fa1ba"))
    (928883, uint256S("5f6d2a00529736e3abdacb79f5e5e3cee5a5d1824a658269d566b3f388647a96"))
    (938871, uint256S("a3258d723103d74a4d3a68fdd02c9ee64e0ab709fdd2e8f3689c43f66d31cbd6"))
    (948859, uint256S("0811292d900ef5f9003265142d518c5f4f4e48dadcb6d5d558471495c2d4f94e"))
    (958847, uint256S("a4ba95d7d35dcfee8db9ae58eb4ebedbdcef0a2e26395d5bcc41443db20824b7"))
    (968835, uint256S("94b5077e47bd23352128b78bb2aec2597ee58bdd235b7c08e2844d641e09bc68"))
    (978823, uint256S("bc1a8b1ac89ef826d07a3aefafd3178076551ef47627068cb16f308300b7f3b1"))
    (988811, uint256S("88c820e3f9bdd7324edaddd2d775ce525ca830f1ef4dc9ccda3480568f608932"))
    (998799, uint256S("19094aeeedd423b69b1df353fbda1f4151b919466cb12ad6552649bad5710781"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1683467670, // * UNIX timestamp of last checkpoint block
    2169120,          // * total number of transactions between genesis and last checkpoint
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

        genesis = CreateGenesisBlock(1622058209, 1716299, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000e5abe79d86f5e7a8adc8a8d0a8afa3d9aad1ae5099eec426df74bf2159e"));
        assert(genesis.hashMerkleRoot == uint256S("0xb81fed5916d638ae849e84e71bb0a920fa6858a0b83cbd596e6ef13c458c84b1"));

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
        consensus.strSporkPubKey = "02cce4f25d4304cd543177aa586cdd618a934022f26c986eca9c7037f4bdda0324";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
           { "sXXXXXXXXXXXXXXXXXXXXXXXXXXXVpr7nX", 0 }
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
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight     = 80000;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                    = uint256S("59ea521b46edf374093a44c5e8bf88fe3db211aa9fe63dad1c065692047f6db8");
	    consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                 = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                  = uint256S("6a864227d00fcef37da49251d2bccc39b05f6e2e55dc6b9bb4198ac488dc17a9");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock      = uint256S("6ca0d4ee6fd87d7deb8a3f31eb57dc52588aad8c75766f6449135182f1b472b0");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock       = uint256S("0f2a78cae02903adaee9b7e43a91b86725980e9ef3bb49303a722a48bf9a32f6");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock = uint256S("a70f1ced0cda9854854bda729aa9c93e5867fd583158f033fb16b50daa258a71");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock     = uint256S("3142c02979abdf5e8e8f6d0f5d68e04caee93fe720d401a806e5e074e50ed5c6");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock     = uint256S("be026155f0d3fce0b28ba5e0153555b34fe850beb0244803e27c64dd895a8938");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf6;
        pchMessageStart[1] = 0xfc;
        pchMessageStart[2] = 0xec;
        pchMessageStart[3] = 0x78;
        nDefaultPort = PORT_MAINNET;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptosaga.net"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptosaga.net"));
	    vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptosaga.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 125);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 44);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 142);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x4B).convert_to_container<std::vector<unsigned char> >();

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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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
        nDefaultPort = PORT_TESTNET;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptosaga.net", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptosaga addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptosaga script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptosaga BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptosaga BIP44 coin type is '1' (All coin's testnet default)
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
        consensus.powLimit   = ~UINT256_ZERO >> 20;   // cryptosaga starting difficulty is 1 / 2^12
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
        nDefaultPort = PORT_REGTEST;

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

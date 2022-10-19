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
    (6251, uint256S("37ace444daae012fed0953864c37188702e3a924743ab80c921b108399a6ee8b"))
    (12503, uint256S("12e1acac5c5e98dbb9a1ecf4cf9ac913c3ea29a7c348831778a070977950c8ba"))
    (18755, uint256S("d2d92497b4fa434e7685328e4c685e7bf6faf53bb371d2aa896a5bc8b2ce5631"))
    (25007, uint256S("e2cfca960afe5323e76afad3c7cbb8cb08c0a2d611f20d5957434ea12daa12cd"))
    (31259, uint256S("ea79a8aca671da3c48becb49dc2936907a807bb368ee816920a539912bfb78bd"))
    (37511, uint256S("2d821f83973a8c943e3385820f443437a4ea294c4c2d7bb51351261c0c7fe779"))
    (43763, uint256S("b72025ddbda671a8a1313e436869d9117d13f24c3daf3122ae25f56a4eac1c9c"))
    (50015, uint256S("ef0b2051f3ce300959b32309dc4056754efe833f57a2d813a0f46f70bc579850"))
    (56267, uint256S("e38e014c37b36944399a1777d4bc890500881f20549838958deb5b34a408c67f"))
    (62519, uint256S("53874791fe6d58407833de5b414fa1f75cd99ad0f1d88353fdcde9e707440983"))
    (68771, uint256S("7b634e343910fed07696cc701b2595ec8a314294bca9aac38e701c939fffd91d"))
    (75023, uint256S("adb7e529be2222a0b5aeee7c1a9ddd2bf6a1aacb5770526581b94a00a5c16cc3"))
    (81275, uint256S("738dc8385dcd0f9e9f81ace9234a5626890ff57420ebc1f64958a8a3d09d446b"))
    (87527, uint256S("adef7a942c1bc4445a096a2db15d6727198e51e1f3744a29b74ca7273f44ae43"))
    (93779, uint256S("3c6f20afb6e8f27b3557dabfcf3acb8794dcc00191c76f8d4401cf26ecacf336"))
    (100031, uint256S("54997c4df52804abef5a3bca5b6da0c42c2996c774fe5a361d93f8e43899a59a"))
    (106283, uint256S("0d82528da12284f78b4d0839f340e8d1f2970b9f8270d10dc3bb6c4673fd79e9"))
    (112535, uint256S("3f0409a84ec92d45352e29e0826303dd8e3902a5bf25d5ba39186ab475ca35a1"))
    (118787, uint256S("548055a952eeefafd7ef2f8b644e65dc682a227b0f031bdbb97744ad33eba811"))
    (125039, uint256S("8ca04fcfa40113304d371c5a7b933a66add3b25d1f0f604aa1831b207d9c469e"))
    (131291, uint256S("0cc1f03dc3c463ab9973d680680dced57577d89a4b7bffd676586eeef37302b5"))
    (137543, uint256S("7a7f96ad3932464411a9246670bc94710ddab0f2c2c4707a433187cb3359be75"))
    (143795, uint256S("ecbd9a573dac5770731574d6527b774608027ddb63c812cb8246778232e54e91"))
    (150047, uint256S("a818268703f1d89efc2319681f158a1c23e3884aa655f1740457470e52080545"))
    (156299, uint256S("3e6ed8c67a22051851455a84ab34b9d2bfcf8352061891ff2cf6734ee1d91308"))
    (162551, uint256S("9c6be22f03aa1f05ddcd421cf52987dc3b974ada73cf49cb6cece7a467e009d0"))
    (168803, uint256S("0afd1ed724899b9bacf26e655d50057392f74968fe848240db4d71924b326a93"))
    (175055, uint256S("407cce092bd2eb3e17db317dad092a48a27f3e94b491cbbecc76e47416b2fa6f"))
    (181307, uint256S("8fb83e9c28181cae19b129d8b9263d219bbc597a16bc9a80724c7414161910e9"))
    (187559, uint256S("13e8467d7c5f9ae8024ed0c7d45c4b6d19ae32cd983c772ebe81262cfd5e3067"))
    (193811, uint256S("2b2e8cb9611ad8535828949db409fbd36aad783ed1b409147c12e567f909cf97"))
    (200063, uint256S("0358485c56ac83dfae91541b93e4e0eeba43786a1f7f4fae33642566c9da5909"))
    (206315, uint256S("f1f38924e014555f6df8d1d3cd633c3e4efb9893de2534a871b3597f7dc103e6"))
    (212567, uint256S("41cd1dc276c9778a33ad367365f4f813fdaedf09d52a2a13e67652dff3d69d07"))
    (218819, uint256S("c0480a8def0e8d9dc21a5bb43d2b2e7eae03a22b85b7f18ea5248971632ceffd"))
    (225071, uint256S("729d4039a3dd939140fd262b7acc32478c5a6751d8e48f30bfad5d2e257d17dc"))
    (231323, uint256S("b7c994c48fee632acd3fbbe522d8cafc6fd619e9534c72f90ede6bc364b8021b"))
    (237575, uint256S("945bac25872884a9603daba8f2d9f57340b0d8fb2fbe88d6d363a3954d381be3"))
    (243827, uint256S("939aa7eaa8af4f3b59d66d35b9cf6c8448158ff87c2fea4d14f689ca7384e568"))
    (250079, uint256S("e4e00b2de9a7a799fec355bfc6401f2c686536ca35e0db6807f70c56209b5801"))
    (256331, uint256S("43ce281a8c43625278da725696a6c182dc3a257bd88f06d1cce26b8b318388fc"))
    (262583, uint256S("1fb04f5372b548fe20c262af576658bd94f701f9fa02c8f4baa8dd0eadb6311e"))
    (268835, uint256S("5abaacbf6a4836c7c51e6582559a172d9db47823607b5162cea4b3a3bd2342fb"))
    (275087, uint256S("884b14b796759d5aee45d7d5bc9d42d629e968ba6d621eacdb3052011a869869"))
    (281339, uint256S("90f7bfff6cb8d593bab0300b495d8fad1902ba27ef272deef47060b8c192255a"))
    (287591, uint256S("e32368cd5ca80ae486a49f383049842f8235ba6b59ac4efa2b57d489085aa7a8"))
    (293843, uint256S("dd2019a18aa2c9b4c55d2ea572115f562149da78502d4f5794a54fe9a35edc48"))
    (300095, uint256S("d6284b7aaaec69186be6ddc4fd712d1d1c9aecfcf1924f10b1be90e83dbb50d3"))
    (306347, uint256S("bef1a8073e4443a5d978f895f34d9b92b80327f5b689b34f6c04acc713234b40"))
    (312599, uint256S("ecc94bc831d51257c5a2398a6e1fd3b262e85008fce845b78d9d3ede10365523"))
    (318851, uint256S("dda966b69700c2ee4a2633b30f6a73c5ee09771f521a7e0af7fcacce38134bae"))
    (325103, uint256S("e213543dbdfa793d793ee0bcf12c57cd5a5e096581828f6004c96904f9fcf73e"))
    (331355, uint256S("5480a256054cae238eb66f3b2a6b1d6b8bcd9a5057cfcc5f1cda9b52c32f8bb6"))
    (337607, uint256S("7871316d0d1cbea4adcda49560e7fd94e574f885ef30a488008ca539e8cef9dc"))
    (343859, uint256S("71e3e8b0d7d85e39b5f100a27af4a3ac2eb88e3863c4d55ea3ef61c1dbcfc97f"))
    (350111, uint256S("36581cb4665a4dea0c525f441e407a558666c04aa8fb2a210863be3414ec076d"))
    (356363, uint256S("e09f08096467d2dea00450eb0d39258e9bc6353c7ccea90a27ecd0caf135b278"))
    (362615, uint256S("66d1b40d6734ec4018c68f540e6265f8a0348d57f9e4071aa6abb99261f834ff"))
    (368867, uint256S("19a7043089c54dbabc28cfa20983c16effeeefe7bd26868c39145e5612da31db"))
    (375119, uint256S("3205800e0a155bb54bea4c48bd6371ca50f7e1296a9313d5ed7e35ce6b2388af"))
    (381371, uint256S("65b64aacc968203cd9e675f87bc124317970192e31f8f52a439e690162c63bf5"))
    (387623, uint256S("f1fc980d193a644af8a4d06b7470c7e556d3bb8fc1f662f8193bbb92b6ad1650"))
    (393875, uint256S("51f97844d1ac56578777fcbcf8e73ca2f4ecd9c29166a0494702223caa7dd6a3"))
    (400127, uint256S("16ef8aa17a4e71aefee79b08ea48812e91d3b22d0129414dbb1e09f8f03edb74"))
    (406379, uint256S("8704ca4b0893b6690c0518b0fb890902345bbaaa4213412da7f621ca0886ee72"))
    (412631, uint256S("eaf7611cd2489cf2e5c4f82cc702bd6a38798c95294dae9f028aca7abaf043e0"))
    (418883, uint256S("b43264514d2d5e850d43f5bdd27806d8443f0fa00ff4091fddadfe4cdd6581d6"))
    (425135, uint256S("1d705c7b0909e324407d35df391ab1de31e55d87afcd0bff11a51f418bfe6138"))
    (431387, uint256S("179d1f9922882a8a26547b0db904b5f3e44d7cc24f11df17dc6ab96d4f4b1ffc"))
    (437639, uint256S("e0e0b5c80025f6122ee58ecbaeca179bdb87eaca844b931ebb39ff9cb5c052a0"))
    (443891, uint256S("0f4996e47f690b8e9c5f1336a46977dae865e332c02df4324e8a6803432be446"))
    (450143, uint256S("df57ecf45296c0f31abd1bbd0d9493b14f1f98cb8aae37e774c6f4b8b55f38bd"))
    (456395, uint256S("691742de72b6abe43caa0489679bce418825f540120ddf609f0c3475c1a8d6ff"))
    (462647, uint256S("7e72a91829486399e6df397d1fc567b9b345c0fb711ade04c424c11a15207ae7"))
    (468899, uint256S("74880cc5226e725ff0a900ed1236910c1ea6ac3c70d2f5a122a74e27b73ecc20"))
    (475151, uint256S("49978ff464c691c3129135c6ab2fc11c49102fcc37ed5d74e8afc06ec0edf49f"))
    (481403, uint256S("63a5dd58e33f32f120958fcc31668a10b5cf54bce90343d2d1ce2cfb8485c16b"))
    (487655, uint256S("34e4c6eb09861ed7ac8871c45e86a8b63480aebfaf244ef4faa356866584cf50"))
    (493907, uint256S("d7976a6d294667460210d044d8fff67fcd01e52dc5ebd865f9f15457ff180cf4"))
    (500159, uint256S("02c8a6f7ccedcfce9a7380d28dbb4f886bc991bfb94b0f209d4920581bbff622"))
    (506411, uint256S("f6d9e1ecb64894ee8646083c80800f6b17e46feb7f5851f7dc495542b81363c1"))
    (512663, uint256S("3b45bc53c68f5107d549f1f643118f621b35eb28172662b59a6efab265699a38"))
    (518915, uint256S("546463b741c8684165b3b1fee5d312a2a4215e0d290a90e374d9cdb10013301f"))
    (525167, uint256S("166eee483f6732b143c792a90e0d0fd84675d7e8d14f7bd03c75835ed25f724d"))
    (531419, uint256S("c8be1380f98d5a8552045f138f03cdfc8db0b08a2e7edc7eeeb211974eab2054"))
    (537671, uint256S("ab8be8ce98c401cf54647764dc86d008e7fbdc56c3d785e1728c09f532caa6b0"))
    (543923, uint256S("7ea481562039d4e143afde34d7ddaf8cfbb2ffe57f0c622986b17165509f48dd"))
    (550175, uint256S("edd853b6432b220e298fa19b12081a002f62326aa0a991bd7bb579786b18b45b"))
    (556427, uint256S("d7a1235d99069875d7cdf7e38977433e3c13988ba4c1d687685d0fa635fed9ee"))
    (562679, uint256S("e9e98de5310f2cf82c8c3554e6150cceb71165e2286c48c65ce2e8d4c0bcb538"))
    (568931, uint256S("96c4ac1a1d41955cfb8ff46ae4b69cbcc1d738410e08e9b0c7e8a6f2d2ade8c1"))
    (575183, uint256S("bff56a0a68d87e2b0eb096e9c5a63919e43dd4d61ef93f4fa9320b0f46f921f7"))
    (581435, uint256S("9ded2a9abb7cbe36ffde7b1cb7ee5176f3f6e7d8e2c88755636cebcfd9eee2ed"))
    (587687, uint256S("9ee8540278983a6149661fec5ea612dc54e53ce694b8e75e0e81d7f0ea83fed3"))
    (593939, uint256S("12f5f58063d18becd92c531e066a3f8ab930b326c29671ae3ffd74cbffa02d86"))
    (600191, uint256S("601cb8ed5673e9c40119b3cb24f42953c987b449156c7b870f775094a0c486ca"))
    (606443, uint256S("c9ca44e8d10b6a608597af4b5acc2e4b573f179bf724c52594001e5a97e0d4ac"))
    (612695, uint256S("ce050536a70e48d2705217c94dffb88df5c056bda2f7a2e43f5ce61455e9e1ab"))
    (618947, uint256S("d1688bf2e27b25dc84a9e588182c15bd564a38685fe6ed90460be17d044f9615"))
    (625199, uint256S("17e062cb0ff30a233a2b539a04ff57e1fc75ab1a4b5ddd4f4d8766276e9fa915"))
; 

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1666169445, // * UNIX timestamp of last checkpoint block
    1361307,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2840        // * estimated number of transactions per day after checkpoint. 2000 for 10 minutes of bitcoin blockchain (1M block size). With 2M of block size and 1 minute of block time, this field should be around 4000 * 10 * 6 * 24 = 5760000
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

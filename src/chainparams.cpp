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
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
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
    const char* pszTimestamp = "Bitcoin is now worth more than Visa and Mastercard combined, COINTELEGRAPH, 16/03/2021";
    const CScript genesisOutputScript = CScript() << ParseHex("0459d0cd928dbe01d8ce77979ef8c87c1f6ed3ccefc64502ac599a38fde1e7424e8a9a7fe8660055332e693d84ee9702d3ff583e2445e201bff209b7b67b405447") << OP_CHECKSIG;
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
    (0, uint256S("000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"))
    (11370, uint256S("ba45d4c4c448cb8799dcef4e7af580d3d0d3003d132ca0b60cc0695c72b6aa0c"))
    (22741, uint256S("e62f4e129a1ba0daf1e0f5e93898fec82018e755b5c754e7e2351ddbef57ed45"))
    (34112, uint256S("a1a8398bc65b064a996ea4988474c0d98062a52d75927186ffc96ca84d7beeb7"))
    (45483, uint256S("6d12b5a6a557546c7441fdedf09e375fd45e4ca774cc5845e09f1ad980c94fb1"))
    (56854, uint256S("e135a9d372b95ddb235b5626d2b7feef6da5033003162efa56a87942bd2d8b21"))
    (68225, uint256S("fc2bac0bd8fe3aa6060f0e6a09f56c32ebd37ff0ae76e2470a89ee016fc4157a"))
    (79596, uint256S("a9d84f3b0cf244cd0643784b6c58dcf50e508963f907af0a867eaec4064a1eb7"))
    (90967, uint256S("855402b975e4e19be614150c97a1fc300e3a87d6652045a5e58b7bcd89a75d5c"))
    (102338, uint256S("b0cac6d96d67b7c2a88145f97cd8d2ed113970e6b94097175485b7e7d4c49adb"))
    (113709, uint256S("62fbf0bbfd1f24dd11205e4bb2862ef35261fc3161ef5cd6404a05a27e339213"))
    (125080, uint256S("fc2b2b87700ae49e9ba80d1442b9dabc562ee7c59be3bd6b3310f1fa579a972f"))
    (136451, uint256S("03eb71efbeec52b05c6d34942bbc8882a0fc81f881fca5468b910ac5528aac22"))
    (147822, uint256S("605efcd1df4e0e14dddf745f7f7b48da7f44d4b3dbe3bbcc855e1c9282cd1243"))
    (159193, uint256S("f7637421516d33f01587e2b6a9f202506f3f70c0ff72829b69ba44f1321b7032"))
    (170564, uint256S("ca45b2a7da47d7bce697c7d5d6f40152bd57388d55ace1695eeddff5307a379b"))
    (181935, uint256S("fc1b6f75670259a1484201dcef98d3e4f87eb501c355dc83e6c2650f387ea818"))
    (193306, uint256S("21731da743b312b534f181518e0f3e5e31166e377417858f08e2c3d1605f29ad"))
    (204677, uint256S("83d6258240fe4bc5b817ffde64565d6efd16ea057983d1df087433bffa77af8a"))
    (216048, uint256S("efecc2373edc53a3a505b8845c48f14d888f262ca53a226a70ae81e2210c0686"))
    (227419, uint256S("901855b8cd2630efcaba7897f1eb7db7e54ed5a8340c591ce028ffef39eb9e85"))
    (238790, uint256S("a2480b8bab16ba8afa9b287048515633e7cb515437bd9d48d9aa852215dd9515"))
    (250161, uint256S("317139ee20783d6f396e050e2916f1fc111a69b98464cf32e5b138b298c26264"))
    (261532, uint256S("e3591c1d6d00c9118526a533c4254f40037f5ddf7c19263809f85e9636845b4e"))
    (272903, uint256S("d48d0aee04da3e98a8277602cfa525825c55ffa293cd3443b47aaed1def83237"))
    (284274, uint256S("c65a2088f908564acf66c21890dba5785e0a6d127ebb9589be5637ad601bdf30"))
    (295645, uint256S("ac880385133e2ce6ca5f98c890d7be7cd4dfb19d8812a6b267cbd694bb8f231c"))
    (307016, uint256S("f6539108ab7e8e6ca3ad258214e182b1f68df7dece5e1c316fcff7a7bb3b8a2b"))
    (318387, uint256S("ba4a2bab3c2512a3acecd9fb0f0bedc07f31219f28c7ad572639be0630ca9358"))
    (329758, uint256S("191cc5f8d32cc838cec54ec8f567b00c6a082a5fef4a0f790cfbeed10801e1e4"))
    (341129, uint256S("eddc47897ab2345b61756684316600fe646986993c59c7dbe2eb04419deb40b1"))
    (352500, uint256S("c347c4d008f6b75c06bad324ea9f08eecafd14830d8a030cee07fa17982a104f"))
    (363871, uint256S("244c165ea1af24ecfcd9ac1063d4589fd5cea6d1ef894b4558fc952934cccaa2"))
    (375242, uint256S("5449a55741e93e27d882e5549398f3773c76ae86fc69838208a7a42ebcc1bbbd"))
    (386613, uint256S("7bbb98f5edfe241afeecf9870ef26d5e78c787bca3a5e3d3efcc8b6317cd6084"))
    (397984, uint256S("64c0530c96dc99c68e33257ae6595fe2c527fddc3d5ef6aa4ac800ba6cb3c87c"))
    (409355, uint256S("e64025f06fd89db7467d6ec21d301802857cdb6295254b27a3509d973368a792"))
    (420726, uint256S("6a59181da2bfc5ac62990edf24c83565e32c5d0ca7fd733e8a3c89e9a1a38ac6"))
    (432097, uint256S("3ad3efc112c8c7ab25c757ad7f36e5b7459618eaea364a177ee2fd0461ddafba"))
    (443468, uint256S("0ab10978af83af19dd3f44aab5835fa84d287c6fbd293d24a09600c69120f424"))
    (454839, uint256S("2668084d672621fe85bf6bb074683b9ea2cdb9b61299dfc2adadd426abb22c1f"))
    (466210, uint256S("00a017656f2ca7d48632c751b975a8e95817398cf459a99073196ed6460f7e3d"))
    (477581, uint256S("926e1b46963a551185ed5175fd0518d415339a4a1ad142547ef617f7ea8bb425"))
    (488952, uint256S("78c87c436b649bfeee47eb4580a276ef35e8118b691dba5ec66b095a50c075ca"))
    (500323, uint256S("737feee7ac867e36343f719e293f9c2a97ffdeab2115a95de9ddcc530a80482d"))
    (511694, uint256S("cdb2aedd3ae0a36d8be5b4e7d7379fe6fa31b409aca87608b58c7e239a33bc8d"))
    (523065, uint256S("0f5d8edc0147e469131c520530e93f6e84cf329af7eea92406537366f469338a"))
    (534436, uint256S("8e5dbb5964938c30fb25e901c1c4485505938f5333e51596c78dc058f36fe7e9"))
    (545807, uint256S("6d743cac3401ae8bfb1c9d3022a6f7ac898e4078267e87359e18f183f6cf9425"))
    (557178, uint256S("2d92098abbbf0f0edde16d688b70943f4fd0d571a2378feed756ade44b791cee"))
    (568549, uint256S("5822d9dfe50937caf9173c9aa6edab9cc4b541692842eb26e86dc81b9b1b2986"))
    (579920, uint256S("d7a54d1e35f397c22ff706bed3c5011793f60d0ddb58223c19f47480f97038b6"))
    (591291, uint256S("9e7de40ecf6e0160946f3ee6305d6e114e6ee3ab726aef20d8543ab17e587c8d"))
    (602662, uint256S("c8b3a24f482a2f39c1c398c71484bc4cb8396532071e252c09bb315100108444"))
    (614033, uint256S("6302fe6b12c6d46c77437ce1c6b7f5c5cfa7ff015d4d0180082cd0580a8551c9"))
    (625404, uint256S("a4dd67a6b9c80333dfbc729f24c1e965214b43e81f2bd976108ec3d260d21f2e"))
    (636775, uint256S("dfc4cdbe97d1276f634c805b0a34d8b46434db28fe28052f6995b2c8cfbb0c0a"))
    (648146, uint256S("0f447e0672830141da1d0f0b8f2bac953ad89ef8de722671f5a3467ddf39cef3"))
    (659517, uint256S("04d2378c146cfe0e2a0c05c6b0d8421cefd603388772bed8a1b86d40688f34ca"))
    (670888, uint256S("efb60a2453892b33b893a5c408e2af627c0bb6dddb8dcd4b37e26caf6c3b3b65"))
    (682259, uint256S("29766f26fc5b0b9c7fc8d2a67590f855a2e80c47fa6a728f8a27d26ddca64dbb"))
    (693630, uint256S("dfa92a2f660650c7e2fe580a8cb07e57e7aa7a2c8e7b098c90757bc9174a5318"))
    (705001, uint256S("045e776a097a85fcb85bdcf5f07d604eb6be5971f5831cc11419251c20da3705"))
    (716372, uint256S("87843a329577bacf2ee9ff129989bcd7f0ae80fa452bfedc2afd2a426ea25f76"))
    (727743, uint256S("575a4211cb6cb542c8adb73276abc7e4ec3321bb7b80a77a83d6a00532918db8"))
    (739114, uint256S("9f9bb1326d14250d56b29fed6772f26b75e060c7855658d2fe606597da9f8c17"))
    (750485, uint256S("d210289b82a866a61f9f20b316d0205ac9df6db976a0b4cc95c9e7009e5c480d"))
    (761856, uint256S("8b16f4805b4b427dc8e6d06318c9b2fcae172a832608814288a617dd7a18e279"))
    (773227, uint256S("ef313c6ec3c2881921eeba1a5df1ceb3f51c0a2996a70ccdf1f066b7b6461d24"))
    (784598, uint256S("455f8178e6d36a9b981701e874d8a9a2e0357a7e05131ac86dd3e8e8b218e8a1"))
    (795969, uint256S("bcfbb4c032ddc5b35e59087b52632412af0f2c17468c34af5d3ceab319529764"))
    (807340, uint256S("069d69cc81e46f374f0619d9df5ec2789d474a0437599b38c79eb18802583638"))
    (818711, uint256S("9d7825b19c9ab05bd7b53a834bad3ee2d84ba7643f4d0d53f30214126a3fbe32"))
    (830082, uint256S("1ef0ceeb37248c3b9253a575748408ac1ee619b97da6fec66163c3446e41c296"))
    (841453, uint256S("fdbc6feb8eebad180649640d81a16fc0d09e672ccf3e38f45f80fce91229aa7b"))
    (852824, uint256S("d136bba2192f3ed5fe6ea250cc5dc653f6a97f77ae586b8a2d29e0bb6128dc90"))
    (864195, uint256S("24374bbc5986dfaa37829f1addb78913e878df646e9c40ad4240d712f8337f63"))
    (875566, uint256S("762abc73694900ce6f2a2469facd8b9099c379fcab114fcd2d5a9603d22210cd"))
    (886937, uint256S("b9b47965c47ff1ac18c8d5a5604b4ddfc6326ecc1f74c2aafe0b9b97322db039"))
    (898308, uint256S("94636978eb142215b2ca94473130ff7b07e5083eea23784466534aaa6b375075"))
    (909679, uint256S("cc92c49826b11503fa694ee8a39737c07d5d4905c9ebdad71a49ceca66d35313"))
    (921050, uint256S("6ea05cf96e800e33744e11387e0ca6c84c67bf66fcb0eb899b9f9629c7c6aa12"))
    (932421, uint256S("77137917ddf770ff9aaca7c49f8a01c78f0bf0f2f24c28387f40dd7d08397302"))
    (943792, uint256S("5fef3d820ae306a9aeb66fa40c07898c4d7718b72d254eb25ebc7ff341edbb9f"))
    (955163, uint256S("d17a03a674a23e10a74170ef78f3a1c37d43440a1a6a1e89ab8074fb2276bfbe"))
    (966534, uint256S("aa0b4d2424b475f441a011c9a9b2f2a061bee572719cb6259e2b61a0d9341706"))
    (977905, uint256S("9f19b756b3e0ffa204241cf2552bdc0568370f975a3b44794bfad61f8625adb2"))
    (989276, uint256S("bee213bfd4e554aa42b4b068ff662905f4b0220c7357f3178b9f759cf4dce56c"))
    (1000647, uint256S("c01814962af2934f17ff1848bd5a51d693a903abb4228d15a3837087f952dad3"))
    (1012018, uint256S("fab57717727983ba8950e25f43f7ef4f70f21ad6a6bbf2c95e6f32c37b83910f"))
    (1023389, uint256S("0fbe1e3d5018bfb14a092e905ea49890ea3b13bd21081f5c86da7111c14dc63c"))
    (1034760, uint256S("33644f2470c3936a995c86649b61a1fc81e8443e2856e7f1769ec9b8b6036a4c"))
    (1046131, uint256S("f999c63326c989c07301a0a093fb2d5f0da7e1327ad682c5b74a20b65d63658c"))
    (1057502, uint256S("93d61c95fca66353ea84be5231d3bf29f6269d1d6b8e2dfa2be517abd0361e0b"))
    (1068873, uint256S("b8d9277f4bcc8169a2503175ebe09a1bd2ad7b24178cf8a6c3f09b705b25fb0c"))
    (1080244, uint256S("62c51b175b74bcc643dfcb97ba121bb62e2c915349fd5678953e49e72d651d33"))
    (1091615, uint256S("8972e332e31d1f064ad8159181222276969498db8ef3bb5e9a1f01b3c6131ff9"))
    (1102986, uint256S("4438b17ef0ab08f471a1f026aa15e2927805a7bfe8b3761df9f0f7a762363987"))
    (1114357, uint256S("6217d507fe9c912df2ec0368c843aa305aa2725bae30a7362b3e010e33f6c7fc"))
    (1125728, uint256S("4f7499c66c3a0c6fdd3403e89e75822b4cc2647a11e26a1436335bc41c50ca35"))
    (1137099, uint256S("f6a4f48ffaf92a7b9ddbae6513708c9ed65a032424f68fc8c02a86b2f32f2387"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1685807310, // * UNIX timestamp of last checkpoint block
    2432667,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2842        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1533446237,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x00"));

static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1533446237,
    0,
    100};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";

        genesis = CreateGenesisBlock(1615902863, 1765803, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x000004024ce90ca90b3d840e8561944882d31a35ee9700fdc4a4187f0e25bcb3"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.powLimit = ~UINT256_ZERO >> 20;
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // burn addresses
        consensus.mBurnAddresses = {
            { "cBURNXXXXXXXXXXXXXXXXXXXXXXXT5p8pX", 0 },
            { "cBurnAddressXXXXXXXXXXXXXXXXVrq7yw", 0 },
        };

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight                      = Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight                 = Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight                       = 1001;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight                    = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight                     = 1441;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].nActivationHeight         = 1541;
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].nActivationHeight          = 1641;
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].nActivationHeight    = 1741;
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].nActivationHeight        = 190001;
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].nActivationHeight        = 190001;

        consensus.vUpgrades[Consensus::UPGRADE_POS].hashActivationBlock                     = uint256S("d2b726f6c67aa8f9444c918a9ee1a7a3f3e71b6d214d930ee1b486e1ccfc49f5");
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].hashActivationBlock                  = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].hashActivationBlock                   = uint256S("6d9da23cdd83b8fe240606aed46399af124fe6f92a757d4fb88221dbc2d1a793");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MODIFIER_V2].hashActivationBlock       = uint256S("13eee22f4b637ad17bfa5836fb086d4a3985242e68f32d483138bfe9240c8a3e");
        consensus.vUpgrades[Consensus::UPGRADE_TIME_PROTOCOL_V2].hashActivationBlock        = uint256S("5c592d9ced3bf780c0d9fac0a46a479e4b9b0bcf834d8f6faf93475aa286cf94");
        consensus.vUpgrades[Consensus::UPGRADE_P2PKH_BLOCK_SIGNATURES].hashActivationBlock  = uint256S("6ee546e646f1277c4d38944a83212b051531f745c4bfa54bac7633c38c47fe9f");
        consensus.vUpgrades[Consensus::UPGRADE_STAKE_MIN_DEPTH_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");
        consensus.vUpgrades[Consensus::UPGRADE_MASTERNODE_RANK_V2].hashActivationBlock      = uint256S("63cb12ae1181ff99d4f13f494413a2001839ca05c544b2bc20250dfcac049768");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xde;
        pchMessageStart[1] = 0xe9;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xef;
        nDefaultPort = 13333;

        vSeeds.push_back(CDNSSeedData("seeder", "seeder.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed1", "seed1.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed4", "seed4.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed5", "seed5.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed6", "seed6.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed7", "seed7.cryptoflow.eu"));
        vSeeds.push_back(CDNSSeedData("seed8", "seed8.cryptoflow.eu"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 87);  // c
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);  // f
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 102);     // i
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x03)(0x44).convert_to_container<std::vector<unsigned char> >();

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

        // uint32_t nGenesisTime = 1615902864;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1e0ffff0, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
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

        genesis = CreateGenesisBlock(1615902864, 42773, 0x1e0ffff0, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000c5ee0ad5d40f6b26125819d873afabc0c0d47034c97d7b1dd74511215bb"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 12; // cryptoflow starting difficulty
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
        consensus.strSporkPubKey = "02f41826b4cb2b38cc896526dbf386c36e31c96a4a7f99bb0eec6de4cb7949ebf1";
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

        pchMessageStart[0] = 0x06;
        pchMessageStart[1] = 0x16;
        pchMessageStart[2] = 0xe6;
        pchMessageStart[3] = 0x15;
        nDefaultPort = 14333;

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("tseeder", "tseeder.cryptoflow.eu", true));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet cryptoflow addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet cryptoflow script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet cryptoflow BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet cryptoflow BIP44 coin type is '1' (All coin's testnet default)
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
        // // /////////////////////////////////////////////////////////////////

        // uint32_t nGenesisTime = 1615902865;

        // arith_uint256 test;
        // bool fNegative;
        // bool fOverflow;
        // test.SetCompact(0x1fffffff, &fNegative, &fOverflow);
        // std::cout << "Test threshold: " << test.GetHex() << "\n\n";

        // int genesisNonce = 0;
        // uint256 TempHashHolding = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");
        // uint256 BestBlockHash = uint256S("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        // for (int i = 0; i < 40000000; i++) {
        //     genesis = CreateGenesisBlock(nGenesisTime, i, 0x1fffffff, 1, 0 * COIN);
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

        // // /////////////////////////////////////////////////////////////////

        genesis = CreateGenesisBlock(1615902865, 506, 0x1fffffff, 1, 0 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000817f2ab1c84d7ae24a42b8cfe71f401f6c05bce5499b9550128e73606a238"));
        assert(genesis.hashMerkleRoot == uint256S("0x4a133058bc8507376b74f38805812a3d3288485689b73c61abadf7766d78b4e2"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.powLimit = ~UINT256_ZERO >> 2; // starting difficulty
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
        consensus.strSporkPubKey = "04ae5f52611fc9f3dcd3f2db88ad4a9b10ab218389cacd1ed07cc893af6ad2f3e6618090edb54038e5a26d2c6d04db4a6c901a8bf52a72fef484f478519fdf0b02";
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

        pchMessageStart[0] = 0xad;
        pchMessageStart[1] = 0xa5;
        pchMessageStart[2] = 0xa0;
        pchMessageStart[3] = 0x93;
        nDefaultPort = 15333;

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

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
    (3368, uint256S("702024c340aa046a7349febb8395a7ccff1cf171831117aa13a69f842a789034"))
    (6737, uint256S("987ae56a0ba1271870edcd76b4dc4f09c800bced1adc6b65fdcced2e4148dc71"))
    (10106, uint256S("6210b4c3c8ee1d328781b0ce8bd2f59720748d0457540c48baba06f10d0b1901"))
    (13475, uint256S("7d71331c4b06f784bfc7b4772a9e1dc8dd475c9d71e6634bf7bfd45773a4468e"))
    (16844, uint256S("a43337df5c180206cafe06b68d90a81056a23eba137efccb1ea127b16980b0a6"))
    (20213, uint256S("2afc9827760f8cb0049f6a98854fdbf91e291faabb7f74334a3474e107f39bf0"))
    (23582, uint256S("62b6a4b6e78d5729135cd378492771b0fde1c7fab767d5427bb8b353b92dd371"))
    (26951, uint256S("8802b7057a7eabe16d1e94c0f2c93bdcc2924e741ff134dfc74af6ad56def621"))
    (30320, uint256S("4b03b5df5006f190175da362b36676199d8786d2ed5db0cb1ae7dc780e93faba"))
    (33689, uint256S("cb6c5be7d7056710d851db83093a09d4aff268f0f9d956edfab799db0668f748"))
    (37058, uint256S("977f210f5c37950317f1ece43f0fb94439a95ba8bd45a1861bcbb594b1425280"))
    (40427, uint256S("89b8752d2bbd3d23c678f8701ea0b292fbfb0563abc7f9b8fbc16abf9f739924"))
    (43796, uint256S("7b52c3521a6718cd33650563ca6432cf286c7883381d8830816b82fea0d70103"))
    (47165, uint256S("da33c287e62bd19c0be7b22aa1a236ae4d94c0968636806fd188f1519adad1b1"))
    (50534, uint256S("f570c7ebbaef066d43b8c47fbdf78a2d60134e01f1d2011f0135565416ec33bb"))
    (53903, uint256S("1dbb69d002244993ccc33e990e7c373f2b380f0a53f0dd6131f8533f7db3a36f"))
    (57272, uint256S("96a1de82eeb2a1b2d4fdce05d156ba0c36f7dc6a80620e265fe0bdb58ed3e6c7"))
    (60641, uint256S("6ef4e26b09a60192b1ad0f3ec3da208e15b18c09c5b93240095f3f4ef34161e1"))
    (64010, uint256S("937ddded7bf36c3d76b9f3bb1a5731a483f65068f25f6e378fb0a059c06faa4e"))
    (67379, uint256S("f1e181db9b48e5ceca3baa222f342e76da12a20cd99fcc9b9f105d7599b0ac14"))
    (70748, uint256S("71b832ae7ce99cc3647089e1b85a8d7d74d90d347546caf838ef2d84819a8423"))
    (74117, uint256S("ccada0ace09b3e4e2c8156d64e29ed53d0b094981573e37c54a73330d8fc93c8"))
    (77486, uint256S("f29f77c16c5300186558c2dffe58fdb0d36e9b137d2dcb9607403463c152f390"))
    (80855, uint256S("df1bb8c2824d56429e60330213a9f325f9e963444027284e419726e855a7caeb"))
    (84224, uint256S("57e4427ff6fd59b244f2d4fa23cd0e6682610b57ac932c56d3381f61374536f9"))
    (87593, uint256S("2698847845f87f04b74b8e09d434aa73c87c42b9e5a12d690aab9333f805c2c2"))
    (90962, uint256S("1e537e9a60fe3b2eb796571b85ba8310c761e3658eb0c60a2dd6ed930140f782"))
    (94331, uint256S("3810c8808c9ab7728e0f3fadd6db9af6164a164700cf51534abde08b0b8e46a6"))
    (97700, uint256S("8b932075cf7ae742ec75303132f7bf15862154c1a39ee44076e0a6cf549e8bdd"))
    (101069, uint256S("60aca38c2b768b1de6e36e7a9b645fd3a5dd7b62b23b36013de4564ad43ea6e7"))
    (104438, uint256S("0653cc9895af6bb12e95831ab30ea60fb13d48bf01b14c19a799d5db660cadbc"))
    (107807, uint256S("007edba3d9be77ee52d246838deb01f4aab679a2351ef12dccaaac06b84e355f"))
    (111176, uint256S("6e012b27f426f99a5cef02a2e3f17b77702bf3233e6a76f24b7f3dddde4e3781"))
    (114545, uint256S("e1e510041b371c3376086354d9956ec8756e82414ba207055b3eccf237418122"))
    (117914, uint256S("af29a66cb06104bddb81569702efae0265ea8ea128e40d7fc4bbbbd360f5e4b3"))
    (121283, uint256S("b333e159af8e288cc012f8316324fca54e6a52f7598f68f12eb325c42939f1c6"))
    (124652, uint256S("5526275aef59ce23a93cda35db35290581cf1011b433a7a36fa4f66659a1e8be"))
    (128021, uint256S("df4d628a47b544c1f3299879ba6719a6804a9b75e956e5cd38081ba9f492e1f2"))
    (131390, uint256S("ff615b46a2164570a628446a9f16fe4796e5ff064f0c8a3a5787766a4e47ca5a"))
    (134759, uint256S("d5df2d1005d0c1a458bcf7c87bcd1415e57dfa7ea08a57d1bec251babffe777c"))
    (138128, uint256S("877a3f5045f87421dbe5dc49f14fa13b6bec70d51da32065764c0ae678ff5edc"))
    (141497, uint256S("73fb00d87a773159f2fe831e4aa776d415ae91651b7ff2eb6e56cb3efcbe317d"))
    (144866, uint256S("939f480d7499e4d91ca8059ef8555ea7c149528b9a399a00de53d2d4f006ea22"))
    (148235, uint256S("9069df8d8595bbbaf7d4117f4aea30a5fb2d33a93d40c4feeef60f89d6eba94b"))
    (151604, uint256S("4c764794a19861c74505d677a906743d572398919cd2d69e760d13258a6b8efc"))
    (154973, uint256S("62aaee95b9c36f2acacca03bb19a642553d2d24b95f6803977b5408ef498a199"))
    (158342, uint256S("43392d5af4ffb1d18cb8a316bff705ffb3b8f99b09818201cea4d73ac04a13dc"))
    (161711, uint256S("75275252c00f8fcdacf70be8b27eb3cce41bd88e68d151b7498bc6b6bd4046d3"))
    (165080, uint256S("467ead1861907ab5e2ef49000530585e381d1d00d982a457c3fe137c15c46e10"))
    (168449, uint256S("2976c8fcefd0c310e6ad743e091e3aef1c97fc61a4400bb5f3c593abe44effb6"))
    (171818, uint256S("1bc4453a864ebd32591a036e3fa91536527617e83ee1052f55cfd1f9d5e3e2bc"))
    (175187, uint256S("2803e6d7a577ac063fe7a774bd488953cf68e8147e6983f471d6596501f72542"))
    (178556, uint256S("4aedffaf08fac2bfdf739beb638d6be5a5748d6e73a3068b1b0ec29c80854eec"))
    (181925, uint256S("7e3c5e8d4dab1e591856774a4df075013bc8786f488ed366bf42393909c55aec"))
    (185294, uint256S("7b4171d81e395e24f07e0604a4a7fb4d63e09e4d5fe4afdda91f6df5b790a060"))
    (188663, uint256S("e244683b11e459f35f89706517b8d0e2b4132d9e8a758851905897e9fd5841f1"))
    (192032, uint256S("7d59a37cfe3581b379482c8f10f5eb9741a2e60c535492250da44f2a5f6ce7dd"))
    (195401, uint256S("b2c37be4deace7e1b08973a9a9668d61efa056efe8666a369dfa6509cd96b082"))
    (198770, uint256S("8566cacce1cc3927451a8feb3547de914e4f4200894e8f0d6e14ae03626cdca9"))
    (202139, uint256S("414b6df50961bd1648a207ad345d79b50a798519d19e42ad47a92099eb27fbf9"))
    (205508, uint256S("dd24a829e7031553714b6302e5f9588417f4e9873bb2c0c9d24e08f0f163fd79"))
    (208877, uint256S("d674d121217e4d157c7a345392a7ee86575c67a26200f8540656a47b34d4d869"))
    (212246, uint256S("2eb0b3d60d5c8897360ebb13a8245782d89363f56aeb6d7c8482100117528c36"))
    (215615, uint256S("09557bb22ed14dc5c4308dc6853cdcbe4848163463d986ce1d882c9868c30d86"))
    (218984, uint256S("51d60fc9f9ed30e26cc8d9c94ed3d772c702af6e8b95ecfe32e0e1f6812ef39e"))
    (222353, uint256S("c1e2832971d5351392d3d32c698667a672968e5d9ea0f12652e152f1dc9cec13"))
    (225722, uint256S("c427edd3ca8a317f04059cfca6141268987f86d1b9db73bca154f5c09208ccde"))
    (229091, uint256S("acae4be94ffb094390228ecdef314a6766f9b52006c224a0eb23714516590560"))
    (232460, uint256S("d715983e76363379b283cb47c129f57a7af42df2c947ce2c478ab456edf19466"))
    (235829, uint256S("2272e7edcb6d97f7a554464a76a0701510b2bbbadee95ae869d325efce34f819"))
    (239198, uint256S("c150f731c767a184521fafb5b0461b80dbab836807e942e100054b8c05ff146b"))
    (242567, uint256S("252ead22ab1271f81beda1be9ecaf55a729e350c72b19b753e5173f998dda644"))
    (245936, uint256S("32b175b66fd2ef00d422bb3785710b0a02d1d21eddcfd51a97ffc71271d84560"))
    (249305, uint256S("d19bb236d27da37de1f05b79d8ceff365d825fdf4d2dcf64a0ce5bf51780892c"))
    (252674, uint256S("b9281a8f6ed178b20fe0e8cb6d79e81d7f1a8efc2b4bc0e5de8d056930863b7d"))
    (256043, uint256S("1abfb13093bcf99926da0f05041de0d14b76d482c34a911bad6bb55be571f22c"))
    (259412, uint256S("92e995f16f9cd4e0b6cfbdbee6b66f929cf65224a88bb26ed24d57f979a03502"))
    (262781, uint256S("cc8907175893869f6cf1426633b05a3e2f5375ae7859bc4665ed41d1d8609e7a"))
    (266150, uint256S("30f11b3421652408f88a2f4177957b5c9e03c01a7634274234bdc389a26f87e1"))
    (269519, uint256S("82f2a64a7600b97ceef7d5ae2dcaa55f6969d0a3cf0db54b23f6b7f515538f02"))
    (272888, uint256S("a9ada77f83a734e61526addc697d14248262258d90245db99040d53de2ddc2d8"))
    (276257, uint256S("a04e4615443b210d0e5296c95e56ff5485fa48f80616174957695538550d9cc8"))
    (279626, uint256S("94b69dd5d7ea09246f6b1da1ce3e885cbd233e6145656f7660fde8d67be8cccb"))
    (282995, uint256S("2a1fa0421274008efcc23caec129b0520cfff29bc56152de7e27928905c085ed"))
    (286364, uint256S("efcf6bcc34d6f38141a3f39d78ac3ebb69bad371f5ba39853ee215c9138e4888"))
    (289733, uint256S("5190834b055fb7e125d3152176a7660da22d3908b973eff5f00b0b1e8c92f85f"))
    (293102, uint256S("d00272571bd7efc1edec19286ccf26b4ac08880addeb24139cfd163e36f39b0d"))
    (296471, uint256S("e3164d331dd73f114c1bd896e900425239c875f565d204b173410583df7eebab"))
    (299840, uint256S("07686a57313744d2b14410ccdbb8776209588c7e9fdfd3d8bf315e41dc9da31d"))
    (303209, uint256S("093ae8cc9978b90f93efee586559f7546b9d4c3832a2e1c5a6c9911efdb956c6"))
    (306578, uint256S("d740c7ee7dee0751c3207bdab1ba7d753877630b85f36083682de7c508e8b7e3"))
    (309947, uint256S("d51d10e815c729dfeea97131342846ee6e15c55cf2da9e5518ff742f1caf3d8b"))
    (313316, uint256S("ec04e1d540fd9f175520bf63720f58fcacea4c40b2a0d20ae7602181c62e6f25"))
    (316685, uint256S("be4a3f17d11a056fb97925b0fa7826af179966df393c34a581b694ebe43b3c6e"))
    (320054, uint256S("d97de2044c624cfb4e1123681e7155914f819030a46b03c4780aacc756ed55f1"))
    (323423, uint256S("094aeee88af871d88d0da4155b799c18513e888b7314356fe9bc5abbaae203bf"))
    (326792, uint256S("e57a0c891dfad72619eedcfe47bfcb448ad471a1eae6c0a9d65547008a675ef7"))
    (330161, uint256S("0a86056978470c7fb4a8015cea78c4187a73c1b2c8bd9a1a69001b2486683bca"))
    (333530, uint256S("4f1db55fe1ce7d7983e4136dbeb5527816ee1b64905ba62ded7c7b6c8f1a8728"))
;

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1642563690, // * UNIX timestamp of last checkpoint block
    715920,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    2928        // * estimated number of transactions per day after checkpoint
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

/**
Copyright (c) 2010 Satoshi Nakamoto
Copyright (c) 2009-2012 The Bitcoin developers
Copyright (c) 2018 VCC developers
Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
*/
#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

static void convertSeeds(std::vector<CAddress>& vSeedsOut, const unsigned int* data, unsigned int count, int port)
{
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int k = 0; k < count; ++k) {
        struct in_addr ip;
        unsigned int i = data[k], t;

        t = (i & 0x000000ff) << 24u | (i & 0x0000ff00) << 8u | (i & 0x00ff0000) >> 8u | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/*******************/
/* Main network    */
/*******************/
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0x1b;
        pchMessageStart[2] = 0xcf;
        pchMessageStart[3] = 0x65;
        vAlertPubKey = ParseHex("0425b474f33e3d56692ba8c04f752a15850e574e33cf1484692c1035c6627c42a2b7ff5d1ce8606d38a5ed959f2935827d9a8333ebd1cc3f3f7c6f1189c8434e48");
        nDefaultPort = 23346;
        nRPCPort = 23347;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char* pszTimestamp = "VCC Genesis";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1523833200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1523833200;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 751050;


        /* REMOVE AFTER GENESIS BLOCK */
        /*
        hashGenesisBlock = uint256("0x");
        if (true && (genesis.GetHash() != hashGenesisBlock)) {
            cout << "Recalculating params for mainnet. : \n"
                 << endl;
            cout << "--------------------------------------" << endl;
            cout << "mainnet.genesis : \n        " << genesis.ToString() << endl;
            cout << "old mainnet genesis hash: \n"
                 << hashGenesisBlock.ToString() << endl;
            cout << "--------------------------------------" << endl;

            // deliberately empty for loop finds nonce value.
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            for (genesis.nNonce = 0; genesis.GetHash() > hashTarget; genesis.nNonce++) {
            }

            cout << "--------------------------------------" << endl;
            cout << "mainnet.genesis : \n            " << genesis.ToString() << endl;
            cout << "mainnet.genesis.GetHash():      " << genesis.GetHash().ToString() << endl;
            cout << "mainnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "mainnet.genesis.nTime:          " << genesis.nTime << endl;
            cout << "mainnet.genesis.nNonce:         " << genesis.nNonce << endl;
            cout << "--------------------------------------" << endl;
        }
        */

        /* REMOVE ABOVE AFTER GENESIS BLOCK */


        /** Genesis block info:
        mainnet.genesis.GetHash():      00000781b3f88fe9ad9fe9c3f2edf7bcf0e4aef6db1f2ccb35085462c0a3544d
        mainnet.genesis.hashMerkleRoot: bd789803ac51cafda6c806403cc7dfeabc97593631f5e3a3d602b09980d767a1
        mainnet.genesis.nTime:          1521870556
        mainnet.genesis.nNonce:         1479185

        mainnet.genesis.GetHash():      0000092fa0d904cdf3ede53f44d3e42e16402883c724b8466430d25b65722b0e
        mainnet.genesis.hashMerkleRoot: a7cf34a559e86b8480d698cb329363cf7a6344340db7eb12566fea5d7ba5c1fe
        mainnet.genesis.nTime:          1523833200
        mainnet.genesis.nNonce:         751050
        */
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x0000092fa0d904cdf3ede53f44d3e42e16402883c724b8466430d25b65722b0e"));
        assert(genesis.hashMerkleRoot == uint256("0xa7cf34a559e86b8480d698cb329363cf7a6344340db7eb12566fea5d7ba5c1fe"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 10);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 43);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 147);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 188);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0", "45.77.206.142"));
        vSeeds.push_back(CDNSSeedData("1", "45.77.147.162"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "CEuDqDZwKQnWQky9Sq9ys6AB2sPPm4SCUx";
        nLastPOWBlock = 1000;
        nPOSStartBlock = 2;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const
    {
        return vFixedSeeds;
    }

protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


/*******************/
/* TestNet network */
/*******************/
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x2b;
        pchMessageStart[2] = 0xcf;
        pchMessageStart[3] = 0x65;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        vAlertPubKey = ParseHex("040124d14e569bd4176927884504f782d12c94b6ec332259ad50d861d3020bdde158cde46201908e18b4cf366e7bd03b61121104f3caad746e88f5cf2daf94e14c");
        nDefaultPort = 22346;
        nRPCPort = 22347;
        strDataDir = "testnet";

        const char* pszTimestamp = "VCC Genesis Test";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1523833200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1523833200;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;


        /* REMOVE AFTER GENESIS BLOCK */
        /*
        hashGenesisBlock = uint256("0x");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            cout << "Recalculating params for testnet. : \n" << endl;
            cout << "--------------------------------------" << endl;
            cout << "testnet.genesis : \n        " << genesis.ToString() << endl;
            cout << "old testnet genesis hash: \n" << hashGenesisBlock.ToString() << endl;
            cout << "--------------------------------------" << endl;

            // deliberately empty for loop finds nonce value.
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            for(genesis.nNonce = 0; genesis.GetHash() > hashTarget; genesis.nNonce++){ }

            cout << "--------------------------------------" << endl;
            cout << "testnet.genesis : \n            " << genesis.ToString() << endl;
            cout << "testnet.genesis.GetHash():      " << genesis.GetHash().ToString() << endl;
            cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "testnet.genesis.nTime:          " << genesis.nTime << endl;
            cout << "testnet.genesis.nNonce:         " << genesis.nNonce << endl;
            cout << "--------------------------------------" << endl;
        }
        */

        /* REMOVE ABOVE AFTER GENESIS BLOCK */


        /**
        testnet.genesis.GetHash():      0000040fa46af9b92dfc7682c8e42810a83d02f1ecca44f3c32a1b84c423e946
        testnet.genesis.hashMerkleRoot: 436d3d31f58cd34b0944b979d99608647512ee9f52bbd615b9bbca8ba0e611d4
        testnet.genesis.nTime:          1521870556
        testnet.genesis.nNonce:         71957
        */
        hashGenesisBlock = genesis.GetHash();

        //assert(hashGenesisBlock == uint256("0x0000040fa46af9b92dfc7682c8e42810a83d02f1ecca44f3c32a1b84c423e946"));
        //assert(genesis.hashMerkleRoot == uint256("0x436d3d31f58cd34b0944b979d99608647512ee9f52bbd615b9bbca8ba0e611d4"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 11);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 29);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 150);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 300;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams* pCurrentParams = &mainParams;

const CChainParams& Params()
{
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network) {
    case CChainParams::MAIN:
        pCurrentParams = &mainParams;
        break;
    case CChainParams::TESTNET:
        pCurrentParams = &testNetParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

bool SelectParamsFromCommandLine()
{
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}

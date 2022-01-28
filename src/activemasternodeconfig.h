// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SRC_ACTIVEMASTERNODECONFIG_H_
#define SRC_ACTIVEMASTERNODECONFIG_H_

#include "fs.h"

#include <string>
#include <vector>

class CActiveMasternodeConfig;
extern CActiveMasternodeConfig activeMasternodeConfig;

class CActiveMasternodeConfig
{
public:
    class CActiveMasternodeEntry
    {
    public:
        std::string alias;
        std::string externalIp;
        std::string privKey;
        std::string bindAddr;

        CActiveMasternodeEntry(std::string alias, std::string externalIp, std::string privKey, std::string bindAddr)
        {
            this->alias = alias;
            this->externalIp = externalIp;
            this->privKey = privKey;
            this->bindAddr = bindAddr;
        }

        const std::string& getAlias() const
        {
            return alias;
        }

        void setAlias(const std::string& alias)
        {
            this->alias = alias;
        }
        
        const std::string& getExternalIP() const
        {
            return externalIp;
        }

        void setExternalIP(const std::string& externalIp)
        {
            this->externalIp = externalIp;
        }
        

        const std::string& getPrivKey() const
        {
            return privKey;
        }

        void setPrivKey(const std::string& privKey)
        {
            this->privKey = privKey;
        }

        const std::string& getBindAddr() const
        {
            return bindAddr;
        }

        void setBindAddr(const std::string& bindAddr)
        {
            this->bindAddr = bindAddr;
        }
    };

    CActiveMasternodeConfig()
    {
        entries = std::vector<CActiveMasternodeEntry>();
    }
    
    void clear();
    bool read(std::string& strErr);
    CActiveMasternodeConfig::CActiveMasternodeEntry* add(std::string alias, std::string externalIp, std::string privKey, std::string bindAddr);
    void remove(std::string alias);

    std::vector<CActiveMasternodeEntry>& getEntries()
    {
        return entries;
    }

    int getCount()
    {
        int c = -1;
        for (auto e : entries) {
            if (e.getAlias() != "") c++;
        }
        return c;
    }

private:
    std::vector<CActiveMasternodeEntry> entries;
};


#endif /* SRC_ACTIVEMASTERNODECONFIG_H_ */

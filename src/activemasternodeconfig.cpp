// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2019 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "netbase.h"
#include "activemasternodeconfig.h"
#include "util.h"
#include "guiinterface.h"
#include <base58.h>
#include <algorithm>

CActiveMasternodeConfig activeMasternodeConfig;

CActiveMasternodeConfig::CActiveMasternodeEntry* CActiveMasternodeConfig::add(std::string alias, std::string externalIp, std::string privKey, std::string bindAddr)
{
    CActiveMasternodeEntry cme(alias, externalIp, privKey, bindAddr);
    entries.push_back(cme);
    return &(entries[entries.size()-1]);
}

void CActiveMasternodeConfig::remove(std::string alias) {
    int pos = -1;
    for (int i = 0; i < ((int) entries.size()); ++i) {
        CActiveMasternodeEntry e = entries[i];
        if (e.getAlias() == alias) {
            pos = i;
            break;
        }
    }
    entries.erase(entries.begin() + pos);
}

bool CActiveMasternodeConfig::read(std::string& strErr)
{
    int linenumber = 1;
    fs::path pathActiveMasternodeConfigFile = GetActiveMasternodeConfigFile();
    fs::ifstream streamConfig(pathActiveMasternodeConfigFile);

    if (!streamConfig.good()) {
        FILE* configFile = fsbridge::fopen(pathActiveMasternodeConfigFile, "a");
        if (configFile != NULL) {
            std::string strHeader = "# Activemasternode config file\n"
                                    "# Format: alias externalIp activemasternodeprivkey bindAddr:port\n"
                                    "#\n"
                                    "# Example: mn1 40.51.62.73 93HaYBVUCYjEMeeH1Y4sBGLALQZE1Yc1K64xiqgX37tGBDQL8Xg 192.168.1.22:12345\n"
                                    "#\n";
            fwrite(strHeader.c_str(), std::strlen(strHeader.c_str()), 1, configFile);
            fclose(configFile);
        }
        return 0; // Nothing to read, so just return
    }

    for (std::string line; std::getline(streamConfig, line); linenumber++) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string comment, alias, externalIp, privKey, bindAddr;

        if (iss >> comment) {
            if (comment.at(0) == '#') continue;
            iss.str(line);
            iss.clear();
        }

        if (!(iss >> alias >> externalIp >> privKey >> bindAddr)) {
            iss.str(line);
            iss.clear();
            if (!(iss >> alias >> externalIp >> privKey >> bindAddr)) {
                strErr = _("Could not parse activemasternode.conf") + "\n" +
                         strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"";
                streamConfig.close();
                return -1;
            }
        }

        int port = 0;
        int nDefaultPort = Params().GetDefaultPort();
        std::string hostname = "";

        SplitHostPort(bindAddr, port, hostname);

        if(port == 0 || hostname == "") {
            strErr = _("Failed to parse host:port string") + "\n"+
                     strprintf(_("Line: %d"), linenumber) + "\n\"" + line + "\"";
            streamConfig.close();
            return -1;
        }

        if (port != nDefaultPort) {
            strErr = strprintf(_("Invalid port %d detected in activemasternode.conf"), port) + "\n" +
                     strprintf(_("Line: %d"), linenumber) + "\n\"" + externalIp + "\"" + "\n" +
                     strprintf(_("(must be %d for %s-net)"), nDefaultPort, Params().NetworkIDString());
            streamConfig.close();
            return -1;
        }


        add(alias, externalIp, privKey, bindAddr);
    }

    streamConfig.close();
    return true;
}

#define COIN "777"

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <cstdio>

#include <boost/json.hpp>
#include <boost/filesystem.hpp>

#include "update.h"
#include "httpclient.h"
//#include "clientversion.h"

#define CLIENT_VERSION_MAJOR 1
#define CLIENT_VERSION_MINOR 0
#define CLIENT_VERSION_REVISION 2
#define CLIENT_VERSION_BUILD 0

namespace fs = boost::filesystem;
namespace json = boost::json;

// get it from clientversion.h
static const int CLIENT_VERSION =
    1000000 * CLIENT_VERSION_MAJOR  ///
    + 10000 * CLIENT_VERSION_MINOR  ///
    + 100 * CLIENT_VERSION_REVISION ///
    + 1 * CLIENT_VERSION_BUILD;

// Define the progress callback function
static int DownloadProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {

    // Calculate progress percentage
    double progress = (dlnow > 0) ? (dlnow / dltotal) * 100.0 : 0.0;

    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    static bool log_flag = false; // Declare log_flag as static
    if (!log_flag && duration.count() % 2 == 0) {
        log_flag = true;
        LogPrintf("-Update: Download: %d%%\n", (uint8_t)progress);
        // LogPrintf("-Bootstrap: Download: %d%%\n", (uint8_t)progress);
        // uiInterface.ShowProgress(_("Download: "), (uint8_t)progress);    
    } else if (duration.count() % 2 != 0) {
        log_flag = false;
    }

    return 0;
}

int main(int argc, char* argv[]) {

    // TODO
    // remove files - on progress
    // make it fail:
        // - no network
        // - file transfer interrupt
        // - request denied
    // change logs - done
    // check syntax - on progress
    // recover current program
    // check MD5 hash if available on header
    // test on windows and macos
    // merge with code

    std::string execName;
    if (argc > 0) {
        execName = argv[0];
        if (execName.substr(0, 2) == "./") {
            execName = execName.substr(2);
        }
        LogPrintf("-Update: Executable name: %s\n",execName);
    } else {
        LogPrintf("-Update: No executable name found\n");
    }

    LogPrintf("-Update: Let's update our app\n");

    HTTPClient client;
    Update update;

    const std::string url = std::string(UPDATE_URL)+std::string(TICKER)+"/releases/latest";
    std::string response = client.get(url);

    json::value jv = json::parse(response);
    update.ParseVersionRequest(jv);
    int version = update.GetRemoteVersion();
    LogPrintf("-Update: remote version: %d\n",version);

    if(version > CLIENT_VERSION){
        LogPrintf("-Update: update app\n");
        if(update.GetLatestVersion()<0){
            LogPrintf("-Update: couldn't update for the new app\n");
            return 0;
        }

        LogPrintf("-Update: lauching new app\n");

        // look for this function
        // ParseParameters()

        // !! optimize the following code !!

        std::vector<std::string> files;
        // get name of the actual app,
        bool ready = false;
        bool launch = true;
        // check if there is a file with the same name inside zip file
        const std::string directoryPath = "app_";
        if (fs::exists(directoryPath) && fs::is_directory(directoryPath)) {

            for (const auto& entry : fs::directory_iterator(directoryPath)) {
                std::string file = entry.path().filename().string();
                files.push_back(file);
                if( file == execName)
                    ready = true;
            }
        } else {
            LogPrintf("-Update: Directory does not exist or is not a directory: %s\n",directoryPath);
        }

        const std::string bckFolder = "app_bck";
        if( ready && update.EnsureOutputFolder(bckFolder) ){
            for (const std::string& file : files) {
                if(fs::exists(file)){        
                    std::string file_backup = bckFolder+"/"+file;
                    fs::rename(file.c_str(), file_backup.c_str());
                }

                try {
                    fs::path destinationFile = fs::current_path() / file;
                    fs::path sourceFile = fs::current_path() / directoryPath / file;
                    fs::copy_file(sourceFile, destinationFile, fs::copy_options::overwrite_existing);
                } catch (const fs::filesystem_error& e) {
                    LogPrintf("-Update: Filesystem error: %s\n",e.what());
                    launch = false;
                } catch (const std::exception& e) {
                    LogPrintf("-Update: General error: %s\n",e.what());
                    launch = false;
                }

            }
        }else launch = false;

        // proceed with new app
        if(launch){

            // grant file permission
            #if defined (_WIN32)
                std::string permission = "F";
                std::string command = "icacls \"" + execName + "\" /grant Everyone:" + permission;
            #else
                std::string permission = "u+x";
                std::string command = "chmod "+ permission + " " + execName;
            #endif 
            int status = std::system(command.c_str());
            if (status != 0) {
                // update.recover();
                LogPrintf("-Update: Failed to change file permission: %s\n",execName);
            }else{

                #if defined (_WIN32)
                    std::string command = execName;
                #else
                    std::string command = " ./"+execName;
                #endif

                int status = std::system(command.c_str());
                if (status == -1) {
                    // update.recover();
                    LogPrintf("-Update: Failed to execute command: \"%s\"",command);
                } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    // update.recover();
                    LogPrintf("-Update: Command failed with exit code %s: while executing \"%s\"", std::to_string(WEXITSTATUS(status)),command);
                }
            }
            

        }
    }else{
        LogPrintf("-Update: current version is the most recent\n");
    }

    return 0;
}

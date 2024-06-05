
#include "update.h"

#include <functional> 
#include <cerrno>  // For perror
#include <cstring>  // For strerror
#include <iostream>
#include <stdexcept>
#include <fstream>
//#include <sstream>
//#include <iomanip>
#include <cstdio>
#include <string>
#include <unordered_map>

#include <boost/json.hpp>
#include <boost/filesystem.hpp>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <sys/stat.h>

namespace fs = boost::filesystem;
namespace json = boost::json;

static bool log_flag = false;
Latest latest;

std::vector<std::string> executablesFiles;
std::unordered_map<std::string, std::string> filehash; // hashmap with executable files and respective sha256 hash

int CUpdate::progressCallback(
    void* clientp, 
    curl_off_t dltotal,
    curl_off_t dlnow,
    curl_off_t ultotal,
    curl_off_t ulnow)
{
    static int progress = 0;
    const auto currentProgress = dltotal > 0 ? (int)((dlnow * 100) / dltotal) : 0;

    if (currentProgress > progress) {
        progress = currentProgress;
        LogPrintf("CUpdate::%s: Download: %d%%\n", __func__, progress);
        uiInterface.ShowProgress(_("Download: "), progress);
    }

    return 0;
}

// keep on update.h file
void CUpdate::ParseVersionRequest(json::value const& jv, std::string* indent){
    std::string indent_;
    if(! indent)
        indent = &indent_;
    switch(jv.kind())
    {
        case json::kind::object:
        {
            indent->append(4, ' ');
            auto const& obj = jv.get_object();
            if(! obj.empty())
            {
                auto it = obj.begin();
                for(;;)
                {
                    std::string key = json::serialize(it->key()); 
                    if( key.compare("\"tag_name\"") == 0){
                        latest.version = json::serialize(it->value().get_string());
                        latest.version = RemoveQuotes(latest.version);
                    }else if( key.compare("\"browser_download_url\"") == 0 ){
                        std::string url = json::serialize(it->value().get_string()); 
                        url = RemoveQuotes(url);
                        #if defined(__APPLE__)
                            if( EndsWith(url, "MacOS-x64.zip") || EndsWith(url, "macos-x64.zip") )
                                latest.url = url;
                            if( EndsWith(url, "SHA256SUMS-MacOS-x64.ASC") || EndsWith(url, "SHA256SUMS-macos-x64.ASC") )
                                latest.sha256_url = url;
                        #elif defined(__linux__)
                            #if defined(__x86_64__) || defined(_M_X64)
                                if (EndsWith(url, "Linux-x64.zip") || EndsWith(url, "linux-x64.zip"))
                                    latest.url = url;
                                if (EndsWith(url, "SHA256SUMS-Linux-x64.ASC") || EndsWith(url, "SHA256SUMS-linux-x64.ASC"))
                                    latest.sha256_url = url;
                            #elif defined(__aarch64__) || defined(_M_ARM64)
                                if (EndsWith(url, "Linux-arm64.zip") || EndsWith(url, "linux-arm64.zip"))
                                    latest.url = url;
                                if (EndsWith(url, "SHA256SUMS-Linux-arm64.ASC") || EndsWith(url, "SHA256SUMS-linux-arm64.ASC"))
                                    latest.sha256_url = url;
                            #else
                                LogPrintf("Update: Platform not supported");
                            #endif
                        #elif defined(_WIN32)
                            if( EndsWith(url, "Windows-x64.zip") || EndsWith(url, "windows-x64.zip") )
                                latest.url = url;
                            if( EndsWith(url, "SHA256SUMS-Windows-x64.ASC") || EndsWith(url, "SHA256SUMS-windows-x64.ASC") )
                                latest.sha256_url = url;
                        #else
                            LogPrintf("-Update: OS not supported");
                        #endif
                    }else
                        ParseVersionRequest(it->value(), indent);
                    if(++it == obj.end())
                        break;
                }
            }
            indent->resize(indent->size() - 4);
            break;
        }
        case json::kind::array:
        {
            indent->append(4, ' ');
            auto const& arr = jv.get_array();
            if(! arr.empty())
            {
                auto it = arr.begin();
                for(;;)
                {
                    ParseVersionRequest(*it, indent);
                    if(++it == arr.end())
                        break;
                }
            }
            indent->resize(indent->size() - 4);
            break;
        }   
    }  
}

// keep on update.h file
int ParseVersionNumber(std::string& version){
    std::vector<int> versionNumbers;

    if (version.empty()){
        LogPrintf("Update: version is empty");
        return -1;
    } 

    if(version.find("-") > 0){
        version = version.substr(version.find("-")+1);
    }

    // Remove the leading "v" from the version string
    if(version[0] == 'v') {
        version = version.substr(1);
    }

    // check if format is x.x.x.x 

    // Tokenize the version string based on the '.' delimiter
    std::istringstream iss(version);
    std::string token;
    while (std::getline(iss, token, '.')) {
        try {
            int number = std::stoi(token);
            versionNumbers.push_back(number);
        } catch (const std::invalid_argument& ia) {
            LogPrintf("Invalid version format: %s\n",ia.what());
            return -1;
        }
    }

    // Calculate the numerical value of the version
    int versionValue = 0;
    for (int i = 0; i < versionNumbers.size(); ++i) {
        versionValue = versionValue * 100 + versionNumbers[i];
    }

    return versionValue;
}

// keep on update.h file
int CUpdate::GetRemoteVersion(){
    return ParseVersionNumber(latest.version);
}

// keep on update.h file
bool CUpdate::MoveListOfFilesFromToFolder(const std::vector<std::string>& files, const std::string& source_folder, const std::string& destination_folder) {
    // Create the destination folder if it doesn't exist
    fs::create_directories(destination_folder);

    for (const auto& file : files) {
        fs::path source_path = fs::path(source_folder) / fs::path(file);
        fs::path destination_path = fs::path(destination_folder) / fs::path(file);

        try {
            if (!fs::exists(source_path))
                continue;
            fs::rename(source_path, destination_path);
            std::cout << "Moved: " << source_path << " to " << destination_path << std::endl;
        } catch (const fs::filesystem_error& e) {
            LogPrintf("-Update: Filesystem error: %s\n",e.what());
            return false;
        }
    }
    return true;
}

// keep on update.h file
bool CUpdate::Recover(){
    // Recover backup files
    fs::path sourceFolder = fs::current_path() / UPDATE_BCK_FOLDER;
    fs::path destinationFolder = fs::current_path();
    if( !MoveListOfFilesFromToFolder(executablesFiles, sourceFolder.string(), destinationFolder.string()) ){
        LogPrintf("-Update: The update process failed and couldn't Recover the old version. Please deal with it manually, sorry for the inconvenient");
        return false;
    }
    fs::remove(sourceFolder.string());
    
    return true;
}

// keep on update.h file
int CUpdate::GetLatestVersion(){
    
    CCurlWrapper client;
    const std::string zipFile = UPDATE_ZIP_FOLDER;
    const std::string appPath = UPDATE_APP_FOLDER;  

    LogPrintf("-Update: get latest version from: %s\n", latest.url);

    if(latest.url.empty()){
        LogPrintf("-Update: No valid url to downloading new version");
        return -1;
    }
    if (!client.DownloadFile(latest.url, zipFile, CUpdate::progressCallback)) {
        LogPrintf("-Update: Error downloading file: %s\n",latest.url);
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        return -1;
    }
    
    const std::string sha256_file = "sha256sums.txt";
    if (client.DownloadFile(latest.sha256_url, sha256_file, CUpdate::progressCallback)) {

        std::ifstream file(sha256_file); // Open file

        if (!file.is_open()) {
            LogPrintf("-Update: Error opening file: %s\n",sha256_file);
            if (fs::exists(sha256_file))
                fs::remove(sha256_file);
            return -1;
        }

        std::string line;
        while (std::getline(file, line)) { // Read file line by line

            std::istringstream iss(line);
            std::string word, sha256, filename;
            int counter = 0;
            while (iss >> word) { // Split line into words based on spaces
                if(counter == 0)
                    sha256 = word;
                else if(counter == 1)
                    filename = word;
                counter++;
            }
            if( !IsValidSHA256(sha256.c_str()))
                continue;
            if( EndsWith(filename,".zip"))
                latest.sha256zip = sha256;
            else{
                filehash[filename] = sha256;
                executablesFiles.push_back(filename);
            }
        }

        file.close(); // Close file

        if (fs::exists(sha256_file))
            fs::remove(sha256_file);

    } else {
        LogPrintf("-Update: Error downloading hashes file: %s\n",latest.sha256_url);
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        if (fs::exists(sha256_file))
            fs::remove(sha256_file);
        return -1;
    }

    std::string hash = "";
    /*
    hash = File_SHA256(zipFile);
    if( hash != latest.sha256zip ){
        LogPrintf("-Update: sha256 doesn't match file: %s\n", zipFile );
        LogPrintf("-Update: calculated hash: %s\n", hash);
        LogPrintf("-Update: source hash: %s\n", latest.sha256zip);
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        if (fs::exists(sha256_file))
            fs::remove(sha256_file);
        return -1;
    }
    */

    if (!CZipWrapper::ExtractZip(zipFile, appPath)) {
        LogPrintf("-Update: Error extracting zip file.");
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        if (fs::exists(sha256_file))
            fs::remove(sha256_file);
        if (fs::exists(appPath))
            fs::remove(appPath);
        return -1;
    }

    if (fs::exists(zipFile))
        fs::remove(zipFile);

    // Iterate over the unordered_map
    for (const auto& pair : filehash) {
        std::string filename = appPath+"/"+pair.first;
        if(IsValidSHA256(pair.second.c_str())){
            hash = File_SHA256(filename);
            if( hash != "" && hash != pair.second ){
                LogPrintf("-Update: sha256 doesn't match file: %s\n", filename );
                LogPrintf("-Update: calculated hash: %s\n", hash);
                LogPrintf("-Update: source hash: %s\n", filehash[pair.second]);
                if (fs::exists(sha256_file))
                    fs::remove(sha256_file);
                if (fs::exists(appPath))
                    fs::remove(appPath);
                return -1;
            }
        }
    }

    if (fs::exists(sha256_file))
        fs::remove(sha256_file);

    return 0;
}

// keep on update.h file
bool CUpdate::Start(const std::string& execName){
    const std::string url = std::string(UPDATE_URL)+std::string(TICKER)+"/releases/latest";
    const std::string appPath = UPDATE_APP_FOLDER;  

    CCurlWrapper client;

    fs::path currentPath = fs::current_path();

    // Check if the current path is writable
    fs::perms perms = fs::status(currentPath).permissions();

    if ((perms & fs::perms::owner_write) != 0 ||
        (perms & fs::perms::group_write) != 0 ||
        (perms & fs::perms::others_write) != 0) {
    } else {
        LogPrintf("-Update: You do NOT have write permissions to the current path: %s \n",currentPath);
        LogPrintf("-Update: Trying to grant permissions..\n");
        uiInterface.InitMessage(_("User doesn't have permissions for current folder"));
        if(!grantWritePermissions(currentPath)){    
            uiInterface.InitMessage(_("Couldn't grant permissions for current folder"));
            return false;
        }
    }

    std::string response = client.Request(url);

    json::value jv = json::parse(response);
    ParseVersionRequest(jv);
    int version = GetRemoteVersion();

    // !! get version from correct file
    // --- Check if current version is lower than remote version ---
    LogPrintf("-Update: current version: %d\n",CLIENT_VERSION);
    LogPrintf("-Update: remote version: %d\n",version);
    if(false && version <= CLIENT_VERSION){
        LogPrintf("-Update: current version is the most recent\n");
        uiInterface.InitMessage(_("Current version is the most recent"));
        return false;
    }
    // --- ----- ---

    // --- Get latest version ---
    LogPrintf("-Update: updating app to version.. \n");
    if(GetLatestVersion()<0){
        LogPrintf("-Update: couldn't update for the new app\n");
        uiInterface.InitMessage(_("Couldn't get the latest version"));
        return false;
    }

    LogPrintf("-Update: lauching new app\n");

    bool ready = false;

    // --- Verify if the new executable exists and copy the executables files ---
    std::vector<std::string> files;
    const std::string directoryPath = UPDATE_APP_FOLDER;
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
    // --- ----- ---

    if(false && !ready){
        LogPrintf("-Update: Executable file not found");
        if (fs::exists(appPath))
            fs::remove(appPath);
        return false;
    }

    // --- Save the current executables into a backup folder --
    fs::path sourceFolder = fs::current_path();
    fs::path destinationFolder = fs::current_path() / UPDATE_BCK_FOLDER;

    // --- Create backup --
    if( !MoveListOfFilesFromToFolder(executablesFiles, sourceFolder.string(), destinationFolder.string()) ){
        LogPrintf("-Update: The update process failed while creating a backup");
        if (fs::exists(appPath))
            fs::remove(appPath);
        if (fs::exists(destinationFolder.string()))
            fs::remove(destinationFolder.string());
        return false;
    }
    // --- ----- ---

    // --- Get the new executable files ---
    sourceFolder = fs::current_path() / UPDATE_APP_FOLDER;
    destinationFolder = fs::current_path();
    if( !MoveListOfFilesFromToFolder(executablesFiles, sourceFolder.string(), destinationFolder.string()) ){
        LogPrintf("-Update: The update process failed while getting the new executables");
        if (fs::exists(appPath))
            fs::remove(appPath);
        Recover();
    }
    fs::remove(sourceFolder.string());
    // --- ----- ---

    // --- Try to launch new app ---
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
        LogPrintf("-Update: Failed to change file permission: %s\n",execName);
        uiInterface.InitMessage(_("Failed to change file permission"));
        Recover();
    }

    return true;
}

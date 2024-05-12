#define COIN "777"

#include <boost/json.hpp>
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
        std::printf("-update: Download: %d%%\n", (uint8_t)progress);
        // LogPrintf("-Bootstrap: Download: %d%%\n", (uint8_t)progress);
        // uiInterface.ShowProgress(_("Download: "), (uint8_t)progress);    
    } else if (duration.count() % 2 != 0) {
        log_flag = false;
    }

    return 0;
}

int main() {

    std::cout << "Let's update our app" << std::endl;

    HTTPClient client;
    Update update;

    const std::string url = std::string(UPDATE_URL)+std::string(TICKER)+"/releases/latest";
    std::string response = client.get(url);

    json::value jv = json::parse(response);
    update.ParseVersionRequest(jv);
    int version = update.GetRemoteVersion();
    std::cout << "remote version: " << version << "\n";

    if(version > CLIENT_VERSION){
        std::cout << "update app" << std::endl;
        update.GetLatestVersion();
    }else{
        std::cout << "current version is the most recent" << std::endl;
    }
    //std::cout << "Parsed JSON: " << jv << std::endl;
    //std::cout << "Serialized JSON: " << boost::json::serialize(jv) << std::endl;

    //std::cout << "Response from " << url << ":\n" << response << std::endl;
    return 0;

    
    /*
    std::cout << "current version is: " << std::string(VERSION) << std::endl;
    const char* currentApp = "test";
    const char* currentAppBackup = "test_bck";
    
    if( VERSION != "1.0.0.1"){
        int result = std::rename(currentApp, currentAppBackup);
        if (result == 0) {
            std::cout << "Executable renamed successfully." << std::endl;
        } else {
            std::cerr << "Error renaming executable: " << strerror(errno) << std::endl;
        }
        
        std::system("./app");
    }

    while(1);
    */
    
    /*
    
    const std::string outputFileName = "bootstrap.zip";
    const std::string extractPath = "bootstrap_";

    std::cout << "Download: " << url << std::endl;

    if(Bootstrap::IsDirectory(extractPath))
        Bootstrap::RemoveDirectory(extractPath);

    if (Bootstrap::DownloadFile(url, outputFileName, DownloadProgressCallback)) {
        std::cout << "File downloaded successfully." << std::endl;

        if (Bootstrap::extractZip(outputFileName, extractPath)) {
            std::cout << "Zip file extracted successfully." << std::endl;
        } else {
            std::cerr << "Error extracting zip file." << std::endl;
        }

        if(Bootstrap::IsDirectory(extractPath))
            Bootstrap::RmDirectory(extractPath);
    
    } else {
        std::cerr << "Error downloading file." << std::endl;
    }

    fs::remove(outputFileName);
    */
    return 0;
}

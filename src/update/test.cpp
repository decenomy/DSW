#include <string>

#include "update.h"

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
        // uiInterface.ShowProgress(_("Download: "), (uint8_t)progress);    
    } else if (duration.count() % 2 != 0) {
        log_flag = false;
    }

    return 0;
}

int main(int argc, char* argv[]) {

    // TODO
    // remove files - done
    // make it fail:
        // - no network
        // - file transfer interrupt
        // - request denied
    // change logs - done
    // check syntax - on progress
    // recover current program - test
    // check MD5 hash if available on header - todo
    // test on windows and macos
    // merge with code

    // !! Make it fail
    
    // look for this function
    // ParseParameters()

    // --- Get executable name ---
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

    // --- ----- ---

    LogPrintf("-Update: Let's update our app\n");

    // --- Get info from latest version ---
    //Update update();
    Update::start(execName);
    std::string suffix = "-qt";
    if (execName.size() >= suffix.size()) {
        if(execName.compare(execName.size() - suffix.size(), suffix.size(), suffix) == 0){
            // print some dialog message
            LogPrintf("-Update: program will continue on current version");
        }
    }else{
        LogPrintf("-Update: try to fix the problem and run it again");
    }
    // if we got here some error occurred
    // 

    return 0;
}

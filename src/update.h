#ifndef UPDATE_H
#define UPDATE_H


#include "clientversion.h"
#include "util.h"
#include "zip.h"
#include "curl.h"
#include "clientversion.h"


#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/json.hpp>
#include <unordered_map> // Include the header for std::unordered_map
#include <vector>

#include "minizip/unzip.h"
#ifdef UPDATETEST
	#include "logging.h"
#else
	#include "../logging.h"
#endif

#ifndef UPDATE_URL
#define UPDATE_URL "https://api.github.com/repos/decenomy/"
#endif

#ifndef TICKER
#define TICKER "DSW"
#endif

#define UPDATE_ZIP_FOLDER "newRelease.zip"
#define UPDATE_APP_FOLDER "newRelease"
#define UPDATE_BCK_FOLDER "bckRelease"

struct Latest {
	std::string version;
	std::string url;
	std::string md5;
	std::string sha256_url;
	std::string sha256zip;
};

class CUpdate{

public:

	// Define the function pointer type
    //using ProgressCallbackFunc = std::function<int(void*, double, double, double, double)>;
	
	static bool Start(std::string execName);

private:

	static bool MoveListOfFilesFromToFolder(const std::vector<std::string>& files, const std::string& source_folder, const std::string& destination_folder);
	static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static bool DownloadFile(const std::string& url, const std::string& outputFileName, curl_progress_callback);
	static void ParseVersionRequest(boost::json::value const& jv, std::string* indent = nullptr);
	static int GetRemoteVersion();
	static bool Recover();
	static int GetLatestVersion();
    
};

#endif

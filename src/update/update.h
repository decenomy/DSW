#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <functional> 
#include <cerrno>  // For perror
#include <cstring>  // For strerror
#include <iostream>
#include <cstdio>
#include <string>
#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/stat.h>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/json.hpp>

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

#ifdef NEWVERSION
#define VERSION "1.0.0.1"
#endif

#ifndef VERSION
#define VERSION "1.0.0.0"
#endif

#ifndef APPLE_CA_PATH
#define APPLE_CA_PATH "/etc/ssl/cert.pem"
#endif
//#define LINUX_CA_PATH "/etc/ssl/certs/ca-certificates.crt"
//#define WIN_CA_PATH ""


struct Latest {
	std::string version;
	std::string url;
};

class Update{

public:
	// Define the function pointer type
    //using ProgressCallbackFunc = std::function<int(void*, double, double, double, double)>;
	static int ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	static bool RemoveDirectory(const std::string& path);
	static bool IsDirectory(const std::string& path);
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static bool DownloadFile(const std::string& url, const std::string& outputFileName, curl_progress_callback);
	static bool ExtractZip(const std::string& inputPath, const std::string& outputPath);
	void ParseVersionRequest(boost::json::value const& jv, std::string* indent = nullptr);
	int GetRemoteVersion();
	int GetLatestVersion();
private:

	static bool EnsureOutputFolder(const std::string& outputPath);
	static bool EndsWithSlash(const std::string& str);

};

#endif

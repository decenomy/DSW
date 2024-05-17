
#include "update.h"

#include <functional> 
#include <cerrno>  // For perror
#include <cstring>  // For strerror
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <unordered_map>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

#include <sys/stat.h>



namespace fs = boost::filesystem;
namespace json = boost::json;

static bool log_flag = false;
Latest latest;


std::string CalculateMD5(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        LogPrintf("-MD5: Error opening file: %s\n",filePath);
        return "";
    }

    MD5_CTX mdContext;
    MD5_Init(&mdContext);

    const int bufferSize = 4096;
    char buffer[bufferSize];
    while (file) {
        file.read(buffer, bufferSize);
        MD5_Update(&mdContext, buffer, file.gcount());
    }
    file.close();

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &mdContext);

    char md5String[MD5_DIGEST_LENGTH * 2 + 1];
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(&md5String[i*2], "%02x", (unsigned int)digest[i]);

    return md5String;
}


// Callback function to write received headers to a string
size_t HeaderCallback(void* buffer, size_t size, size_t nmemb, std::string* headers) {
    size_t totalSize = size * nmemb;
    headers->append((char*)buffer, totalSize);
    return totalSize;
}

std::string RemoveQuotes(const std::string& str) {
    std::string result = str;
    
    // Check if the string starts with a double quote
    if (!result.empty() && result.front() == '"') {
        result.erase(0, 1); // Erase the first character
    }
    
    // Check if the string ends with a double quote
    if (!result.empty() && result.back() == '"') {
        result.pop_back(); // Remove the last character
    }

    return result;
}

bool EndsWith(const std::string& fullString, const std::string& ending) {
    if (fullString.length() >= ending.length()) {
        return (fullString.compare(fullString.length() - ending.length(), ending.length(), ending) == 0);
    } else {
        return false;
    }
}


bool Update::RemoveDirectory(const std::string& directory_path) {

    try {
        if (fs::exists(directory_path)) {
            fs::remove_all(directory_path);
        }
    } catch (const fs::filesystem_error& ex) {
        LogPrintf("-Update: Error removing directory: %s\n",ex.what());
        return false;
    }

    return true;
}

bool Update::IsDirectory(const std::string& directory_path) {

    if (fs::exists(directory_path)) return true;

    return false;
}

// Callback function to write downloaded data to a file
size_t Update::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<const char*>(contents), total_size);
    return total_size;
}

// Define a function to handle progress updates
int Update::ProgressCallback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow) {
    // Calculate progress percentage
    double progress = (dlnow > 0) ? (dlnow / dltotal) * 100.0 : 0.0;

    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    if(!log_flag && duration.count() % 2 == 0){
        log_flag = true;
        LogPrintf("-Update: Download: %d%%\n", (uint8_t)progress);
        //uiInterface.ShowProgress(_("Download: "), (uint8_t)progress);    
    }else if(duration.count() % 2 != 0) log_flag = false;
    
    return 0;
}

// Function to download a file using libcurl
bool Update::DownloadFile(const std::string& url, const std::string& outputFileName, curl_progress_callback func) {

    CURL* curl = curl_easy_init();
    if (!curl) {
        LogPrintf("-Update: Error initializing libcurl.");
        return false;
    }

    curl_version_info_data *info = curl_version_info(CURLVERSION_NOW);

    if (!info) {
        LogPrintf("-Update: Failed to retrieve libcurl version information.\n");
    }

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        LogPrintf("-Update: Error opening output file.");
        return false;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify the peer's SSL certificate
    curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outputFile);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

    // Follow redirects
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Set the callback function to receive headers
    std::string headers;
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);

    // Set User-Agent header
    if (info) {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, info->version);
    }

    if(func == nullptr)
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);
    else
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, func);

    #if defined(__APPLE__)
        LogPrintf("-Update: apple ca path: %s \n",(const char*)APPLE_CA_PATH);
        curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)APPLE_CA_PATH);
    #elif defined(__linux__)
        //LogPrintf("-Update: linux ca path: " << (const char*)LINUX_CA_PATH);
        //curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)LINUX_CA_PATH);
    #elif defined(_WIN32)
        ///LogPrintf("-Update: windows ca path: " << (const char*)WIN_CA_PATH);
        //curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)WIN_CA_PATH);
    #else
        LogPrintf("-Update: OS not recognized, CA Path not defined");
    #endif

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        LogPrintf("-Update: Error: Failed to perform HTTP request: %s\n", curl_easy_strerror(res));
    } else {
        // Print the received headers
        // std::cout << "Received headers:\n" << headers << std::endl;
    }

    curl_easy_cleanup(curl);
    outputFile.close();

    /* !! calculate md5hash if available
    std::string hexMD5 = CalculateMD5(outputFileName);
    std::cout << "calculated md5: " << hexMD5 << std::endl;

    // get md5 from header
    std::string headerMD5 = "Z+Ye9ExZ/IUfkl/Rb5piiQ==";
    std::string decoded = "";
    base64Decode(headerMD5,decoded);
    std::string hex = stringToHex(decoded);
    std::cout << "headerMD5: " << hex << std::endl;
    */

    if (res != CURLE_OK) {
        LogPrintf("-Update: Error downloading file: %s \n",curl_easy_strerror(res));
        return false;
    }

    return true;
}

bool Update::ExtractZip(const std::string& zipFilePath, const std::string& outputFolderPath) {

    // Open the zip file
    unzFile zipFile = unzOpen(zipFilePath.c_str());
    if (!zipFile) {
        LogPrintf("-Update: Error opening zip file: %s \n",zipFilePath);
        return false;
    }

    // Create the output folder if it doesn't exist
    if (!EnsureOutputFolder(outputFolderPath)) {
        LogPrintf("-Update: Error creating output folder: %s \n",outputFolderPath);
        unzClose(zipFile);
        return false;
    }

    // Go through each file in the zip and extract it
    unz_global_info globalInfo;
    if (unzGetGlobalInfo(zipFile, &globalInfo) != UNZ_OK) {
        LogPrintf("-Update: Error getting global info from zip file.");
        unzClose(zipFile);
        return false;
    }

    for (uLong i = 0; i < globalInfo.number_entry; ++i) {
        char fileName[256];
        unz_file_info fileInfo;

        if (unzGetCurrentFileInfo(zipFile, &fileInfo, fileName, sizeof(fileName), nullptr, 0, nullptr, 0) != UNZ_OK) {
            LogPrintf("-Update: Error getting file info from zip file.");
            unzClose(zipFile);
            return false;
        }

        if (unzOpenCurrentFile(zipFile) != UNZ_OK) {
            LogPrintf("-Update: Error opening current file in zip.");
            unzClose(zipFile);
            return false;
        }

        std::string outputPath = std::string(outputFolderPath) + "/" + fileName;
        LogPrintf("-Update: extract file: %s \n",fileName);

        if(EndsWithSlash(outputPath))
            EnsureOutputFolder(outputPath);
        else{
            std::ofstream outFile(outputPath, std::ios::binary);
            if (!outFile.is_open()) {
                LogPrintf("-Update: Error creating output file: %s \n",outputPath);
                unzCloseCurrentFile(zipFile);
                unzClose(zipFile);
                return false;
            }

            // Read and write the file data
            char buffer[4096];
            int bytesRead;

            while ((bytesRead = unzReadCurrentFile(zipFile, buffer, sizeof(buffer))) > 0) {
                outFile.write(buffer, bytesRead);
            }
            outFile.close();
        }


        unzCloseCurrentFile(zipFile);

        if (unzGoToNextFile(zipFile) != UNZ_OK) {
            break;  // Reached the end of the zip file
        }
    }

    // Close the zip file
    unzClose(zipFile);

    return true;

}

bool Update::EnsureOutputFolder(const std::string& outputPath) {
    try {
        if (!fs::exists(outputPath)) {
            // Create the directory if it doesn't exist
            fs::create_directories(outputPath);
        } else if (!fs::is_directory(outputPath)) {
            // If it exists but is not a directory, print an error
            LogPrintf("-Update: Error: Output path %s is not a directory.\n", outputPath);
            return false;
        }
    } catch (const std::exception& e) {
        // Handle any exceptions that may occur during filesystem operations
        LogPrintf("-Update: Error creating output folder: %s \n",e.what());
        return false;
    }

    return true;
}

bool Update::EndsWithSlash(const std::string& str) {
    // Check if the string ends with '/'
    return !str.empty() && str.back() == '/';
}

void Update::ParseVersionRequest(json::value const& jv, std::string* indent){
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
                            if( EndsWith(url, "MacOs-x64.zip") || EndsWith(url, "macos-x64.zip") )
                                latest.url = url;
                            if( EndsWith(url, "SHA256SUMS-MacOs-x64.ASC") || EndsWith(url, "SHA256SUMS-macos-x64.ASC") )
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

int Update::GetRemoteVersion(){
    return ParseVersionNumber(latest.version);
}

bool base64Decode(const std::string &input, std::string &out) {
    static constexpr unsigned char kDecodingTable[] = {
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63, 52, 53, 54, 55, 56, 57,
        58, 59, 60, 61, 64, 64, 64, 64, 64, 64, 64, 0,  1,  2,  3,  4,  5,  6,
        7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 64, 64, 64, 64, 64, 64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
        37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
        64, 64, 64, 64
    };

    size_t in_len = input.size();
    if (in_len % 4 != 0)
      return false;

    size_t out_len = in_len / 4 * 3;
    if (in_len >= 1 && input[in_len - 1] == '=')
      out_len--;
    if (in_len >= 2 && input[in_len - 2] == '=')
      out_len--;

    out.resize(out_len);

    for (size_t i = 0, j = 0; i < in_len;) {
        uint32_t a = input[i] == '='
           ? 0 & i++
           : kDecodingTable[static_cast<int>(input[i++])];
        uint32_t b = input[i] == '='
           ? 0 & i++
           : kDecodingTable[static_cast<int>(input[i++])];
        uint32_t c = input[i] == '='
           ? 0 & i++
           : kDecodingTable[static_cast<int>(input[i++])];
        uint32_t d = input[i] == '='
           ? 0 & i++
           : kDecodingTable[static_cast<int>(input[i++])];

        uint32_t triple =
            (a << 3 * 6) + (b << 2 * 6) + (c << 1 * 6) + (d << 0 * 6);

        if (j < out_len)
            out[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < out_len)
            out[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < out_len)
            out[j++] = (triple >> 0 * 8) & 0xFF;
    }

    return true;
}

std::string stringToHex(const std::string& input) {
    std::string hex;
    for (char c : input) {
        hex += "0123456789ABCDEF"[((unsigned char)c) >> 4];
        hex += "0123456789ABCDEF"[((unsigned char)c) & 0xf];
    }
    return hex;
}

std::string sha256(const std::string& path)
{
  std::ifstream fp(path, std::ios::in | std::ios::binary);

  if (not fp.good()) {
    std::ostringstream os;
    LogPrintf("-SHA256: Error: %s, Cannot open: %s\n",std::strerror(errno),path);
    return "";
  }

  constexpr const std::size_t buffer_size { 1 << 12 };
  char buffer[buffer_size];

  unsigned char hash[SHA256_DIGEST_LENGTH] = { 0 };

  SHA256_CTX ctx;
  SHA256_Init(&ctx);

  while (fp.good()) {
    fp.read(buffer, buffer_size);
    SHA256_Update(&ctx, buffer, fp.gcount());
  }

  SHA256_Final(hash, &ctx);
  fp.close();

  std::ostringstream os;
  os << std::hex << std::setfill('0');

  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    os << std::setw(2) << static_cast<unsigned int>(hash[i]);
  }

  return os.str();
}

int Update::GetLatestVersion(){
    
    const std::string zipFile = "app.zip";
    const std::string appPath = "app_";
    std::unordered_map<std::string, std::string> filehash;

    LogPrintf("-Update: get latest version from: %s\n", latest.url);

    if(latest.url.empty()){
        LogPrintf("-Update: No valid url to downloading new version");
        return -1;
    }
    if (!DownloadFile(latest.url, zipFile, nullptr)) {
        LogPrintf("-Update: Error downloading file: %s\n",latest.url);
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        return -1;
    }
    
    const std::string sha256_file = "sha256sums.txt";
    if (DownloadFile(latest.sha256_url, sha256_file, nullptr)) {

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
            if( EndsWith(filename,".zip"))
                latest.sha256zip = sha256;
            else
                filehash[filename] = sha256;
        }

        file.close(); // Close file

        if (fs::exists(sha256_file))
            fs::remove(sha256_file);

    } else {
        LogPrintf("-Update: Error downloading hashes file: %s\n",latest.sha256_url);
        if (fs::exists(sha256_file))
            fs::remove(sha256_file);
        return -1;
    }


    std::string hash = sha256(zipFile);
    if( hash != latest.sha256zip ){
        LogPrintf("-Update: sha256 doesn't match for file: %s\n", zipFile );
        LogPrintf("-Update: calculated hash: %s\n", hash);
        LogPrintf("-Update: source hash: %s\n", latest.sha256zip);
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        return -1;
    }


    if (!ExtractZip(zipFile, appPath)) {
        LogPrintf("-Update: Error extracting zip file.");
        if (fs::exists(zipFile))
            fs::remove(zipFile);
        if (fs::exists(appPath))
            fs::remove(appPath);
        return -1;
    }

    if (fs::exists(zipFile))
        fs::remove(zipFile);

    // Iterate over the unordered_map
    for (const auto& pair : filehash) {
        std::string filename = appPath+"/"+pair.first;
        hash = sha256(filename);
        if( hash != pair.second ){
            LogPrintf("-Update: sha256 doesn't match for file: %s\n", filename );
            LogPrintf("-Update: calculated hash: %s\n", hash);
            LogPrintf("-Update: source hash: %s\n", filehash[pair.second]);
            return -1;
        }
    }

    return 0;
}
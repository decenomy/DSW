
#include "update.h"

#include <iostream>
#include <fstream>
#include <string>
#include <openssl/md5.h>

namespace fs = boost::filesystem;
namespace json = boost::json;

static bool log_flag = false;
Latest latest;

std::string hexToUtf8(const std::string& hex) {
    std::string utf8;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = static_cast<unsigned char>(std::stoi(byteString, nullptr, 16));
        utf8.push_back(byte);
    }
    return utf8;
}

std::string CalculateMD5(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filePath << std::endl;
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
size_t headerCallback(void* buffer, size_t size, size_t nmemb, std::string* headers) {
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
        // Check if the directory exists
        if (fs::exists(directory_path)) {
            // Remove the directory and its contents
            fs::remove_all(directory_path);
            //LogPrintf("-bootstrap: Directory removed successfully.");
        } else {
            //LogPrintf("-bootstrap: Directory does not exist.");
        }
    } catch (const fs::filesystem_error& ex) {
        //LogPrintf("-bootstrap: Error removing directory: " << ex.what());
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
        LogPrintf("-bootstrap: Download: %d%%\n", (uint8_t)progress);
        //uiInterface.ShowProgress(_("Download: "), (uint8_t)progress);    
    }else if(duration.count() % 2 != 0) log_flag = false;
    
    return 0;
}

// Function to download a file using libcurl
bool Update::DownloadFile(const std::string& url, const std::string& outputFileName, curl_progress_callback func) {

    CURL* curl = curl_easy_init();
    if (!curl) {
        //LogPrintf("-bootstrap: Error initializing libcurl.");
        return false;
    }

    curl_version_info_data *info = curl_version_info(CURLVERSION_NOW);

    if (!info) {
        LogPrintf("-update: Failed to retrieve libcurl version information.\n");
    }

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        LogPrintf("-bootstrap: Error opening output file.");
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
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
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
        LogPrintf("-bootstrap: apple ca path: %s \n",(const char*)APPLE_CA_PATH);
        curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)APPLE_CA_PATH);
    #elif defined(__linux__)
        //LogPrintf("-bootstrap: linux ca path: " << (const char*)LINUX_CA_PATH);
        //curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)LINUX_CA_PATH);
    #elif defined(_WIN32)
        ///LogPrintf("-bootstrap: windows ca path: " << (const char*)WIN_CA_PATH);
        //curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)WIN_CA_PATH);
    #else
        LogPrintf("-bootstrap: OS not recognized, CA Path not defined");
    #endif

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error: Failed to perform HTTP request: " << curl_easy_strerror(res) << std::endl;
    } else {
        // Print the received headers
        std::cout << "Received headers:\n" << headers << std::endl;
    }

    curl_easy_cleanup(curl);
    outputFile.close();

    if (res != CURLE_OK) {
        LogPrintf("-bootstrap: Error downloading file: %s \n",curl_easy_strerror(res));
        return false;
    }

    return true;
}

bool Update::ExtractZip(const std::string& zipFilePath, const std::string& outputFolderPath) {

    // Open the zip file
    unzFile zipFile = unzOpen(zipFilePath.c_str());
    if (!zipFile) {
        LogPrintf("-bootstrap: Error opening zip file: %s \n",zipFilePath);
        return false;
    }

    // Create the output folder if it doesn't exist
    if (!EnsureOutputFolder(outputFolderPath)) {
        LogPrintf("-bootstrap: Error creating output folder: %s \n",outputFolderPath);
        unzClose(zipFile);
        return false;
    }

    // Go through each file in the zip and extract it
    unz_global_info globalInfo;
    if (unzGetGlobalInfo(zipFile, &globalInfo) != UNZ_OK) {
        LogPrintf("-bootstrap: Error getting global info from zip file.");
        unzClose(zipFile);
        return false;
    }

    for (uLong i = 0; i < globalInfo.number_entry; ++i) {
        char fileName[256];
        unz_file_info fileInfo;

        if (unzGetCurrentFileInfo(zipFile, &fileInfo, fileName, sizeof(fileName), nullptr, 0, nullptr, 0) != UNZ_OK) {
            LogPrintf("-bootstrap: Error getting file info from zip file.");
            unzClose(zipFile);
            return false;
        }

        if (unzOpenCurrentFile(zipFile) != UNZ_OK) {
            LogPrintf("-bootstrap: Error opening current file in zip.");
            unzClose(zipFile);
            return false;
        }

        std::string outputPath = std::string(outputFolderPath) + "/" + fileName;
        LogPrintf("-bootstrap: extract file: %s \n",fileName);

        if(EndsWithSlash(outputPath))
            EnsureOutputFolder(outputPath);
        else{
            std::ofstream outFile(outputPath, std::ios::binary);
            if (!outFile.is_open()) {
                LogPrintf("-bootstrap: Error creating output file: %s \n",outputPath);
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

    LogPrintf("-bootstrap: Zip extraction successful.");

    return true;

}

bool Update::EnsureOutputFolder(const std::string& outputPath) {
    try {
        if (!fs::exists(outputPath)) {
            // Create the directory if it doesn't exist
            fs::create_directories(outputPath);
        } else if (!fs::is_directory(outputPath)) {
            // If it exists but is not a directory, print an error
            LogPrintf("-bootstrap: Error: Output path %s is not a directory.", outputPath);
            return false;
        }
    } catch (const std::exception& e) {
        // Handle any exceptions that may occur during filesystem operations
        LogPrintf("-bootstrap: Error creating output folder: %s \n",e.what());
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
            //std::cout << "{\n";
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
                        //std::cout << "remote version: " << latest.version << "\n";
                        //ParseVersionNumber(version);
                        //std::cout << "local version: " << CLIENT_VERSION << "\n";
                    }else if( key.compare("\"browser_download_url\"") == 0 ){
                        std::string url = json::serialize(it->value().get_string()); 
                        url = RemoveQuotes(url);
                        #if defined(__APPLE__)
                            if( EndsWith(url, "MacOs-x64.zip") || EndsWith(url, "macos-x64.zip") )
                                latest.url = url;
                        #elif defined(__linux__)
                            if( EndsWith(url, "Linux-x64.zip") || EndsWith(url, "linux-x64.zip") )
                                latest.url = url;
                        #elif defined(_WIN32)
                            if( EndsWith(url, "Windows-x64.zip") || EndsWith(url, "windows-x64.zip") )
                                latest.url = url;
                        #else
                            std::cout << "not supported"  << "\n";
                        #endif
                    }else
                        ParseVersionRequest(it->value(), indent);
                    if(++it == obj.end())
                        break;
                    //std::cout << ",\n";
                }
            }
            //std::cout << "\n";
            indent->resize(indent->size() - 4);
            //std::cout << *indent << "}";
            break;
        }
        case json::kind::array:
        {
            //std::cout << "[\n";
            indent->append(4, ' ');
            auto const& arr = jv.get_array();
            if(! arr.empty())
            {
                auto it = arr.begin();
                for(;;)
                {
                    //std::cout << *indent;
                    ParseVersionRequest(*it, indent);
                    if(++it == arr.end())
                        break;
                    //std::cout << ",\n";
                }
            }
            //std::cout << "\n";
            indent->resize(indent->size() - 4);
            //std::cout << *indent << "]";
            break;
        }   
    }  
}

int ParseVersionNumber(std::string& version){
    std::vector<int> versionNumbers;

    if (version.empty()){
        return -1;
        std::cerr << "version is empty" << std::endl;
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
            std::cerr << "Invalid version format: " << ia.what() << std::endl;
            return -2;
        }
    }

    // Calculate the numerical value of the version
    int versionValue = 0;
    for (int i = 0; i < versionNumbers.size(); ++i) {
        versionValue = versionValue * 100 + versionNumbers[i];
    }

    std::cout << "Numerical value of version " << version << ": " << versionValue << std::endl;

    return versionValue;
}

int Update::GetRemoteVersion(){
    return ParseVersionNumber(latest.version);
}

std::string base64Decode(const std::string &input, std::string &out) {
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
      return "Input data size is not a multiple of 4";

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

    return "";
}

std::string stringToHex(const std::string& input) {
    std::string hex;
    for (char c : input) {
        hex += "0123456789ABCDEF"[((unsigned char)c) >> 4];
        hex += "0123456789ABCDEF"[((unsigned char)c) & 0xf];
    }
    return hex;
}

int Update::GetLatestVersion(){
    
    const std::string outputFileName = "app.zip";
    const std::string extractPath = "app_";
    std::cout << "get latest version from: " << latest.url << std::endl;

    if(latest.url.empty()){
        std::cerr << "No valid url to downloading new version" << std::endl;
        return -1;
    }
    if (DownloadFile(latest.url, outputFileName, nullptr)) {
        std::cout << "File downloaded successfully." << std::endl;

        std::string hexMD5 = CalculateMD5(outputFileName);
        std::cout << "calculated md5: " << hexMD5 << std::endl;

        // get md5 from header
        std::string headerMD5 = "Z+Ye9ExZ/IUfkl/Rb5piiQ==";
        std::string decoded = "";
        base64Decode(headerMD5,decoded);
        std::string hex = stringToHex(decoded);
        std::cout << "headerMD5: " << hex << std::endl;

        if (ExtractZip(outputFileName, extractPath)) {
            std::cout << "Zip file extracted successfully." << std::endl;
        } else {
            std::cerr << "Error extracting zip file." << std::endl;
        }
        /*
        if(IsDirectory(extractPath))
            RemoveDirectory(extractPath);
        */
    } else {
        std::cerr << "Error downloading file." << std::endl;
    }
}
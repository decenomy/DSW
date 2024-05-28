// Copyright (c) 2024 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "curl.h"

#include "init.h"
#include "logging.h"

#include <openssl/md5.h>

// Callback function to write downloaded data to a file
size_t downloadWriteCallback(void* data, size_t size, size_t nmemb, void* clientp)
{
    if(ShutdownRequested()) {
        LogPrintf(
            "CCurlWrapper::%s: Shutdown requested while downloading a file\n", 
            __func__);
        return 0;
    }

    size_t total_size = size * nmemb;
    std::ofstream* file = static_cast<std::ofstream*>(clientp);
    file->write(static_cast<const char*>(data), total_size);
    return total_size;
}

// Callback function to append downloaded data from a request method
size_t requestWriteCallback(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

// Callback function to write received headers to a string
size_t headerCallback(void* buffer, size_t size, size_t nmemb, std::string* headers) {
    size_t totalSize = size * nmemb;
    headers->append((char*)buffer, totalSize);
    return totalSize;
}

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

bool Base64Decode(const std::string &input, std::string &out) {
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

CCurlWrapper::CCurlWrapper() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        LogPrintf("CCurlWrapper::%s: Error initializing libcurl.\n", __func__);
    }else{
        // Gets libcurl version information
        const auto info = curl_version_info(CURLVERSION_NOW);
        if (info) {
            LogPrintf(
                "CCurlWrapper::%s: libcurl version: %s\n", 
                __func__, info->version);
            LogPrintf(
                "CCurlWrapper::%s: libcurl SSL version: %s\n", 
                __func__, info->ssl_version);
            LogPrintf(
                "CCurlWrapper::%s: libcurl zlib version: %s\n", 
                __func__, info->libz_version);
        } else {
            LogPrintf(
                "CCurlWrapper::%s: Failed to retrieve libcurl version information.\n", 
                __func__);
        }
    }
}

CCurlWrapper::~CCurlWrapper() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

bool CCurlWrapper::DownloadFile(
    const std::string& url,
    const std::string& filename,
    curl_xferinfo_callback xferinfoCallback)
{
    try {

        LogPrintf(
            "CCurlWrapper::%s: Downloading from %s\n", 
            __func__,
            url);

        // Creates and open the destination file
        std::ofstream outputFile(filename, std::ios::binary);
        if (!outputFile.is_open()) {
            LogPrintf(
                "CCurlWrapper::%s: Error opening output file %s\n", 
                __func__, filename);
            return false;
        }

        // Sets url parameter
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Sets HTTPS parameters
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
#if defined(__APPLE__)
        LogPrintf("CCurlWrapper::%s: apple ca path: %s\n", __func__, (const char*)APPLE_CA_PATH);
        curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)APPLE_CA_PATH);
#endif

        // Sets file releated parameters
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadWriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outputFile);

        // Sets progress function parameters
        if (xferinfoCallback) {
            // Enable the progress function
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            // Set up the progress function
            curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, xferinfoCallback);
            // Necessary to pass the callback to CURLOPT_XFERINFODATA (not used)
            curl_easy_setopt(curl, CURLOPT_XFERINFODATA, NULL); 
        }

        // Follow redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Set the callback function to receive headers
        std::string headers;
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headers);

        const auto info = curl_version_info(CURLVERSION_NOW);
        printf("info version: %s\n",info->version);
        // Set User-Agent header
        if (info) {
            curl_easy_setopt(curl, CURLOPT_USERAGENT, info->version);
        }

        // HTTP call execution
        const auto res = curl_easy_perform(curl);

        outputFile.close();

        /* !! calculate md5hash if available
        std::string hexMD5 = CalculateMD5(outputFileName);
        std::cout << "calculated md5: " << hexMD5 << std::endl;

        // get md5 from header
        std::string headerMD5 = "Z+Ye9ExZ/IUfkl/Rb5piiQ==";
        std::string decoded = "";
        Base64Decode(headerMD5,decoded);
        std::string hex = StringToHex(decoded);
        std::cout << "headerMD5: " << hex << std::endl;
        */

        // Evaluation and return
        if (res != CURLE_OK) {
            if(!ShutdownRequested()) {
                LogPrintf(
                    "CCurlWrapper::%s: Error downloading file: %s\n", 
                    __func__, curl_easy_strerror(res));
            }
            fs::remove_all(filename);
            return false;
        }
    } catch (const std::exception& e) {
        LogPrintf(
            "CCurlWrapper::%s: Error downloading file: %s\n", 
            __func__, e.what());
        fs::remove_all(filename);
        return false;
    }

    return true;
}

std::string CCurlWrapper::Request(const std::string& url) {

    std::string response = "";
    try {
        LogPrintf("CCurlWrapper::%s: request: %s\n", __func__, url);
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify the peer's SSL certificate
            curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, requestWriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

#if defined(__APPLE__)
            LogPrintf("CCurlWrapper::%s: apple ca path: %s\n", __func__, (const char*)APPLE_CA_PATH);
            curl_easy_setopt(curl, CURLOPT_CAINFO, (const char*)APPLE_CA_PATH);
#endif
            
            // Set User-Agent header
            curl_version_info_data *info = curl_version_info(CURLVERSION_NOW);

            if (info) {
                curl_easy_setopt(curl, CURLOPT_USERAGENT, info->version);
            }else{
                 curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl x.xx");
            }
            
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                LogPrintf("CCurlWrapper::%s: error: Failed to perform HTTP request: %s", __func__, curl_easy_strerror(res));
            }
        }
    } catch (const std::exception& e) {
        LogPrintf(
            "CCurlWrapper::%s: Error requesting url: %s\n", 
            __func__, e.what());
        return "";
    }

    
    return response;
}

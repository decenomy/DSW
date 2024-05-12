#include "httpclient.h"

HTTPClient::HTTPClient() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: Failed to initialize libcurl." << std::endl;
    }
}

HTTPClient::~HTTPClient() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

std::string HTTPClient::get(const std::string& url) {

    std::cout << "get info from: " << url << std::endl;
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify the peer's SSL certificate
        curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Set User-Agent header
        curl_version_info_data *info = curl_version_info(CURLVERSION_NOW);

        if (info) {
            curl_easy_setopt(curl, CURLOPT_USERAGENT, info->version);
        }
        
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error: Failed to perform HTTP request: " << curl_easy_strerror(res) << std::endl;
        }
    }
    return response;
}

size_t HTTPClient::writeCallback(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

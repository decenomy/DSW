#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <curl/curl.h>

#ifdef UPDATETEST
    #include "logging.h"
#else
    #include "../logging.h"
#endif

class HTTPClient {
public:
    HTTPClient();
    ~HTTPClient();
    std::string get(const std::string& url);

private:
    CURL* curl;
    static size_t writeCallback(void* ptr, size_t size, size_t nmemb, std::string* data);
};

#endif // HTTPCLIENT_H

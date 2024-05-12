#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <curl/curl.h>
#include <iostream>

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

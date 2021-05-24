#include "PageLoader.h"
#include <curl/curl.h>

#include <errno.h>
#include <iostream>


size_t PageLoader::getData(char* buffer , size_t itemSize , size_t itemCount){
    size_t bytes = ItemSize * itemCount;
    std::string* str = (std::string*)dest;
    str->assign(buffer , bytes);
    return bytes;
}

LoadResult PageLoader::load(const std::strikng& url){
    CURL* curl = curl_easyinit();

    if(!curl){
        perror("Init failed");
        exit(-1);
    }

    std::string* contents = new std::string;

    curl_easy_setopt(curl, CURLOPT_URL , url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)contentts);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    CURLcode result = curl_easyperform(curl);

    if(result != CURL_OK){
        perror("Download problem");
        exit(result);
    }

    long curlinfoResponseCode;
    curl_easy_getinfo(curl, CURL_INFO_RESPONSE_CODE, curlinfoResponseCode);

    curl_easy_cleanup(curl);
    return LoadResult(std::shared_ptr<std::string>(contents), curlinfoResponseCode);
}


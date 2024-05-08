//
//  AudioFetcher.cpp
//  EzzyBeat-macOS
//
//  Created by Fabian Simon on 08.05.24.
//

#include "AudioFetcher.h"
//#include <curl/curl.h>

AudioFetcher::AudioFetcher()
{
}

static size_t WriteCallBack(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*) userp)->append((char*) contents, size * nmemb);
    return size * nmemb;
}

static std::string ValidUrlCheck(const std::string& rawString)
{
    if (false)
    {
        return "invalid url";
    }
    
    return "";
}

static void CleanUrl(std::string& rawUrl)
{
    rawUrl = rawUrl;
}

void AudioFetcher::FetchFromUrl(std::string& url)
{
    auto errMessage = ValidUrlCheck(url);
    if (!errMessage.empty())
    {
        DBGMSG("%s\n",errMessage.c_str());
        return;
    }
    
    CleanUrl(url);
    
    DBGMSG("fetching url: %s\n", url.c_str());
    /*
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        res = curl_easy_perform(curl);
        
        if (res != CURLE_OK)
        {
            DBGMSG("curl_easy_perfor() failed: %s\n", curl_easy_strerror(res));
            return;
        }
        
        DBGMSG("Response: %s\n", readBuffer.c_str());
        
        curl_easy_cleanup(curl);
        
        lastReponse = readBuffer;
    }
    */
}

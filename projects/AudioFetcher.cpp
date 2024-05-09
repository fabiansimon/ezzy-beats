//
//  AudioFetcher.cpp
//  EzzyBeat-macOS
//
//  Created by Fabian Simon on 08.05.24.
//

#include "AudioFetcher.h"


static std::string COMMAND_BASE = "youtube-dl --extract-audio --audio-format mp3 --audio-quality 0 -o \"~/Desktop/%(title)s.%(ext)s\" ";


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


static bool YoutubeDLCheck() {
    return system("youtube-dl --version") == 0;
}


void AudioFetcher::FetchFromUrl(std::string& url, const std::string& outputPath)
{
    auto errMessage = ValidUrlCheck(url);
    if (!errMessage.empty())
    {
        DBGMSG("%s\n", errMessage.c_str());
        return;
    }
    
    CleanUrl(url);
    
    DBGMSG("fetching url: %s\n", url.c_str());
    
    DBGMSG("youtube-dl installed: %d\n", YoutubeDLCheck());
    
    if (!YoutubeDLCheck()) {
        DBGMSG("youtube-dl not installed.");
        return;
    }
    
    std::string command = COMMAND_BASE + "\"" + url + "\"";
    DBGMSG("%s\n", command.c_str());
    system(command.c_str());
}


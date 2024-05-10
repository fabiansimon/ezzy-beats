//
//  AudioFetcher.cpp
//  EzzyBeat-macOS
//
//  Created by Fabian Simon on 08.05.24.
//

#include "AudioFetcher.h"

static std::string COMMAND_BASE = "youtube-dl --extract-audio --audio-format mp3 --write-thumbnail --audio-quality 0 -o ";
static std::string PROJECT_FOLDER_NAME = "EzzyBeats";

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

static std::string GetTempPath() 
{
    std::string path;
    #ifdef _WIN32
        char const* temp = getenv("TEMP");
        if (temp == nullptr) temp = "C:\\Temp";  // Fallback if TEMP is not set
        path = temp;
    #else
        path = "/tmp";
    #endif
    return path;
}

static std::string UnixTimestamp() 
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    return std::to_string(seconds);
}

static std::string GenerateBasePath(std::string& base) 
{ 
    auto tempPath = GetTempPath();
    auto timestamp = UnixTimestamp();
    auto fileName = "%(title)s.%(ext)s";
    
    base = tempPath + "/" + PROJECT_FOLDER_NAME + "/" + timestamp;

    return base + "/" + fileName;
}

void AudioFetcher::FetchFromUrl(std::string& url, std::string& basePath)
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

    std::string outputPath = GenerateBasePath(basePath);
    std::string fetchCmd = COMMAND_BASE + "\"" + outputPath + "\"" + " \"" + url + "\"";

    DBGMSG("%s\n", fetchCmd.c_str());

    system(fetchCmd.c_str());

    std::string convertCmd = "find " + basePath + " \\( -name \\*.webp -o -name \\*.jpg \\) -exec sh -c '"
           "file=\"$1\"; "
           "outdir=$(dirname \"$file\"); "
           "case \"$file\" in "
           "*.webp) "
           "dwebp \"$file\" -o \"$outdir/thumbnail.png\" && rm \"$file\" ;; "
           "*.jpg) "
           "convert \"$file\" \"$outdir/thumbnail.png\" && rm \"$file\" ;; "
           "esac' sh {} \\;";

    system(convertCmd.c_str());

    DBGMSG("Finished");
}

#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include <string>
#include <chrono>

using namespace iplug;
using namespace igraphics;

class AudioFetcher
{
public:
    AudioFetcher();
    
    void FetchFromUrl(std::string& url, std::string& basePath);

private:
    std::string lastReponse; 
};

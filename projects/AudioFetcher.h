#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include <string>

using namespace iplug;
using namespace igraphics;

class AudioFetcher
{
public:
    AudioFetcher();
    
    void FetchFromUrl(std::string& url);

private:
    std::string lastReponse; 
};

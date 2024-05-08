#include "EzzyBeat.h"
#include "AudioFetcher.h"
#include "IPlug_include_in_plug_src.h"
#include "IControls.h"
#include "IControl.h"
#include "iostream"

enum EControlTags
{
  kTagEditText = 100,
  kTagButton,
  kTagKnob
};

EzzyBeat::EzzyBeat(const InstanceInfo& info)
: Plugin(info, MakeConfig(kNumParams, kNumPresets))
{
#if IPLUG_EDITOR // http://bit.ly/2S64BDd
  mMakeGraphicsFunc = [&]() {
    return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
  };
  

  mLayoutFunc = [this](IGraphics* pGraphics) { this->CreateUI(pGraphics); };
#endif
}

#if IPLUG_DSP
void EzzyBeat::ProcessBlock(sample** inputs, sample** outputs, int nFrames)
{
  const double gain = GetParam(kGain)->Value() / 100.;
  const int nChans = NOutChansConnected();
  
  for (int s = 0; s < nFrames; s++) {
    for (int c = 0; c < nChans; c++) {
      outputs[c][s] = inputs[c][s] * gain;
    }
  }
}
#endif

#if IPLUG_EDITOR
void EzzyBeat::CreateUI(IGraphics* pGraphics)
{
    const IRECT b = pGraphics->GetBounds();
    
    pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
    pGraphics->AttachPanelBackground(COLOR_WHITE);
    pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);

    pGraphics->AttachControl(new IEditableTextControl(b.GetFromTop(50), "Enter Youtube URL"), kTagEditText);
    pGraphics->AttachControl(new IVButtonControl(b.GetFromTop(50).GetVShifted(100), [pGraphics](IControl* pCaller) {
        ITextControl* pTextControl = dynamic_cast<ITextControl*>(pGraphics->GetControlWithTag(kTagEditText));
        if (pTextControl)
        {
            std::string url = pTextControl->GetStr();
            AudioFetcher* fetcher = new AudioFetcher();
            fetcher->FetchFromUrl(url);
        }
    }, "Fetch Beat"));
    
}
#endif

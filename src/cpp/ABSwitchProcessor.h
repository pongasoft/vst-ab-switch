#ifndef VST_AB_SWITCH_ABSWITCHPROCESSOR_H
#define VST_AB_SWITCH_ABSWITCHPROCESSOR_H

#include <public.sdk/source/vst/vstaudioeffect.h>

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {

class ABSwitchProcessor : public AudioEffect
{
public:
  ABSwitchProcessor();

  ~ABSwitchProcessor() override;

  /** Called at first after constructor */
  tresult PLUGIN_API initialize(FUnknown *context) override;

  /** Called at the end before destructor */
  tresult PLUGIN_API terminate() override;

  /** Switch the Plug-in on/off */
  tresult PLUGIN_API setActive(TBool state) override;

  /** Here we go...the process call */
  tresult PLUGIN_API process(ProcessData &data) override;

  /** Asks if a given sample size is supported see \ref SymbolicSampleSizes. */
  tresult PLUGIN_API canProcessSampleSize (int32 symbolicSampleSize) override;

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this Plug-in
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/) { return (IAudioProcessor *) new ABSwitchProcessor(); }

protected:
  //==============================================================================
  template <typename SampleType>
  SampleType processAudio (SampleType** input,
                           SampleType** output,
                           int32 numChannels,
                           int32 sampleFrames,
                           float gain);
};

}
}

#endif //VST_AB_SWITCH_ABSWITCHPROCESSOR_H

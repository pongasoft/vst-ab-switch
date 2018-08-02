#ifndef VST_AB_SWITCH_ABSWITCHPROCESSOR_H
#define VST_AB_SWITCH_ABSWITCHPROCESSOR_H

#include <public.sdk/source/vst/vstaudioeffect.h>
#include <pongasoft/VST/RT/RTProcessor.h>
#include "ABSwitchPlugin.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {
namespace ABSwitch {

/**
 * class ABSwitchProcessor, main processor for ABSwitch VST
 */
class ABSwitchProcessor : public RT::RTProcessor
{
public:
  ABSwitchProcessor();

  ~ABSwitchProcessor() override;

  // getRTState
  RTState *getRTState() override { return &fState; }

  /** Called at first after constructor */
  tresult PLUGIN_API initialize(FUnknown *context) override;

  /** Called at the end before destructor */
  tresult PLUGIN_API terminate() override;

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this Plug-in
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/) { return (IAudioProcessor *) new ABSwitchProcessor(); }

protected:
  /**
   * Processes inputs (step 2 always called after processing the parameters)
   */
  template<typename SampleType>
  tresult genericProcessInputs(ProcessData &data);

  // processInputs32Bits
  tresult processInputs32Bits(ProcessData &data) override { return genericProcessInputs<Sample32>(data); }

  // processInputs64Bits
  tresult processInputs64Bits(ProcessData &data) override { return genericProcessInputs<Sample64>(data); }

protected:
  /**
   * Handles inputs when cross fade needs to happen
   */
  template<typename SampleType>
  tresult processCrossFade(ProcessData &data);

  /**
   * Handles inputs when it is just a copy
   */
  template<typename SampleType>
  tresult processCopy(ProcessData &data);

private:
  ABSwitchParameters fParameters;
  ABSwitchRTState fState;
};

}
}
}

#endif //VST_AB_SWITCH_ABSWITCHPROCESSOR_H

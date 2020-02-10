#include <base/source/fstreamer.h>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>
#include <pongasoft/logging/logging.h>
#include <pongasoft/VST/Debug/ParamTable.h>
#include "version.h"
#include "jamba_version.h"

#include "ABSwitchProcessor.h"
#include "ABSwitchUtils.h"
#include "ABSwitchCIDs.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

using namespace RT;

/*
 * We assume that input A is indexed 0 and input B is indexed 1
 */
inline int mapSwitchStateToInput(ESwitchState switchState)
{
  return switchState == ESwitchState::kA ? 0 : 1;
}

///////////////////////////////////////////
// ABSwitchProcessor::ABSwitchProcessor
///////////////////////////////////////////
ABSwitchProcessor::ABSwitchProcessor() : RTProcessor(ABSwitchControllerUID),
                                         fParameters{},
                                         fState{fParameters}
{
  DLOG_F(INFO, "ABSwitchProcessor() - jamba: %s - plugin: v%s", JAMBA_GIT_VERSION_STR, FULL_VERSION_STR);
#ifndef NDEBUG
  DLOG_F(INFO, "Parameters ---> \n%s", Debug::ParamTable::from(fParameters).full().toString().c_str());
#endif
}

///////////////////////////////////////////
// ABSwitchProcessor::~ABSwitchProcessor
///////////////////////////////////////////
ABSwitchProcessor::~ABSwitchProcessor()
{
  DLOG_F(INFO, "~ABSwitchProcessor()");
}


///////////////////////////////////////////
// ABSwitchProcessor::initialize
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::initialize(FUnknown *context)
{
  DLOG_F(INFO, "ABSwitchProcessor::initialize()");

  tresult result = RTProcessor::initialize(context);
  if(result != kResultOk)
  {
    return result;
  }

  // 2 ins (A and B) => 1 out
  addAudioInput(STR16 ("Stereo In A"), SpeakerArr::kStereo);
  addAudioInput(STR16 ("Stereo In B"), SpeakerArr::kStereo);
  addAudioOutput(STR16 ("Stereo Out"), SpeakerArr::kStereo);

#ifndef NDEBUG
  using Key = Debug::ParamDisplay::Key;
  DLOG_F(INFO, "RT Save State - Version=%d --->\n%s",
         fParameters.getRTSaveStateOrder().fVersion,
         Debug::ParamTable::from(getRTState(), true).keys({Key::kID, Key::kTitle}).full().toString().c_str());
#endif

  return result;
}

///////////////////////////////////////////
// ABSwitchProcessor::terminate
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::terminate()
{
  DLOG_F(INFO, "ABSwitchProcessor::terminate()");

  return RTProcessor::terminate();
}


///////////////////////////////////////////
// ABSwitchProcessor::genericProcessInputs
///////////////////////////////////////////
template<typename SampleType>
tresult ABSwitchProcessor::genericProcessInputs(ProcessData &data)
{
  // 2. process inputs
  if(data.numInputs == 0 || data.numOutputs == 0)
  {
    // nothing to do
    return kResultOk;
  }

  tresult res;

  // case when we are switching between A & B and soften is on => need to cross fade
  // also note that we need more than 1 input in order to cross fade...
  if(fState.fSwitch.hasChanged() && *fState.fSoften && data.numInputs > 1)
    res = processCrossFade<SampleType>(data);
  else
    res = processCopy<SampleType>(data);


  // handle Audio On/Off LED light
  if(res == kResultOk)
  {
    AudioBusBuffers &stereoOutput = data.outputs[0];

    bool audioOn = !Utils::isSilent(stereoOutput);

    if(audioOn != fState.fAudioOn)
    {
      fState.fAudioOn.update(audioOn, data);
    }
  }

  return res;
}

///////////////////////////////////////////
// ABSwitchProcessor::processCopy
///////////////////////////////////////////
template<typename SampleType>
tresult ABSwitchProcessor::processCopy(ProcessData &data)
{
  // there is at least 1 input (data.numInputs > 0 at this point)
  int inputIndex = 0;

  // this is where the "magic" happens => determines which input we use (A or B)
  if(data.numInputs > 1)
    inputIndex = mapSwitchStateToInput(*fState.fSwitch);

  AudioBusBuffers &stereoInput = data.inputs[inputIndex];
  AudioBusBuffers &stereoOutput = data.outputs[0];

  return Utils::copy<SampleType>(stereoInput,
                                 stereoOutput,
                                 data.numSamples);
}

///////////////////////////////////////////
// ABSwitchProcessor::processCrossFade
///////////////////////////////////////////
template<typename SampleType>
tresult ABSwitchProcessor::processCrossFade(ProcessData &data)
{
  AudioBusBuffers &stereoOutput = data.outputs[0];

  AudioBusBuffers &stereoInput1 = data.inputs[mapSwitchStateToInput(fState.fSwitch.previous())];
  AudioBusBuffers &stereoInput2 = data.inputs[mapSwitchStateToInput(fState.fSwitch.value())];

  return Utils::linearCrossFade<SampleType>(stereoInput1,
                                            stereoInput2,
                                            stereoOutput,
                                            data.numSamples);
}

}
}
}
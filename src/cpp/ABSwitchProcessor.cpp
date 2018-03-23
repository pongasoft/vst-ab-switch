#include <base/source/fstreamer.h>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>

#include "ABSwitchProcessor.h"
#include "ABSwitchUtils.h"
#include "ABSwitchCIDs.h"
#include "logging/loguru.hpp"

namespace pongasoft {
namespace VST {

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
ABSwitchProcessor::ABSwitchProcessor() : AudioEffect(),
  fSwitchState{ESwitchState::kA},
  fPreviousSwitchState{fSwitchState},
  fSoften{true}
{
  setControllerClass(ABSwitchControllerUID);
  DLOG_F(INFO, "ABSwitchProcessor::ABSwitchProcessor()");
}

///////////////////////////////////////////
// ABSwitchProcessor::~ABSwitchProcessor
///////////////////////////////////////////
ABSwitchProcessor::~ABSwitchProcessor()
{
  DLOG_F(INFO, "ABSwitchProcessor::~ABSwitchProcessor()");
}


///////////////////////////////////////////
// ABSwitchProcessor::initialize
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::initialize(FUnknown *context)
{
  DLOG_F(INFO, "ABSwitchProcessor::initialize()");

  tresult result = AudioEffect::initialize(context);
  if(result != kResultOk)
  {
    return result;
  }

  // 2 ins (A and B) => 1 out
  addAudioInput(STR16 ("Stereo In A"), SpeakerArr::kStereo);
  addAudioInput(STR16 ("Stereo In B"), SpeakerArr::kStereo);
  addAudioOutput(STR16 ("Stereo Out"), SpeakerArr::kStereo);

  return result;
}

///////////////////////////////////////////
// ABSwitchProcessor::terminate
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::terminate()
{
  DLOG_F(INFO, "ABSwitchProcessor::terminate()");

  return AudioEffect::terminate();
}

///////////////////////////////////////////
// ABSwitchProcessor::setupProcessing
///////////////////////////////////////////
tresult ABSwitchProcessor::setupProcessing(ProcessSetup &setup)
{
  tresult result = AudioEffect::setupProcessing(setup);

  if(result != kResultOk)
    return result;

  DLOG_F(INFO,
         "ABSwitchProcessor::setupProcessing(processMode=%d, symbolicSampleSize=%d, maxSamplesPerBlock=%d, sampleRate=%f)",
         setup.processMode,
         setup.symbolicSampleSize,
         setup.maxSamplesPerBlock,
         setup.sampleRate);

  return result;
}

///////////////////////////////////////////
// ABSwitchProcessor::setActive
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::setActive(TBool state)
{
  DLOG_F(INFO, "ABSwitchProcessor::setActive(%s)", state ? "true" : "false");
  return AudioEffect::setActive(state);
}

///////////////////////////////////////////
// ABSwitchProcessor::process
///////////////////////////////////////////
tresult PLUGIN_API ABSwitchProcessor::process(ProcessData &data)
{
  // 1. process parameter changes
  if(data.inputParameterChanges != nullptr)
    processParameters(*data.inputParameterChanges);

  // 2. process inputs
  tresult res = processInputs(data);

  // 3. update the state
  fPreviousSwitchState = fSwitchState;

  return res;
}

///////////////////////////////////////////
// ABSwitchProcessor::processInputs
///////////////////////////////////////////
tresult ABSwitchProcessor::processInputs(ProcessData &data)
{
  // 2. process inputs
  if(data.numInputs == 0 || data.numOutputs == 0)
  {
    // nothing to do
    return kResultOk;
  }

  // case when we are switching between A & B and soften is on => need to cross fade
  // also note that we need more than 1 input in order to cross fade...
  if(fPreviousSwitchState != fSwitchState && fSoften && data.numInputs > 1)
  {
    return processCrossFade(data);
  }

  // there is at least 1 input (data.numInputs > 0 at this point)
  int inputIndex = 0;

  // this is where the "magic" happens => determines which input we use (A or B)
  if(data.numInputs > 1)
    inputIndex = mapSwitchStateToInput(fSwitchState);

  AudioBusBuffers &stereoInput = data.inputs[inputIndex];
  AudioBusBuffers &stereoOutput = data.outputs[0];

  //---get audio buffers----------------
  uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
  void **in = getChannelBuffersPointer(processSetup, stereoInput);
  void **out = getChannelBuffersPointer(processSetup, stereoOutput);

  // since we copy input to output, we end up with the same flags
  stereoOutput.silenceFlags = stereoInput.silenceFlags;

  for(int i = 0; i < stereoInput.numChannels; ++i)
  {
    // sanity check => we make sure there is enough output channels
    if(stereoOutput.numChannels >= i)
    {
      // no need to copy if input and output are the same...
      if(in[i] != out[i])
      {
        // simply copy the samples
        memcpy(out[i], in[i], sampleFramesSize);
      }
    }
  }

  // in the event there are more output channels than input channels, we simply silence them
  if(stereoOutput.numChannels > stereoInput.numChannels)
  {
    for(int i = stereoInput.numChannels; i < stereoOutput.numChannels; ++i)
    {
      memset(out[i], 0, sampleFramesSize);
      stereoOutput.silenceFlags |= static_cast<uint64>(1) << i;
    }
  }

  return kResultOk;
}

///////////////////////////////////////////
// ABSwitchProcessor::processCrossFade
///////////////////////////////////////////
tresult ABSwitchProcessor::processCrossFade(ProcessData &data)
{
  AudioBusBuffers &stereoOutput = data.outputs[0];

  AudioBusBuffers &stereoInput1 = data.inputs[mapSwitchStateToInput(fPreviousSwitchState)];
  AudioBusBuffers &stereoInput2 = data.inputs[mapSwitchStateToInput(fSwitchState)];

  // should be the same but making sure since linearCrossFade assumes they are
  int32 numChannels = std::min(std::min(stereoInput1.numChannels,
                                        stereoInput2.numChannels),
                               stereoOutput.numChannels);

  uint64 silenceFlags;

  if(data.symbolicSampleSize == kSample32)
  {
    silenceFlags = Utils::linearCrossFade<Sample32>(stereoInput1,
                                                    stereoInput2,
                                                    stereoOutput,
                                                    numChannels,
                                                    data.numSamples);
  } else
  {
    silenceFlags = Utils::linearCrossFade<Sample64>(stereoInput1,
                                                    stereoInput2,
                                                    stereoOutput,
                                                    numChannels,
                                                    data.numSamples);
  }

  stereoOutput.silenceFlags = silenceFlags;

  return kResultTrue;
}

///////////////////////////////////////////
// ABSwitchProcessor::canProcessSampleSize
//
// * Overridden so that we can declare we support 64bits
///////////////////////////////////////////
tresult ABSwitchProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
  if(symbolicSampleSize == kSample32)
    return kResultTrue;

  // we support double processing
  if(symbolicSampleSize == kSample64)
    return kResultTrue;

  return kResultFalse;
}

///////////////////////////////////////////
// ABSwitchProcessor::processParameters
///////////////////////////////////////////
void ABSwitchProcessor::processParameters(IParameterChanges &inputParameterChanges)
{
  int32 numParamsChanged = inputParameterChanges.getParameterCount();
  for(int i = 0; i < numParamsChanged; ++i)
  {
    IParamValueQueue *paramQueue = inputParameterChanges.getParameterData(i);
    if(paramQueue != nullptr)
    {
      ParamValue value;
      int32 sampleOffset;
      int32 numPoints = paramQueue->getPointCount();

      // we read the "last" point (ignoring multiple changes for now)
      if(paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultOk)
      {
        switch(paramQueue->getParameterId())
        {
          case kAudioSwitch:
            fSwitchState = ESwitchStateFromValue(value);
            DLOG_F(INFO, "ABSwitchProcessor::processParameters => fSwitchState=%i", fSwitchState);
            break;

          case kSoftenSwitch:
            fSoften = value == 1.0;
            DLOG_F(INFO, "ABSwitchProcessor::processParameters => fSoften=%s", fSoften ? "true" : "false");
            break;

          default:
            // shouldn't happen?
            break;
        }
      }
    }
  }
}

///////////////////////////////////
// ABSwitchProcessor::setState
///////////////////////////////////
tresult ABSwitchProcessor::setState(IBStream *state)
{
  if(state == nullptr)
    return kResultFalse;

  DLOG_F(INFO, "ABSwitchProcessor::setState()");

  IBStreamer streamer(state, kLittleEndian);

  // ABSwitchParamID::kAudioSwitch
  float savedParam1 = 0.f;
  if(!streamer.readFloat(savedParam1))
    return kResultFalse;

  fSwitchState = ESwitchStateFromValue(savedParam1);

  DLOG_F(INFO, "ABSwitchProcessor::setState => fSwitchState=%s", fSwitchState == ESwitchState::kA ? "kA" : "kB");

  return kResultOk;
}

///////////////////////////////////
// ABSwitchProcessor::getState
///////////////////////////////////
tresult ABSwitchProcessor::getState(IBStream *state)
{
  if(state == nullptr)
    return kResultFalse;

  DLOG_F(INFO, "ABSwitchProcessor::getState()");

  IBStreamer streamer(state, kLittleEndian);
  streamer.writeFloat(fSwitchState == ESwitchState::kA ? 0 : 1.0f);
  return kResultOk;
}


}
}
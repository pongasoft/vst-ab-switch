#include "ABSwitchProcessor.h"
#include "ABSwitchProcess.h"
#include "ABSwitchCIDs.h"
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>

namespace pongasoft {
namespace VST {

ABSwitchProcessor::ABSwitchProcessor() : AudioEffect()
{
  setControllerClass(ABSwitchControllerUID);
}

ABSwitchProcessor::~ABSwitchProcessor() = default;

tresult PLUGIN_API ABSwitchProcessor::initialize(FUnknown *context)
{
  tresult result = AudioEffect::initialize(context);
  if(result != kResultOk)
  {
    return result;
  }

  //---create Audio In/Out buses------
  addAudioInput(STR16 ("Stereo In"), SpeakerArr::kStereo);
  addAudioOutput(STR16 ("Stereo Out"), SpeakerArr::kStereo);

  return result;
}

tresult PLUGIN_API ABSwitchProcessor::terminate()
{
  return AudioEffect::terminate();
}

tresult PLUGIN_API ABSwitchProcessor::setActive(TBool state)
{
  return AudioEffect::setActive(state);
}

/**
 * This is where the processing actually happens
 */
tresult PLUGIN_API ABSwitchProcessor::process(ProcessData &data)
{
  if(data.numInputs == 0 || data.numOutputs == 0)
  {
    // nothing to do
    return kResultOk;
  }

  AudioBusBuffers &stereoInput = data.inputs[0];
  AudioBusBuffers &stereoOutput = data.outputs[0];

  // (simplification) we suppose in this example that we have the same input channel count than the output
  int32 numChannels = stereoInput.numChannels;

  //---get audio buffers----------------
  uint32 sampleFramesSize = getSampleFramesSizeInBytes(processSetup, data.numSamples);
  void **in = getChannelBuffersPointer(processSetup, stereoInput);
  void **out = getChannelBuffersPointer(processSetup, stereoOutput);

  //---check if silence---------------
  // normally we have to check each channel (simplification)
  if(stereoInput.silenceFlags != 0)
  {
    // mark output silence too
    stereoOutput.silenceFlags = stereoInput.silenceFlags;

    // the Plug-in has to be sure that if it sets the flags silence that the output buffer are clear
    for(int32 i = 0; i < numChannels; i++)
    {
      // do not need to be cleared if the buffers are the same (in this case input buffer are already cleared by the host)
      if(in[i] != out[i])
      {
        memset(out[i], 0, sampleFramesSize);
      }
    }

    // nothing to do at this point
    return kResultOk;
  }

  // mark our outputs has not silent
  stereoOutput.silenceFlags = 0;

  //---apply gain factor----------
  float gain = 0.5f;

  if(data.symbolicSampleSize == kSample32)
    processAudio<Sample32>((Sample32 **) in, (Sample32 **) out, numChannels,
                           data.numSamples, gain);
  else
    processAudio<Sample64>((Sample64 **) in, (Sample64 **) out, numChannels,
                           data.numSamples, gain);

  return kResultOk;
}

/** Overridden so that we can declare we support 64bits */
tresult ABSwitchProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
  if (symbolicSampleSize == kSample32)
    return kResultTrue;

  // we support double processing
  if (symbolicSampleSize == kSample64)
    return kResultTrue;

  return kResultFalse;
}


}
}
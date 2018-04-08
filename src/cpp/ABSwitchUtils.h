#ifndef VST_AB_SWITCH_ABSWITUTILS_H
#define VST_AB_SWITCH_ABSWITUTILS_H

#include <pluginterfaces/vst/ivstaudioprocessor.h>

namespace pongasoft {
namespace VST {

namespace Utils {

// defines the threshold of silence
constexpr Sample32 Sample32SilentThreshold = ((Sample32)2.0e-8);
constexpr Sample64 Sample64SilentThreshold = ((Sample64)2.0e-8);

// check if sample is silent (lower than threshold) Sample32 version
inline bool isSilent(Sample32 value)
{
  if(value < 0)
    value = -value;
  return value <= Sample32SilentThreshold;
}

// check if sample is silent (lower than threshold) Sample64 version
inline bool isSilent(Sample64 value)
{
  if(value < 0)
    value = -value;
  return value <= Sample64SilentThreshold;
}

// returns true if the buffer is silent (meaning all channels are silent => set to 1)
inline bool isSilent(AudioBusBuffers &buffer)
{
  return buffer.silenceFlags == (static_cast<uint64>(1) << buffer.numChannels) - 1;
}

/**
 * Use of template to retrieve the proper buffer
 */
template<typename SampleType>
inline SampleType** getBuffer(AudioBusBuffers &buffer);

// specialization for Sample32
template<>
inline Sample32** getBuffer(AudioBusBuffers &buffer) { return buffer.channelBuffers32; }

// specialization for Sample64
template<>
inline Sample64** getBuffer(AudioBusBuffers &buffer) { return buffer.channelBuffers64; }

/**
 * Cross fades between in1 and in2 in a linear fashion [in1 * (1-t) + in2 * t for 0 <= t <= 1]
 */
template<typename SampleType>
tresult linearCrossFade(AudioBusBuffers &audioBufferIn1,
                        AudioBusBuffers &audioBufferIn2,
                        AudioBusBuffers &audioBufferOut,
                        int32 numSamples)
{
  audioBufferOut.silenceFlags = 0;

  int32 numChannels = std::min(std::min(audioBufferIn1.numChannels,
                                        audioBufferIn2.numChannels),
                               audioBufferOut.numChannels);

  // making sure we don't divide by 0
  if(numSamples <= 1)
    return kInvalidArgument;

  SampleType** in1 = getBuffer<SampleType>(audioBufferIn1);
  SampleType** in2 = getBuffer<SampleType>(audioBufferIn2);
  SampleType** out = getBuffer<SampleType>(audioBufferOut);

  double delta = 1.0 / (numSamples - 1);

  for(int32 i = 0; i < numChannels; i++)
  {
    int32 samples = numSamples;
    auto ptrIn1 = in1[i];
    auto ptrIn2 = in2[i];
    auto ptrOut = out[i];
    bool silent = true;

    double t = 0;

    while(--samples >= 0)
    {
      auto sample1 = *ptrIn1++;
      auto sample2 = *ptrIn2++;

      // cross fade
      SampleType tmp = (sample1) * (1.0 - t) + (sample2) * t;
      (*ptrOut++) = tmp;
      t += delta;

      if(silent && !isSilent(tmp))
        silent = false;
    }

    if(silent)
      audioBufferOut.silenceFlags |= static_cast<uint64>(1) << i;
  }

  return kResultOk;
}

/**
 * copy input buffer into output buffer (and sets the silence flag appropriately)
 */
template<typename SampleType>
tresult copy(AudioBusBuffers &audioBufferIn,
             AudioBusBuffers &audioBufferOut,
             int32 numSamples)
{
  audioBufferOut.silenceFlags = 0;

  int32 numChannels = std::min(audioBufferIn.numChannels, audioBufferOut.numChannels);

  SampleType** in = getBuffer<SampleType>(audioBufferIn);
  SampleType** out = getBuffer<SampleType>(audioBufferOut);

  for(int32 i = 0; i < numChannels; i++)
  {
    int32 samples = numSamples;

    auto ptrIn = in[i];
    auto ptrOut = out[i];
    bool silent = true;

    while(--samples >= 0)
    {
      auto sample = *ptrIn++;

      (*ptrOut++) = sample;

      if(silent && !isSilent(sample))
        silent = false;
    }

    if(silent)
      audioBufferOut.silenceFlags |= static_cast<uint64>(1) << i;
  }

  return kResultOk;
}


}
}
}


#endif //VST_AB_SWITCH_ABSWITUTILS_H

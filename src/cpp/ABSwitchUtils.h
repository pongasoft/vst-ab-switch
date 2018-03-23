#ifndef VST_AB_SWITCH_ABSWITUTILS_H
#define VST_AB_SWITCH_ABSWITUTILS_H

namespace pongasoft {
namespace VST {

namespace Utils {

constexpr Sample32 Sample32SilentThreshold = ((Sample32)2.0e-8);
constexpr Sample64 Sample64SilentThreshold = ((Sample64)2.0e-8);

inline bool isSilent(Sample32 value)
{
  if(value < 0)
    value = -value;
  return value <= Sample32SilentThreshold;
}

inline bool isSilent(Sample64 value)
{
  if(value < 0)
    value = -value;
  return value <= Sample64SilentThreshold;
}


/**
 * Cross fades between in1 and in2 in a linear fashion [in1 * (1-t) + in2 * t for 0 <= t <= 1]
 * @return the silence flags as defined by the VST SDK. a bit set to 0 means not silent
 */
template<typename SampleType>
uint64 linearCrossFade(SampleType **in1,
                       SampleType **in2,
                       SampleType **out,
                       int32 numChannels,
                       int32 numSamples)
{
  uint64 silenceFlags = 0;

  // making sure we don't divide by 0
  if(numSamples < 1)
    return silenceFlags;

  double delta = 1.0 / (numSamples - 1);

  for(int32 i = 0; i < numChannels; i++)
  {
    int32 samples = numSamples;
    auto ptrIn1 = in1[i];
    auto ptrIn2 = in2[i];
    auto ptrOut = out[i];
    bool silent = true;

    double t = 0;

    SampleType tmp;
    while(--samples >= 0)
    {
      auto sample1 = *ptrIn1++;
      auto sample2 = *ptrIn2++;

      // cross fade
      tmp = (sample1) * (1.0 - t) + (sample2) * t;
      (*ptrOut++) = tmp;
      t += delta;

      if(!isSilent(tmp))
        silent = false;
    }

    if(silent)
      silenceFlags |= static_cast<uint64>(1) << i;
  }

  return silenceFlags;
}

}
}
}


#endif //VST_AB_SWITCH_ABSWITUTILS_H

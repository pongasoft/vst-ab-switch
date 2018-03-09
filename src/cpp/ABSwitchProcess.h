#ifndef VST_AB_SWITCH_ABSWITCHPROCESS_H
#define VST_AB_SWITCH_ABSWITCHPROCESS_H

#include "ABSwitchProcessor.h"

namespace pongasoft {
namespace VST {

template<typename SampleType>
SampleType ABSwitchProcessor::processAudio(SampleType **in,
                                           SampleType **out,
                                           int32 numChannels,
                                           int32 sampleFrames,
                                           float gain)
{
  SampleType max = 0;

  for(int32 i = 0; i < numChannels; i++)
  {
    int32 samples = sampleFrames;
    auto ptrIn = in[i];
    auto ptrOut = out[i];
    SampleType tmp;
    while(--samples >= 0)
    {
      // apply gain
      tmp = (*ptrIn++) * gain;
      (*ptrOut++) = tmp;

      if(tmp < 0)
        tmp = -tmp;

      if(tmp > max)
      {
        max = tmp;
      }
    }
  }
  return max;
}

}
}


#endif //VST_AB_SWITCH_ABSWITCHPROCESS_H

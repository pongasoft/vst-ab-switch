#include "ABSwitchPlugin.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

//------------------------------------------------------------------------
// ABSwitchParameters::readRTState
//------------------------------------------------------------------------
tresult ABSwitchParameters::readRTState(IBStreamer &iStreamer, NormalizedState *oNormalizedState) const
{
  DLOG_F(INFO, "ABSwitchParameters::readRTState");

  // ABSwitchParamID::kAudioSwitch
  float savedParam1;
  if(!iStreamer.readFloat(savedParam1))
    savedParam1 = static_cast<float>(fSwitchParam->fDefaultValue);
  oNormalizedState->set(0, fSwitchParam->normalize(fSwitchParam->denormalize(savedParam1)));

  // ABSwitchParamID::kSoftenSwitch
  bool savedParam2;
  if(!iStreamer.readBool(savedParam2))
    savedParam2 = fSoftenParam->getDefaultValue();
  oNormalizedState->set(1, fSoftenParam->normalize(savedParam2));

  return kResultOk;
}

//------------------------------------------------------------------------
// ABSwitchParameters::writeRTState
//------------------------------------------------------------------------
tresult ABSwitchParameters::writeRTState(NormalizedState const *iNormalizedState, IBStreamer &oStreamer) const
{
  DLOG_F(INFO, "ABSwitchParameters::writeRTState");

  oStreamer.writeFloat(fSwitchParam->denormalize(iNormalizedState->fValues[0]) == ESwitchState::kA ? 0 : 1.0f);
  oStreamer.writeBool(fSoftenParam->denormalize(iNormalizedState->fValues[1]));

  return kResultOk;
}


}
}
}
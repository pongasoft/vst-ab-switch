#include "ABSwitchPlugin.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

//------------------------------------------------------------------------
// ABSwitchParameters::readRTState
//------------------------------------------------------------------------
std::unique_ptr<NormalizedState> ABSwitchParameters::readRTState(IBStreamer &iStreamer) const
{
  DLOG_F(INFO, "ABSwitchParameters::readRTState");

  auto state = newRTState();

  // ABSwitchParamID::kAudioSwitch
  float savedParam1;
  if(!iStreamer.readFloat(savedParam1))
    savedParam1 = static_cast<float>(fSwitchParam->fDefaultValue);
  state->set(0, fSwitchParam->normalize(fSwitchParam->denormalize(savedParam1)));

  // ABSwitchParamID::kSoftenSwitch
  bool savedParam2;
  if(!iStreamer.readBool(savedParam2))
    savedParam2 = fSoftenParam->getDefaultValue();
  state->set(1, fSoftenParam->normalize(savedParam2));

  return state;
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
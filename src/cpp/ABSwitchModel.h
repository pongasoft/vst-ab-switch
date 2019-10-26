#pragma once

#include <pluginterfaces/vst/vsttypes.h>
#include <pluginterfaces/base/ustring.h>
#include <pongasoft/VST/ParamConverters.h>

namespace pongasoft {
namespace VST {
namespace ABSwitch {

using namespace Steinberg;
using namespace Steinberg::Vst;

// ESwitchState
enum class ESwitchState
{
  kA, kB
};

// SwitchStateParamConverter
class SwitchStateParamConverter : public IParamConverter<ESwitchState>
{
public:
  int32 getStepCount() const override { return fBooleanParamConverter.getStepCount(); }

  inline ParamValue normalize(ESwitchState const &iValue) const override
  {
    return fBooleanParamConverter.normalize(iValue == ESwitchState::kB);
  }

  inline ESwitchState denormalize(ParamValue iNormalizedValue) const override
  {
    return fBooleanParamConverter.denormalize(iNormalizedValue) ? ESwitchState::kB : ESwitchState::kA;
  }

  inline void toString(ParamType const &iValue, String128 oString, int32 iPrecision) const override
  {
    fBooleanParamConverter.toString(iValue == ESwitchState::kB, oString, iPrecision);
  }

  BooleanParamConverter fBooleanParamConverter{STR16("A"), STR16("B")};
};

}
}
}
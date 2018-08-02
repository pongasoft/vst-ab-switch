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
class SwitchStateParamConverter
{
public:
  using ParamType = ESwitchState;

  inline static ParamValue normalize(ESwitchState const &iValue)
  {
    return BooleanParamConverter::normalize(iValue == ESwitchState::kB);
  }

  inline static ESwitchState denormalize(ParamValue iNormalizedValue)
  {
    return BooleanParamConverter::denormalize(iNormalizedValue) ? ESwitchState::kB : ESwitchState::kA;
  }

  inline static void toString(ParamType const &iValue, String128 oString, int32 iPrecision)
  {
    Steinberg::UString wrapper(oString, str16BufferSize(String128));
    if(iValue == ESwitchState::kA)
      wrapper.assign(STR16("A"));
    else
      wrapper.assign(STR16("B"));
  }
};

}
}
}
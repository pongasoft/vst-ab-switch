#pragma once

#include <pongasoft/VST/Parameters.h>
#include <pongasoft/VST/RT/RTState.h>
#include <pongasoft/VST/GUI/GUIState.h>
#include <pongasoft/VST/GUI/Params/GUIParamSerializers.h>

#include "ABSwitchCIDs.h"
#include "ABSwitchModel.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

using namespace GUI;

using UTF8StringSerializer = UTF8StringParamSerializer<128>;

class ABSwitchParameters : public Parameters
{
public:
  ABSwitchParameters() : Parameters()
  {
    // the toggle that switches between A and B input
    fSwitchParam =
      vst<SwitchStateParamConverter>(ABSwitchParamID::kAudioSwitch, STR16 ("Audio Switch"))
        .stepCount(1)
        .defaultValue(ESwitchState::kA)
        .shortTitle(STR16 ("Switch"))
        .add();

    // the toggle that enables/disables cross fading for softening the transition between A and B
    fSoftenParam =
      vst<BooleanParamConverter>(ABSwitchParamID::kSoftenSwitch, STR16 ("Soften"))
        .defaultValue(true)
        .shortTitle(STR16 ("Soft"))
        .add();

    // the LED light when there is sound or not
    fAudioOnParam =
      vst<BooleanParamConverter>(ABSwitchParamID::kAudioOn, STR16 ("Audio On"))
        .flags(ParameterInfo::kIsReadOnly)
        .transient()
        .add();

    // the free form text for input label A (saved in state but not tied to a vst parameter since it's a string)
    fLabelAParam =
      ser<UTF8StringSerializer>(ABSwitchParamID::kAudioInputLabelA, STR16("Label A"))
        .uiOnly()
        .defaultValue("Input Label A")
        .add();

    // the free form text for input label B (saved in state but not tied to a vst parameter since it's a string)
    fLabelBParam =
      ser<UTF8StringSerializer>(ABSwitchParamID::kAudioInputLabelB, STR16("Label B"))
        .uiOnly()
        .defaultValue("Input Label B")
        .add();

    setRTSaveStateOrder(-1, fSwitchParam, fSoftenParam); // ignore version (for backward compatibility)
    setGUISaveStateOrder(-1, fLabelAParam, fLabelBParam); // ignore version (for backward compatibility)
  }

  VstParam<ESwitchState> fSwitchParam;
  VstParam<bool> fSoftenParam;

  // transient
  VstParam<bool> fAudioOnParam;

  // Non vst params
  SerParam<UTF8String> fLabelAParam;
  SerParam<UTF8String> fLabelBParam;

protected:
  /**
   * Overridden to handle backward compatibility state saving. */
  std::unique_ptr<NormalizedState> readRTState(IBStreamer &iStreamer) const override;

  /**
   * Overridden to handle backward compatibility state saving. */
  tresult writeRTState(NormalizedState const *iNormalizedState, IBStreamer &oStreamer) const override;
};

using namespace RT;

class ABSwitchRTState : public RTState
{
public:
  explicit ABSwitchRTState(ABSwitchParameters const &iParams) :
    RTState(iParams),
    fSwitch{add(iParams.fSwitchParam)},
    fSoften{add(iParams.fSoftenParam)},
    fAudioOn{add(iParams.fAudioOnParam)}
  {}

public:
  RTVstParam<ESwitchState> fSwitch;
  RTVstParam<bool> fSoften;

  // transient
  RTVstParam<bool> fAudioOn;
};


class ABSwitchGUIState : public GUIPluginState<ABSwitchParameters>
{
public:
  explicit ABSwitchGUIState(ABSwitchParameters const &iParams) :
    GUIPluginState(iParams),
    fLabelA{add(iParams.fLabelAParam)},
    fLabelB{add(iParams.fLabelBParam)}
  {};

public:
  GUISerParam<UTF8String> fLabelA;
  GUISerParam<UTF8String> fLabelB;
};
}
}
}

#pragma once

#include <pongasoft/VST/Parameters.h>
#include <pongasoft/VST/RT/RTState.h>
#include <pongasoft/VST/GUI/GUIState.h>
#include <pongasoft/VST/GUI/Params/GUIParamSerializers.h>
#include <pongasoft/VST/Debug/ParamLine.h>

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
  VstParam<ESwitchState> fSwitchParam;
  VstParam<bool> fSoftenParam;

  // transient
  VstParam<bool> fAudioOnParam;

  // Non vst params
  JmbParam<UTF8String> fLabelAParam;
  JmbParam<UTF8String> fLabelBParam;

public:
  ABSwitchParameters() : Parameters()
  {
    // the toggle that switches between A and B input
    fSwitchParam =
      vst<SwitchStateParamConverter>(ABSwitchParamID::kAudioSwitch, STR16 ("Audio Switch"))
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
      jmb<UTF8StringSerializer>(ABSwitchParamID::kAudioInputLabelA, STR16("Label A"))
        .guiOwned()
        .defaultValue("Input Label A")
        .add();

    // the free form text for input label B (saved in state but not tied to a vst parameter since it's a string)
    fLabelBParam =
      jmb<UTF8StringSerializer>(ABSwitchParamID::kAudioInputLabelB, STR16("Label B"))
        .guiOwned()
        .defaultValue("Input Label B")
        .add();

    setRTSaveStateOrder(-1, fSwitchParam, fSoftenParam); // ignore version (for backward compatibility)
    setGUISaveStateOrder(-1, fLabelAParam, fLabelBParam); // ignore version (for backward compatibility)
  }

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
  RTVstParam<ESwitchState> fSwitch;
  RTVstParam<bool> fSoften;

  // transient
  RTVstParam<bool> fAudioOn;

public:
  explicit ABSwitchRTState(ABSwitchParameters const &iParams) :
    RTState(iParams),
    fSwitch{add(iParams.fSwitchParam)},
    fSoften{add(iParams.fSoftenParam)},
    fAudioOn{add(iParams.fAudioOnParam)}
  {}

#ifndef NDEBUG
protected:
  // afterReadNewState
  void afterReadNewState(NormalizedState *iState) override
  {
    DLOG_F(INFO, "RTState::read - %s", Debug::ParamLine::from(this, true).toString(*iState).c_str());
    //Debug::ParamTable::from(this, true).showCellSeparation().print(*iState, "RTState::read ---> ");
  }

  // beforeWriteNewState
  void beforeWriteNewState(NormalizedState *iState) override
  {
    DLOG_F(INFO, "RTState::write - %s", Debug::ParamLine::from(this, true).toString(*iState).c_str());
    //Debug::ParamTable::from(this, true).showCellSeparation().print(*iState, "RTState::write ---> ");
  }
#endif

};


class ABSwitchGUIState : public GUIPluginState<ABSwitchParameters>
{
public:
  GUIJmbParam<UTF8String> fLabelA;
  GUIJmbParam<UTF8String> fLabelB;

public:
  explicit ABSwitchGUIState(ABSwitchParameters const &iParams) :
    GUIPluginState(iParams),
    fLabelA{add(iParams.fLabelAParam)},
    fLabelB{add(iParams.fLabelBParam)}
  {};

#ifndef NDEBUG
protected:
  // readGUIState
  tresult readGUIState(IBStreamer &iStreamer) override
  {
    tresult res = GUIState::readGUIState(iStreamer);
    if(res == kResultOk)
    {
      DLOG_F(INFO, "GUIState::read - %s", Debug::ParamLine::from(this, true).toString().c_str());
      //Debug::ParamTable::from(this, true).showCellSeparation().print("GUIState::read ---> ");
    }
    return res;
  }

  // writeGUIState
  tresult writeGUIState(IBStreamer &oStreamer) const override
  {
    tresult res = GUIState::writeGUIState(oStreamer);
    if(res == kResultOk)
    {
      DLOG_F(INFO, "GUIState::write - %s", Debug::ParamLine::from(this, true).toString().c_str());
      //Debug::ParamTable::from(this, true).showCellSeparation().print("GUIState::write ---> ");
    }
    return res;
  }
#endif
};
}
}
}

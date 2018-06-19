#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include <base/source/fstreamer.h>
#include "logging/loguru.hpp"
#include "ABSwitchController.h"
#include "ABSwitchCIDs.h"

namespace pongasoft {
namespace VST {

///////////////////////////////////////////
// ABSwitchController::ABSwitchController
///////////////////////////////////////////
ABSwitchController::ABSwitchController() : EditController(),
  fXmlFile("ABSwitch.uidesc"),
  fInputLabelA{"Input Label A"},
  fInputLabelB{"Input Label B"}
{
  DLOG_F(INFO, "ABSwitchController::ABSwitchController()");
}

///////////////////////////////////////////
// ABSwitchController::~ABSwitchController
///////////////////////////////////////////
ABSwitchController::~ABSwitchController()
{
  DLOG_F(INFO, "ABSwitchController::~ABSwitchController()");
}

///////////////////////////////////////////
// ABSwitchController::initialize
///////////////////////////////////////////
tresult ABSwitchController::initialize(FUnknown *context)
{
  DLOG_F(INFO, "ABSwitchController::initialize()");

  tresult result = EditController::initialize(context);
  if(result != kResultOk)
  {
    return result;
  }

  // the toggle that switches between A and B input
  parameters.addParameter(STR16 ("Audio Switch"), // title
                          nullptr, // units
                          1, // stepCount => 1 means toggle
                          0, // defaultNormalizedValue => we start with A (0)
                          Vst::ParameterInfo::kCanAutomate, // flags
                          ABSwitchParamID::kAudioSwitch, // tag
                          kRootUnitId, // unitID => not using units at this stage
                          STR16 ("Switch")); // shortTitle

  // the toggle that enables/disables cross fading for softening the transition between A and B
  parameters.addParameter(STR16 ("Soften"), // title
                          nullptr, // units
                          1, // stepCount => 1 means toggle
                          1, // defaultNormalizedValue => soften on by default
                          Vst::ParameterInfo::kCanAutomate, // flags
                          ABSwitchParamID::kSoftenSwitch, // tag
                          kRootUnitId, // unitID => not using units at this stage
                          STR16 ("Soft")); // shortTitle

  // the LED light when there is sound or not
  parameters.addParameter(STR16 ("Audio On"), // title
                          nullptr, // units
                          1, // stepCount => 1 means toggle
                          0, // defaultNormalizedValue => we start with no sound => 0
                          ParameterInfo::kIsReadOnly, // flags
                          ABSwitchParamID::kAudioOn); // tag

  return result;
}

///////////////////////////////////////////
// ABSwitchController::terminate
///////////////////////////////////////////
tresult ABSwitchController::terminate()
{
  return EditController::terminate();
}

///////////////////////////////////////////
// ABSwitchController::createView
///////////////////////////////////////////
IPlugView *ABSwitchController::createView(const char *name)
{
  if(name && strcmp(name, ViewType::kEditor) == 0)
  {
    return new VSTGUI::VST3Editor(this, "view", fXmlFile);
  }
  return nullptr;
}

///////////////////////////////////////////
// ABSwitchController::verifyView
///////////////////////////////////////////
CView *ABSwitchController::verifyView(CView *view,
                                      const UIAttributes &attributes,
                                      const IUIDescription * /*description*/,
                                      VST3Editor * /*editor*/)
{
  DLOG_F(INFO, "ABSwitchController::verifyView()");

  auto te = dynamic_cast<CTextEdit *>(view);
  if(te != nullptr)
  {
    switch(te->getTag())
    {
      case kAudioInputLabelA:
        fInputLabelA.assignTextEdit(te);
        break;

      case kAudioInputLabelB:
        fInputLabelB.assignTextEdit(te);
        break;

      default:
        // nothing to do in this case
        break;
    }
  }

  return view;
}

///////////////////////////////////////////
// ABSwitchController::setComponentState
///////////////////////////////////////////
tresult ABSwitchController::setComponentState(IBStream *state)
{
  // we receive the current state of the component (processor part)
  if(state == nullptr)
    return kResultFalse;

  // using helper to read the stream
  IBStreamer streamer(state, kLittleEndian);

  // ABSwitchParamID::kAudioSwitch
  float savedParamAudioSwitch = 0.f;
  if(!streamer.readFloat(savedParamAudioSwitch))
    savedParamAudioSwitch = 0;
  setParamNormalized(ABSwitchParamID::kAudioSwitch, savedParamAudioSwitch);

  // ABSwitchParamID::kSoftenSwitch
  bool savedParamSoftenSwitch = true;
  if(!streamer.readBool(savedParamSoftenSwitch))
    savedParamSoftenSwitch = true;
  setParamNormalized(ABSwitchParamID::kSoftenSwitch, savedParamSoftenSwitch);

  DLOG_F(INFO, "ABSwitchController::setComponentState => kAudioSwitch=%s, kSoftenSwitch=%s",
         savedParamAudioSwitch == 0 ? "kA" : "kB",
         savedParamSoftenSwitch ? "true" : "false");

  return kResultOk;
}

///////////////////////////////////
// ABSwitchController::setState
///////////////////////////////////
tresult ABSwitchController::setState(IBStream *state)
{
  if(state == nullptr)
    return kResultFalse;

  DLOG_F(INFO, "ABSwitchController::setState()");

  IBStreamer streamer(state, kLittleEndian);

  char8 str[128];
  streamer.readString8(str, 128);
  UTF8String utfStrA{str};
  fInputLabelA.setText(utfStrA);

  streamer.readString8(str, 128);
  UTF8String utfStrB{str};
  fInputLabelB.setText(utfStrB);

  return kResultOk;
}

///////////////////////////////////
// ABSwitchController::getState
///////////////////////////////////
tresult ABSwitchController::getState(IBStream *state)
{
  if(state == nullptr)
    return kResultFalse;

  DLOG_F(INFO, "ABSwitchController::getState()");

  IBStreamer streamer(state, kLittleEndian);
  streamer.writeString8(fInputLabelA.getText(), true);
  streamer.writeString8(fInputLabelB.getText(), true);
  return kResultOk;
}


}
}
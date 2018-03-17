#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include <base/source/fstreamer.h>
#include "ABSwitchController.h"
#include "ABSwitchCIDs.h"

namespace pongasoft {
namespace VST {

ABSwitchController::ABSwitchController() : EditController(),
  fXmlFile("ABSwitch.uidesc")
{

}

/**
 * Nothing to do in destructor
 */
ABSwitchController::~ABSwitchController() = default;

/**
 * Called to initialized the controller
 */
tresult ABSwitchController::initialize(FUnknown *context)
{
  tresult result = EditController::initialize(context);
  if(result != kResultOk)
  {
    return result;
  }

  // the toggle that switches between A and B input
  parameters.addParameter(STR16 ("Audio Switch"), // title
                          STR16 ("A/B"), // units
                          1, // stepCount => 1 means toggle
                          0, // defaultNormalizedValue => we start with A (0)
                          Vst::ParameterInfo::kCanAutomate, // flags
                          ABSwitchParamID::kAudioSwitch, // tag
                          0, // unitID => not using units at this stage
                          STR16 ("Switch")); // shortTitle

  return result;
}

/**
 * Called to terminate the controller
 */
tresult ABSwitchController::terminate()
{
  return EditController::terminate();
}

/**
 * Creates the view attached to this controller
 */
IPlugView *ABSwitchController::createView(const char *name)
{
  if(name && strcmp(name, ViewType::kEditor) == 0)
  {
    return new VSTGUI::VST3Editor(this, "view", fXmlFile);
  }
  return nullptr;
}

/**
 * Sets the component state (after setting the processor) or after restore */
tresult ABSwitchController::setComponentState(IBStream *state)
{
  // we receive the current state of the component (processor part)
  if(state == nullptr)
    return kResultFalse;

  // using helper to read the stream
  IBStreamer streamer(state, kLittleEndian);

  // ABSwitchParamID::kAudioSwitch
  float savedParam1 = 0.f;
  if(!streamer.readFloat(savedParam1))
    return kResultFalse;
  setParamNormalized(ABSwitchParamID::kAudioSwitch, savedParam1);

  return kResultOk;
}

}
}
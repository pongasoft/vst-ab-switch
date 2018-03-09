#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include "ABSwitchController.h"

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

  // further init goes here

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

}
}
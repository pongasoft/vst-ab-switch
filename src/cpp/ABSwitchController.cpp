#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include <base/source/fstreamer.h>
#include <pongasoft/logging/logging.h>
#include <pongasoft/VST/Debug/ParamTable.h>
#include "ABSwitchController.h"
#include "ABSwitchCIDs.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

//------------------------------------------------------------------------
// ABSwitchController::ABSwitchController
//------------------------------------------------------------------------
ABSwitchController::ABSwitchController() : GUIController("ABSwitch.uidesc"),
                                           fParameters{},
                                           fState{fParameters}
{
  DLOG_F(INFO, "ABSwitchController::ABSwitchController()");
}

//------------------------------------------------------------------------
// ABSwitchController::~ABSwitchController
//------------------------------------------------------------------------
ABSwitchController::~ABSwitchController()
{
  DLOG_F(INFO, "ABSwitchController::~ABSwitchController()");
}

//------------------------------------------------------------------------
// ABSwitchController::initialize
//------------------------------------------------------------------------
tresult ABSwitchController::initialize(FUnknown *context)
{
  tresult res = GUIController::initialize(context);

  //------------------------------------------------------------------------
  // In debug mode this code displays the order in which the GUI parameters
  // will be saved
  //------------------------------------------------------------------------
#ifndef NDEBUG
  if(res == kResultOk)
  {
    using Key = Debug::ParamDisplay::Key;
    DLOG_F(INFO, "GUI Save State - Version=%d --->\n%s",
           fParameters.getGUISaveStateOrder().fVersion,
           Debug::ParamTable::from(getGUIState(), true).keys({Key::kID, Key::kTitle}).full().toString().c_str());
  }
#endif

  return res;
}

}
}
}
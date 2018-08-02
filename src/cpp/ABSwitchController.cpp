#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include <base/source/fstreamer.h>
#include <pongasoft/logging/logging.h>
#include "ABSwitchController.h"
#include "ABSwitchCIDs.h"

namespace pongasoft {
namespace VST {
namespace ABSwitch {

///////////////////////////////////////////
// ABSwitchController::ABSwitchController
///////////////////////////////////////////
ABSwitchController::ABSwitchController() : GUIController("ABSwitch.uidesc"),
                                           fParameters{},
                                           fState{fParameters}
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

}
}
}
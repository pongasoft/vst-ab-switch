#ifndef VST_AB_SWITCH_ABSWITCHCONTROLLER_H
#define VST_AB_SWITCH_ABSWITCHCONTROLLER_H

#include <pongasoft/VST/GUI/GUIController.h>
#include "StringTextEdit.h"
#include "ABSwitchPlugin.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {
namespace ABSwitch {

/**
 * Represents the controller part of the plugin. Manages the UI.
 */
class ABSwitchController : public GUI::GUIController
{
public:
  ABSwitchController();

  ~ABSwitchController() override;

  // getGUIState
  GUIState *getGUIState() override {return &fState; };

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this controller
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/) { return (IEditController *) new ABSwitchController(); }

private:
  ABSwitchParameters fParameters;
  ABSwitchGUIState fState;
};

}
}
}

#endif //VST_AB_SWITCH_ABSWITCHCONTROLLER_H

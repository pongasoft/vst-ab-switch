#ifndef VST_AB_SWITCH_ABSWITCHCONTROLLER_H
#define VST_AB_SWITCH_ABSWITCHCONTROLLER_H

#include <pongasoft/VST/GUI/GUIController.h>
#include "ABSwitchPlugin.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft::VST::ABSwitch {

/**
 * Represents the controller part of the plugin. Manages the UI.
 */
class ABSwitchController : public GUI::GUIController
{
public:
  //------------------------------------------------------------------------
  // UUID() method used to create the controller
  //------------------------------------------------------------------------
  static inline ::Steinberg::FUID UUID() { return ABSwitchControllerUID; };

  ABSwitchController();

  ~ABSwitchController() override;

  // getGUIState
  GUIState *getGUIState() override {return &fState; };

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this controller
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/) { return (IEditController *) new ABSwitchController(); }

protected:
  tresult initialize(FUnknown *context) override;

private:
  ABSwitchParameters fParameters;
  ABSwitchGUIState fState;
};

}

#endif //VST_AB_SWITCH_ABSWITCHCONTROLLER_H

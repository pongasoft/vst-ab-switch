#ifndef VST_AB_SWITCH_ABSWITCHCONTROLLER_H
#define VST_AB_SWITCH_ABSWITCHCONTROLLER_H

#include <public.sdk/source/vst/vsteditcontroller.h>
#include <vstgui4/vstgui/plugin-bindings/vst3editor.h>
#include "StringTextEdit.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {

/**
 * Represents the controller part of the plugin. Manages the UI.
 */
class ABSwitchController : public EditController, public VSTGUI::VST3EditorDelegate
{
public:
  ABSwitchController();

  ~ABSwitchController() override;


  /** Called at first after constructor */
  tresult PLUGIN_API initialize(FUnknown *context) override;

  /** Called at the end before destructor */
  tresult PLUGIN_API terminate() override;

  /** Create the view */
  IPlugView *PLUGIN_API createView(const char *name) override;

  /** Sets the component state (after setting the processor) or after restore */
  tresult PLUGIN_API setComponentState(IBStream *state) override;

  /** Restore the state (UI only!) (ex: after loading preset or project) */
  tresult PLUGIN_API setState(IBStream *state) override;

  /** Called to save the state (UI only!) (before saving a preset or project) */
  tresult PLUGIN_API getState(IBStream *state) override;

  /** From VST3EditorDelegate to be able to get a handle to the text edit views */
  CView *verifyView(CView *view,
                    const UIAttributes &attributes,
                    const IUIDescription *description,
                    VST3Editor *editor) override;

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this controller
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/)
  {
    return (IEditController *) new ABSwitchController();
  }

private:
  // the name of the xml file (relative) which contains the ui description
  char const *const fXmlFile;
  // the UI only controls: text fields to name the inputs
  StringTextEdit fInputLabelA;
  StringTextEdit fInputLabelB;
};

}
}

#endif //VST_AB_SWITCH_ABSWITCHCONTROLLER_H

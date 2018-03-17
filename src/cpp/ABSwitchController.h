#ifndef VST_AB_SWITCH_ABSWITCHCONTROLLER_H
#define VST_AB_SWITCH_ABSWITCHCONTROLLER_H

#include <public.sdk/source/vst/vsteditcontroller.h>

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace pongasoft {
namespace VST {

class ABSwitchController : public EditController
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

  //--- ---------------------------------------------------------------------
  // create function required for Plug-in factory,
  // it will be called to create new instances of this controller
  //--- ---------------------------------------------------------------------
  static FUnknown *createInstance(void * /*context*/)
  {
    return (IEditController *) new ABSwitchController();
  }

private:
  char const *const fXmlFile;
};

}
}

#endif //VST_AB_SWITCH_ABSWITCHCONTROLLER_H

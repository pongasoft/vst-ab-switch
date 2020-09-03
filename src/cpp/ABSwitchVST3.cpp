//------------------------------------------------------------------------------------------------------------
// This file contains the standard boilerplate code that VST3 sdk requires to instantiate the plugin
// components
//------------------------------------------------------------------------------------------------------------
#include "ABSwitchCIDs.h"

#include "version.h"
#include "ABSwitchProcessor.h"
#include "ABSwitchController.h"

#include <pongasoft/VST/PluginFactory.h>

using namespace pongasoft::VST;

//------------------------------------------------------------------------
//  Module init/exit
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// called after library was loaded
bool InitModule()
{
  return true;
}

//------------------------------------------------------------------------
// called after library is unloaded
bool DeinitModule()
{
  return true;
}

//------------------------------------------------------------------------
//  VST3 Plugin Main entry point
//------------------------------------------------------------------------
EXPORT_FACTORY Steinberg::IPluginFactory* PLUGIN_API GetPluginFactory()
{
  return JambaPluginFactory::GetVST3PluginFactory<
    pongasoft::VST::ABSwitch::ABSwitchProcessor, // processor class (Real Time)
    pongasoft::VST::ABSwitch::ABSwitchController // controller class (GUI)
  >("pongasoft", // company/vendor
    "https://www.pongasoft.com", // url
    "support@pongasoft.com", // email
    stringPluginName, // plugin name
    FULL_VERSION_STR, // plugin version
    Vst::PlugType::kFx // plugin category (can be changed to other like kInstrument, etc...)
  );
}

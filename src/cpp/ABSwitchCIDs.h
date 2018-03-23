#pragma once

#include <pluginterfaces/base/funknown.h>
#include <pluginterfaces/vst/vsttypes.h>

namespace pongasoft {
namespace VST {

// generated with java/groovy UUID.randomUUID()

static const ::Steinberg::FUID ABSwitchProcessorUID(0x8d605466, 0x25154967, 0x85ddbb25, 0x8ac01235);
static const ::Steinberg::FUID ABSwitchControllerUID(0x82aea4a3, 0x5b4e4a5f, 0xa3d68b1a, 0x8a1b69c5);

enum ABSwitchParamID : Steinberg::Vst::ParamID {

  // used in GUI only
  kAudioInputLabelA = 500,
  kAudioInputLabelB = 501,

  // used in code
  kAudioSwitch = 1000, // the toggle that switches between A and B input
  kSoftenSwitch = 1010 // turns soften (cross fade) on or off
};
//------------------------------------------------------------------------
} // namespace VST
} // namespace pongasoft

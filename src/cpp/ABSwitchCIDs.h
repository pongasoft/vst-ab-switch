#pragma once

#include <pluginterfaces/base/funknown.h>
#include <pluginterfaces/vst/vsttypes.h>

namespace pongasoft::VST {

// generated with java/groovy UUID.randomUUID()

#ifndef NDEBUG
static const ::Steinberg::FUID ABSwitchProcessorUID(0x599454df, 0x01e140a3, 0x8ccd07e6, 0xfb5d42c4);
static const ::Steinberg::FUID ABSwitchControllerUID(0xbca69cca, 0x10f34b27, 0x851b0835, 0xc240fbfa);
#else
static const ::Steinberg::FUID ABSwitchProcessorUID(0x8d605466, 0x25154967, 0x85ddbb25, 0x8ac01235);
static const ::Steinberg::FUID ABSwitchControllerUID(0x82aea4a3, 0x5b4e4a5f, 0xa3d68b1a, 0x8a1b69c5);
#endif

enum ABSwitchParamID : Steinberg::Vst::ParamID {

  // used in GUI only
  kAudioInputLabelA = 500,
  kAudioInputLabelB = 501,

  // used in code
  kAudioSwitch = 1000, // the toggle that switches between A and B input
  kSoftenSwitch = 1010, // turns soften (cross fade) on or off
  kAudioOn = 1020, // drives the LED that shows audio on/silence (computed in the processor)
};
//------------------------------------------------------------------------
} // namespace pongasoft

#pragma once

#include "pluginterfaces/base/fplatform.h"

#define MAJOR_VERSION_STR "1"
#define MAJOR_VERSION_INT 1

#define SUB_VERSION_STR "3"
#define SUB_VERSION_INT 3

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "1" // Build number to be sure that each result could identified.
#define BUILD_NUMBER_INT 1

// Version with build number (example "1.0.3.342")
#define FULL_VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR

// Version without build number (example "1.0.3")
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

#define stringOriginalFilename	"pongasoft_ABSwitch.vst3"
#if PLATFORM_64
#define stringFileDescription	"A/B Switch VST plugin by pongasoft (64Bit)"
#else
#define stringFileDescription	"ABSwitch VST plugin by pongasoft"
#endif
#define stringCompanyName		"pongasoft\0"
#define stringLegalCopyright	"© 2018 pongasoft LLC"

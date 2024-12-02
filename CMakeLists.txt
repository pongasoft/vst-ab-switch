cmake_minimum_required(VERSION 3.17)

# build Audio Unit?
option(JAMBA_ENABLE_AUDIO_UNIT "Enable Audio Unit" ON)

# Download VST SDK if not installed?
option(JAMBA_DOWNLOAD_VSTSDK "Download VST SDK if not installed" ON)

# This plugin does not have any tests at the moment
option(JAMBA_ENABLE_TESTING "Enable Testing (GoogleTest)" OFF)

# Sets the deployment target for macOS
set(JAMBA_MACOS_DEPLOYMENT_TARGET "10.14" CACHE STRING "macOS deployment target")

# To use local jamba install, uncomment the following line (no download)
set(JAMBA_ROOT_DIR "")
#set(JAMBA_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../pongasoft/jamba")

# download jamba framework
include(fetch_jamba.cmake)

# Determine proper architecture for the project
include("${JAMBA_ROOT_DIR}/cmake/JambaSetArchitecture.cmake")

set(PLUGIN_MAJOR_VERSION 1)
set(PLUGIN_MINOR_VERSION 1)
set(PLUGIN_PATCH_VERSION 3)
set(PLUGIN_VERSION "${PLUGIN_MAJOR_VERSION}.${PLUGIN_MINOR_VERSION}.${PLUGIN_PATCH_VERSION}")

project(vst-ab-switch VERSION "${PLUGIN_VERSION}")

# To use local googletest install, uncomment the following line (no download) and modify the path accordingly
set(GOOGLETEST_ROOT_DIR "")
#set(GOOGLETEST_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../google/googletest")

# Include Jamba
include("${JAMBA_ROOT_DIR}/jamba.cmake")

set(CPP_SOURCES "src/cpp")

# Generating the version.h header file which contains the plugin version (to make sure it is in sync with the version
# defined here)
set(VERSION_DIR "${CMAKE_BINARY_DIR}/generated")
configure_file("${CPP_SOURCES}/version.h.in" "${VERSION_DIR}/version.h")

# Source files for VST2
if (JAMBA_ENABLE_VST2)
  set(vst2_sources
      "${CPP_SOURCES}/ABSwitchVST2.cpp"
      )
endif ()

set(vst_sources
		${CPP_SOURCES}/ABSwitchCIDs.h
		${CPP_SOURCES}/ABSwitchController.h
		${CPP_SOURCES}/ABSwitchController.cpp
		${CPP_SOURCES}/ABSwitchModel.h
		${CPP_SOURCES}/ABSwitchPlugin.h
		${CPP_SOURCES}/ABSwitchPlugin.cpp
		${CPP_SOURCES}/ABSwitchProcessor.h
		${CPP_SOURCES}/ABSwitchProcessor.cpp
		${CPP_SOURCES}/ABSwitchUtils.h
		${CPP_SOURCES}/ABSwitchVST3.cpp
		)

# Location of resources
set(RES_DIR "${CMAKE_CURRENT_LIST_DIR}/resource")

# List of resources (images)
set(vst_resources
    "${RES_DIR}/Background.png"
    "${RES_DIR}/Background_2x.png"
    "${RES_DIR}/Control_AudioSwitch.png"
    "${RES_DIR}/Control_AudioSwitch_2x.png"
    "${RES_DIR}/Control_SoftenSwitch.png"
    "${RES_DIR}/Control_SoftenSwitch_2x.png"
    "${RES_DIR}/Control_LEDLight.png"
    "${RES_DIR}/Control_LEDLight_2x.png"
)

# Finally invoke jamba_add_vst_plugin
jamba_add_vst_plugin(
    TARGET                "pongasoft_ABSwitch" # name of CMake target for the plugin
    RELEASE_FILENAME      "ABSwitch" # filename for the plugin (ABSwitch.vst3)
    ARCHIVE_ARCHITECTURE  "${JAMBA_ARCHIVE_ARCHITECTURE}"
    TARGETS_PREFIX        "jmb_" # prefix used by all targets directly linked to this plugin
    VST_SOURCES           "${vst_sources}" "${vst2_sources}" # the source files that compose the plugin
    INCLUDE_DIRECTORIES   "${VERSION_DIR}" # we add the version folder to the list of includes
    UIDESC                "${RES_DIR}/ABSwitch.uidesc" # the main xml file for the GUI
    RESOURCES             "${vst_resources}" # the resources for the GUI (png files)
)

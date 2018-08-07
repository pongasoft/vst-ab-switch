cmake_minimum_required (VERSION 3.9)

# build VST 2 by default
option(SMTG_CREATE_VST2_VERSION "Use VST2" ON)
option(SMTG_CREATE_VST3_LINK "" OFF)

set(JAMBA_GIT_REPO "https://github.com/pongasoft/jamba" CACHE STRING "Jamba git repository url" FORCE)
set(JAMBA_GIT_TAG 0c525d8a900492c4beaaaa4c5560059a018aae28 CACHE STRING "Jamba git tag" FORCE)


#-------------------------------------------------------------------------------
# Platform Detection
#-------------------------------------------------------------------------------

set(PLUGIN_MAJOR_VERSION 1)
set(PLUGIN_MINOR_VERSION 1)
set(PLUGIN_PATCH_VERSION 2)
set(PLUGIN_VERSION "${PLUGIN_MAJOR_VERSION}.${PLUGIN_MINOR_VERSION}.${PLUGIN_PATCH_VERSION}")

project(VST_AB_Switch)

# for working on the framework at the same time...
#set(JAMBA_ROOT_DIR ../jamba)

if(NOT JAMBA_ROOT_DIR)
	include(jamba.cmake)
endif()

include(${JAMBA_ROOT_DIR}/jamba.cmake)

set(CPP_SOURCES src/cpp)

configure_file(${CPP_SOURCES}/version.h.in ${CMAKE_BINARY_DIR}/generated/version.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

if (SMTG_CREATE_VST2_VERSION)
	set(vst2_sources
			${CPP_SOURCES}/ABSwitchVST2.cpp
			)
endif()

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

# VST2 is only defined for macOS and Windows
if(MAC OR WIN)
	set(vst_sources ${vst_sources} ${vst2_sources})
endif()

set(target pongasoft_ABSwitch)
smtg_add_vst3plugin(${target} ${VST3_SDK_ROOT} ${vst_sources})
target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support jamba)

smtg_add_vst3_resource(${target} "resource/ABSwitch.uidesc")
smtg_add_vst3_resource(${target} "resource/Background.png")
smtg_add_vst3_resource(${target} "resource/Background_2x.png")
smtg_add_vst3_resource(${target} "resource/Control_AudioSwitch.png")
smtg_add_vst3_resource(${target} "resource/Control_AudioSwitch_2x.png")
smtg_add_vst3_resource(${target} "resource/Control_SoftenSwitch.png")
smtg_add_vst3_resource(${target} "resource/Control_SoftenSwitch_2x.png")
smtg_add_vst3_resource(${target} "resource/Control_LEDLight_On_2x.png")
smtg_add_vst3_resource(${target} "resource/Control_LEDLight_On.png")
smtg_add_vst3_resource(${target} "resource/Control_LEDLight_Off_2x.png")
smtg_add_vst3_resource(${target} "resource/Control_LEDLight_Off.png")

if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/mac/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/ABSwitch.rc)
endif()

# fix for vst2
jamba_fix_vst2(${target})

###################################################
# Create archive (.tgz)
###################################################
jamba_create_archive(${target} ABSwitch)

###################################################
# Create dev scripts
###################################################
jamba_dev_scripts(${target})
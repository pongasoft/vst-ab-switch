cmake_minimum_required (VERSION 3.9)

# build VST 2?
option(JAMBA_ENABLE_VST2 "Use VST2" ON)

# build Audio Unit? (not yet)
option(JAMBA_ENABLE_AUDIO_UNIT "Enable Audio Unit" OFF)

#-------------------------------------------------------------------------------
# Platform Detection
#-------------------------------------------------------------------------------

set(PLUGIN_MAJOR_VERSION 1)
set(PLUGIN_MINOR_VERSION 1)
set(PLUGIN_PATCH_VERSION 2)
set(PLUGIN_VERSION "${PLUGIN_MAJOR_VERSION}.${PLUGIN_MINOR_VERSION}.${PLUGIN_PATCH_VERSION}")

project(VST_AB_Switch)

# To disable download/update, you can set those 2 variables to local folders
unset(JAMBA_ROOT_DIR)
#set(JAMBA_ROOT_DIR ../../pongasoft/jamba)
unset(GOOGLETEST_ROOT_DIR)
#set(GOOGLETEST_ROOT_DIR ../../google/googletest)

include(jamba.cmake)

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
jamba_add_vst3plugin(${target} "${vst_sources}")
target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support jamba)

###################################################
# Resources
###################################################
jamba_add_vst3_resource(${target} DATA "ABSwitch.uidesc")
jamba_add_vst3_resource(${target} PNG "Background.png")
jamba_add_vst3_resource(${target} PNG "Background_2x.png")
jamba_add_vst3_resource(${target} PNG "Control_AudioSwitch.png")
jamba_add_vst3_resource(${target} PNG "Control_AudioSwitch_2x.png")
jamba_add_vst3_resource(${target} PNG "Control_SoftenSwitch.png")
jamba_add_vst3_resource(${target} PNG "Control_SoftenSwitch_2x.png")
jamba_add_vst3_resource(${target} PNG "Control_LEDLight.png")
jamba_add_vst3_resource(${target} PNG "Control_LEDLight_2x.png")

# this must be called after you are done calling jamba_add_vst3_resource for all resources
jamba_gen_vst3_resources(${target} "ABSwitch")

###################################################
# Create archive (.tgz)
###################################################
jamba_create_archive(${target} ABSwitch)

###################################################
# Create dev scripts
###################################################
jamba_dev_scripts(${target})
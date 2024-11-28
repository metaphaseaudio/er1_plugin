cmake_minimum_required(VERSION 3.2)

project(MP1)
set(MP1_VERSION_MAJOR 1)
set(MP1_VERSION_MINOR 0)
set(VERSION ${MP1_VERSION_MAJOR}.${MP1_VERSION_MINOR})
add_definitions(-DMP1_VERSION="${MP1_VERSION_MAJOR}.${MP1_VERSION_MINOR}")
set(JUCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shared/JUCE)
include(${CMAKE_CURRENT_SOURCE_DIR}/shared/MUDS/cmake_snippets/CPP17Boilerplate.cmake)
include(${MUDS_ROOT}/cmake_snippets/PackageAudioPlugIn.cmake)

#-----------------------------------------------------------------------------
# Build the VST SDK
#------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/shared/vst3sdk)
#------------------------------------------------------------------------------
# Build the JUCE library
#------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/shared/JUCE)
#------------------------------------------------------------------------------
# Build Metaphase Shared Libraries
#------------------------------------------------------------------------------
add_subdirectory(shared/metaphase_core)
#------------------------------------------------------------------------------
# Build MP-1 DSP Shared Libraries
#------------------------------------------------------------------------------
add_subdirectory(shared/er1_dsp)
#------------------------------------------------------------------------------
# Build JSON lib
#------------------------------------------------------------------------------
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(shared/json)
#------------------------------------------------------------------------------
# Build MP-1
#------------------------------------------------------------------------------
juce_add_plugin(MP-1
        VERSION 1.0
        COMPANY_NAME Metaphase
        NEEDS_MIDI_INPUT TRUE
        VST_NUM_MIDI_INS 1
        PLUGIN_MANUFACTURER_CODE Mtap
        PLUGIN_CODE MMP1
        COPY_PLUGIN_AFTER_BUILD TRUE
        FORMATS VST3 Standalone
        PRODUCT_NAME "MP-1")

juce_generate_juce_header(MP-1)

FILE(GLOB_RECURSE MP1_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.h)
LIST(SORT MP1_SOURCE)

target_sources(MP-1 PRIVATE ${MP1_SOURCE})
target_compile_definitions(MP-1
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(MP-1
    PRIVATE
        juce::juce_audio_utils
        juce::juce_product_unlocking
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        nlohmann_json::nlohmann_json
    PUBLIC
        er1dsp
        metaphase_core
)

install(
    TARGETS MP-1_VST3
    LIBRARY
    DESTINATION metaphase
    COMPONENT vst3
)

# Install widgets
install(
    FILES install_extras/gui/widgets.zip
    DESTINATION  $ENV{APPDATA}/Metaphase/MP-1
    COMPONENT widgets
)

# Install preset data
set(MP1_PRESET_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_extras/presets/)
file(GLOB_RECURSE MP1_PRESET_FILES "${MP1_PRESET_DATA_DIR}/*")

install(
    FILES ${MP1_PRESET_FILES}
    DESTINATION  MP1_presets
    COMPONENT presets
)

set(CPACK_PACKAGE_NAME "Metaphase MP-1")
set(CPACK_PACKAGE_VENDOR "Metaphase Audio")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MP-1 VST3 Plug-in")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Common Files\\VST3")

set(CPACK_COMPONENT_VST3_DISPLAY_NAME "VST3")

set(CPACK_NSIS_PACKAGE_NAME "Metaphase MP-1")
set(CPACK_NSIS_IGNORE_LICENSE_PAGE TRUE)
set(CPACK_COMPONENTS_ALL vst3 presets)

include(CPack)

option(BUILD_TESTS "BUILD_TESTS" OFF)
if (BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

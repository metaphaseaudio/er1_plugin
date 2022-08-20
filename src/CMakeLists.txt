cmake_minimum_required(VERSION 3.2)

project(ER1)
set(ER1_VERSION_MAJOR 1)
set(ER1_VERSION_MINOR 0)
set(VERSION ${ER1_VERSION_MAJOR}.${ER1_VERSION_MINOR})
add_definitions(-DER1_VERSION="${ER1_VERSION_MAJOR}.${ER1_VERSION_MINOR}")
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
# Build ER-1 DSP Shared Libraries
#------------------------------------------------------------------------------
add_subdirectory(shared/er1_dsp)
#------------------------------------------------------------------------------
# Build JSON lib
#------------------------------------------------------------------------------
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(shared/json)
#------------------------------------------------------------------------------
# Build ER1
#------------------------------------------------------------------------------
juce_add_plugin(ER-1
        VERSION 1.0
        COMPANY_NAME Metaphase
        NEEDS_MIDI_INPUT TRUE
        VST_NUM_MIDI_INS 1
        PLUGIN_MANUFACTURER_CODE Mtap
        PLUGIN_CODE MER1
        COPY_PLUGIN_AFTER_BUILD TRUE
        FORMATS VST3 Standalone
        PRODUCT_NAME "ER-1")

juce_generate_juce_header(ER-1)

FILE(GLOB_RECURSE ER1_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.h)
LIST(SORT ER1_SOURCE)

target_sources(ER-1 PRIVATE ${ER1_SOURCE})
target_compile_definitions(ER-1
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(ER-1
    PRIVATE
        juce::juce_audio_utils
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
        nlohmann_json::nlohmann_json
    PUBLIC
        er1dsp
        metaphase_core
)

install(
    TARGETS ER-1_VST3
    LIBRARY
    DESTINATION metaphase
    COMPONENT vst3
)

set(ER1_PRESET_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/install_extras/presets/)
file(GLOB_RECURSE ER1_PRESET_FILES "${ER1_PRESET_DATA_DIR}/*")

install(
    FILES ${ER1_PRESET_FILES}
    DESTINATION  er1_presets
    COMPONENT presets
)

set(CPACK_PACKAGE_NAME "Metaphase ER-1")
set(CPACK_PACKAGE_VENDOR "Metaphase Audio")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ER-1 VST3 Plug-in")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "Common Files\\VST3")

set(CPACK_COMPONENT_VST3_DISPLAY_NAME "VST3")

set(CPACK_NSIS_PACKAGE_NAME "Metaphase ER-1")
set(CPACK_NSIS_IGNORE_LICENSE_PAGE TRUE)
set(CPACK_COMPONENTS_ALL vst3 presets)

include(CPack)

option(BUILD_TESTS "BUILD_TESTS" OFF)
if (BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

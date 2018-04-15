cmake_minimum_required(VERSION 3.2)

project(ER1)
set(ER1_VERSION_MAJOR 1)
set(ER1_VERSION_MINOR 0)
set(VERSION ${ER1_VERSION_MAJOR}.${ER1_VERSION_MINOR})
add_definitions(-DER1_VERSION="${ER1_VERSION_MAJOR}.${ER1_VERSION_MINOR}")
include(${CMAKE_CURRENT_SOURCE_DIR}/shared/MUDS/cmake_snippets/CPP11Boilerplate.cmake)

#------------------------------------------------------------------------------
# Build the JUCE library
#------------------------------------------------------------------------------
set(JUCE_APP_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/juce_includes/AppConfig.h)
set(JUCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shared/JUCE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/juce_includes)

set(JUCE_ENABLE_PLUGIN_VST ON)
set(JUCE_ENABLE_AUDIO_BASICS ON)
set(JUCE_ENABLE_AUDIO_FORMATS ON)
set(JUCE_ENABLE_AUDIO_PROCESSORS ON)
set(JUCE_ENABLE_AUDIO_DEVICES ON)
set(JUCE_ENABLE_AUDIO_UTILS ON)
set(JUCE_ENABLE_CRYPTOGRAPHY ON)
set(JUCE_ENABLE_DATA_STRUCTURES ON)
set(JUCE_ENABLE_EVENTS ON)
set(JUCE_ENABLE_GRAPHICS ON)
set(JUCE_ENABLE_GUI_BASICS ON)
set(JUCE_ENABLE_GUI_EXTRA ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/shared/MUDS/cmake_snippets/CompileJUCE.cmake)

#------------------------------------------------------------------------------
# Build Metaphase Shared Libraries
#------------------------------------------------------------------------------
add_subdirectory(shared/metaphase_core)
add_subdirectory(shared/er1_dsp)

#------------------------------------------------------------------------------
# Build ER1
#------------------------------------------------------------------------------
FILE(GLOB_RECURSE ER1_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/er1/*.h)
LIST(SORT ER1_SOURCE)

add_library(er1lib STATIC ${ER1_SOURCE})
set_target_properties(er1lib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(er1lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/er1)

# This corresponds with the VST plug-in itself.
add_library(ER-1 MODULE ${JUCE_PLUGIN_SOURCE})

set(ER1_SOURCE
    ${ER1_SOURCE}
    ${JUCE_PLUGIN_SOURCE})

set(ER1_LIBS
    ${JUCE_LIBS}
    ${META_SHARED_LIBS}
    juce
    er1dsp
    metaphase_core)

target_link_libraries(er1lib ${ER1_LIBS} )
target_link_libraries(ER-1 er1lib)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/standalone)

if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(ER-1 ${CMAKE_THREAD_LIBS_INIT})
endif()

option(BUILD_TESTS "BUILD_TESTS" OFF)
if (BUILD_TESTS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

message("-- ER1 Plugin Test Suite build enabled")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_er1_tests AllTests.cpp)
target_link_libraries(run_er1_tests
        ${GTEST_LIBRARIES}
        ${JUCE_LIBS}
        ${META_SHARED_LIBS}
        juce
        metaphase_core
        er1lib)

set_target_properties(run_er1_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/test/metaphase_core)

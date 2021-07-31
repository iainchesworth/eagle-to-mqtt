file(GLOB_RECURSE PROJECT_TEST_TOOLS_SOURCES "*.cpp")

set(TEST_TOOLS_LIBRARY_TARGET "eagle-to-mqtt-test-tools")
add_library(${TEST_TOOLS_LIBRARY_TARGET} STATIC ${PROJECT_TEST_TOOLS_SOURCES})

target_include_directories(${TEST_TOOLS_LIBRARY_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${TEST_TOOLS_LIBRARY_TARGET} SYSTEM PRIVATE "${CMAKE_SOURCE_DIR}/deps/date/include") # Support 3rd-party dependencies
target_include_directories(${TEST_TOOLS_LIBRARY_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${TEST_TOOLS_LIBRARY_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/tests")

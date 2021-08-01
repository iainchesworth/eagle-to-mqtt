cmake_minimum_required(VERSION 3.13...3.20)

# Project + versions
#-----------------------------------------------------------------------------------------------------------------------

project(
    eagle-to-mqtt 
    VERSION 0.0.2 
    DESCRIPTION "Listens for Rainforest Automation EAGLE-200 messages and forwards them to an MQTT broker." 
    HOMEPAGE_URL "https://github.com/iainchesworth/eagle-to-mqtt" 
    LANGUAGES CXX
)

# CMake options
#-----------------------------------------------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LINK)

if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Build options
#-----------------------------------------------------------------------------------------------------------------------

option(E2M_OPTION_CODE_COVERAGE "Determine unit test code coverage" OFF)
if (E2M_OPTION_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()
option(E2M_OPTION_SUPPORT_SONARQUBE "Integrate with SonarQube reporting" OFF)

if(WIN32)
    # Custom Windows options go here...
else()
    option(E2M_OPTION_BUILD_DEB_PACKAGE "Build Debian package" OFF)
endif()

# System dependent settings
#-----------------------------------------------------------------------------------------------------------------------

if (UNIX)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    # Enable PIC
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    # Fix issues with RPATH when building under _real_ Linux/Unix (i.e. not WSL2)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

    # Set some variables to handle different library names under different environments
    set(PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTT eclipse-paho-mqtt-c::paho-mqtt3a-static eclipse-paho-mqtt-c::paho-mqtt3c-static eclipse-paho-mqtt-c::paho-mqtt3as-static eclipse-paho-mqtt-c::paho-mqtt3cs-static)
    set(PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTTPP PahoMqttCpp::paho-mqttpp3-static)

endif ()

if (WIN32)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)

    macro(get_WIN32_WINNT version)
        if (WIN32 AND CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REPLACE "10" "A" ver ${ver})
            string(REPLACE "." "" ver ${ver})
            string(REGEX REPLACE "([A-F0-9])" "0\\1" ver ${ver})
            string(SUBSTRING ${ver} 0 4 ver)

            set(${version} "0x${ver}")
        endif ()
    endmacro()

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})

    # Silence MSVC warnings about features that are deprecated in C++17 (notably in Boost headers)
    add_definitions(-D_SILENCE_CXX17_ADAPTOR_TYPEDEFS_DEPRECATION_WARNING -D_CRT_SECURE_NO_WARNINGS)

    # Set some variables to handle different library names under different environments
    set(PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTT eclipse-paho-mqtt-c::paho-mqtt3a eclipse-paho-mqtt-c::paho-mqtt3c eclipse-paho-mqtt-c::paho-mqtt3as eclipse-paho-mqtt-c::paho-mqtt3cs)
    set(PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTTPP PahoMqttCpp::paho-mqttpp3)

endif ()

# Main application
#-----------------------------------------------------------------------------------------------------------------------

find_package(Boost COMPONENTS log log_setup json program_options system thread unit_test_framework REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PahoMqttCpp CONFIG REQUIRED)
find_package(Threads REQUIRED)

# Template the git commit information prior to building the application.
set(GIT_FAIL_IF_NONZERO_EXIT false)
set(PRE_CONFIGURE_FILE "src/versions/versions_git.constants.cpp.in")
set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/versions_git.constants.cpp")
include(GitWatcher)

# Template the versioning information prior to building the application. 
set(VERSION_CMAKE_SOURCE_FILE "src/versions/versions_cmake.constants.cpp.in")
set(VERSION_CMAKE_DEST_FILE "${CMAKE_CURRENT_BINARY_DIR}/versions_cmake.constants.cpp")
configure_file(${VERSION_CMAKE_SOURCE_FILE} ${VERSION_CMAKE_DEST_FILE})

file(GLOB_RECURSE PROJECT_SOURCES "src/*/*.cpp")

set(LIBRARY_TARGET "eagle-to-mqtt-core")
add_library(${LIBRARY_TARGET} STATIC ${PROJECT_SOURCES} ${POST_CONFIGURE_FILE} ${VERSION_CMAKE_DEST_FILE})
target_compile_definitions(${LIBRARY_TARGET} PRIVATE -DPAHO_MQTTPP_VERSIONS)
target_include_directories(${LIBRARY_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${LIBRARY_TARGET} SYSTEM PRIVATE "${CMAKE_SOURCE_DIR}/deps/date/include") # Support 3rd-party dependencies
target_include_directories(${LIBRARY_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src")

set(APPLICATION_TARGET "eagle-to-mqtt")
add_executable (${APPLICATION_TARGET} "src/main.cpp")
target_include_directories(${APPLICATION_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${APPLICATION_TARGET} SYSTEM PRIVATE "${CMAKE_SOURCE_DIR}/deps/date/include") # Support 3rd-party dependencies
target_include_directories(${APPLICATION_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src")

target_link_directories(${APPLICATION_TARGET} PRIVATE ${Boost_LIBRARY_DIRS} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(
    ${APPLICATION_TARGET}
        PRIVATE
            eagle-to-mqtt-core
        PRIVATE 
            Boost::boost
            Boost::log 
            Boost::log_setup
            Boost::json 
            Boost::program_options
            OpenSSL::Crypto 
            OpenSSL::SSL
            ${PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTT}
            ${PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTTPP}
            Threads::Threads
)

# Unit testing
#-----------------------------------------------------------------------------------------------------------------------

enable_testing()
add_subdirectory(tests)

# Static analysis and code coverage
#-----------------------------------------------------------------------------------------------------------------------

if (E2M_OPTION_CODE_COVERAGE)

if (E2M_OPTION_SUPPORT_SONARQUBE)
    set(GCOVR_ADDITIONAL_ARGS --sonarqube coverage.sonarqube.xml)
endif ()

    set(COVERAGE_EXCLUDES "${CMAKE_SOURCE_DIR}/tests")
    setup_target_for_coverage_gcovr_xml(NAME coverage EXECUTABLE ctest DEPENDENCIES unit-tests)

endif ()

# Installation
#-----------------------------------------------------------------------------------------------------------------------

include(GNUInstallDirs)

install(TARGETS ${APPLICATION_TARGET} DESTINATION bin)

set(APPS \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/${APPLICATION_TARGET}${CMAKE_EXECUTABLE_SUFFIX})     # paths to executables
set(LIBS "")
set(DIRS ${CMAKE_CURRENT_BINARY_DIR})                                                                    # directories to search for prerequisites

install (CODE "
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"${LIBS}\" \"${DIRS}\")
" OPTIONAL)

# Packaging and distribution
#-----------------------------------------------------------------------------------------------------------------------

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
    if(E2M_OPTION_BUILD_DEB_PACKAGE)
        set(CPACK_GENERATOR "DEB")
        include(CPackDebConfig)
    else()
        set(CPACK_GENERATOR "TGZ")
	endif()
endif()

set(CPACK_PACKAGE_CHECKSUM SHA512)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")

include(CPack)

# Add a custom target to enable CPack to be run under Visual Studio
add_custom_target(bundle COMMAND "${CMAKE_CPACK_COMMAND}" "-C" "$<CONFIGURATION>" "--config" "${CMAKE_BINARY_DIR}/CPackConfig.cmake" COMMENT "Running CPack. Please wait...")
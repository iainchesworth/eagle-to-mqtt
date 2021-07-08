cmake_minimum_required(VERSION 3.13...3.20)

# Project + versions
#-----------------------------------------------------------------------------------------------------------------------

project (eagle-to-mqtt VERSION 0.0.1)

# CMake options
#-----------------------------------------------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LINK)
if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

# Build options
#-----------------------------------------------------------------------------------------------------------------------

if(WIN32)
    # Custom Windows options go here...
else()
    option(BUILD_DEB_PACKAGE "Build Debian package" FALSE)
endif()

# System dependent settings
#-----------------------------------------------------------------------------------------------------------------------

if (UNIX)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    # Fix issues with RPATH when building under _real_ Linux/Unix (i.e. not WSL2)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

    # Fix issues with dynamic linking for Boost under Linux/Unix
    add_definitions(-DBOOST_LOG_DYN_LINK)

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
endif ()

# Main application
#-----------------------------------------------------------------------------------------------------------------------

find_package(Boost COMPONENTS log json program_options system thread unit_test_framework REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(PahoMqttCpp CONFIG REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "src/*/*.cpp")

set(LIBRARY_TARGET "eagle-to-mqtt-core")
add_library(${LIBRARY_TARGET} STATIC ${PROJECT_SOURCES})
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
            ${LIBRARY_TARGET}
        PRIVATE 
            Boost::boost
            Boost::log 
            Boost::json 
            Boost::program_options
            OpenSSL::Crypto 
            OpenSSL::SSL 
            PahoMqttCpp::paho-mqttpp3
            Threads::Threads
)

# Unit testing
#-----------------------------------------------------------------------------------------------------------------------

enable_testing()
add_subdirectory(tests)

# Packaging and distribution
#-----------------------------------------------------------------------------------------------------------------------

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
    if(BUILD_DEB_PACKAGE)
        set(CPACK_GENERATOR "DEB")
        include(cmake/CPackDebConfig.cmake)
    else()
        set(CPACK_GENERATOR "TGZ")
	endif()
endif()

include(CPack)

# Installation
#-----------------------------------------------------------------------------------------------------------------------

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

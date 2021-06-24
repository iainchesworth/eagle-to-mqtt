file(GLOB_RECURSE PROJECT_TEST_SOURCES "**.cpp")

set(TEST_TARGET "eagle-to-mqtt-tests")
add_executable(${TEST_TARGET} ${PROJECT_TEST_SOURCES})

target_include_directories(${TEST_TARGET} SYSTEM PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${TEST_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${TEST_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/tests")
target_link_directories(${TEST_TARGET} PRIVATE ${Boost_LIBRARY_DIRS} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(
    ${TEST_TARGET}
        PRIVATE
            ${LIBRARY_TARGET}
        PRIVATE 
            Boost::boost 
            Boost::log 
            Boost::program_options
            Boost::unit_test_framework
            OpenSSL::Crypto 
            OpenSSL::SSL 
            PahoMqttCpp::paho-mqttpp3
            Threads::Threads
)

add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})

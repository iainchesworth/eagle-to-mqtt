include(BoostTestHelpers)

file(GLOB_RECURSE PROJECT_TEST_SOURCES "**.cpp")

add_custom_target(unit-tests) # Phony target to group unit tests together

foreach(PROJECT_TEST_SOURCE_FILE ${PROJECT_TEST_SOURCES})
	
	# Add each of the various test source files to the test suite to be run under make test
	add_boost_test(
		SOURCE 
			${PROJECT_TEST_SOURCE_FILE} 
		INCLUDE 
			${Boost_INCLUDE_DIR} 
			"${CMAKE_SOURCE_DIR}/deps/date/include" 
			"${CMAKE_SOURCE_DIR}/src"
			"${CMAKE_SOURCE_DIR}/tests"
		LINK_TARGETS
			eagle-to-mqtt-core
			eagle-to-mqtt-test-tools
		LINK_LIBS
			Boost::boost 
			Boost::json 
			Boost::log 
            Boost::log_setup
			Boost::program_options 
			OpenSSL::Crypto 
			OpenSSL::SSL 
			${PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTT} 
			${PLATFORM_SPECIFIC_LINK_TARGET_PAHO_MQTTPP} 
			Threads::Threads
		TEST_TARGET
		    unit-tests
	)

endforeach()

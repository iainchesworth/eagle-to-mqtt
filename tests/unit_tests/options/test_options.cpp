#include <boost/program_options/errors.hpp>
#include <boost/test/unit_test.hpp>
#include <spdlog/spdlog.h>

#include <array>
#include <stdexcept>

#include "exceptions/options_option_conflict.h"
#include "options/options.h"

#include "test_tools/test_tools_pass_c_array.h"

BOOST_AUTO_TEST_SUITE(ProgramOptions)

BOOST_AUTO_TEST_CASE(Test_Default_aka_NoOptions)
{
	std::array<char*, 1> program_arguments =
	{
		(char*)"Test_Default_aka_NoOptions"
	};

	BOOST_CHECK_THROW(Options options(program_arguments.size(), test_tools::c_array_cast(program_arguments)), boost::program_options::required_option);
}

BOOST_AUTO_TEST_CASE(Test_ConflictingOptions)
{
	std::array<char*, 3> program_arguments_test1 =
	{
		(char*)"Test_ConflictingOptions - test quiet vs. verbose",
		(char*)"--quiet",
		(char*)"--verbose"
	};

	BOOST_CHECK_THROW(Options options_1(program_arguments_test1.size(), test_tools::c_array_cast(program_arguments_test1)), Options_OptionConflict);

	std::array<char*, 3> program_arguments_test2 =
	{
		(char*)"Test_ConflictingOptions - test debug vs. verbose",
		(char*)"--debug",
		(char*)"--verbose"
	};

	BOOST_CHECK_THROW(Options options_2(program_arguments_test2.size(), test_tools::c_array_cast(program_arguments_test2)), Options_OptionConflict);
}

BOOST_AUTO_TEST_CASE(Test_DependentOptions)
{
}

BOOST_AUTO_TEST_CASE(Test_LoggingLevelOptions)
{
	std::array<char*, 3> default_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host"
	};

	Options options_1(default_program_arguments.size(), test_tools::c_array_cast(default_program_arguments));
	BOOST_TEST(spdlog::get_level() == spdlog::level::info);

	std::array<char*, 4> debug_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--debug"
	};

	Options options_2(debug_logging_level.size(), test_tools::c_array_cast(debug_logging_level));
	BOOST_TEST(spdlog::get_level() == spdlog::level::debug);

	std::array<char*, 4> trace_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--verbose"
	};

	Options options_3(trace_logging_level.size(), test_tools::c_array_cast(trace_logging_level));
	BOOST_TEST(spdlog::get_level() == spdlog::level::trace);

	std::array<char*, 4> critical_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--quiet"
	};

	Options options_4(critical_logging_level.size(), test_tools::c_array_cast(critical_logging_level));
	BOOST_TEST(spdlog::get_level() == spdlog::level::critical);
}

BOOST_AUTO_TEST_CASE(Test_IntegrationOptions)
{
	std::array<char*, 3> default_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host"
	};

	Options options_1(default_program_arguments.size(), test_tools::c_array_cast(default_program_arguments));

	BOOST_TEST(true == options_1.FroniusIntegrationIsEnabled());
	BOOST_TEST(true == options_1.RainforestIntegrationIsEnabled());
	BOOST_TEST(true == options_1.StatisticsReportingIsEnabled());

	std::array<char*, 4> disable_fronius_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--disable-fronius"
	};

	Options options_2(disable_fronius_program_arguments.size(), test_tools::c_array_cast(disable_fronius_program_arguments));

	BOOST_TEST(false == options_2.FroniusIntegrationIsEnabled());
	BOOST_TEST(true == options_2.RainforestIntegrationIsEnabled());
	BOOST_TEST(true == options_2.StatisticsReportingIsEnabled());

	std::array<char*, 4> disable_rainforest_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--disable-rainforest"
	};

	Options options_3(disable_rainforest_program_arguments.size(), test_tools::c_array_cast(disable_rainforest_program_arguments));

	BOOST_TEST(true == options_3.FroniusIntegrationIsEnabled());
	BOOST_TEST(false == options_3.RainforestIntegrationIsEnabled());
	BOOST_TEST(true == options_3.StatisticsReportingIsEnabled());

	std::array<char*, 4> disable_statistics_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--disable-statistics"
	};

	Options options_4(disable_statistics_program_arguments.size(), test_tools::c_array_cast(disable_statistics_program_arguments));

	BOOST_TEST(true == options_4.FroniusIntegrationIsEnabled());
	BOOST_TEST(true == options_4.RainforestIntegrationIsEnabled());
	BOOST_TEST(false == options_4.StatisticsReportingIsEnabled());

	std::array<char*, 6> disable_all_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--disable-fronius",
		(char*)"--disable-rainforest",
		(char*)"--disable-statistics"
	};

	Options options_5(disable_all_program_arguments.size(), test_tools::c_array_cast(disable_all_program_arguments));

	BOOST_TEST(false == options_5.FroniusIntegrationIsEnabled());
	BOOST_TEST(false == options_5.RainforestIntegrationIsEnabled());
	BOOST_TEST(false == options_5.StatisticsReportingIsEnabled());
}

BOOST_AUTO_TEST_CASE(Test_HttpOptions)
{
	std::array<char*, 3> default_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host"
	};

	Options options_1(default_program_arguments.size(), test_tools::c_array_cast(default_program_arguments));

	BOOST_TEST(0 == options_1.HttpInterface().compare("0.0.0.0"));
	BOOST_TEST(3000 == options_1.HttpPort());
	BOOST_TEST(false == options_1.HttpUseTls());

	std::array<char*, 8> all_http_program_arguments =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--http-host",
		(char*)"http.host",
		(char*)"--http-port",
		(char*)"12345",
		(char*)"--http-use-tls"
	};

	Options options_2(all_http_program_arguments.size(), test_tools::c_array_cast(all_http_program_arguments));

	BOOST_TEST(0 == options_2.HttpInterface().compare(all_http_program_arguments[4]));
	BOOST_TEST(12345 == options_2.HttpPort());
	BOOST_TEST(true == options_2.HttpUseTls());
}

BOOST_AUTO_TEST_CASE(Test_MqttOptions)
{
	std::array<char*, 3> default_program_arguments =
	{
		(char*)"Test_MqttOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host"
	};

	Options options_1(default_program_arguments.size(), test_tools::c_array_cast(default_program_arguments));

	BOOST_TEST(0 == options_1.MqttHost().compare(default_program_arguments[2]));
	BOOST_TEST(true == options_1.MqttPassword().empty());
	BOOST_TEST(1883 == options_1.MqttPort());
	BOOST_TEST(0 == options_1.MqttTopic().compare("eagle"));
	BOOST_TEST(false == options_1.MqttUseTls());
	BOOST_TEST(true == options_1.MqttUsername().empty());

	std::array<char*, 12> all_mqtt_program_arguments =
	{
		(char*)"Test_MqttOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--mqtt-password",
		(char*)"mqtt.password",
		(char*)"--mqtt-port",
		(char*)"12345",
		(char*)"--mqtt-topic",
		(char*)"mqtt.topic",
		(char*)"--mqtt-username",
		(char*)"mqtt.username",
		(char*)"--mqtt-use-tls"
	};

	Options options_2(all_mqtt_program_arguments.size(), test_tools::c_array_cast(all_mqtt_program_arguments));

	BOOST_TEST(0 == options_2.MqttHost().compare(all_mqtt_program_arguments[2]));
	BOOST_TEST(0 == options_2.MqttPassword().compare(all_mqtt_program_arguments[4]));
	BOOST_TEST(12345 == options_2.MqttPort());
	BOOST_TEST(0 == options_2.MqttTopic().compare(all_mqtt_program_arguments[8]));
	BOOST_TEST(true == options_2.MqttUseTls());
	BOOST_TEST(0 == options_2.MqttUsername().compare(all_mqtt_program_arguments[10]));
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/log/trivial.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/test/unit_test.hpp>

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
	auto options_1_logging_level_triggered = boost::log::trivial::fatal;

	// boost::log::trivial::info <-- default logging level

	BOOST_LOG_TRIVIAL(trace) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::trace; return options_1_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_1_logging_level_triggered);
	BOOST_LOG_TRIVIAL(debug) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::debug; return options_1_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_1_logging_level_triggered);
	BOOST_LOG_TRIVIAL(info) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::info; return options_1_logging_level_triggered; }());
	// NOTE THE CHANGE IN LOGGING LEVEL HERE
	BOOST_TEST(boost::log::trivial::info == options_1_logging_level_triggered);
	BOOST_LOG_TRIVIAL(warning) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::warning; return options_1_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::warning == options_1_logging_level_triggered);
	BOOST_LOG_TRIVIAL(error) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::error; return options_1_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::error == options_1_logging_level_triggered);
	BOOST_LOG_TRIVIAL(fatal) << ([&options_1_logging_level_triggered]() { options_1_logging_level_triggered = boost::log::trivial::fatal; return options_1_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_1_logging_level_triggered);

	std::array<char*, 4> debug_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--debug"
	};

	Options options_2(debug_logging_level.size(), test_tools::c_array_cast(debug_logging_level));
	auto options_2_logging_level_triggered = boost::log::trivial::fatal;

	// boost::log::trivial::debug <-- new logging level

	BOOST_LOG_TRIVIAL(trace) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::trace; return options_2_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_2_logging_level_triggered);
	BOOST_LOG_TRIVIAL(debug) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::debug; return options_2_logging_level_triggered; }());
	// NOTE THE CHANGE IN LOGGING LEVEL HERE
	BOOST_TEST(boost::log::trivial::debug == options_2_logging_level_triggered);
	BOOST_LOG_TRIVIAL(info) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::info; return options_2_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::info == options_2_logging_level_triggered);
	BOOST_LOG_TRIVIAL(warning) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::warning; return options_2_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::warning == options_2_logging_level_triggered);
	BOOST_LOG_TRIVIAL(error) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::error; return options_2_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::error == options_2_logging_level_triggered);
	BOOST_LOG_TRIVIAL(fatal) << ([&options_2_logging_level_triggered]() { options_2_logging_level_triggered = boost::log::trivial::fatal; return options_2_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_2_logging_level_triggered);

	std::array<char*, 4> trace_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--verbose"
	};

	Options options_3(trace_logging_level.size(), test_tools::c_array_cast(trace_logging_level));
	auto options_3_logging_level_triggered = boost::log::trivial::fatal;

	// boost::log::trivial::trace <-- new logging level

	// NOTE THE CHANGE IN LOGGING LEVEL HERE
	BOOST_LOG_TRIVIAL(trace) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::trace; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::trace == options_3_logging_level_triggered);
	BOOST_LOG_TRIVIAL(debug) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::debug; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::debug == options_3_logging_level_triggered);
	BOOST_LOG_TRIVIAL(info) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::info; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::info == options_3_logging_level_triggered);
	BOOST_LOG_TRIVIAL(warning) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::warning; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::warning == options_3_logging_level_triggered);
	BOOST_LOG_TRIVIAL(error) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::error; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::error == options_3_logging_level_triggered);
	BOOST_LOG_TRIVIAL(fatal) << ([&options_3_logging_level_triggered]() { options_3_logging_level_triggered = boost::log::trivial::fatal; return options_3_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_3_logging_level_triggered);

	std::array<char*, 4> fatal_logging_level =
	{
		(char*)"Test_HttpOptions",
		(char*)"--mqtt-host",
		(char*)"mqtt.host",
		(char*)"--quiet"
	};

	Options options_4(fatal_logging_level.size(), test_tools::c_array_cast(fatal_logging_level));
	auto options_4_logging_level_triggered = boost::log::trivial::fatal;

	// boost::log::trivial::fatal <-- new logging level

	BOOST_LOG_TRIVIAL(trace) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::trace; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
	BOOST_LOG_TRIVIAL(debug) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::debug; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
	BOOST_LOG_TRIVIAL(info) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::info; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
	BOOST_LOG_TRIVIAL(warning) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::warning; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
	BOOST_LOG_TRIVIAL(error) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::error; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
	// NOTE THE CHANGE IN LOGGING LEVEL HERE
	BOOST_LOG_TRIVIAL(fatal) << ([&options_4_logging_level_triggered]() { options_4_logging_level_triggered = boost::log::trivial::fatal; return options_4_logging_level_triggered; }());
	BOOST_TEST(boost::log::trivial::fatal == options_4_logging_level_triggered);
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

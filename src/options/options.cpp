#include <boost/program_options.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.
#include <spdlog/sinks/ostream_sink.h>

#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

#include "options/options.h"
#include "options/option_validators.h"
#include "versions/versions_cmake.h"
#include "versions/versions_git.h"

Options::Options(int argc, char* argv[]) :
	m_HttpPort(),
	m_MqttPassword(MQTT_DEFAULT_PASSWORD),
	m_MqttPort(),
	m_MqttUseAuthentication(false),
	m_MqttUsername(MQTT_DEFAULT_USERNAME)
{
	boost::program_options::options_description cmdline_options("Program Arguments");

	auto set_logging_level = [](spdlog::level::level_enum log_level) { spdlog::set_level(log_level); };
	auto set_debug_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(spdlog::level::debug); } };
	auto set_trace_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(spdlog::level::trace); } };
	auto set_fatal_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(spdlog::level::critical); } };

	auto enable_authentication = [this](const std::string&) { this->m_MqttUseAuthentication = true; };

	auto cout_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(std::cout);
	auto out_logger = std::make_shared<spdlog::logger>("std::cout", cout_sink);
	out_logger->set_pattern("%v");
	auto cerr_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(std::cerr);
	auto err_logger = std::make_shared<spdlog::logger>("std::cerr", cerr_sink);
	err_logger->set_pattern("%v");

	try
	{

		// Set the default logging level before any of the various level options are processed.
		set_logging_level(spdlog::level::info);

		// Configure the various options for the application,
		boost::program_options::options_description options_app("Application Options");
		options_app.add_options()
			("debug,d", boost::program_options::bool_switch()->default_value(false)->notifier(set_debug_logging), "Enable debugging")
			("quiet,q", boost::program_options::bool_switch()->default_value(false)->notifier(set_fatal_logging), "Don't output any status messages")
			("help,h", "Prints this message")
			("verbose,v", boost::program_options::bool_switch()->default_value(false)->notifier(set_trace_logging), "Verbose output")
			("version", "Prints version information");

		boost::program_options::options_description options_integrations("Integrations");
		options_integrations.add_options()
			("disable-fronius", boost::program_options::bool_switch(&m_DisableFroniusIntegration)->default_value(false), "Disables Fronius Symo (SOLAR API v1) support")
			("disable-rainforest", boost::program_options::bool_switch(&m_DisableRainforestIntegration)->default_value(false), "Disables Rainforest Automation RFA-Z109 and EAGLE-200 support")
			("disable-statistics", boost::program_options::bool_switch(&m_DisableStatisticsReporting)->default_value(false), "Disables the capture and reporting of statistics via the HTTP interface");

		boost::program_options::options_description options_httpuploader("HTTP Uploader API Options");
		options_httpuploader.add_options()
			("http-host", boost::program_options::value<std::string>(&m_HttpInterface)->default_value(HTTP_DEFAULT_INTERFACE), "Interface that the HTTP server should listen on")
			("http-port", boost::program_options::value<uint16_t>(&m_HttpPort)->default_value(HTTP_DEFAULT_PORT), "Port for the HTTP server to listen on")
			("http-use-tls", boost::program_options::bool_switch(&m_HttpUseTls)->default_value(false), "Enable HTTP server TLS support");

		boost::program_options::options_description options_mqttclient("MQTT Client Options");
		options_mqttclient.add_options()
			("mqtt-host", boost::program_options::value<std::string>(&m_MqttHost)->required(), "Hostname of the MQTT server")
			("mqtt-password", boost::program_options::value<std::string>(&m_MqttPassword)->notifier(enable_authentication), "Password for the MQTT server user")
			("mqtt-port", boost::program_options::value<uint16_t>(&m_MqttPort)->default_value(MQTT_DEFAULT_PORT), "Port of the MQTT server")
			("mqtt-topic", boost::program_options::value<std::string>(&m_MqttTopic)->default_value(MQTT_DEFAULT_TOPIC), "MQTT topic to use")
			("mqtt-use-tls", boost::program_options::bool_switch(&m_MqttUseTls)->default_value(false), "Enable MQTT client TLS support")
			("mqtt-username", boost::program_options::value<std::string>(&m_MqttUsername)->notifier(enable_authentication), "USername for the MQTT server user");

		cmdline_options
			.add(options_app)
			.add(options_integrations)
			.add(options_httpuploader)
			.add(options_mqttclient);

		boost::program_options::variables_map vm;
		boost::program_options::parsed_options intermediate = boost::program_options::parse_command_line(argc, argv, cmdline_options);
		boost::program_options::store(intermediate, vm);

		if (vm.count("help"))
		{
			out_logger->info("{}: {}", VersionInfo::ProjectName(), VersionInfo::ProjectDescription());
			out_logger->info("{}", cmdline_options);
			std::exit(EXIT_SUCCESS);
		}
		else if (vm.count("version"))
		{
			std::ostringstream version_oss;
			version_oss << VersionInfo::ProjectName() << " v" << VersionInfo::ProjectVersion();
			
			if (GitMetadata::Populated())
			{
				version_oss << " (" << GitMetadata::Describe() << ": " << GitMetadata::CommitDate() << ")" << std::endl << std::endl;

				version_oss << "Commit " << GitMetadata::CommitSHA1() << " (HEAD)" << std::endl;
				version_oss << "Author: " << GitMetadata::AuthorName() << " <" << GitMetadata::AuthorEmail() << ">" << std::endl;

				if (GitMetadata::AnyUncommittedChanges())
				{
					out_logger->info("{}", version_oss.str());
					err_logger->warn("WARNING: there were uncommitted changes at build-time");
					std::exit(EXIT_FAILURE);
				}
			}
			else
			{
				version_oss << " (" << "No git commit information found" << ")" << std::endl;
			}

			out_logger->info("{}", version_oss.str());
			std::exit(EXIT_SUCCESS);
		}
		else
		{
			Validator_ConflictingOptions(vm, "quiet", "verbose");
			Validator_ConflictingOptions(vm, "debug", "verbose");

			boost::program_options::notify(vm);
		}
	}
	catch (const boost::program_options::required_option& roex)
	{
		if (0 == roex.get_option_name().compare("mqtt-host"))
		{
			err_logger->critical("Must specify the MQTT host!");
		}
		else
		{
			err_logger->critical("Missing required argument: {}", roex.get_option_name());
		}

		err_logger->critical("{}", cmdline_options);
		throw; // Re-throw to propagate the exception up to the main application (so it terminates).
	}
	catch (const boost::program_options::error& poex)
	{
		// Display the help information then re-throw the exception...
		err_logger->critical("Failed to process provided arguments: {}", poex.what());
		err_logger->critical("{}", cmdline_options);
		throw; // Re-throw to propagate the exception up to the main application (so it terminates).
	}
}

bool Options::FroniusIntegrationIsEnabled() const
{
	// Inverted boolean --> return value
	return (!m_DisableFroniusIntegration);
}

bool Options::RainforestIntegrationIsEnabled() const
{
	// Inverted boolean --> return value
	return (!m_DisableRainforestIntegration);
}

bool Options::StatisticsReportingIsEnabled() const
{
	// Inverted boolean --> return value
	return (!m_DisableStatisticsReporting);
}

const std::string& Options::HttpInterface() const
{
	return m_HttpInterface;
}

uint16_t Options::HttpPort() const
{
	return m_HttpPort;
}
bool Options::HttpUseTls() const
{
	return m_HttpUseTls;
}

const std::string& Options::MqttHost() const
{
	return m_MqttHost;
}

std::string Options::MqttPassword() const
{
	return m_MqttPassword;
}

uint16_t Options::MqttPort() const
{
	return m_MqttPort;
}

std::string Options::MqttTopic() const
{
	return m_MqttTopic;
}

bool Options::MqttUseAuthentication() const
{
	return m_MqttUseAuthentication;
}

bool Options::MqttUseTls() const
{
	return m_MqttUseTls;
}

std::string Options::MqttUsername() const
{
	return m_MqttUsername;
}

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp> 
#include <boost/program_options.hpp>

#include <cstdint>
#include <iostream>
#include <string>

#include "options/options.h"
#include "options/option_validators.h"
#include "versions/versions_cmake.h"
#include "versions/versions_git.h"

Options::Options(int argc, char* argv[]) :
	m_HttpInterface(),
	m_HttpUseTls(),
	m_HttpPort(),
	m_MqttHost(),
	m_MqttPassword(MQTT_DEFAULT_PASSWORD),
	m_MqttPort(),
	m_MqttTopic(),
	m_MqttUseTls(),
	m_MqttUseAuthentication(false),
	m_MqttUsername(MQTT_DEFAULT_USERNAME)
{
	boost::program_options::options_description cmdline_options("Program Arguments");

	auto set_logging_level = [](boost::log::trivial::severity_level log_level) { boost::log::core::get()->set_filter(boost::log::trivial::severity >= log_level); };
	auto set_debug_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(boost::log::trivial::debug); } };
	auto set_trace_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(boost::log::trivial::trace); } };
	auto set_fatal_logging = [set_logging_level](const bool& set_level) { if (set_level) { set_logging_level(boost::log::trivial::fatal); } };

	auto enable_authentication = [this](const std::string&) { this->m_MqttUseAuthentication = true; };

	try
	{
		// Set the default logging level before any of the various level options are processed.
		set_logging_level(boost::log::trivial::info);

		// Configure the various options for the application,
		boost::program_options::options_description options_app("Application Options");
		options_app.add_options()
			("debug,d", boost::program_options::bool_switch()->default_value(false)->notifier(set_debug_logging), "Enable debugging")
			("quiet,q", boost::program_options::bool_switch()->default_value(false)->notifier(set_fatal_logging), "Don't output any status messages")
			("help,h", "Prints this message")
			("verbose,v", boost::program_options::bool_switch()->default_value(false)->notifier(set_trace_logging), "Verbose output")
			("version", "Prints version information");

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

		cmdline_options.add(options_app).add(options_httpuploader).add(options_mqttclient);

		boost::program_options::variables_map vm;
		boost::program_options::parsed_options intermediate = boost::program_options::parse_command_line(argc, argv, cmdline_options);
		boost::program_options::store(intermediate, vm);

		if (vm.count("help"))
		{
			std::cout << VersionInfo::ProjectName() << ": " << VersionInfo::ProjectDescription() << std::endl;
			std::cout << cmdline_options;
			std::exit(EXIT_SUCCESS);
		}
		else if (vm.count("version"))
		{
			std::cout << VersionInfo::ProjectName() << " v" << VersionInfo::ProjectVersion();
			
			if (GitMetadata::Populated())
			{
				std::cout << " (" << GitMetadata::Describe() << ": " << GitMetadata::CommitDate() << ")" << std::endl << std::endl;

				std::cout << "Commit " << GitMetadata::CommitSHA1() << " (HEAD)" << std::endl;
				std::cout << "Author: " << GitMetadata::AuthorName() << " <" << GitMetadata::AuthorEmail() << ">" << std::endl;

				if (GitMetadata::AnyUncommittedChanges())
				{
					std::cerr << "WARNING: there were uncommitted changes at build-time" << std::endl;
					std::exit(EXIT_FAILURE);
				}
			}
			else
			{
				std::cout << " (" << "No git commit information found" << ")" << std::endl;
			}

			std::cout << std::endl;
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
			std::cerr << "Must specify the MQTT host!" << std::endl;
		}
		else
		{
			std::cerr << "Missing required argument: " << roex.get_option_name() << std::endl;
		}

		std::cerr << cmdline_options;
		exit(-1);
	}
	catch (const boost::program_options::error& poex)
	{
		// Display the help information then re-throw the exception...
		std::cerr << "Failed to process provided arguments: " << poex.what() << std::endl;
		std::cerr << cmdline_options;
		exit(-1);
	}
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

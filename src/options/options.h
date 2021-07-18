#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>
#include <string>

class Options
{
public:
	Options(int argc, char* argv[]);

public:
	bool FroniusIntegrationIsEnabled() const;
	bool RainforestIntegrationIsEnabled() const;
	bool StatisticsReportingIsEnabled() const;

public:
	// Uploader API options
	const std::string& HttpInterface() const;
	uint16_t HttpPort() const;
	bool HttpUseTls() const;

public:
	// MQTT client options
	const std::string& MqttHost() const;
	std::string MqttPassword() const;
	uint16_t MqttPort() const;
	std::string MqttTopic() const;
	bool MqttUseAuthentication() const;
	bool MqttUseTls() const;
	std::string MqttUsername() const;

private:
	const std::string HTTP_DEFAULT_INTERFACE{ "0.0.0.0" };
	const uint16_t HTTP_DEFAULT_PORT = 3000;
	const std::string MQTT_DEFAULT_PASSWORD{ "" };
	const uint16_t MQTT_DEFAULT_PORT = 1883;
	const std::string MQTT_DEFAULT_TOPIC{"eagle"};
	const std::string MQTT_DEFAULT_USERNAME{ "" };

private:
	bool m_DisableFroniusIntegration;
	bool m_DisableRainforestIntegration;
	bool m_DisableStatisticsReporting;
	std::string m_HttpInterface;
	uint16_t m_HttpPort;
	bool m_HttpUseTls;
	std::string m_MqttHost;
	std::string m_MqttPassword;
	uint16_t m_MqttPort;
	std::string m_MqttTopic;
	bool m_MqttUseAuthentication;
	bool m_MqttUseTls;
	std::string m_MqttUsername;
};

#endif // OPTIONS_H

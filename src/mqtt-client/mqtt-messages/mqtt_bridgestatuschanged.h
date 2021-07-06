#ifndef MQTT_BRIDGESTATUSCHANGED_H
#define MQTT_BRIDGESTATUSCHANGED_H

#include <string>

#include "bridge/bridge_status.h"
#include "mqtt-client/mqtt-messages/mqtt_message.h"

class Mqtt_BridgeStatusChanged : public MqttMessage
{
	static const std::string TOPIC;

public:
	Mqtt_BridgeStatusChanged(const std::string& topic_prefix, const BridgeStatus status);
	virtual ~Mqtt_BridgeStatusChanged();

private:
	virtual MqttMessage::DataBufferPtr Generate() const;

private:
	const BridgeStatus m_Status;
};

#endif // MQTT_BRIDGESTATUSCHANGED_H

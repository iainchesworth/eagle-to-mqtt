#ifndef MQTT_QOS_H
#define MQTT_QOS_H

enum class MqttQosLevels : int
{
	AtMostOnce = 0,
	AtLeastOnce = 1,
	ExactlyOnce = 2
};

#endif // MQTT_QOS_H

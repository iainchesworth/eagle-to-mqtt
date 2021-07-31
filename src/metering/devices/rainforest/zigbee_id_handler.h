#ifndef ZIGBEE_ID_HANDLER_H
#define ZIGBEE_ID_HANDLER_H

#include <boost/log/trivial.hpp>

#include <functional>
#include <optional>

#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "notifications/notification_manager.h"

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void ProcessAndSaveZigbeeId(T1 ethernet_mac_id, const T2& src_mac_id, T3& dest_mac_id, const T4& device_name, T5 notification_ptr, T6 notification_func)
{
	if (!src_mac_id.has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing " << device_name << L" id in message payload";
	}
	else if (!src_mac_id.value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid " << device_name << L" id in message payload";
	}
	else if (dest_mac_id.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid " << device_name << L" id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing " << device_name << L" id for Eagle: " << ZigBeeMacId::ToString(src_mac_id.value());
		dest_mac_id = src_mac_id.value();

		std::bind(notification_func, notification_ptr, std::placeholders::_1)(dest_mac_id);
		NotificationManagerSingleton()->Dispatch(notification_ptr);
	}
}

#endif // ZIGBEE_ID_HANDLER_H

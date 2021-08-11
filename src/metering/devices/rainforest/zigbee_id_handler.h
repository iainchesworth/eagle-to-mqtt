#ifndef ZIGBEE_ID_HANDLER_H
#define ZIGBEE_ID_HANDLER_H

#include <spdlog/spdlog.h>

#include <functional>
#include <optional>

#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "notifications/notification_manager.h"

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
void ProcessAndSaveZigbeeId(T1 ethernet_mac_id, const T2& src_mac_id, T3& dest_mac_id, const T4& device_name, T5 notification_ptr, T6 notification_func)
{
	if (!src_mac_id.has_value())
	{
		spdlog::trace("Missing {} id in message payload", device_name);
	}
	else if (!src_mac_id.value().IsValid())
	{
		spdlog::debug("Received invalid {} id in message payload", device_name);
	}
	else if (dest_mac_id.IsValid())
	{
		spdlog::trace("Have already received valid id; ignoring ", device_name);
	}
	else
	{
		spdlog::debug("Capturing {} id for Eagle: {}", device_name, ZigBeeMacId::ToString(src_mac_id.value()));
		dest_mac_id = src_mac_id.value();

		std::bind(notification_func, notification_ptr, std::placeholders::_1)(dest_mac_id);
		NotificationManagerSingleton()->Dispatch(notification_ptr);
	}
}

#endif // ZIGBEE_ID_HANDLER_H

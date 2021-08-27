#ifndef NOTIFICATION_PUBLISHPAYLOAD_H
#define NOTIFICATION_PUBLISHPAYLOAD_H

#include <boost/signals2/signal.hpp>

#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>

#include "notifications/notification_base.h"
#include "notifications/common/streamable_any.h"

template<typename DEVICE_ID>
class PayloadTypes
{
public:
	using DeviceId = DEVICE_ID;
	using ElementMap = std::unordered_map<std::string, streamable_any>;
	using Element = ElementMap::value_type;
	using Payload = std::pair<DeviceId, ElementMap>;

public:
	using NotificationSignature = void(const Payload& payload);
};

template<typename DEVICE_ID>
class Notification_PublishPayload : public NotificationBase<typename PayloadTypes<DEVICE_ID>::NotificationSignature>
{
public:
	using Types = PayloadTypes<DEVICE_ID>;

public:
	Notification_PublishPayload(typename Types::DeviceId device_id, std::initializer_list<typename Types::Element> payload_elements = {}) :
		NotificationBase<typename PayloadTypes<DEVICE_ID>::NotificationSignature>(),
		m_ElementsMap(payload_elements),
		m_DeviceId(device_id)
	{
	}

protected:
	void Notify(boost::signals2::signal<typename NotificationBase<typename PayloadTypes<DEVICE_ID>::NotificationSignature>::NotificationCallback>& signal) final
	{
		signal(std::make_pair(m_DeviceId, m_ElementsMap));
	}

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;

protected:
	typename Types::ElementMap m_ElementsMap;
	typename Types::DeviceId m_DeviceId;
};

#endif // NOTIFICATION_PUBLISHPAYLOAD_H

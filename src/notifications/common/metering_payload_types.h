#ifndef METERING_PAYLOAD_TYPES_H
#define METERING_PAYLOAD_TYPES_H

#include <date/date.h>

#include <any>
#include <initializer_list>
#include <sstream>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"

struct streamable_any : private std::any
{
	void(*streamer)(std::ostream&, streamable_any const&) = nullptr;
	friend std::ostream& operator<<(std::ostream& os, streamable_any const& a)
	{
		a.streamer(os, a);
		return os;
	}
	template<class T, std::enable_if_t<!std::is_same<std::decay_t<T>, streamable_any>{}, bool> = true>
	streamable_any(T && t) : std::any(std::forward<T>(t)), streamer([](std::ostream& os, streamable_any const& self)
		{
			os << std::any_cast<std::decay_t<T>>(self);
		})
	{
	}
	template<std::enable_if_t<!std::is_same<std::decay_t<uint8_t>, streamable_any>{}, bool> = true>
	streamable_any(uint8_t && t) : std::any(std::forward<uint8_t>(t)), streamer([](std::ostream& os, streamable_any const& self)
		{
			// In above template, the uint8_t type gets cast to a char (e.g. 100 = d, 90 = Z, and so forth)...don't do that.
			os << std::to_string(std::any_cast<uint8_t>(self));
		})
	{
	}
	template<std::enable_if_t<!std::is_same<std::decay_t<std::chrono::time_point<std::chrono::system_clock>>, streamable_any>{}, bool> = true>
	streamable_any(std::chrono::time_point<std::chrono::system_clock>&& t) : std::any(std::forward<std::chrono::time_point<std::chrono::system_clock>>(t)), streamer([](std::ostream& os, streamable_any const& self)
		{
			using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

			// <sigh> why didn't the C++17 standard allow iostreams support for <chrono>
			os << std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(self);
		})
	{
	}
};

using MeteringPayload_DeviceId = EthernetMacId;
using MeteringPayload_ElementMap = std::unordered_map<std::string, streamable_any>;
using MeteringPayload_Element = MeteringPayload_ElementMap::value_type;
using MeteringPayload = std::pair<MeteringPayload_DeviceId, MeteringPayload_ElementMap>;

#endif // METERING_PAYLOAD_TYPES_H

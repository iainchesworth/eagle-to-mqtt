#include <date/date.h>

#include <string>

#include "notifications/common/streamable_any.h"

template<>
streamable_any::streamable_any(uint8_t&& t) : 
	std::any(std::move(t)), 
	streamer([](std::ostream& os, streamable_any const& self)
	{
		// In above template, the uint8_t type gets cast to a char (e.g. 100 = d, 90 = Z, and so forth)...don't do that.
		os << std::to_string(std::any_cast<uint8_t>(self));
	})
{
}

template<>
streamable_any::streamable_any(std::chrono::time_point<std::chrono::system_clock>&& t) : 
	std::any(std::move(t)),
	streamer([](std::ostream& os, streamable_any const& self)
	{
		using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

		// <sigh> why didn't the C++17 standard allow iostreams support for <chrono>
		os << std::any_cast<std::chrono::time_point<std::chrono::system_clock>>(self);
	})
{
}

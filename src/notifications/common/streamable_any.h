#ifndef STREAMABLE_ANY_H
#define STREAMABLE_ANY_H

#include <any>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <typeindex>

struct streamable_any : public std::any
{
	void(*streamer)(std::ostream&, streamable_any const&) = nullptr;
	friend std::ostream& operator<<(std::ostream& os, streamable_any const& a)
	{
		a.streamer(os, a);
		return os;
	}

	template<class T, std::enable_if_t<!std::is_same<std::decay_t<T>, streamable_any>{}, bool> = true>
	streamable_any(T&& t) : std::any(std::forward<T>(t)), streamer([](std::ostream& os, streamable_any const& self)
		{
			os << std::any_cast<std::decay_t<T>>(self);
		})
	{
	}
};

template<>
streamable_any::streamable_any(uint8_t&& t);
template<>
streamable_any::streamable_any(std::chrono::time_point<std::chrono::system_clock>&& t);

#endif // STREAMABLE_ANY_H

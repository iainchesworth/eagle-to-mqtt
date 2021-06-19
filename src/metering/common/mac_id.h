#ifndef MAC_ID_H
#define MAC_ID_H

#include <boost/log/trivial.hpp>

#include <array>
#include <cstdint>
#include <string>

#include "metering/common/unit_converters.h"

template<std::size_t ADDRESS_ELEMENTS>
class MacId
{
	const uint32_t DEVICE_MAC_ID_STRING_LENGTH = (ADDRESS_ELEMENTS * 2) + 2;	// Format expected as "0xFFFFFFFF...."
	const std::array<uint8_t, ADDRESS_ELEMENTS> UNKNOWN_DEVICE_MACID { 0x00 };	// Default initialised to zero.

public:
	explicit MacId() :
		m_DeviceMacId{ UNKNOWN_DEVICE_MACID }
	{
	}

	MacId(const std::string& device_mac_id) :
		m_DeviceMacId{ UNKNOWN_DEVICE_MACID }
	{
		if (DEVICE_MAC_ID_STRING_LENGTH != device_mac_id.length())
		{
			BOOST_LOG_TRIVIAL(warning) << L"Invalid Device MAC Id value; length incorrect - was " << device_mac_id.length() << L"; expected " << DEVICE_MAC_ID_STRING_LENGTH;
		}
		else if (0 != device_mac_id.compare(0, 2, "0x"))
		{
			BOOST_LOG_TRIVIAL(warning) << L"Invalid Device MAC Id format received";
		}
		else
		{
			const auto trimmed = device_mac_id.substr(2);

			for (uint32_t elem_count = 0; elem_count < ADDRESS_ELEMENTS; elem_count += 2)
			{
				const std::string::const_iterator it_start = trimmed.begin() + (elem_count * 2);
				const std::string::const_iterator it_end = (it_start + 1);

				m_DeviceMacId[elem_count] = hex_string_to_uint8_t(std::string(it_start, it_end));
			}
		}
	}

	~MacId()
	{
	}

public:
	MacId(const MacId& other) :
		m_DeviceMacId(other.m_DeviceMacId)
	{
	}

	MacId(MacId&& other) noexcept :
		m_DeviceMacId(std::exchange(other.m_DeviceMacId, UNKNOWN_DEVICE_MACID))
	{
	}

public:
	MacId& operator=(const MacId& other)
	{
		return *this = MacId(other);
	}

	MacId& operator=(MacId&& other) noexcept
	{
		std::swap(m_DeviceMacId, other.m_DeviceMacId);
		return *this;
	}

protected:
	std::array<uint8_t, ADDRESS_ELEMENTS> m_DeviceMacId;
};

#endif // DEVICE_MAC_ID_H

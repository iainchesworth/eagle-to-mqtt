#ifndef MAC_ID_H
#define MAC_ID_H

#include <boost/log/trivial.hpp>

#include <array>
#include <cstdint>
#include <ostream>
#include <string>
#include <tuple>

#include "exceptions/invalid_message_value.h"
#include "metering/common/unit_converters.h"

template<std::size_t ADDRESS_ELEMENTS>
class MacId
{
	const uint32_t DEVICE_MAC_ID_STRING_LENGTH = (ADDRESS_ELEMENTS * 2) + 2;	// Format expected as "0xFFFFFFFF...."
	static constexpr std::array<uint8_t, ADDRESS_ELEMENTS> UNKNOWN_DEVICE_MACID { 0x00 };	// Default initialised to zero.

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
			throw InvalidMessageValue("Mac Id - incorrect length - got " + std::to_string(device_mac_id.length()));
		}
		else if (0 != device_mac_id.compare(0, 2, "0x"))
		{
			BOOST_LOG_TRIVIAL(warning) << L"Invalid Device MAC Id format received";
			throw InvalidMessageValue("Mac Id - incorrect format");
		}
		else
		{
			for (auto [string_elem, array_elem] = std::tuple{ 2, 0 }; array_elem < ADDRESS_ELEMENTS; string_elem += 2, ++array_elem)
			{
				const auto char_seq = std::string(device_mac_id.begin() + string_elem, device_mac_id.begin() + string_elem + 2);
				m_DeviceMacId[array_elem] = std::stoi(char_seq, nullptr, 16);
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

public:
	bool operator==(const MacId<ADDRESS_ELEMENTS>& other) const
	{
		return (m_DeviceMacId == other.m_DeviceMacId);
	}

public:
	bool IsValid() const
	{
		return (UNKNOWN_DEVICE_MACID != m_DeviceMacId);
	}

protected:
	std::array<uint8_t, ADDRESS_ELEMENTS> m_DeviceMacId;

public:
	friend std::ostream& operator<<(std::ostream& os, const MacId<ADDRESS_ELEMENTS>& mac_id)
	{
		for (uint32_t i = 0; i < mac_id.m_DeviceMacId.size(); ++i)
		{
			os << mac_id.m_DeviceMacId[i];

			if ((mac_id.m_DeviceMacId.size() - 1) > i)
			{
				os << ":";
			}
		}

		return os;
	}
};

#endif // DEVICE_MAC_ID_H

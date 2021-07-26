#ifndef MAC_ID_H
#define MAC_ID_H

#include <boost/log/trivial.hpp>

#include <array>
#include <cstdint>
#include <iomanip>
#include <ostream>
#include <string>
#include <string_view>
#include <tuple>

#include "exceptions/invalid_message_value.h"
#include "metering/common/unit_converters.h"

template<std::size_t ADDRESS_ELEMENTS>
class MacId
{
	static const uint32_t DEVICE_MAC_ID_STRING_LENGTH = (ADDRESS_ELEMENTS * 2) + 2;	// Format expected as "0xFFFFFFFF...."
	static constexpr std::array<uint8_t, ADDRESS_ELEMENTS> UNKNOWN_DEVICE_MACID { 0x00 };	// Default initialised to zero.

public:
	explicit MacId() = default;

	explicit MacId(const std::string& device_mac_id) :
		MacId(FromString(device_mac_id))
	{
	}

public:
	MacId<ADDRESS_ELEMENTS> FromString(const std::string_view& device_mac_id)
	{
		MacId<ADDRESS_ELEMENTS> mac_id;

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
			try
			{
				for (auto [string_elem, array_elem] = std::tuple{ 2, 0 }; array_elem < ADDRESS_ELEMENTS; string_elem += 2, ++array_elem)
				{
					const auto char_seq = std::string(device_mac_id.begin() + string_elem, device_mac_id.begin() + string_elem + 2);
					mac_id.m_DeviceMacId[array_elem] = std::stoi(char_seq, nullptr, 16);
				}
			}
			catch (const std::invalid_argument& ex_ia)
			{
				BOOST_LOG_TRIVIAL(warning) << L"Invalid Device MAC Id content received - what(): " << ex_ia.what();
				throw InvalidMessageValue("Mac Id - invalid characters present in string");
			}
		}

		return mac_id;
	}

	static std::string ToString(const MacId<ADDRESS_ELEMENTS>& mac_id)
	{
		static const uint32_t HEX_BUF_STRING_LENGTH = 3; // <CHAR> + <CHAR> + NULL;

		std::ostringstream oss;

		for(uint32_t i = 0; i < ADDRESS_ELEMENTS; ++i)
		{
			char hex_value_buffer[HEX_BUF_STRING_LENGTH] = { 0 };

			std::snprintf(hex_value_buffer, HEX_BUF_STRING_LENGTH, "%.2hhX", mac_id.m_DeviceMacId[i]);

			oss << hex_value_buffer;

			if ((mac_id.m_DeviceMacId.size() - 1) > i)
			{
				oss << ":";
			}
		}

		return oss.str();
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
	std::array<uint8_t, ADDRESS_ELEMENTS> DeviceMacId() const
	{
		return m_DeviceMacId;
	}

private:
	std::array<uint8_t, ADDRESS_ELEMENTS> m_DeviceMacId{ UNKNOWN_DEVICE_MACID };
};

#endif // DEVICE_MAC_ID_H

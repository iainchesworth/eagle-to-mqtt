#include <boost/test/unit_test.hpp>

#include <any>
#include <sstream>
#include <string>

#include "test_tools/test_tools_notification_payload_test.h"

void test_tools::NotificationPayload_ValueTester(const EagleNotification_PublishPayload::Types::ElementMap& map, const EagleNotification_PublishPayload::Types::ElementMap::key_type& key, const std::string& value_as_string)
{
	if (const auto& it = map.find(key); map.end() == it)
	{
		BOOST_ERROR(std::string("Missing key in NotificationPayload_ValueTester: ") + key);
	}
	else
	{
		std::stringstream ss;

		if (typeid(uint8_t) == it->second.type())
		{
			ss << std::to_string(std::any_cast<uint8_t>(it->second));
		}
		else
		{
			ss << it->second;
		}

		BOOST_TEST(value_as_string == ss.str());
	}
}

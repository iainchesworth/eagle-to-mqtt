#include <boost/test/unit_test.hpp>

#include <any>
#include <cstdint>

#include "notifications/notification_manager.h"
#include "notifications/common/metering_payload_types.h"
#include "notifications/metering/notification_connectivity.h"

BOOST_AUTO_TEST_SUITE(Notifications);

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity)
{
	try
	{
		const EthernetMacId device_id("0xAABBCCDDEEFF");
		uint32_t notification_received = 0;
		NotificationManager mgr;

		mgr.RegisterCallback< Notification_Connectivity>(
			[&device_id, &notification_received](const MeteringPayload& metering_payload)
			{
				auto test_payload_value = [](const MeteringPayload_ElementMap& map, const MeteringPayload_ElementMap::key_type& key, const std::string& value_as_string)
				{
					if (const auto& it = map.find(key); map.end() == it)
					{
						BOOST_ERROR(std::string("Missing key in Test_NotificationConnectivity: ") + key);
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
				};

				switch (notification_received)
				{
				case 0:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 0);
					break;

				case 1:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 1);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					break;

				case 2:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 2);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					test_payload_value(metering_payload.second, std::string("extended_panid"), std::string("AA:BB:CC:DD:EE:FF:00:11"));
					break;

				case 3:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 3);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					test_payload_value(metering_payload.second, std::string("extended_panid"), std::string("AA:BB:CC:DD:EE:FF:00:11"));
					test_payload_value(metering_payload.second, std::string("link_strength"), std::string("67"));
					break;

				case 4:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 4);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					test_payload_value(metering_payload.second, std::string("extended_panid"), std::string("AA:BB:CC:DD:EE:FF:00:11"));
					test_payload_value(metering_payload.second, std::string("link_strength"), std::string("67"));
					test_payload_value(metering_payload.second, std::string("meter_macid"), std::string("11:00:FF:EE:DD:CC:BB:AA"));
					break;

				case 5:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 5);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					test_payload_value(metering_payload.second, std::string("extended_panid"), std::string("AA:BB:CC:DD:EE:FF:00:11"));
					test_payload_value(metering_payload.second, std::string("link_strength"), std::string("67"));
					test_payload_value(metering_payload.second, std::string("meter_macid"), std::string("11:00:FF:EE:DD:CC:BB:AA"));
					test_payload_value(metering_payload.second, std::string("status"), std::string("Initializing"));
					break;

				case 6:
					BOOST_TEST(metering_payload.first == device_id);
					BOOST_TEST(metering_payload.second.size() == 5);
					test_payload_value(metering_payload.second, std::string("channel"), std::string("TEST_CHANNEL"));
					test_payload_value(metering_payload.second, std::string("extended_panid"), std::string("AA:BB:CC:DD:EE:FF:00:11"));
					test_payload_value(metering_payload.second, std::string("link_strength"), std::string("34"));
					test_payload_value(metering_payload.second, std::string("meter_macid"), std::string("11:00:FF:EE:DD:CC:BB:AA"));
					test_payload_value(metering_payload.second, std::string("status"), std::string("Connected"));
					break;

				default:
					BOOST_ERROR(std::string("Invalid notification count in Test_NotificationConnectivity: ") + std::to_string(notification_received));
					break;
				}

				++notification_received;
			}
		);

		auto connection_status_notif = std::make_shared<Notification_Connectivity>(device_id);

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(0 == notification_received);
		mgr.Poll();
		BOOST_TEST(1 == notification_received);

		(*connection_status_notif)
			.Channel("TEST_CHANNEL");

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(1 == notification_received);
		mgr.Poll();
		BOOST_TEST(2 == notification_received);

		(*connection_status_notif)
			.Extended_PanId(ZigBeeMacId("0xAABBCCDDEEFF0011"));

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(2 == notification_received);
		mgr.Poll();
		BOOST_TEST(3 == notification_received);

		(*connection_status_notif)
			.LinkStrength(67);

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(3 == notification_received);
		mgr.Poll();
		BOOST_TEST(4 == notification_received);

		(*connection_status_notif)
			.Meter_MacId(ZigBeeMacId("0x1100FFEEDDCCBBAA"));

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(4 == notification_received);
		mgr.Poll();
		BOOST_TEST(5 == notification_received);

		(*connection_status_notif)
			.Status(Statuses(Statuses::StatusTypes::Initializing));

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(5 == notification_received);
		mgr.Poll();
		BOOST_TEST(6 == notification_received);

		(*connection_status_notif)
			.LinkStrength(34)
			.Status(Statuses(Statuses::StatusTypes::Connected));

		mgr.Dispatch(connection_status_notif);
		BOOST_TEST(6 == notification_received);
		mgr.Poll();
		BOOST_TEST(7 == notification_received);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

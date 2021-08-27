#include <boost/test/unit_test.hpp>

#include <memory>

#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "notifications/notification_manager.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_connectivity.h"

#include "test_tools/test_tools_notification_payload_test.h"

struct Fixture_NotificationConnectivity
{
	struct LastNotificationPayload
	{
		EagleNotification_PublishPayload::Types::DeviceId device_id;
		EagleNotification_PublishPayload::Types::ElementMap payload;
	};

	LastNotificationPayload last_notification_payload;
	uint32_t notifications_count = 0;

	const EthernetMacId device_id{ std::string("0xAABBCCDDEEFF") };
	const ZigBeeMacId extended_panid{ std::string("0xAABBCCDDEEFF0011") };
	const ZigBeeMacId meter_macid{ std::string("0x1100FFEEDDCCBBAA") };

	std::shared_ptr<Notification_Connectivity> connection_status_notif;
	NotificationManager mgr;

	static const std::string TEST_CHANNEL;

	Fixture_NotificationConnectivity() :
		connection_status_notif{ std::make_shared<Notification_Connectivity>(device_id) }
	{
		mgr.RegisterCallback<Notification_Connectivity>(
			[this](const EagleNotification_PublishPayload::Types::Payload& metering_payload)
			{
				last_notification_payload.device_id = metering_payload.first;
				last_notification_payload.payload = metering_payload.second;

				++notifications_count;
			}
		);
	}
};

const std::string Fixture_NotificationConnectivity::TEST_CHANNEL{ "TEST_CHANNEL" };

BOOST_AUTO_TEST_SUITE(Notifications)

//-----------------------------------------------------------------------------
// 
// Define the test fixture here (as we don't want it set-up, torn down between
// test case executions).
// 
//-----------------------------------------------------------------------------

Fixture_NotificationConnectivity fixture_nc;

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_0)
{
	try
	{
		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(0 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(1 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 0);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_1)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.Channel(Fixture_NotificationConnectivity::TEST_CHANNEL);

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(1 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(2 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 1);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_2)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.Extended_PanId(fixture_nc.extended_panid);

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(2 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(3 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 2);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("extended_panid"), ZigBeeMacId::ToString(fixture_nc.extended_panid));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_3)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.LinkStrength(67);

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(3 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(4 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 3);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("extended_panid"), ZigBeeMacId::ToString(fixture_nc.extended_panid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("link_strength"), std::string("67"));

	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_4)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.Meter_MacId(fixture_nc.meter_macid);

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(4 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(5 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 4);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("extended_panid"), ZigBeeMacId::ToString(fixture_nc.extended_panid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("link_strength"), std::string("67"));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("meter_macid"), ZigBeeMacId::ToString(fixture_nc.meter_macid));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_5)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.Status(Statuses(Statuses::StatusTypes::Initializing));

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(5 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(6 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 5);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("extended_panid"), ZigBeeMacId::ToString(fixture_nc.extended_panid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("link_strength"), std::string("67"));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("meter_macid"), ZigBeeMacId::ToString(fixture_nc.meter_macid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("status"), Statuses::ToString(Statuses::StatusTypes::Initializing));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_NotificationConnectivity_6)
{
	try
	{
		(*(fixture_nc.connection_status_notif))
			.LinkStrength(34)
			.Status(Statuses(Statuses::StatusTypes::Connected));

		fixture_nc.mgr.Dispatch(fixture_nc.connection_status_notif);
		BOOST_TEST(6 == fixture_nc.notifications_count);
		fixture_nc.mgr.Poll();
		BOOST_TEST(7 == fixture_nc.notifications_count);

		BOOST_TEST(fixture_nc.last_notification_payload.device_id == fixture_nc.device_id);
		BOOST_TEST(fixture_nc.last_notification_payload.payload.size() == 5);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("channel"), Fixture_NotificationConnectivity::TEST_CHANNEL);
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("extended_panid"), ZigBeeMacId::ToString(fixture_nc.extended_panid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("link_strength"), std::string("34"));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("meter_macid"), ZigBeeMacId::ToString(fixture_nc.meter_macid));
		test_tools::NotificationPayload_ValueTester(fixture_nc.last_notification_payload.payload, std::string("status"), Statuses::ToString(Statuses::StatusTypes::Connected));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

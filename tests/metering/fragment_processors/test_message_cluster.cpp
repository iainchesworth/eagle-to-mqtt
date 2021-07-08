#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>
#include <string>

#include "metering/fragment_processors/message_cluster.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_time.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<MessageCluster>
<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>
<TimeStamp>0xFFFFFFFF</TimeStamp>
<Id>0xFFFFFFFF</Id>
<Text>{string}</Text>
<Priority>Critical</Priority>
<ConfirmationRequired>N</ConfirmationRequired>
<Confirmed>Y</Confirmed>
<Queue>Cancel Pending</Queue>
</MessageCluster>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<MessageCluster>
 <DeviceMacId>0xd8d5b9000000af85</DeviceMacId>
 <MeterMacId>0xd8d5b900000021a7</MeterMacId>
 <TimeStamp>0x20acaeef</TimeStamp>
 <Id>0x00000000</Id>
 <Text>Welcome to the program</Text>
 <Priority>Low</Priority>
 <StartTime>0x20acad0d</StartTime>
 <Duration>0xffff</Duration>
 <ConfirmationRequired>N</ConfirmationRequired>
 <Confirmed>N</Confirmed>
 <Queue>Active</Queue>
 <Protocol>Zigbee</Protocol>
</MessageCluster>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_MessageCluster)
{
	using namespace test_tools;

	auto v1 = FragmentGenerator(FragmentGenerator::FragmentVersions::V1)
		.AddFragment_MessageCluster()
		.Generate();
	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_MessageCluster()
		.Generate();

	boost::property_tree::ptree v1_messagecluster, v2_messagecluster;
	boost::property_tree::read_xml(v1, v1_messagecluster);
	boost::property_tree::read_xml(v2, v2_messagecluster);

	try
	{
		MessageCluster mc_v1(v1_messagecluster.get_child("rainforest.MessageCluster"));
		MessageCluster mc_v2(v2_messagecluster.get_child("rainforest.MessageCluster"));

		const auto v1_valid_from = std::chrono::system_clock::now();
		const auto v1_valid_till = std::chrono::system_clock::now();

		BOOST_TEST(mc_v1.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(mc_v1.Message().Id() == std::string("0xFFFFFFFF"));
		BOOST_TEST(mc_v1.Message().Text() == std::string("{string}"));
		BOOST_TEST(mc_v1.Message().Priority() == Priorities::PriorityTypes::Critical);
		BOOST_TEST(test_tools::within_60_seconds(mc_v1.Message().ValidFrom(), v1_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(mc_v1.Message().ValidTill(), v1_valid_till));
		BOOST_TEST(mc_v1.Message().ConfirmationRequired() == false);
		BOOST_TEST(mc_v1.Message().IsConfirmed() == true);
		BOOST_TEST(mc_v1.Queue() == Queues::QueueTypes::CancelPending);

		const auto v2_valid_from = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x20acad0d);
		const auto v2_valid_till = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x20acad0d) + std::chrono::minutes(0xffff);

		BOOST_TEST(mc_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000af85"));
		BOOST_TEST(mc_v2.Message().Id() == std::string("0x00000000"));
		BOOST_TEST(mc_v2.Message().Text() == std::string("Welcome to the program"));
		BOOST_TEST(mc_v2.Message().Priority() == Priorities::PriorityTypes::Low);
		BOOST_TEST(test_tools::within_60_seconds(mc_v2.Message().ValidFrom(), v2_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(mc_v2.Message().ValidTill(), v2_valid_till));
		BOOST_TEST(mc_v2.Message().ConfirmationRequired() == false);
		BOOST_TEST(mc_v2.Message().IsConfirmed() == false);
		BOOST_TEST(mc_v2.Queue() == Queues::QueueTypes::Active);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>
#include <string>

#include "metering/devices/rainforest/messages/current_summation.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"

BOOST_AUTO_TEST_SUITE(Rainforest);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<CurrentSummationDelivered>
<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>
<TimeStamp>0xFFFFFFFF</TimeStamp>
<SummationDelivered>0xFFFFFFFF</SummationDelivered>
<SummationReceived>0xFFFFFFFF</SummationReceived>
<Multiplier>0xFFFFFFFF</Multiplier>
<Divisor>0xFFFFFFFF</Divisor>
<DigitsRight>0xFF</DigitsRight>
<DigitsLeft>0xFF</DigitsLeft>
<SuppressLeadingZero>{enumeration}</SuppressLeadingZero>
</CurrentSummationDelivered>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<CurrentSummation>
 <DeviceMacId>0xd8d5b9000000af85</DeviceMacId>
 <MeterMacId>0xd8d5b900000021a7</MeterMacId>
 <TimeStamp>0x20acaec0</TimeStamp>
 <SummationDelivered>0x000000000001f81f</SummationDelivered>
 <SummationReceived>0x0000000000000000</SummationReceived>
 <Multiplier>0x00000001</Multiplier>
 <Divisor>0x000003e8</Divisor>
 <UnitOfMeasure>0x00</UnitOfMeasure>
 <DigitsRight>0x03</DigitsRight>
 <DigitsLeft>0x00</DigitsLeft>
 <SuppressLeadingZero>Y</SuppressLeadingZero>
 <Protocol>Zigbee</Protocol>
</CurrentSummation>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_CurrentSummation, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Summation testing (floating-point)
{
	using namespace test_tools;

	auto v1 = FragmentGenerator(FragmentGenerator::FragmentVersions::V1)
		.AddFragment_CurrentSummation()
		.Generate();
	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_CurrentSummation()
		.Generate();

	boost::property_tree::ptree v1_currentsummation, v2_currentsummation;
	boost::property_tree::read_xml(v1, v1_currentsummation);
	boost::property_tree::read_xml(v2, v2_currentsummation);

	try
	{
		CurrentSummation cs_v1(v1_currentsummation.get_child("rainforest.CurrentSummationDelivered"));
		CurrentSummation cs_v2(v2_currentsummation.get_child("rainforest.CurrentSummation"));

		BOOST_TEST(cs_v1.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(cs_v1.Delivered().value().ValueIn<WattHours>() == 1.0f);
		BOOST_TEST(cs_v1.Received().value().ValueIn<WattHours>() == 1.0f);

		BOOST_TEST(cs_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000af85"));
		BOOST_TEST(cs_v2.Delivered().value().ValueIn<WattHours>() == 129.055f);
		BOOST_TEST(cs_v2.Received().value().ValueIn<WattHours>() == 0.0f);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/current_summation.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

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
	static const std::string V1_HEADER = "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">";
	static const std::string V2_HEADER = "<?xml version=\"1.0\"?><rainforest timestamp=\"0000000000s\" version=\"2.0\" macId=\"0xffffffffffff\">";

	static const std::string V1_BODY = 
		"<CurrentSummationDelivered>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<SummationDelivered>0xFFFFFFFF</SummationDelivered>"
		"<SummationReceived>0xFFFFFFFF</SummationReceived>"
		"<Multiplier>0xFFFFFFFF</Multiplier>"
		"<Divisor>0xFFFFFFFF</Divisor>"
		"<DigitsRight>0xFF</DigitsRight>"
		"<DigitsLeft>0xFF</DigitsLeft>"
		"<SuppressLeadingZero>N</SuppressLeadingZero>"
		"</CurrentSummationDelivered>";
	static const std::string V2_BODY = 
		"<CurrentSummation>"
		"<DeviceMacId>0xd8d5b9000000af85</DeviceMacId>"
		"<MeterMacId>0xd8d5b900000021a7</MeterMacId>"
		"<TimeStamp>0x20acaec0</TimeStamp>"
		"<SummationDelivered>0x000000000001f81f</SummationDelivered>"
		"<SummationReceived>0x0000000000000000</SummationReceived>"
		"<Multiplier>0x00000001</Multiplier>"
		"<Divisor>0x000003e8</Divisor>"
		"<UnitOfMeasure>0x00</UnitOfMeasure>"
		"<DigitsRight>0x03</DigitsRight>"
		"<DigitsLeft>0x00</DigitsLeft>"
		"<SuppressLeadingZero>Y</SuppressLeadingZero>"
		"<Protocol>Zigbee</Protocol>"
		"</CurrentSummation>";

	static const std::string FOOTER = "</rainforest>";

	boost::property_tree::ptree v1_currentsummation, v2_currentsummation;
	std::stringstream v1_iss, v2_iss;

	v1_iss << V1_HEADER << V1_BODY << FOOTER;
	v2_iss << V2_HEADER << V2_BODY << FOOTER;

	boost::property_tree::read_xml(v1_iss, v1_currentsummation);
	boost::property_tree::read_xml(v2_iss, v2_currentsummation);

	try
	{
		CurrentSummation cs_v1(v1_currentsummation.get_child("rainforest.CurrentSummationDelivered"));
		CurrentSummation cs_v2(v2_currentsummation.get_child("rainforest.CurrentSummation"));

		BOOST_TEST(ZigBeeMacId("0xFFFFFFFFFFFFFFFF") == cs_v1.DeviceMacId());
		BOOST_TEST(1.0f == cs_v1.Delivered().EnergyValue());
		BOOST_TEST(1.0f == cs_v1.Received().EnergyValue());

		BOOST_TEST(ZigBeeMacId("0xd8d5b9000000af85") == cs_v2.DeviceMacId());
		BOOST_TEST(129.055f == cs_v2.Delivered().EnergyValue());
		BOOST_TEST(0.0f == cs_v2.Received().EnergyValue());
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

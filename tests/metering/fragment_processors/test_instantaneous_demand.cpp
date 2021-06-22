#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<InstantaneousDemand>
<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>
<TimeStamp>0xFFFFFFFF</TimeStamp>
<Demand>0xFFFFFF</Demand>
<Multiplier>0xFFFFFFFF</Multiplier>
<Divisor>0xFFFFFFFF</Divisor>
<DigitsRight>0xFF</DigitsRight>
<DigitsLeft>0xFF</DigitsLeft>
<SuppressLeadingZero>{enumeration}</SuppressLeadingZero>
</InstantaneousDemand>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<InstantaneousDemand>
 <DeviceMacId>0xd8d5b9000000b74d</DeviceMacId>
 <MeterMacId>0x001d230100402d72</MeterMacId>
 <TimeStamp>0x211cc7a8</TimeStamp>
 <Demand>0x000032</Demand>
 <Multiplier>0x00000001</Multiplier>
 <Divisor>0x000003e8</Divisor>
 <UnitOfMeasure>0x00</UnitOfMeasure>
 <DigitsRight>0x03</DigitsRight>
 <DigitsLeft>0x06</DigitsLeft>
 <SuppressLeadingZero>Y</SuppressLeadingZero>
 <Protocol>Zigbee</Protocol>
</InstantaneousDemand>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_InstantaneousDemand, * boost::unit_test::tolerance(0.00001)) // Tolerance is for Summation testing (floating-point)
{
	static const std::string V1_HEADER = "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">";
	static const std::string V2_HEADER = "<?xml version=\"1.0\"?><rainforest timestamp=\"0000000000s\" version=\"2.0\" macId=\"0xffffffffffff\">";

	static const std::string V1_BODY = 
		"<InstantaneousDemand>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<Demand>0xFFFFFF</Demand>"
		"<Multiplier>0xFFFFFFFF</Multiplier>"
		"<Divisor>0xFFFFFFFF</Divisor>"
		"<DigitsRight>0xFF</DigitsRight>"
		"<DigitsLeft>0xFF</DigitsLeft>"
		"<SuppressLeadingZero>N</SuppressLeadingZero>"
		"</InstantaneousDemand>";
	static const std::string V2_BODY = 
		"<InstantaneousDemand>"
		"<DeviceMacId>0xd8d5b9000000b74d</DeviceMacId>"
		"<MeterMacId>0x001d230100402d72</MeterMacId>"
		"<TimeStamp>0x211cc7a8</TimeStamp>"
		"<Demand>0x000032</Demand>"
		"<Multiplier>0x00000001</Multiplier>"
		"<Divisor>0x000003e8</Divisor>"
		"<UnitOfMeasure>0x00</UnitOfMeasure>"
		"<DigitsRight>0x03</DigitsRight>"
		"<DigitsLeft>0x06</DigitsLeft>"
		"<SuppressLeadingZero>Y</SuppressLeadingZero>"
		"<Protocol>Zigbee</Protocol>"
		"</InstantaneousDemand>";

	static const std::string FOOTER = "</rainforest>";

	boost::property_tree::ptree v1_instantaneousdemand, v2_instantaneousdemand;
	std::stringstream v1_iss, v2_iss;

	v1_iss << V1_HEADER << V1_BODY << FOOTER;
	v2_iss << V2_HEADER << V2_BODY << FOOTER;

	boost::property_tree::read_xml(v1_iss, v1_instantaneousdemand);
	boost::property_tree::read_xml(v2_iss, v2_instantaneousdemand);

	try
	{
		InstantaneousDemand id_v1(v1_instantaneousdemand.get_child("rainforest.InstantaneousDemand"));
		InstantaneousDemand id_v2(v2_instantaneousdemand.get_child("rainforest.InstantaneousDemand"));

		BOOST_TEST(id_v1.DeviceMacId() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(16777215.0f == id_v1.Now().EnergyValue());

		BOOST_TEST(id_v2.DeviceMacId() == ZigBeeMacId("0xd8d5b9000000b74d"));
		BOOST_TEST(0.05f == id_v2.Now().EnergyValue());
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

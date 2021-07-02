#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/common/statuses.h"
#include "metering/fragment_processors/connection_status.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">

//
// NO V1 FRAGMENT FOR THIS MESSAGE TYPE (NetworkInfo was renamed ConnectionStatus)
//

</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<ConnectionStatus>
 <DeviceMacId>0xd8d5b9000000b200</DeviceMacId>
 <MeterMacId>0x000781000081fd0b</MeterMacId>
 <Status>Rejoining</Status>
 <ExtPanId>0x000781000081fd0b</ExtPanId>
 <Channel>14</Channel>
 <ShortAddr>0xd291</ShortAddr>
 <LinkStrength>0x00</LinkStrength>
 <Protocol>Zigbee</Protocol>
</ConnectionStatus>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_ConnectionStatus)
{
	using namespace test_tools;

	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_ConnectionStatus()
		.Generate();

	boost::property_tree::ptree v2_connectionstatus;
	boost::property_tree::read_xml(v2, v2_connectionstatus);

	try
	{
		ConnectionStatus cs_v2(v2_connectionstatus.get_child("rainforest.ConnectionStatus"));

		BOOST_TEST(cs_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000b200"));
		BOOST_TEST(cs_v2.Meter_MacId().value() == ZigBeeMacId("0x000781000081fd0b"));
		BOOST_TEST(cs_v2.ShortAddr().value() == std::string("0xd291"));
		BOOST_TEST(cs_v2.Status().value() == Statuses::StatusTypes::AuthenticatingSuccess);
		BOOST_TEST(cs_v2.Channel().value() == std::string("14"));
		BOOST_TEST(cs_v2.LinkStrength().value() == 0);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/network_info.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<NetworkInfo>
 <DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
 <CoordMacId>0xFFFFFFFFFFFFFFFF</CoordMacId>
 <Status>{enumeration}</Status>
 [<Description>{string}</Description>]
 [<StatusCode>0xFF</StatusCode>]
 [<ExtPanId>0xFFFFFFFFFFFFFFFF</ExtPanId>]
 [<Channel>00</Channel>]
 [<ShortAddr>0xFFFF</ShortAddr>]
 <LinkStrength>0xFF</LinkStrength>
</NetworkInfo>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">

//
// NO V2 FRAGMENT FOR THIS MESSAGE TYPE (NetworkInfo was renamed ConnectionStatus)
//

</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_NetworkInfo)
{
	using namespace test_tools;

	auto v1 = FragmentGenerator(FragmentGenerator::FragmentVersions::V1)
		.AddFragment_NetworkInfo()
		.Generate();

	boost::property_tree::ptree v1_networkinfo;
	boost::property_tree::read_xml(v1, v1_networkinfo);

	try
	{
		NetworkInfo ni_v1(v1_networkinfo.get_child("rainforest.NetworkInfo"));

		BOOST_TEST(ni_v1.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(ni_v1.CoordinatorZigbeeId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(ni_v1.Status().value() == Statuses::StatusTypes::JoinSuccess);
		BOOST_TEST(ni_v1.StatusCode().value() == 255);
		BOOST_TEST(ni_v1.Channel().value() == "00");
		BOOST_TEST(ni_v1.LinkStrength().value() == 255);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

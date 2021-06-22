#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/network_info.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

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
	static const std::string V1_HEADER = "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">";
	static const std::string V1_BODY = 
		"<NetworkInfo>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<CoordMacId>0xFFFFFFFFFFFFFFFF</CoordMacId>"
		"<Status>Join: Success</Status>"
		"<Description>{string}</Description>"
		"<StatusCode>0xFF</StatusCode>"
		"<ExtPanId>0xFFFFFFFFFFFFFFFF</ExtPanId>"
		"<Channel>00</Channel>"
		"<ShortAddr>0xFFFF</ShortAddr>"
		"<LinkStrength>0xFF</LinkStrength>"
		"</NetworkInfo>";
	static const std::string FOOTER = "</rainforest>";

	boost::property_tree::ptree v1_networkinfo;
	std::stringstream v1_iss, v2_iss;

	v1_iss << V1_HEADER << V1_BODY << FOOTER;

	boost::property_tree::read_xml(v1_iss, v1_networkinfo);

	try
	{
		NetworkInfo ni_v1(v1_networkinfo.get_child("rainforest.NetworkInfo"));

		BOOST_TEST(ni_v1.DeviceMacId() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(ni_v1.CoordinatorZigbeeId() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(ni_v1.Status() == Statuses::StatusTypes::JoinSuccess);
		BOOST_TEST(ni_v1.StatusCode() == 255);
		BOOST_TEST(ni_v1.Channel() == "00");
		BOOST_TEST(ni_v1.LinkStrength() == 255);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/fragment_processors/price_cluster.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<PriceCluster>
<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>
<TimeStamp>0xFFFFFFFF</TimeStamp>
<Price>0xFFFFFFFF</Price>
<Currency>0xFFFF</Currency>
<TrailingDigits>0xFF</TrailingDigits>
<Tier>00</Tier>
[<TierLabel>{string}</TierLabel> | <RateLabel>{string}</RateLabel>]
</PriceCluster>
</rainforest>

<?xml version="1.0"?>
<rainforest timestamp="0000000000s" version="2.0" macId="0xffffffffffff">
<PriceCluster>
<DeviceMacId>0xd8d5b9000000fca8</DeviceMacId>
<MeterMacId>0x00078100005a499f</MeterMacId>
<TimeStamp>0x24e5ffd8</TimeStamp>
<Price>0x00000005</Price>
<Currency>0x0348</Currency>
<TrailingDigits>0x02</TrailingDigits>
<Tier>0x01</Tier>
<StartTime>0x24e60010</StartTime>
<Duration>0xffff</Duration>
<RateLabel>Price1</RateLabel>
<Protocol>Zigbee</Protocol>
</PriceCluster>
</rainforest>

*/

BOOST_AUTO_TEST_CASE(Test_PriceCluster, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Pricing testing (floating-point)
{
	static const std::string V1_HEADER = "<?xml version=\"1.0\"?><rainforest macId=\"0xffffffffffff\" version=\"undefined\" timestamp=\"0000000000s\">";
	static const std::string V2_HEADER = "<?xml version=\"1.0\"?><rainforest timestamp=\"0000000000s\" version=\"2.0\" macId=\"0xffffffffffff\">";

	static const std::string V1_BODY = 
		"<PriceCluster>"
		"<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>"
		"<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>"
		"<TimeStamp>0xFFFFFFFF</TimeStamp>"
		"<Price>0xFFFFFFFF</Price>"
		"<Currency>0x03E7</Currency>"
		"<TrailingDigits>0x02</TrailingDigits>"
		"<Tier>00</Tier>"
		"<TierLabel>{string}</TierLabel>"
		"<RateLabel>{string}</RateLabel>"
		"</PriceCluster>";
	static const std::string V2_BODY = "<PriceCluster>"
		"<DeviceMacId>0xd8d5b9000000fca8</DeviceMacId>"
		"<MeterMacId>0x00078100005a499f</MeterMacId>"
		"<TimeStamp>0x24e5ffd8</TimeStamp>"
		"<Price>0x00000005</Price>"
		"<Currency>0x0348</Currency>"
		"<TrailingDigits>0x01</TrailingDigits>"
		"<Tier>0x01</Tier>"
		"<StartTime>0x24e60010</StartTime>"
		"<Duration>0xffff</Duration>"
		"<RateLabel>Price1</RateLabel>"
		"<Protocol>Zigbee</Protocol>"
		"</PriceCluster>";

	static const std::string FOOTER = "</rainforest>";

	boost::property_tree::ptree v1_pricecluster, v2_pricecluster;
	std::stringstream v1_iss, v2_iss;

	v1_iss << V1_HEADER << V1_BODY << FOOTER;
	v2_iss << V2_HEADER << V2_BODY << FOOTER;

	boost::property_tree::read_xml(v1_iss, v1_pricecluster);
	boost::property_tree::read_xml(v2_iss, v2_pricecluster);

	try
	{
		PriceCluster pc_v1(v1_pricecluster.get_child("rainforest.PriceCluster"));
		PriceCluster pc_v2(v2_pricecluster.get_child("rainforest.PriceCluster"));

		BOOST_TEST(pc_v1.DeviceMacId() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1.TierPricing().Pricing().Currency() == CurrencyCodes::ISO4127_CurrencyCodes::XXX);
		BOOST_TEST(pc_v1.TierPricing().Pricing().Price() == 0.01f);
		BOOST_TEST(pc_v1.Tier() == Tiers::SupportedTiers::Unknown);

		BOOST_TEST(pc_v2.DeviceMacId() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2.TierPricing().Pricing().Currency() == CurrencyCodes::ISO4127_CurrencyCodes::USD);
		BOOST_TEST(pc_v2.TierPricing().Pricing().Price() == 0.5f);
		BOOST_TEST(pc_v2.Tier() == Tiers::SupportedTiers::Tier_1);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

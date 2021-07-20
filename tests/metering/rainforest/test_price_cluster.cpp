#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>
#include <string>

#include "metering/devices/rainforest/messages/price_cluster.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_time.h"

BOOST_AUTO_TEST_SUITE(Rainforest);

/*

<?xml version="1.0"?>
<rainforest macId="0xffffffffffff" version="undefined" timestamp="0000000000s">
<PriceCluster>
<DeviceMacId>0xFFFFFFFFFFFFFFFF</DeviceMacId>
<MeterMacId>0xFFFFFFFFFFFFFFFF</MeterMacId>
<TimeStamp>0xFFFFFFFF</TimeStamp>
<Price>0x000003E8</Price>
<Currency>0x0348</Currency>
<TrailingDigits>0x02</TrailingDigits>
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
	using namespace test_tools;
	
	auto v1 = FragmentGenerator(FragmentGenerator::FragmentVersions::V1)
		.AddFragment_PriceCluster()
		.Generate();
	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_PriceCluster()
		.Generate();

	boost::property_tree::ptree v1_pricecluster, v2_pricecluster;
	boost::property_tree::read_xml(v1, v1_pricecluster);
	boost::property_tree::read_xml(v2, v2_pricecluster);

	try
	{
		PriceCluster pc_v1(v1_pricecluster.get_child("rainforest.PriceCluster"));
		PriceCluster pc_v2(v2_pricecluster.get_child("rainforest.PriceCluster"));

		const auto v1_valid_from = std::chrono::system_clock::now();
		const auto v1_valid_till = std::chrono::system_clock::now();

		BOOST_TEST(pc_v1.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(pc_v1.TierPricing().Pricing().Price() == 10.0f);
		BOOST_TEST(pc_v1.Tier() == Tiers::SupportedTiers::Unknown);
		BOOST_TEST(test_tools::within_60_seconds(pc_v1.TierPricing().StartsAt(), v1_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(pc_v1.TierPricing().EndsAt(), v1_valid_till));

		const auto v2_valid_from = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x24e60010);
		const auto v2_valid_till = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x24e60010) + std::chrono::minutes(0xffff);

		BOOST_TEST(pc_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v2.TierPricing().Pricing().Price() == 0.5f);
		BOOST_TEST(pc_v2.Tier() == Tiers::SupportedTiers::Tier_1);
		BOOST_TEST(test_tools::within_60_seconds(pc_v2.TierPricing().StartsAt(), v2_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(pc_v2.TierPricing().EndsAt(), v2_valid_till));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

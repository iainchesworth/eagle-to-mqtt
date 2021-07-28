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
		BOOST_TEST(pc_v1.Tier() == Tiers(Tiers::SupportedTiers::Unknown));
		BOOST_TEST(test_tools::within_60_seconds(pc_v1.TierPricing().StartsAt(), v1_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(pc_v1.TierPricing().EndsAt(), v1_valid_till));

		const auto v2_valid_from = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x24e60010);
		const auto v2_valid_till = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x24e60010) + std::chrono::minutes(0xffff);

		BOOST_TEST(pc_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v2.TierPricing().Pricing().Price() == 0.5f);
		BOOST_TEST(pc_v2.Tier() == Tiers(Tiers::SupportedTiers::Tier_1));
		BOOST_TEST(test_tools::within_60_seconds(pc_v2.TierPricing().StartsAt(), v2_valid_from));
		BOOST_TEST(test_tools::within_60_seconds(pc_v2.TierPricing().EndsAt(), v2_valid_till));
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_AllPriceTiers, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Pricing testing (floating-point)
{
	using namespace test_tools;

	auto v1 = FragmentGenerator(FragmentGenerator::FragmentVersions::V1)
		.AddFragment_PriceCluster("0x00000001", "0x00000101", "0x0024", "0x00", "0x01", "", "", "Tier 1", "Rate 1")
		.AddFragment_PriceCluster("0x00000002", "0x00000202", "0x0348", "0x01", "0x02", "", "", "Tier 2", "Rate 2")
		.AddFragment_PriceCluster("0x00000003", "0x00000303", "0x03E7", "0x02", "0x03", "", "", "Tier 3", "Rate 3")
		.AddFragment_PriceCluster("0x00000004", "0x00000404", "0x0348", "0x03", "0x04", "", "", "Tier 4", "Rate 4")
		.AddFragment_PriceCluster("0x00000005", "0x00000505", "0x0024", "0x04", "0x05", "", "", "Tier 5", "Rate 5")
		.Generate();
	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_PriceCluster("0x00000001", "0x00000101", "0x0024", "0x00", "0x01", "0x24e50000", "0x0010", "", "Rate 1")
		.AddFragment_PriceCluster("0x00000002", "0x00000202", "0x0348", "0x01", "0x02", "0x24e60000", "0x0020", "", "Rate 2")
		.AddFragment_PriceCluster("0x00000003", "0x00000303", "0x03E7", "0x02", "0x03", "0x24e70000", "0x0030", "", "Rate 3")
		.AddFragment_PriceCluster("0x00000004", "0x00000404", "0x0348", "0x03", "0x04", "0x24e80000", "0x0040", "", "Rate 4")
		.AddFragment_PriceCluster("0x00000005", "0x00000505", "0x0024", "0x04", "0x05", "0x24e90000", "0x0050", "", "Rate 5")
		.Generate();

	boost::property_tree::ptree v1_pricecluster, v2_pricecluster;
	boost::property_tree::read_xml(v1, v1_pricecluster);
	boost::property_tree::read_xml(v2, v2_pricecluster);

	try
	{
		auto& price_cluster_nodes_v1 = v1_pricecluster.get_child("rainforest");
		auto pcn_v1_it = price_cluster_nodes_v1.begin();

		++pcn_v1_it; // Skip any <XMLATTR> fields.

		PriceCluster pc_v1_tier1((*pcn_v1_it).second);
		BOOST_TEST(pc_v1_tier1.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1_tier1.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(pc_v1_tier1.TierPricing().RateLabel() == std::string("Rate 1"));
		BOOST_TEST(pc_v1_tier1.Tier() == Tiers(Tiers::SupportedTiers::Tier_1));
		++pcn_v1_it;

		PriceCluster pc_v1_tier2((*pcn_v1_it).second);
		BOOST_TEST(pc_v1_tier2.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1_tier2.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v1_tier2.TierPricing().RateLabel() == std::string("Rate 2"));
		BOOST_TEST(pc_v1_tier2.Tier() == Tiers(Tiers::SupportedTiers::Tier_2));
		++pcn_v1_it;

		PriceCluster pc_v1_tier3((*pcn_v1_it).second);
		BOOST_TEST(pc_v1_tier3.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1_tier3.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(pc_v1_tier3.TierPricing().RateLabel() == std::string("Rate 3"));
		BOOST_TEST(pc_v1_tier3.Tier() == Tiers(Tiers::SupportedTiers::Tier_3));
		++pcn_v1_it;

		PriceCluster pc_v1_tier4((*pcn_v1_it).second);
		BOOST_TEST(pc_v1_tier4.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1_tier4.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v1_tier4.TierPricing().RateLabel() == std::string("Rate 4"));
		BOOST_TEST(pc_v1_tier4.Tier() == Tiers(Tiers::SupportedTiers::Tier_4));
		++pcn_v1_it;

		PriceCluster pc_v1_tier5((*pcn_v1_it).second);
		BOOST_TEST(pc_v1_tier5.DeviceMacId().value() == ZigBeeMacId("0xFFFFFFFFFFFFFFFF"));
		BOOST_TEST(pc_v1_tier5.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(pc_v1_tier5.TierPricing().RateLabel() == std::string("Rate 5"));
		BOOST_TEST(pc_v1_tier5.Tier() == Tiers(Tiers::SupportedTiers::Tier_5));
		++pcn_v1_it;

		bool no_more_elements_v1 = (price_cluster_nodes_v1.end() == pcn_v1_it);
		BOOST_TEST(no_more_elements_v1);

		auto& price_cluster_nodes_v2 = v2_pricecluster.get_child("rainforest");
		auto pcn_v2_it = price_cluster_nodes_v2.begin();

		++pcn_v2_it; // Skip any <XMLATTR> fields.

		PriceCluster pc_v2_tier1((*pcn_v2_it).second);
		BOOST_TEST(pc_v2_tier1.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2_tier1.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(pc_v2_tier1.TierPricing().RateLabel() == std::string("Rate 1"));
		BOOST_TEST(pc_v2_tier1.Tier() == Tiers(Tiers::SupportedTiers::Tier_1));
		++pcn_v2_it;

		PriceCluster pc_v2_tier2((*pcn_v2_it).second);
		BOOST_TEST(pc_v2_tier2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2_tier2.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v2_tier2.TierPricing().RateLabel() == std::string("Rate 2"));
		BOOST_TEST(pc_v2_tier2.Tier() == Tiers(Tiers::SupportedTiers::Tier_2));
		++pcn_v2_it;

		PriceCluster pc_v2_tier3((*pcn_v2_it).second);
		BOOST_TEST(pc_v2_tier3.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2_tier3.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(pc_v2_tier3.TierPricing().RateLabel() == std::string("Rate 3"));
		BOOST_TEST(pc_v2_tier3.Tier() == Tiers(Tiers::SupportedTiers::Tier_3));
		++pcn_v2_it;

		PriceCluster pc_v2_tier4((*pcn_v2_it).second);
		BOOST_TEST(pc_v2_tier4.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2_tier4.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(pc_v2_tier4.TierPricing().RateLabel() == std::string("Rate 4"));
		BOOST_TEST(pc_v2_tier4.Tier() == Tiers(Tiers::SupportedTiers::Tier_4));
		++pcn_v2_it;

		PriceCluster pc_v2_tier5((*pcn_v2_it).second);
		BOOST_TEST(pc_v2_tier5.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000fca8"));
		BOOST_TEST(pc_v2_tier5.TierPricing().Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(pc_v2_tier5.TierPricing().RateLabel() == std::string("Rate 5"));
		BOOST_TEST(pc_v2_tier5.Tier() == Tiers(Tiers::SupportedTiers::Tier_5));
		++pcn_v2_it;

		bool no_more_elements_v2 = (price_cluster_nodes_v2.end() == pcn_v2_it);
		BOOST_TEST(no_more_elements_v2);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <stdexcept>

#include "metering/common/unit_converters.h"
#include "metering/device_registry.h"
#include "metering/devices/rainforest/eagle-200/eagle_200.h"

#include "test_tools/test_tools_fragment_generator.h"

BOOST_AUTO_TEST_SUITE(Eagle200_DataModel);

BOOST_AUTO_TEST_CASE(Test_DemandHistory)
{
	using namespace test_tools;

	try
	{
		static const std::string TIMEPOINT_1 = "0x00000001";
		static const std::string TIMEPOINT_2 = "0x00000002";
		static const std::string TIMEPOINT_3 = "0x00000003";
		static const std::string TIMEPOINT_4 = "0x00000004";
		static const std::string TIMEPOINT_5 = "0x00000005";

		auto base_device = DeviceRegistrySingleton()->GetOrCreate<Eagle200>(EthernetMacId("0xF57625CDDBF7"));
		auto test_device = std::dynamic_pointer_cast<Eagle200>(base_device);
		
		{
			auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
				.AddFragment_CurrentSummation()
				.AddFragment_InstantaneousDemand(TIMEPOINT_1, "0x00000001", "0x00000000", "0x00000000")
				.AddFragment_InstantaneousDemand(TIMEPOINT_2, "0x00000010", "0x00000000", "0x00000000")
				.AddFragment_InstantaneousDemand(TIMEPOINT_3, "0x00000100", "0x00000000", "0x00000000")
				.Generate();

			boost::property_tree::ptree payload;
			boost::property_tree::read_xml(raw_payload, payload);
			test_device->ProcessPayload(payload);
		}

		// Deducing which overload to use (const vs. non-const) is based on the const'ness of *this.
		const auto const_device = std::dynamic_pointer_cast<const Eagle200>(base_device);

		BOOST_TEST(const_device->EnergyUsage().History.size() == 3);

		BOOST_TEST(1 == const_device->EnergyUsage().History[0].second.ValueIn<Watts>());
		BOOST_TEST(16 == const_device->EnergyUsage().History[1].second.ValueIn<Watts>());
		BOOST_TEST(256 == const_device->EnergyUsage().History[2].second.ValueIn<Watts>());

		{
			// NOTE THAT THESE ELEMENTS ARE DELIBERATELY OUT OF ORDER

			auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
				.AddFragment_InstantaneousDemand(TIMEPOINT_5, "0x00010000", "0x00000000", "0x00000000")
				.AddFragment_InstantaneousDemand(TIMEPOINT_4, "0x00001000", "0x00000000", "0x00000000")
				.Generate();

			boost::property_tree::ptree payload;
			boost::property_tree::read_xml(raw_payload, payload);
			test_device->ProcessPayload(payload);
		}

		BOOST_TEST(const_device->EnergyUsage().History.size() == 5);

		// NOTE THAT THE TESTED ELEMENTS ARE DELIBERATELY OUT OF ORDER

		BOOST_TEST(4096 == const_device->EnergyUsage().History[4].second.ValueIn<Watts>());
		BOOST_TEST(65536 == const_device->EnergyUsage().History[3].second.ValueIn<Watts>());
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_CASE(Test_TieredPricing, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Pricing testing (floating-point)
{
	using namespace test_tools;

	try
	{
		auto base_device = DeviceRegistrySingleton()->GetOrCreate<Eagle200>(EthernetMacId("0x75AFD6920098"));
		auto test_device = std::dynamic_pointer_cast<Eagle200>(base_device);

		{
			auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
				.AddFragment_PriceCluster("0x00000001", "0x00000101", "0x0024", "0x00", "0x01", "0x24e50000", "0x0010", "", "Rate 1")
				.AddFragment_PriceCluster("0x00000002", "0x00000202", "0x0348", "0x01", "0x02", "0x24e60000", "0x0020", "", "Rate 2")
				.AddFragment_PriceCluster("0x00000003", "0x00000303", "0x03E7", "0x02", "0x03", "0x24e70000", "0x0030", "", "Rate 3")
				.Generate();

			boost::property_tree::ptree payload;
			boost::property_tree::read_xml(raw_payload, payload);
			test_device->ProcessPayload(payload);
		}

		BOOST_TEST(test_device->PriceTiers().size() == 3);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::NotSpecified)).RateLabel(), std::out_of_range);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).RateLabel() == std::string("Rate 1"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Price() == 257.0f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).RateLabel() == std::string("Rate 2"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Price() == 51.4f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).RateLabel() == std::string("Rate 3"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Price() == 7.71f);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).RateLabel(), std::out_of_range);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).RateLabel(), std::out_of_range);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Unknown)).RateLabel(), std::out_of_range);

		{
			// NOTE THAT THESE ELEMENTS ARE DELIBERATELY OUT OF ORDER

			auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
				.AddFragment_PriceCluster("0x00000005", "0x00000505", "0x0024", "0x04", "0x05", "0x24e90000", "0x0050", "", "Rate 5")
				.AddFragment_PriceCluster("0x00000004", "0x00000404", "0x0348", "0x03", "0x04", "0x24e80000", "0x0040", "", "Rate 4")
				.Generate();

			boost::property_tree::ptree payload;
			boost::property_tree::read_xml(raw_payload, payload);
			test_device->ProcessPayload(payload);
		}

		BOOST_TEST(test_device->PriceTiers().size() == 5);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::NotSpecified)).RateLabel(), std::out_of_range);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).RateLabel() == std::string("Rate 1"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Price() == 257.0f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).RateLabel() == std::string("Rate 2"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Price() == 51.40f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).RateLabel() == std::string("Rate 3"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Price() == 7.71f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).RateLabel() == std::string("Rate 4"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).Pricing().Price() == 1.028f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).RateLabel() == std::string("Rate 5"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).Pricing().Price() == 0.1285f);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Unknown)).RateLabel(), std::out_of_range);

		{
			auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
				.AddFragment_PriceCluster("0x00000006", "0x00000606", "0x0024", "0x01", "0x01", "0x24e50000", "0x0010", "", "Rate 1 - Updated")
				.AddFragment_PriceCluster("0x00000007", "0x00000707", "0x0348", "0x01", "0x02", "0x24e60000", "0x0020", "", "Rate 2 - Updated")
				.AddFragment_PriceCluster("0x00000008", "0x00000808", "0x03E7", "0x01", "0x03", "0x24e70000", "0x0030", "", "Rate 3 - Updated")
				.Generate();

			boost::property_tree::ptree payload;
			boost::property_tree::read_xml(raw_payload, payload);
			test_device->ProcessPayload(payload);
		}

		BOOST_TEST(test_device->PriceTiers().size() == 5);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::NotSpecified)).RateLabel(), std::out_of_range);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).RateLabel() == std::string("Rate 1 - Updated"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_1)).Pricing().Price() == 154.2f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).RateLabel() == std::string("Rate 2 - Updated"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_2)).Pricing().Price() == 179.9f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).RateLabel() == std::string("Rate 3 - Updated"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::XXX));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_3)).Pricing().Price() == 205.6f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).RateLabel() == std::string("Rate 4"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::USD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_4)).Pricing().Price() == 1.028f);
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).RateLabel() == std::string("Rate 5"));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).Pricing().Currency() == CurrencyCodes(CurrencyCodes::ISO4127_CurrencyCodes::AUD));
		BOOST_TEST(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Tier_5)).Pricing().Price() == 0.1285f);
		BOOST_CHECK_THROW(test_device->PriceTiers().at(Tiers(Tiers::SupportedTiers::Unknown)).RateLabel(), std::out_of_range);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

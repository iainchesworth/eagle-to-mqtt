#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>

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

		BOOST_TEST(test_device->EnergyUsage().History.size() == 3);

		BOOST_TEST(1 == test_device->EnergyUsage().History[0].second.EnergyValue());
		BOOST_TEST(16 == test_device->EnergyUsage().History[1].second.EnergyValue());
		BOOST_TEST(256 == test_device->EnergyUsage().History[2].second.EnergyValue());

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

		BOOST_TEST(test_device->EnergyUsage().History.size() == 5);

		// NOTE THAT THE TESTED ELEMENTS ARE DELIBERATELY OUT OF ORDER

		BOOST_TEST(4096 == test_device->EnergyUsage().History[4].second.EnergyValue());
		BOOST_TEST(65536 == test_device->EnergyUsage().History[3].second.EnergyValue());
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "metering/common/statuses.h"
#include "metering/fragment_processors/billing_period_list.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_time.h"
#include "test_tools/test_tools_zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

BOOST_AUTO_TEST_CASE(Test_BillingPeriodList)
{
	using namespace test_tools;

	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_BillingPeriodList()
		.Generate();

	boost::property_tree::ptree v2_billingperiodlist;
	boost::property_tree::read_xml(v2, v2_billingperiodlist);

	try
	{
		BillingPeriodList bpl_v2(v2_billingperiodlist.get_child("rainforest.BillingPeriodList"));

		const auto v2_current_period_start = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x28518880);
		const auto v2_current_period_end = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x28518880) + std::chrono::minutes(0x3983db9);

		BOOST_TEST(bpl_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000ff7c"));
		BOOST_TEST(test_tools::within_60_seconds(bpl_v2.CurrentPeriodStart(), v2_current_period_start));
		BOOST_TEST(test_tools::within_60_seconds(bpl_v2.CurrentPeriodEnd(), v2_current_period_end));
		BOOST_TEST(bpl_v2.NumberOfPeriods() == 0);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();
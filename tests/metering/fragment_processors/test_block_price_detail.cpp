#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>
#include <sstream>
#include <string>

#include "metering/common/statuses.h"
#include "metering/fragment_processors/block_price_detail.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_fragment_generator.h"
#include "test_tools/test_tools_time.h"

BOOST_AUTO_TEST_SUITE(FragmentProcessors);

BOOST_AUTO_TEST_CASE(Test_BlockPriceDetail, *boost::unit_test::tolerance(0.00001)) // Tolerance is for Pricing testing (floating-point)
{
	using namespace test_tools;

	auto v2 = FragmentGenerator(FragmentGenerator::FragmentVersions::V2)
		.AddFragment_BlockPriceDetail()
		.Generate();

	boost::property_tree::ptree v2_blockpricedetail;
	boost::property_tree::read_xml(v2, v2_blockpricedetail);

	try
	{
		BlockPriceDetail bpd_v2(v2_blockpricedetail.get_child("rainforest.BlockPriceDetail"));

		const auto v2_block_start = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x00000000);
		const auto v2_block_end = std::chrono::system_clock::now() + std::chrono::duration<uint32_t>(0x00000000) + std::chrono::minutes(0x0000);

		BOOST_TEST(bpd_v2.DeviceMacId().value() == ZigBeeMacId("0xd8d5b9000000ff7c"));
		BOOST_TEST(test_tools::within_60_seconds(bpd_v2.CurrentBlock().Starts(), v2_block_start));
		BOOST_TEST(test_tools::within_60_seconds(bpd_v2.CurrentBlock().Ends(), v2_block_end));
		BOOST_TEST(bpd_v2.CurrentBlock().Consumption() == 0.0f);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

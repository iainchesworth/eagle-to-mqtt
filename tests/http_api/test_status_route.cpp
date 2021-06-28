#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include "metering/device_registry.h"
#include "metering/devices/eagle-200/eagle_200.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "upload-api/routes/status.h"

#include "test_tools/test_tools_fragment_generator.h"

BOOST_AUTO_TEST_SUITE(HTTP_API);

BOOST_AUTO_TEST_CASE(Test_StatusRoute)
{
	auto test_device = CheckRegistryAndGetOrCreate<Eagle200>(EthernetMacId("0xaabbccddeeff"));
	auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
		.AddFragment_ConnectionStatus()
		.AddFragment_CurrentSummation()
		.AddFragment_DeviceInfo()
		.AddFragment_InstantaneousDemand()
		.AddFragment_MessageCluster()
		.AddFragment_PriceCluster()
		.Generate();

	boost::property_tree::ptree payload;
	boost::property_tree::read_xml(raw_payload, payload);
	test_device->ProcessPayload(payload);

	boost::beast::http::request<boost::beast::http::dynamic_body> req;
	auto res = Status(req);
}

BOOST_AUTO_TEST_SUITE_END();

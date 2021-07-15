#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/test/unit_test.hpp>

#include <exception>

#include "metering/device_registry.h"
#include "metering/devices/rainforest/eagle-200/eagle_200.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "upload-api/routes/status.h"

#include "test_tools/test_tools_fragment_generator.h"

BOOST_AUTO_TEST_SUITE(HTTP_API);

BOOST_AUTO_TEST_CASE(Test_StatusRoute)
{
	try
	{
		auto test_device = DeviceRegistrySingleton()->GetOrCreate<Eagle200>(EthernetMacId("0x19F95BEA87DE"));
		auto raw_payload = test_tools::FragmentGenerator(test_tools::FragmentGenerator::FragmentVersions::V2)
			.AddFragment_ConnectionStatus()
			.AddFragment_CurrentSummation()
			.AddFragment_DeviceInfo()
			.AddFragment_InstantaneousDemand("0x211cc7a8", "0x000032", "0x00000001", "0x000003e8")
			.AddFragment_InstantaneousDemand("0x211cc7a9", "0x000033", "0x00000001", "0x000003e8")
			.AddFragment_InstantaneousDemand("0x211cc7aa", "0x000034", "0x00000001", "0x000003e8")
			.AddFragment_InstantaneousDemand("0x211cc7ab", "0x000035", "0x00000001", "0x000003e8")
			.AddFragment_MessageCluster()
			.AddFragment_PriceCluster()
			.Generate();

		boost::property_tree::ptree payload;
		boost::property_tree::read_xml(raw_payload, payload);
		test_device->ProcessPayload(payload);

		boost::beast::http::request<boost::beast::http::dynamic_body> req;
		auto res = Status(req);
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/test/unit_test.hpp>

#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"

#include "test_tools/test_tools_ethernet_mac_id.h"

BOOST_AUTO_TEST_SUITE(Conversion);

BOOST_AUTO_TEST_CASE(Test_EthernetMacId_ToString)
{
	try
	{
		BOOST_REQUIRE_THROW(EthernetMacId("12345678901234"),     InvalidMessageValue); // Invalid format (not 0x123456789012)
		BOOST_REQUIRE_THROW(EthernetMacId("0x1234567890"),       InvalidMessageValue); // Invalid length (too short)
		BOOST_REQUIRE_THROW(EthernetMacId("0x1234567890123456"), InvalidMessageValue); // Invalid length (too long)
		BOOST_REQUIRE_THROW(EthernetMacId("This is a test"),     InvalidMessageValue); // Invalid format (not a number; good length; bad format)
		BOOST_REQUIRE_THROW(EthernetMacId("0xis is a test"),     InvalidMessageValue); // Invalid format (not a number; good length; good format)
		BOOST_REQUIRE_THROW(EthernetMacId(""),                   InvalidMessageValue); // Invalid length (empty string)
		
		EthernetMacId test_defaultctor;
		EthernetMacId test_validhexstring("0xAABBCCDDEEFF");
		EthernetMacId test_validintstring("0x123456789012");

		BOOST_TEST(EthernetMacId::ToString(test_defaultctor) == "00:00:00:00:00:00");
		BOOST_TEST(EthernetMacId::ToString(test_validhexstring) == "AA:BB:CC:DD:EE:FF");
		BOOST_TEST(EthernetMacId::ToString(test_validintstring) == "12:34:56:78:90:12");
	}
	catch (const std::exception ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

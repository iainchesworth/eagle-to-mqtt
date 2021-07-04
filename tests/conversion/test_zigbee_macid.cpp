#include <boost/test/unit_test.hpp>

#include <exception>

#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

#include "test_tools/test_tools_zigbee_mac_id.h"

BOOST_AUTO_TEST_SUITE(Conversion);

BOOST_AUTO_TEST_CASE(Test_ZigBeeMacId_ToString)
{
	try
	{
		BOOST_REQUIRE_THROW(ZigBeeMacId("123456789012345678"),   InvalidMessageValue); // Invalid format (not 0x1234567890123456)
		BOOST_REQUIRE_THROW(ZigBeeMacId("0x123456789012"),	     InvalidMessageValue); // Invalid length (too short)
		BOOST_REQUIRE_THROW(ZigBeeMacId("0x123456789012345678"), InvalidMessageValue); // Invalid length (too long)
		BOOST_REQUIRE_THROW(ZigBeeMacId("This is a test val"),   InvalidMessageValue); // Invalid format (not a number; good length; bad format)
		BOOST_REQUIRE_THROW(ZigBeeMacId("0xis is a test val"),   InvalidMessageValue); // Invalid format (not a number; good length; good format)
		BOOST_REQUIRE_THROW(ZigBeeMacId(""),                     InvalidMessageValue); // Invalid length (empty string)

		ZigBeeMacId test_defaultctor;
		ZigBeeMacId test_validhexstring("0xAABBCCDDEEFF1122");
		ZigBeeMacId test_validintstring("0x1234567890123456");

		BOOST_TEST(ZigBeeMacId::ToString(test_defaultctor) == "00:00:00:00:00:00:00:00");
		BOOST_TEST(ZigBeeMacId::ToString(test_validhexstring) == "AA:BB:CC:DD:EE:FF:11:22");
		BOOST_TEST(ZigBeeMacId::ToString(test_validintstring) == "12:34:56:78:90:12:34:56");
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

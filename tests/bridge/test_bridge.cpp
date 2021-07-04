#include <boost/test/unit_test.hpp>

#include <exception>

#include "bridge/bridge.h"

BOOST_AUTO_TEST_SUITE(BridgeService);

BOOST_AUTO_TEST_CASE(Test_TBC)
{
	try
	{
	}
	catch (const std::exception& ex)
	{
		BOOST_ERROR(std::string("Unexpected exception while performing test: ") + ex.what());
	}
}

BOOST_AUTO_TEST_SUITE_END();

#ifndef EXPECTED_H
#define EXPECTED_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <functional>
#include <stdexcept>
#include <string>

#include "exceptions/missing_message_key.h"

template<typename FIELD_TYPE, typename GETTER_FUNC>
FIELD_TYPE IsExpected(GETTER_FUNC getter_func, FIELD_TYPE default_value = FIELD_TYPE())
{
	try
	{
		// Attempt to retrieve the "expected" value...
		return getter_func();
	}
	catch (const std::invalid_argument& ia)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (std::invalid_argument) while retrieving expected field - what(): " << ia.what();
	}
	catch (const boost::property_tree::ptree_error& pterr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (boost::property_tree::ptree_error) while retrieving expected field - what(): " << pterr.what();
	}
	catch (const MissingMessageKey& mmk)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (MissingMessageKey - " << mmk.MissingKey() << L") while retrieving expected field - what() : " << mmk.what();
		BOOST_LOG_TRIVIAL(debug) << L"Eagle Bug: Expected field is missing (refer to Uploader API documentation)";
	}

	return default_value;
}

#endif // EXPECTED_H

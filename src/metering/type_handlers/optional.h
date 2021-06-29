#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <functional>

#include "exceptions/missing_message_key.h"

template<typename FIELD_TYPE, typename GETTER_FUNC>
FIELD_TYPE IsOptional(GETTER_FUNC getter_func, FIELD_TYPE default_value = FIELD_TYPE())
{
	try
	{
		// Attempt to retrieve the "optional" value...return the default in the event of failure.
		return getter_func();
	}
	catch (const std::invalid_argument& ia)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Exception (std::invalid_argument) while retrieving optional field - what(): " << ia.what();
	}
	catch (const boost::property_tree::ptree_error& pterr)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Exception (boost::property_tree::ptree_error) while retrieving optional field - what(): " << pterr.what();
	}
	catch (const MissingMessageKey& mmk)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Exception (MissingMessageKey - " << mmk.MissingKey() << L") while retrieving optional field - what(): " << mmk.what();
	}

	return default_value;
}

#endif // OPTIONAL_H

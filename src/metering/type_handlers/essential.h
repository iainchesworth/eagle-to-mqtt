#ifndef ESSENTIAL_H
#define ESSENTIAL_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <functional>
#include <stdexcept>
#include <string>

#include "exceptions/missing_message_key.h"

template<typename FIELD_TYPE>
FIELD_TYPE IsEssential(std::function<FIELD_TYPE()> getter_func)
{
	try
	{
		// Attempt to retrieve the "essential" value...
		return getter_func();
	}
	catch (const std::invalid_argument& ia)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (std::invalid_argument) while retrieving essential field - what(): " << ia.what();
		throw;
	}
	catch (const boost::property_tree::ptree_error& pterr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (boost::property_tree::ptree_error) while retrieving essential field - what(): " << pterr.what();
		throw;
	}
	catch (const MissingMessageKey& mmk)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception (MissingMessageKey) while retrieving essential field - what(): " << mmk.what();
		throw;
	}
}

#endif // ESSENTIAL_H

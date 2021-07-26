#ifndef PRESENCE_HELPERS_H
#define PRESENCE_HELPERS_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <functional>
#include <optional>
#include <string>

#include "exceptions/missing_message_key.h"
#include "exceptions/not_implemented.h"

// Forward Declarations
class CurrencyCodes;
class EthernetMacId;
class Priorities;
class Protocols;
class Queues;
class Statuses;
class Tiers;
class Usage;
class ZigBeeMacId;
class ZigbeeTimepoint;

namespace PresenseHelpers
{

//=====================================================================================================================
//
// EXPECTED -> Helpers to attempt and retrieve fields that may/may not exist in a fragment being processed.
//

template<typename FIELD_TYPE, typename GETTER_FUNC>
FIELD_TYPE RetrieveValue(GETTER_FUNC getter)
{
	try
	{
		// Attempt to retrieve the "expected" value; on failure, the exception is propagated up.
		return FIELD_TYPE(getter());

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
		BOOST_LOG_TRIVIAL(warning) << L"Exception (MissingMessageKey - " << mmk.MissingKey() << L") while retrieving essential field - what() : " << mmk.what();
		throw;
	}
}

template<typename FIELD_TYPE>
FIELD_TYPE RetrieveValue(const boost::property_tree::ptree& node, const std::string& field)
{
	throw NotImplemented();
}
template<>
std::string RetrieveValue<std::string>(const boost::property_tree::ptree& node, const std::string& field);
template<>
bool RetrieveValue<bool>(const boost::property_tree::ptree& node, const std::string& field);
template<>
double RetrieveValue<double>(const boost::property_tree::ptree& node, const std::string& field);
template<>
uint8_t RetrieveValue<uint8_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
uint16_t RetrieveValue<uint16_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
uint32_t RetrieveValue<uint32_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
uint64_t RetrieveValue<uint64_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
int8_t RetrieveValue<int8_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
int16_t RetrieveValue<int16_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
int32_t RetrieveValue<int32_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
int64_t RetrieveValue<int64_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
CurrencyCodes RetrieveValue<CurrencyCodes>(const boost::property_tree::ptree& node, const std::string& field);
template<>
EthernetMacId RetrieveValue<EthernetMacId>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Priorities RetrieveValue<Priorities>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Protocols RetrieveValue<Protocols>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Queues RetrieveValue<Queues>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Statuses RetrieveValue<Statuses>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Tiers RetrieveValue<Tiers>(const boost::property_tree::ptree& node, const std::string& field);
template<>
Usage RetrieveValue<Usage>(const boost::property_tree::ptree& node, const std::string& field);
template<>
ZigBeeMacId RetrieveValue<ZigBeeMacId>(const boost::property_tree::ptree& node, const std::string& field);
template<>
ZigbeeTimepoint RetrieveValue<ZigbeeTimepoint>(const boost::property_tree::ptree& node, const std::string& field);

//=====================================================================================================================
//
// OPTIONAL -> Helpers to attempt and retrieve fields that may/may not exist in a fragment being processed.
//

template<typename FIELD_TYPE, typename GETTER_FUNC>
std::optional<FIELD_TYPE> TryAndRetrieveValue(GETTER_FUNC getter)
{
	std::optional<FIELD_TYPE> optional_value;

	try
	{
		// Attempt to retrieve the "optional" value; on failure, the "un-initialised" optional is returned.
		optional_value = FIELD_TYPE(getter());

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

	return optional_value;
}

template<typename FIELD_TYPE>
std::optional<FIELD_TYPE> TryAndRetrieveValue(const boost::property_tree::ptree& node, const std::string& field)
{
	throw NotImplemented();
}
template<>
std::optional<std::string> TryAndRetrieveValue<std::string>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<bool> TryAndRetrieveValue<bool>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<double> TryAndRetrieveValue<double>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<uint8_t> TryAndRetrieveValue<uint8_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<uint16_t> TryAndRetrieveValue<uint16_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<uint32_t> TryAndRetrieveValue<uint32_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<uint64_t> TryAndRetrieveValue<uint64_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<int8_t> TryAndRetrieveValue<int8_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<int16_t> TryAndRetrieveValue<int16_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<int32_t> TryAndRetrieveValue<int32_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<int64_t> TryAndRetrieveValue<int64_t>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<CurrencyCodes> TryAndRetrieveValue<CurrencyCodes>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<EthernetMacId> TryAndRetrieveValue<EthernetMacId>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Priorities> TryAndRetrieveValue<Priorities>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Protocols> TryAndRetrieveValue<Protocols>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Queues> TryAndRetrieveValue<Queues>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Statuses> TryAndRetrieveValue<Statuses>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Tiers> TryAndRetrieveValue<Tiers>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<Usage> TryAndRetrieveValue<Usage>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<ZigBeeMacId> TryAndRetrieveValue<ZigBeeMacId>(const boost::property_tree::ptree& node, const std::string& field);
template<>
std::optional<ZigbeeTimepoint> TryAndRetrieveValue<ZigbeeTimepoint>(const boost::property_tree::ptree& node, const std::string& field);

}
// namespace PresenseHelpers

#endif // PRESENCE_HELPERS_H

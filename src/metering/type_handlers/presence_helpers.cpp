#include "metering/common/currency_codes.h"
#include "metering/common/priorities.h"
#include "metering/common/protocols.h"
#include "metering/common/queues.h"
#include "metering/common/statuses.h"
#include "metering/type_handlers/boolean.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/presence_helpers.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "metering/fragment_processors/partial_fragment_types/pricing_tier.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

//=====================================================================================================================
//
// EXPECTED -> Helpers to attempt and retrieve fields that may/may not exist in a fragment being processed.
//

template<>
std::string PresenseHelpers::RetrieveValue<std::string>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<std::string>([&node, &field]() { return node.get<std::string>(field); });
}
template<>
bool PresenseHelpers::RetrieveValue<bool>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<bool>([&node, &field]() { return GetValue_Boolean(node, field); });
}
template<>
double PresenseHelpers::RetrieveValue<double>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<double>([&node, &field]() { return node.get<double>(field); });
}
template<>
uint8_t PresenseHelpers::RetrieveValue<uint8_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<uint8_t>([&node, &field]() { return GetValue_UInt8(node, field); });
}
template<>
uint16_t PresenseHelpers::RetrieveValue<uint16_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<uint16_t>([&node, &field]() { return GetValue_UInt16(node, field); });
}
template<>
uint32_t PresenseHelpers::RetrieveValue<uint32_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<uint32_t>([&node, &field]() { return GetValue_UInt32(node, field); });
}
template<>
uint64_t PresenseHelpers::RetrieveValue<uint64_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<uint64_t>([&node, &field]() { return GetValue_UInt64(node, field); });
}
template<>
int8_t PresenseHelpers::RetrieveValue<int8_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<int8_t>([&node, &field]() { return GetValue_Int8(node, field); });
}
template<>
int16_t PresenseHelpers::RetrieveValue<int16_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<int16_t>([&node, &field]() { return GetValue_Int16(node, field); });
}
template<>
int32_t PresenseHelpers::RetrieveValue<int32_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<int32_t>([&node, &field]() { return GetValue_Int32(node, field); });
}
template<>
int64_t PresenseHelpers::RetrieveValue<int64_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<int64_t>([&node, &field]() { return GetValue_Int64(node, field); });
}
template<>
CurrencyCodes PresenseHelpers::RetrieveValue<CurrencyCodes>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<CurrencyCodes>([&node, &field]() { return node.get<CurrencyCodes>(field, CurrencyCodes::PropertyTreeTranslator()); });
}
template<>
EthernetMacId PresenseHelpers::RetrieveValue<EthernetMacId>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<EthernetMacId>([&node, &field]() { return node.get<EthernetMacId>(field, EthernetMacId::PropertyTreeTranslator()); });
}
template<>
Priorities PresenseHelpers::RetrieveValue<Priorities>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Priorities>([&node, &field]() { return Priorities::FromString(node.get<std::string>(field)); });
}
template<>
Protocols PresenseHelpers::RetrieveValue<Protocols>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Protocols>([&node, &field]() { return Protocols::FromString(node.get<std::string>(field)); });
}
template<>
Queues PresenseHelpers::RetrieveValue<Queues>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Queues>([&node, &field]() { return Queues::FromString(node.get<std::string>(field)); });
}
template<>
Statuses PresenseHelpers::RetrieveValue<Statuses>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Statuses>([&node, &field]() { return Statuses::FromString(node.get<std::string>(field)); });
}
template<>
Summation PresenseHelpers::RetrieveValue<Summation>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Summation>([&node, &field]() { return Summation::ExtractFromPayload(node, field); });
}
template<>
Tiers PresenseHelpers::RetrieveValue<Tiers>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<Tiers>([&node, &field]() { return Tiers::FromString(node.get<std::string>(field)); });
}
template<>
ZigBeeMacId PresenseHelpers::RetrieveValue<ZigBeeMacId>(const boost::property_tree::ptree& node, const std::string& field)
{
	return RetrieveValue<ZigBeeMacId>([&node, &field]() { return node.get<ZigBeeMacId>(field, ZigBeeMacId::PropertyTreeTranslator()); });
}

//=====================================================================================================================
//
// OPTIONAL -> Helpers to attempt and retrieve fields that may/may not exist in a fragment being processed.
//

template<>
std::optional<std::string> PresenseHelpers::TryAndRetrieveValue<std::string>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<std::string>([&node, &field]() { return node.get<std::string>(field); });
}
template<>
std::optional<bool> PresenseHelpers::TryAndRetrieveValue<bool>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<bool>([&node, &field]() { return GetValue_Boolean(node, field); });
}
template<>
std::optional<double> PresenseHelpers::TryAndRetrieveValue<double>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<double>([&node, &field]() { return node.get<double>(field); });
}
template<>
std::optional<uint8_t> PresenseHelpers::TryAndRetrieveValue<uint8_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<uint8_t>([&node, &field]() { return GetValue_UInt8(node, field); });
}
template<>
std::optional<uint16_t> PresenseHelpers::TryAndRetrieveValue<uint16_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<uint16_t>([&node, &field]() { return GetValue_UInt16(node, field); });
}
template<>
std::optional<uint32_t> PresenseHelpers::TryAndRetrieveValue<uint32_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<uint32_t>([&node, &field]() { return GetValue_UInt32(node, field); });
}
template<>
std::optional<uint64_t> PresenseHelpers::TryAndRetrieveValue<uint64_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<uint64_t>([&node, &field]() { return GetValue_UInt64(node, field); });
}
template<>
std::optional<int8_t> PresenseHelpers::TryAndRetrieveValue<int8_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<int8_t>([&node, &field]() { return GetValue_Int8(node, field); });
}
template<>
std::optional<int16_t> PresenseHelpers::TryAndRetrieveValue<int16_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<int16_t>([&node, &field]() { return GetValue_Int16(node, field); });
}
template<>
std::optional<int32_t> PresenseHelpers::TryAndRetrieveValue<int32_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<int32_t>([&node, &field]() { return GetValue_Int32(node, field); });
}
template<>
std::optional<int64_t> PresenseHelpers::TryAndRetrieveValue<int64_t>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<int64_t>([&node, &field]() { return GetValue_Int64(node, field); });
}
template<>
std::optional<CurrencyCodes> PresenseHelpers::TryAndRetrieveValue<CurrencyCodes>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<CurrencyCodes>([&node, &field]() { return node.get<CurrencyCodes>(field, CurrencyCodes::PropertyTreeTranslator()); });
}
template<>
std::optional<EthernetMacId> PresenseHelpers::TryAndRetrieveValue<EthernetMacId>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<EthernetMacId>([&node, &field]() { return node.get<EthernetMacId>(field, EthernetMacId::PropertyTreeTranslator()); });
}
template<>
std::optional<Priorities> PresenseHelpers::TryAndRetrieveValue<Priorities>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Priorities>([&node, &field]() { return Priorities::FromString(node.get<std::string>(field)); });
}
template<>
std::optional<Protocols> PresenseHelpers::TryAndRetrieveValue<Protocols>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Protocols>([&node, &field]() { return Protocols::FromString(node.get<std::string>(field)); });
}
template<>
std::optional<Queues> PresenseHelpers::TryAndRetrieveValue<Queues>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Queues>([&node, &field]() { return Queues::FromString(node.get<std::string>(field)); });
}
template<>
std::optional<Statuses> PresenseHelpers::TryAndRetrieveValue<Statuses>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Statuses>([&node, &field]() { return Statuses::FromString(node.get<std::string>(field)); });
}
template<>
std::optional<Summation> PresenseHelpers::TryAndRetrieveValue<Summation>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Summation>([&node, &field]() { return Summation::ExtractFromPayload(node, field); });
}
template<>
std::optional<Tiers> PresenseHelpers::TryAndRetrieveValue<Tiers>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<Tiers>([&node, &field]() { return Tiers::FromString(node.get<std::string>(field)); });
}
template<>
std::optional<ZigBeeMacId> PresenseHelpers::TryAndRetrieveValue<ZigBeeMacId>(const boost::property_tree::ptree& node, const std::string& field)
{
	return TryAndRetrieveValue<ZigBeeMacId>([&node, &field]() { return node.get<ZigBeeMacId>(field, ZigBeeMacId::PropertyTreeTranslator()); });
}

#ifndef COLLECTION_H
#define COLLECTION_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "exceptions/invalid_unitsofmeasure_value.h"
#include "metering/common/units_of_measure.h"

using NamedCollectionElementId = uint32_t;

template<typename FIELD_TYPE>
using NamedCollectionElement = std::pair<NamedCollectionElementId, FIELD_TYPE>;

template<typename FIELD_TYPE>
using NamedCollectionVector = std::vector<NamedCollectionElement<FIELD_TYPE>>;

template<typename FIELD_TYPE>
struct NamedCollection
{
	UnitsOfMeasure Units;
	NamedCollectionVector<FIELD_TYPE> Values;
};

template<typename FIELD_TYPE>
NamedCollection<FIELD_TYPE> Collection(const boost::property_tree::ptree& node, const std::string& field)
{
	try
	{
		const std::string field_units{ field + ".Unit" };
		const std::string field_values{ field + ".Values" };

		NamedCollection<FIELD_TYPE> collection;

		auto X = node.get<std::string>(field_units);
		collection.Units = UnitsOfMeasure(UnitsOfMeasure::FromString(X));

		for (const auto& [key, child_node] : node.get_child(field_values))
		{
			collection.Values.push_back(std::make_pair(NamedCollectionElementId(std::stoi(key)), child_node.template get_value<FIELD_TYPE>()));
		}

		return collection;
	}
	catch (const std::invalid_argument& ex_ia)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Failed while processing integer string - exception was: " << ex_ia.what();
		throw;
	}
	catch (const boost::property_tree::ptree_error& ex_pte)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Missing field while trying to decode NamedCollection - exception was: " << ex_pte.what();
		throw;
	}
	catch (const InvalidUnitsOfMeasureValue& iuomv_ex)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Unknown units of measure while decoding NamedCollection";
		throw;
	}
}

#endif // COLLECTION_H

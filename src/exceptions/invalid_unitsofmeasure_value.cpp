#include "exceptions/invalid_unitsofmeasure_value.h"

InvalidUnitsOfMeasureValue::InvalidUnitsOfMeasureValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

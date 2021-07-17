#include "exceptions/invalid_unitsofmeasure_value.h"

InvalidUnitsOfMeasureValue::InvalidUnitsOfMeasureValue(std::string reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

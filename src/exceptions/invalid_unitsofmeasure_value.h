#ifndef INVALID_UNITSOFMEASURE_VALUE_H
#define INVALID_UNITSOFMEASURE_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidUnitsOfMeasureValue : public InvalidValue
{
public:
	explicit InvalidUnitsOfMeasureValue(const std::string& reason_for_invalid_value);
};

#endif // INVALID_UNITSOFMEASURE_VALUE_H

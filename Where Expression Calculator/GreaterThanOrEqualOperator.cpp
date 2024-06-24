#include "GreaterThanOrEqualOperator.h"

GreaterThanOrEqualOperator::GreaterThanOrEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* GreaterThanOrEqualOperator::clone() const
{
	return new GreaterThanOrEqualOperator(*this);
}

bool GreaterThanOrEqualOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField >= stringedCompareValue);
}

#include "LessThanOrEqualOperator.h"

LessThanOrEqualOperator::LessThanOrEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* LessThanOrEqualOperator::clone() const
{
	return new LessThanOrEqualOperator(*this);
}

bool LessThanOrEqualOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField <= stringedCompareValue);
}

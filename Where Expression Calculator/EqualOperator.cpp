#include "EqualOperator.h"

EqualOperator::EqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* EqualOperator::clone() const
{
	return new EqualOperator(*this);
}

bool EqualOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField == stringedCompareValue);
}

#include "NotEqualOperator.h"

NotEqualOperator::NotEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* NotEqualOperator::clone() const
{
	return new NotEqualOperator(*this);
}

bool NotEqualOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField != stringedCompareValue);
}

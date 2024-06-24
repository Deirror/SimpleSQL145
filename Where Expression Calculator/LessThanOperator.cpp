#include "LessThanOperator.h"

LessThanOperator::LessThanOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* LessThanOperator::clone() const
{
	return new LessThanOperator(*this);
}

bool LessThanOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField < stringedCompareValue);
}

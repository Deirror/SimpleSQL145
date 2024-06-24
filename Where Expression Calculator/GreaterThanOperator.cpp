#include "GreaterThanOperator.h"

GreaterThanOperator::GreaterThanOperator(const PolymorphicPointer<SQLType>&  _toCompareWith)
	: ComparisonOperator(_toCompareWith)
{
}

ComparisonOperator* GreaterThanOperator::clone() const
{
	return new GreaterThanOperator(*this);
}

bool GreaterThanOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	ComparisonOperator::evalulate(field);

	if (field->getType() == '\0')
		return false;

	String stringedField = stringFieldWithType(field);

	String stringedCompareValue = stringFieldWithType(toCompareWith);

	return (stringedField > stringedCompareValue);
}

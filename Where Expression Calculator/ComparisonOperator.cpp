#include "ComparisonOperator.h"

ComparisonOperator::ComparisonOperator(const PolymorphicPointer<SQLType>& _toCompareWith)
{
	if (!_toCompareWith)
		throw std::invalid_argument("Nullptr");

	toCompareWith = _toCompareWith;
}

bool ComparisonOperator::evalulate(const PolymorphicPointer<SQLType>& field) const
{
	if (!field)
		throw std::invalid_argument("Nullptr");

	if (toCompareWith->getType() != field->getType() && field->getType() != '\0')
		throw std::invalid_argument("Not equal types, cannot compare!");

	return true;
}

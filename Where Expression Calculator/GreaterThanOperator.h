#pragma once
#include "ComparisonOperator.h"

class GreaterThanOperator : public ComparisonOperator
{
public:
	GreaterThanOperator() = default;

	GreaterThanOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const override;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};


#pragma once
#include "ComparisonOperator.h"

class GreaterThanOrEqualOperator : public ComparisonOperator
{
public:
	GreaterThanOrEqualOperator() = default;

	GreaterThanOrEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const override;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};


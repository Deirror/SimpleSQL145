#pragma once
#include "ComparisonOperator.h"

class LessThanOrEqualOperator : public ComparisonOperator
{
public:
	LessThanOrEqualOperator() = default;

	LessThanOrEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const override;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};


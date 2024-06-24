#pragma once
#include "ComparisonOperator.h"

class NotEqualOperator : public ComparisonOperator
{
public:
	NotEqualOperator() = default;

	NotEqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const override;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};


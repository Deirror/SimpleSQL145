#pragma once
#include "ComparisonOperator.h"

class LessThanOperator : public ComparisonOperator
{
public:
	LessThanOperator() = default;

	LessThanOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const override;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};


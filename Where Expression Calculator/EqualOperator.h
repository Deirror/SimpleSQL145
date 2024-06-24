#pragma once
#include "ComparisonOperator.h"

class EqualOperator : public ComparisonOperator
{
public:
	EqualOperator() = default;

	EqualOperator(const PolymorphicPointer<SQLType>& _toCompareWith);

	ComparisonOperator* clone() const;

	bool evalulate(const PolymorphicPointer<SQLType>& field) const override;
};
#pragma once
#include "PolymorphicPointer.hpp"
#include "helperFunctions.h"

class ComparisonOperator
{
protected:
	PolymorphicPointer<SQLType> toCompareWith;

public:
	ComparisonOperator() = default;

	ComparisonOperator(const PolymorphicPointer<SQLType>& field);

	virtual bool evalulate(const PolymorphicPointer<SQLType>& field) const = 0;

	virtual ComparisonOperator* clone() const = 0;

	virtual ~ComparisonOperator() = default;
};


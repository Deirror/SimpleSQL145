#pragma once
#include "ComparisonOperator.h"

ComparisonOperator* comparisonOperatorFactory(const String& compOperator, const PolymorphicPointer<SQLType>& value);


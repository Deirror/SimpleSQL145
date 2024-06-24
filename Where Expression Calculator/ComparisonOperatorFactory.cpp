#include "ComparisonOperatorFactory.h"
#include "EqualOperator.h"
#include "GreaterThanOperator.h"
#include "GreaterThanOrEqualOperator.h"
#include "LessThanOperator.h"
#include "LessThanOrEqualOperator.h"
#include "NotEqualOperator.h"

namespace Operators
{
    constexpr short operatorsSize = 6;

    const char operators[][3] = {
       "=","!=","<","<=",">",">="
    };
}

static short getOperatorIndex(const String& compOperator)
{
    for (int i = 0; i < Operators::operatorsSize; i++)
    {
        if (compOperator == Operators::operators[i])
        {
            return i;
        }
    }

    return -1;
}


ComparisonOperator* comparisonOperatorFactory(const String& compOperator, const PolymorphicPointer<SQLType>& value)
{
    if (!value)
        return nullptr;

    short operatorIndex = getOperatorIndex(compOperator);

    switch (operatorIndex)
    {
    case 0:
    {
        return new EqualOperator(value);
    }
    case 1:
    {
        return new NotEqualOperator(value);
    }
    case 2:
    {
        return new LessThanOperator(value);
    }
    case 3:
    {
        return new LessThanOrEqualOperator(value);
    }
    case 4:
    {
        return new GreaterThanOperator(value);
    }
    case 5:
    {
        return new GreaterThanOrEqualOperator(value);
    }
    }

    return nullptr;
}

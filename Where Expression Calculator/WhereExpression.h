#pragma once
#include "PolymorphicContainer.hpp"
#include "String.h"
#include "Vector.hpp"
#include <sstream>
#include "helperFunctions.h"
#include "ComparisonOperator.h"
#include "Dictionary.hpp"
#include "SQLColumn.h"

class WhereExpression
{
private:
	Vector<String> columnNames;

	PolymorphicContainer<ComparisonOperator> comparisonOperators;

	Vector<bool> logicalOperators;

	bool isSet = false;

public:
	void analyzeExpression(std::stringstream& query, const Dictionary<SQLColumn>& columns);
	
	void pushCondition(const String& columnName, const String& comparisonOperator, const PolymorphicPointer<SQLType>& value, char logicalOperator = -1);

	bool getIsSet() const;

	const Vector<String>& getColumnNames() const;

	void excludeRow(const SQLColumn& column, Vector<bool>& excludedRows, int logOperatorIndex) const;
};


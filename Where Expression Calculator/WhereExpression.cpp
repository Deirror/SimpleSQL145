#include "WhereExpression.h"
#include "ComparisonOperatorFactory.h"
#include "SQLTypesFactory.h"

static bool isCompOperator(char ch)
{
	return (ch == '<' || ch == '>' || ch == '=' || ch == '!');
}

static bool isDifferentFromCompOperator(char ch)
{
	return !(ch == '<' || ch == '>' || ch == '=' || ch == '!');
}

void WhereExpression::analyzeExpression(std::stringstream& query, const Dictionary<SQLColumn>& columns)
{
	String currentColumnName;
	String currentComparisonOperator;
	String value;

	bool logicalOperator;

	while (query.peek() != ';' && !query.eof())
	{
		skipSymbol(query, ' ');

		currentColumnName = getStringWithSepartor(query, ' ', isCompOperator);

		char ch = checkPreviousCharacter(query, isCompOperator);

		if(ch)
		{
			currentComparisonOperator += ch;

			if (isCompOperator(query.peek()))
			{
				currentComparisonOperator += query.get();
			}
		}
		else
		{
			skipSymbol(query, ' ');

			currentComparisonOperator = getStringWithSepartor(query, ' ', isDifferentFromCompOperator);
		}

		skipSymbol(query, ' ');

		value = getStringWithSepartor(query, ' ');

		value.removeSymbol('\'');

		bool isFinalConditoion = value.removeSymbol(';');

		PolymorphicPointer<SQLType> convertedValue = sqlTypeFactory(columns.getByKey(currentColumnName.c_string()).getType());

		convertedValue->getValue(value.c_string());

		if (isFinalConditoion)
		{
			pushCondition(currentColumnName, currentComparisonOperator, convertedValue);
			break;
		}

		skipSymbol(query, ' ');

		if (specialComparer(query, "and"))
		{
			logicalOperator = false;
		}
		else if(specialComparer(query, "or"))
		{
			logicalOperator = true;
		}
		else
		{
			throw std::invalid_argument("Logical operator is missing!");
		}

		pushCondition(currentColumnName, currentComparisonOperator, convertedValue, logicalOperator);
	}

	isSet = true;
}

void WhereExpression::pushCondition(const String& columnName, const String& comparisonOperator, const PolymorphicPointer<SQLType>& value, char logicalOperator)
{
	if (!value)
		throw std::invalid_argument("Nullptr");

	columnNames.pushBack(columnName);

	comparisonOperators.pushBack(comparisonOperatorFactory(comparisonOperator, value));

	if(logicalOperator != -1)
	    logicalOperators.pushBack(logicalOperator);
}

bool WhereExpression::getIsSet() const
{
	return isSet;
}

const Vector<String>& WhereExpression::getColumnNames() const
{
	return columnNames;
}

void WhereExpression::excludeRow(const SQLColumn& column, Vector<bool>& excludedRows, int logOperatorIndex) const
{
	for (int i = 0; i < column.getRowsInColumn(); i++)
	{
		if (logOperatorIndex == -1)
		{
		     excludedRows.pushBack(comparisonOperators[logOperatorIndex + 1]->evalulate(column.getFields()[i]));
		}
		else
		{
			bool result = comparisonOperators[logOperatorIndex + 1]->evalulate(column.getFields()[i]);

			if (logicalOperators[logOperatorIndex])
			{
				excludedRows.setAtIndex((result || excludedRows[i]), i);
			}
			else
			{
				excludedRows.setAtIndex((result && excludedRows[i]), i);
			}
		}
	}
}

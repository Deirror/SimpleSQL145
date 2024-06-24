#include "UpdateCommand.h"
#include "helperFunctions.h"

SQLResponse UpdateCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    String tableName = getStringWithSepartor(query, ' ');

    skipSymbol(query, ' ');

    if (!specialComparer(query, "set"))
    {
        return SQLResponse("Keyword set is missing!");
    }

    skipSymbol(query, ' ');

    String columnName = getStringWithSepartor(query, ' ', [](char ch) -> bool {return ch == '=';});

    if (query.peek() == '=')
    {
        query.ignore();

        skipSymbol(query, ' ');
    }

    String value;

    if (query.peek() == '\'')
    {
        query.ignore();

        value = getStringWithSepartor(query, '\'');

        if (query.eof())
        {
            return SQLResponse("\' is missing!");
        }
    }
    else
    {
        value = getStringWithSepartor(query, ' ', [](char ch) -> bool {return ch == ';';});
    }

    skipSymbol(query, ' ');

    size_t rowsCount = 0;

    if (query.eof())
    {
        return SQLResponse("; is missing!");
    }
    else if (query.peek() != ';')
    {
        if (specialComparer(query, "where"))
        {

            WhereExpression expr;

            const CSVParserSQLTable& table = tables.getTables().getByKey(tableName.c_string());

            expr.analyzeExpression(query, table.getColumns());

            rowsCount = tables.updateRowsInTable(tableName, columnName, value, expr);
        }
        else
        {
            return SQLResponse("Keyword where is missing!");
        }
    }
    else
    {
        rowsCount = tables.updateRowsInTable(tableName, columnName, value);
    }

    return SQLResponse(1, 'a', rowsCount);
}

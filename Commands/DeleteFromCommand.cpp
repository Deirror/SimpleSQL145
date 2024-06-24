#include "DeleteFromCommand.h"

SQLResponse DeleteFromCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    String tableName = getStringWithSepartor(query, ' ');

    size_t rowsCount = 0;

    if (!tableName.removeSymbol(';'))
    {
        skipSymbol(query, ' ');

        if (!specialComparer(query, "where"))
        {
            return SQLResponse("Keyword where is misspelled or is omitted!");
        }

        WhereExpression expr;

        const CSVParserSQLTable& table = tables.getTables().getByKey(tableName.c_string());

        expr.analyzeExpression(query, table.getColumns());

        rowsCount = tables.deleteRowsInTable(tableName, expr);
    }
    else
    {
        rowsCount = tables.deleteRowsInTable(tableName);
    }

    return SQLResponse(1,'a',rowsCount);
}

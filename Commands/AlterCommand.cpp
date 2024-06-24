#include "AlterCommand.h"
#include "helperFunctions.h"

SQLResponse AlterCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    String tableName = getStringWithSepartor(query, ' ');

    skipSymbol(query, ' ');

    if (specialComparer(query, "add"))
    {
        skipSymbol(query, ' ');

        String columnName = getStringWithSepartor(query, ' ');

        skipSymbol(query, ' ');

        char columnType = getColumnType(query);

        if (columnType == -1)
        {
            return SQLResponse("Invalid sql type!");
        }

        tables.addColumnToTable(tableName, columnName, columnType);
    }
    else if (specialComparer(query, "drop column"))
    {
        skipSymbol(query, ' ');

        String columnName = getStringWithSepartor(query, ';');

        if (query.eof())
        {
            return SQLResponse("; is missing!");
        }

        columnName.removeSymbol(' ');

        tables.deleteColumnInTable(tableName, columnName);

    }
    else if (specialComparer(query, "rename column"))
    {
        skipSymbol(query, ' ');

        String oldColumnName = getStringWithSepartor(query, ' ');

        skipSymbol(query, ' ');

        if (specialComparer(query, "to"))
        {
            skipSymbol(query, ' ');

            String newColumnName = getStringWithSepartor(query, ';');

            if (newColumnName.getLength() == 0)
                return SQLResponse("Empty column name is invalid!");

            if (query.eof())
            {
                return SQLResponse("; is missing!");
            }

            newColumnName.removeSymbol(' ');

            tables.renameColumnInTable(tableName, oldColumnName, newColumnName);
        }
        else
        {
            return SQLResponse("Keyword to is omitted!");
        }
    }
    else
    {
        return SQLResponse("Cannot recognize subcommand!");
    }

    return SQLResponse(1,'a',0);
}
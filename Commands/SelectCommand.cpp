#include "SelectCommand.h"
#include "WhereExpression.h"
#include "helperFunctions.h"

static void getColumnNamesForPrinting(std::stringstream& query, Vector<String>& columnNames)
{
    do
    {
        String currentColumnName = getStringWithSepartor(query, ' ', [](char ch) -> bool {return (ch == ',');});

        skipSymbol(query, ' ');

        if (!currentColumnName.removeSymbol(','))
        {
            if (query.peek() == ',')
            {
                query.ignore();

                skipSymbol(query, ' ');
            }
        }

        columnNames.pushBack(currentColumnName);

    } while (!query.eof() && !specialComparer(query, "from"));
}

SQLResponse SelectCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    Vector<String> columnNames;

    if (query.peek() != '*')
    {
        getColumnNamesForPrinting(query, columnNames);

        if (query.eof())
        {
            return SQLResponse("Keyword from may be omitted or invalid column names!");
        }
    }
    else
    {
        query.ignore();

        skipSymbol(query, ' ');

        if (!specialComparer(query, "from"))
        {
            return SQLResponse("Keyword from is misspelled or is omitted!");
        }
    }

    skipSymbol(query, ' ');

    size_t countOfWhiteSpace = getCountOfSymbol(query, ' ', ';');    

    String tableName;
    size_t rowsCount = 0;

    if (countOfWhiteSpace == 0)
    {
        tableName = getStringWithSepartor(query, ';');
        
        rowsCount = tables.printTable(tableName, columnNames);
    }
    else
    {
        tableName = getStringWithSepartor(query, ' ');

        skipSymbol(query, ' ');

        if (specialComparer(query, "where"))
        {
            WhereExpression expr;

            const CSVParserSQLTable& table = tables.getTables().getByKey(tableName.c_string());
                
            expr.analyzeExpression(query, table.getColumns());

            rowsCount = tables.printTable(tableName, columnNames, expr);
        }
        else if (specialComparer(query, "join"))
        {
            CSVParserSQLTable joinedTable = tables.getTables().getByKey(tableName.c_string());

            WhereExpression expr;

            do
            {
                skipSymbol(query, ' ');

                String toJoinTableName = getStringWithSepartor(query, ' ');

                skipSymbol(query, ' ');

                if (!specialComparer(query, "on"))
                {
                    return SQLResponse("Keyword on is omitted!");
                }

                skipSymbol(query, ' ');

                String columnNameInFirstTable = getStringWithSepartor(query, '=');

                columnNameInFirstTable.removeSymbol(' ');

                String columnNameInToJoinTable = getStringWithSepartor(query, ' ', [](char ch) -> bool {return ch == ';';});

                skipSymbol(query, ' ');

                const CSVParserSQLTable& toJoinTable = tables.getTables().getByKey(toJoinTableName.c_string());

                joinedTable.joinWithTable(toJoinTable, columnNameInFirstTable, columnNameInToJoinTable);

                if (query.peek() == ';')
                {
                    break;
                }
                else if (query.eof())
                {
                    return SQLResponse("; is missing!");
                }

                if (specialComparer(query, "where"))
                {
                    expr.analyzeExpression(query, joinedTable.getColumns());

                    break;
                }
           
            } while (specialComparer(query, "join") && !query.eof());

            rowsCount = tables.printJoinedTable(joinedTable,columnNames, expr);
        }
        else
        {
            return SQLResponse("Cannot recongnize the subcommand!");
        }
    }

    if (rowsCount == 0)
        return SQLResponse(rowsCount);

    return SQLResponse(1, 's', rowsCount);
}

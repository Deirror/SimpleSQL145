#include "InsertIntoCommand.h"
#include "helperFunctions.h"

static void getColumnNamesForInsertingInto(std::stringstream& query, Vector<String>& columnNames)
{
    while (query.peek() != ')' && !query.eof())
    {
        String currentColumnName = getStringWithSepartor(query, ' ', [](char ch) -> bool {return (ch == ',');});

        skipSymbol(query, ' ');

        if (currentColumnName.removeSymbol(','))
        {
            columnNames.pushBack(currentColumnName);
        }
        else
        {
            if (query.peek() == ',')
            {
                query.ignore();

                skipSymbol(query, ' ');
            }
            else
            {
                if (currentColumnName.removeSymbol(')'))
                {
                    columnNames.pushBack(currentColumnName);
                    break;
                }
                else
                {
                    if (query.peek() == ')')
                    {
                        query.ignore();
                        columnNames.pushBack(currentColumnName);
                        break;
                    }
                }
            }

            columnNames.pushBack(currentColumnName);
        }
    }

    if (query.eof())
        throw std::invalid_argument("Incorrect syntax near column names!");
}

static SQLResponse getValuesInQuery(std::stringstream& query, Vector<Vector<String>>& rows)
{
    Vector<String> currentRow;
    String currentValue;

    while (query.peek() != ';' && !query.eof())
    {
        if (query.get() != '(')
            return SQLResponse("( is missing in the query!");

        while (query.peek() != '(')
        {
            if (query.peek() == '\'')
            {
                query.ignore();
                currentValue = getStringWithSepartor(query, '\'');
            }
            else
            {
                currentValue = getStringWithSepartor(query, ' ', [](char ch) -> bool {return (ch == ',');});
            }
            
            skipSymbol(query, ' ');

            if (!currentValue.removeSymbol(','))
            {
                if (query.peek() == ',')
                {
                    query.ignore();

                    skipSymbol(query, ' ');
                }

                if (currentValue.removeSymbol(')'))
                {
                    if (currentValue.removeSymbol(';'))
                    {
                        currentRow.pushBack(currentValue);
                        break;
                    }
                    else if (query.eof())
                    {
                        if (query.peek() != ';')
                        {
                            return SQLResponse("; is omitted!");
                        }
                    }
                }
                else if (query.peek() == ')')
                {
                    query.ignore();
                    skipSymbol(query, ' ');

                    if (query.peek() == ',')
                    {
                        query.ignore();
                        skipSymbol(query, ' ');
                    }
                    else if(query.peek() == ';')
                    {
                        currentRow.pushBack(currentValue);
                        break;
                    }
                }
            }
            else if (currentValue.removeSymbol(')'))
            {
                currentRow.pushBack(currentValue);
                break;
            }

            currentRow.pushBack(currentValue);
        }

        rows.pushBack(currentRow);
        currentRow.clear();
    }

    return SQLResponse("");
}

SQLResponse InsertIntoCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    String tableName = getStringWithSepartor(query, ' ');

    skipSymbol(query, ' ');

    if (query.peek() != '(')
        return SQLResponse("( is missing in the query!");

    query.ignore();

    skipSymbol(query, ' ');

    Vector<String> columnNames;

    getColumnNamesForInsertingInto(query, columnNames);

    skipSymbol(query, ' ');

    if (!specialComparer(query, "values"))
    {
        return SQLResponse("Keyword values is misspelled or is omitted!");
    }

    skipSymbol(query, ' ');

    Vector<Vector<String>> rows;
  
    SQLResponse response = getValuesInQuery(query, rows);

    if (response.getMessage() != "")
        return response;

    for (int i = 0; i < rows.getSize(); i++)
    {
        if (rows[i].getSize() != columnNames.getSize())
            return SQLResponse("Too many values or column names are given!");
    }

    tables.addRowsToTable(tableName, columnNames, rows);

    return SQLResponse(1,'a', rows.getSize());
}

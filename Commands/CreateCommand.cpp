#include "CreateCommand.h"
#include "helperFunctions.h"

SQLResponse CreateCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');
    
    String tableName = getStringWithSepartor(query, ' ');

    skipSymbol(query, ' ');

    if (query.peek() != '(')
        return SQLResponse("( is missing in the query!");

    Vector<String> columnNames;
    Vector<char> columnTypes;

    while (query.peek() == ',' || query.peek() != ')')
    {
        query.ignore();

        skipSymbol(query, ' ');

        columnNames.pushBack(getStringWithSepartor(query, ' '));

        skipSymbol(query, ' ');

        char ch = getColumnType(query);

        if(ch == -1)
            return SQLResponse("Unkhown column type is given!");

        columnTypes.pushBack(ch);

        skipSymbol(query, ' ');
    }
    
    query.ignore();

    skipSymbol(query, ' ');

    if (query.peek() != ';')
        return SQLResponse("; is missing in the query!");

    tables.createTable(tableName, columnNames, columnTypes);

    return SQLResponse(true);
}

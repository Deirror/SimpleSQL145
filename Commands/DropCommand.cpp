#include "DropCommand.h"
#include "helperFunctions.h"

SQLResponse DropCommand::execute(std::stringstream& query, SQLTables& tables) const
{
    skipSymbol(query, ' ');

    String tableName = getStringWithSepartor(query, ';');

    tables.deleteTable(tableName);

    return SQLResponse(true, 'a', 0);
}

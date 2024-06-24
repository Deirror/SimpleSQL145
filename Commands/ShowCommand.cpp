#include "ShowCommand.h"

SQLResponse ShowCommand::execute(std::stringstream& query, SQLTables& tables) const
{
	if (query.peek() != ';')
		return SQLResponse("; is missing in the query!");

	return tables.showTablesNames();
}

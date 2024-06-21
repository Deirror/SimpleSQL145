#include "dblib.h"
#include <stdexcept>
#include "CommandFactory.h"
#include "helperFunctions.h"

static String addSlashIfNeeded(const String& databasePath)
{
	String res = databasePath;

	if (!res.isEmpty() && res[res.getLength() - 1] != '/')
		res += "/";

	return res;
}

Database::Database(const String& newDatabasePath) 
	: databasePath(addSlashIfNeeded(newDatabasePath)), 
	  sqlTables(addSlashIfNeeded(newDatabasePath))
{
	
}

const DirectoryPath& Database::getDatabasePath() const
{
	return databasePath;
}

const SQLTables& Database::getSQLTables() const
{
	return sqlTables;
}

SQLResponse Database::executeQuery(const String& query)
{
	std::stringstream ss(query.c_string());

	Command* cmd = commandFactory(ss);

	if (!cmd)
		return SQLResponse("Command cannot be recognized!");

	return cmd->execute(ss, sqlTables);
}

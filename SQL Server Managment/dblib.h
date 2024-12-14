#pragma once
#include "DirectoryPath.h"
#include "SQLTables.h"
#include "SQLResponse.h"

class Database
{
private:
	DirectoryPath databasePath;

	SQLTables sqlTables;

public:
	Database() = default;

	Database(const String& newDatabasePath);

	const DirectoryPath& getDatabasePath() const;

	const SQLTables& getSQLTables() const;

	SQLResponse executeQuery(const String& query);
};


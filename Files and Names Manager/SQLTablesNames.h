#pragma once
#include "SQLResponse.h"
#include "Vector.hpp"
#include "String.h"

class SQLTablesNames
{
private:
	Vector<String> namesOfSQLTables;

	const String sqlTablesNamesFilePath;

	static const String sqlTablesFileName;

	void changeContentOfTablesNamesFile() const;

public:
	SQLTablesNames() = default;

	SQLTablesNames(const String& databasePath);

	void addNewTable(const String& tableName);

	void removeTable(const String& tableName);

	SQLResponse showTablesNames() const;

	const Vector<String>& getNamesOfTables() const;

	size_t getCountOfTables() const;

private:
	void printTablesNames(size_t len) const;
};


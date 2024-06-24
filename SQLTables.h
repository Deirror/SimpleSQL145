#pragma once
#include "Dictionary.hpp"
#include "CSVParserSQLTable.h"
#include "SQLTablesNames.h"

class SQLTables
{
private:
	SQLTablesNames namesHandler;

	Dictionary<CSVParserSQLTable> tables;

	const String databasePath;

	static const String format;

public:
	SQLTables() = default;

	SQLTables(const String& newDatabasePath);

	const Dictionary<CSVParserSQLTable>& getTables() const;

	SQLResponse showTablesNames() const;

	void createTable(const String& tableName, const Vector<String>& columnNames, const Vector<char>& columnTypes);

	void deleteTable(const String& tableName);

	int deleteRowsInTable(const String& tableName, const WhereExpression& expr = {});

	void deleteColumnInTable(const String& tableName, const String& columnName);

	void renameColumnInTable(const String& tableName, const String& oldColumnName, const String& newColumnName);

	void addRowsToTable(const String& tableName, const Vector<String>& columnNames, const Vector<Vector<String>>& rows);

	int updateRowsInTable(const String& tableName, const String& columnName, const String& value, const WhereExpression& expr = {});

	void addColumnToTable(const String& tableName, const String& columnName, char columnType);

	int printTable(const String& tableName, const Vector<String>& columnNames, const WhereExpression& expr = {} )const;

	int printJoinedTable(const CSVParserSQLTable& joinedTable,const Vector<String>& columnNames, const WhereExpression& expr = {}) const;

private:
	int findTable(const String& tableName) const;
	
	void changeContentOfGivenTableFile(const String& tableName, const CSVParserSQLTable& table) const;
};


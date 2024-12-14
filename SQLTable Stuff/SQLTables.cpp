#include "SQLTables.h"
#include "SQLTablesFilesManager.h"
#include "WhereExpression.h"
#include "Null.h"

const String SQLTables::format = ".ss145";

SQLTables::SQLTables(const String& newDatabasePath) 
	: databasePath(newDatabasePath), namesHandler(newDatabasePath)
{ 
	const Vector<String>& tablesNames = namesHandler.getNamesOfTables();

	for (int i = 0; i < namesHandler.getCountOfTables(); i++)
	{
		tables.add(tablesNames[i].c_string(), CSVParserSQLTable(newDatabasePath + tablesNames[i] + format));
	}
}

const Dictionary<CSVParserSQLTable>& SQLTables::getTables() const
{
	return tables;
}

SQLResponse SQLTables::showTablesNames() const
{
	return namesHandler.showTablesNames();
}


void SQLTables::createTable(const String& tableName, const Vector<String>& columnNames, const Vector<char>& columnTypes)
{
	namesHandler.addNewTable(tableName);

	String newTableFilePath = (databasePath + tableName + format);

	SQLTablesFilesManager::createTableFile(newTableFilePath, columnNames, columnTypes);

	tables.add(tableName.c_string(), CSVParserSQLTable(columnNames, columnTypes));
}

void SQLTables::deleteTable(const String& tableName)
{
	namesHandler.removeTable(tableName);

	tables.removeByKey(tableName.c_string());

	String tableFilePath = (databasePath + tableName + format);

	SQLTablesFilesManager::deleteTableFile(tableFilePath);
}

int SQLTables::deleteRowsInTable(const String& tableName, const WhereExpression& expr)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	int affectedRows = table.deleteRows(expr);

	changeContentOfGivenTableFile(tableName, table);

	return affectedRows;
}

void SQLTables::deleteColumnInTable(const String& tableName, const String& columnName)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	table.deleteColumn(columnName);

	changeContentOfGivenTableFile(tableName, table);
}

void SQLTables::renameColumnInTable(const String& tableName, const String& oldColumnName, const String& newColumnName)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	table.renameColumn(oldColumnName, newColumnName);

	changeContentOfGivenTableFile(tableName, table);
}

void SQLTables::addRowsToTable(const String& tableName, const Vector<String>& columnNames, const Vector<Vector<String>>& rows)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	table.addRows(columnNames, rows);

	changeContentOfGivenTableFile(tableName, table);
}

int SQLTables::updateRowsInTable(const String& tableName, const String& columnName, const String& value, const WhereExpression& expr)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	int affectedRows =  table.updateRows(columnName, value, expr);

	changeContentOfGivenTableFile(tableName, table);

	return affectedRows;
}

void SQLTables::addColumnToTable(const String& tableName, const String& columnName, char columnType)
{
	CSVParserSQLTable& table = tables[findTable(tableName)];

	PolymorphicPointer<SQLType> instantiateWith = new Null();

	table.addColumn(columnName.c_string(), columnType, instantiateWith);

	changeContentOfGivenTableFile(tableName, table);
}

int SQLTables::printTable(const String& tableName, const Vector<String>& columnNames, const WhereExpression& expr) const
{
	const CSVParserSQLTable& table = tables[findTable(tableName)];

	if (table.getRows() == 0)
		return 0;

	if (columnNames.getSize() == 0)
	{
		return table.printSQLTable(expr);
	}
	else
	{
		return table.printSQLTableByGivenColumnNames(columnNames, expr);
	}
}

int SQLTables::printJoinedTable(const CSVParserSQLTable& joinedTable, const Vector<String>& columnNames, const WhereExpression& expr) const
{
	if (columnNames.getSize() == 0)
	{
		return joinedTable.printSQLTable(expr);
	}
	else
	{
		return joinedTable.printSQLTableByGivenColumnNames(columnNames, expr);
	}
}

int SQLTables::findTable(const String& tableName) const
{
	int index = tables.contains(tableName.c_string());

	if (index == -1)
	{
		throw std::invalid_argument("Table not found!");
	}

	return index;
}

void SQLTables::changeContentOfGivenTableFile(const String& tableName, const CSVParserSQLTable& table) const
{
	String tableFilePath = (databasePath + tableName + format);

	SQLTablesFilesManager::changeContentOfTableFile(tableFilePath, table);
}

#include "SQLTablesFilesManager.h"

void SQLTablesFilesManager::createTableFile(const String& tableFilePath, const Vector<String>& columnNames, const Vector<char>& columnTypes)
{
	std::ofstream ofs(tableFilePath.c_string());

	if (!ofs.is_open())
		throw std::runtime_error("Cannot create new tableFile!");
	
	for (int i = 0;i < columnNames.getSize(); i++)
	{
		ofs << columnNames[i];
		ofs << '/' << columnTypes[i];
		ofs << '|';
	}

	ofs.close();
}

void SQLTablesFilesManager::deleteTableFile(const String& tableFilePath)
{
	std::remove(tableFilePath.c_string());
}

void SQLTablesFilesManager::changeContentOfTableFile(const String& tableFilePath, const CSVParserSQLTable& table)
{
	std::ofstream ofs(tableFilePath.c_string());

	if (!ofs.is_open())
		throw std::runtime_error("Cannot open tableFile!");

	table.writeContentOfTableToFile(ofs);

	ofs.close();
}

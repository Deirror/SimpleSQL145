#pragma once
#include <fstream>
#include "CSVParserSQLTable.h"
#include "Vector.hpp"
#include "String.h"

class SQLTablesFilesManager
{
public:
	static void createTableFile(const String& filePath, const Vector<String>& columnNames, const Vector<char>& columnTypes);

	static void deleteTableFile(const String& filePath);

	static void changeContentOfTableFile(const String& filePath, const CSVParserSQLTable& table);

};
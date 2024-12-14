#pragma once
#include "dblib.h"

class SQLServerManagment
{
public:
	static void startServer();

private:
	static String getPathToDatabase();

	static void runSQLQueries(Database& db);
};


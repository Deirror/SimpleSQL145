#include "SQLServerManagment.h"

void SQLServerManagment::startServer()
{
	String path = getPathToDatabase();

	try
	{
		Database db(path);

		std::cout << "ssql145> Successfully connected to database!\n\n";

		std::cout << "ssql145> --------------Queries--------------\n\n";

		SQLServerManagment::runSQLQueries(db);
	}
	catch (std::exception& e)
	{
		std::cout << '\n' << e.what();
	}
}

String SQLServerManagment::getPathToDatabase()
{
	std::cout << "ssql145> Write path to database : ";

	String path;
	std::cin >> path;

	std::cout << '\n';

	return path;
}

void SQLServerManagment::runSQLQueries(Database& db)
{
	String query;

	while (true)
	{
		std::cout << "ssql145> ";

		std::cin >> query;

		if (query == "exit")
			return;

		try
		{
			SQLResponse response = db.executeQuery(query);

			std::cout << '\n' << response.getMessage() << '\n' << '\n';
		}
		catch (std::exception& e)
		{
			std::cout << '\n' << e.what() << '\n' << '\n';
		}
	}
}

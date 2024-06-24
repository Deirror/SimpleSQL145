#pragma once
#include "SQLTables.h"
#include <sstream>

class Command
{
public:
	virtual SQLResponse execute(std::stringstream& query, SQLTables& tables) const = 0;

	virtual ~Command() = default;
};


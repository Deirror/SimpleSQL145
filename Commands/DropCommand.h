#pragma once
#include "Command.h"

class DropCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


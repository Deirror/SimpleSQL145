#pragma once
#include "Command.h"

class ShowCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


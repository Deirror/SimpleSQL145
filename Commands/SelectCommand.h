#pragma once
#include "Command.h"

class SelectCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


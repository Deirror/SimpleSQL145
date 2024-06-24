#pragma once
#include "Command.h"

class InsertIntoCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


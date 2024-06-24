#pragma once
#include "Command.h"

class UpdateCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


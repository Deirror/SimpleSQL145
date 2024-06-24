#pragma once
#include "Command.h"

class DeleteFromCommand : public Command
{
public:
	SQLResponse execute(std::stringstream& query, SQLTables& tables) const override;
};


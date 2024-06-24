#include "CommandFactory.h"
#include "AlterCommand.h"
#include "CreateCommand.h"
#include "DeleteFromCommand.h"
#include "DropCommand.h"
#include "ShowCommand.h"
#include "SelectCommand.h"
#include "InsertIntoCommand.h"
#include "UpdateCommand.h"
#include "helperFunctions.h"

namespace Commands
{
    constexpr short commandsSize = 8;

    const char commands[][13] = {
        "show tables",
        "create table", 
        "select",
        "insert into",
        "alter table",
        "update",
        "delete from",
        "drop table"
    };
}

static short getCommandIndex(std::stringstream& ss)
{
    for (int i = 0; i < Commands::commandsSize; i++)
    {
        if (specialComparer(ss, Commands::commands[i]))
        {
           return i;
        }
    }

    return -1;
}

Command* commandFactory(std::stringstream& ss)
{
    short commandIndex = getCommandIndex(ss);

    switch (commandIndex)
    {
    case 0:
    {
        return new ShowCommand();
    }
    case 1:
    {
        return new CreateCommand();
    }
    case 2:
    {
        return new SelectCommand();
    }
    case 3:
    {
        return new InsertIntoCommand();
    }
    case 4:
    {
        return new AlterCommand();
    }
    case 5:
    {
        return new UpdateCommand();
    }
    case 6:
    {
        return new DeleteFromCommand();
    }
    case 7:
    {
        return new DropCommand();
    }
    }

    return nullptr;
}

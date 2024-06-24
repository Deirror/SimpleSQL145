#include "SQLResponse.h"
#include <stdexcept>
#include "helperFunctions.h"

SQLResponse::SQLResponse() : message("")
{
}

SQLResponse::SQLResponse(bool typeOfMessage, char setOrAffected, unsigned count)
{
    switch (typeOfMessage)
    {
    case false://Empty
    {
        message = "Empty set";
        break;
    }
    case true://OK
    {
        if (setOrAffected == 's')
        {
            if (count == 1)
            {
                message = "1 row in set";
            }
            else if(count > 1)
            {
                message = (toString(count) += " rows in set");
            }

            break;
        }

        message = "Query OK";

        if(setOrAffected == 'a')
        {
            message += ", ";

            if (count == 1)
            {
                message += "1 row affected";
            }
            else if (count > 1 || count == 0)
            {
                message += (toString(count) += " rows affected");
            }
        }

        break;
    }
    }
}

SQLResponse::SQLResponse(const char* newMessage)
{
    if (!newMessage)
        throw std::invalid_argument("Nullptr!");

    message = newMessage;
}

const String& SQLResponse::getMessage() const
{
    return message;
}

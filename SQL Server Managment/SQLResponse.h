#pragma once
#include "String.h"

class SQLResponse
{
private:
	String message;

public:
	SQLResponse();

	SQLResponse(bool typeOfMessage, char setOrAffected = '\0', unsigned count = -1);

	SQLResponse(const char* newMessage);//mainly used for error messages

	const String& getMessage() const;
};

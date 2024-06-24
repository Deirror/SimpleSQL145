#pragma once
#include "SQLType.h"
#include "String.h"

class Null : public SQLType
{
private:
	const String field = "NULL";
public:
	char getType() const override;

	SQLType* clone() const override;

	const String& getField() const;
};


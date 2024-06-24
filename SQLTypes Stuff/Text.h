#pragma once
#include "SQLType.h"
#include "String.h"

class Text : public SQLType
{
private:
	String field;

public:
	Text() = default;

	Text(const String& value);

	SQLType* clone() const override;

	char getType() const override;

	void getValue(const char* field);

	void setField(const String& value);

	const String& getField() const;

};
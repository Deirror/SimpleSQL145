#pragma once
#include "SQLType.h"

class Integer : public SQLType
{
private:
	int field = 0;

public:
	Integer() = default;

	Integer(int value);

	SQLType* clone() const override;

	void getValue(const char* field);

	char getType() const override;

	void setField(int value);

	int getField() const;
};


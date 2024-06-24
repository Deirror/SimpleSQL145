#pragma once
#include "specialSqlHelper.h"

class SQLType
{
public:
	virtual void getValue(const char* field) {};

	virtual char getType() const = 0;

	virtual SQLType* clone() const = 0;

	virtual ~SQLType() = default;
};


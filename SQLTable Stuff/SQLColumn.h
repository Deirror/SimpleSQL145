#pragma once
#include "PolymorphicContainer.hpp"
#include "SQLType.h"

class SQLColumn
{
private:
	char columnType = '\0';//i,r,t

	PolymorphicContainer<SQLType> fields;

public:
	SQLColumn() = default;

	SQLColumn(char _columnType);

	SQLColumn(char _columnType, size_t rowsCap, const PolymorphicPointer<SQLType>& instantiateWith);

	size_t getRowsInColumn() const;

	char getType() const;

	void addField(const char* field, int index = -1);

	void setNextField(const PolymorphicPointer<SQLType>& obj);

	void setFieldByIndex(const PolymorphicPointer<SQLType>& obj, int index);

	void removeField(size_t index);

	const PolymorphicContainer<SQLType>& getFields() const;

private:
	void setColumnType(char _columnType);
};


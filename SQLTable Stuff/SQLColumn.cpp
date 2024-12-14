#include "SQLColumn.h"
#include "SQLTypesFactory.h"
#include "PolymorphicPointer.hpp"
#include "Null.h"

SQLColumn::SQLColumn(char _columnType)
{
	setColumnType(_columnType);
}

SQLColumn::SQLColumn(char _columnType, size_t rowsCap, const PolymorphicPointer<SQLType>& instantiateWith)
	: fields(rowsCap, instantiateWith)
{
	setColumnType(_columnType);
}

size_t SQLColumn::getRowsInColumn() const
{
	return fields.getSize();
}

char SQLColumn::getType() const
{
	return columnType;
}

void SQLColumn::addField(const char* field, int index)
{
	if (!field)
		throw std::invalid_argument("Nullptr");

	PolymorphicPointer<SQLType> convertedField = nullptr;

	if (*field != '\0')
	{ 
		convertedField = sqlTypeFactory(columnType);

		convertedField->getValue(field);
	}
	else
	{
		convertedField = sqlTypeFactory(*field);
	}
	
	if (index == -1)
	{
		setNextField(convertedField);
	}
	else
	{
		setFieldByIndex(convertedField, index);
	}
}

void SQLColumn::setNextField(const PolymorphicPointer<SQLType>& obj)
{
	if (!obj)
		throw std::invalid_argument("Nullptr");

	fields.pushBack(obj);
}

void SQLColumn::setFieldByIndex(const PolymorphicPointer<SQLType>& obj, int index)
{
	if (!obj)
		throw std::invalid_argument("Nullptr");

	fields.setAtIndex(obj, index);
}

void SQLColumn::removeField(size_t index)
{
	fields.removeAt(index);
}

const PolymorphicContainer<SQLType>& SQLColumn::getFields() const
{
	return fields;
}

void SQLColumn::setColumnType(char _columnType)
{
	switch (_columnType)
	{
	case 'i':
	case 'r':
	case 't':
	{
		columnType = _columnType;
		break;
	}
	default:
	{
		throw std::invalid_argument("Unknown sql type!");
	}
	}
}

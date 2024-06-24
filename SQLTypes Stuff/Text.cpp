#include "Text.h"

Text::Text(const String& value) : field(value)
{
}

SQLType* Text::clone() const
{
	return new Text(*this);
}

char Text::getType() const
{
	return 't';
}

void Text::getValue(const char* field)
{
	if (!field)
		throw std::invalid_argument("Nullptr");

	this->field = field;
}

void Text::setField(const String& value)
{
	field = value;
}

const String& Text::getField() const
{
	return field;
}


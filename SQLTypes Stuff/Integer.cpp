#include "Integer.h"
#include <sstream>
#include <stdexcept>

Integer::Integer(int value) : field(value)
{
}

SQLType* Integer::clone() const
{
    return new Integer(*this);
}

void Integer::getValue(const char* field)
{
    if (!field)
        throw std::invalid_argument("Nullptr");

    std::stringstream ss(field);

    if (!checkContentOfStream(ss, isDigit))
        throw std::invalid_argument("Value is invalid!");

    ss >> this->field;
}

char Integer::getType() const
{
    return 'i';
}

void Integer::setField(int value)
{
    field = value;
}

int Integer::getField() const
{
    return field;
}

#include "Real.h"
#include <sstream>
#include <stdexcept>

Real::Real(double value) : field(value)
{
}

SQLType* Real::clone() const
{
    return new Real(*this);
}

char Real::getType() const
{
    return 'r';
}

void Real::getValue(const char* field)
{
    if (!field)
        throw std::invalid_argument("Nullptr");

    std::stringstream ss(field);

    if (!checkContentOfStream(ss, isFloatingDigit))
        throw std::invalid_argument("Value is invalid!");

    ss >> this->field;
}

void Real::setField(double value)
{
    field = value;
}

double Real::getField() const
{
    return field;
}

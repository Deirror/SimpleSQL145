#include "Null.h"
#include "String.h"

char Null::getType() const
{
    return '\0';
}

SQLType* Null::clone() const
{
    return new Null();
}

const String& Null::getField() const
{
    return field;
}

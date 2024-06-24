#include "SQLTypesFactory.h"
#include "Integer.h"
#include "Real.h"
#include "Text.h"
#include "Null.h"

SQLType* sqlTypeFactory(char columnType)
{
    switch (columnType)
    {
    case 'i':
    {
        return new Integer();
    }
    case 'r':
    {
        return new Real();
    }
    case 't':
    {
        return new Text();
    }
    case '\0':
    {
        return new Null();
    }
    }

    return nullptr;
}

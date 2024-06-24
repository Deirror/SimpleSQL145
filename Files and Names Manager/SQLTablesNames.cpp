#include "SQLTablesNames.h"
#include "helperFunctions.h"
#include <stdexcept>

const String SQLTablesNames::sqlTablesFileName = "tables.txt";

void SQLTablesNames::addNewTable(const String& tableName)
{
    if (!namesOfSQLTables.contains(tableName))
    {
        namesOfSQLTables.pushBack(tableName);

        changeContentOfTablesNamesFile();
    }
    else
    {
        throw std::invalid_argument("A table with this name already exists!");
    }
}

void SQLTablesNames::removeTable(const String& tableName)
{
    int index = namesOfSQLTables.find(tableName);

    if (index != -1)
    {
        namesOfSQLTables.removeAt(index);

        changeContentOfTablesNamesFile();
    }
    else
    {
        throw std::invalid_argument("A table with this name doesn't exists!");
    }
}

void SQLTablesNames::printTablesNames(size_t len) const
{
    for (int i = 0; i < namesOfSQLTables.getSize(); i++)
    {
        printLine(len);
        addFinalSymbolToRow('o');

        printCell(namesOfSQLTables[i], len);
        addFinalSymbolToRow('|');
    }

    printLine(len);
    addFinalSymbolToRow('o');
}

SQLResponse SQLTablesNames::showTablesNames() const
{
    if (namesOfSQLTables.getSize() == 0)
        return SQLResponse(false);

    static const String mainField = "Tables in Database";

    size_t len = maxLenOnColumn(namesOfSQLTables);

    if (len < mainField.getLength())
        len = mainField.getLength();

    printLine(len);
    addFinalSymbolToRow('o');

    printCell(mainField, len);
    addFinalSymbolToRow('|');

    printTablesNames(len);

    return SQLResponse(true, 's', namesOfSQLTables.getSize());
}

const Vector<String>& SQLTablesNames::getNamesOfTables() const
{
    return namesOfSQLTables;
}

size_t SQLTablesNames::getCountOfTables() const
{
    return namesOfSQLTables.getSize();
}


SQLTablesNames::SQLTablesNames(const String& databasePath)
    : sqlTablesNamesFilePath(databasePath + SQLTablesNames::sqlTablesFileName)
{
    if (!databasePath)
        throw std::invalid_argument("First time instantiating needs valid argument!");

    std::ifstream ifs(sqlTablesNamesFilePath.c_string());

    if (!ifs.is_open())
        throw std::runtime_error("File cannot be opened!");

    size_t size = getCountOfSymbol(ifs, '|');

    for (int i = 0; i < size; i++)
    {
        namesOfSQLTables.pushBack(getStringWithSepartor(ifs, '|'));
    }

    ifs.close();
}

void SQLTablesNames::changeContentOfTablesNamesFile() const
{
    std::ofstream ofs(sqlTablesNamesFilePath.c_string());

    if (!ofs.is_open())
        throw std::runtime_error("File cannot be opened!");

    for (int i = 0; i < namesOfSQLTables.getSize(); i++)
    {
        ofs << namesOfSQLTables[i] << '|';      
    }

    ofs.close();
}


#include "CSVParserSQLTable.h"
#include <stdexcept>
#include <sstream>
#include "helperFunctions.h"
#include "SQLTypesFactory.h"

namespace parserTools
{
	constexpr char sepType = '/';
	constexpr char sepField = '|';
	constexpr char sepEndLine = '\n';

	constexpr size_t sizeOfArray = 22;
	constexpr char invalidSymbolsColumnName[] = { '&','!','@','%','^','~','*','(',')','-','+','=','|','\\','/','?',':',';','{','}','[',']'};
}

static void validateColumnName(const String& obj)
{
	for (int i = 0; i < parserTools::sizeOfArray; i++)
	{
		if (obj.containsCharachter(parserTools::invalidSymbolsColumnName[i]))
			throw std::invalid_argument("Incorrect format of string!");
	}
}

CSVParserSQLTable::CSVParserSQLTable(const String& filePath)
{
	std::ifstream ifs(filePath.c_string());

	if (!ifs.is_open())
		throw std::runtime_error("Cannot be opened!");

	parseTable(ifs);
}

CSVParserSQLTable::CSVParserSQLTable(const Vector<String>& columnNames, const Vector<char>& columnTypes)
{
	for (int i = 0; i < columnNames.getSize(); i++)
	{
		addColumn(columnNames[i].c_string(), columnTypes[i]);
	}
}

void CSVParserSQLTable::parseTable(std::ifstream& ifs)
{
	char buff[1024]{};

	cols = getCountOfSymbol(ifs, parserTools::sepField, parserTools::sepEndLine);

	bool areKeysPopulated = false;

	while (!ifs.eof())
	{
		ifs.getline(buff, 1024, parserTools::sepEndLine);

		std::stringstream ss(buff);

		if (areKeysPopulated)
			rows++;

		populateFieldsOnRow(ss, areKeysPopulated);
	}
}

void CSVParserSQLTable::populateFieldsOnRow(std::stringstream& ss, bool& areKeysPopulated)
{
	char buff[1024]{};

	for (int i = 0; i < cols; i++)
	{
		if (!areKeysPopulated)
		{
			ss.getline(buff, 1024, parserTools::sepType);

			if (strlen(buff) == 0)
				throw std::invalid_argument("Empty column name is invalid!");

			validateColumnName(buff);

			columns.add(buff, SQLColumn(ss.get()));

			ss.ignore();
		}
		else
		{
			ss.getline(buff, 1024, parserTools::sepField);

			columns[i].addField(buff);
		}
	}

	ss.ignore();
	areKeysPopulated = true;
}

void CSVParserSQLTable::addColumn(const char* columnName, char columnType, const PolymorphicPointer<SQLType>& instantiateWith)
{
	if (!columnName)
		throw std::invalid_argument("Nullptr");

	validateColumnName(columnName);

	if (instantiateWith)
	{
		columns.add(columnName, SQLColumn(columnType, rows, instantiateWith));
	}
	else
	{
		columns.add(columnName, SQLColumn(columnType));
	}

	cols++;
}

void CSVParserSQLTable::deleteColumn(const String& columnName)
{
	columns.removeByKey(columnName.c_string());

	cols--;
}

void CSVParserSQLTable::addRows(const Vector<String>& columnNames, const Vector<Vector<String>>& rows)
{
	for (int i = 0; i < columnNames.getSize(); i++)
	{
		validateColumnName(columnNames[i]);
	}

	Vector<size_t> indexes;

	if (columnNames.getSize() > 0)
	{
		getIndexesOfGivenColumnNames(columnNames, indexes);
	}

	for (int i = 0; i < rows.getSize(); i++)
	{
		for (int j = 0; j < columnNames.getSize(); j++)
		{
			columns[indexes[j]].addField(rows[i][j].c_string());
		}

		for (int j = 0; j < cols; j++)
		{
			if(!indexes.contains(j))
			    columns[j].addField("");
		}	

		this->rows++;
	}
}

void CSVParserSQLTable::renameColumn(const String& oldColumnName, const String& newColumnName)
{
	columns.changeKey(oldColumnName.c_string(), newColumnName.c_string());
}

int CSVParserSQLTable::updateRows(const String& columnName, const String& value, const WhereExpression& expr)
{
	Vector<bool> excludedRows;

	if (expr.getIsSet())
	{
		excludeRowsInTable(expr, excludedRows);
	}

	int counter = 0;

	int columnIndex = columns.contains(columnName.c_string());

	if (columnIndex == -1)
		throw std::invalid_argument("Invalid column name!");

	char columnType = columns[columnIndex].getType();

	PolymorphicPointer<SQLType> newValue = sqlTypeFactory(columnType);

	newValue->getValue(value.c_string());

	for (int i = 0; i < rows; i++)
	{
		if (expr.getIsSet())
		{
			if (!excludedRows[i])
			{
				continue;
			}
		}

		columns[columnIndex].setFieldByIndex(newValue, i);

		counter++;
	}

	return counter;
}

int CSVParserSQLTable::deleteRows(const WhereExpression& expr)
{
	Vector<bool> excludedRows;

	if (expr.getIsSet())
	{
		excludeRowsInTable(expr, excludedRows);
	}

	int counter = 0;

	int deleteIndex = 0;

	for (int i = 0; i < rows; i++)
	{
		if (expr.getIsSet())
		{
			if (!excludedRows[i])
			{
				deleteIndex++;
				continue;
			}
		}

		counter++;

		for (int j = 0; j < cols; j++)
		{
			columns[j].removeField(deleteIndex);
		}
	}

	rows -= counter;

	return counter;
}

int CSVParserSQLTable::printSQLTable(const WhereExpression& expr) const
{
	Vector<bool> excludedRows;

	if (expr.getIsSet())
	{
		excludeRowsInTable(expr, excludedRows);
	}

	Vector<size_t> lengths = getMaxLengthOnEachColumn();

	printLinesOnRow(cols, lengths);

	for (int i = 0; i < cols; i++)
	{
		printCell(columns.getKeyByIndex(i), lengths[i]);
	}

	addFinalSymbolToRow('|');

	int counter = 0;

	for (int i = 0; i < rows; i++)
	{
		if (expr.getIsSet())
		{
			if (!excludedRows[i])
			{
				continue;
			}	
		}
		counter++;

		printLinesOnRow(cols, lengths);

		for (int j = 0; j < cols; j++)
		{
			printFieldValue(i, j, lengths[j]);
		}
		addFinalSymbolToRow('|');
	}

	printLinesOnRow(cols, lengths);

	return counter;
}

int CSVParserSQLTable::printSQLTableByGivenColumnNames(const Vector<String>& columnNames, const WhereExpression& expr) const
{
	Vector<bool> excludedRows;

	if (expr.getIsSet())
	{
		excludeRowsInTable(expr, excludedRows);
	}

	Vector<size_t> indexes;

	if (columnNames.getSize() > 0)
	{
		getIndexesOfGivenColumnNames(columnNames, indexes);
	}

	Vector<size_t> lengths = getMaxLengthOnEachColumnByGivenColumnNames(indexes);

	size_t floatingColsSize = columnNames.getSize();

	printLinesOnRow(floatingColsSize, lengths);

	for (int i = 0; i < columnNames.getSize(); i++)
	{
		printCell(columnNames[i], lengths[i]);
	}

	addFinalSymbolToRow('|');

	size_t lenIndex = 0;

	int counter = 0;

	for (int i = 0; i < rows; i++)
	{
		if (expr.getIsSet())
		{
			if (!excludedRows[i])
			{
				continue;
			}
		}
		counter++;

		printLinesOnRow(floatingColsSize, lengths);

		for (int j = 0; j < cols; j++)
		{
			if (indexes.contains(j))
			{
				printFieldValue(i, indexes[lenIndex], lengths[lenIndex]);
				lenIndex++;
			}
		}

		lenIndex = 0;
		addFinalSymbolToRow('|');
	}

	printLinesOnRow(floatingColsSize, lengths);

	return counter;
}

void CSVParserSQLTable::writeContentOfTableToFile(std::ofstream& ofs) const
{
	writeColumnNamesToFile(ofs);

	writeFieldsToFile(ofs);
}

char CSVParserSQLTable::getTypeOfColumnByName(const String& columnName) const
{
	return columns.getByKey(columnName.c_string()).getType();;
}

static bool compareColumn(const SQLColumn& lhs, const SQLColumn& rhs)
{
	if (lhs.getRowsInColumn() != rhs.getRowsInColumn())
		return false;

	if (lhs.getType() != rhs.getType())
		return false;

	size_t size = lhs.getRowsInColumn();

	for (int i = 0; i < size; i++)
	{
		if (stringFieldWithType(lhs.getFields()[i]) != stringFieldWithType(rhs.getFields()[i]))
			return false;
	}

	return true;
}

void CSVParserSQLTable::joinWithTable(const CSVParserSQLTable& tableToJoin, const String& columnNameOfThis, const String& columnNameOfToJoin)
{
	const SQLColumn& lhs = columns.getByKey(columnNameOfThis.c_string());

	const SQLColumn& rhs = tableToJoin.columns.getByKey(columnNameOfToJoin.c_string());

	if (!compareColumn(lhs, rhs))
	{
		throw std::runtime_error("Cannot join the tables, columns are not equal!");
	}

	for (int i = 0; i < tableToJoin.cols; i++)
	{
		String columnName = tableToJoin.getColumns().getKeyByIndex(i);

		columns.add(columnName.c_string(), tableToJoin.getColumns()[i]);

		cols++;
	}
}

void CSVParserSQLTable::writeColumnNamesToFile(std::ofstream& ofs) const
{
	for (int i = 0; i < cols; i++)
	{
		ofs << columns.getKeyByIndex(i);
		ofs << '/' << columns[i].getType();
		ofs << '|';
	}

	if(rows > 0)
		ofs << '\n';
}

void CSVParserSQLTable::writeFieldsToFile(std::ofstream& ofs) const
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			const PolymorphicPointer<SQLType>& field = columns[j].getFields()[i];

			if (!field)
				throw std::invalid_argument("Nullptr");

			if (field->getType() != '\0')
			{
				ofs << stringFieldWithType(field);
			}
			
			ofs << '|';
		}

		if(i != rows - 1)
		ofs << '\n';
	}
}

void CSVParserSQLTable::excludeRowsInTable(const WhereExpression& expr, Vector<bool>& excludedRows) const
{
	Vector<String> columnNames = expr.getColumnNames();

	for (int i = 0; i < columnNames.getSize(); i++)
	{
		expr.excludeRow(columns.getByKey(columnNames[i].c_string()), excludedRows, i - 1);
	}
}

size_t CSVParserSQLTable::getCols() const
{
	return cols;
}

size_t CSVParserSQLTable::getRows() const
{
	return rows;
}

const Dictionary<SQLColumn>& CSVParserSQLTable::getColumns() const
{
	return columns;
}

void CSVParserSQLTable::getIndexesOfGivenColumnNames(const Vector<String>& columnNames, Vector<size_t>& indexes) const
{
	for (int i = 0; i < columnNames.getSize(); i++)
	{
		int index = (columns.contains(columnNames[i].c_string()));

		if (index == -1)
		{
			String invalidColumnName = String("The column name ") + columnNames[i] + String(" is not found in the table!");
			throw std::invalid_argument(invalidColumnName.c_string());
		}

		indexes.pushBack(index);
	}
}

void CSVParserSQLTable::printFieldValue(size_t row, size_t col, size_t len) const
{
	const PolymorphicPointer<SQLType>& field = columns[col].getFields()[row];

	printCell(stringFieldWithType(field),len);
}

const Vector<size_t> CSVParserSQLTable::getMaxLengthOnEachColumn() const
{
	Vector<size_t> lengths;

	size_t max = 0;
	size_t current = 0;

	for (int i = 0; i < cols; i++)
	{
		max = strlen(columns.getKeyByIndex(i));

		for (int j = 0; j < rows; j++)
		{
			current = stringFieldWithType(columns[i].getFields()[j]).getLength();

			if (max < current)
				max = current;		
		}

		lengths.pushBack(max);
	}

	return lengths;
}

const Vector<size_t> CSVParserSQLTable::getMaxLengthOnEachColumnByGivenColumnNames(const Vector<size_t>& indexes) const
{
	Vector<size_t> lengths;

	size_t max = 0;
	size_t current = 0;

	for (int i = 0; i < indexes.getSize(); i++)
	{
		max = strlen(columns.getKeyByIndex(indexes[i]));

		for (int j = 0; j < rows; j++)
		{
			current = stringFieldWithType(columns[indexes[i]].getFields()[j]).getLength();

			if (max < current)
				max = current;
		}

		lengths.pushBack(max);
	}

	return lengths;
}
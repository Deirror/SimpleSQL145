#pragma once
#include "WhereExpression.h"
#include "Dictionary.hpp"
#include "Vector.hpp"
#include "String.h"
#include "SQLColumn.h"

class CSVParserSQLTable
{
private:
	Dictionary<SQLColumn> columns;

	size_t rows = 0;
	size_t cols = 0;

public:
	CSVParserSQLTable() = default;

	CSVParserSQLTable(const String& filePath);

	CSVParserSQLTable(const Vector<String>& columnNames, const Vector<char>& columnTypes);

	void parseTable(std::ifstream& ifs);

	void populateFieldsOnRow(std::stringstream& ss, bool& areKeysPopulated);
	
	void addColumn(const char* columnName, char columnType, const PolymorphicPointer<SQLType>& instantiateWith = nullptr);

	void deleteColumn(const String& columnName);

	void addRows(const Vector<String>& columnNames, const Vector<Vector<String>>& rows);

	void renameColumn(const String& oldColumnName, const String& newColumnName);

	int updateRows(const String& columnName, const String& value, const WhereExpression& expr = {});

	int deleteRows(const WhereExpression& expr = {});

	int printSQLTable(const WhereExpression& expr = {}) const;

	int printSQLTableByGivenColumnNames(const Vector<String>& columnNames, const WhereExpression& expr = {}) const;

	void writeContentOfTableToFile(std::ofstream& ofs) const;

	char getTypeOfColumnByName(const String& columnName) const;

	void joinWithTable(const CSVParserSQLTable& tableToJoin, const String& columnNameOfThis, const String& columnNameOfToJoin);

	size_t getCols() const;
	size_t getRows() const;

	const Dictionary<SQLColumn>& getColumns() const;

private:
	void printFieldValue(size_t row, size_t col, size_t len) const;

	const Vector<size_t> getMaxLengthOnEachColumn() const;

	const Vector<size_t> getMaxLengthOnEachColumnByGivenColumnNames(const Vector<size_t>& indexes) const;
	
	void writeColumnNamesToFile(std::ofstream& ofs) const;

	void writeFieldsToFile(std::ofstream& ofs) const;
	
	void excludeRowsInTable(const WhereExpression& expr, Vector<bool>& exculdedRows) const;
	
	void getIndexesOfGivenColumnNames(const Vector<String>& columnNames, Vector<size_t>& indexes) const;
};


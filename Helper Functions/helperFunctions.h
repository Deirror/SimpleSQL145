#pragma once
#include "PolymorphicPointer.hpp"
#include "String.h"
#include "Vector.hpp"
#include "SQLType.h"
#include <iostream>
#include <fstream>
#include <sstream>

size_t getCountOfSymbol(std::istream& ifs, char symbol, char end = -1);

char checkPreviousCharacter(std::stringstream& ss, bool(*pred)(char ch));

String getStringWithSepartor(std::istream& ifs, char separator, bool(*pred)(char ch) = nullptr);

void skipSymbol(std::stringstream& ss, char symbol);

char toLower(char symbol);

bool specialComparer(std::stringstream& ss, const String& searched);

size_t maxLenOnColumn(const Vector<String>& columnNames);

template <class T>
String toString(const T& obj);

void printSymbol(char symbol, size_t times);

size_t getLengthWithEndChar(std::stringstream& ss, char end);

char getColumnType(std::stringstream& ss);

void addFinalSymbolToRow(char symbol);

void printLinesOnRow(size_t times, const Vector<size_t>& lengths);

void printLine(size_t len);

void printCell(const String& name, size_t len);

String stringFieldWithType(const PolymorphicPointer<SQLType>& field);

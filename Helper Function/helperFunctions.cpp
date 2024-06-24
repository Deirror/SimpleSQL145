#include "helperFunctions.h"
#include "Integer.h"
#include "Real.h"
#include "Null.h"
#include "Text.h"

size_t getCountOfSymbol(std::istream& ifs, char searched, char end)
{
	size_t count = 0;

	size_t currPos = ifs.tellg();

	while (true)
	{
		char symbol = ifs.get();

		if (searched == symbol)
			count++;

		if (ifs.eof() || symbol == end)
			break;
	}

	ifs.clear();
	ifs.seekg(currPos);

	return count;
}

char checkPreviousCharacter(std::stringstream& ss, bool(*pred)(char ch))
{
	ss.seekg(-1, std::ios::cur);

	bool result = pred(ss.peek());

	char toReturn = '\0';

	if(result)
		toReturn = ss.peek();

	ss.ignore();

	return toReturn;
}

String getStringWithSepartor(std::istream& ifs, char separator, bool(*pred)(char ch))
{
	char buff[128]{};

	int index = 0;

	while (ifs.peek() != separator && !ifs.eof())
	{
		if (pred)
		{
			if (pred(ifs.peek()))
				return String(buff);
		}

		buff[index++] = ifs.get();
	}

	ifs.ignore();

	return String(buff);
}

void skipSymbol(std::stringstream& ss, char symbol)
{
	while (ss.peek() == symbol)
	{
		ss.ignore();
	}
}

char toLower(char symbol)
{
	if (symbol >= 'A' && symbol <= 'Z')
		return symbol + ('a' - 'A');

	return symbol;
}

bool specialComparer(std::stringstream& ss, const String& searched)
{
	char ch = '\0';

	size_t currPos = ss.tellg();

	for (int i = 0; i < searched.getLength(); i++)
	{
		ch = ss.get();

		if (ch == ' ' && ss.peek() == ' ')
			skipSymbol(ss, ' ');

		if (toLower(ch) != searched[i])
		{
			ss.clear();
			ss.seekg(currPos);
			return false;
		}
	}

	return true;
}

void printSymbol(char symbol, size_t times)
{
	for (int i = 0; i < times; i++)
		std::cout << symbol;
}

size_t getLengthWithEndChar(std::stringstream& ss, char end)
{
	size_t length = 0;

	while (ss.peek() != end)
	{
		ss.ignore();
		length++;
	}

	return length;
}

char getColumnType(std::stringstream& ss)
{
	if (specialComparer(ss, "int"))
	{
		return 'i';
	}
	else if (specialComparer(ss, "real"))
	{
		return 'r';
	}
	else if (specialComparer(ss, "text"))
	{
		return 't';
	}
	else
	{
		return -1;
	}
}

void addFinalSymbolToRow(char symbol)
{
	std::cout << symbol << '\n' << '\n';
}

void printLinesOnRow(size_t times, const Vector<size_t>& lengths)
{
	for (int i = 0; i < times; i++)
	{
		printLine(lengths[i]);
	}

	addFinalSymbolToRow('o');
}

void printLine(size_t len)
{
	std::cout << 'o';
	printSymbol('-', len + 2);
}

void printCell(const String& name, size_t len)
{
	std::cout << '|' << ' ';
	std::cout << name;
	printSymbol(' ', len - name.getLength());
	std::cout << ' ';
}

String stringFieldWithType(const PolymorphicPointer<SQLType>& field)
{
	if (!field)
		throw std::invalid_argument("Nullptr");

	switch (field->getType())
	{
	case 'i':
	{
		return toString((static_cast<const Integer*>(field.get()))->getField());
	}
	case 'r':
	{
		return toString((static_cast<const Real*>(field.get()))->getField());
	}
	case 't':
	{
		return (static_cast<const Text*>(field.get()))->getField();
	}
	case '\0':
	{
		return (static_cast<const Null*>(field.get()))->getField();
	}
	default:
	{
		throw std::invalid_argument("Unkown sql type!");
	}
	}
}

size_t maxLenOnColumn(const Vector<String>& columnNames)
{
	size_t max = 0;

	for (int i = 0; i < columnNames.getSize(); i++)
	{
		if (max < columnNames[i].getLength())
			max = columnNames[i].getLength();
	}

	return max;
}

template<class T>
String toString(const T& obj)
{
	std::stringstream ss;

	ss << obj;
	
	String res;

	ss >> res;

	return res;
}

template String toString<int>(const int& obj);
template String toString<double>(const double& obj);
template String toString<unsigned int>(const unsigned int& obj);
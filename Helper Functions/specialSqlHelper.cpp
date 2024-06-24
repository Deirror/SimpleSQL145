#include "specialSqlHelper.h"

bool checkContentOfStream(std::stringstream& ss, bool(*pred)(char ch))
{
	size_t currPos = ss.tellg();

	while (!ss.eof() && pred(ss.get()));

	bool isAtEnd = ss.eof();

	ss.clear();

	ss.seekg(currPos);

	return isAtEnd;
}

bool isDigit(char ch)
{
	return (ch >= '0' && ch <= '9');
}

bool isFloatingDigit(char ch)
{
	return (isDigit(ch) || ch == '.');
}
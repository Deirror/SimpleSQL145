#pragma once
#include <sstream>

bool checkContentOfStream(std::stringstream& ss, bool(*pred)(char ch));

bool isDigit(char ch);

bool isFloatingDigit(char ch);
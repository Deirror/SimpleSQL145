#include "DirectoryPath.h"
#include <stdexcept>
#include <fstream>

DirectoryPath::DirectoryPath() : DirectoryPath("")
{

}

DirectoryPath::DirectoryPath(const String& newDirPath)
{
	setDirPath(newDirPath);
}

void DirectoryPath::setDirPath(const String& newDirPath)
{
	if (!newDirPath)
		throw std::runtime_error("Invalid path!");

	dirPath = newDirPath;

	if (!checkIfDirExists())
	{
		dirPath.clear();

		throw std::runtime_error("Directory doesn't exist!");
	}
}

const String& DirectoryPath::getDirPath() const
{
	if (!doesExist)
		throw std::runtime_error("Directory doesn't exist!");

	return dirPath;

}

String DirectoryPath::appendFileToDirPath(const String& fileName)
{
	if (!doesExist)
		throw std::runtime_error("Directory doesn't exist!");

	return String(dirPath + fileName);
}

bool DirectoryPath::checkIfDirExists() const
{
	String temp = dirPath + String(".txt");

	std::ofstream testStream(temp.c_string());

	doesExist = testStream.is_open();

	testStream.close();

	if (doesExist)
		std::remove(temp.c_string());

	return doesExist;
}
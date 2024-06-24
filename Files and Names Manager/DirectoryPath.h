#pragma once
#include "String.h"

class DirectoryPath
{
private:
	String dirPath;

	mutable bool doesExist = false;

public:
	DirectoryPath();

	DirectoryPath(const String& newDirPath);

	void setDirPath(const String& newDirPath);

	const String& getDirPath() const;

	String appendFileToDirPath(const String& fileName);

private:
	bool checkIfDirExists() const;
};


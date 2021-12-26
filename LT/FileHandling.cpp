#include "FileHandling.hpp"

std::wstring getFileFullPath(LPCWSTR fileName) {
	TCHAR** lppPart = { NULL };
	TCHAR  buffer[4096] = TEXT("");
	if (!GetFullPathNameW(fileName, 4096, buffer, lppPart)) {
		std::cerr << "Can not get full path\n";
		std::cerr << "Error: " << GetLastError() << '\n';
	}
	return (std::wstring)buffer;
}

std::string getFileFullPath(const char* fileName) {
	char** lppPart = { NULL };
	char  buffer[4096] = "";
	if (!GetFullPathNameA(fileName, 4096, buffer, lppPart)) {
		std::cerr << "Can not get full path\n";
		std::cerr << "Error: " << GetLastError() << '\n';
	}
	return (std::string)buffer;
}
/*
void printPath(LPCWSTR fileName) {
std::wcout << getPath(fileName) << '\n';
}
*/

std::string concat(const char* base, const char* top) {
	std::string mywstring = base;
	std::string mywstring1 = top;
	mywstring.pop_back();
	std::string concatted_stdstr = mywstring + mywstring1;
	return concatted_stdstr;
}

// TODO: this is a file action and will be passed to visitFiles later 
std::string getRelPath(std::string dirPath, std::string fileName) {
	std::string path = concat(dirPath.c_str(), fileName.c_str()) + "\\*";
	return path;
}

void printFileInfo(std::string fileName) {
	std::cout << "file: ";
	std::cout << fileName << '\n';
}

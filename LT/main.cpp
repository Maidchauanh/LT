#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<string>
#include<Windows.h>
#include<fstream> 

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

bool parseFile(std::string dirPath, std::string fileName) {
	std::ifstream input;
	std::string path = getRelPath(dirPath, fileName);
	path.pop_back();
	path.pop_back();
	input.open(path);
	if (!input.is_open()) {
		std::cerr << "Can not open file: " << fileName << '\n';
		return false;
	}

	int counter = 1;
	while (input) {
		std::string line; 
		std::getline(input, line);
		size_t found = line.find("TODO");
		if (found != std::string::npos) {
			found = line.find("/");
			if (found != std::string::npos) {
				if (found > 0) {
					// erase til found (var)
					line.erase(0, found);
				}
				std::cout << path << ":" << counter << " ";
				std::cout << line << '\n';
			}
		}
		counter++;
	}

	input.close();
	return true;
}

// use to check if it's a code file 
bool checkFileExtension(std::string fileName) {
	// TODO: support more file extension
	if (fileName.substr(fileName.find_last_of(".") + 1) == "cpp") {
		return true;
	}
	else {
		return false;
	}
}

// TODO: allow indentation
// TODO: generalize the function pointer, maybe use a struct of general input  
void visitFiles(std::string dirPath) {
	WIN32_FIND_DATAA findFileData;
	HANDLE hfindFile = FindFirstFileA(dirPath.c_str(), &findFileData);

	if (hfindFile != INVALID_HANDLE_VALUE) {
		while (FindNextFileA(hfindFile, &findFileData)) {
			// not print the dot 
			std::string fileName = findFileData.cFileName;
			bool notADot = !(fileName[0] == '.');
			if (notADot) {
				// if it's a directory 
				if (findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
					//std::cout << "dir: " << fileName << '\n';
					//std::cout << path << '\n';
					std::string path = getRelPath(dirPath, fileName);
					visitFiles(path);

				}
				else { // if it's a file
					//printFileInfo(fileName);
					// TODO: Parse the file to find the TODOs 
					// TODO: If it's the right format(code file) than parse it
					// TODO: Store the code file tail (different languages) in a json file, but first let's just use a normal text file
							// and store the tail in a alphabetical order and use binary search to search it 

					// TODO: check how many continuos Os to indicate the importance
					if (checkFileExtension(fileName)) {
						//std::string path = getRelPath(dirPath, fileName);
						parseFile(dirPath, fileName);
					}
				}
			}
		}
	}

	FindClose(hfindFile);
}

int main(int argc, char **argv) {
	// TODO: open folder and search recursively  - DONE 
	// FindFirstFile
	// FindNextFile 
	// FindClose
	// GetFullPathName

	// TODO: get the TODO line number, which file(show relative path), the time(day, hour, minutes) get the TODO
		// syntax: File:Line

	// TODO: add a folder tree visualization (after done) 
	std::string dirPath = ".\\*";
	visitFiles(dirPath);
	system("pause");
	return 0;
}
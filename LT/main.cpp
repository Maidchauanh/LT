#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<string>
#include<Windows.h>
#include<fstream> 
#include<vector>
#include<algorithm> 
#include<sstream> 

struct TODO{
	std::string line;
	int OsLen;
};

std::vector<TODO> gTODOs;

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

// TODO: try to make a better countOs function 
int countOs(const char *line) {
	int i = 0;
	int count = 0; 
	while (line[i] != ':') {
		i++;
		if(line[i] == 'O') 
			count++;
	}
	return count - 1;
}

// TODO: normal swap not working so i have to use iter_swap, check this for more info: https://stackoverflow.com/questions/6224830/c-trying-to-swap-values-in-a-vector
void swap(std::vector<TODO> &v, int position, int next_position) {
	// assuming your vector is called v
	std::iter_swap(v.begin() + position, v.begin() + next_position);
	// position, next_position are the indices of the elements you want to swap
}

int partition(std::vector<TODO> &arr, int low, int high)
{
	TODO pivot = arr[high];
	int left = low;
	int right = high - 1;
	while (true){
		while (left <= right && arr[left].OsLen < pivot.OsLen) left++;
		while (right >= left && arr[right].OsLen > pivot.OsLen) right--;
		if (left >= right) break;
		swap(arr, left, right);
		left++;
		right--;
	}
	swap(arr, left, high);
	return left;
}

// TODO: convert this to use std::ector 
void quickSortByOsLen(std::vector<TODO> &arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSortByOsLen(arr, low, pi - 1);
		quickSortByOsLen(arr, pi + 1, high);
	}
}


void deleteLine(std::string fileName) {
	// TODO: implement the deleteLine function 

}

bool parseAndPrintInfo(std::string dirPath, std::string fileName) {
	std::ifstream input;
	std::string path = getRelPath(dirPath, fileName);
	path.pop_back();
	path.pop_back();
	input.open(path);
	if (!input.is_open()) {
		std::cerr << "Can not open file: " << fileName << '\n';
		return false;
	}

	std::stringstream ss; 

	int counter = 1;
	while (input) {
		std::string line; 
		std::getline(input, line);
		// TODOOO: have little bugs with TODO and / keyword 
		size_t found = line.find("TODO");
		if (found != std::string::npos) {
			found = line.find("/");
			if (found != std::string::npos) {
				if (found > 0) {
					// erase til found (var)
					line.erase(0, found);
				}

				// TODO: steps of doing push into vector -> sort -> output to file 
				// TODOOOOO: output TODOs to file 
				line.erase(0, 2);
				std::string str = path  +  ":"  +  std::to_string(counter)  +  " - "  +  line  +  '\n';
				////
				TODO todo = { str, countOs(line.c_str())};
				gTODOs.push_back(todo);
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
					// TODO: Store the code file tail (different languages) in a json file, but first let's just use a normal text file, call the file LTsettings.json which contains the file extensions to parse and the keyword and format to parse(like TODO: absc)
							// and store the tail in a alphabetical order and use binary search to search it 
					
					// TODO: check how many continuos Os to indicate the importance
					// TODO: have a database to store the TODOs, hash(maybe) to check something
					if (checkFileExtension(fileName)) {
						//std::string path = getRelPath(dirPath, fileName);
						parseAndPrintInfo(dirPath, fileName);
					}
				}
			}
		}
	}

	FindClose(hfindFile);
}

void fillText(std::string line, int txtcol, int bgcol) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col = txtcol;
	SetConsoleTextAttribute(hConsole, col);
	std::cout << col << line << '\n';
	SetConsoleTextAttribute(hConsole, 15);
}

int main(int argc, char **argv) {
	// TODO: open folder and search recursively  - DONE 
	// FindFirstFile
	// FindNextFile 
	// FindClose
	// GetFullPathName

	// TODO: get the TODO line number, which file(show relative path), the time(day, hour, minutes) get the TODO - syntax: File:Line

	// TODO: print the TODOs on terminal with different colors based on their importance 
	// TODO: have a database that store the TODOs and when you delete a TODO in that file (means the TODO is done), run the program to auto delete that TODO in the code 
	// TODO: have a mechanism to know which line in the database in deleted 
	// TODO: have command line flag to specify the output database name, if not then use the default name


	// TODO: Commandline arguments options
	// TODO: User manual 
	// TODO: Add multithreading (2 threads maybe) 
	// TODO: add a folder tree visualization (after done) 

	// TODO: have history of TODOs deletion with dates and time like Git log
	// TODO: alittle bit too slow for now but it will change later, after i optimize it 

	std::string dirPath = ".\\*";
	visitFiles(dirPath);
	//std::cout << countOs("TODOOOOOOO:") << '\n';
	quickSortByOsLen(gTODOs, 0, gTODOs.size()-1);
	if (gTODOs.size() == 0) std::cout << "No TODOs, looks like you have done all of your jobs :))\n";
	else 
		for (int i = gTODOs.size() - 1; i >= 0; i--) {
			std::cout << gTODOs.at(i).line << '\n';
		}
	system("pause");
	return 0;
}
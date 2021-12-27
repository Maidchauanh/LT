#include "FileProcessing.hpp"


void deleteLine(std::string fileName) {
	// TODO: implement the deleteLine function 

}

// TODOOO: haven't test the write2file function yet 
void write2file(std::string fileName, std::string line) {
	std::ofstream file;
	file.open(fileName, std::ios::out);
	file << line;
	file.close();
}

bool parseAndPrintInfo(std::vector<TODO> &TODOs, std::string dirPath, std::string fileName) {
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

	// TODOOO: this need clean up, prevent it gets out of control and make the program more dynamic (works with different format of TODO using json file)
	int counter = 1;
	while (input) {
		std::string line; 
		std::getline(input, line);
		// TODO: have little bugs with TODO and / keyword 
		size_t found = line.find("TODO");
		if (found != std::string::npos) {
			found = line.find('/');
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
				TODOs.push_back(todo); 
			}
		}
		counter++;
	}

	input.close();
	return true;
}

// use to check if it's a code file 
bool checkFileExtension(std::string fileName) {
	std::string fileExtension = fileName.substr(fileName.find_last_of(".") + 1);

	// TODOOOOO: may be read supported file extensions from json file 
	std::vector<std::string> supportedFileExtensions = {"cpp", "hpp", "h", "js", "c", "json"};
	bool isInVect = false;
	isInVect = std::find(supportedFileExtensions.begin(), supportedFileExtensions.end(), fileExtension) != supportedFileExtensions.end();
	if (isInVect) {
		return true;
	}
	else {
		return false;
	}
}

void visitFiles(std::vector<TODO> &TODOs, std::string dirPath) {
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
					std::string path = getRelPath(dirPath, fileName);
					visitFiles(TODOs, path);
				}
				else { // if it's a file
					// TODO: have a database to store the TODOs, hash(maybe) to check something
					if (checkFileExtension(fileName)) {
						//std::string path = getRelPath(dirPath, fileName);
						parseAndPrintInfo(TODOs, dirPath, fileName);
					}
				}
			}
		}
	}
	else {
		std::cerr << "Directory/File not exists.\n Please check!!\n";
	}

	FindClose(hfindFile);
}

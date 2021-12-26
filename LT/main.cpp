#define _CRT_SECURE_NO_WARNINGS
#include<iostream> 
#include<string>
#include<Windows.h>
#include<fstream> 
#include<vector>
#include<algorithm> 
#include<sstream> 

#include "FileHandling.hpp" // the functions in this header is not meant to be used widely since it made to work only for this program purpose 
#include "FileProcessing.hpp"


void fillText(std::string line, int txtcol, int bgcol) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int col = txtcol;
	SetConsoleTextAttribute(hConsole, col);
	std::cout << col << line << '\n';
	SetConsoleTextAttribute(hConsole, 15);
}

enum CMD_OPTIONS {
};

/*
std::string parseCmdArg(int argc, char **argv) {
	// TODOOOO: based everything on linux command (man, arguments, help,...)
	// TODOOOOOOO: first off, have this syntax: lt and lt directory, if lt alone list *, if lt directory than list that directory, oke??
	if (argc == 2) {
	}
}
*/

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


	// TODOOOOOOOOO: Commandline arguments options, commandline argument process have some problem 

	// TODO: User manual 
	// TODO: Add multithreading (2 threads maybe) 
	// TODO: add a folder tree visualization (after done) 

	// TODO: have history of TODOs deletion with dates and time like Git log
	// TODO: alittle bit too slow for now but it will change later, after i optimize it 

	// Handle commandline argument right here 

	std::vector<TODO> TODOs;

	std::string dirPath = ".";
	if (argc == 2) {
		dirPath += "\\";
		dirPath += argv[1];
	}

	WIN32_FIND_DATAA findfiledata;
	HANDLE findfirstfile = FindFirstFileA(dirPath.c_str(), &findfiledata);
	if (findfirstfile != INVALID_HANDLE_VALUE) {
		if (findfiledata.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
			std::cout << "folder" << '\n';
			dirPath += "\\*";

			visitFiles(TODOs, dirPath);

			quickSortByOsLen(TODOs, 0, TODOs.size()-1);

			// TODOOOOOOO: change this to an enum 

			if (TODOs.size() == 0) std::cout << "No TODOs, looks like you have done all of your tasks :))\n";
			else {
				enum CHOICES
				{
					TERMINAL_OUTPUT,
					FILE_OUTPUT
				};

				int choice = TERMINAL_OUTPUT;
				std::string outputFileName = "TODOsList.txt";
				std::ofstream myfile(outputFileName);

				for (int i = TODOs.size() - 1; i >= 0; i--) {
					// TODOOO: have multiple choice whether to output to commandline or to file 
					// TODOOOOOOO: use switch case instead
					if (choice == TERMINAL_OUTPUT) {
						std::cout << TODOs.at(i).line << '\n';
					}

					// TODOOOOOOO: clean this up, fix the write2file function, the reason it's not working the last time is because the function is closing the file every time a line was written, may be i should use a global output file?? 
					else if (choice == FILE_OUTPUT) {
						//write2file(outputFileName, gTODOs.at(i).line);
						if (myfile.is_open()) {
							myfile << TODOs.at(i).line;
						}
						else std::cout << "Can not openfile to write\n";
					}
				}
				myfile.close();
			}

		}
		else {
			std::ifstream input;
			std::string fileName = argv[1];
			input.open(fileName);
			if (!input.is_open()) {
				std::cerr << "Can not open file: " << fileName << '\n';
				return false;
			}

			std::stringstream ss; 

			// TODOOO: this need clean up, prevent it gets out of control and make the program more dynamic (works with different format of TODO using json file)
			int lineNum = 1;
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
						line.erase(0, 2);
						std::cout << lineNum << " " << line << '\n';
						// TODO: steps of doing push into vector -> sort -> output to file 
						// TODOOOOO: output TODOs to file 
						//std::string str = path  +  ":"  +  std::to_string(lineNum)  +  " - "  +  line  +  '\n';
						////
						//TODO todo = { str, countOs(line.c_str())};
						//TODOs.push_back(todo); 
					}
				}
				lineNum++;
			}

			input.close();
				
		}
	}

	FindClose(findfirstfile);

	system("pause");
	return 0;
}
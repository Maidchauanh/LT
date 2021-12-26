#pragma once 

#include<iostream> 
#include<string> 
#include<Windows.h>
#include "FileHandling.hpp"

struct TODO{
	std::string line;
	int OsLen;
};


int countOs(const char *line) ;
void quickSortByOsLen(std::vector<TODO> &arr, int low, int high);
void write2file(std::string fileName, std::string line) ;
bool parseAndPrintInfo(std::vector<TODO> &TODOs, std::string dirPath, std::string fileName) ;
bool checkFileExtension(std::string fileName) ;
void visitFiles(std::vector<TODO> &TODOs, std::string dirPath) ;
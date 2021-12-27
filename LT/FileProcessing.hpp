#pragma once 

#include<iostream> 
#include<string> 
#include<Windows.h>
#include "FileHandling.hpp"
#include "TODO.hpp"

// i don't know how to do this but yeah this works 
extern int countOs(const char *line);

void write2file(std::string fileName, std::string line) ;
bool parseAndPrintInfo(std::vector<TODO> &TODOs, std::string dirPath, std::string fileName) ;
bool checkFileExtension(std::string fileName) ;
void visitFiles(std::vector<TODO> &TODOs, std::string dirPath) ;
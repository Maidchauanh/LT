#pragma once 

#include<iostream> 
#include<string>
#include<Windows.h>
#include<fstream> 
#include<vector>
#include<algorithm> 
#include<sstream> 

std::wstring getFileFullPath(LPCWSTR fileName) ;
std::string getFileFullPath(const char* fileName) ;
std::string concat(const char* base, const char* top) ;
std::string getRelPath(std::string dirPath, std::string fileName) ;
void printFileInfo(std::string fileName) ;

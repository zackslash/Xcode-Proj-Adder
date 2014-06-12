//
//  stringMethods.h
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
//

#include <string>
#include <vector>
#include <sstream>

#ifndef XcodeProjAdder_stringMethods_h
#define XcodeProjAdder_stringMethods_h

//Retriees file extension from file name string
std::string getFileExtensionFromFile(std::string &s);

//Retrieves filename form path string
std::string getFileNameFromPath(std::string path);

//Splits string with pre-constructed vector
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

//Splits string with new vector
std::vector<std::string> split(const std::string &s, char delim);

//Remove everything in string from delimiter onwards
std::string trimPast(const std::string &s, const std::string delimiter);

//Remove everything in string infront of delimiter
std::string trimBefore(const std::string &s, const std::string delimiter);

//Replace substring in string
std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);

#endif

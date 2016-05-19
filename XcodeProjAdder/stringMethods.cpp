//
//  stringMethods.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
#include "stringMethods.h"

std::string getFileExtensionFromFile(std::string &s)
{
    return s.substr(s.find_last_of(".") + 1);
}

std::string getFileNameFromPath(std::string path)
{
    std::string filename;
    
    size_t pos = path.find_last_of("/");
    if(pos != std::string::npos)
        filename.assign(path.begin() + pos + 1, path.end());
    else
        filename = path;
    
    return filename;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string trimPast(const std::string &s, const std::string delimiter)
{
    size_t pos = s.find(delimiter);
    std::string token = (pos != -1) ? s.substr(0, pos) : s;
    return token;
}

std::string trimBefore(const std::string &s, const std::string delimiter)
{
    size_t pos = s.find(delimiter);
    std::string token = (pos != -1) ? s.substr(pos, s.length()) : s;
    return token;
}

std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace)
{
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

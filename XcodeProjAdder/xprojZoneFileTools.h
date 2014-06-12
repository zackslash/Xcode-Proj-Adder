//
//  xprojZoneFileChecker.h
//  XcodeProjAdder
//
//  Created by Luke Hines on 12/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class ZoneFileTools
{
    public:
        //Checks if a extention file belongs in a perticular Xcode project zone (Going by default Xcode behaviour)
        static bool fileBelongsInArea(string fileExtension,string areaID);
    
        //Retrieves the .pbxproj file type identifier for extension
        static string getIdentifierForFileExtention(string fileExtention);
    
        //Checks if a specific file type is supported by this tool
        static bool isFileTypeSupported(std::string ext);
    
    private:
        static bool in_array(const string &value, const vector<string> &array);
};

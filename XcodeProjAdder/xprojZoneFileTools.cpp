//
//  xprojZoneFileChecker.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

/*
 * ADDING NEW FILE TYPES
 * ======================
 * Assuming that the file type only needs to be listed in one of the 5 groups listed in the 'Belongs in area' class
 * all that is required to add in a new file type is 
 * 1.Add its extention into 'supportedFileTypes' vector
 * 2.Set the 'Xcode File Type Identifier' for this file type (This can be found in a xcode.proj file after this file has been added)
 * 3.Enter the extension into 'eligibleFileTypes' for each group where this should appear (again this is found out by reading through a standard project.pbxproj file)
 *
 */

#include "xprojZoneFileTools.h"

//File types currently supported by this tool
vector<string> supportedFileTypes {"cpp", "h", "png", "jpg","m","swift","mp3","ttf","ogg","mm"};

//Returns the xcode file type ID for a specified file type
string ZoneFileTools::getIdentifierForFileExtention(string fileExtention)
{
    string fileIdentifier = "";
    if(fileExtention == supportedFileTypes[0])
        fileIdentifier = "sourcecode.cpp.cpp";
    else if(fileExtention == supportedFileTypes[1])
        fileIdentifier = "sourcecode.c.h";
    else if(fileExtention == supportedFileTypes[2])
        fileIdentifier = "image.png";
    else if(fileExtention == supportedFileTypes[3])
        fileIdentifier = "image.jpeg";
    else if(fileExtention == supportedFileTypes[4])
        fileIdentifier = "sourcecode.c.objc";
    else if(fileExtention == supportedFileTypes[5])
        fileIdentifier = "sourcecode.swift";
    else if(fileExtention == supportedFileTypes[6])
        fileIdentifier = "audio.mp3";
    else if(fileExtention == supportedFileTypes[9])
        fileIdentifier = "sourcecode.cpp.objcpp";
    else
        return "file";
    
    return fileIdentifier;
}

 bool ZoneFileTools::fileBelongsInArea(string fileExtension,string areaID)
{
    if(areaID == "PBXBuildFile")
    {
        vector<string> eligibleFileTypes {supportedFileTypes[0], supportedFileTypes[2], supportedFileTypes[3], supportedFileTypes[4], supportedFileTypes[5],supportedFileTypes[6],supportedFileTypes[7],supportedFileTypes[8],supportedFileTypes[9]};
        return ZoneFileTools::in_array(fileExtension, eligibleFileTypes);
    }
    else if(areaID == "PBXSourcesBuildPhase")
    {
        vector<string> eligibleFileTypes {supportedFileTypes[0], supportedFileTypes[4], supportedFileTypes[5],supportedFileTypes[9]};
        return ZoneFileTools::in_array(fileExtension, eligibleFileTypes);
    }
    else if(areaID == "PBXFileReference")
    {
        vector<string> eligibleFileTypes {supportedFileTypes[0], supportedFileTypes[1], supportedFileTypes[2], supportedFileTypes[3], supportedFileTypes[4], supportedFileTypes[5],supportedFileTypes[6],supportedFileTypes[7],supportedFileTypes[8],supportedFileTypes[9]};
        return ZoneFileTools::in_array(fileExtension, eligibleFileTypes);
    }
    else if(areaID == "PBXGroup")
    {
        vector<string> eligibleFileTypes {supportedFileTypes[0], supportedFileTypes[1], supportedFileTypes[2], supportedFileTypes[3], supportedFileTypes[4], supportedFileTypes[5],supportedFileTypes[6],supportedFileTypes[7],supportedFileTypes[8],supportedFileTypes[9]};
        return ZoneFileTools::in_array(fileExtension, eligibleFileTypes);
    }
    else if(areaID == "PBXResourcesBuildPhase")
    {
        vector<string> eligibleFileTypes {supportedFileTypes[2], supportedFileTypes[3],supportedFileTypes[6],supportedFileTypes[7],supportedFileTypes[8]};
        return ZoneFileTools::in_array(fileExtension, eligibleFileTypes);
    }
    
    return false;
}

bool ZoneFileTools::isFileTypeSupported(std::string ext)
{
    return ZoneFileTools::in_array(ext, supportedFileTypes);
}

bool ZoneFileTools::in_array(const string &value, const vector<string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}
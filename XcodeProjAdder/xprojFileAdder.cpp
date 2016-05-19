//
//  xprojFileAdder.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#include <cstdlib>

#include "xprojFileAdder.h"

void addFilesToXproj(std::string projectFileLocation, std::string sourceFilePathCSV)
{
    /* xcode projects '.xcodeproj' is actually a folder, we want to target a file within
     this folder so we append this to the users project file path input */
    projectFileLocation = projectFileLocation + "/project.pbxproj";
    
    std::string initialProjectContent = IOMethods::get_file_contents(projectFileLocation);
    std::string transformedProjectContent = initialProjectContent;
    std::vector<std::string> sourceFilePaths = split(sourceFilePathCSV, ',');
    sourceFilePaths =  IOMethods::expand_dirs(sourceFilePaths);
    std::cout <<  "\n";
    
    for(std::vector<std::string>::iterator it = sourceFilePaths.begin(); it != sourceFilePaths.end(); ++it)
    {
        std::string sourceFilePath = *it;
        std::string sourceFileName = getFileNameFromPath(sourceFilePath);
        std::string fileExt = getFileExtensionFromFile(sourceFileName);
        std::cout << sourceFilePath + "\n";
        
        //Check this tools compatiblity with file type
        if(!ZoneFileTools::isFileTypeSupported(fileExt))
        {
            std::cout <<  "\n ERROR: file type '" + fileExt +"' is currently unsupported by this tool, please remove that file from the CSV and try again (or implement it in src!)\n\n";
            exit(1);
        }
        
        //Generate UUIDs 1 & 2
        std::string UUID1 = IOMethods::generateOSXUUID();
        std::string UUID2 = IOMethods::generateOSXUUID();
        
        //PBXBuildFile section
        if (ZoneFileTools::fileBelongsInArea(fileExt, "PBXBuildFile"))
        {
            std::string buildFileSectionHeader = "/* Begin PBXBuildFile section */";
            std::string buildFileSectionEntry = "		" + UUID1 + " /* " + sourceFileName + " in Sources */ = {isa = PBXBuildFile; fileRef = " + UUID2 + " /* " + sourceFileName + " */; };";
            transformedProjectContent = ReplaceString(transformedProjectContent, buildFileSectionHeader, buildFileSectionHeader + "\n" + buildFileSectionEntry);
        }
        
        //PBXSourcesBuildPhase section
        if (ZoneFileTools::fileBelongsInArea(fileExt, "PBXSourcesBuildPhase"))
        {
            std::string PBXSourcesBuildPhaseHeader = "/* Begin PBXSourcesBuildPhase section */";
            std::string PBXSourcesBuildPhaseFooter = "/* End PBXSourcesBuildPhase section */";
            std::string initialBuildPhaseWholeSection = trimPast(transformedProjectContent, PBXSourcesBuildPhaseFooter);
            initialBuildPhaseWholeSection = trimBefore(initialBuildPhaseWholeSection, PBXSourcesBuildPhaseHeader);
            initialBuildPhaseWholeSection = trimPast(initialBuildPhaseWholeSection, ");");
            std::string transformedBuildPhaseWholeSection = initialBuildPhaseWholeSection + "    " + UUID1 + " /* " + sourceFileName + " in Sources */,\n";
            transformedProjectContent = ReplaceString(transformedProjectContent, initialBuildPhaseWholeSection, transformedBuildPhaseWholeSection);
        }
        
        //PBXFileReference section
        if (ZoneFileTools::fileBelongsInArea(fileExt, "PBXFileReference"))
        {
            std::string PBXFileReferenceHeader = "/* Begin PBXFileReference section */";
            std::string PBXFileReferenceEntry = "		" + UUID2 + " /* " + sourceFileName + " */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = " + ZoneFileTools::getIdentifierForFileExtention(fileExt) + "; name = " + sourceFileName + "; path = " + sourceFilePath + "; sourceTree = \"<group>\"; };";
            transformedProjectContent = ReplaceString(transformedProjectContent, PBXFileReferenceHeader, PBXFileReferenceHeader + "\n" + PBXFileReferenceEntry);
        }
        
        //PBXGroup section
        if (ZoneFileTools::fileBelongsInArea(fileExt, "PBXGroup"))
        {
            const std::string PBXGroupHeader="/* Begin PBXGroup section */";
            std::string initialPBXGroupWholeSection = trimBefore(transformedProjectContent, PBXGroupHeader);
            initialPBXGroupWholeSection = trimPast(initialPBXGroupWholeSection, ");");
            std::string transformedPBXGroupWhileSection = initialPBXGroupWholeSection + "    " + UUID2 + " /* " + sourceFileName + " */,\n";
            transformedProjectContent = ReplaceString(transformedProjectContent, initialPBXGroupWholeSection, transformedPBXGroupWhileSection);
        }
        
        //PBXResourcesBuildPhase section
        if (ZoneFileTools::fileBelongsInArea(fileExt, "PBXResourcesBuildPhase"))
        {
            const std::string PBXResourcesBuildHeader="/* Begin PBXResourcesBuildPhase section */";
            std::string initialPBXResourcesBuildWholeSection = trimBefore(transformedProjectContent, PBXResourcesBuildHeader);
            initialPBXResourcesBuildWholeSection = trimPast(initialPBXResourcesBuildWholeSection, ");");
            std::string transformedPBXResourcesBuildWhileSection = initialPBXResourcesBuildWholeSection + "    " + UUID1 + " /* " + sourceFileName + " */,\n";
            transformedProjectContent = ReplaceString(transformedProjectContent, initialPBXResourcesBuildWholeSection, transformedPBXResourcesBuildWhileSection);
        }
    }
    
    std::cout << "\n";
    std::cout << "New project created\n";
    
    std::ofstream out(projectFileLocation);
    out << transformedProjectContent;
    out.close();
    
    //perform intersive logic (build)
    std::cout << "Written transformed project\n";
    
    //Write backup file to perform a restore
    std::ofstream outr(projectFileLocation+"back");
    outr << initialProjectContent;
    outr.close();
    std::cout << "Restore file created\n";
    std::cout << "\nCOMPLETE\n\n";
}

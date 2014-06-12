//
//  xprojFileAdder.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
//

#include "xprojFileAdder.h"

void addFilesToXproj(std::string projectFileLocation, std::string sourceFilePathCSV)
{
    /* xcode projects '.xcodeproj' is actually a folder, we want to target a file within
     this folder so we append this to the users project file path input */
    projectFileLocation = projectFileLocation+"/project.pbxproj";
    
    std::string initialProjectContent = get_file_contents(projectFileLocation);
    std::string transformedProjectContent = initialProjectContent;
    std::vector<std::string> sourceFilePaths = split(sourceFilePathCSV, ',');
    std::cout <<  "\n";
    
    for(std::vector<std::string>::iterator it = sourceFilePaths.begin(); it != sourceFilePaths.end(); ++it)
    {
        std::string sourceFilePath = *it;
        std::string sourceFileName = getFileNameFromPath(sourceFilePath);
        std::string fileExt = getFileExtensionFromFile(sourceFileName);
        std::cout << sourceFilePath + "\n";
        
        //Generate UUIDs 1 & 2
        std::string UUID1 = generateOSXUUID();
        std::string UUID2 = generateOSXUUID();
        
        //Add to PBXBuildFile section (.cpp)
        if (fileExt == "cpp")
        {
            std::string buildFileSectionHeader = "/* Begin PBXBuildFile section */"; //Only .CPP
            std::string buildFileSectionEntry = "		" + UUID1 + " /* " + sourceFileName + " in Sources */ = {isa = PBXBuildFile; fileRef = " + UUID2 + " /* " + sourceFileName + " */; };";
            transformedProjectContent = ReplaceString(transformedProjectContent, buildFileSectionHeader, buildFileSectionHeader + "\n" + buildFileSectionEntry);
        }
        
        //Add to PBXSourcesBuildPhase section (.cpp)
        if (fileExt == "cpp")
        {
            std::string PBXSourcesBuildPhaseHeader = "/* Begin PBXSourcesBuildPhase section */";
            std::string PBXSourcesBuildPhaseFooter = "/* End PBXSourcesBuildPhase section */";
            std::string initialBuildPhaseWholeSection = trimPast(transformedProjectContent, PBXSourcesBuildPhaseFooter);
            initialBuildPhaseWholeSection = trimBefore(initialBuildPhaseWholeSection, PBXSourcesBuildPhaseHeader);
            initialBuildPhaseWholeSection = trimPast(initialBuildPhaseWholeSection, ");");
            std::string transformedBuildPhaseWholeSection = initialBuildPhaseWholeSection + "    " + UUID1 + " /* " + sourceFileName + " in Sources */,\n";
            transformedProjectContent = ReplaceString(transformedProjectContent, initialBuildPhaseWholeSection, transformedBuildPhaseWholeSection);
        }
        
        //Add to PBXFileReference section (.CPP & .h)
        if (fileExt == "cpp" || fileExt == "h")
        {
            std::string PBXFileReferenceHeader = "/* Begin PBXFileReference section */";
            
            //Determine and set file type
            std::string cppIdentifier = "sourcecode.cpp.cpp";
            std::string hIdentifier = "sourcecode.c.h";
            std::string selectedIdentifier = "";
            
            //Select our file identifier
            if(fileExt == "cpp")
                selectedIdentifier = cppIdentifier;
            else if(fileExt == "h")
                selectedIdentifier = hIdentifier;
            else //fallback to cpp
                selectedIdentifier = cppIdentifier;
            
            std::string PBXFileReferenceEntry = "		" + UUID2 + " /* " + sourceFileName + " */ = {isa = PBXFileReference; fileEncoding = 4; lastKnownFileType = " + selectedIdentifier + "; name = " + sourceFileName + "; path = " + sourceFilePath + "; sourceTree = \"<group>\"; };";
            transformedProjectContent = ReplaceString(transformedProjectContent, PBXFileReferenceHeader, PBXFileReferenceHeader + "\n" + PBXFileReferenceEntry);
        }
        
        //Add to PBXGroup section (.CPP & .h)
        if (fileExt == "cpp" || fileExt == "h")
        {
            const std::string PBXGroupHeader="/* Begin PBXGroup section */";
            std::string PBXGroupEntry= UUID2 +" /* + sourceFileName + */,\n";
            std::string initialPBXGroupWholeSection = trimBefore(transformedProjectContent, PBXGroupHeader);
            initialPBXGroupWholeSection = trimPast(initialPBXGroupWholeSection, ");");
            std::string transformedPBXGroupWhileSection = initialPBXGroupWholeSection + "    " + UUID2 + " /* " + sourceFileName + " */,\n";
            transformedProjectContent = ReplaceString(transformedProjectContent, initialPBXGroupWholeSection, transformedPBXGroupWhileSection);
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
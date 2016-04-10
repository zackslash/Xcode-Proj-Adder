//
//  main.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#include <cstring>

#include "xprojRestorer.h"
#include "xprojFileAdder.h"

/*
 * Arguments
 * ==================
 * -XCP = Xcode project location.
 * -SCSV = CSV list of source file locations relative to the xcode project you wish to add them.
 * -RESTORE = restore project file that was backed up on last run of this tool.
 */

int main(int argc, const char * argv[])
{
    std::string projectFileLocation = ""; //Example: "/Users/lukehines/Library/Developer/Xcode/DerivedData/xProjgjdr/Build/Products/Debug/TestProj/TestProj.xcodeproj";
    std::string sourceFilePathCSV = ""; //Example: "../tst1.cpp,../tst2.cpp";
    bool restore = false;

    //Get arguments
    for(int count = 1; count < argc; count++ )
    {
        if(!strcmp(argv[count], "-XCP")) //Xcode project location
        {
            projectFileLocation = argv[count+1];
        }
        if(!strcmp(argv[count], "-SCSV")) //CSV list of source file locations (that must be relative to -XCP location)
        {
            sourceFilePathCSV = argv[count+1];
        }
        if(!strcmp(argv[count], "-RESTORE")) //Flag to restore project from backup
        {
            restore = true;
        }
    }

    //Input validation
    if(restore)
    {
        if(projectFileLocation.length() <= 0)
        {
            std::cout << "Xcode project location is required for restore | \n-XCP = Xcode project location\n";
            return 1;
        }
        restoreXprojFromBackup(projectFileLocation);
        return 0;
    }

    //Input validation
    if(projectFileLocation.length() <= 0 || sourceFilePathCSV.length() <= 0)
    {
        std::cout << "atleast XCP with 1 other argument required. \n-XCP = Xcode project location (.xcodeproj) \n-SCSV = CSV list of source file locations relative to the xcode project\n-RESTORE = restore project to backup file\n";
        return 1;
    }

    addFilesToXproj(projectFileLocation, sourceFilePathCSV);

    return 0;
}

//
//  main.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
//

#include "xprojRestorer.h"
#include "xprojFileAdder.h"

/*
 *Takes arguments -XCP = Xcode project location
 *-SCSV CSV list of source file locations relative to the xcode project you wish to add them
 *(Right now only supports .cpp & .h)
 */
int main(int argc, const char * argv[])
{
    std::string projectFileLocation = ""; //"/Users/lukehines/Library/Developer/Xcode/DerivedData/xProjgjdr/Build/Products/Debug/TestProj/TestProj.xcodeproj";
    std::string sourceFilePathCSV = ""; //"../tst1.cpp,../tst2.cpp";
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
            return 0;
        }
        restoreXprojFromBackup(projectFileLocation);
        return 0;
    }
    
    //Input validation
    if(projectFileLocation.length() <= 0 || sourceFilePathCSV.length() <= 0)
    {
        std::cout << "-XCP and one other argument are required | \n-XCP = Xcode project location \n-SCSV = CSV list of source file locations relative to the xcode project\n-RESTORE = restore project to backup file\n";
        return 0;
    }
    
    addFilesToXproj(projectFileLocation, sourceFilePathCSV);
    
    return 0;
}


//
//  xprojRestorer.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#include "xprojRestorer.h"

void restoreXprojFromBackup(std::string projectFileLocation)
{
    /* xcode projects '.xcodeproj' is actually a folder, we want to target a file within
     * this folder so we append this to the users project file path input */
    projectFileLocation = projectFileLocation+"/project.pbxproj";

    std::string initialProjectContent = IOMethods::get_file_contents(projectFileLocation+"back");
    std::ofstream out(projectFileLocation);
    out << initialProjectContent;
    out.close();
    
    std::cout << "\nProject Restored\n\n";
}
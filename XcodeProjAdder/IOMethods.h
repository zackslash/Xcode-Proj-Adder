//
//  IOMethods.h
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#ifndef XcodeProjAdder_IOMethods_h
#define XcodeProjAdder_IOMethods_h

#include <iostream>
#include <fstream>
#include <string>
#include "stringMethods.h"

namespace IOMethods
{
    //Generates a 24 char UUID string in OSX
    std::string generateOSXUUID();
    
    //Retrieves file contents as string
    std::string get_file_contents(std::string filename);
    
    //Given a list if files, expand it so that all directory paths are converted to their contents
    std::vector<std::string> expand_dirs(std::vector<std::string> filenames);
}

#endif

//
//  IOMethods.h
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
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
}

#endif

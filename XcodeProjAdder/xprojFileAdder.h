//
//  xprojFileAdder.h
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#ifndef XcodeProjAdder_xprojFileAdder_h
#define XcodeProjAdder_xprojFileAdder_h

#include <iostream>
#include "stringMethods.h"
#include "IOMethods.h"
#include "xprojRestorer.h"
#include "xprojZoneFileTools.h"

//Adds a CSV list of relative (to the project) source files to an xcode project
void addFilesToXproj(std::string projectFileLocation, std::string sourceFilePathCSV);

#endif

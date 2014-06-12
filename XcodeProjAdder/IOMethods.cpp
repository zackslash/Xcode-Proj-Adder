//
//  IOMethods.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines. All rights reserved.
//

#include "IOMethods.h"

std::string IOMethods::generateOSXUUID()
{
    FILE* pipe = popen("uuidgen", "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe))
    {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    result=ReplaceString(result, "-", "");
    result.resize(24);
    return result;
}

std::string IOMethods::get_file_contents(std::string filename)
{
    try {
        std::ifstream in(filename, std::ios::in | std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }
    catch(int errNum)
    {
        std::cout << "\n\nERROR: Looks like I cannot read your Xcode project file, make sure the path to your '.xcodeproj' is fully qualified and that you have both read and write permissions\n\n";
        exit(1);
    }
}

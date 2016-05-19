//
//  IOMethods.cpp
//  XcodeProjAdder
//
//  Created by Luke Hines on 11/06/2014.
//  Copyright (c) 2014 Luke Hines.
//
//  DON'T BE A DICK PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//

#include <cerrno>
#include <cstdlib>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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



inline bool ends_with(std::string const & value, std::string const & ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
inline bool starts_with(std::string const & value, std::string const & start) {
    if (start.size() > value.size()) return false;
    return std::equal(start.begin(), start.end(), value.begin());
}

std::vector<std::string> IOMethods::expand_dirs(std::vector<std::string> filenames) {
    std::vector<std::string> result;
    
    DIR *d = NULL;
    struct dirent *dir;
    struct stat s;
    
    for (auto it = filenames.begin(); it != filenames.end(); it++) {
        std::string filename = *it;
        
        // Drop the last "/" in case of a directory
        if (ends_with(filename, "/")) {
            filename = filename.substr(0, filename.size()-1);
        }
        
        if (stat(filename.c_str(), &s) != 0) {
            continue; // error
        }
        
        if (s.st_mode & S_IFREG) {
            // Regular file: add to result
            result.push_back(filename);
        }
        
        else if( s.st_mode & S_IFDIR ) {
            // Directory
            
            d = opendir(filename.c_str());
            if (d == NULL) {
                continue; //error
            }
            
            std::vector<std::string> dir_contents;
            
            while ((dir = readdir(d)) != NULL) {
                std::string name = std::string(dir->d_name);
                
                if (starts_with(name, ".")) {
                    // ignore ".", ".." and hidden files like ".DS_STORE"
                    continue;
                }
                
                dir_contents.push_back(filename + "/" + name);
            }

            // recursive call to get contents of each subdirectory
            std::vector<std::string> dir_result = IOMethods::expand_dirs(dir_contents);
            
            // add all the files to the result
            result.insert(result.end(), dir_result.begin(), dir_result.end());
        }
    }
    
    return result;

}
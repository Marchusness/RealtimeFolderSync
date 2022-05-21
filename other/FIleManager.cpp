#include <iostream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <fstream>

#include "FileManager.h"

FileManager::FileManager(std::string _dirPath){
    dirPath = _dirPath;
    std::filesystem::create_directory(dirPath);
}

// FileManager(std::string _baseDirPath, std::string zipFilePath) { // used if you join another persons project
//     dirPath = _dirPath;
//     int err = 0;
//     zip *z = zip_open("foo.zip", 0, &err);
// }

void FileManager::writeFile(std::string _path, std::string _data) {
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    std::ofstream myfile;
    myfile.open (path);
    myfile << _data;
    myfile.close();
}

std::string FileManager::getFileData(std::string _path) {
    std::ifstream file (_path);
    std::string data = "";
    if ( file.is_open() ) {
        char mychar;
        while ( file ) {
            data += file.get();
        }
    }
    return data;
}

void FileManager::deleteFile(std::string _path) {
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    remove( path.c_str() );
}

    
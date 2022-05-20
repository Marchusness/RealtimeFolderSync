#include <iostream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <fstream>
#include "FileWatcher.h"
#include "Engine.h"
#include "FileManager.h"

FileManager::FileManager(Engine* _engine, std::string _dirPath){
    engine = _engine;
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
    std::cout << "writing file func " << path << std::endl;


    std::string directory = "";
    std::string temp = "";
    for(unsigned i = 0; i < path.length(); i++) {
        if (path.at(i) == '/') {
            directory += temp;
            std::filesystem::create_directory(directory);
            temp = "";
        }
        temp += path.at(i);
    }

    std::ofstream myfile;
    myfile.open (path);
    myfile << _data;
    myfile.close();

    engine->fileWatcher->updateFileTimes(path);
}

std::string FileManager::getFileData(std::string _path) {
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    std::ifstream file (path);
    std::string data = "";
    if ( file.is_open() ) {
        char mychar;
        while ( file ) {
            data += file.get();
        }
    }
    data.pop_back();
    return data;
}

void FileManager::deleteFile(std::string _path) {
    std::cout << "removing file " << _path << std::endl;
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    remove( path.c_str() );
}

    
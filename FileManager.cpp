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

FileManager::FileManager(std::string _testPath) {  // this is for testing
    dirPath = _testPath;
}

// FileManager(std::string _baseDirPath, std::string zipFilePath) { // used if you join another persons project
//     dirPath = _dirPath;
//     int err = 0;
//     zip *z = zip_open("foo.zip", 0, &err);
// }

void FileManager::writeFile(std::string _path, char* _data, unsigned int _dataLength) {
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    std::cout << "writing file " << path << std::endl;

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

    if (temp.at(1) != '.') {

        // int arrSize = sizeof(_data);
        std::cout << "size of data writing " << _dataLength << std::endl;
        std::ofstream(path, std::ios::binary).write(_data, _dataLength);

        engine->fileWatcher->updateFileTimes(path);
    } else {
        std::cout << "didnt write" << temp << std::endl;
    }
    
    
}

std::vector<char> FileManager::getFileData(std::string _path) {
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;

    std::ifstream input(path, std::ios::binary);

    std::vector<char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();

    return bytes;
}

void FileManager::deleteFile(std::string _path) {
    std::cout << "removing file " << _path << std::endl;
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    remove( path.c_str() );
}

    

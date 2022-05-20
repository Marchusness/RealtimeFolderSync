#include <iostream>
#include <stdio.h>
#include <string.h>
#include <filesystem>
#include <fstream>

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

void FileManager::writeFile(std::string _path, char* _data) {
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

    // int arrSize = sizeof(arr)/sizeof(arr[0]); am i good to not use this one cause char is 1 byte ?
    int arrSize = sizeof(_data);
    std::cout << "size of data writing " << arrSize << std::endl;
    std::ofstream(path, std::ios::binary).write(_data, arrSize);

    engine->fileWatcher->updateFileTimes(path);
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
    std::string path = _path;
    path.erase(0,1);
    path = dirPath + path;
    remove( path.c_str() );
}

    
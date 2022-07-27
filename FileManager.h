#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher.h"

class Engine;

class FileManager {
public:
    FileManager(Engine* engine, std::string dirPath);
    
    FileManager(std::string test);

    void writeFile(std::string path, char* data, unsigned int _dataLength);

    void writePartialFile(std::string path, unsigned int fileSize, unsigned int dataSize, char* data);

    std::vector<char> getFileData(std::string path);

    void deleteFile(std::string path);

    void deleteDirectory(std::string path);

private:
    Engine* engine;
    std::string dirPath;
};

#endif

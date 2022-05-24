#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <string.h>
#include <vector>
#include "FileWatcher.h"
#include "anAbstractClass.h"

class Engine;

class FileManager : public anAbstractClass {
public:
    FileManager(Engine* engine, std::string dirPath);
    
    FileManager(std::string test);

    void writeFile(std::string path, char* data, unsigned int _dataLength);

    std::vector<char> getFileData(std::string path);

    void deleteFile(std::string path);

    void printUselessInformation();

private:
    Engine* engine;
    std::string dirPath;
};

#endif

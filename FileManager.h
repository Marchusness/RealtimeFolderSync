#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <string.h>
#include "FileWatcher.h"

class Engine;

class FileManager {
public:
    FileManager(Engine* engine, std::string dirPath);

    // FileManager(std::string baseDirPath, std::string zipFilePath);

    void writeFile(std::string path, std::string data);

    std::string getFileData(std::string path);

    void deleteFile(std::string path);

private:
    std::string dirPath;
    Engine* engine;
};

#endif
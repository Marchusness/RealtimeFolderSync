#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <string.h>
#include "FileWatcher.h"

class FileManager {
public:
    FileManager(std::string dirPath);

    // FileManager(std::string baseDirPath, std::string zipFilePath);

    void writeFile(std::string path, char* data, FileWatcher* fw);

    const char* getFileData(std::string path);

    void deleteFile(std::string path);

private:
    std::string dirPath;
};

#endif

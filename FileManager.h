#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <string.h>
#include "FileWatcher.h"

class FileManager {
public:
    FileManager(std::string dirPath);

    // FileManager(std::string baseDirPath, std::string zipFilePath);

    void writeFile(std::string path, std::string data, FileWatcher* fw);

    std::string getFileData(std::string path);

    void deleteFile(std::string path);

private:
    std::string dirPath;
};

#endif

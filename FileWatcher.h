#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <queue>

#include "FileStatus.h"

class Engine;

class FileWatcher {
public:
    struct action {
        std::string path;
        FileStatus action;
    };

    FileWatcher(Engine* engine, std::string dirPath);

    bool check();
    action getAction(); 
    std::vector<std::string> getPaths();

    void updateFileTimes(std::string);
    void deleteFile(std::string);

private:
    Engine* engine;
    std::string dirToWatch;
    std::queue<action> changes;

    std::unordered_map<std::string, std::filesystem::file_time_type> files;
};

#endif

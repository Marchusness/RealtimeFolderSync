#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

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
    // if there is a file delete action within a folder that will be deleted it will remove the file delete
    void simplifyActions(); 
    action getAction(); 
    std::vector<std::string> getPaths();

    void updateFileTimes(std::string);
    void deleteFile(std::string);
    void deleteDirectory(std::string);

private:
    Engine* engine;
    std::string dirToWatch;

    std::queue<std::string> dirDeletes;
    std::queue<action> fileChanges;

    std::unordered_map<std::string, std::filesystem::file_time_type> files;
    std::unordered_set<std::string> directories;
    // std::vector<std::string> directories;
};

#endif

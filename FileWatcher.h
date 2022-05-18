#ifndef FILEWATCHER_H
#define FILEWATCHER_H
#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_map>

#include "FileStatus.h"


class FileWatcher {
public:
    FileWatcher(std::string dirPath, std::chrono::duration<int, std::milli> delay);

    void startWatching(const std::function<void (std::string, FileStatus)> &action);

    void stopWatching();

private:
    std::string dirToWatch;
    bool watching = true;
    std::chrono::duration<int, std::milli> delay;

    std::unordered_map<std::string, std::filesystem::file_time_type> files;

    bool contains(const std::string &key) {
        auto el = files.find(key);
        return el != files.end();
    }
};

#endif

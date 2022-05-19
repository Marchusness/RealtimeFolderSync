#include <iostream>
#include <string.h>
#include <filesystem>
#include <unordered_map>
#include <thread>

#include "FileWatcher.h"
#include "FileStatus.h"

FileWatcher::FileWatcher(std::string _dirPath){
    dirToWatch = _dirPath;
}

bool FileWatcher::check() {
    bool changed = false;
    auto it = files.begin();
    while (it != files.end()) {
        if (!std::filesystem::exists(it->first)) {
            action a;
            a.path = it->first;
            a.action = FileStatus::erased;
            changes.push(a);
            it = files.erase(it);
            changed = true;
        }
        else {
            it++;
        }                    
    }

    for(auto &file : std::filesystem::recursive_directory_iterator(dirToWatch)) {
        auto current_file_last_write_time = std::filesystem::last_write_time(file);

        if(files.find(file.path().string()) == files.end()) {
            files[file.path().string()] = current_file_last_write_time;
            action a;
            a.path = file.path().string();
            a.action = FileStatus::created;
            changes.push(a);
            changed = true;
        } else if(files[file.path().string()] != current_file_last_write_time) {
            files[file.path().string()] = current_file_last_write_time;
            action a;
            a.path = file.path().string();
            a.action = FileStatus::modified;
            changed = true;
        }
    }
    return changed;
}

FileWatcher::action FileWatcher::getAction()
{
    if (changes.size() > 0)
    {
        action a = changes.front();
        changes.pop();
        return a;
    }
    else
    {
        action a;
        a.action = FileStatus::none;
        return a;
    }
}

std::vector<std::string> FileWatcher::getPaths()
{
    std::vector<std::string> filePaths;
    for (auto it : files)
    {
        filePaths.push_back(it.first);
    }
    return filePaths;
}
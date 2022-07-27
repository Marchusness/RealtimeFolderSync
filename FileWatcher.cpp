#include <iostream>
#include <string.h>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <thread>

#include "FileWatcher.h"
#include "FileStatus.h"

FileWatcher::FileWatcher(Engine* _engine, std::string _dirPath){
    engine = _engine;
    dirToWatch = _dirPath;
}

bool FileWatcher::check() {
    bool changed = false;
    auto it = files.begin();
    while (it != files.end()) {
        if (!std::filesystem::exists(it->first)) {
            std::filesystem::path path = it->first;
            if (std::filesystem::exists(path.parent_path())){
                action a;
                a.path = it->first;
                a.path = a.path.erase(1,dirToWatch.length()-1);
                a.action = FileStatus::erased;
                fileChanges.push(a);
                it = files.erase(it);
                changed = true;
            } else {
                it = files.erase(it);
            }
        }
        else {
            it++;
        }                    
    }
    
    if (!directories.empty()) {
        for(auto it = directories.begin(); it != directories.end(); ) {
            if (!std::filesystem::exists(*it)) {
                std::filesystem::path path = *it;
                if (std::filesystem::exists(path.parent_path())){
                    dirDeletes.push(path.string().erase(1,dirToWatch.length()-1));
                    it = directories.erase(it);
                    changed = true;
                } else {
                    it++;
                }                
            }
            else {
                it++;
            }
        }
    }
    
    try {
        for(auto &file : std::filesystem::recursive_directory_iterator(dirToWatch)) {
            if (std::filesystem::is_regular_file(file.path())) {
                auto curFileLastWriteTime = std::filesystem::last_write_time(file);
                if(files.find(file.path().string()) == files.end()) {
                    files[file.path().string()] = curFileLastWriteTime;
                    action a;
                    a.path = file.path().string().erase(1,dirToWatch.length()-1);
                    a.action = FileStatus::created;
                    fileChanges.push(a);
                    changed = true;
                } else if(files[file.path().string()] != curFileLastWriteTime) {
                    files[file.path().string()] = curFileLastWriteTime;
                    action a;
                    a.path = file.path().string().erase(1,dirToWatch.length()-1);
                    a.action = FileStatus::modified;
                    fileChanges.push(a);
                    changed = true;
                }
            } 
            else if (std::filesystem::is_directory(file.path())) {
                directories.insert(file.path().string());
            }
        }
    }
    catch(std::filesystem::filesystem_error e)
    {
        std::cout << e.what() << std::endl;
    }
    return changed;
}

FileWatcher::action FileWatcher::getAction()
{
    if (!dirDeletes.empty())
    {
        action a;
        a.action = FileStatus::dirErased;
        a.path = dirDeletes.front();
        dirDeletes.pop();
        return a;
    }

    if (!fileChanges.empty())
    {
        action a = fileChanges.front();
        fileChanges.pop();
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
        filePaths.push_back(std::string(it.first).erase(1,dirToWatch.length()-1));
    }
    return filePaths;
}

void FileWatcher::updateFileTimes(std::string _path) {
    std::filesystem::path path = _path;
    files[path.string()] = std::filesystem::last_write_time(path);
}

void FileWatcher::deleteFile(std::string _path) {
    files.erase(_path);
}

void FileWatcher::deleteDirectory(std::string _path) {
    directories.erase(_path);
}
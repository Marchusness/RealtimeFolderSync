#include <iostream>
#include <string.h>
#include <filesystem>
#include <unordered_map>
#include <thread>

#include "FileWatcher.h"
#include "FileStatus.h"

FileWatcher::FileWatcher(std::string _dirPath, std::chrono::duration<int, std::milli> _delay){
    dirToWatch = _dirPath;
    delay = _delay;
}

void FileWatcher::startWatching(const std::function<void (std::string, FileStatus)> &action) {
    watching = true;
    while(watching) {
        // Wait for "delay" milliseconds
        std::this_thread::sleep_for(delay);

        auto it = files.begin();
        while (it != files.end()) {
            if (!std::filesystem::exists(it->first)) {
                action(it->first, FileStatus::erased);
                it = files.erase(it);
            }
            else {
                it++;
            }                    
        }

        for(auto &file : std::filesystem::recursive_directory_iterator(dirToWatch)) {
            auto current_file_last_write_time = std::filesystem::last_write_time(file);

            if(!contains(file.path().string())) {
                files[file.path().string()] = current_file_last_write_time;
                action(file.path().string(), FileStatus::created);
            } else {
                if(files[file.path().string()] != current_file_last_write_time) {
                    files[file.path().string()] = current_file_last_write_time;
                    action(file.path().string(), FileStatus::modified);
                }
            }
        }
    }
}

void FileWatcher::stopWatching() {
    watching = false;
}



    
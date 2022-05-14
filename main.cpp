#include <iostream>
#include "FileWatcher.h"
#include "FileManager.h"
#include "FileStatus.h"

int main() {
    FileWatcher fw{"./", std::chrono::milliseconds(5000)};

    fw.startWatching([] (std::string path_to_watch, FileStatus status) -> void {
        // Process only regular files, all other file types are ignored
        FileManager fm{"../testing"};
        if(!std::filesystem::is_regular_file(std::filesystem::path(path_to_watch)) && status != FileStatus::erased) {
            return;
        }

        if (status == FileStatus::created || status == FileStatus::modified) {
            std::cout << "File created or modified: " << path_to_watch << '\n';

            std::string data = fm.getFileData(path_to_watch);

            fm.writeFile(path_to_watch, data);

        } else if (status == FileStatus::erased) {
            std::cout << "File erased: " << path_to_watch << '\n';

            fm.deleteFile(path_to_watch);

        } else {
            std::cout << "Error! Unknown file status.\n";
        }

    });
}

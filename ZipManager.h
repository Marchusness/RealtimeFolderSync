#ifndef ZIPMANAGER_H
#define ZIPMANAGER_H
#include <iostream>
#include <string.h>

class ZipManager {
    private:
        static bool is_dir(const std::string& dir);
        static void walk_directory(const std::string& startdir, const std::string& inputdir, zip_t *zipper);
    public:
        static void zip_directory(const std::string& inputdir, const std::string& output_filename);
};
#endif
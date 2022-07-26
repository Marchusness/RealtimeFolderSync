#include <iostream>
#include <string.h>
#include "FileManager.h"
int main(){

    FileManager fm = FileManager("./Test");
    
    std::vector<char> initialData = fm.getFileData("./test.png");

    char* cdata = initialData.data();

    char* Cdata = reinterpret_cast<char* >(cdata);

    char* filedata = new char[initialData.size()];
    memcpy(filedata, Cdata, initialData.size());

    fm.writeFile("./new.png", Cdata, initialData.size());

    std::vector<char> afterData = fm.getFileData("./new.png");

    if (afterData == initialData) {
        std::cout << "it worked" << std::endl;
    } else {
        std::cout << "it did in fact not work" << std::endl;

    }

    std::vector<char> original = fm.getFileData("./brew.rtf");
    std::vector<char> corrupt = fm.getFileData("./brew1.rtf");

    if (original == corrupt) {
        std::cout << "well it worked" << std::endl;
    } else {
        std::cout << "well it didnt work" << std::endl;
        std::string s(original.begin(), original.end());
        std::cout << s << std::endl;
        std::string e(corrupt.begin(), corrupt.end());
        std::cout << e << std::endl;

    }



    return 0;
}

// run with g++ -std=c++2a test.cpp FileManager.cpp
#include <iostream>
#include <string.h>
#include "FileManager.h"
int main(){

    FileManager fm = FileManager("./Test");
    
    std::vector<char> initialData = fm.getFileData("./test.png");

    char* cdata = initialData.data();

    fm.writeFile("./new.png", cdata, initialData.size());

    std::vector<char> afterData = fm.getFileData("./new.png");

    if (afterData == initialData) {
        std::cout << "it worked" << std::endl;
    } else {
        std::cout << "it did in fact not work" << std::endl;

    }





    return 0;
}

// run with g++ -std=c++2a test.cpp FileManager.cpp
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream> 

std::vector<char> load_file(std::string path){
    std::ifstream input(path, std::ios::binary);

    std::vector<char> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();

    return bytes;
}

int main(){
    
    std::vector<char> bytes = load_file("hello.txt");

    std::ofstream("after.txt", std::ios::binary).write(bytes.data(), bytes.size());

}


// run with {g++ -Wall readWrite.cpp }
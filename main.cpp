#include <iostream>
#include "Engine.h"

int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        std::cout << "needs <Sync path> <Port> <address>" << std::endl;
    }
    std::string syncPath = argv[1];
    int port = std::stoi(argv[2]);
    Engine* engine;
    if (argc < 4)
    {
        engine = new Engine(syncPath, port);
    }
    else
    {
        std::string address = argv[3];
        engine = new Engine(syncPath, port, address);
    }
    engine->loop();
    delete engine;
    return 0;
}

#include <iostream>
#include "Engine.h"

int main(int argc, char const *argv[])
{
    std::string syncPath;
    while (syncPath.length() == 0)
    {
        std::cout << "Enter a folder path to sync" << std::endl;
        getline(std::cin, syncPath);
    }
    int port = 0;
    std::string portString;
    while (port == 0)
    {
        std::cout << "Enter a port number" << std::endl;
        getline(std::cin, portString);
        try
        {
            port = std::stoi(portString);
        }
        catch(const std::exception& e)
        {
        }
    }
    std::string address;
    std::cout << "Enter an address to connect to or nothing to start a server" << std::endl;
    getline(std::cin, address);

    Engine* engine;
    if (address.length() == 0)
    {
        std::cout << "Starting server with folder path " << syncPath << " on port " << port << std::endl;
        engine = new Engine(syncPath, port);
    }
    else
    {
        std::cout << "Connecting to address " << address << " with folder path " << syncPath << " on port " << port << std::endl;
        engine = new Engine(syncPath, port, address);
    }
    engine->loop();
    delete engine;
    return 0;
}

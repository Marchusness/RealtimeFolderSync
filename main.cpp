#include <iostream>
#include <filesystem>
#include "Engine.h"


int main(int argc, char const *argv[])
{
    // gets the server address from the user
    std::string address;
    std::cout << "Enter an address to connect to or nothing to start a server" << std::endl;
    getline(std::cin, address);


    // gets the port number from the user
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


    // gets the folder to sync from the user
    std::string syncPath;
    while (syncPath.length() == 0)
    {
        std::cout << "Enter a relative folder path to sync" << std::endl;
        getline(std::cin, syncPath);
    }
    std::filesystem::path path = syncPath;
    // continue if the path is relative and (is a server or the path doesnt exist or is empty)
    // not the continue condition
    while (!(path.is_relative() && (address.length() == 0 || (!std::filesystem::exists(path) || std::filesystem::is_empty(path))))) {

        std::cout << "Folder path must be relative to your current working directory" << std::endl;
        if (address.length() > 0){
            std::cout << "If you are connecting to a server your syncing folder must not exist or must be empty" << std::endl;
        }
        getline(std::cin, syncPath);
        path = syncPath;
    }


    // startes the engine
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

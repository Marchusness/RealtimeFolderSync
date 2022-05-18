#include <iostream>
#include "Engine.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cout << "needs atleast a port" << std::endl;
    }
    int port = 0;
    std::cin >> port;
    Engine* engine;
    if (argc < 3)
    {
        engine = new Engine(port);
    }
    else
    {
        std::string address;
        std::cin >> address; 
        engine = new Engine(port, address);
    }
    engine->loop();
    delete engine;
    return 0;
}

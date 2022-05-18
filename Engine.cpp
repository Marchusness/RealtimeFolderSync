#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"
#include "FileStatus.h"
#include "TCPListener.h"
#include "TCPStream.h"s

Engine::Engine(int port)
{
    tCPListener = new TCPListener(port);
}

Engine::Engine(int port, std::string address)
{
    tCPStream = TCPStream::connectTo(address.c_str(), port);
}

Engine::~Engine()
{
    if (tCPStream)
    {
        delete tCPStream;
    }
    if (tCPListener)
    {
        delete tCPListener;
    }
    delete fileManager;
    delete fileWatcher;
}

void Engine::loop()
{
    if (!(tCPListener || tCPStream)) //check connected
    {
        return;
    }
    
    bool running;
    while (running)
    {
        //do file checks
        fileWatcher->check();
        FileWatcher::action a;
        while ((a = fileWatcher->getAction()).action != FileStatus::none)
        {
            //a change occoured
        }
        

        //do networking checks

    }
}

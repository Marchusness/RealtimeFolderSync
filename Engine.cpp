#include <chrono>
#include <thread>

#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"
#include "FileStatus.h"
#include "TCPListener.h"
#include "TCPStream.h"
#include "Packet.h"
#include "PacketTypes.h"

Engine::Engine(std::string syncPath, int port)
{
    tCPListener = new TCPListener(port);
    fileWatcher = new FileWatcher(syncPath);
    fileManager = new FileManager(syncPath);
}

Engine::Engine(std::string syncPath, int port, std::string address)
{
    tCPStream = TCPStream::connectTo(address.c_str(), port);
    fileWatcher = new FileWatcher(syncPath);
    fileManager = new FileManager(syncPath);
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
    //if (!(tCPListener || tCPStream)) //check connected
    {
     //   return;
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
            if (a.action == FileStatus::created || a.action == FileStatus::modified)
            {
                std::string filedata = fileManager->getFileData(a.path);
                Packet_WriteFile* p = new Packet_WriteFile(a.path, filedata);
            }
        }
        

        //do networking checks
        if (tCPListener)
        {
            tCPListener->check();
        }
        
        Packet* p;
        while ((p = getPacket()))
        {
            p->exicute(this);
        }

        //pause
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Engine::sendPacket(Packet* p)
{
    if (tCPListener)
    {
        tCPListener->sendToAll(p);
    }
    else
    {
        tCPStream->write(p);
    }
}

Packet* Engine::getPacket()
{
    if (tCPListener)
    {
        return tCPListener->getPacketInQueue();
    }
    else
    {
        return tCPStream->tryReadPacket();
    }
}
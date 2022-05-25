#include <chrono>
#include <thread>
#include <signal.h>
#include <stdlib.h>

#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"
#include "FileStatus.h"
#include "TCPListener.h"
#include "TCPStream.h"
#include "Packet.h"
#include "PacketTypes.h"

Engine* Engine::engine = nullptr;

Engine::Engine(std::string syncPath, int port)
{
    if (!engine)
    {
        engine = this;
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = Engine::escapeHandler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
    }
    
    tCPListener = new TCPListener(port);
    fileWatcher = new FileWatcher(this, syncPath);
    fileManager = new FileManager(this, syncPath);
}

Engine::Engine(std::string syncPath, int port, std::string address)
{
    if (!engine)
    {
        engine = this;
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = Engine::escapeHandler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
    }

    tCPStream = TCPStream::connectTo(address.c_str(), port);
    fileWatcher = new FileWatcher(this, syncPath);
    fileManager = new FileManager(this, syncPath);
}

Engine::~Engine()
{
    running = false;
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

    //using an abstract class
    anAbstractClass* a = fileManager;
    a->printUselessInformation();

    running = true;
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
                std::vector<char> filedata = fileManager->getFileData(a.path);
                Packet_WriteFile* p = new Packet_WriteFile(a.path, filedata.data(), filedata.size());
                sendPacket((Packet*)p);
                delete p;
            }
            if (a.action == FileStatus::erased){
                Packet_DeletePath* p = new Packet_DeletePath(a.path);
                sendPacket((Packet*)p);
                delete p;
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
            delete p;
        }

        //pause
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Engine::escapeHandler(int s)
{
    engine->running = false;
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

void Engine::sendPacket(Packet* p, TCPStream* stream)
{
    if (tCPListener)
    {
        tCPListener->sendToAll(p, stream);
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
        Packet* p = tCPStream->tryReadPacket(); 
        if (p)
        {
            if (p->getType() == 1)
            {
                delete p;
                escapeHandler(0);
                return nullptr;
            }
        }
        return p; 
    }
}

#include <iostream>

#include "TCPListener.h"
#include "PacketTypes.h"
#include "TCPStream.h"
#include "Packet.h"
#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"


/*      PACKET_CLOSED      */


Packet_Closed::Packet_Closed(TCPStream* stream) : Packet(stream, 1)
{
}

Packet_Closed::Packet_Closed() : Packet(1, 0)
{ 
}

Packet_Closed::~Packet_Closed()
{
}


/*         PACKET_WRITEFILE         */


Packet_WriteFile::Packet_WriteFile(TCPStream* stream) : Packet(stream, 2)
{
}

Packet_WriteFile::Packet_WriteFile(std::string path, char* _filedata, unsigned int len) : Packet(2, path.size() + len + INITIALPACKETSIZE + 10)
{
    this->path = path;
    this->filedatalen = len;
    filedata = new char[filedatalen];
    memcpy(filedata, _filedata, filedatalen);
}

Packet_WriteFile::~Packet_WriteFile()
{
    delete[] filedata;
}

char* Packet_WriteFile::toByteArray()
{
    addToByteArray(path);
    addToByteArray(&filedatalen, sizeof(filedatalen));
    addToByteArray(filedata, filedatalen);
    writeHeader();
    return data;
}

bool Packet_WriteFile::read()
{
    if (!Packet::read())
    {
        return false;
    }
    readFromByteArray(path);
    readFromByteArray(&filedatalen, sizeof(filedatalen));
    filedata = new char[filedatalen];
    readFromByteArray(filedata, filedatalen);

    return true;
}

void Packet_WriteFile::exicute(Engine* engine)
{
    engine->fileManager->writeFile(path, filedata, filedatalen);
    if (engine->tCPListener)
    {
        Packet* p = new Packet_WriteFile(path, filedata, filedatalen);
        engine->tCPListener->sendToAll(p, stream);
        delete p;
    }
}


/*        PACKET_DELETEPATH         */


Packet_DeletePath::Packet_DeletePath(TCPStream* stream) : Packet(stream,3)
{
}

Packet_DeletePath::Packet_DeletePath(std::string path) : Packet(3, path.size() + INITIALPACKETSIZE + 10)
{
    this->path = path;
}

Packet_DeletePath::~Packet_DeletePath()
{
}

char* Packet_DeletePath::toByteArray()
{
    addToByteArray(path);
    writeHeader();
    return data;
}

bool Packet_DeletePath::read()
{
    if (!Packet::read())
    {
        return false;
    }
    readFromByteArray(path);

    return true;
}

void Packet_DeletePath::exicute(Engine* engine)
{
    engine->fileManager->deleteFile(path);
    engine->fileWatcher->deleteFile(path);
    if (engine->tCPListener)
    {
        Packet* p = new Packet_DeletePath(path);
        engine->sendPacket(p, stream);
        delete p;
    }
}
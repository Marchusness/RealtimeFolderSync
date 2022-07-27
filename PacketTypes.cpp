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


/*        PACKET_DIRECTORYDELETE         */


Packet_DeleteDir::Packet_DeleteDir(TCPStream* stream) : Packet(stream,4)
{
}

Packet_DeleteDir::Packet_DeleteDir(std::string path) : Packet(4, path.size() + INITIALPACKETSIZE + 10)
{
    this->path = path;
}

Packet_DeleteDir::~Packet_DeleteDir()
{
}

char* Packet_DeleteDir::toByteArray()
{
    addToByteArray(path);
    writeHeader();
    return data;
}

bool Packet_DeleteDir::read()
{
    if (!Packet::read())
    {
        return false;
    }
    readFromByteArray(path);

    return true;
}

void Packet_DeleteDir::exicute(Engine* engine)
{
    engine->fileManager->deleteDirectory(path);
    engine->fileWatcher->deleteDirectory(path);
    if (engine->tCPListener)
    {
        Packet* p = new Packet_DeletePath(path);
        engine->sendPacket(p, stream);
        delete p;
    }
}


/*         PACKET_WRITEPARTIAL         */


Packet_PartialWrite::Packet_PartialWrite(TCPStream* stream) : Packet(stream, 5)
{
}

Packet_PartialWrite::Packet_PartialWrite(std::string path, unsigned int fileSize, unsigned int dataSize, char* data, unsigned int packetNumber) : Packet(5, path.size() + dataSize + INITIALPACKETSIZE + 20)
{
    this->path = path;
    this->fileSize = fileSize;
    this->dataSize = dataSize;
    this->packetNumber = packetNumber;
    partialData = new char[dataSize];
    memcpy(partialData, data, dataSize);
}

Packet_PartialWrite::~Packet_PartialWrite()
{
    //this should cause a memory leak having it commented but adding it back causes a double free
    //delete[] partialData;
}

char* Packet_PartialWrite::toByteArray()
{
    addToByteArray(path);
    addToByteArray(&fileSize, sizeof(fileSize));
    addToByteArray(&dataSize, sizeof(dataSize));
    addToByteArray(&packetNumber, sizeof(packetNumber));
    addToByteArray(partialData, dataSize);
    writeHeader();
    return data;
}

bool Packet_PartialWrite::read()
{
    if (!Packet::read())
    {
        return false;
    }
    readFromByteArray(path);
    readFromByteArray(&fileSize, sizeof(fileSize));
    readFromByteArray(&dataSize, sizeof(dataSize));
    readFromByteArray(&packetNumber, sizeof(packetNumber));
    partialData = new char[dataSize];
    readFromByteArray(partialData, dataSize);

    return true;
}

void Packet_PartialWrite::exicute(Engine* engine)
{
    if (packetNumber == 0)
    {
        engine->fileManager->deleteFile(path);
    }
    
    engine->fileManager->writePartialFile(path, fileSize, dataSize, partialData);
    if (engine->tCPListener)
    {
        Packet* p = new Packet_PartialWrite(path, fileSize, dataSize, data, packetNumber);
        engine->tCPListener->sendToAll(p, stream);
        delete p;
    }
}

unsigned int Packet_PartialWrite::getPacketNumber()
{
    return packetNumber;
}
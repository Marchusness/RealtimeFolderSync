#include <iostream>

#include "PacketTypes.h"
#include "TCPStream.h"
#include "Packet.h"
#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"

Packet_Closed::Packet_Closed(TCPStream* stream) : Packet(stream, 1)
{
}

Packet_Closed::Packet_Closed() : Packet(1, 0)
{
}

Packet_Closed::~Packet_Closed()
{
}

Packet_WriteFile::Packet_WriteFile(TCPStream* stream) : Packet(stream, 2)
{
}

Packet_WriteFile::Packet_WriteFile(std::string path, const char* filedata) : Packet(2, path.size() + strlen(filedata) + INITIALPACKETSIZE + 10)
{
    this->path = path;
    this->filedata = filedata;
}

Packet_WriteFile::~Packet_WriteFile()
{
}

char* Packet_WriteFile::toByteArray()
{
    addToByteArray(path);
    // addToByteArray(filedata);
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
    // readFromByteArray(filedata);

    return true;
}

void Packet_WriteFile::exicute(Engine* engine)
{
    engine->fileManager->writeFile(path, data, engine->fileWatcher);
}

Packet_RequestFile::Packet_RequestFile(TCPStream* stream) : Packet(stream, 3)
{
}

Packet_RequestFile::Packet_RequestFile(std::string path) : Packet(3, 50)
{
    this->path = path;
}

Packet_RequestFile::~Packet_RequestFile()
{
}

char* Packet_RequestFile::toByteArray()
{
    addToByteArray(path);
    writeHeader();
    return data;
}

bool Packet_RequestFile::read()
{
    if (!Packet::read())
    {
        return false;
    }
    readFromByteArray(path);
    return true;
}

void Packet_RequestFile::exicute(Engine* engine)
{
    //read file
    const char* fileData = engine->fileManager->getFileData(path);
    //send file back
    Packet_WriteFile* p = new Packet_WriteFile(path, fileData);
    stream->write((Packet*)p);
    delete p;
}

Packet_GetPaths::Packet_GetPaths(TCPStream* stream) : Packet(stream, 4)
{
}

Packet_GetPaths::Packet_GetPaths() : Packet(4, 0)
{
}

Packet_GetPaths::~Packet_GetPaths()
{
}

//gets all the files being watched and sends them back to the socket that asked
void Packet_GetPaths::exicute(Engine* engine)
{
    Packet_UpdatePaths* p = new Packet_UpdatePaths();
    p->paths = engine->fileWatcher->getPaths();
    stream->write((Packet*)p);
    delete p;
}


Packet_UpdatePaths::Packet_UpdatePaths(TCPStream* stream) : Packet(stream, 5)
{
}

Packet_UpdatePaths::Packet_UpdatePaths() : Packet(5, 1024)  //random guess at a large size
{
}

Packet_UpdatePaths::~Packet_UpdatePaths()
{
}

char* Packet_UpdatePaths::toByteArray()
{
    unsigned int numPaths;
    unsigned int len = paths.size();
    addToByteArray(&len, sizeof(len));
    for (auto file : paths)
    {
        addToByteArray(file);
    }

    writeHeader();
    return data;
}

bool Packet_UpdatePaths::read()
{
    if (!Packet::read())
    {
        return false;
    }
    unsigned int numPaths;
    readFromByteArray(&numPaths, sizeof(numPaths));
    for (unsigned int i = 0; i < numPaths; i++)
    {
        std::string path;
        readFromByteArray(path);
        paths.push_back(path);
    }
    return true;
}

void Packet_UpdatePaths::exicute(Engine* engine)
{
    for (std::string path : paths)
    {
        std::cout << "update path " << path << std::endl;
    }
}

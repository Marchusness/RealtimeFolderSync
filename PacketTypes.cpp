#include <iostream>

#include "TCPListener.h"
#include "PacketTypes.h"
#include "TCPStream.h"
#include "Packet.h"
#include "Engine.h"
#include "FileManager.h"
#include "FileWatcher.h"

Packet_WriteFile::Packet_WriteFile(TCPStream* stream) : Packet(stream, 2)
{
}

Packet_WriteFile::Packet_WriteFile(std::string path, char* _filedata, unsigned int len) : Packet(2, path.size() + len + INITIALPACKETSIZE + 10)
{
    std::cout << len << std::endl;
    std::cout << path << std::endl;
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
    std::cout << "got file " << path << std::endl;
    engine->fileManager->writeFile(path, data);
}
















Packet_DeletePath::Packet_DeletePath(TCPStream* stream) : Packet(stream, 1)
{
}

Packet_DeletePath::Packet_DeletePath(std::string path, std::string filedata) : Packet(1, path.size() + filedata.size() + INITIALPACKETSIZE + 10)
{
    this->path = path;
    this->filedata = filedata;
}

Packet_DeletePath::~Packet_DeletePath()
{
}

char* Packet_DeletePath::toByteArray()
{
    addToByteArray(path);
    addToByteArray(filedata);
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
    readFromByteArray(filedata);

    return true;
}

void Packet_DeletePath::exicute(Engine* engine)
{
    std::cout << "delete file excecute" << std::endl;
    engine->fileManager->deleteFile(path);
    engine->fileWatcher->deleteFile(path);
    if (engine->tCPListener)
    {
        std::string filedata = "fuck";

        Packet* p = new Packet_DeletePath(path, filedata);
        engine->tCPListener->sendToAll(p, stream);
    }   
}















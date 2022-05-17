#include <iostream>

#include "PacketTypes.h"
#include "TCPStream.h"
#include "Packet.h"

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

Packet_WriteFile::Packet_WriteFile() : Packet(2, 0)
{
}

Packet_WriteFile::~Packet_WriteFile()
{
    delete[] path;
    delete[] file;
}

void Packet_WriteFile::exicute()
{

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

void Packet_GetPaths::exicute()
{
    std::cout << "please give me the paths i require" << std::endl;
    Packet_UpdatePaths* p = new Packet_UpdatePaths();
    stream->write((Packet*)p);
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
    unsigned int numPaths = 1;
    std::string aFile("/some/path/idk.txt");

    addToByteArray(&numPaths, sizeof(numPaths));
    addToByteArray(aFile);
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

void Packet_UpdatePaths::exicute()
{
    for (std::string path : paths)
    {
        std::cout << "update path " << path << std::endl;
    }
}

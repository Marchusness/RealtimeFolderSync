#ifndef H_PACKETTYPES
#define H_PACKETTYPES

#include <vector>
#include <string>
#include "Packet.h"

class Engine;

//used to tell the listener or reader that this stream has been closed
class Packet_Closed : public Packet //1
{
public:
    Packet_Closed(TCPStream* stream);
    Packet_Closed();
    ~Packet_Closed();
};

//writes a file
class Packet_WriteFile : public Packet //2
{
private:
    std::string path;
    char* filedata;
    unsigned int filedatalen;

public:
    Packet_WriteFile(TCPStream* stream);                                                     //read from socket constructor
    Packet_WriteFile(std::string path, char* data, unsigned int length);                     //going to be sent on socket constructor
    ~Packet_WriteFile();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};

//delete file
class Packet_DeletePath : public Packet //3
{
private:
    std::string path;
public:
    Packet_DeletePath(TCPStream* stream);
    Packet_DeletePath(std::string path);
    ~Packet_DeletePath();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};

//delete directory
class Packet_DeleteDir : public Packet //4
{
private:
    std::string path;
public:
    Packet_DeleteDir(TCPStream* stream);
    Packet_DeleteDir(std::string path);
    ~Packet_DeleteDir();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};

//write partially
class Packet_PartialWrite : public Packet //5
{
private:
    std::string path;
    unsigned int fileSize;
    unsigned int dataSize;
    unsigned int packetNumber;
    char* partialData;

public:
    Packet_PartialWrite(TCPStream* stream);
    Packet_PartialWrite(std::string path, unsigned int fileSize, unsigned int dataSize, char* data, unsigned int packetNumber);
    ~Packet_PartialWrite();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);

    unsigned int getPacketNumber();
};

#endif
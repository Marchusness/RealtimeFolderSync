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
    Packet_WriteFile(TCPStream* stream);    //read from socket constructor
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
    std::string filedata;
public:
    Packet_DeletePath(TCPStream* stream);
    Packet_DeletePath(std::string path, std::string data);
    ~Packet_DeletePath();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};







#endif
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
    const char* filedata;

public:
    Packet_WriteFile(TCPStream* stream);    //read from socket constructor
    Packet_WriteFile(std::string path, const char* data);                     //going to be sent on socket constructor
    ~Packet_WriteFile();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};

//request a file
class Packet_RequestFile : public Packet //3
{
private:
    std::string path;
public:
    Packet_RequestFile(TCPStream* stream);
    Packet_RequestFile(std::string path);
    ~Packet_RequestFile();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);
};

//requests folder paths
class Packet_GetPaths : public Packet //4
{
public:
    Packet_GetPaths(TCPStream* stream);
    Packet_GetPaths();
    ~Packet_GetPaths();

    void exicute(Engine* engine);
};

//updates folder paths
class Packet_UpdatePaths : public Packet //5
{
public:
    Packet_UpdatePaths(TCPStream* stream);
    Packet_UpdatePaths();
    ~Packet_UpdatePaths();

    char* toByteArray();
    bool read();
    void exicute(Engine* engine);

    std::vector<std::string> paths;
};

#endif
#ifndef H_PACKETTYPES
#define H_PACKETTYPES

#include <vector>
#include <string>
#include "Packet.h"

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
    char* path;
    char* file;

public:
    Packet_WriteFile(TCPStream* stream);    //read from socket constructor
    Packet_WriteFile();                     //going to be sent on socket constructor
    ~Packet_WriteFile();

    void exicute();
};

//requests folder paths
class Packet_GetPaths : public Packet //4
{
public:
    Packet_GetPaths(TCPStream* stream);
    Packet_GetPaths();
    ~Packet_GetPaths();

    void exicute();
};

//updates folder paths
class Packet_UpdatePaths : public Packet //5
{
private:
    std::vector<std::string> paths;

public:
    Packet_UpdatePaths(TCPStream* stream);
    Packet_UpdatePaths();
    ~Packet_UpdatePaths();

    char* toByteArray();
    bool read();
    void exicute();
};

#endif
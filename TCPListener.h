#ifndef H_TCPLISTENER
#define H_TCPLISTENER
#include <vector>
#include <queue>

class TCPStream;
class Packet;

class TCPListener
{
private:
    int lisfd;
    std::vector<TCPStream*> streams;
    std::queue<Packet*> packets;

public:
    TCPListener(int port);      //starts listening on port
    ~TCPListener();

    void check();               //checks for packets from sockets
    Packet* getPacketInQueue(); //gets the next packet in queue or nullptr
};

#endif
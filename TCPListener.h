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

    std::vector<TCPStream*> check(); //checks for packets from sockets return new streams 
    Packet* getPacketInQueue(); //gets the next packet in queue or nullptr
    void sendToAll(Packet* p);  //sends a packet to all streams
    void sendToAll(Packet* p, TCPStream* notStream); //excludes a stream from all
};

#endif
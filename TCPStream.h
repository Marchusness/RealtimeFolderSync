#ifndef H_TCPSTREAM
#define H_TCPSTREAM

class TCPListener;
class Packet;

class TCPStream
{
    friend TCPListener;

private:
    int sockfd; //socket file descriptor
    TCPStream(int sockfd);

public:
    static TCPStream* connectTo(const char* address, int port); //connects to a server and returns a stream pointer if successful

    ~TCPStream();

    int write(void* buff, int len); //writes a buffer of length to the socket, returns bytes sent
    int read(void* buff, int len);  //reads a buffer of length to from the socket, returns bytes read
    void write(Packet* packet);     //writes a packet to the socket
    Packet* tryReadPacket();        //tries reading a packet and turns a pointer if successfull, keeps reading untill finished
};

#endif
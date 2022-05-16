#ifndef H_TCPLISTENER
#define H_TCPLISTENER
#include <vector>

class TCPStream;

class TCPListener
{
private:
    int lisfd;
    std::vector<TCPStream*> streams;

public:
    TCPListener(int port);
    ~TCPListener();

    void check();
};

#endif
#ifndef H_TCPSTREAM
#define H_TCPSTREAM

class TCPListener;

class TCPStream
{
    friend TCPListener;
    
private:
    int sockfd; //socket file descriptor

    TCPStream(int sockfd);

public:
    const int BUFFERMAX = 1024;

    static TCPStream* connectTo(const char*, int port);

    ~TCPStream();

    int write(void* buff, int len);
    int read(void* buff);
};

#endif
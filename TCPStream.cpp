//i dont know how many of these are relevant
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#include "TCPStream.h"

TCPStream::TCPStream(int sockfd)
{
    this->sockfd = sockfd;
}

TCPStream::~TCPStream()
{
    ::close(sockfd);
}

TCPStream* TCPStream::connectTo(const char* ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //fcntl(sockfd, F_SETFL, O_NONBLOCK);

    if (sockfd < 0)
    {
        fprintf(stderr, "ERROR opening socket\n");
        return nullptr;
    }

    server = gethostbyname(ip);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        return nullptr;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length); //i think this copies the ip as a cstring but idfk
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) //idk where the adress goes when casting
    {
        fprintf(stderr, "ERROR connecting\n");
        return nullptr;
    }
    return new TCPStream(sockfd);
}

int TCPStream::write(void* buf, int len)
{
    return ::write(sockfd, buf, len);
}

int TCPStream::read(void* buf)
{
    return ::read(sockfd, buf, BUFFERMAX);
}
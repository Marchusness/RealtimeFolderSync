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
#include "Packet.h"
#include "PacketTypes.h"


TCPStream::TCPStream(int sockfd)
{
    this->sockfd = sockfd;
}

TCPStream::~TCPStream()
{
    Packet_Closed* p = new Packet_Closed();
    write((Packet*)p);
    ::close(sockfd);
}

TCPStream* TCPStream::connectTo(const char* ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

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
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) //idk where the adress goes when casting
    {
        fprintf(stderr, "ERROR connecting\n");
        fprintf(stderr, "%d %s\n", errno, strerror(errno));
        return nullptr;
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    return new TCPStream(sockfd);
}

int TCPStream::write(void* buf, int len)
{
    return ::write(sockfd, buf, len);
}

int TCPStream::read(void* buf, int len)
{
    return ::read(sockfd, buf, len);
}

void TCPStream::write(Packet* packet)
{
    char* data = packet->toByteArray();
    unsigned int length = packet->getDataSize();
 
    unsigned int dataWritten = 0;
    while (dataWritten < length)
    {
        dataWritten += write(data + dataWritten, length - dataWritten);
    }
}

Packet* TCPStream::tryReadPacket()
{
    char buf[1];            //still need a char array type
    if (read(buf, 1) == 1)
    {
        Packet* p;
        //identify type
        char type = buf[0];
        std::cout << "new thingo of type?" << type << std::endl;

        if (type == 0)
        {
            std::cerr << "eh?" << std::endl;
            return nullptr;
        }
        else if (type == 1)
        {
            p = new Packet_Closed(this);
        }
        else if (type == 2)
        {
            p = new Packet_WriteFile(this);
        }
        else if (type == 3)
        {
            std::cout << "type 3" << std::endl;
            p = new Packet_DeletePath(this);
        }
        else if (type == 4)
        {
            // p = new Packet_GetPaths(this);
        }
        else if (type == 5)
        {
            // p = new Packet_UpdatePaths(this);
        }
        else if (type == 6)
        {
            
        }
        else
        {
            return nullptr;
        }
        
        if (p->read())
        {
            return p;
        }
    }
    return nullptr;
}
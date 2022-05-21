//i still dont know how many of these are relevant
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

#include "TCPListener.h"
#include "TCPStream.h"
#include "Packet.h"

TCPListener::TCPListener(int port)
{
    struct sockaddr_in serv_addr;

    lisfd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(lisfd, F_SETFL, O_NONBLOCK);
    if (lisfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(lisfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR on binding" << std::endl;
        return;
    }

    listen(lisfd, 5);
}

TCPListener::~TCPListener()
{
    for (TCPStream* stream : streams)
    {
        delete stream;
    }
}

void TCPListener::check()
{
    //check for new connections
    struct sockaddr_in cli_addr;
    memset(&cli_addr, 0, sizeof(cli_addr));
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(lisfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd > 0)
    {
        std::cout << "accepted fd " << newsockfd << ", moved to port " << cli_addr.sin_port << std::endl;
        TCPStream* s = new TCPStream(newsockfd);
        streams.push_back(s);
    }
    //check for data from existnig connections
    for (int i = 0; i < streams.size(); i++)
    {
        Packet* p = streams[i]->tryReadPacket();
        if (p)
        {
            if (p->getType() == 1) //stream has closed
            {
                std::cout << "stream with fd " << streams[i]->sockfd << " has disconnected" << std::endl;
                delete streams[i];
                streams.erase(streams.begin() + i);
                i--;
            }
            else
            {
                packets.push(p);
            }
        }
    }
}

Packet* TCPListener::getPacketInQueue()
{
    if (packets.size() > 0)
    {
        Packet* p = packets.front();
        packets.pop();
        return p;
    }
    return nullptr;
}

void TCPListener::sendToAll(Packet* p)
{
    for (TCPStream* stream : streams)
    {
        stream->write(p);
    }
}
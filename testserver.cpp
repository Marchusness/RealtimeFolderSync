#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR on binding" << std::endl;
        return 1;
    }

    listen(sockfd,5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
    {
        std::cerr << "ERROR on accept" << std::endl;
        return 1;
    }

    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0)
    {
        std::cerr << "ERROR reading from socket" << std::endl;
        printf("Here is the message: %s",buffer);
        return 1;
    } 
    printf("message: %s",buffer);

    n = write(newsockfd,buffer,256);
    if (n < 0)
    {
        std::cerr <<"ERROR writing to socket" << std::endl;
        return 1;
    }

    return 0;
}

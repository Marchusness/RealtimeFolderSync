#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port", argv[0]);
        return 0;
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "ERROR opening socket" << std::endl;
        return 1;
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host");
        return 1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    sockaddr test;
    memset(&test, 0, sizeof(test));
    test.sa_family = AF_INET;

    if (connect(sockfd, (sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    {
        std::cerr << "ERROR connecting" << std::endl;
        return 1;
    }

    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0)
    {
        std::cerr << "ERROR writing to socket" << std::endl;
        return 1;
    }
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    
    if (n < 0)
    {
        std::cerr << "ERROR reading from socket" << std::endl;
        return 1;
    }
    printf("%s",buffer);
    return 0;
}
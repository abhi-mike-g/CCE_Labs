#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXSIZE 90

int main(void)
{
    int sockfd, newsockfd;
    socklen_t actuallen;
    int recedbytes, sentbytes;

    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Socket creation failed");
        return 1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    if (listen(sockfd, 1) == -1)
    {
        perror("Listen failed");
        close(sockfd);
        return 1;
    }

    actuallen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &actuallen);
    if (newsockfd == -1)
    {
        perror("Accept failed");
        close(sockfd);
        return 1;
    }

    memset(buff, 0, MAXSIZE);
    recedbytes = recv(newsockfd, buff, MAXSIZE - 1, 0);
    if (recedbytes == -1)
    {
        perror("Receive failed");
        close(newsockfd);
        close(sockfd);
        return 1;
    }

    printf("Client says: %s\n", buff);

    memset(buff, 0, MAXSIZE);
    fgets(buff, MAXSIZE, stdin);
    buff[strcspn(buff, "\n")] = '\0';

    sentbytes = send(newsockfd, buff, strlen(buff), 0);
    if (sentbytes == -1)
    {
        perror("Send failed");
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}

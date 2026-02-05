#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAXSIZE 256

int main(void)
{
    int sockfd, newsockfd;
    socklen_t addrlen;
    char buff[MAXSIZE];

    struct sockaddr_in serveraddr, clientaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket error");
        return 1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Bind error");
        close(sockfd);
        return 1;
    }

    listen(sockfd, 1);
    addrlen = sizeof(clientaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &addrlen);

    while (1) {
        memset(buff, 0, MAXSIZE);

        int n = recv(newsockfd, buff, MAXSIZE - 1, 0);
        if (n <= 0) break;

        printf("Client: %s", buff);

        if (strncmp(buff, "stop", 4) == 0)
            break;

        memset(buff, 0, MAXSIZE);
        fgets(buff, MAXSIZE, stdin);

        send(newsockfd, buff, strlen(buff), 0);

        if (strncmp(buff, "stop", 4) == 0)
            break;
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}

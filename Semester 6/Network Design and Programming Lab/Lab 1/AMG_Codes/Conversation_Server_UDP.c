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
    int sockfd, retval, i;
    socklen_t actuallen;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket creation error");
        return 1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&clientaddr, 0, sizeof(clientaddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    retval = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        printf("Binding error");
        close(sockfd);
        return 1;
    }

    for (i = 0; ; i++)
    {
        actuallen = sizeof(clientaddr);
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0,
                              (struct sockaddr*)&clientaddr, &actuallen);

        if (recedbytes == -1)
        {
            printf("Receiving error\n");
            close(sockfd);
            return 1;
        }

        puts(buff);
        printf("\n");

        if (strncmp(buff, "stop", 4) == 0)
            break;

        scanf("%s", buff);

        sentbytes = sendto(sockfd, buff, sizeof(buff), 0,
                           (struct sockaddr*)&clientaddr, sizeof(clientaddr));

        if (sentbytes == -1)
        {
            printf("Sending error");
            close(sockfd);
            return 1;
        }

        if (strncmp(buff, "stop", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}


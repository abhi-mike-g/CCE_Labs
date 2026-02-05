#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAXSIZE 50

int main(void)
{
    int sockfd, retval, i;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket Creation Error");
        return 1;
    }

    memset(&serveraddr, 0, sizeof(serveraddr));
    memset(&clientaddr, 0, sizeof(clientaddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(3389);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    retval = bind(sockfd, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if (retval == -1)
    {
        printf("Binding error");
        close(sockfd);
        return 1;
    }

    for (i = 0; ; i++)
    {
        printf("enter the text\n");
        scanf("%s", buff);

        sentbytes = sendto(sockfd, buff, sizeof(buff), 0,
                           (struct sockaddr*)&serveraddr, sizeof(serveraddr));

        if (sentbytes == -1)
        {
            printf("Sending error");
            close(sockfd);
            return 1;
        }

        if (strncmp(buff, "stop", 4) == 0)
            break;

        socklen_t size = sizeof(serveraddr);
        recedbytes = recvfrom(sockfd, buff, sizeof(buff), 0,
                              (struct sockaddr*)&serveraddr, &size);

        puts(buff);
        printf("\n");

        if (strncmp(buff, "stop", 4) == 0)
            break;
    }

    close(sockfd);
    return 0;
}


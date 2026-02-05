#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>      // FIX: for inet_addr()
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 50

int main(void)              // FIX: explicit return type
{
    char buff[MAXSIZE];
    int sockfd, retval, i;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("\nSocket Creation Error");
        return 1;           // FIX: return value
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(3388);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    retval = connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (retval == -1)
    {
        printf("Connection error");
        return 1;           // FIX: return value
    }

    for (i = 0; ; i++)
    {
        memset(buff, '\0', sizeof(buff));
        printf("enter the text\n");
        scanf("%s", buff);

        int s = strlen(buff);
        sentbytes = send(sockfd, buff, s, 0);
        if (sentbytes == -1)
        {
            printf("!!");
            close(sockfd);
            return 1;
        }

        if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p')
            break;

        memset(buff, '\0', sizeof(buff));
        recedbytes = recv(sockfd, buff, sizeof(buff), 0);
        printf("%s\n", buff);

        if (buff[0]=='s' && buff[1]=='t' && buff[2]=='o' && buff[3]=='p')
            break;
    }

    close(sockfd);
    return 0;               // FIX: proper termination
}


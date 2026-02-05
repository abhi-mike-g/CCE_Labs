#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXSIZE 50

int main(void)
{
    int sockfd;
    int recedbytes, sentbytes;
    struct sockaddr_in serveraddr;
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
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("Connection failed");
        close(sockfd);
        return 1;
    }

    printf("Enter the text:\n");

    fgets(buff, MAXSIZE, stdin);
    buff[strcspn(buff, "\n")] = '\0';

    sentbytes = send(sockfd, buff, strlen(buff), 0);
    if (sentbytes == -1)
    {
        perror("Send failed");
        close(sockfd);
        return 1;
    }

    memset(buff, 0, MAXSIZE);
    recedbytes = recv(sockfd, buff, MAXSIZE - 1, 0);
    if (recedbytes == -1)
    {
        perror("Receive failed");
        close(sockfd);
        return 1;
    }
    else if (recedbytes == 0)
    {
        printf("Server closed the connection\n");
        close(sockfd);
        return 0;
    }

    printf("Server says: %s\n", buff);

    close(sockfd);
    return 0;
}


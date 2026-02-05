#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3388
#define MAXSIZE 100

int main(void)
{
    int sockfd;
    struct sockaddr_in serveraddr;
    char str1[MAXSIZE], str2[MAXSIZE], result[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket error");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    send(sockfd, str1, strlen(str1), 0);
    send(sockfd, str2, strlen(str2), 0);

    memset(result, 0, MAXSIZE);
    recv(sockfd, result, MAXSIZE, 0);

    printf("\nServer response: %s\n", result);

    close(sockfd);
    return 0;
}

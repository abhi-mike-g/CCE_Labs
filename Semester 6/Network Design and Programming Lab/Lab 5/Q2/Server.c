#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 3388
#define MAXSIZE 100

int are_anagrams(char *s1, char *s2)
{
    int count[256] = {0};

    if (strlen(s1) != strlen(s2))
        return 0;

    for (int i = 0; s1[i]; i++) {
        count[(unsigned char)s1[i]]++;
        count[(unsigned char)s2[i]]--;
    }

    for (int i = 0; i < 256; i++)
        if (count[i] != 0)
            return 0;

    return 1;
}

int main(void)
{
    int sockfd, newsockfd;
    socklen_t len;
    struct sockaddr_in serveraddr, clientaddr;
    char str1[MAXSIZE], str2[MAXSIZE], result[MAXSIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket error");
        exit(1);
    }

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 5);

    printf("Iterative Server started...\n");

    while (1)   // Iterative server loop
    {
        len = sizeof(clientaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);

        time_t now = time(NULL);
        printf("\nConnected to client %s:%d",
               inet_ntoa(clientaddr.sin_addr),
               ntohs(clientaddr.sin_port));
        printf("\nDate & Time: %s", ctime(&now));

        memset(str1, 0, MAXSIZE);
        memset(str2, 0, MAXSIZE);

        recv(newsockfd, str1, MAXSIZE, 0);
        recv(newsockfd, str2, MAXSIZE, 0);

        if (are_anagrams(str1, str2))
            strcpy(result, "Strings are Anagrams");
        else
            strcpy(result, "Strings are NOT Anagrams");

        send(newsockfd, result, strlen(result), 0);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}

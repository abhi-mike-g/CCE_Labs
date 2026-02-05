#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3388
#define MAXSIZE 1024

int main(void)
{
    int sockfd, newsockfd;
    socklen_t len;
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[MAXSIZE];
    int client_count = 0;

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

    printf("Server waiting for connections...\n");

    char final_msg[MAXSIZE] = "Manipal ";

    while (1)
    {
        len = sizeof(clientaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);
        client_count++;

        if (client_count > 2)
        {
            char term[] = "terminate session";
            send(newsockfd, term, strlen(term), 0);
            close(newsockfd);
            printf("More than 2 clients connected. Terminating.\n");
            close(sockfd);
            exit(0);
        }

        if (fork() == 0)
        {
            close(sockfd);

            memset(buffer, 0, sizeof(buffer));
            recv(newsockfd, buffer, sizeof(buffer), 0);

            printf("Client IP: %s, Port: %d\n",
                   inet_ntoa(clientaddr.sin_addr),
                   ntohs(clientaddr.sin_port));

            strcat(final_msg, buffer);
            strcat(final_msg, " ");

            close(newsockfd);
            exit(0);
        }
        close(newsockfd);

        if (client_count == 2)
        {
            sleep(1);   // allow both children to finish
            printf("\nFinal Output:\n%s\n", final_msg);
        }
    }
}

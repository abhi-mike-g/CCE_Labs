#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Keep asking for file until "File found"
    while (1) {
        printf("Enter filename: ");
        scanf("%s", input);
        send(sock, input, strlen(input), 0);

        memset(buffer, 0, BUFFER_SIZE);
        read(sock, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);

        if (strcmp(buffer, "File found") == 0) break;
    }

    int choice;
    while (1) {
        printf("\n1. Search\n2. Replace\n3. Reorder\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        memset(buffer, 0, BUFFER_SIZE);
        if (choice == 4) {
            send(sock, "4", 1, 0);
            break;
        } else if (choice == 1) {
            printf("Enter string to search: ");
            scanf("%s", input);
            sprintf(buffer, "1 %s", input);
        } else if (choice == 2) {
            char s1[64], s2[64];
            printf("Enter str1 (to find) and str2 (to replace): ");
            scanf("%s %s", s1, s2);
            sprintf(buffer, "2 %s %s", s1, s2);
        } else if (choice == 3) {
            sprintf(buffer, "3");
        }

        send(sock, buffer, strlen(buffer), 0);
        memset(buffer, 0, BUFFER_SIZE);
        read(sock, buffer, BUFFER_SIZE);
        printf("Server response: %s\n", buffer);
    }

    close(sock);
    return 0;
}
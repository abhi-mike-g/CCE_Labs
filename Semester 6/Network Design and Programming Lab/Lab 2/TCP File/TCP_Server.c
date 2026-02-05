#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sort_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    char *data = malloc(size + 1);
    fread(data, 1, size, fp);
    data[size] = '\0';
    fclose(fp);

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                char temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
    fp = fopen(filename, "w");
    fprintf(fp, "%s", data);
    free(data);
    fclose(fp);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        printf("Client connected.\n");

        char filename[256];
        int file_ready = 0;

        // Loop until a valid file is provided or client exits
        while (!file_ready) {
            memset(buffer, 0, BUFFER_SIZE);
            if (read(new_socket, buffer, BUFFER_SIZE) <= 0) break;
            
            FILE *fp = fopen(buffer, "r");
            if (!fp) {
                send(new_socket, "File not present", 16, 0);
            } else {
                strcpy(filename, buffer);
                send(new_socket, "File found", 10, 0);
                fclose(fp);
                file_ready = 1;
            }
        }

        // Menu loop
        while (file_ready) {
            memset(buffer, 0, BUFFER_SIZE);
            if (read(new_socket, buffer, BUFFER_SIZE) <= 0) break;

            int choice = buffer[0] - '0';
            if (choice == 4) break;

            if (choice == 1) {
                char *search_str = buffer + 2;
                int count = 0;
                char word[256];
                FILE *fp = fopen(filename, "r");
                while (fscanf(fp, "%s", word) != EOF) {
                    if (strcmp(word, search_str) == 0) count++;
                }
                fclose(fp);
                if (count > 0) {
                    sprintf(buffer, "Occurrences: %d", count);
                    send(new_socket, buffer, strlen(buffer), 0);
                } else send(new_socket, "String not found", 16, 0);
            } 
            else if (choice == 2) {
                char str1[128], str2[128];
                sscanf(buffer + 2, "%s %s", str1, str2);
                FILE *fp = fopen(filename, "r");
                FILE *temp = fopen("temp.txt", "w");
                char word[256]; int found = 0;
                while (fscanf(fp, "%s", word) != EOF) {
                    if (strcmp(word, str1) == 0) { fprintf(temp, "%s ", str2); found = 1; }
                    else fprintf(temp, "%s ", word);
                }
                fclose(fp); fclose(temp);
                remove(filename); rename("temp.txt", filename);
                send(new_socket, found ? "String replaced" : "String not found", 20, 0);
            } 
            else if (choice == 3) {
                sort_file(filename);
                send(new_socket, "File reordered", 14, 0);
            }
        }
        close(new_socket);
        printf("Client disconnected. Waiting for new connection...\n");
    }
    return 0;
}

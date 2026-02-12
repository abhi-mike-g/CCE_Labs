#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXSIZE 1024

#define SAI struct sockaddr_in
#define SA struct sockaddr

// Convert ASCII character to 8-bit binary string
void char_to_binary(char c, char *binary) {
    for (int i = 7; i >= 0; i--) {
        binary[i] = (c & 1) ? '1' : '0';
        c >>= 1;
    }
    binary[8] = '\0';
}

// Convert binary string to character
char binary_to_char(const char *binary) {
    char result = 0;
    for (int i = 0; i < 8; i++) {
        result = (result << 1) | (binary[i] - '0');
    }
    return result;
}

// Calculate parity bit for data
int calculate_parity(const char *data, int length, int mode) {
    int count = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < 8; j++) {
            if (data[i] & (1 << (7 - j))) {
                count++;
            }
        }
    }
    
    if (mode == 0) {  // Even parity
        return (count % 2 == 0) ? 0 : 1;
    } else {  // Odd parity
        return (count % 2 == 1) ? 0 : 1;
    }
}

// Structure to hold transmission data
typedef struct {
    char data[MAXSIZE];
    char binary_data[MAXSIZE * 9];
    char binary_with_parity[MAXSIZE * 9 + 100];
    int parity;
    int parity_type;
    int length;
} TransmissionData;

int main() {
    int sockfd;
    SAI serveraddr, clientaddr;
    TransmissionData rx_data;
    socklen_t clientlen = sizeof(clientaddr);
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DATA RECEIVER                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Server PID: %d\n\n", getpid());
    
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    printf("[Receiver] Socket created successfully.\n");
    
    // Configure server address
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(PORT);
    
    // Bind
    if (bind(sockfd, (SA *)&serveraddr, sizeof(serveraddr)) == -1) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("[Receiver] Socket bound to port %d.\n", PORT);
    printf("[Receiver] Waiting for data...\n\n");
    
    // Receive data
    ssize_t received = recvfrom(sockfd, &rx_data, sizeof(TransmissionData), 0,
                               (SA *)&clientaddr, &clientlen);
    
    if (received < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DATA RECEIVED                               ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("Received: %zd bytes\n\n", received);
    
    // Display received data
    printf("============================================================\n");
    printf("                    RECEIVED DATA                           \n");
    printf("============================================================\n");
    printf("\nOriginal Data: \"%s\"\n", rx_data.data);
    printf("Length: %d bytes\n", rx_data.length);
    printf("Parity Type: %s\n", rx_data.parity_type == 0 ? "Even" : "Odd");
    printf("Received Parity Bit: %d\n", rx_data.parity);
    printf("\nReceived Binary Data: %s\n", rx_data.binary_data);
    
    // Extract data bits (without parity bit)
    int total_bits = strlen(rx_data.binary_with_parity);
    int data_bits = total_bits - 1;
    char received_data_bits[ MAXSIZE * 9 ];
    strncpy(received_data_bits, rx_data.binary_with_parity, data_bits);
    received_data_bits[data_bits] = '\0';
    
    printf("Received Data Bits: %s\n", received_data_bits);
    printf("Received Parity Bit: %c\n", rx_data.binary_with_parity[data_bits]);
    
    // Recalculate parity from received data
    int calculated_parity = calculate_parity(rx_data.data, rx_data.length, rx_data.parity_type);
    
    printf("\n============================================================\n");
    printf("                    PARITY CHECK                            \n");
    printf("============================================================\n");
    printf("\nReceived Parity Bit: %d\n", rx_data.parity);
    printf("Calculated Parity Bit: %d\n", calculated_parity);
    
    // Check for errors
    printf("\n");
    printf("------------------------------------------------------------\n");
    
    if (rx_data.parity == calculated_parity) {
        printf("RESULT: ✓ NO ERROR - Data integrity verified!\n");
        printf("        The received data matches the parity check.\n");
    } else {
        printf("RESULT: ✗ ERROR DETECTED!\n");
        printf("        The received parity does not match calculated parity.\n");
        printf("        Data may have been corrupted during transmission.\n");
    }
    
    printf("------------------------------------------------------------\n");
    
    // Reconstruct data from binary
    printf("\n============================================================\n");
    printf("                    DATA RECONSTRUCTION                      \n");
    printf("============================================================\n");
    printf("\nReconstructed Data from Binary:\n");
    
    char reconstructed[MAXSIZE] = "";
    for (int i = 0; i < rx_data.length; i++) {
        char byte_bin[9];
        strncpy(byte_bin, &received_data_bits[i * 8], 8);
        byte_bin[8] = '\0';
        char c = binary_to_char(byte_bin);
        printf("  Bits %d-%d: %s = '%c'\n", i * 8 + 1, i * 8 + 8, byte_bin, c);
        strncat(reconstructed, &c, 1);
    }
    
    printf("\nReconstructed String: \"%s\"\n", reconstructed);
    
    if (strcmp(reconstructed, rx_data.data) == 0) {
        printf("Match: Original and reconstructed data are identical.\n");
    } else {
        printf("Mismatch: Data may be corrupted!\n");
    }
    
    printf("\n============================================================\n");
    printf("                    SUMMARY                                 \n");
    printf("============================================================\n");
    printf("\n  Data Length:    %d bytes\n", rx_data.length);
    printf("  Parity Type:   %s\n", rx_data.parity_type == 0 ? "Even" : "Odd");
    printf("  Transmitted Parity: %d\n", rx_data.parity);
    printf("  Calculated Parity:  %d\n", calculated_parity);
    printf("  Status:         %s\n", 
           rx_data.parity == calculated_parity ? "NO ERROR" : "ERROR DETECTED");
    printf("\n============================================================\n");
    
    close(sockfd);
    printf("\nConnection closed.\n");
    
    return 0;
}

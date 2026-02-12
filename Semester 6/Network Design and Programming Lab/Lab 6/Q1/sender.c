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
// mode: 0 = even parity, 1 = odd parity
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
    char data[MAXSIZE];      // Original data
    char binary_data[MAXSIZE * 9];  // Binary representation
    char binary_with_parity[MAXSIZE * 9 + 100];  // With parity bit
    int parity;              // Parity bit (0 or 1)
    int parity_type;         // 0 = even, 1 = odd
    int length;              // Data length
} TransmissionData;

int main() {
    int sockfd;
    SAI serveraddr;
    TransmissionData tx_data;
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    DATA TRANSMITTER (SENDER)                  ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("Client PID: %d\n\n", getpid());
    
    // Get user input
    printf("Enter data to transmit: ");
    fgets(tx_data.data, MAXSIZE, stdin);
    tx_data.data[strcspn(tx_data.data, "\n")] = '\0';
    tx_data.length = strlen(tx_data.data);
    
    printf("\nSelect parity type:\n");
    printf("  0 = Even Parity (Total 1s should be even)\n");
    printf("  1 = Odd Parity  (Total 1s should be odd)\n");
    printf("Enter choice (0/1): ");
    scanf("%d", &tx_data.parity_type);
    
    if (tx_data.parity_type < 0 || tx_data.parity_type > 1) {
        printf("Invalid choice. Using Even Parity.\n");
        tx_data.parity_type = 0;
    }
    
    // Calculate parity
    tx_data.parity = calculate_parity(tx_data.data, tx_data.length, tx_data.parity_type);
    
    // Convert to binary
    printf("\n============================================================\n");
    printf("                    DATA CONVERSION                           \n");
    printf("============================================================\n");
    printf("\nOriginal Data: \"%s\"\n", tx_data.data);
    printf("Length: %d bytes\n\n", tx_data.length);
    
    printf("Binary Representation:\n");
    tx_data.binary_data[0] = '\0';
    
    for (int i = 0; i < tx_data.length; i++) {
        char binary[9];
        char_to_binary(tx_data.data[i], binary);
        printf("  '%c' = %s\n", tx_data.data[i], binary);
        strcat(tx_data.binary_data, binary);
    }
    
    printf("\nFull Binary String: %s\n", tx_data.binary_data);
    printf("Parity Type: %s\n", tx_data.parity_type == 0 ? "Even" : "Odd");
    printf("Parity Bit: %d\n", tx_data.parity);
    
    // Create binary with parity bit
    strcpy(tx_data.binary_with_parity, tx_data.binary_data);
    int data_bits = strlen(tx_data.binary_data);
    
    // Add parity bit at the end
    char parity_str[2];
    parity_str[0] = tx_data.parity ? '1' : '0';
    parity_str[1] = '\0';
    strcat(tx_data.binary_with_parity, parity_str);
    
    printf("\nBinary with Parity Bit: %s (%d bits)\n", 
           tx_data.binary_with_parity, data_bits + 1);
    
    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    printf("\n[Sender] Socket created successfully.\n");
    
    // Configure server address
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
    
    printf("Sending data to receiver at 127.0.0.1:%d...\n\n", PORT);
    
    // Send data
    ssize_t sent = sendto(sockfd, &tx_data, sizeof(TransmissionData), 0,
                         (SA *)&serveraddr, sizeof(serveraddr));
    
    if (sent < 0) {
        perror("Send failed");
    } else {
        printf("╔══════════════════════════════════════════════════════════════╗\n");
        printf("║                    TRANSMISSION COMPLETE                     ║\n");
        printf("╚══════════════════════════════════════════════════════════════╝\n");
        printf("Data sent: %zd bytes\n", sent);
        printf("Parity: %s\n", tx_data.parity_type == 0 ? "Even" : "Odd");
        printf("Parity Bit: %d\n\n", tx_data.parity);
    }
    
    // Simulate error (optional)
    printf("Simulation Mode:\n");
    printf("  The receiver will verify parity and detect if data is corrupted.\n");
    printf("  To test error detection, you can:\n");
    printf("    1. Run receiver normally (should show 'No Error')\n");
    printf("    2. Modify receiver code to flip a bit (should show 'Error Detected')\n\n");
    
    close(sockfd);
    printf("Connection closed.\n");
    
    return 0;
}

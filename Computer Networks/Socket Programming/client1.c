#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int client_socket;
    struct sockaddr server_addr; // Using generic sockaddr directly
    unsigned short port;
    unsigned int ip_addr_binary;

    if(argc < 3){
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0){
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Zero out the structure
    memset(&server_addr, 0, sizeof(server_addr));
    
    // 1. Set Address Family
    server_addr.sa_family = AF_INET;
    
    // 2. Pack Port (2 bytes) into the first 2 bytes of sa_data
    // Note: sa_data[0] and sa_data[1] correspond to the port in Network Byte Order
    port = htons(atoi(argv[2]));
    memcpy(&server_addr.sa_data[0], &port, 2);

    // 3. Pack IP Address (4 bytes) into the next 4 bytes of sa_data
    // Note: sa_data[2] through sa_data[5] correspond to the IP address
    if(inet_pton(AF_INET, argv[1], &ip_addr_binary) <= 0){
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    memcpy(&server_addr.sa_data[2], &ip_addr_binary, 4);

    
    // Connect to server (No casting needed now, it's already sockaddr)
    if(connect(client_socket, &server_addr, sizeof(server_addr)) < 0){
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
    
    char message[] = "Hello World!!";
    printf("Sending message to server: %s\n", message);

    // Send data to server
    send(client_socket, message, strlen(message), 0);

    // Receive data from server
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0); 
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received message from server: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}

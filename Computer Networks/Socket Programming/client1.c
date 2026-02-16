#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int client_socket;
    struct sockaddr server_addr; 
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
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sa_family = AF_INET;
    port = htons(atoi(argv[2]));
    memcpy(&server_addr.sa_data[0], &port, 2);
    if(inet_pton(AF_INET, argv[1], &ip_addr_binary) <= 0){
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    memcpy(&server_addr.sa_data[2], &ip_addr_binary, 4);


    if(connect(client_socket, &server_addr, sizeof(server_addr)) < 0){
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
    
    char message[] = "Hello World!!";
    printf("Sending message to server: %s\n", message);

    if(send(client_socket, message, strlen(message), 0) < 0){
        perror("send failed");
        exit(EXIT_FAILURE);
    }
    
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0); 
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received message from server: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}

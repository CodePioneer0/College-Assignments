#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> 

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr server_addr;
    struct sockaddr client_addr;
    unsigned short port;
    unsigned int ip_addr = 0; // 0 represents INADDR_ANY
    socklen_t addr_len = sizeof(client_addr);

    // 1. Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Prepare the sockaddr structure manually
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sa_family = AF_INET;

    // Pack Port (sa_data[0] and sa_data[1])
    port = htons(PORT);
    memcpy(&server_addr.sa_data[0], &port, 2);

    // Pack IP (sa_data[2] through sa_data[5])
    memcpy(&server_addr.sa_data[2], &ip_addr, 4); 

    // 3. Bind
    if (bind(server_fd, &server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d...\n", PORT);

    // 5. Accept
    if ((new_socket = accept(server_fd, &client_addr, &addr_len)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 6. Read Data
    char buffer[1024] = {0};
    ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
    if(bytes_read > 0) {
        // Ensure null termination for safety, though buffer was zero-init
        buffer[bytes_read] = '\0';
        printf("Received message from client: %s\n", buffer);
    }

    // 7. Send Response
    char *hello = "Hello from server";
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // 8. Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}

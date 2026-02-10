#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]){
    int server_fd;
    struct sockaddr server_addr;
    char*msg = "What's the time?";
    char buffer[1024] = {0};
    unsigned short port;
    unsigned int ip_addr;

    //1 Create socket
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //2 Prepare sockaddr structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sa_family = AF_INET;
    port = htons(atoi(argv[1]));
    memcpy(&server_addr.sa_data[0], &port, 2);
    if(inet_pton(AF_INET, argv[2], &ip_addr) <= 0){
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }
    memcpy(&server_addr.sa_data[2], &ip_addr, 4);

    //3 Connect to server
    if(connect(server_fd, &server_addr, sizeof(server_addr)) < 0){
        perror("connection failed");
        exit(EXIT_FAILURE); 
    }

    send(server_fd, msg, strlen(msg), 0);
    printf("Message sent to server: %s\n", msg);

    read(server_fd, buffer, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    printf("Message received from server: %s\n", buffer);
    close(server_fd);
    return 0;
}
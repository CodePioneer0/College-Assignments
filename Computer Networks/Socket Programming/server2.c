#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080

int main(int argc,char*argv[]){
    int server_fd,client_socket;
    struct sockaddr server_addr,client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[1024] = {0};
    char *expected_msg = "What's the time?";
    time_t current_time;
    char *time_str;

    //1 Create socket
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //2 Prepare sockaddr structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sa_family = AF_INET;
    unsigned short port = htons(PORT);
    memcpy(&server_addr.sa_data[0], &port, 2);
    unsigned int ip_addr = 0; //0.0.0.0
    memcpy(&server_addr.sa_data[2], &ip_addr, 4);

    //3 Bind
    if(bind(server_fd, &server_addr, sizeof(server_addr)) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //4 Listen
    if(listen(server_fd, 3) < 0){
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while(1){
        if((client_socket = accept(server_fd, &client_addr, &addr_len)) < 0){
            perror("accept");
            continue;
        }

        memset(buffer, 0, sizeof(buffer));
        read(client_socket, buffer, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
        printf("Received message: %s\n", buffer);

        if(strcmp(buffer, expected_msg) == 0){
            current_time = time(NULL);
            time_str = ctime(&current_time);
            send(client_socket, time_str, strlen(time_str), 0);
        } else {
            char *error_msg = "Invalid request";
            send(client_socket, error_msg, strlen(error_msg), 0);
        }
        close(client_socket);
    }
}
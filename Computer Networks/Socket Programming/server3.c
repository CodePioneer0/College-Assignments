#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, client_fd;
    struct sockaddr server_addr, client_addr;
    socklen_t addr_len = sizeof(server_addr);

    //1 Create socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    //2 Prepare sockaddr structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sa_family = AF_INET;
    uint16_t port_net = htons(PORT);
    memcpy(&server_addr.sa_data[0], &port_net, 2);
    unsigned int ip_addr_binary = 0;
    memcpy(&server_addr.sa_data[2], &ip_addr_binary, 4);
    //3 Bind
    if(bind(server_fd,&server_addr, addr_len) < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd, 1) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);
    client_fd = accept(server_fd, &client_addr, &addr_len);
    if (client_fd < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    uint16_t n_net;
    if(recv(client_fd, &n_net, 2, 0) < 0){
        perror("recv failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    int n = ntohs(n_net);
    int arr[n];
    for (int i = 0; i < n; i++) {
        int temp;
        if(recv(client_fd, &temp, 4, 0) < 0){
            perror("recv failed");
            close(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
        arr[i] = ntohl(temp);
    }
    printf("Received elements:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    // Simple insertion sort
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    n_net = htons(n);
    if (send(client_fd, &n_net, 2, 0) < 0) {
        perror("send failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        int temp = htonl(arr[i]);
        if (send(client_fd, &temp, 4, 0) < 0) {
            perror("send failed");
            close(client_fd);
            close(server_fd);
            exit(EXIT_FAILURE);
        }
    }

    close(client_fd);
    close(server_fd);
    return 0;
}

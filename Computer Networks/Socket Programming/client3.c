#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    int client_fd;
    struct sockaddr server_addr;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sa_family = AF_INET;
    uint16_t port_net = htons(8080);
    memcpy(&server_addr.sa_data[0], &port_net, 2);
    unsigned int ip_addr_binary = 0;
    memcpy(&server_addr.sa_data[2], &ip_addr_binary, 4);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    uint16_t n_net = htons(n);
    if (send(client_fd, &n_net, 2, 0) < 0) {
        perror("Send failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        int temp = htonl(arr[i]);
        if (send(client_fd, &temp, 4, 0) < 0) {
            perror("Send failed");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (recv(client_fd, &n_net, 2, 0) < 0) {
        perror("Receive failed");
        close(client_fd);
        exit(EXIT_FAILURE);
    }
    n = ntohs(n_net);

    printf("Sorted elements:\n");
    for (int i = 0; i < n; i++) {
        int temp;
        if (recv(client_fd, &temp, 4, 0) < 0) {
            perror("Receive failed");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        printf("%d ", ntohl(temp));
    }
    printf("\n");

    close(client_fd);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "application.h"
#include "socket.h"


#define PORT 8080

int server_socket;

int client_socket;

struct sockaddr_in server_addr;

struct sockaddr_in client_addr;

socklen_t client_addr_len = sizeof(client_addr);

pthread_t thread_id;

struct ClientInfo {
    int socket;
    char name[20];
    char ip[INET_ADDRSTRLEN];
};

struct ClientInfo connected_clients[MAX_CLIENTS];

int num_clients = 0;

void *handle_client(void *arg);

void closeClientSocket(int client_socket);

void closeClientSockets();

void closeServerSocket();

void initSocket()
{
    // Create socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == -1)
    {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
}

int acceptClient()
{
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
    {
        perror("Accepting connection failed");
        closeClientSocket(client_socket);
        return 0;
    }

    if (num_clients < MAX_CLIENTS) {
        struct ClientInfo new_client;
        new_client.socket = client_socket;
        inet_ntop(AF_INET, &(client_addr.sin_addr), new_client.ip, INET_ADDRSTRLEN); // Store the IP address as a string
        snprintf(new_client.name, sizeof(new_client.name), "%s %d", new_client.ip, num_clients + 1); // Generate a unique name
        connected_clients[num_clients] = new_client;

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&connected_clients[num_clients]) != 0) {
            perror("Thread creation failed");
            closeClientSocket(client_socket);
            return 0;
        }

        // Detach the thread (so it can clean up resources on its own)
        pthread_detach(thread_id);

        return 1;
    } else {
        fprintf(stderr, "Max number of clients reached. Connection rejected.\n");
        closeClientSocket(client_socket);
        return 0;
    }
}

void closeClientSocket(int socket)
{
    close(socket);
}

void closeClientSockets() {
    for (int i = 0; i < num_clients; ++i) {
        closeClientSocket(connected_clients[i].socket);
    }
}

void closeServerSocket()
{
    close(server_socket);
}

void *handle_client(void *arg)
{
    struct ClientInfo *client_info = (struct ClientInfo *)arg;
    char buffer[1024];
    ssize_t bytes_received;
    
    while ((bytes_received = recv(client_info->socket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[bytes_received] = '\0';
        if (strcmp(buffer, "ping") != 0)
            printf("%s: %s\n", client_info->name, buffer);
        send(client_info->socket, buffer, bytes_received, 0);
        buffer[0] = '\0';
    }

    closeClientSocket(client_info->socket);
    pthread_exit(NULL);
}
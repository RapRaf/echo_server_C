#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
#include "application.h"

int client_socket;

int PORT = 8080;

char *SERVER_IP = "127.0.0.1";

struct sockaddr_in server_addr;

char buffer[1024];

ssize_t bytes_received;

int connected = 0;

clock_t start_time;

clock_t end_time;

pthread_t thread_ping;

pthread_t thread_receive;

int sending;

void closeSocket()
{
    close(client_socket);
}

void sendToSocket(char *str)
{
    sending = 1;
    start_time = clock();

    send(client_socket, str, strlen(str), 0);
}

int setupConnection()
{
    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    return 1;
}

void *pinging()
{
    while (connected == 1)
    {
        if (sending == 0)
        {
            sendToSocket("ping");
        }

        sleep(2);
    }

    pthread_exit(NULL);
}

void *receiveFromSocket()
{
    while (connected == 1)
    {
        char buffer[1024];
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        end_time = clock();

        if (bytes_received > 0)
        {
            buffer[bytes_received] = '\0';

            double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;

            printf("\e[s");

            printf("\e[H");

            printf("\e[1;%dH", 80);

            printf("%.2fms", elapsed_time);

            printf("\e[u");

            if (strcmp(buffer, "ping") != 0)
            {
                printf("Received: %s\n", buffer);
            }

            fflush(stdout);

            buffer[0] = '\0';

            sending = 0;
        }
        else
        {
            perror("Error receiving response from the server");
            closeProgram();
        }
    }

    pthread_exit(NULL);
}
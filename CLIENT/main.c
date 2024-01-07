#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "socket.h"
#include "application.h"
#include "input.h"
#include <pthread.h>

void echoProcess();
void startPing();
void startReceving();

int main()
{
    printf("\e[1;1H\e[2J\e[2;1H");

    connected = setupConnection();

    if (connected != 1)
        closeProgram();

    startReceving();
    startPing();

    while (connected == 1)
    {
        echoProcess();
        while (sending == 1)
        {
            usleep(100000);
        }
    }

    return 0;
}

void echoProcess()
{
    char *message = getValidatedString("Text: ");

    sendToSocket(message);
}

void startPing()
{
    if (pthread_create(&thread_ping, NULL, pinging, NULL) != 0)
    {
        perror("Thread creation failed");
        closeProgram();
    }

    if (pthread_detach(thread_ping) != 0)
    {
        perror("Thread detach failed");
        closeProgram();
    }
}

void startReceving()
{
    if (pthread_create(&thread_receive, NULL, receiveFromSocket, NULL) != 0)
    {
        perror("Thread creation failed");
        closeProgram();
    }

    if (pthread_detach(thread_receive) != 0)
    {
        perror("Thread detach failed");
        closeProgram();
    }
}



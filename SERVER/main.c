#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "socket.h"
#include "application.h"
#include "input.h"

void startCloseListener();

void *waitClose();

int main()
{
    initSocket();

    //startCloseListener();

    while (1)
    {
        if (acceptClient() == 1)
        {
            num_clients++;
        }
    }

    return 0;
}

void startCloseListener()
{
    if (pthread_create(&thread_close, NULL, waitClose, NULL) != 0)
    {
        perror("Thread creation failed");
        closeProgram();
    }

    if (pthread_detach(thread_close) != 0)
    {
        perror("Thread detach failed");
        closeProgram();
    }
}

void *waitClose()
{
    getValidatedString("");

    pthread_exit(NULL);
}

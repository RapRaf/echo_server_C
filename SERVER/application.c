#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include <pthread.h>

pthread_t thread_close;

void closeProgram()
{
    printf("Request to exiting the program\n");
    printf("Closing socket...\n");
    closeClientSockets();
    closeServerSocket();
    printf("Socket closed.!\n");
    
    printf("Exiting the program...\n");
    exit(0);
}

void closeProgramWithError()
{
    printf("Errore, chiusura in corso.\n");
    printf("Closing socket...\n");
    closeClientSockets();
    closeServerSocket();
    printf("Socket closed.!\n");
    printf("Exiting the program...\n");
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

void closeProgram()
{
    connected = 0;
    closeSocket();
    printf("Exiting the program...\n");
    exit(0);
}
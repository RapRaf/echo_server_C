#ifndef SOCKET_H
#define SOCKET_H

#include <sys/types.h>
#include <pthread.h>

extern int client_socket;

extern int connected;

extern int PORT;

extern int sending;

extern char *SERVER_IP;

extern struct sockaddr_in server_addr;

extern char buffer[1024];

extern ssize_t bytes_received;

extern clock_t start_time;

extern clock_t end_time;

extern pthread_t thread_ping;

extern pthread_t thread_receive;

void closeSocket();

void sendToSocket(char *str);

void *pinging();

void *receiveFromSocket();

int setupConnection();


#endif

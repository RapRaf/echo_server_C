#ifndef SOCKET_H
#define SOCKET_H


#include <pthread.h>
#include <arpa/inet.h>


#define MAX_CLIENTS 10

extern int server_socket;

extern int client_socket;

extern struct sockaddr_in server_addr;

extern struct sockaddr_in client_addr;

extern socklen_t client_addr_len;

extern pthread_t thread_id;

extern int num_clients;

extern void initSocket();

extern int acceptClient();

extern void closeClientSocket(int client_socket);

extern void closeClientSockets();

extern void closeServerSocket();

#endif
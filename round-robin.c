#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_COUNT 3

const char *backend_servers[SERVER_COUNT] = {"127.0.0.1", "127.0.0.1", "127.0.0.1"};
const int backend_ports[SERVER_COUNT] = {8081,8082,8083};

int current_server = 0;
pthread_mutex_t lock;



void *forward_to_backend(void *client_socket_ptr) {
	int client_socket = *(int *)client_socket_ptr;
	free(client_socket_ptr);
}




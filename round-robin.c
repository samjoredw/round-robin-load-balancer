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

int current_backend = 0;
pthread_mutex_t lock;



void *forward_to_backend(void *client_socket_ptr) {

	int client_socket = *(int *)client_socket_ptr;
	free(client_socket_ptr);

	pthread_mutex_lock(&lock);
	int backend_index = current_backend;
	current_backend = (current_backend + 1) % SERVER_COUNT;
	pthread_mutex_unlock(&lock);
	
	int backend_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (backend_socket < 0) {
		perror("Socket failure.");
		close(client_socket);
		pthread_exit(NULL);
	}

	struct sockaddr_in backend_addr;
	backend_addr.sin_family = AF_INET;
	backend_addr.sin_port = htons(backend_ports[back_index]);

	if (inet_pton(AF_INET, backend_servers[backend_index], &backend_addr.sin_addr) <= 0) {
		perror("Invalid address.");
		close(client_socket);
		close(backend_socket);
		pthread_exit(NULL);
	}

	if (connect(backendsocket, (struct sockaddr *)&backend_addr, sizeof(backend_addr)) < 0) {
		perror("Connection to backend failed.");
		close(client_socket);
		close(backend_socket);
		pthread_exit(NULL);
	}
	
	char buffer[1024];
	int bytes_read;
	while ((bytes_read = read(client_socket, buffer, sizeof(buffer))) > 0) {
		send(backend_socket, buffer, bytes_read, 0);
		bytes_read = read(backend_socket, buffer, sizeof(buffer));
		send(client_socket, buffer , bytes_read, 0);
	}

	close(client_socket);
	close(backend_socket);
	pthread_exit(NULL);




}




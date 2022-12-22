#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8082
#define STR_NUM 50
#define BATCH_SIZE 5

typedef struct Node{
    int id;
    char data[4];
} Node;


int main(int argc, char const* argv[]){
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	Node buffer[STR_NUM];
    

	// printf("Data copied to struct");

	// for(int i=0; i<STR_NUM; i++) {
    // 	printf("data[%d].id : %d\n", i, hello[i].id);
    // 	printf("data[%d].data : %s\n", i, hello[i].data);
	// }

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT, &opt,	sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,	sizeof(address))< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address,	(socklen_t*)&addrlen))< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	// valread = read(new_socket, buffer, 1024);
	// printf("%s\n", buffer);

	printf("Hello from server\n");

	int max_ID = -1;
	valread = read(new_socket, buffer, sizeof(buffer));
	for(int i=0; i<BATCH_SIZE; i++){
		if (buffer[i].id > max_ID){
			max_ID = buffer[i].id;
		}
		printf("Str id : %d and str data : %s\n", buffer[i].id, buffer[i].data);
	}
	printf("Max ID : %d\n", max_ID);

	send(new_socket, &max_ID, sizeof(int), 0);
	printf("Max ID sent\n");
	
	while(max_ID<49){
		valread = read(new_socket, buffer, sizeof(buffer));
		printf("\nread strings sent from server\n");
		for(int i=0; i<BATCH_SIZE; i++){
			if (buffer[i].id > max_ID){
				max_ID = buffer[i].id;
			}
			printf("Str id : %d and str data : %s\n", buffer[i].id, buffer[i].data);
		}
		printf("Max ID : %d\n", max_ID);

		send(new_socket, &max_ID, sizeof(int), 0);
		printf("Max ID sent\n");
	}


	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}

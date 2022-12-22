#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>

#define PORT 8082
#define STR_NUM 50
#define BATCH_SIZE 5

typedef struct Node{
    int id;
    char data[4];
} Node;

int main(int argc, char const* argv[]){
	struct timespec startT, stopT;
	double timeTaken;
	clock_gettime(CLOCK_MONOTONIC, &startT);

	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;

	// char p1_strings[STR_NUM][4] = {
	// "aaa","aab","aac","aad","aae",
	// "aba","abb","abc","abd","abe",
	// "aca","acb","acc","acd","ace",
	// "ada","adb","adc","add","ade",
	// "aea","aeb","aec","aed","aee",
	// "baa","bab","bac","bad","bae",
	// "bba","bbb","bbc","bbd","bbe",
	// "bca","bcb","bcc","bcd","bce",
	// "bda","bdb","bdc","bdd","bde",
	// "bea","beb","bec","bed","bee",};

	char p1_strings[STR_NUM][4];
    for(int i=0; i<STR_NUM; i++){
	    for(int j=0; j<3; j++){
            p1_strings[i][j] = rand()%26 + 65;
        }
        p1_strings[i][3] = 0;
    }

	Node hello[STR_NUM];
	// Copy data to struct
	for(int i=0; i<STR_NUM; i++) {
    	hello[i].id = i;
    	strcpy(hello[i].data, p1_strings[i]);
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))	< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	
	send(sock, hello, BATCH_SIZE*sizeof(Node), 0);
	printf("Strings sent\n");
	
	int c_ret = -1;
	valread = read(sock, &c_ret, sizeof(int));
	printf("Max ID : %d\n", c_ret);
	// c_ret = -1;

	while(c_ret<=45){
		send(sock, &(hello[c_ret+1]), BATCH_SIZE*sizeof(Node), 0);
		printf("Strings sent\n");

		valread = read(sock, &c_ret, sizeof(int));
		printf("Max ID : %d\n", c_ret);
	}
	
	// closing the connected socket
	close(client_fd);
	
	clock_gettime(CLOCK_MONOTONIC, &stopT);
	// printf("start : %ld nsec\n", startT.tv_nsec);
	// printf("stop : %ld nsec\n", stopT.tv_nsec);
	timeTaken = (stopT.tv_nsec - startT.tv_nsec);
	printf("\nTime Taken : %f nsec\n", timeTaken);
		
	// timeTaken = (stopT.tv_sec - startT.tv_sec);
	// printf("Time Taken : %f sec\n", timeTaken);

	return 0;
}

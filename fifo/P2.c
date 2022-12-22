#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define STR_NUM 50
#define BATCH_SIZE 5

typedef struct Node{
    int id;
    char data[4];
} Node;

int main(){
    printf("Reciever process with pid %d\n", getpid());

    int stringFd;
    stringFd = open("/tmp/stringFifo", O_RDONLY);
    if (stringFd == -1){
        perror("Error in open\n");
        return EXIT_FAILURE;
    }

    int intFd ; /*Descriptor for FIFO*/
    intFd = open("/tmp/intFifo", O_WRONLY);

    Node payload[BATCH_SIZE];
    int max_ID = -1;

    while(max_ID < STR_NUM-1) {
        int read_status = read(stringFd, payload, BATCH_SIZE*sizeof(Node));
        if (read_status == -1){
            perror("Error in read\n");
            return EXIT_FAILURE;
        }
        printf("Strings recieved\n");
        for(int i=0; i<BATCH_SIZE; i++){
            if (payload[i].id > max_ID){
                max_ID = payload[i].id;
            }
            printf("Str id : %d and str data : %s\n", payload[i].id, payload[i].data);
        }

        int write_status = write(intFd, &max_ID, sizeof(int));

        if (write_status == -1)
        {
            perror("Error in sending count1 from P2\n");
            return EXIT_FAILURE;
        }
    }

// // B2 logic

// read_status = read(stringFd, payload, BATCH_SIZE*sizeof(Node));
// if (read_status == -1){
//     perror("Error in read\n");
//     return EXIT_FAILURE;
// }

// printf("B2 recieved\n");
// for(int i=0; i<BATCH_SIZE; i++){
//     if (payload[i].id > max_ID){
//         max_ID = payload[i].id;
//     }
//     printf("Str id : %d and str data : %s\n", payload[i].id, payload[i].data);
// }

// write_status = write(intFd, &max_ID, sizeof(int));

// if (write_status == -1)
// {
//     perror("Error in sending count2 from P2\n");
//     return EXIT_FAILURE;
// }


    return EXIT_SUCCESS;
}

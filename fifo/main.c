#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define STR_NUM 50
#define BATCH_SIZE 5

typedef struct Node{
    int id;
    char data[4];
} Node;

int main()
{
    printf("Main process with pid %d\n", getpid());

    /*Create a string fifo*/
    int statusStringFifo = mkfifo("/tmp/stringFifo", 0666);
    if (statusStringFifo == -1)
    {
        perror("Error in string mkfifo\n");
        return EXIT_FAILURE;
    }

    /*Create a int fifo*/
    int statusIntFifo = mkfifo("/tmp/intFifo", 0666);
    if (statusIntFifo == -1)
    {
        perror("Error in string mkfifo\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

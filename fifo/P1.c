#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define STR_NUM 50
#define BATCH_SIZE 5

typedef struct Node{
    int id;
    char data[4];
} Node;

int main(){
	struct timespec startT, stopT;
	double timeTaken;
	clock_gettime(CLOCK_MONOTONIC, &startT);

    printf("Sender process with pid %d\n", getpid());

    int stringFd ; /*Descriptor for string FIFO*/
    stringFd = open("/tmp/stringFifo", O_WRONLY);

    
    int intFd;
    intFd = open("/tmp/intFifo", O_RDONLY);

    if (intFd == -1){
        perror("Error in int fifo open\n");
        return EXIT_FAILURE;
    }
    
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

	Node payload[STR_NUM];
	// Copy data to struct
	for(int i=0; i<STR_NUM; i++) {
    	payload[i].id = i;
    	strcpy(payload[i].data, p1_strings[i]);
	}    
    
    if (stringFd == -1)
    {
        perror("Error in open\n");
        return EXIT_FAILURE;
    }


    int max_ID = -1;
    while(max_ID < STR_NUM-BATCH_SIZE+1){
        printf("Sending from : %d to %d\n", max_ID+1, max_ID+BATCH_SIZE);
        int write_status = write(stringFd, &(payload[max_ID+1]), BATCH_SIZE * sizeof(Node));

        if (write_status == -1)
        {
            perror("Error in writing entries\n");
            return EXIT_FAILURE;
        }
        /*Read from int fifo*/
        int read_status = read(intFd, &max_ID, sizeof(int));
        if (read_status == -1){
            perror("Error in reading maxID\n");
            return EXIT_FAILURE;
        }
        printf("MaxID received : %d\n", max_ID);
    }
    clock_gettime(CLOCK_MONOTONIC, &stopT);
	// printf("start : %ld nsec\n", startT.tv_nsec);
	// printf("stop : %ld nsec\n", stopT.tv_nsec);
	timeTaken = (stopT.tv_nsec - startT.tv_nsec);
	printf("\nTime Taken : %f nsec\n", timeTaken);

    return EXIT_SUCCESS;
}

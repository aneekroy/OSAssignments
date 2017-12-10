#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
int main(){
	char *fifo_filename1="/tmp/myfifo_caller";
	char *fifo_filename2="/tmp/myfifo_receiver";
    if(mkfifo(fifo_filename1 ,0666)==-1){

		printf("Unable to open fifo for caller. Error \n");
		abort();
	}
    if(mkfifo(fifo_filename2 ,0666)==-1){

		printf("Unable to open fifo for receiver. Error \n");
		abort();
	}
	printf("Link created\n");
	return 0;
}	
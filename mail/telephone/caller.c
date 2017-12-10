#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXLENGTH 1024

int main (){

	int fd_caller, fd_receiver, i, j;
/*
	char *fifo_filename1="/tmp/myfifo_caller";
	
    if(mkfifo(fifo_filename1 ,0666)==-1){

		printf("Unable to open fifo for caller. Error \n");
		abort();
	}

*/
	char *myfifo_caller="/tmp/myfifo_caller";
	char *myfifo_receiver="/tmp/myfifo_receiver";
	char buffer1[MAXLENGTH+1], buffer2[MAXLENGTH+1];
	printf("Calling....\n");
	printf("Waiting for receiver...\n");
	/*O_NONBLOCK not used, open will wait until receiver opens for reading*/
	fd_caller= open(myfifo_caller, O_WRONLY);
	fd_receiver= open(myfifo_receiver, O_RDONLY);
	
	
	do{
		printf("Caller: ");
		scanf("%1024[^\n]%*c", buffer1); //take callers input
		write(fd_caller, buffer1, MAXLENGTH);
		if(strcmp(buffer1, "Bye")==0)
			break;
		/*EOF is received when write on other end completes exeution*/
		read(fd_receiver, buffer2, MAXLENGTH) ; //read message from receiver
		if(strcmp(buffer2, "Bye")==0)
			break;
		printf("Received : %s\n", buffer2);
	}while(strcmp(buffer2, "Bye"));
	close(fd_caller);
	close(fd_receiver);
	unlink(myfifo_caller);
	return 0;
}

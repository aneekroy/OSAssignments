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
char *fifo_filename2="/tmp/myfifo_receiver";
    
    if(mkfifo(fifo_filename2 ,0666)==-1){

		printf("Unable to open fifo for receiver. Error \n");
		abort();
	}
	printf("Link created\n");

*/
	char *myfifo_caller="/tmp/myfifo_caller";
	char *myfifo_receiver="/tmp/myfifo_receiver";
	char buffer1[MAXLENGTH+1], buffer2[MAXLENGTH+1];
	printf("Receiving....\n ");
	
	fd_caller= open(myfifo_caller, O_RDONLY);
	/*O_NONBLOCK not used, open will wait until caller opens for reading*/
	fd_receiver= open(myfifo_receiver, O_WRONLY);
	
	do{
		
		/*EOF is received when write on other end completes exeution*/
		read(fd_caller, buffer1, MAXLENGTH) ; //read message from caller
		printf("Received : %s\n", buffer1);
		if(strcmp(buffer1, "Bye")==0)
			break;
		printf("Receiver: ");
		scanf("%1024[^\n]%*c", buffer2); //take receivers input
		write(fd_receiver, buffer2, MAXLENGTH);
		if(strcmp(buffer2, "Bye")==0)
			break;
	}while(strcmp(buffer1, "Bye"));
	close(fd_receiver);
	close(fd_caller);
	unlink(myfifo_receiver);
	return 0;
}

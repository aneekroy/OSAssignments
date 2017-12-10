#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXLENGTH 1024

int main (){

	int fd_caller;
	char *myfifo_caller="/tmp/myfifo_listener0";
	char buffer1[MAXLENGTH+1];
	printf("Receiving....\n");
	
	fd_caller= open(myfifo_caller, O_RDONLY);
	do{
		
		/*EOF is received when write on other end completes execution*/
		read(fd_caller, buffer1, MAXLENGTH) ; //read message from broadcaster
		printf("Received : %s\n", buffer1);
	}while(strcmp(buffer1, "Quit"));
	close(fd_caller);
	return 0;
}
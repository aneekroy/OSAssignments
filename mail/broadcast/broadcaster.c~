#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAXLENGTH 1024
#define NO_OF_LISTENERS 2
int main (){

	int fd_listener[4], i, j;
	char buffer1[MAXLENGTH+1], str[50];
	printf("Connecting....\n");
	printf("Waiting for listeners...\n\n");
	/*O_NONBLOCK not used, open will wait until receiver opens for reading*/
	for(i=0;i<NO_OF_LISTENERS;i++){
		
		printf("Waiting for listener%d\n",i);
		sprintf(str, "/tmp/myfifo_listener%d", i);
		fd_listener[i]=open(str, O_WRONLY);
		printf("Connected to listener %d\n",i);
	}
	do{
		printf("Broadcaster: ");
		scanf("%1024[^\n]%*c", buffer1); //take callers input
		for(i=0;i<NO_OF_LISTENERS;i++)
			write(fd_listener[i], buffer1, MAXLENGTH);
		
	}while(strcmp(buffer1, "Quit"));
	for(i=0;i<NO_OF_LISTENERS;i++){
		
		sprintf(str, "/tmp/myfifo_listener%d", i);
		close(fd_listener[i]);
		unlink(str);
	}
	return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#define NO_OF_LISTENES 2
int main(){
	
	char receiver[50];
	for(int i=0;i<NO_OF_LISTENES;i++){
    	
    	sprintf(receiver,"/tmp/myfifo_listener%d",i);
    	if(mkfifo(receiver ,0666)==-1){
			printf("Unable to open fifo for receiver%d. Error \n", i);
			abort();
		}
	}	
	printf("Links created\n");
	return 0;
}	
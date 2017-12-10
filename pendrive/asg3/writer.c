#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

   
    fd = open(myfifo, O_WRONLY);
    char str[20];
    while(1){
    scanf("%s",str);
    write(fd, str, sizeof(str));
    close(fd);
	if(strlen(str))==0){
    /* remove the FIFO */
    unlink(myfifo);
exit(0);
}
}
    return 0;
}

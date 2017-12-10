#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/stat.h>

//#define FIFO_FILE       "MYFIFO"

int main(int argc,char *argv[])
{
        FILE *fp;
        char readbuf[80];
        umask(0);
        if ( argc != 2 ) {      //if client name not given..
                printf("USAGE: fifoclient not given [string]\n");
                exit(1);
        }
        else{
        /* Create the FIFO if it does not exist */
        
        printf("Client name: %s\n",argv[1]);
        
        mknod(argv[1], S_IFIFO|0666, 0);
        //printf("Client name: %s",argv[1]);
        while(1)
        {
                fp = fopen(argv[1], "r");
                fgets(readbuf, 80, fp);
                printf("Received string: %s\n", readbuf);
                fclose(fp);
        }

        return(0);
    }
}

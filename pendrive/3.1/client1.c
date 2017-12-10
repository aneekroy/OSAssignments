#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/stat.h>

//#define FIFO_FILE       "MYFIFO"

int main(int argc, char *argv[])
{
        FILE *fp;
        int i;
        umask(0);
        char readbuf[80];
        if ( argc<2 ) {
                printf("USAGE: fifoclient [string]\n");
                exit(1);
        }
        else{
        for(i=1;i<argc;i++){
            mknod(argv[i], S_IFIFO|0666, 0);
        }
        while(1)
        {
            printf("Write message: ");
            fgets(readbuf,80, stdin);
            
            for(i=1;i<argc;i++){
                
                if((fp = fopen(argv[i], "w")) == NULL) {
                    perror("fopen");
                    exit(1);
                }

            fputs(readbuf, fp);

            fclose(fp);
            }
        }
        }
        return(0);
        
}

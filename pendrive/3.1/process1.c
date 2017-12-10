#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/stat.h>
#define FIFO_FILE1       "MYFIFO1"
#define FIFO_FILE2       "MYFIFO2"

int main(int argc,char *argv[])
{
        FILE *fp2,*fp1;
        char readbuf[80];
        /* Create the FIFO if it does not exist */
        umask(0);
        mknod(FIFO_FILE1, S_IFIFO|0666, 0);
        mknod(FIFO_FILE2, S_IFIFO|0666, 0);
        if(argc==1)
            printf("ERROR\n");
        else if(argc!=3 && strcmp(argv[1],"read")==0){    
            while(1)
            {
                fp1 = fopen(FIFO_FILE1, "r");
                fgets(readbuf, 80, fp1);
                printf("Received string: %s\n", readbuf);
                fclose(fp1);
            }
            
        }
        else if ( argc != 3 &&  strcmp(argv[1],"write")==0){
            while(1){
            printf("Write message: ");
            fgets(readbuf,80, stdin);
            if((fp2 = fopen(FIFO_FILE2, "w")) == NULL) {
                    perror("fopen");
                    exit(1);
            }
            fputs(readbuf, fp2);
            fclose(fp2);
            }

        
        }

        return(0);
}



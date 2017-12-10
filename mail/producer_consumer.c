#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//#define NUM_LOOPS 20
int main(int argc, char* argv[])
{
    int prod,cons,buffsize,p,c,i;
    printf("Enter the no of producers : ");
    scanf("%d",&prod);
    printf("Enter the no of Consumers : ");
    scanf("%d",&cons);
    printf("Enter the Buffer Size : ");
    scanf("%d",&buffsize);
    int sem_set_id;
    int payload[buffsize];
    for(i=1;i<=buffsize;i++)
    	payload[i]=rand()%100;
    p=c=1;
     union semun {
	 int val;
	 struct semid_ds *buf;
	 unsigned short int *array;
    };
    union semun sem_val;
    int child_pid;
    struct sembuf sem_op;
    int rc;
    struct timespec delay;
     
     
    sem_set_id = semget(IPC_PRIVATE, 1, 0600);
    if (sem_set_id == -1) {
        perror("main: semget");
        exit(1);
    }
    printf("Semaphore set created.\nSemaphore set id : %d\n\n", sem_set_id);
    printf("/*Item ID invloves item no,producer/consumer no and the item payload.*/\n");
     
    sem_val.val = 0;
    rc = semctl(sem_set_id, 0, SETVAL, sem_val);
    child_pid = fork();
    switch (child_pid) {
        case -1:
        perror("fork");
        exit(1);
        case 0:
       // for (i=1; i<=cons; i++) {
	for (i=1; ; i++) {
	if(i>cons)i=1;
            sem_op.sem_num = 0;
            sem_op.sem_op = -1;
            sem_op.sem_flg = 0;
            semop(sem_set_id, &sem_op, 1);
            printf("Consumer %d consumes Item no. %d with Item ID %d and item_payload %d \n",c,i,((1000*c+100*i+10*(payload[i]/10)+payload[i]%10)%10000),payload[i]);
            c++;
		
            fflush(stdout);
            sleep(2);
		

        }
        break;
        default:
        for (i=1; i<=prod; i++)
	//for (i=1;; i++)
        {
            printf("Producer %d produces Item no. %d with Item ID %d and item_payload %d \n",p,i,((1000*p+100*i+10*(payload[i]/10)+payload[i]%10)%10000),payload[i]);
            p++;
		
            fflush(stdout);
            sem_op.sem_num = 0;
            sem_op.sem_op = 1;
            sem_op.sem_flg = 0;
            semop(sem_set_id, &sem_op, 1);
            sleep(3);
        }
        break;
    }
     
     
    return 0;
}

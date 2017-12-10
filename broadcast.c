/*
 * queue_sender.c - a program that reads messages with one of 3 identifiers
 *                  to a message queue.
 */

#include <stdio.h>       /* standard I/O functions.              */
#include <stdlib.h>      /* malloc(), free() etc.                */
#include <string.h>
#include <sys/types.h>   /* various type definitions.            */
#include <sys/ipc.h>     /* general SysV IPC structures          */
#include <sys/msg.h>     /* message queue functions and structs. */
#define MAX_MSG_SIZE 100
#define NUM_MESSAGES 3
//#include "queue_defs.h"  /* definitions shared by both programs  */
struct msgbuf {
       long mtype;     /* message type, must be > 0 */
       char mtext[1];  /* message data */
            };

int main(int argc, char* argv[])
{
    int queue_id;             /* ID of the created queue.            */
    struct msgbuf* msg;       /* structure used for sent messages.   */
    /*struct msgbuf* recv_msg;*/
    int i;                    /* loop counter                        */
    int rc;                   /* error code retuend by system calls. */

    /* create a public message queue, with access only to the owning user. */
    queue_id = msgget(250, IPC_CREAT | IPC_EXCL | 0600);
    if (queue_id == -1) {
	perror("main: msgget");
	exit(1);
    }
    printf("message queue created, queue id '%d'.\n", queue_id);
    msg = (struct msgbuf*)malloc(sizeof(msg)+1+MAX_MSG_SIZE);

    /* form a loop of creating messages and sending them. */
    for (i=1; i <= NUM_MESSAGES; i++) {
        msg->mtype = (i % 3) + 1; /* create message type between '1' and '3' */
        sprintf(msg->mtext, "hello world - %d", i);
        rc = msgsnd(queue_id, msg, strlen(msg->mtext)+1, 0);
        if (rc == -1) {
	    perror("main: msgsnd");
	    exit(1);
        }
    }
    /* free allocated memory. */
    free(msg);
    
    printf("generated %d messages, exiting.\n", NUM_MESSAGES);

    return 0;
}


/*
 * queue_reader.c - a program that reads messages with a given identifier
 *                  off of a message queue.
 */

#include <stdio.h>       /* standard I/O functions.              */
#include <stdlib.h>      /* malloc(), free() etc.                */
#include <unistd.h>      /* sleep(), etc.                        */
#include <sys/types.h>   /* various type definitions.            */
#include <sys/ipc.h>     /* general SysV IPC structures          */
#include <sys/msg.h>     /* message queue functions and structs. */
#define MAX_MSG_SIZE 100
#define NUM_MESSAGES 1
//#include "queue_defs.h"  /* definitions shared by both programs  */
struct msgbuf {
       long mtype;     /* message type, must be > 0 */
       char mtext[1];  /* message data */
            };

void main(int argc, char* argv[])
{
    int queue_id;             /* ID of the created queue.              */
    struct msgbuf* msg;       /* structure used for received messages. */
    int rc;                   /* error code returned by system calls.  */
    int msg_type;             /* type of messages we want to receive.  */

    /* read message type from command line */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message type>\n", argv[0]);
        fprintf(stderr, "       <message type> must be between 1 and 3.\n");
	exit(1);
    }
    msg_type = atoi(argv[1]);
    if (msg_type < 1 || msg_type > 3) {
        fprintf(stderr, "Usage: %s <message type>\n", argv[0]);
        fprintf(stderr, "       <message type> must be between 1 and 3.\n");
	exit(1);
    }

    /* access the public message queue that the sender program created. */
    queue_id = msgget(250, 0);
    if (queue_id == -1) {
	perror("main: msgget");
	exit(1);
    }
    printf("message queue opened, queue id '%d'.\n", queue_id);
    msg = (struct msgbuf*)malloc(sizeof(struct msgbuf)+MAX_MSG_SIZE);

    /* form a loop of receiving messages and printing them out. */
    while (1) {
        rc = msgrcv(queue_id, msg, MAX_MSG_SIZE+1, msg_type, 0);
        if (rc == -1) {
	    perror("main: msgrcv");
	    exit(1);
        }
	printf("Reader '%d' read message: '%s'\n", msg_type, msg->mtext);
        /* slow down a little... */
        sleep(2);
    }
    /* NOT REACHED */
}


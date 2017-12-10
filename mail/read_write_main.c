#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <inttypes.h>

sem_t mutex, r;
int data, wcount=0;

void *read(void *arg){
	int *index;
	index=(int *)(uintptr_t)arg;

	sem_wait(&r);
	printf("Reader: %d, Data read: %d\n\n", *index, data);
	sleep(1);
	sem_post(&r);
}

void *write(void *arg){
	int *index;
	index=(int *)(uintptr_t)arg;

	sem_wait(&mutex);
	wcount++;
	if(wcount==1){
		sem_wait(&r);
		printf("\n--Writer Waiting--\n %d", wcount);
	}
	sem_post(&mutex);

	sem_wait(&mutex);
	data++;
	printf("Writer: %d, Data written: %d\n\n", *index, data);
	sleep(1);
	//sem_post(&mutex);

	//sem_wait(&mutex);
	wcount--;
	if(wcount==0){
		sem_post(&r);
		printf("\n--No Writer Waiting--\n %d", wcount);
	}
	sem_post(&mutex);
}

main(){
	int i;
	pthread_t reader_t[10], writer_t[10];
	int reader_no[10], writer_no[10];

	sem_init(&mutex,0,1);
	sem_init(&r,0,1);

	for(i=1;i<=10;i++){
		reader_no[i-1]=i;
		writer_no[i-1]=i;
		pthread_create(&writer_t[i-1], NULL, write, &reader_no[i-1]);
		pthread_create(&reader_t[i-1], NULL, read, &writer_no[i-1]);
	}

	for(i=0;i<10;i++){
		pthread_join(writer_t[i], NULL);
		pthread_join(reader_t[i], NULL);
	}

	return 0;
}

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t slot_free,item_present;
pthread_t prod_t[20],cons_t[20];

int* buffer;
int buffersize;
int in,out,count;
pthread_mutex_t mutex,mutex1;

void initialize(){
	buffer = (int*)malloc(buffersize*sizeof(int));
	count = 0;
	in = 0;
	out =0;
	pthread_cond_init(&slot_free,NULL);
	pthread_cond_init(&item_present,NULL);
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_init(&mutex1,NULL);



}

void write(int item){
	pthread_mutex_lock(&mutex);
	while (count==buffersize){
		pthread_cond_wait(&slot_free,&mutex);
	}

	int wait = rand()%4;
	sleep(wait);	
	
	buffer[in] = item;
	in = (in+1)%buffersize;
	count++;
	pthread_cond_signal(&item_present);
	pthread_mutex_unlock(&mutex);

}

int read(){

	pthread_mutex_lock(&mutex1);
	while (count==0){
		pthread_cond_wait(&item_present,&mutex1);
	}
	int wait = rand()%4;
	sleep(wait);
	
	int item = buffer[out];
	out = (out+1)%buffersize;
	count--;

	pthread_cond_signal(&slot_free);
	pthread_mutex_unlock(&mutex1);

	return item;
	
}

void* producer(void *param){
	int item= rand()%10000;
	
	int *i = ((int*)param);
	while (item<1000)
		item= rand()%10000;
	write(item);
	printf("Producer %d placed %d in the buffer\n",*i,item);
}

void* consumer(void *param){
	int item;;
	int *i = (int*)param;
	item = read();
	printf("Consumer %d consumed %d\n",*i,item );
}

int main(){
	int nprod,ncons,i;
	printf("Enter no of producers,consumers & buffer-size: ");
	scanf("%d %d %d",&nprod,&ncons,&buffersize);
	int prod_i[nprod],cons_i[ncons]; 
	initialize(buffersize);
	for(i=0;i<nprod;i++){
		prod_i[i]=i;
		pthread_create(&prod_t[i],NULL,producer,(void*)&prod_i[i]);
	}
	for(i=0;i<ncons;i++){
		cons_i[i]=i;
		pthread_create(&cons_t[i],NULL,consumer,(void*)&cons_i[i]);
	}
	for(i=0;i<nprod;i++)
		pthread_join(prod_t[i],NULL);
	for(i=0;i<ncons;i++)
		pthread_join(cons_t[i],NULL);
}

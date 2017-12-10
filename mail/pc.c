#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,write_block;
int data = 1,rcount = 1;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex);
  rcount = rcount + 1;
	printf("\nIncreasing Read Count !\n\n");
  if(rcount==1)
   sem_wait(&write_block);
  sem_post(&mutex);
  printf("\nData read by the Reader %d is %d\n",f,data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
	printf("\nDecreasing Read Count !!");
  if(rcount==0)
   sem_post(&write_block);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);

  sem_wait(&write_block);

  printf("\nBlocking All other Writers !\n");
  data++;
  printf("\nData written by the Writer %d is %d\n",f,data);
  sleep(1);
  sem_post(&write_block);
}

int main()
{
  int i,b,wr,rd;
  printf("Enter the number of writers :");
  scanf("%d",&wr);
  printf("Enter the number of readers :");
  scanf("%d",&rd);
  printf("\n/**/\n\n");
  pthread_t rtid[20],wtid[20];
  sem_init(&mutex,0,1);
  sem_init(&write_block,0,1);
  for(i=1;;i++)
  {
    pthread_create(&wtid[i],NULL,writer,(void *)i);
 
    pthread_create(&rtid[i],NULL,reader,(void *)i);
 
    pthread_join(wtid[i],NULL);
 
    pthread_join(rtid[i],NULL);
  }
  return 0;
}

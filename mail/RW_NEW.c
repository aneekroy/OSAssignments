#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t read_block,write_block,x,y,z;
int data = 1,rcount = 0,wcount=0;

void *reader(void *arg)
{
  int f;
//while(1){
  f = ((int)arg);
  sem_wait(&z);
  sem_wait(&read_block);
  sem_wait(&x);
  rcount = rcount + 1;
	printf("\nIncreasing Read Count !\n");
  if(rcount==1)
   sem_wait(&write_block);
  sem_post(&x);
  sem_post(&read_block);
  sem_post(&z);	
  printf("\nData read by the Reader %d is %d\n",f,data);
  sleep(1);
  sem_wait(&x);
  rcount = rcount - 1;
	printf("\nDecreasing Read Count !!\n");
  if(rcount==0)
   sem_post(&write_block);
  sem_post(&x);
//}
}
/* writecount++;
        if (writecount==1) 
             wait(rsem);
      signal(y);
      wait(wsem);
      doWriting();
      signal(wsem);
      wait(y);
        writecount--;
        if (writecount==0)
             signal(rsem);
      signal(y);
*/
void *writer(void *arg)
{
  int f;
//while(1){
  f = ((int) arg);
	
  sem_wait(&y);
	if(wcount==1)
	sem_wait(&read_block);
  sem_post(&y);
  sem_wait(&write_block);
  printf("\nBlocking All other Writers !\n");
  data++;
  printf("\nData written by the Writer %d is %d\n",f,data);
  sleep(1);
  sem_post(&write_block);
  sem_wait(&y);
  wcount--;
	if(wcount==0)
	sem_post(&read_block);
sem_post(&y);
//  }
}

int main()
{
  int i,b,wr,rd;
  printf("\nEnter the number of writers :\n");
  scanf("%d",&wr);
  printf("\nEnter the number of readers :\n");
  scanf("%d",&rd);
  printf("\n/** Writing starts here **/\n\n");
  pthread_t rtid[20],wtid[20];
  sem_init(&read_block,0,1);
  sem_init(&write_block,0,1);
  sem_init(&x,0,1);
  sem_init(&y,0,1);
  sem_init(&z,0,1);
while(1){
  for(i=1;i<=wr;i++)
  {
    pthread_create(&wtid[i],NULL,writer,(void *)i);
  }
  for(i=1;i<=rd;i++)
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  
  for(i=1;i<=wr;i++)
  {
    pthread_join(wtid[i],NULL);
  }
  for(i=1;i<=rd;i++){
    pthread_join(rtid[i],NULL);
  }
}
  return 0;
}

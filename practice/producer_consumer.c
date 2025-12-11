#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
#define buff 5
int in=0,out=0;
int buffer[buff];
sem_t empty;
sem_t full;
sem_t mutex;
void* producer()
{
    for(int i=0;i<10;i++)
    {
        int item=i+1;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in]=item;
        printf("producer produced : %d\n",item);
        in=(in+1)%buff;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}
void* consumer()
{
    for(int i=0;i<10;i++)
    {
        
        sem_wait(&full);
        sem_wait(&mutex);
       int item=buffer[out];
        printf("consumer consumed : %d\n",item);
        out=(out+1)%buff;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}
int main()
{
    pthread_t cons,prod;
    sem_init(&empty,0,buff);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    
    pthread_create(&prod,NULL,producer,NULL);
    pthread_create(&cons,NULL,consumer,NULL);
    
    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
}
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#define n 5
sem_t chopstick[n];
void* philosopher(void * arg)
{
    int id=*(int *)arg;
    while(1)
    {
        printf("%d thinking\n",id);
        sleep(1);
        if(id%2==0)
        {
            sem_wait(&chopstick[id]);
            sem_wait(&chopstick[(id+1)%n]);
        }
        else{
            sem_wait(&chopstick[(id+1)%n]);
            sem_wait(&chopstick[id]);
        }
        printf(" %d eating\n",id);
        sleep(2);
        
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id+1)%n]);
        printf("%d finished eating\n",id);
    }
    return NULL;
}
int main()
{
    pthread_t tid[n];
    int ids[n];
    for(int i=0;i<n;i++)
    {
        sem_init(&chopstick[i],0,1);
    }
    for(int i=0;i<n;i++)
    {
        ids[i]=i;
        pthread_create(&tid[i],NULL,philosopher,&ids[i]);
    }
    for(int i=0;i<n;i++)
    {
        pthread_join(tid[i],NULL);
    }
}
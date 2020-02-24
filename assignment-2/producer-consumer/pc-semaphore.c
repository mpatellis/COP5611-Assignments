#include "pc-semaphore.h"
 
int main(void) 
{
    pthread_t producerThread, consumerThread;  
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    sem_init(&empty, 1, 1);
    sem_init(&full, 1, 0);

    pthread_create(&producerThread, &attr, producer, NULL);
    pthread_create(&consumerThread, &attr, consumer, NULL);
    
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}
 
void *producer(void *in) 
{
    int produced;
    for (produced = 0; produced < NUM_ITER; produced++) 
    {
        sem_wait(&empty);
        buff = produced;
        printf("Producer: new buff = %d\n", buff);
        sem_post(&full);
    }
}
 
void *consumer(void *in) 
{
    int total = 0, i;
    for (i = 0; i < NUM_ITER; i++) 
    {
        sem_wait(&full);
        total += buff;
        printf("Consumer: new total = %d\n", total);
        sem_post(&empty);
    }
    printf("Final total is %d after %d iterations\n", total, NUM_ITER);
}
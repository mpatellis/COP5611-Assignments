#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define NUM_ITER 5

void *producer(void *in);
void *consumer(void *in);
 
sem_t empty, full;
int buff;

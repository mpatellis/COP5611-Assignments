#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_empty = PTHREAD_COND_INITIALIZER;

int list[50];
int readIndex = 0;
int writeIndex = 0;

void* consumer();
void* producer();

int main(void);
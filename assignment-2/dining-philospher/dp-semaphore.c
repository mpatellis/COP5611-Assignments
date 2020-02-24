#include "dp-semaphore.h"

void try_eat(int phIndex)
{
    if (state[phIndex] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        state[phIndex] = EATING; 
  
        sleep(1);
        printf("Philosopher %d takes fork %d and %d\n", phIndex+1, LEFT+1, phIndex+1); 
        printf("Philosopher %d is eating\n", phIndex+1);
  
        sem_post(&S[phIndex]); 
    } 
} 
  
void pickup_fork(int phIndex) 
{ 
    sem_wait(&sem); 
  
    state[phIndex] = HUNGRY; 
  
    printf("Philosopher %d hungers\n", phIndex+1); 
  
    try_eat(phIndex); 
  
    sem_post(&sem); 
    sem_wait(&S[phIndex]); 
    sleep(1); 
} 
  
void putdown_fork(int phIndex) 
{
    sem_wait(&sem); 
  
    state[phIndex] = THINKING; 
  
    printf("Philosopher %d putting fork %d and %d down\n", phIndex+1, LEFT+1, phIndex+1); 
    printf("Philosopher %d is thinking\n", phIndex+1); 
  
    try_eat(LEFT); 
    try_eat(RIGHT); 
  
    sem_post(&sem); 
} 
  
void* philospher(void* num) 
{ 
    while (1) 
    { 
        int* i = num; 
        
        sleep(1);

        pickup_fork(*i); 
        sleep(0); 
        putdown_fork(*i); 
    } 
} 
  
int main() 
{
    int i; 
    pthread_t thread_id[NUM_PHIL]; 
  
    sem_init(&sem, 0, 1); 
  
    for (i = 0; i < NUM_PHIL; i++)
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < NUM_PHIL; i++) 
    { 
        pthread_create(&thread_id[i], NULL, philospher, &phils[i]); 
        printf("Philosopher %d is thinking\n", i + 1); 
    } 
  
    for (i = 0; i < NUM_PHIL; i++)
        pthread_join(thread_id[i], NULL); 
} 

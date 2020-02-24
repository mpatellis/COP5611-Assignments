#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define NUM_PHIL 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phIndex + 4) % NUM_PHIL 
#define RIGHT (phIndex + 1) % NUM_PHIL 
  
int state[NUM_PHIL]; 
int phils[NUM_PHIL] = {0, 1, 2, 3, 4}; 
  
sem_t sem; 
sem_t S[NUM_PHIL];  

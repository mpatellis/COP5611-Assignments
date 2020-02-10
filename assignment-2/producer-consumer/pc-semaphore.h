#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int list[50];
int index = 0;

pthread_mutex_t mutex;
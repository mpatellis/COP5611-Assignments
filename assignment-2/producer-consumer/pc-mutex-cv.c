#include "pc-mutex-cv.h"

int main(void)
{
    int i;
    pthread_t threads[NUM_THREAD];
    int id[NUM_THREAD] = {0, 1, 2, 3, 4};

    for (i = 0; i < NUM_THREAD; i++)
    {
        if (i%2 == 0)
            pthread_create(&threads[i], NULL, (void*)consumer, &id[i]);
        else
            pthread_create(&threads[i], NULL, (void*)producer, &id[i]);
    }
    
    for (i = 0; i < NUM_THREAD; i++)
    {
        printf("hello main   %d\n", i);
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* consumer(int *id)
{
    int i = 0;
    pthread_mutex_lock(&mutex);

    while (i < 50)
    {
        pthread_cond_wait(&cond_empty, &mutex);

        printf("Consumed value is %d by thread id %d\n", list[readIndex], *id);
        readIndex = (readIndex+1)%50;

        i++;
    }

    pthread_mutex_unlock(&mutex);
}

void* producer(int *id)
{
    int i = 0;

    while(i < 50)
    {
        pthread_mutex_lock(&mutex);

        list[writeIndex] = rand()%100;
        printf("%d produced: %d by %d\n", i, list[writeIndex], *id);
        writeIndex = (writeIndex+1)%50;
        i++;

        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(&mutex);
    }
}
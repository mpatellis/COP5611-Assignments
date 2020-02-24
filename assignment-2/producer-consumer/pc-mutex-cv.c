#include "pc-mutex-cv.h"

int main(void)
{
    int i;
    pthread_t threads[NUM_THREAD];
    int id[NUM_THREAD] = {0, 1};
    

    for (i = 0; i < NUM_THREAD; i++)
    {
        if (i%2 == 0)
            pthread_create(&threads[i], NULL, (void*)consumer, &id[i]);
        else
            pthread_create(&threads[i], NULL, (void*)producer, &id[i]);
    }

    for (i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void* consumer(int *id)
{
    int i = 0;
    pthread_mutex_lock(&mutex);

    while (i < NUM_ITER)
    {
        pthread_cond_wait(&cond_empty, &mutex);

        printf("Consumed value is %d by thread id %d\n", list[readIndex], *id);
        readIndex = (readIndex+1)%NUM_ITER;

        i++;

        if (i < (NUM_ITER-2))
        {
            sleep(5);
        }
    }

    pthread_mutex_unlock(&mutex);
}

void* producer(int *id)
{
    int i = 0;

    while(i < NUM_ITER)
    {
        pthread_mutex_lock(&mutex);

        list[writeIndex] = rand()%100;
        printf("%d produced: %d by %d\n", i, list[writeIndex], *id);
        writeIndex = (writeIndex+1)%NUM_ITER;
        i++;

        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(&mutex);

        if (i < (NUM_ITER-2))
        {
            sleep(5);
        }
    }
}
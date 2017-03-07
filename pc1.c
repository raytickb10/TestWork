#include <stdio.h>
#include <pthread.h>

#define MAX 1000000             /* how many numbers to produce */
#define BUFFER_SIZE 10          /* buffer size */

pthread_cond_t full, empty;    /* condition variables for the consumer and the producer */

int buffer[BUFFER_SIZE];        /* buffer used between producer and consumer */

void *producer(void *ptr)   /* produce data */
{
    int i;

    for (i = 1; i <= MAX; i++)
    {      
        while (buffer[i] != 0) pthread_cond_wait(&empty);
        buffer[i] = i;                    /* put item in buffer */
        pthread_cond_signal(&full);      /* wake up consumer */
    }
    pthread_exit(0);
}

void *consumer(void *ptr)   /* consume data */
{
    int i;

    for (i = 1; i <= MAX; i++)
    {      
        while (buffer[i] == 0) pthread_cond_wait(&full);
        buffer[i] = 0;                    /* take item out of buffer */
        pthread_cond_signal(&empty);      /* wake up producer */
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t pro, con;
    pthread_cond_init(&full, 0);
    pthread_cond_init(&empty, 0);
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);    
    pthread_join(pro, 0);
    pthread_join(con, 0);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
}

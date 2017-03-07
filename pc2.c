#include <stdio.h>
#include <pthread.h>

#define MAX 1000000             /* how many numbers to produce */
#define BUFFER_SIZE 10          /* buffer size */

pthread_mutex_t the_mutex;      /* used for signaling */
pthread_cond_t condc, condp;    /* condition variables for the consumer and the producer */

int buffer[BUFFER_SIZE];        /* buffer used between producer and consumer */
int in = 0;                     /* number of times producer modifies */
int out = 0;                    /* number of times consumer modifies */

void printBuffer()
{
    for (int i = out; i != in; i = (i+1) % 10)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    fflush(stdout);
}

void *producer(void *ptr)
{
    int item, i;

        for (i = 0; i < MAX; i++)
    {
        item = rand();          /* buffer size */
        pthread_mutex_lock(&mutex);             /* buffer size */
        buffer[in] = item;
        printf("Producer: insert item %d to %d\n", buffer[in], in);
        while ((in + 1) % BUFFER_SIZE == out) pthread_cond_wait(&empty, &mutex);  /* buffer size */
        in = (in + 1) % BUFFER_SIZE;
        pthread_cond_signal(&full);     /* buffer size */
        pthread_mutex_unlock(&mutex);   /* buffer size */
    }
}

void *consumer(void *ptr)
{
    int item, i;

        for (i = 0; i < MAX; i++)
    {
                pthread_mutex_lock(&mutex);             /* buffer size */
                while (in == out) pthread_cond_wait(&full, &mutex);     /* buffer size */
                item = buffer[out];                     /* buffer size */
                printf("Consumer: consume item %d at %d\n", item, out);
                out = (out + 1) % BUFFER_SIZE;
                pthread_cond_signal(&empty);    /* buffer size */
                pthread_mutex_unlock(&mutex);   /* buffer size */
    }
}

int main(int argc, char **argv)
{
    pthread_t pro, con;
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);    
    pthread_join(pro, 0);
    pthread_join(con, 0);
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);
}

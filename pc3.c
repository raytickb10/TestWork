#include <stdio.h>
#include <pthread.h>

#define MAX 1000000             /* how many numbers to produce */
#define BUFFER_SIZE 10          /* buffer size */

pthread_mutex_t the_mutex;      /* used for signaling */
pthread_cond_t full, empty;    /* condition variables for the consumer and the producer */

int buffer[BUFFER_SIZE];        /* buffer used between producer and consumer */
int p_counter = 0;                     
int c_counter = 0;                    

void printBuffer()
{
    int i;
    for (i = c_counter; i != p_counter; i = (i+1) % 10)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    fflush(stdout);
}

void *producer(void *ptr)   /* produce data */
{
    int item, i;

    for (i = 1; i <= MAX; i++)
    {      
        pthread_mutex_lock(&the_mutex);   /* get exclusive access to buffer */
        buffer[p_counter] = item;
        printf("Producer: insert item %d to %d\n", buffer[p_counter], in);
        while ((p_counter + 1) % BUFFER_SIZE == c_counter) pthread_cond_wait(&empty, &the_mutex);  
        p_counter = (p_counter + 1) % BUFFER_SIZE;                    /* put item in buffer */
        pthread_cond_signal(&full);      /* wake up consumer */
        pthread_mutex_unlock(&the_mutex); /* release access to buffer */
    }
    pthread_exit(0);
}

void *consumer(void *ptr)   /* consume data */
{
    int item, i;

    for (i = 1; i <= MAX; i++)
    {      
        pthread_mutex_lock(&the_mutex);   /* get exclusive access to buffer */
        while (p_counter == c_counter) pthread_cond_wait(&full, &the_mutex);    
        item = buffer[c_counter];                     
        printf("Consumer: consume item %d at %d\n", item, c_counter);
        c_counter = (c_counter - 1) % BUFFER_SIZE;                    /* take item out of buffer */
        pthread_cond_signal(&empty);      /* wake up producer */
        pthread_mutex_unlock(&the_mutex); /* release access to buffer */
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t pro, con;
    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&full, 0);
    pthread_cond_init(&empty, 0);
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);    
    pthread_join(pro, 0);
    pthread_join(con, 0);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    pthread_mutex_destroy(&the_mutex);
}

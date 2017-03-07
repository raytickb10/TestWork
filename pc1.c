/*
 * Name: Brian Raytick
 * Class: CSCI 3000 Spring 2017
 * Instructor: Karl Abrahamson
*/

#include <stdio.h>
#include <pthread.h>

#define MAX 1000000             /* how many numbers to produce */
#define BUFFER_SIZE 10          /* buffer size */

int buffer[BUFFER_SIZE];        /* buffer used between producer and consumer */

void *producer(void *ptr)   /* produce data */
{
    int i;

    for (i = 1; i <= MAX; i++)
    {      
        buffer[i] = i;                    /* put item in buffer */
    }
    pthread_exit(0);
}

void *consumer(void *ptr)   /* consume data */
{
    int i;

    for (i = 1; i <= MAX; i++)
    {      
        buffer[i] = 0;                    /* take item out of buffer */
    }
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t pro, con;
    pthread_create(&con, 0, consumer, 0);
    pthread_create(&pro, 0, producer, 0);    
    pthread_join(pro, 0);
    pthread_join(con, 0);
}

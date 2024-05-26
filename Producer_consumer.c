#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

/*
This program provides a possible solution for producer-consumer problem using mutex and semaphore.
I have used 5 producers and 5 consumers to demonstrate the solution. You can always play with these values.
*/

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce an random item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}
void *consumer(void *cno)
{   
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main()
{   

    pthread_t pro[5],con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[5] = {1,2,3,4,5}; //Just used for numbering the producer and consumer

    for(int i = 0; i < 5; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}



/*

This program will terminate when all producers and consumers have completed their tasks. 
Here's a detailed explanation of how and when this happens:

1. Initialization:
    
   * 'MaxItems' is defined as 5, meaning each producer will produce 5 items and each consumer will consume 5 items.
   * 'BufferSize' is set to 5, which is the size of the buffer shared between producers and consumers.
   *  Semaphores 'empty' and 'full' are initialized. 'empty' is initialized to 'BufferSize' (5), indicating the buffer has 5 empty slots initially.
     'full' is initialized to 0, indicating no items are in the buffer initially.
   * A mutex 'mutex' is initialized for protecting the critical section of code where the buffer is accessed.



2. Producer and Consumer Creation

   * Five producer threads (pro[5]) and five consumer threads (con[5]) are created.
     Each thread is passed a unique number (from 1 to 5) for identification.


3. Producers Execution

   * Each producer thread runs the 'producer' function. Inside the 'producer' function:
     
     * The producer generates 5 items (since 'MaxItems' is 5).
     * For each item, the 'producer':
       * Waits for an empty slot in the buffer (sem_wait(&empty)).
       * Locks the mutex ('pthread_mutex_lock(&mutex)''), inserts the item into the buffer, and updates the 'in' index.
       * Unlocks the mutex ('pthread_mutex_unlock(&mutex)'').
       * Signals that there is one more item in the buffer (sem_post(&full)).
       

4. Consumers Execution

   * Each consumer thread runs the 'consumer' function. Inside the 'consumer' function:
    
     * The consumer consumes 5 items (since 'MaxItems' is 5).
     * For each item, the 'consumer':
       * Waits for an item to be present in the buffer (sem_wait(&full)).
       * Locks the mutex (pthread_mutex_lock(&mutex)), removes the item from the buffer, and updates the out index.
       * Unlocks the mutex (pthread_mutex_unlock(&mutex)).
       * Signals that there is one more empty slot in the buffer (sem_post(&empty)).


5. Termination
 
   * The main function waits for all producer threads to complete using pthread_join(pro[i], NULL).
   * Then it waits for all consumer threads to complete using pthread_join(con[i], NULL).
   * Once all producer and consumer threads have finished, the main function destroys the mutex and semaphores (pthread_mutex_destroy, sem_destroy),
     and then terminates.



SUMMARY 

The program will terminate after:

  * All five producer threads have each produced 5 items (a total of 25 items).
  * All five consumer threads have each consumed 5 items (a total of 25 items).

  Each producer and consumer will wait for the respective conditions (empty slots or full slots) to be met,
  ensuring proper synchronization and preventing deadlock or race conditions.

*/
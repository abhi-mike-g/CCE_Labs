#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Buffer size (bounded buffer)
#define PRODUCER_COUNT 1
#define CONSUMER_COUNT 1

// Buffer to store the items
int buffer[BUFFER_SIZE];
int in = 0;  // Index for next produced item
int out = 0; // Index for next consumed item

// Semaphores
sem_t empty;  // Count of empty slots in the buffer
sem_t full;   // Count of full slots in the buffer
sem_t mutex;  // Mutex for mutual exclusion to modify buffer

// Function to simulate the producer's behavior
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Produce 10 items
        sleep(rand() % 3);  // Simulate the time taken to produce an item
        sem_wait(&empty);   // Wait for an empty slot
        sem_wait(&mutex);   // Enter critical section

        // Produce an item and add it to the buffer
        buffer[in] = i;
        printf("Produced: %d at index %d\n", i, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // Exit critical section
        sem_post(&full);    // Signal that there is a new full slot
    }
    return NULL;
}

// Function to simulate the consumer's behavior
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {  // Consume 10 items
        sleep(rand() % 3);  // Simulate the time taken to consume an item
        sem_wait(&full);    // Wait for a full slot
        sem_wait(&mutex);   // Enter critical section

        // Consume an item from the buffer
        int item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // Exit critical section
        sem_post(&empty);   // Signal that there is a new empty slot
    }
    return NULL;
}

int main() {
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, all slots are empty
    sem_init(&full, 0, 0);             // Initially, no slots are full
    sem_init(&mutex, 0, 1);            // Mutex starts unlocked

    // Create producer and consumer threads
    pthread_t producer_thread[PRODUCER_COUNT], consumer_thread[CONSUMER_COUNT];

    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_create(&producer_thread[i], NULL, producer, NULL);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_create(&consumer_thread[i], NULL, consumer, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < PRODUCER_COUNT; i++) {
        pthread_join(producer_thread[i], NULL);
    }

    for (int i = 0; i < CONSUMER_COUNT; i++) {
        pthread_join(consumer_thread[i], NULL);
    }

    // Clean up semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

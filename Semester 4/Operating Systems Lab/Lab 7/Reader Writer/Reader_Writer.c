// Reader Writer Problem

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5  // Maximum number of readers

// Semaphore declarations
sem_t mutex, write_lock;
int read_count = 0;

// Function for reader
void *reader(void *param) {
    // Reader's attempt to access the resource
    sem_wait(&mutex);  // Lock the mutex to update the reader count
    read_count++;
    if (read_count == 1) {
        // If it's the first reader, acquire the write_lock (no writers allowed)
        sem_wait(&write_lock);
    }
    sem_post(&mutex);  // Unlock the mutex

    // Simulate reading from the resource
    printf("Reader %ld is reading the resource\n", (long)param);
    sleep(1);  // Simulate reading time

    sem_wait(&mutex);  // Lock the mutex to update the reader count
    read_count--;
    if (read_count == 0) {
        // If it's the last reader, release the write_lock (writers can write now)
        sem_post(&write_lock);
    }
    sem_post(&mutex);  // Unlock the mutex

    return NULL;
}

// Function for writer
void *writer(void *param) {
    // Writer's attempt to access the resource
    sem_wait(&write_lock);  // Lock for writing (exclusive access)

    // Simulate writing to the resource
    printf("Writer %ld is writing to the resource\n", (long)param);
    sleep(2);  // Simulate writing time

    sem_post(&write_lock);  // Unlock the write_lock

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_READERS];
    
    // Initialize the semaphores
    sem_init(&mutex, 0, 1);  // Mutex for protecting read_count
    sem_init(&write_lock, 0, 1);  // Semaphore for write access

    // Create reader and writer threads
    for (long i = 0; i < MAX_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)i);
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    // Destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_lock);

    return 0;
}

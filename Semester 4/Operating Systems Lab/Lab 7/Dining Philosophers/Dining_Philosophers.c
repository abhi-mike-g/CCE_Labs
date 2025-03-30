//Dining Philosophers

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Semaphores for controlling access to forks
sem_t forks[NUM_PHILOSOPHERS];

// Function to simulate thinking
void think(int philosopher_id) {
    printf("Philosopher %d is thinking.\n", philosopher_id);
    sleep(2);  // Simulate thinking time
}

// Function to simulate eating
void eat(int philosopher_id) {
    printf("Philosopher %d is eating.\n", philosopher_id);
    sleep(2);  // Simulate eating time
}

// Function to handle the philosopher's actions (pick up forks, eat, release forks)
void* philosopher(void* num) {
    int philosopher_id = *(int*)num;

    while (1) {
        think(philosopher_id);  // Philosopher is thinking

        // Pick up the left and right fork (semaphores)
        sem_wait(&forks[philosopher_id]);  // Pick up left fork
        sem_wait(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Pick up right fork

        eat(philosopher_id);  // Philosopher is eating

        // Put down the forks after eating
        sem_post(&forks[philosopher_id]);  // Release left fork
        sem_post(&forks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Release right fork
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores (forks) with value 1 (indicating each fork is available)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher, (void*)&philosopher_ids[i]);
    }

    // Wait for all threads to finish (this will not actually happen since philosophers are always thinking/eating)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 2

// Global semaphore
sem_t semaphore;

// Function that each thread will execute
void* thread_function(void* arg) {
    int thread_id = *((int*)arg);

    // Wait (decrement semaphore)
    sem_wait(&semaphore);
    printf("Thread %d is in the critical section\n", thread_id);
    
    // Simulate some work
    sleep(1);

    // Signal (increment semaphore)
    sem_post(&semaphore);
    printf("Thread %d has left the critical section\n", thread_id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Initialize semaphore (value of 1 allows one thread at a time)
    sem_init(&semaphore, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}

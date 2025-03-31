/*Henok Woldemichael 001198444*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t leftChopstick;
sem_t rightChopstick;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <num_threads> <num_meals>\n", argv[0]);
        return 1;
    }

    int numThreads = atoi(argv[1]);
    int numMeals = atoi(argv[2]);
    pthread_t threads[numThreads];

    sem_init(&leftChopstick, 0, 1);
    sem_init(&rightChopstick, 0, 1);

    for (int i = 0; i < numMeals; i++) {
        for (int j = 1; j <= numThreads; j++) {
            if (j % 2 == 1) {
                printf("Odd philosopher %d picking up left chopstick\n", j);
                sem_wait(&leftChopstick);

                printf("Odd philosopher %d picking up right chopstick\n", j);
                sem_wait(&rightChopstick);
                printf("Odd philosopher %d Eating\n", j);
                printf("All other philosophers Thinking\n");

                sleep(1);

                sem_post(&leftChopstick);
                sem_post(&rightChopstick);
                printf("Odd philosopher %d Done Eating, resources freed up.\n", j);
            } else {
                printf("Even philosopher %d picking up right chopstick\n", j);
                sem_wait(&rightChopstick);

                printf("Even philosopher %d picking up left chopstick\n", j);
                sem_wait(&leftChopstick);

                printf("Even philosopher %d Eating\n", j);
                printf("All other philosophers Thinking\n");

                sleep(1);

                sem_post(&rightChopstick);
                sem_post(&leftChopstick);

                printf("Even philosopher %d Done Eating, resources freed up.\n", j);
            }
        }
    }

    sem_destroy(&leftChopstick);
    sem_destroy(&rightChopstick);

    return 0;
}

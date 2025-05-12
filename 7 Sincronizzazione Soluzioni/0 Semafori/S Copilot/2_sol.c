#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define NUM_ELEMENTS 20
#define BLOCK_SIZE (NUM_ELEMENTS/2)

int shared_array[NUM_ELEMENTS];
int current_index = 0;
pthread_mutex_t array_mutex;

void *thread_func(void *arg) {
    // Attesa casuale tra 0 e 2 secondi
    sleep(rand() % 3);
    
    pthread_mutex_lock(&array_mutex);
    printf("Thread %ld acquisisce il lock. current_index=%d\n", (long)pthread_self(), current_index);
    
    // Aggiorna BLOCK_SIZE elementi, se disponibili
    int count = 0;
    while (count < BLOCK_SIZE && current_index < NUM_ELEMENTS) {
        shared_array[current_index] = getpid();  // inserisce il PID del processo
        current_index++;
        count++;
    }
    printf("Thread %ld ha aggiornato %d elementi.\n", (long)pthread_self(), count);
    
    pthread_mutex_unlock(&array_mutex);
    pthread_exit(NULL);
}

int main(void) {
    pthread_t tid1, tid2;
    srand(time(NULL));  // inizializza il seme per i numeri casuali

    pthread_mutex_init(&array_mutex, NULL);
    
    if (pthread_create(&tid1, NULL, thread_func, NULL) != 0) {
        perror("Errore nella creazione del thread 1");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&tid2, NULL, thread_func, NULL) != 0) {
        perror("Errore nella creazione del thread 2");
        exit(EXIT_FAILURE);
    }
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // Stampa il contenuto dell'array condiviso
    printf("Contenuto dell'array condiviso:\n");
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        printf("%d ", shared_array[i]);
    }
    printf("\n");
    
    pthread_mutex_destroy(&array_mutex);
    return 0;
}
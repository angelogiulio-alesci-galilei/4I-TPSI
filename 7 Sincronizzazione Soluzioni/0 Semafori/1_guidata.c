#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define TANTI 10

pthread_mutex_t mutex;                  // semaforo condiviso tra i thread
int buffer = 0;                         // variabile condivisa

void *cod_thread1(void *arg) {
    int accessi1 = 0;                   // num. di accessi del thread 1 alla sez critica
    while (buffer < TANTI) {            // fino a TANTI
        pthread_mutex_lock(&mutex);     // accesso sez. critica
        accessi1++;
        buffer++;
        printf("Accessi di T1: %d Valore buffer: %d\n", accessi1, buffer);
        pthread_mutex_unlock(&mutex);                   // rilascio sez. critica
        sleep((int)(5.0 * rand()/(RAND_MAX + 1.0)));    // riposo casuale
    }
    pthread_exit(0);
}

void *cod_thread2(void *arg) {
    int accessi2 = 0;                   // num. di accessi del thread 2 alla sez critica
    while (buffer < TANTI) {            // fino a TANTI
        pthread_mutex_lock(&mutex);     // accesso sez. critica
        accessi2++;
        buffer++;
        printf("Accessi di T2: %d Valore buffer: %d\n", accessi2, buffer);
        pthread_mutex_unlock(&mutex);                   // rilascio sez. critica
        sleep((int)(5.0 * rand()/(RAND_MAX + 1.0)));    // riposo casuale
    }
    pthread_exit(0);
}

int main () {
    pthread_t tid1, tid2;
    pthread_mutex_init(&mutex, NULL);   // semaforo iniz. a verde

    if (pthread_create(&tid1, NULL, cod_thread1, NULL) < 0) {
        fprintf(stderr, "errore nella creazione del thread 1\n");
        exit(1);
    }
    
    if (pthread_create(&tid2, NULL, cod_thread2, NULL) < 0) {
        fprintf(stderr, "errore nella creazione del thread 2\n");
        exit(1);
    }

    pthread_join (tid1, NULL);
    pthread_join (tid2, NULL);
}
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TANTI1 30
#define TANTI2 20

int condivisa = 0;                      // variabile globale condivisa da main e thread
pthread_mutex_t mutex;                  // definizione semaforo

void *cod_thread(void *arg) {           // funzione che viene eseguita dal thread
    int i, dato;
    for (i = 0; i < TANTI1; i++) {
        pthread_mutex_lock(&mutex);     // entra nella sez. critica
        dato = condivisa;               // aggiorna la variabile condivisa
        dato++;                         // copiandola prima in var. locale
        condivisa = dato;               // solo per rallentare l'esecuzione
        printf(",");
        fflush(stdout);
        pthread_mutex_unlock(&mutex);   // esce dalla sez. critica
    }
}

int main (void) {
    pthread_t tid1;
    int x, err;
    pthread_mutex_init(&mutex, NULL);   // semaforo inizi. a verde

    if ((err = pthread_create(&tid1, NULL, cod_thread, NULL)) != 0) {
        printf("Errore nella creazione thread: %s\n", strerror(err));
        exit(1);
    }

    for (x = 0; x < TANTI2; x++) {
        pthread_mutex_lock(&mutex);       // entra nella sez. critica
        condivisa++;                      // aggiorna direttamente condivisa
        printf("o");
        fflush(stdout);
        pthread_mutex_unlock(&mutex);     // esce dalla sez. critica
    }

    if (pthread_join (tid1, NULL)) {      // attende la terminazione del thread
        printf("errore: %s\n", strerror(err));
        exit(1);
    }

    printf("\nVariabile condivisa uguale a: %d\n", condivisa);
    exit(0);
}
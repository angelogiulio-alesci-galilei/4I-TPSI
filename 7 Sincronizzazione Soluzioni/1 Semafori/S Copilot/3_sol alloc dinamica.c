/*
    Prompt: A partire dalla (mia) soluzione, realizza come meccanismo di gestione
    della concorrenza quello della "mutua esclusione per struttura",
    dove la struttura mutex va allocata dinamicamente.

    La soluzione generata usa:
    - variabile mutex puntatore a pthread_mutex_t nella struct struttura (globale)
    - variabile test puntatore a struttura (globale)
    - la notazione freccia -> invece che . per accedere ad elementi di una struttura
      (come già visto nei puntatori a oggetto in C++)
    - malloc di test e mutex, con relativi free finali
    - destroy del mutex

    Non credo fosse questo il livello di difficoltà atteso, quindi ho rimosso l'esercizio
    nelle dispense
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct struttura {
    int a;
    int b;
    pthread_mutex_t *mutex;
};

struct struttura *test;

void *somma1(void *arg) {
    while (test->a < 20 || test->b < 20) {
        pthread_mutex_lock(test->mutex);
        if (test->a < 20)
            test->a++;
        if (test->b < 20)
            test->b++;
        printf("somma1: %d, %d\n", test->a, test->b);
        pthread_mutex_unlock(test->mutex);
        sleep(rand() % 2);
    }
    pthread_exit(0);
}

void *somma2(void *arg) {
    while (test->a < 20 || test->b < 20) {
        pthread_mutex_lock(test->mutex);
        if (test->a < 20)
            test->a++;
        if (test->b < 20)
            test->b++;
        printf("somma2: %d, %d\n", test->a, test->b);
        pthread_mutex_unlock(test->mutex);
        sleep(rand() % 2);
    }
    pthread_exit(0);
}

int main() {
    // Allocazione dinamica della struttura
    test = malloc(sizeof(struct struttura));
    if (!test) {
        fprintf(stderr, "Errore di allocazione della struttura\n");
        exit(1);
    }
    test->a = 0;
    test->b = 0;
    
    // Allocazione dinamica del mutex
    test->mutex = malloc(sizeof(pthread_mutex_t));
    if (!test->mutex) {
        fprintf(stderr, "Errore di allocazione del mutex\n");
        exit(1);
    }
    pthread_mutex_init(test->mutex, NULL);
    
    pthread_t tid1, tid2;
    
    if (pthread_create(&tid1, NULL, somma1, NULL) < 0) {
        fprintf(stderr, "Errore nella creazione del thread 1\n");
        return 1;
    }
    if (pthread_create(&tid2, NULL, somma2, NULL) < 0) {
        fprintf(stderr, "Errore nella creazione del thread 2\n");
        return 1;
    }
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("%d, %d\n", test->a, test->b);
    
    pthread_mutex_destroy(test->mutex);
    free(test->mutex);
    free(test);
    
    return 0;
}
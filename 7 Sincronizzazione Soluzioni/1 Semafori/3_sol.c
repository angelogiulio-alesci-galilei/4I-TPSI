#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t semaforo;

struct struttura {
    int a;
    int b;
};

struct struttura test = {0, 0}; // inizializzo a 0 i valori di a e b

void *somma1(void *arg) {
    while (test.a < 20 || test.b < 20) {
        pthread_mutex_lock(&semaforo);
        if (test.a < 20)
            test.a++;
        if (test.b < 20)
            test.b++;
        printf ("somma1: %d, %d\n", test.a, test.b);
        pthread_mutex_unlock(&semaforo);
        sleep(rand()%2);
    }

    pthread_exit(0);
}

void *somma2(void *arg) {
    while (test.a < 20 || test.b < 20) {
        pthread_mutex_lock(&semaforo);
        if (test.a < 20)
            test.a++;
        if (test.b < 20)
            test.b++;
        printf ("somma2: %d, %d\n", test.a, test.b);
        pthread_mutex_unlock(&semaforo);
        sleep(rand()%2);
    }

    pthread_exit(0);
}

int main () {
    pthread_mutex_init (&semaforo, NULL);
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, somma1, NULL) < 0) {
        fprintf(stderr, "errore nella creazione del thread 1\n");
        return 1;
    }
    if (pthread_create(&tid2, NULL, somma2, NULL) < 0) {
        fprintf(stderr, "errore nella creazione del thread 2\n");
        return 1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf ("%d, %d\n", test.a, test.b);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#define DIM 10

pthread_mutex_t semaforo;
int arr[DIM];
int i = 0;

void *thread1(void *arg);
void *thread2(void *arg);

int main () {
    pthread_mutex_init(&semaforo, NULL);
    pthread_t tid1, tid2;

    if (pthread_create(&tid1, NULL, thread1, NULL) != 0) {
        perror("Errore nella creazione del thread 1\n");
        return 1;
    }

    if (pthread_create(&tid2, NULL, thread2, NULL) != 0) {
        perror("Errore nella creazione del thread 2\n");
        return 1;
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("array: ");
    for (i=0; i<DIM-1; i++)
        printf("%d, ", arr[i]);
    printf("%d.\n", arr[i]);

    return 0;
}

void *thread1(void *arg) {
    srand(time(NULL));
    int conta = 0;
    while (i<DIM && conta<DIM/2) {
        pthread_mutex_lock(&semaforo);
        arr[i]=1;
        i++;
        conta++;
        pthread_mutex_unlock(&semaforo);
        sleep(rand()%2);
    }
    pthread_exit(0);
}

void *thread2(void *arg) {
    srand(time(NULL));
    int conta = 0;
    while (i<DIM && conta<DIM/2) {
        pthread_mutex_lock(&semaforo);
        arr[i]=2;
        i++;
        conta++;
        pthread_mutex_unlock(&semaforo);
        sleep(rand()%2);
    }
    pthread_exit(0);
}
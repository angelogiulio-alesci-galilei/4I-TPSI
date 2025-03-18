#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NRFIGLI 3

int main () {
    int status, pid, x;
    for (x = 0; x < NRFIGLI; x++) {
        pid = fork();                   // creazione del figlio
        if (pid == 0) {                 // nel figlio pid e' uguale a 0
            printf("F> Sono il figlio, il mio pid e': %d. ", getpid());
            printf("Il mio papi ha pid: %d.\n", getppid());
            exit(1);
        }
        else {                          // nel padre ha valore <> 0
            printf("P> Sono il padre, il mio pid e': %d. ", getpid());
            printf("Il pid del figlio corrente e': %d.\n", pid);
            printf("P> Mi metto in attesa che mio figlio (%d) termini ...\n", wait(&status));
            printf("... (%d) ha finito.\n", pid);
        }
    }
    return 0;
}
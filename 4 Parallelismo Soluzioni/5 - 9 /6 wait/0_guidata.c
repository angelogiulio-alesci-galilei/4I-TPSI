#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
    int status;
    int pid = fork();           // creazione del figlio
    if (pid == 0) {             // e' il figlio
        printf("F> Sono il figlio, il mio pid e': %d; ",getpid());
        printf("il mio papi ha pid: %d\n",getppid());
        printf("F> Ho finito il lavoro!\n");
        exit(0);
    }
    else {                      // e' il padre
        printf("P> Sono il padre, il mio pid e': %d; ",getpid());
        printf("resto in attesa di mio figlio (%d) ...\n",wait(&status));
        printf("P> ... mio figlio ha terminato l'elaborazione!\n");
        return 0;
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid == 0) {
        // Processo figlio: invia a sé stesso SIGUSR1 per terminare in modo forzato.
        raise(SIGUSR1);
        // Non dovrebbe raggiungere questo punto.
        exit(0);
    } else {
        int status;
        wait(&status);

        if (WIFSIGNALED(status)) {
            printf("Il figlio è terminato a causa del segnale: %d\n", WTERMSIG(status));
        } else {
            printf("Il figlio non è stato terminato da un segnale.\n");
        }
    }
    
    return 0;
}
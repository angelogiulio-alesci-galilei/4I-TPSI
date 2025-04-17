#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define NRFIGLI 4
#define VOLTE 3

int main () {
    int pid, status, i, j;
    char c;
    for (i=0; i<NRFIGLI; i++) {
        pid = fork();
        if (pid == 0) { // processo figlio
            c = 'a' + i;
            for (j=0; j<VOLTE; j++) {
                printf("%c", c);
                fflush(0); // In questo modo possiamo vedere il risultato lettera per lettera
                sleep(1); // Rallentiamo in modo da vedere lettera per lettera
            }
            printf(" \n");
            exit(0);
        }
        else // processo padre
            pid = wait(&status); // controllo dello stato del figlio
        if (WIFEXITED(status))
            printf("Terminazione volontaria di %d con stato %d\n", pid, WEXITSTATUS(status));
        else
            if(WIFSIGNALED(status))
                printf("Terminazione involontaria di %d per segnale %d\n", pid, WTERMSIG(status));
    }
}
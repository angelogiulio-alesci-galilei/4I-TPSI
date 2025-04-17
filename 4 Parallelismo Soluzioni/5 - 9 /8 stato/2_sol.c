#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
    int pid, status;
    pid = fork();
    if (pid == 0) { // processo figlio
        printf("Eseguito dal figlio\n");
        exit(0);
    }
    else {  // processo padre
        pid = wait(&status); // controllo dello stato del processo figlio
        if (WIFEXITED(status))
            printf("Terminazione volontaria di %d con stato %d\n", pid, WEXITSTATUS(status));
        else
            if (WIFSIGNALED(status))
                printf("Terminazione involontaria di %d per segnale %d\n", pid, WTERMSIG(status));
   }
}
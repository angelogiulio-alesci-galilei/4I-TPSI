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
    if (pid == 0) {             // ramo eseguito dal solo processo figlio
        printf("Codice del figlio\n");
        exit(0);
    }
    else {                      // ramo eseguito dal solo processo padre
        pid = wait(&status);    // attesa terminazione
        printf("Terminato processo figlio n.%d\n", pid);
        if ((char)status == 0)  // controllo terminazione figlio
            printf("Terminazione volontaria con stato %d\n",status);
        else
            printf("Terminazione errata con segnale %d\n", (char)status);
        return 0;
    }
}
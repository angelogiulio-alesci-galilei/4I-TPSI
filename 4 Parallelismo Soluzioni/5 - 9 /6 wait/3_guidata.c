#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main () {
    int pid, pid1, pid2, status, x;
    srand(time(NULL));
    pid1 = fork();
    if (pid1 == 0) {                // primo processo figlio
        x = (rand() % 4) + 1;
        printf("1) Sono il primo processo figlio con pid: %d sleep: %d\n", getpid(), x);
        sleep(x);
        exit(1);                    // termina primo processo figlio
    }
    else {
        pid2 = fork();
        if (pid2 == 0) {            // secondo processo figlio
            x = (rand() % 2) + 1;
            printf("2) Sono il secondo processo figlio con pid: %d sleep: %d\n", getpid(), x);
            sleep(x);
            exit(2);                // termina secondo processo figlio
        }
        else {
            printf("3) Padre in attesa del primo figlio che termina\n");
            pid = wait(&status);    // attesa terminazione
            printf("4) Per primo termina il figlio con pid: %d\n", pid);
            return 0;
        }
    }
}
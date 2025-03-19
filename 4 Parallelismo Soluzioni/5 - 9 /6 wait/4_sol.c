#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define NRFIGLI 4
 
int main() {
	int i, pid, tempo, status;
	
	for (i = 0; i < NRFIGLI; i++)  { 
    	pid = fork();				// creazione del figlio 
		if (pid == 0) {				// nel figlio pid e' uguale a 0
			srand(time(NULL) ^ getpid());
			tempo = rand()%4+1;		// numero causale tra 1 e 4
			printf("Sono il %d figlio, il mio pid e': %d, dormiro' per %d... ", i+1, getpid(), tempo);
			sleep(tempo); 
			printf("Il mio papi ha pid: %d.\n", getppid());
			exit(0);
		}
		else {						// nel padre ha valore <> 0 
			printf("Sono il padre di %d, il mio pid e': %d. ", i+1, getpid());
			printf("Il pid del figlio corrente e': %d.\n", pid);
			printf("Rimango in attesa del figlio (%d).\n", wait(&status));
		}
	}
	return 0;
}

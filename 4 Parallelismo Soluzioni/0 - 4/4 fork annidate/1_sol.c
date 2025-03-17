#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void mettiSpazi(int quanti) {				//per meglio vedere la gerarchia
	int i;
	for (i=0;i<quanti;i++)
		printf("  ");
}

void faiFiglio(int nFigli, int quanti) {
	int pid;
	pid = fork();							//creo processo figlio
	if (pid==0) {
		mettiSpazi(nFigli-quanti);
		printf("Sono il processo figlio con pid: %d. ",getpid());
		printf("Il mio papi ha pid: %d.\n",getppid());
		if (quanti>0)
			faiFiglio(nFigli, quanti-1);	//il figlio diventa il padre
		else
			exit(0);
	}
	else {
		mettiSpazi(nFigli-quanti);
		printf("Sono il processo padre con pid: %d.\n",getpid());
		sleep(1);
	}
}

int main () {
	int x;
	printf("Inserisci il numero di livelli di gerarchia:\n");
	scanf("%d",&x);
	x--;
	faiFiglio(x,x);
	return 0;
}

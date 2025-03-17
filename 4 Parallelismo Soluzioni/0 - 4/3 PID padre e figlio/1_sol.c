#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void faiFiglio();

int main () {
	int i,x;
	printf("Inserisci il numero di processi figli che vuoi creare:\n");
	scanf("%d",&x);
	for (i=0;i<x;i++) {
		faiFiglio();
	}
	printf("\n Padre. Il mio pid e': %d; Il mio ppid e': %d.\n",getpid(),getppid());
	return 0;
}

void faiFiglio() {
	int pid;
	pid=fork();
	if (pid==0) {
		printf("\n Figlio. Il mio pid e': %d; Il mio ppid e': %d.\n",getpid(),getppid());
		exit(0);
	}	
}

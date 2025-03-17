#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
	/* PRIMA DELLA FORK */
	int pid;
	printf(" 1) Prima della fork \n");
	
	/* FORK */
	pid = fork();	//creo il processo figlio
	printf(" 2) Dopo della fork \n");
	if (pid==0) {
		sleep(3);	//ritardo di 3 secondi
		printf(" 3f) Sono il processo figlio, il mio pid e': %d\n",getpid());
		printf(" 4f) Il mio papi ha pid: %d\n",getppid());
		exit(1);	//termina il processo figlio
	}
	else {
		printf(" 3p) Sono il processo padre, il mio pid e': %d\n",getpid());
		printf(" 4p) Il mio papi ha pid: %d\n",getppid());
		exit(0);	//non necessario
	}
}

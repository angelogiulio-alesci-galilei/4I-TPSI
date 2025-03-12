#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
	int pid;
	printf(" 1) Prima della fork \n");
	pid = fork();	//creo il processo figlio
	printf(" 2) Dopo della fork \n");
	if (pid==0) {
		printf(" 3) Sono il processo figlio \n");
		exit(1);	//termina il processo figlio
	}
	else {
		printf(" 3) Sono il processo padre \n");
		exit(0);	//termina il padre
	}
}

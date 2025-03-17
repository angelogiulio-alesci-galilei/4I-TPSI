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
	int x = 10;
	printf(" La variabile x prima della fork vale: %d \n",x);
	
	/* FORK */
	pid = fork();	//creo il processo figlio
	printf(" 2) Dopo della fork \n");
	if (pid==0) {
		printf(" 3) Sono il processo figlio, il mio pid e': %d \n",getpid());
		printf(" Il process group e': %d",getpgid(0));
		x = 20;
		printf(" La variabile x nel processo figlio vale: %d \n",x);
		exit(1);	//termina il processo figlio
	}
	else {
		printf(" 3) Sono il processo padre, il mio pid e': %d \n",getpid());
		printf(" Il process group e': %d",getpgid(0));
		x = 30;
		printf(" La variabile x nel processo padre vale: %d \n",x);
		exit(0);	//termina il padre
	}
}

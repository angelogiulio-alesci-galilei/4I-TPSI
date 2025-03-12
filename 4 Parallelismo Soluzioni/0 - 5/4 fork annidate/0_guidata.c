#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
	int pid1, pid2, pid3;
	pid1=fork();								//crea processo figlio
	pid2=fork();								//crea processo figlio
	pid3=fork();								//crea processo figlio
	if ((pid1==0) || (pid2==0) || (pid3==0)) {	//se uno è 0 è un figlio
		printf("Sono il processo figlio con pid:%d.\n",getpid());
		printf("Il mio papi ha pid:%d.\n",getppid());
		sleep(1);								//attesa per non creare orfani
		exit(1);								//termina il processo figlio		
	}
	else {
		printf("Sono il processo padre con pid:%d.\n",getpid());
		sleep(2);								//attesa per far elaborare i figli
	}
	return 0;
}

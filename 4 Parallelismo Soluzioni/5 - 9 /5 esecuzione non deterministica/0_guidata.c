#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
	int pid1, pid2;
	pid1 = fork();
	if (pid1==0) {
		printf("1. Sono il 1o figlio PID: %d\n",getpid());
		exit(1);
	}
	else {
		printf("2. Sono il processo padre\n");
		printf("2. Ho creato un processo PID: %d\n",pid1);
		printf("2. Il mio PID invece e': %d\n",getpid());
		pid2 = fork();
		if (pid2==0) {		//Secondo processo figlio
			printf("3. Sono il 2o figlio, PID: %d\n",getpid());
			exit(2);
		}
		else {
			printf("4. Sono il processo padre\n");
			printf("5. Ho creato il 2o figlio PID: %d\n",pid2);
		}
	}
}

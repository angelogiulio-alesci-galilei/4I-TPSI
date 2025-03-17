#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//	Le parti commentate non si possono fare perche' i case dello switch devono essere costanti, non possono essere variabili

int main () {
	int pid;
	//int pidMain, pid1, pid2;
	pid = fork();
	if (pid==0)
		pid = 1;
		//pid = pid1 = getpid();
	else {
		pid = fork();
		if (pid==0)
			pid = 2;
			//pid = pid2 = getpid();
		else
			pid = 0;
			//pid = pidMain = getpid();
	}

	switch (pid) {
		case 0:		//case pidMain:
			printf("Processo padre con PID: %d\n",pid);
			break;
		case 1:		//case pid1:
			printf("Processo 1o con PID: %d\n",pid);
			exit(1);
			break;
		case 2:		//case pid2:
			printf("Processo 2o con PID: %d\n",pid);
			exit(2);
			break;
	}
}

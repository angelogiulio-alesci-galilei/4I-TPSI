#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	printf("1 Sono il padre  .. \n");
  
	int pid;
	pid = fork();
  
	switch(pid){
	  	case -1:
			printf("Errore in creazione figlio\n");
	      	return(-1);
	    case  0:					// figlio 
	    	printf("2 Figlio si riposa  .. \n");
	    	sleep(2);
	    	printf("3 Figlio termina\n");
	    	exit(0);				// termina il processo figlio                      
	    default:
			printf("4 Padre aspetta che termini il figlio...\n");
			sleep(3);
			printf("5 Padre termina \n");
			exit(1);				// termina il processo padre  
	}
}



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
void main(){ 
  int pid, pid1, pid2;
  pid1 = fork();
  if(pid1 == 0){      // processo figlio  
    printf("1.sono il I figlio PID: %i\n", getpid());
    exit(1);         // termina primo processo figlio
  }
  else{
    printf("2.sono il processo padre\n");
    printf("2.ho creato un processo PID: %i\n", pid1);
    printf("2.il mio PID e' invece: %i\n", getpid());
    pid2 = fork();
    if (pid2 == 0){   // secondo processo figlio
      printf("3.sono il II figlio PID: %i\n", getpid());
      exit(2);       // termina secondo processo figlio 
    }
 	  else{
      printf("4.sono il processo padre\n");
      printf("5.ho creato il II figlio PID: %i\n", pid2);
    }
  }
}




/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2016 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/


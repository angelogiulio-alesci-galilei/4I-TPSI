#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
void main(){ 
  int pid, pid1, pid2, pid3, pid4, pid5;
  pid1 = fork();           // main crea secondo figlio pid1
  if(pid1 == 0){           // processo figlio  
    printf("0) primo processo figlio con pid: %i. Mio padre e' : %i \n", getpid(), getppid() );
    pid3 = fork();  
    if(pid3 == 0){         // processo figlio  
      printf("1) primo processo nipote con pid: %i. Mio padre e': %i \n", getpid(), getppid() );
      exit(1);             // termina processo nipote 
    }
    else{
      printf("2) processo padre %i \n", getpid()); 
      exit(1);             // termina primo processo figlio
    }
  }
  else{                    // main 
    printf("3) processo padre %i \n", getpid()); 
    printf("4) ho creato un processo con pid: %i\n", pid1);
    pid2 = fork();         // main crea secondo figlio pid2 
    if (pid2 == 0){        // secondo processo figlio
      printf("5) secondo processo figlio con pid: %i .Mio padre e' : %i \n", getpid(), getppid() );
      pid4 = fork();      
      if(pid4 == 0){       // processo figlio  
        printf("6) secondo processo nipote con pid: %i. Mio padre e' : %i \n", getpid(), getppid() );
        exit(1);           // termina processo nipote 
      }
      else{
        printf("7) processo padre %i \n", getpid()); 
        exit(1);           // termina primo processo figlio
      }
    }
 	else {                 // main 
      printf("8) processo padre %i \n", getpid()); 
      printf("9) ho creato un secondo processo con pid: %i\n", pid2);
      sleep (2);
    }
  }
}



/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/





#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
int main(){ 
  int pid;
  int uguale, diversa;
  uguale  = 10;
  diversa = 10;
  printf( "1) prima della fork \n" );
  pid = fork();                            // creo processo figlio 
  printf( " 2) dopo della fork \n" );
  if (pid == 0){
    diversa = 20;
    printf( " 3) sono il processo figlio con pid: %d\n", getpid() );
    printf( " 4) appartengo al gruppo %d\n", getppid() );
    printf( " 5) la mia variabile uguale contiene : %d\n", uguale);
    printf( " 6) sono il processo diversa contiene: %d\n", diversa);
    exit(1) ;                              // termina il processo figlio 
  }
  else{
    diversa = 30;
    printf( " 3) sono il processo padre pid: %d\n", getpid()) ;
    printf( " 4) appartengo al gruppo %d\n", getppid() );
    printf( " 5) la mia variabile uguale contiene : %d\n", uguale);
    printf( " 6) sono il processo diversa contiene: %d\n", diversa);
    exit(0) ;                              // non necessaria
  }
}



/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/


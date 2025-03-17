#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(){ 
  int pid;
  printf("1) prima della fork \n");
  pid = fork();            // creo processo figlio 
  printf(" 2) dopo della fork \n");
  if (pid == 0){
    printf(" 3) sono il figlio con pid: %d", getpid());
    printf("\n    Il mio papi ha pid: %d\n", getppid());
    exit(1);               // termina il processo figlio 
  }
  else{
    printf(" 3) sono il padre con pid: %d", getpid());
    printf("\n    Il mio papi ha pid: %d\n", getppid());
    exit(0);               // non necessaria
  }
}

/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/


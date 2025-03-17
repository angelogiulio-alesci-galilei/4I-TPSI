#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 

int main(int argc, char *argv[]) {
  int pid,retv;
  printf("1 Sono il padre  .. \n");
  pid = fork();
  switch(pid){
    case -1: printf("Errore in creazione figlio\n");
      return(-1);
    case 0 :                 // figlio 
      printf("2 Figlio si riposa  .. \n");
      sleep(2);
      printf("3 Figlio termina\n");
      exit(69);              // termina il processo figlio                      
    default: 
      printf("4 Padre aspetta che termina il figlio...\n");
      sleep(3);
      printf("5 Padre termina \n");
      exit(1);               // termina il processo padre  
  }
}


/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
// #define NRFIGLI 4

void faiFiglio(){
  pid_t pid;
  pid = fork();         // creo processo figlio 
  if (pid == 0){
    printf(" Sono il figlio con pid: %d", getpid());
    printf(" Il mio papi ha pid: %d\n", getppid());
    exit(1);            // NB prova a togliere questa istruzione! 
  }
  else{
    printf("Sono il padre con pid: %d\n", getpid());
  }
}

int main(){ 
  int x, NRFIGLI;
  printf(" Quanti fratelli devo generare ? ");
  scanf ("%d", &NRFIGLI);
  for (x= 0; x < NRFIGLI; x++)   
    faiFiglio(); 
  return 0;
}

/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/


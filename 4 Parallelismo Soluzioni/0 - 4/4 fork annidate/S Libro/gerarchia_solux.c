#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
int NRFIGLI;

void mettiSpazi(int quanti){   // per meglio vedere la gerarchia 
  int x;
  for (x = 0; x <= quanti; x++)
    printf(" ");
}

void faiFiglio (int quanti){
  int pid;
  pid = fork();                    // creo processo figlio 
  if (pid == 0){
    mettiSpazi(NRFIGLI-quanti);
    printf( "Sono il processo figlio con pid: %d", getpid() );
    printf( "Il mio papi ha pid: %d\n", getppid());
    if (quanti > 0)
      faiFiglio(quanti-1);         // il figlio diventa il padre  
    else
      exit(0);
  }
  else{
    mettiSpazi(NRFIGLI-quanti);
    printf( "Sono il processo padre con pid: %d\n", getpid() );
    sleep(1);  // altrimenti termina prima il padre dei processi figli 
  }
}
int main(){ 
  printf( " Quanti processi fratelli devo generare ? ");
  scanf ("%d", &NRFIGLI);
  faiFiglio(NRFIGLI);
  printf( " Termine elaborazione processo con pid: %d\n", getpid() ); 
  sleep(1);  // altrimenti termina prima delle alttre visualizzazioni  
  return 0;
} 

/*********************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2        *
* Copyright (C) 2012-2024 by Hoepli Editore                          * 
* collaudo in: gcc - linux                                           *
**********************************************************************/


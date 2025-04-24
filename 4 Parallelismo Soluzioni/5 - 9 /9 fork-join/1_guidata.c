#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void ramo34();

int main( ){ 
  int status;
  pid_t pid_figlio;
  printf("S1 (padre1) - pid = %d\n", getpid());
  printf("  fork esterna - \n");
  if ((pid_figlio = fork()) == -1)               // prima fork 
    printf("fork non riuscita !");          
  else
    if (pid_figlio == 0){
      printf("    figlio1: pid = %d, padre pid = %d\n", getpid(), getppid());
      ramo34();           // esecuzione fork processi 3 e 4  (P34)
    }
    else{                 // esecuzione ramo padre 
      printf("  S2 (padre1) - pid = %d\n", getpid());
      printf("  wait fine ramo P34 (padre1 join figlio1) \n");
      waitpid(pid_figlio, &status, 0);           // attesa prima fork  
      printf("  fine attesa P34 \n");
      printf("S5 (padre1) - pid = %d\n", getpid());
      exit( 0 );
   } 
}

void ramo34(){
  int status;
  pid_t pid4;
  printf("    fork - processi P34 -> creazione P4  \n");
  if ((pid4 = fork()) == -1)                     // seconda fork 
    printf("        fork non riuscita !");
  if (pid4 == 0){
    printf("        S4 (figlio2)- pid = %d, padre pid = %d\n", getpid(), getppid());
  }
  else{
    printf("      S3 (padre2) - pid = %d, padre pid = %d\n", getpid(), getppid());
    printf("      wait fine figlio P4 (padre2 join figlio2)  \n");
    waitpid(pid4, &status, 0);                  // attesa fork interna   
    printf("      fine attesa P4 \n");
    printf("    fine ramo P34 \n");
    printf("    figlio1: pid = %d, padre pid = %d\n", getpid(), getppid());
   
  }
  exit(0);
}
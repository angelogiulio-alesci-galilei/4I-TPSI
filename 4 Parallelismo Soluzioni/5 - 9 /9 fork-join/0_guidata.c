#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int calcoli_padre1() {
  int k;
  printf("1 elab. // padre \n");
  k = 3 + 2;
  return k; 
} 

int calcoli_padre2(int a, int b) {
  int k;
  printf("2 elab. finale padre \n");
  k = (a + b);
  return k; 
} 

int calcoli_figlio1() {
  int k;
  printf("1.1 elab. // figlio \n");
  k = 6 - 2;
  return k; 
} 
  
int main( ) { 
  int x, y, z, retv;
  pid_t pid;
  
  pid = fork();                              // inizio elaborazione parallela 
  if (pid == 0) {    
    x = calcoli_figlio1();                   // esecuzione parallela calcoli figlio
    exit(x);                                 // termina processo figlio 
  }
  else
    y = calcoli_padre1();                    // esecuzione parallela calcoli padre

  printf(".. join: padre aspetta \n");
  wait(&retv);                               // join : il padre aspetta il figlio 
  x = WEXITSTATUS(retv);                     // prende il risultato del figlio
  z = calcoli_padre2(x, y);                  // esegue gli ultimi calcoli

  printf("-> risultato finale z = %d \n", z);
}
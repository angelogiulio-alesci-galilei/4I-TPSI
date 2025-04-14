#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int f1, f2, g, h, padre;
  padre = getpid();
  f1 = 0;
  f2 = 0;
  g = 0;
  h = 0;
  
  printf("1) processo padre con pid: %i \n", getpid());
  
  f1 = fork();
  if (getpid() != padre)
    printf("2) _ dopo prima fork processo con pid: %i \n", getpid());
  
  if (f1 != 0) {
    f2 = fork();
    if (getpid() != padre)
      printf("3) _ dopo seconda fork processo figlio con pid: %i \n", getpid());
  } 
  if (f1 == 0 || f2 == 0) {      // processo F1 oppure F2
    g = fork();
    printf("4) __ dopo terza fork processo figlio con pid: %i \n", getpid());
    if (g != 0) {
      h = fork();
      printf("5) __ dopo quarta fork processo figlio con pid: %i \n", getpid());
    } 
	if (g != 0 && h != 0) { // processo F1 oppure F2
      waitpid(g, 0, 0);
      waitpid(h, 0, 0);
    }
  } 
  else { // processo P
    waitpid(f2,0,0);
    printf("6) ha terminato F2: %i \n", f2 );
    waitpid(f1,0,0);
    printf("7) ha terminato F1: %i \n", f1 );
  }  
 return 0;
}
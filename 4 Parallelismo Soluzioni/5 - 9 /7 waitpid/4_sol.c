#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int padre, f1, f2, g, h;
  padre = getpid();
  f1 = f2 = g = h = 0;
  
  printf("1) processo P con pid: %i \n", padre);
  
  f1 = fork();
  if (getpid() != padre)    // if (f1 == 0)
    printf("2) _ processo F1 con pid: %i \n", getpid());
  
  if (f1 != 0) {            // else
    f2 = fork();
    if (getpid() != padre)  // if (f2 == 0)
      printf("3) _ processo F2 con pid: %i \n", getpid());
  }

  if (f1 == 0 || f2 == 0) { // processo F1 oppure F2
    g = fork();
    if (g == 0)
      printf("4) __ processo G con pid: %i \n", getpid());
    
    if (g != 0) {           // processo F1 oppure F2, non G
      h = fork();
      if (h == 0)
        printf("5) __ processo H con pid: %i \n", getpid());
    }
     
	if (g != 0 && h != 0) {   // processo F1 oppure F2, non G, non H
      waitpid(g, 0, 0);     // attende G prima di H
      printf("6) ha terminato G: %i \n", g );
      waitpid(h, 0, 0);
      printf("7) ha terminato H: %i \n", h );
    }
  }
  
  else {                    // processo non F1 e non F2 (processo P)
    waitpid(f2,0,0);        // attende F2 prima di F1
    printf("8) ha terminato F2: %i \n", f2 );
    waitpid(f1,0,0);        // attende F1
    printf("9) ha terminato F1: %i \n", f1 );
  }  
 return 0;
}
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int scriviLeggi (char *f1);

int main () {
  int ok; 
  char nomefile[80];
  printf("digita il nome del file da creare: ");
  scanf("%s", nomefile);
  ok = scriviLeggi(nomefile);
  exit (ok);
}

int scriviLeggi (char *f1) {
  int status, pid;
  FILE *fp;
  char parola[80];

  // creo processo figlio  
  if ((pid = fork()) < 0) {
    perror("fork");
    exit(1);
  }
  
  if (pid == 0) {                 // codice eseguito dal FIGLIO 
    printf("Digita la stringa che il figlio leggera' e scrivera' nel file: "); 
    scanf("%s", parola);
    
    if ((fp = fopen(f1, "w")) < 0) {
      perror("open"); 
      exit(1); 
    }

    fprintf(fp, "%s", parola);
    fclose(fp);
    exit(0);     
  }
  
  else {                          // codice eseguito dal PADRE 
    waitpid(-1, &status, 0);
    
    if ((fp = fopen(f1, "r")) < 0) {
      perror("open");
      exit(1);
    }

    fscanf(fp, "%s", parola);
    printf("Il padre ha letto la stringa: %s\n", parola); 
    
    fclose(fp); 
    return (0);
  }
}
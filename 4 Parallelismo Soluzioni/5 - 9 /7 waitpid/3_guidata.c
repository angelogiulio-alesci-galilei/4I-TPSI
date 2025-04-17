#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
  int status, pid, i;
  FILE *fp;
  char parola[80];

  for (i = 0; i < 3; i++) { // ciclo per creare 3 figli
    if ((pid = fork()) < 0) {
      perror("fork");
      exit(1); 
    }
    
    if (pid == 0) { // codice eseguito dai FIGLI
      printf("Figlio %d: Digita la stringa da scrivere nel file: ", i + 1); 
      scanf("%s", parola);
      
      if ((fp = fopen(f1, (i == 0) ? "w" : "a")) < 0) {
        /* 
          Costrutto ternario per aprire il file in modo diverso
          "w" per il primo figlio, "a" per gli altri
          "w" sta per "write" (scrittura)
          "a" sta per "append" (aggiunta), in modo che non sovrascriva il file
        */
        perror("open"); 
        exit(1); 
      }

      fprintf(fp, "Figlio %d: %s\n", i + 1, parola);
      fclose(fp);
      exit(0);
    } else { // codice eseguito dal PADRE
      if (waitpid(-1, &status, 0) < 0) { // attende la terminazione del figlio corrente
        perror("wait");
        exit(1);
      }
    }
  }
  
  /*
    Il for è terminato e tutti i figli sono terminati
    Codice eseguito dal PADRE per leggere e stampare il contenuto del file
  */
  if ((fp = fopen(f1, "r")) < 0) {
    perror("open");
    exit(1);
  }

  printf("Il padre legge il contenuto del file:\n");
  /*
    Ciclo di lettura del file fino a che non si raggiunge la fine e quindi si ottiene NULL
    fgets legge una riga alla volta e la memorizza in parola
    Il numero massimo di caratteri della riga è dato da sizeof(parola)
    */
  while (fgets(parola, sizeof(parola), fp) != NULL) {
    printf("%s", parola);
  }
    
  fclose(fp); 
  return (0);
}
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int scriviLeggi (char *f1);

int main (int argc, char *argv[]) {
  int ok; 
  char nomefile[80];
  printf("digita il nome del file da creare: ");
  scanf("%s", nomefile);
  ok = scriviLeggi(nomefile);
  exit (ok);
}

int scriviLeggi (char *f1) {
  //file di comunicazione 
  int nread, nwrite = 0, atteso, status, pid;
  FILE *fp;         //fp è un puntatore a file
  char parola[80];

  // creo processo figlio  
  if ((pid = fork()) < 0) {
    perror("fork"); //aggiunge il messaggio personalizzato "fork" alla descrizione dell'errore fatta dal sistema
    exit(1);
  }
  
  // differenziazione codice tra padre e figlio
  if (pid == 0) {                 // codice eseguito dal FIGLIO 
    printf ("Il figlio legge e scrive la stringa nel file : "); 
    scanf ("%s", parola);
    
    //apertura del file in scrittura, con gestione dell'errore
    if ((fp = fopen (f1,"w")) < 0) {
      perror("open"); 
      exit(1); 
    }

    //stampa sul file e chiusura
    fprintf(fp, "%s", parola);
    fclose(fp); 
    exit (0);        
  }
  
  else {                          // codice eseguito dal PADRE 
    atteso = wait (&status);      // attesa terminazione del figlio
    
    //apertura del file in sola lettura, con gestione dell'errore
    if ((fp = fopen (f1,"r")) < 0) {
      perror("open");
      exit(1);
    }

    nread = fscanf (fp, "%s", parola); //leggo dal file
                                       //fscanf restituisce il numero di elementi letti
                                       //ha 3 argomenti: il file, la stringa da leggere e la stringa su cui scrivere
    printf ("Il padre ha letto la stringa: %s\n", parola); 
    
    //chiusura del file
    fclose(fp); 
    return (0);
  }
}
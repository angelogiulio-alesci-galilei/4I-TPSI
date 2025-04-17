#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int scriviLeggi (char *f1);
/*
  Prototipo della funzione scriviLeggi, che accetta un puntatore a char (stringa) e restituisce un intero.
  f1 è il nome del file da creare e scrivere.
  Il valore di ritorno della funzione indica se l'operazione è andata a buon fine (0) o se c'è stato un errore (1).
*/

int main () {
  int ok; 
  char nomefile[80];
  printf("digita il nome del file da creare: ");
  scanf("%s", nomefile);
  ok = scriviLeggi(nomefile);
  exit (ok);
  /* terminazione del processo con risultato in base al valore di ok, quindi della funzione scriviLeggi
     se ok == 0 -> terminazione con successo
     se ok != 0 -> terminazione con errore
  */
}

int scriviLeggi (char *f1) {
  int status, pid;
  FILE *fp;         // dichiariamo fp come un puntatore a file
  char parola[80];

  // creo processo figlio  
  if ((pid = fork()) < 0) {
    perror("fork"); // aggiunge il messaggio personalizzato "fork" alla descrizione dell'eventuale errore fatta dal sistema
    exit(1); // terminazione del processo con errore
  }
  
  if (pid == 0) {                 // codice eseguito dal FIGLIO 
    printf("Digita la stringa che il figlio leggera' e scrivera' nel file: "); 
    scanf("%s", parola);
    
    // apertura del file in scrittura, con gestione dell'errore
    if ((fp = fopen(f1, "w")) < 0) {
      perror("open"); 
      exit(1); 
    }

    fprintf(fp, "%s", parola); // stampa sul file puntato da fp la stringa in parola
    fclose(fp); // chiusura del file
    exit(0);    // il figlio termina con successo     
  }
  
  else {                          // codice eseguito dal PADRE 
    waitpid(-1, &status, 0);      // attesa terminazione del figlio, equivalente a wait()
    
    // apertura del file in sola lettura, con gestione dell'errore
    if ((fp = fopen(f1, "r")) < 0) {
      perror("open");
      exit(1);
    }

    fscanf(fp, "%s", parola);
    printf("Il padre ha letto la stringa: %s\n", parola); 
    
    // chiusura del file e ritorno della funzione come successo
    fclose(fp); 
    return (0);
  }
}
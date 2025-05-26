#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// X -> (3 + x)
// Y -> (5 - y)
// Z -> (7 * z + 3)
// P -> X - Y * Z

int calcoli_X();
int calcoli_Y(int y);
int calcoli_Z(int z);
int calcoli_P(int a, int b, int c);

int main() { 
  int x, y, z;
  int retY, retZ, ris;
  pid_t pid1, pid2;

  printf ("inserisci valore per la variabile y: ");
  scanf ("%d", &y);
  printf ("inserisci valore per la variabile z: ");
  scanf ("%d", &z);

  pid1 = fork();                        // inizio elaborazione parallela 
  if (pid1 == 0) {    
    y = calcoli_Y(y);                   // esecuzione parallela calcoli figlio
    exit(y);                            // termina processo figlio 
  }
  else{
    pid2 = fork();                      // inizio elaborazione parallela 
    if (pid2 == 0){    
      z = calcoli_Z(z);                 // esecuzione parallela calcoli figlio
      exit(z);                          // termina processo figlio 
    }
    else {                       // esecuzione parallela calcoli padre
      sleep(2);                  // attesa per il completamento dei figli, altrimenti la richiesta di input del padre viene eseguita durante l'esecuzione dei figli, che stampano a video altri messaggi, creando confusione
      x = calcoli_X();             
    }

  printf(".. join: padre aspetta \n");
 
  waitpid(pid1, &retY, 0);              // join : il padre aspetta il figlio pid1 
  y = WEXITSTATUS(retY);                // prende il risultato del figlio
  printf("-> y = %d \n", y);
  printf("-> y = %d \n", retY>>8);      // shift a destra di 8 bit
                                        // WEXITSTATUS() restituisce gli 8 bit più significativi, equivale a retY>>8
 
  waitpid(pid2, &retZ, 0);              // join : il padre aspetta il figlio pid2 
  z = WEXITSTATUS(retZ);                // prende il risultato del figlio
  printf("-> z = %d\n", z);
  printf("-> z = %d \n", retZ>>8);
 
  // x = calcoli_X();               // alternativa: esecuzione non parallela calcoli padre

  ris = calcoli_P(x, y, z);             // esegue gli ultimi calcoli 
  printf("-> risultato finale ris = %d\n", ris);
  }
}

int calcoli_Y(int y) {
  int k;
  printf("1.1 elab. parallela processo figlio 1 \n");
  k = 5 - y;
  printf("-> y = %d\n", k);
 return k;
} 

int calcoli_Z(int z) {
  int k;
  sleep(1);
  printf("1.2 elab. parallela processo figlio 2 \n");
  k = 7 * z + 3;
  printf("-> z = %d\n", k);
  return k; 
}

int calcoli_X() {
  int k, x;
  printf("1 elab. parallela processo padre \n");
  printf ("inserisci valore per la variabile x: ");
  scanf ("%d", &x);
  k = 3 + x ;
  return k; 
}

int calcoli_P(int a, int b, int c) {
  int k;
  printf("2 elab. finale padre \n");
  k = (a - b * c);
  return k; 
}
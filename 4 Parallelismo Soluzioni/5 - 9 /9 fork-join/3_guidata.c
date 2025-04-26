#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//    (2 + x) * (3 + y) * (7 * z + 4) - 10   // x, y, z letti da input  
//       S2       S3        S4 
//  S5 = S2   *   S3    *   S4        - 10

// 000 -> 2        3        4         - 10 = 14  
// 110 -> 3        4        4         - 10 = 38
// 010 -> 2        4        4         - 10 = 22
// 100 -> 3        3        4         - 10 = 26

void segmento_S1(int* x, int* y, int* z); // input per riferimento
int segmento_S2(int x);                   // (2 + x)

int ramo34(int y, int z);                 // co-begin S3 e S4
int segmento_S3(int y);                   // (3 + y)
int segmento_S4(int z);                   // (7 * z + 4)
int risultato34(int y, int z);            // co-end S3 e S4

int segmento_S5(int x, int yz);

int main() { 
  int x, y, z;
  x = y = z = 0;
  int yz, ris, retv34;
  pid_t pid34;

  printf ("S1 (padre1) - pid = %d\n", getpid());
  segmento_S1(&x, &y, &z);
  printf("Nel padre1 -> x: %d, y: %d, z: %d\n", x, y, z);

  printf("fork esterna - \n" );
  if ((pid34 = fork()) == -1 )               // prima fork 
    printf(" fork non riuscita !" );          
  else
    if (pid34 == 0) {
      printf("  figlio1: pid = %d, padre pid = %d\n", getpid(), getppid());
      printf("  y: %d, z: %d\n", y, z);
      yz = ramo34(y, z);     // esecuzione fork processi 3 e 4  (S34)
      exit(yz);              // ritorna al padre 
    }
    else {                    // esecuzione ramo padre 
      printf(" S2 (padre1) - pid = %d\n",getpid());
      x = segmento_S2(x);

      printf(" wait fine ramo S34 (padre1 join figlio1) \n" );
      waitpid(pid34, &retv34 , 0);         // co-end  
      yz = WEXITSTATUS(retv34);            // prende il risultato del figlio

      printf("Fine attesa S34 \n" );
      
      printf("S5 (padre1) - pid = %d\n", getpid());
      ris = segmento_S5(x, yz);
	    printf("Risultato = %d\n", ris);
      exit( 0 );
    }
}

void segmento_S1 (int* x, int* y, int* z) {
  // fase di input delle variabili
  // Le variabili sono passate per riferimento per risparmiare memoria
  printf("S1 elab. padre1 prima della fork \n");
  printf ("Inserisci valore per la variabile x: ");
  scanf ("%d", x);
  // x è un puntatore, quindi è già un indirizzo, non bisogna usare l'operatore & in scanf
  printf ("Inserisci valore per la variabile y: ");
  scanf ("%d", y);
  printf ("Inserisci valore per la variabile z: ");
  scanf ("%d", z);
  printf("Nella funzione -> x: %d, y: %d, z: %d\n", *x, *y, *z);
  // x, y e z sono puntatori, quindi per stampare il loro valore bisogna dereferenziarli con l'operatore *
}
 
int segmento_S2 (int x) {
  int k;
  printf(" S2 elab. parallela padre1 \n");
  k = 2 + x;
  printf(" -> S2 = %d\n", k );
 return k;
}

int ramo34 (int y, int z) {
  int retv4;
  pid_t pid4;

  printf( "  fork - processi S34 -> creazione S4  \n" );
  if (( pid4 = fork() ) == -1 )
    printf( "    fork non riuscita !" );
  if (pid4 == 0 ){
    printf("    S4 (figlio2) - pid = %d, padre pid = %d\n", getpid(), getppid() );
    z = segmento_S4(z);
    exit (z);                              // ritorno al padre S3 
  }
  else {
    printf("   S3 (padre2) - pid = %d, padre pid = %d\n", getpid(), getppid() );
 	  y = segmento_S3(y);
    printf("   wait fine figlio S4 (padre2 join figlio2)  \n" );
    waitpid(pid4, &retv4 , 0);             // attesa fork interna
    z = WEXITSTATUS(retv4);                // prende il risultato del figlio
    printf("   Fine attesa S4 \n" );
  }
   
  printf(" Fine ramo S34 \n" );
  return risultato34 (y, z);               // risultato parziale finale (y * z) 
}

int segmento_S3 (int y) {
  int k;
  printf("   S3 elab. parallela figlio1 \n");
  k = 3 + y;
  printf("   -> S3 = %d\n", k);
  return k;
}

int segmento_S4 (int z) {
  int k;
  printf("    S4 elab. parallela figlio2 \n");
  k = 7 * z + 4;
  printf("    -> S4 = %d\n", k );
  return k; 
}

int risultato34 (int y, int z) {
  int k;
  printf(" S34 - fine S34  \n");
  k =  y * z ;
  printf(" -> S34 = %d\n", k);
  return k;
}

int segmento_S5 (int x, int yz) {
  int k;
  printf("S5 elab. finale padre1 \n");
  k = x * yz -10;
  printf("-> S5 = %d\n", k);
  return k;
}
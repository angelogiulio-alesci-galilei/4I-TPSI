#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int somma (int a, int b) {return a + b;}
int prodotto (int a, int b) {return a * b;}
int differenza (int a, int b) {return a - b;}

int prima ();
int seconda ();
int terza ();

int main () {
    pid_t pid1, pid2, pid3;
    int retv1, retv2, retv3;

    pid1 = fork();
    if (pid1 == 0)
        exit(prima());
    
    else {
    pid2 = fork();
    if (pid2 == 0)
        exit(seconda());
    
    else {
    pid3 = fork();
    if (pid3 == 0)
        exit(terza());
    
    else {
        waitpid(pid1, &retv1, 0);
        retv1 = WEXITSTATUS(retv1);
        waitpid(pid2, &retv2, 0);
        retv2 = WEXITSTATUS(retv2);
        waitpid(pid3, &retv3, 0);
        retv3 = WEXITSTATUS(retv3);
        printf("Risultati finali: %d, %d, %d\n", retv1, retv2, retv3); 
    }}}
}

int prima () {
    // 5 * [(2 + 4) * (7 + 3)] - 100
    // 5 * [   6    *    10  ] - 100
    // 5 *          60         - 100
    // 300                     - 100 = 200
    
    pid_t pid1, pid2;
    int retv1, retv2, ris;

    pid1 = fork();
    if (pid1 == 0)
        exit(somma(2, 4));
    
    else {
    pid2 = fork();
    if (pid2 == 0)
        exit(somma(7, 3));
    
    else {
        waitpid(pid1, &retv1, 0);
        retv1 = WEXITSTATUS(retv1);
        waitpid(pid2, &retv2, 0);
        retv2 = WEXITSTATUS(retv2); 
    }}

    printf("1) Risultati parziali: %d, %d\n", retv1, retv2);
    ris = prodotto(retv1, retv2);
    printf("1) Risultato parziale: %d\n", ris);
    ris = prodotto(5, ris);
    printf("1) Risultato parziale: %d\n", ris);
    ris = differenza(ris, 100);
    printf("1) Risultato finale: %d\n", ris);
    return ris;
}

int seconda () {
    // (3 + 2) * (5 + 7) + (8 - 3)
    //    5    *   12    +    5
    //         60        +    5     = 65
    
    pid_t pid1, pid2, pid3;
    int retv1, retv2, retv3, ris;
    
    pid1 = fork();
    if (pid1 == 0)
        exit(somma(3, 2));
    
    else {
    pid2 = fork();
    if (pid2 == 0)
        exit(somma(5, 7));
    
    else {
    pid3 = fork();
    if (pid3 == 0)
        exit(differenza(8, 3));
        
    else {
        waitpid(pid1, &retv1, 0);
        retv1 = WEXITSTATUS(retv1);
        waitpid(pid2, &retv2, 0);
        retv2 = WEXITSTATUS(retv2);
        waitpid(pid3, &retv3, 0);
        retv3 = WEXITSTATUS(retv3); 
    }}}
    
    printf("2) Risultati parziali: %d, %d, %d\n", retv1, retv2, retv3);
    ris = prodotto(retv1, retv2);
    printf("2) Risultato parziale: %d\n", ris);
    ris = somma(ris, retv3);
    printf("2) Risultato finale: %d\n", ris);
    return ris;
}

int terza () {
    // (3 + 2) * (5 - 2) + (8 - 3)
    //    5    *    3    +    5
    //         15        +    5     = 20
    
    pid_t pid1, pid2, pid3;
    int retv1, retv2, retv3, ris;
    
    pid1 = fork();
    if (pid1 == 0)
        exit(somma(3, 2));
    
    else {
    pid2 = fork();
    if (pid2 == 0)
        exit(differenza(5, 2));
    
    else {
    pid3 = fork();
    if (pid3 == 0)
        exit(differenza(8, 3));
        
    else {
        waitpid(pid1, &retv1, 0);
        retv1 = WEXITSTATUS(retv1);
        waitpid(pid2, &retv2, 0);
        retv2 = WEXITSTATUS(retv2);
        waitpid(pid3, &retv3, 0);
        retv3 = WEXITSTATUS(retv3); 
    }}}
    
    printf("3) Risultati parziali: %d, %d, %d\n", retv1, retv2, retv3);
    ris = prodotto(retv1, retv2);
    printf("3) Risultato parziale: %d\n", ris);
    ris = somma(ris, retv3);
    printf("3) Risultato finale: %d\n", ris);
    return ris;
}
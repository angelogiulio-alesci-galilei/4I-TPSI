#include <stdio.h>
#include <sys/wait.h>

/*
    Questo programma illustra il funzionamento di WEXITSTATUS e WTERMSIG
    che gestiscono gli stati di uscita dei processi in base al valore di status,
    che in questo caso viene simulato, in ordine crescente.
*/

#define MIN 0
#define MAX 256

int main () {
    int status;

    status = MIN;
    printf("Status vale %d, cioè 0000 in HEX, cioè 0000 0000 0000 0000 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
    printf("E' l'inizio del range xxxx xxxx 0000 0000 che rappresentano gli stati di terminazione volontaria\n");
    printf("Pertanto calcolare WTERMSIG è errato\n\n");

    status = MIN + 1;
    printf("Status vale %d, cioè 0001 in HEX, cioè 0000 0000 0000 0001 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
    printf("E' l'inizio del range 0000 0000 0xxx xxxx che rappresentano i segnali di terminazione involontaria\n");
    printf("Pertanto calcolare WEXITSTATUS è errato\n\n");

    status = MAX / 2 - 1;
    printf("Status vale %d, cioè 007F in HEX, cioè 0000 0000 0111 1111 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("WTERMSIG(status) = %d\n\n", WTERMSIG(status));
    printf("E' la fine del range 0000 0000 0xxx xxxx che rappresentano i segnali di terminazione involontaria\n");
    printf("Pertanto calcolare WEXITSTATUS è errato\n\n");

    status = (MIN + 1) * MAX;
    printf("Status vale %d, cioè 0100 in HEX, cioè 0000 0001 0000 0000 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("status/256 = %d\n", status / 256);
    printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
    printf("E' l'inizio del range xxxx xxxx 0000 0000 che rappresentano gli stati di terminazione volontaria\n");
    printf("Pertanto calcolare WTERMSIG è errato\n\n");

    status = (MAX - 1) * MAX;
    printf("Status vale %d, cioè FF00 in HEX, cioè 1111 1111 0000 0000 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("status/256 = %d\n", status / 256);
    printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
    printf("E' la fine del range xxxx xxxx 0000 0000 che rappresentano gli stati di terminazione volontaria\n");
    printf("Pertanto calcolare WTERMSIG è errato\n\n");
 
    status = (MAX - 1) * MAX + 1;
    printf("Status vale %d, cioè FF01 in HEX, cioè 1111 1111 0000 0001 in BIN\n", status);
    printf("WEXITSTATUS(status) = %d\n", WEXITSTATUS(status));
    printf("status >> 8 = %d\n", status >> 8);
    printf("status/256 = %d\n", status / 256);
    printf("WTERMSIG(status) = %d\n", WTERMSIG(status));
    printf("E' un esempio in cui ci sono valori diversi da zero sia nei bit riservati alla terminazione volontaria, sia in quelli riservati ai segnali di terminazione involontaria.\n");
    printf("Non accade davvero!\n");

    return 0;
}
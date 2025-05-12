#include <stdio.h>
#include <stdlib.h>

/*
    Per rendere più chiaro l'esempio non usiamo srand() in modo che i valori pseudocasuali
    generati siano sempre gli stessi
*/

int main () {
    int i, x, y[10];
    for (i = 0; i < 10; i++) {
        y[i] = rand();
        x = (int)(5.0 * y[i]/(RAND_MAX + 1.0));
        printf ("rand() = %d, RAND_MAX = %f, x = %d\n", y[i], RAND_MAX + 1.0, x);
    }
    return 0;
}
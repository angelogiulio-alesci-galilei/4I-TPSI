#include <stdio.h>

int main() {
    int a = 5, b = 3;

    // con il classico if
    if (a > b) {
        printf("Il massimo è: %d\n", a);
    } else {
        printf("Il massimo è: %d\n", b);
    }

    // con il costrutto ternario
    printf("Il massimo è: %d\n", (a > b) ? a : b);

    return 0;
}
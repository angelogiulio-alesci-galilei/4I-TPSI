#include <stdio.h>
#include <string.h>
#include <errno.h>

int main () {
    // Errore con stderr
    fprintf(stderr, "Messaggio che simula un errore scritto in stderr (e stampato a terminale). Richiede stdio.h\n\n");

    // Errore con strerror
    int err = 2; // Simula l'errore "No such file or directory"
    printf("Errore simulato con strerror: %s. Richiede string.h\n\n", strerror(err));
    
    // Errore con tutto + errno
    printf("Errore simulato con stderr, strerror e errno.\n");
    FILE *fp;
    fp = fopen ("nonExisting.txt", "r");    // Tentativo di apertura file non esistente
        if (fp == NULL) {
            fprintf(stderr, "Errore nell'apertura del file: %s\n", strerror(errno));
            return 1;
        }
    fclose(fp);
    
    return 0;
}
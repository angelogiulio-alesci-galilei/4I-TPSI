#include <stdio.h>
#include <sys/wait.h>

#define MIN_VOL 0
#define MAX_VOL 255
#define MIN_SIG 1
#define MAX_SIG 127

void stato(int *status);
void statoOut(int *status);
void segnale(int *status);
void segnaleOut(int *status);

int main() {
    int scelta, status;
    
    do {
        printf("\nMenu:\n");
        printf("0: Esci dal programma\n");
        printf("1: Simula uno stato di terminazione volontaria\n");
        printf("2: Simula un segnale di terminazione involontaria\n");
        printf("Inserisci scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 0:
                printf("Uscita dal programma.\n");
                break;
            case 1:
                stato(&status);
                statoOut(&status);
                break;
            case 2:
                segnale(&status);
                segnaleOut(&status);
                break;
            default:
                printf("Scelta non valida! Riprova.\n");
                break;
        }
    } while (scelta != 0);

    return 0;
}

void stato(int *status) {
    int input;
    do {
        printf("Inserisci un valore (0-255) per lo status volontario: ");
        scanf("%d", &input);
        if (input < MIN_VOL || input > MAX_VOL) {
            printf("Valore non valido! Riprova.\n");
        }
    } while (input < MIN_VOL || input > MAX_VOL);
    *status = input * 256;
}

void statoOut(int *status) {
    printf("\nTerminazione volontaria con stato simulata.\n");
    printf("Metodo WEXITSTATUS(status): %d\n", WEXITSTATUS(*status));
    printf("Metodo status/256: %d\n", *status / 256);
    printf("Metodo status >> 8: %d\n", *status >> 8);
}

void segnale(int *status) {
    int input;
    do {
        printf("Inserisci un segnale (1-127): ");
        scanf("%d", &input);
        if (input < MIN_SIG || input > MAX_SIG) {
            printf("Valore non valido! Riprova.\n");
        }
    } while (input < MIN_SIG || input > MAX_SIG);
    *status = input;
}

void segnaleOut(int *status) {
    printf("\nTerminazione involontaria simulata per segnale.\n");
    printf("Metodo WTERMSIG(status): %d\n", WTERMSIG(*status));
    printf("Metodo status %% 128: %d\n", *status % 128);
}
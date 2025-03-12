#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	/* messaggio di saluto in cinque lingue */
	char *messaggi[5];
	messaggi[0]="English: Hello World!";
	messaggi[1]="French: Bonjour, le monde!";
	messaggi[2]="Spanish: Hola al mundo";
	messaggi[3]="Italiano: Ciao mondo!";
	messaggi[4]="German: Guten Tag, Welt!";

	/* stampa del messaggio */
	int x = atoi(argv[1]);
	printf("%s\n", messaggi[x]);

}

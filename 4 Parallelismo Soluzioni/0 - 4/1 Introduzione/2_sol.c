#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main () {

	/* messaggio di saluto in cinque lingue */
	char *messaggi[5];
	messaggi[0]="English: Hello World!";
	messaggi[1]="French: Bonjour, le monde!";
	messaggi[2]="Spanish: Hola al mundo";
	messaggi[3]="Italiano: Ciao mondo!";
	messaggi[4]="German: Guten Tag, Welt!";

	/* stampa del messaggio */
	int i;
	for (i=0;i<5;i++)
		printf("%s\n", messaggi[i]);
	
	return 0;
}

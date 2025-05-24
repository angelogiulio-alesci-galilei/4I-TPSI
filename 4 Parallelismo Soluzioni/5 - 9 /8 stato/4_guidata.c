#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void child(char flag, int num, int num_chld);  // procedura che il figlio dovra' eseguire per generare i nipoti
void wait_child();                             // attesa della terminazione di un figlio

int main(int argc, char* argv[]){
	/*
		argc è il numero di argomenti passati al programma
		argv[] è un array di puntatori a carattere, cioè un array di stringhe
		argv[0] è il nome del programma
		Se gli argomenti sono passati in modo corretto:
		argv[1] è il flag
		argv[2] è il numero di figli da generare
		Da argv[3] in poi ci sono i numeri di figli da generare per ogni figlio
	*/

	int i=0,j=0,
		num_children, 	// numero di figli da generare
		pid;         	// pid del figlio generato
	char flag;
	/*
		flag per capire dove eseguire la wait: 
		flag==1 il padre attende la terminazione di un figlio prima di generare il successivo
		flag!=1 il padre attende la terminazione dei figli dopo averli generati tutti
	*/

	// controllo parametri

	/*
		Controllo che ci siano almeno 3 argomenti.
		Senza questo controllo, se l'utente non passa argomenti, il programma genera
		un errore di segmentazione (segmentation fault) quando, nel controllo successivo,
		cerca di accedere a argv[1].
	*/
	if (argc < 3) {
		printf("Errore di sintassi. Il comando deve essere: %s <flag> <num_cldr> <num_grandcldr>*\n", argv[0]);
		exit(-1);
	}

	/*
		verifica del flag
		la stringa che contiene il flag è argv[1]
		il flag vero e proprio è la prima lettera della stringa -> argv[1][0]
		deve essere '0' o '1', quindi se non è '0' o '1' esce con errore
	*/
	if(argv[1][0]!='0' && argv[1][0]!='1'){
		printf("Errore di sintassi. Il comando deve essere: %s <flag> <num_cldr> <num_grandcldr>*\n",argv[0]);
		exit(-1);
	}
	flag=argv[1][0];

	/*
		verifica di argv[2]
		argv[2] è il numero di figli da generare, quindi deve essere un numero intero positivo
		potrebbe avere più cifre, quindi non è sufficiente controllare che sia un carattere compreso tra '0' e '9'
		con strlen(argv[2]) si calcola la lunghezza della stringa argv[2]
		con il for si controlla che ogni carattere della stringa sia compreso tra '0' e '9'
	*/
	for(i=0; i<strlen(argv[2]); i++){
		if(argv[2][i]<'0' || argv[2][i]>'9'){
			printf("Errore di sintassi. Il comando deve essere: %s <flag> <num_cldr> <num_grandcldr>*\n",argv[0]);
			exit(-1);
			}
	}
	num_children=atoi(argv[2]); // conversione della stringa argv[2] in intero
	
	/*
		ora che conosciamo il numero di figli da generare, controlliamo che il numero di argomenti arcg sia corretto
		gli argomenti precedenti sono 3: argv[0], argv[1] e argv[2]
		quindi il numero di argomenti deve essere num_children+3
		se non è così, esce con errore
	*/
	if(argc!=num_children+3) {
		printf("Errore di sintassi. Il comando deve essere: %s <flag> <num_cldr> <num_grandcldr>*\n",argv[0]);
			exit(-1);
	}
	
	/*
		ora controlliamo che gli argomenti da argv[3] in poi siano numeri interi positivi
		esattamente come abbiamo fatto per argv[2]
		il ciclo esterno scorre gli argomenti da argv[3] all'ultimo
	*/
	for(i=3;i<num_children+3;i++){
		for(j=0;j<strlen(argv[i]);j++){
			if(argv[i][j]<'0' || argv[i][j]>'9'){
				printf("Errore di sintassi. Il comando deve essere: %s <flag> <num_cldr> <num_grandcldr>*\n",argv[0]);
				exit(-1);
			}
		}	
	}
	
	// con il ciclo for generiamo tutti i figli con fork()
	for(i=0;i<num_children;i++) {
		pid=fork();
		if(pid==0) { //figlio i-mo
			// ogni figlio chiama la funzione child() per generare i nipoti
			// passa il flag, il numero del figlio e il numero di nipoti da generare
			child(flag,i,atoi(argv[i+3]));
			exit(0); //exit da fare per sicurezza, nel caso di dimenticanze nel codice del figlio...
		}
		else if(pid>0) {
			printf("PADRE: Creato figlio (pid=%d)\n",pid);
			if(flag=='1') // se il flag è 1, i figli vengono generati in sequenza, quindi il padre attende la terminazione di un figlio prima di generare il successivo
				wait_child();
		}
		else {
			perror("Fork error:"); // errore nella creazione del figlio
			exit(1);
		}
	}	
	
	if(flag!='1') { // se il flag è diverso da 1, il padre attende la terminazione di tutti i figli DOPO averli generati
		for(i=0;i<num_children;i++)
			wait_child();
	}
	exit(0);
}


void child(char flag, int num, int num_chld) {
	int num_cmd, i, pid;
	
	for(i=0; i<num_chld; i++){
		pid=fork();
		if(pid==0) { //nipote i-mo
			printf("Nipote %d, figlio di %d\n",getpid(),getppid());
			exit(0); //exit da fare per sicurezza
		}
		else if(pid>0) {
			printf("Figlio %d: Creato nipote (pid=%d)\n",getpid(),pid);
			if(flag=='1')  // anche per i figli diventati padri vale lo stesso discorso del flag: se è 1, i nipoti vengono generati in sequenza, quindi il padre attende la terminazione di un nipote prima di generare il successivo
				wait_child();
		}
		else {
			perror("Fork error:"); // errore nella creazione del nipote
			exit(1);
		}
	}	
	
	if(flag!='1') { // se in parallelo, il figlio attende la terminazione di tutti i nipoti DOPO averli generati tutti
		for(i=0; i<num_chld; i++)
			wait_child();
	}
}

void wait_child() {
	int pid_terminated,status;
	pid_terminated=wait(&status);
		if(WIFEXITED(status))
			printf("\nPADRE: terminazione volontaria del figlio %d con stato %d\n",pid_terminated,WEXITSTATUS(status));
		else if(WIFSIGNALED(status))
			printf("\nPADRE: terminazione involontaria del figlio %d a causa del segnale %d\n",pid_terminated,WTERMSIG(status));
}

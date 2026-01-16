/* Programma in C pauseEalarm.c che ha bisogno di almeno due parametri: il primoe' il numero di minuti impostati per l'allarme e gli altri stringhe che verranno riportate sullo standard output; il processo padre genera un processo figlio e poi termina (simulando l'esecuzione in background), mentre il figlio aspettera' che scatti l'allarme */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define TRUE  1
#define FALSE 0
#define BELLS "\007\007\007"

/* funzione che verra' invocata alla ricezione del segnale SIGALRM */
void handler(int signo)
{
	printf("DEBUG-Processo con pid = %d ha ricevuto il segnale SIGALRM che e' il nro %d\n", getpid(), signo);
}

int main (int argc, char **argv)
{
   int pid;		/* per fork */
   int nmin, nsecs; 	/* per calcolo secondi */
   int j;		/* indice/contatore */

   	/* controllo sul numero di parametri: almeno due parametri, il primo numero di minuti e gli altri stringhe da stampare ==> controllo lasco! */
	if (argc < 3) 
	{ 	printf("Errore: Necessari almeno 2 parametri per %s e invece argc = %d\n", argv[0], argc);
		exit(1);
	}

	/* dobbiamo controllare che il primo parametro sia un numero strettamente positivo */
	if ((nmin=atoi(argv[1])) <= 0)
	{ 	printf ("Errore nel valore del tempo %s\n", argv[1]);
		exit(2);
	}
	/* ora convertiamo i minuti in secondi dato che la primitiva alarm vuole il parametro in secondi */
	nsecs = nmin * 60; 

	if ((pid = fork()) < 0)
	{
		/* fork fallita */
		 printf("Errore in fork\n");
		 exit(1);
	}

	if (pid == 0)
	{
		/* figlio */
		/* installa l'azione specifica da eseguire alla ricezione del segnale SIGALRM */
		signal(SIGALRM, handler);
		/* attiva l'allarme per il numero di secondi calcolato dal primo parametro (fornito in minuti) */
		alarm(nsecs);
		/* attende l'arrivo di un qualunque segnale */
		pause();
		/* se arriva un segnale, si suppone che sia quello dell'allarme e allora stampa su standard output le stringhe passate come parametri dal secondo in poi */
		printf(BELLS); /* viene suonata la 'campanella' per 3 volte */
		/* quindi stampiamo le stringhe passate dal secondo parametro in poi */
		for (j=2; j < argc; j++)
			printf("%s ", argv[j]);
		printf("\n");

		exit(0); 	/* figlio termina */
	}

	/* padre */
	printf("Creazione del processo %d\n", pid);

	/* padre termina: simulazione esecuzione in background */
	exit(0);
}

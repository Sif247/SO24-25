/* Soluzione della Prova d'esame del 5 Giugno 2015 - SOLO Parte C */
/* VERSIONE RIDOTTA SENZA CREAZIONE NIPOTI */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];	

int main(int argc, char **argv) 
{
   /* -------- Variabili locali ---------- */
   int pid;			/* process identifier per le fork() */
   int M; 			/* numero di file passati sulla riga di comando, che corrispondera' al numero di figli */
   pipe_t *piped;		/* array dinamico di pipe per comunicazioni figli-padre  */
   int j, k;			/* indici per i cicli */
   int lunghezza; 		/* variabile che viene comunicata da ogni figlio al padre */
   int status;			/* variabile di stato per la wait */
   int ritorno;                 /* variabile usata dal padre per recuperare valore di ritorno di ogni figlio */
   /* ------------------------------------ */
	
	/* controllo sul numero di parametri: almeno due nomi di file */
	if (argc < 3) 
	{
        	printf("Errore: Necessari almeno 2 parametri per %s e invece argc = %d\n", argv[0], argc);
		exit(1);
	}

	/* calcoliamo il numero di file passati e quindi di figli da creare */
	M = argc - 1;
	
	/* allocazione dell'array di M pipe */
	piped = (pipe_t *) malloc (M * sizeof(pipe_t));
	if (piped == NULL)
	{
		printf("Errore nella allocazione array dinamico per le pipe\n");
		exit(2);
	}
	
	/* creazione delle M pipe figli-padre */
	for (j=0; j < M; j++)
	{
		if(pipe(piped[j]) < 0)
		{
			printf("Errore nella creazione della pipe di indice n = %d\n", j);
			exit(3);
		}
	}

	printf("DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), M);
		
	/* ciclo di generazione dei figli */
	for (j=0; j < M; j++)
	{
		if ( (pid = fork()) < 0)
		{
		        printf("Errore creazione figlio %d-esimo\n", j);
			exit(4);
		}
		
		if (pid == 0) 
		{
			/* codice del figlio Pj */
			printf("DEBUG-Sono il processo figlio di indice %d e pid %d sto per creare il nipote che recuperera' l'ultima linea del file %s\n", j, getpid(), argv[j+1]);
			/*  in caso di errori nei figli o nei nipoti decidiamo di tornare dei numeri negativi (-1 che corrispondera' per il padre al valore 255, -2 che corrispondera' a 254, etc.) che non possono essere valori accettabili di ritorno per il comando tail */

			/* chiusura dei lati delle pipe non usate nella comunicazione con il padre */
			for (k=0; k < M; k++)
			{
				/* ogni figlio NON legge da nessuna pipe e scrive solo sulla sua che e' la j-esima! */
				close(piped[k][0]);
				if (k != j) close(piped[k][1]);
			}

			/* COMPITO SEMPLIFICATO FIGLIO, PER QUESTA VERSIONE RIDOTTA! */
			lunghezza=3000+j;

			/* il figlio comunica al padre */
			write(piped[j][1], &lunghezza, sizeof(lunghezza));

			/* dato che il figlio NON ha generato un nipote NON puo' recuperarne il valore di ritorno e quindi deciso di tornare 0 (SUCCESSO!) */
			exit(0);
		}
	}
	
	/* codice del padre */
	/* chiusura di tutti i lati delle pipe che non usa, cioe' tutti i lati di scrittura */
	for (j=0; j < M; j++)
		close(piped[j][1]);

	/* il padre recupera le informazioni inviate dai figli in ordine inverso di indice */
	for (j=M-1; j >= 0; j--)
	{
		/* il padre recupera tutti i valori interi dai figli */
		read(piped[j][0], &lunghezza, sizeof(lunghezza));
		printf("Il figlio di indice %d ha comunicato il valore %d per il file %s\n", j, lunghezza, argv[j+1]);
	}	

	/* il padre aspetta i figli */
	for (j=0; j < M; j++)
	{
		if ((pid = wait(&status)) < 0)
		{
			printf("Errore in wait\n");
			exit(5);
		}

		if ((status & 0xFF) != 0)
    			printf("Figlio con pid %d terminato in modo anomalo\n", pid);
    		else
		{ 	ritorno=(int)((status >> 8) & 0xFF); 
		  	if (ritorno != 0)
 				printf("Il figlio con pid=%d ha ritornato %d e quindi vuole dire che il nipote non e' riuscito ad eseguire il tail oppure il figlio o il nipote sono incorsi in errori\n", pid, ritorno);
		  	else  	printf("Il figlio con pid=%d ha ritornato %d\n", pid, ritorno);
		}
	}

	exit(0);
}

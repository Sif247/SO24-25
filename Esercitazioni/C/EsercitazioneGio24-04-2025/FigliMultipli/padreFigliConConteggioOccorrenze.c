/* Programma in C padreFigliConConteggioOccorrenze.c che ha bisogno di N+1 parametri (con N >= 2; primi N nomi file e ultimo singolo carattere Cx); padre deve generare N figli, ognuno associato ad un file (in ordine); ogni figlio deve contare quante occorrenze del carattere Cx ci sono nel proprio file associato e tornare tale conteggio (supposto strettamente minore di 255) al padre */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main (int argc, char **argv)
{
   char Cx;				/* carattere che i figli devono cercare nel file a loro associato */
   int N; 				/* numero di figli */
   int pid;				/* pid per fork */
   int n; 				/* indice per i figli */
   int totale=0; 			/* serve per calcolare il numero di occorrenze: in questo caso abbiamo usato un semplice int perche' la specifica dice che si puo' supporre minore di 255 */
   int fd; 				/* per la open */
   char c; 				/* per leggere i caratteri da ogni file; N.B. un carattere alla volta! */
   int pidFiglio, status, ritorno;	/* per valore di ritorno figli */

	/* controllo sul numero di parametri: almeno due nomi file e un carattere ==> controllo lasco! */
	if (argc < 4)
	{	
		printf("Errore: Necessari almeno 3 parametri per %s e invece argc = %d\n", argv[0], argc);
		exit(1);
	}

	/* controlliamo che l'ultimo parametro sia un singolo carattere, usando la funzione strlen */
	if (strlen(argv[argc-1]) != 1)
	{
        	printf("Errore ultimo parametro non singolo carattere dato che e' %s\n", argv[argc-1]);
        	exit(2);
	}

	/* individuiamo il carattere da cercare */
	Cx = argv[argc-1][0];

	/* individuiamo il numero di file e quindi di conseguenza il numero di processi */
	N=argc-2; 	/* ATTENZIONE dobbiamo togliere sia il nome dell'eseguibile che il carattere! */

	/* introdotto una stampa di DEBUG, che non era richiesta dalla specifica, in modo da controllare il valore di N e di Cx */
	printf("DEBUG-Sono il processo padre con pid %d e creero' %d processi figli che cercheranno il carattere %c nei file passati come parametri\n", getpid(), N, Cx); 

	/* creazione figli */
	for (n=0; n < N; n++)
	{
		if ((pid=fork())<0)
		{
			printf("Errore creazione figlio %d-esimo\n", n);
			exit(3);
		}
		if (pid==0)
		{ 	/* codice figlio */
			/* anche in questo caso abbiamo introdotto una stampa di DEBUG, che non era richiesta, per controllare indice e nome del file associato */
			printf("DEBUG-Sono il figlio %d di indice %d e sono associato al file %s\n", getpid(), n, argv[n+1]);

			/* apriamo il file (deleghiamo ad ogni processo figlio, il controllo che i singoli parametri (a parte l'ultimo) siano nomi di file */
			/* notare che l'indice che dobbiamo usare e' n+1 */
			/* in caso di errore decidiamo di ritornare -1 che sara' interpretato dal padre come 255 e quindi un valore non valido! */
			if ((fd = open(argv[n+1], O_RDONLY)) < 0)
			{	
				printf("Errore: FILE %s NON ESISTE o NON LEGGIBILE\n", argv[n+1]); 
				exit(-1);
			}	
			/* leggiamo il file */
			while (read (fd, &c, 1) != 0)
		         	if (c == Cx) totale++;     /* se troviamo il carattere incrementiamo il conteggio */
		
		 	/* ogni figlio deve tornare il numero di occorrenze e quindi totale */
			exit(totale);	
		}	
	} /* fine for */

	/* codice del padre */
	/* Il padre aspetta i figli */
	for (n=0; n < N; n++)
	{
        	if ((pidFiglio=wait(&status)) < 0)
        	{
                	printf("Errore in wait\n");
                	exit(4);
        	}
        	if ((status & 0xFF) != 0)
                	printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        	else
        	{ 
			ritorno=(int)((status >> 8) & 0xFF);
        		printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
        	} 
	}

	exit(0);
}

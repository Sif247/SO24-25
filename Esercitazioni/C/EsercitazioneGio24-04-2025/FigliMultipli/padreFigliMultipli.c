/* Programma in C padreFigliMultipli.c che ha bisogno di un solo parametro che deve essere un numero intero (strettamente maggiore di 0 e strettamente minore di 255) che rappresenta il numero di processi figli che devono essere generati */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char **argv)
{
    int N;                                  /* numero di figli */
    int pid;                                /* pid per fork */
    int n;                                  /* indice per i figli */
    int pidFiglio, status, ritorno;         /* per wait e valore di ritorno figli */

	/* controllo sul numero di parametri: esattamente uno */
	if (argc != 2)
	{
	        printf("Errore numero di parametri: %s vuole un singolo parametro (numero) e invece argc = %d\n", argv[0], argc);
	        exit(1);
	}

	/* convertiamo l'unico parametro in numero */
	N=atoi(argv[1]);
	if (N <= 0 || N >= 255) /* facciamo i controlli richiesti dalla specifica */
	{
	        printf("Errore l'unico parametro non e' un numero strettamente positivo o non e' strettamente minore di 255: %d\n", N);
	        exit(2);
	}

	printf("Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);

	/* creazione figli */
	for (n=0; n < N; n++)
	{
	        if ((pid=fork())<0)
	        {
	                printf("Errore creazione figlio %d-esimo\n", n);
	                exit(3);
	        }

		if (pid==0)
	        {       /* codice figlio */
	                printf("Sono il figlio %d di indice %d\n", getpid(), n);
	                /* ogni figlio deve tornare il suo indice ordine */
	                exit(n);
			/* al di la' del valore ritornato, e' ASSOLUTAMENTE INDISPENSABILE che ci sia la presenza di una exit per fare in modo che il processo figlio termini e NON esegua il ciclo for, che invece deve essere eseguito solo dal padre */
	        }
	} /* fine for */

	/* codice del padre */
	printf("DEBUG-Sono il processo padre con pid %d e, dato che ho finito di generare i miei %d figli, ora li posso aspettare uno per uno!\n", getpid(), N);

	/* Il padre aspetta i figli */
	for (n=0; n < N; n++)
	{
        	pidFiglio = wait(&status);
		if (pidFiglio < 0)
		{	printf("Errore in wait\n");
		        exit(4);
		}

		if ((status & 0xFF) != 0)
		        printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
		else
		{
		        ritorno=(int)((status >> 8) & 0xFF);
		        printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);
		}
	}

	exit(0);
}

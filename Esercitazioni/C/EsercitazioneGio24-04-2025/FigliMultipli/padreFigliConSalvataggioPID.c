/* Programma in C padreFigliConSalvataggioPID.c ha bisogno di un solo parametro che deve essere un numero intero (strettamente maggiore di 0 e strettamente minore di 155) che rappresenta il numero di processi figli che devono essere generati */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int mia_random(int n)
{  /* funzione che calcola un numero random compreso fra 1 e n (fornita nel testo) */
   int casuale;

	casuale = rand() % n;
	casuale++;
	return casuale;
}

int main (int argc, char **argv)
{
	int N; 					/* numero di figli */
	int *pid;				/* array dinamico di pid per fork */
	int n; 					/* indice per i figli */
	int j; 					/* indice per recuperare il numero d'ordine di creazione dei figli */
	int pidFiglio, status, ritorno;		/* per wait e valore di ritorno figli */

	/* controllo sul numero di parametri: esattamente uno */
	if (argc != 2)
	{
		printf("Errore numero di parametri: %s vuole un singolo parametro (numero) e invece argc = %d\n", argv[0], argc);
		exit(1);
	}

	/* convertiamo il parametro in numero */
	N=atoi(argv[1]);
	if (N <= 0 || N >= 155)  /* facciamo i controlli richiesti dalla specifica */
	{
		printf("Errore l'unico parametro non e' un numero strettamente positivo o non e' strettamente minore di 155: %d\n", N);
		exit(2);
	}
 
	/* allocazione pid */
	/* ATTENZIONE: non viene ammesso l'uso dei VARIABLE LENGHT ARRAY (VLA) */
	/* OSSERVAZIONE: abbiamo bisogno di questo array dinamico dato che la specifica richiede che il padre stampi, insieme con il valore di ritorno dei figli e PID, anche il numero d'ordine derivante dalla creazione! */
	if ((pid=(int *)malloc(N*sizeof(int))) == NULL)	/* bisogna sempre controllare che la malloc abbia avuto successo! */
	{
        	printf("Errore allocazione pid\n");
        	exit(3);
	}

	printf("Sono il processo padre con pid %d\n", getpid());
	srand(time(NULL)); 	/* inizializziamo il seme per la generazione random di numeri  */
	/* DA NOTARE CHE NEI TESTI DI ESAMI DOVE SI DEVE USARE LA GENERAZIONE RANDOM E' SCRITTO IN ESPLICITO CHI DEVE INIZIALIZZARE IL SEME E QUANDO: IN QUESTO CASO NON  E' SCRITTO ED E' STATO DECISO DI FARLO FARE AL PADRE PRIMA DI GENERARE I FIGLI */

	/* creazione figli */
	for (n=0; n < N; n++)
	{
		if ((pid[n]=fork())<0)	/* memorizziamo il pid del figlio corrente nel posto giusto dell'array dinamico! */
		{
			printf("Errore creazione figlio %d-esimo\n", n);
			exit(4);
		}

		if (pid[n]==0)
		{  /* codice figlio */
		   int r; 			/* per valore generato random */
			printf("Sono il figlio %d di indice %d\n", getpid(), n);
			r=mia_random(100+n); /* usiamo la funzione mia_random */

			/* ogni figlio deve tornare il numero random calcolato */ 	
			exit(r);
		}
	} /* fine for */

	/* codice del padre */

	/* Il padre aspetta i figli */
	for (n=0; n < N; n++)
	{
		if ((pidFiglio=wait(&status)) < 0)
        	{
                	printf("Errore in wait %d\n", pidFiglio);
                	exit(5);
        	}
        	if ((status & 0xFF) != 0)
                	printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        	else
        	{ 
			ritorno=(int)((status >> 8) & 0xFF);
			/* la specifica richiede che il padre, oltre il valore di ritorno e il PID, stampi anche il numero d'ordine e questo puo' essere fatto solo analizzando il contenuto dell'array di pid e riportando l'indice di tale array. ATTENZIONE CHE SAREBBE ASSOLUTAMENTE ERRATO ANDARE A STAMPARE L'INDICE DEL FOR ESTERNO! */
			for (j=0; j < N; j++)
				if (pidFiglio == pid[j])
				{
        				printf("Il figlio con pid=%d di indice %d ha ritornato %d\n", pidFiglio, j, ritorno);	/* attenzione a stampare j e NON i!!! */
					break; /* usiamo break perche' ci puo' essere un solo figlio con il pid appena trovato */
				}	
        	}	 
	}

	exit(0);
}

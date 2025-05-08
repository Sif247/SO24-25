/* Programma in C provaEsame2-b.c che ha bisogno di un nome di file, esistente e leggibile e di almeno due caratteri */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* versione con N pipe */

/* definizione del TIPO pipe_t come array di 2 interi */
typedef int pipe_t[2];

int main(int argc, char **argv)
{
   int pid;		/* pid per fork */
   int N; 		/* numero di caratteri e quindi numero di processi */
   int fdr; 		/* per open */
   int n;               /* indice processi */
   int k; 		/* indice */
   long int cont;	/* per conteggio */
   char c;		/* per leggere dal file */
   pipe_t *piped; 	/* array dinamico di pipe per comunicazioni figli-padre */
   int pidFiglio, status, ritorno;    /* variabili per wait*/
  
   /* controllo sul numero di parametri: un nome file e almeno due caratteri ==> controllo *  lasco! */
	if (argc < 4)
	{       printf("Errore: Necessari almeno 3 parametri (il nome di un file e almeno due caratteri) per %s e invece argc = %d\n", argv[0], argc);
    		exit(1);
  	}

  	/* numero dei caratteri passati sulla linea di comando che corrispondera' al numero di processi da creare */
  	N = argc - 2;	/* ATTENZIONE DOBBIAMO TOGLIERE 2, il nome del programma eseguibile e il nome del file */
  
  	/* controllo se singoli caratteri */
  	for (n=0; n < N; n++)
    	if (strlen(argv[n+2]) != 1)	/* ATTENZIONE: caratteri si trovano incrementando l'indice n di 2 */
    	{ 	printf("Errore nella stringa %s che non e' un singolo carattere\n", argv[n+2]); 
      		exit(2);
    	}

  	/* allocazione dell'array di N pipe */
  	piped = (pipe_t *)malloc(N * sizeof(pipe_t));
  	if (piped == NULL) 
  	{ 	printf("Errore nella allocazione array dinamico per le pipe\n");
      		exit(3);
  	}
  
  	/* creazione delle N pipe figli-padre */
  	for (n=0; n < N; n++)
    	if (pipe(piped[n]) < 0)
    	{ 	printf("Errore nella creazione della pipe di indice n = %d\n", n); 
      		exit(4);
    	}
 
  	printf("DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);
              
  	for (n=0; n < N; n++)
  	{
    		/* creazione dei figli */
    		if ((pid = fork()) < 0)
    		{
      			printf ("Errore nella fork\n");
      			exit(5);
    		}
    
    		if (pid == 0) /* figlio */
    		{
      			printf("DEBUG-Figlio %d con pid %d: sono associato al carattere %c\n", n, getpid(), argv[n+2][0]);
  
      			/* chiusura dei lati delle pipe non usati nella comunicazione con il padre */
      			for (k = 0; k < N; k++)
      			{	/* ogni figlio NON legge da nessuna pipe e scrive solo sulla sua che e' la n-esima! */
        			close(piped[k][0]);
        			if (k != n)
          				close(piped[k][1]);
      			}
      
      			/* ogni figlio apre lo stesso file: ATTENZIONE DI NON FARE QUESTA OPEN nel padre perche' altrimenti i figli condividerebbero il FILE POINTER e quindi non leggerebbero e controllerebbero tutti i caratteri! */
      			if ((fdr = open(argv[1], O_RDONLY)) < 0)
      			{ 	printf("Errore nella apertura del file %s\n", argv[1]);
        			exit(-1); 	/* torniamo -1 che verra' interpretato come 255 e quindi come errore */
      			}

      			cont = 0L; 	/* conta le occorrenze del carattere associato e quindi va inizializzato a 0 (come costante LONG!) */
      			while(read(fdr, &c, 1) > 0)	/* si legge il file un carattere alla volta fino alla fine */
      			{
        			if (c == argv[n+2][0])	/* se si e' trovato il carattere associato */
          				cont++;		/* si incrementa il contatore */
      			}

      			/* comunica al padre usando la n-esima pipe */
      			write(piped[n][1], &cont, sizeof(cont));
			/* NOTA BENE: essendo cont un long int NON si potrebbe mai pensare di passare questa informazione al padre con una exit */
                        exit(argv[n+2][0]);     /* torniamo il carattere cercato */
    		}
  	}
 
         /* dopo aver concluso il ciclo for di creazione di tutti i figli, si considera il resto del codice che deve eseguire il padre! */
  	/* padre */
  	/* chiude tutti i lati delle pipe che non usa, cioe' tutti i lati di scrittura */
  	for (n=0; n < N; n++)
  	{
    		close(piped[n][1]);
  	}

  	/* legge dalle pipe i messaggi */
  	for (n=0; n < N; n++)
  	{
    		if (read(piped[n][0], &cont, sizeof(cont)) > 0)
      			printf("Trovate %ld occorrenze del carattere %c nel file %s\n", cont, argv[n+2][0], argv[1]);	/* i long int si stampano con %ld */
  	}
  
	/* attesa della terminazione dei figli */
  	for (n=0; n < N; n++)
  	{
   		if ((pidFiglio = wait(&status)) < 0)
   		{
      			printf("Errore wait\n");
      			exit(6);
   		}
   		if ((status & 0xFF) != 0)
                	printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
   		else
   		{
                	ritorno=(int)((status >> 8) & 0xFF);
			printf("Il figlio con pid=%d ha ritornato %c (in decimale %d, se 255 problemi!)\n", pidFiglio, ritorno, ritorno); /* il padre stampa il valore ritornato come carattere; aggiunta la stampa come intero solo per intercettare un eventuale errore nel figlio */
   		}
  	} 

  	exit(0);                                              
}

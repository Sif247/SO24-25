/* Programma in C provaEsame2-a.c che ha bisogno di un nome di file, esistente e leggibile e di almeno due caratteri */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* versione con 1 pipe e uso di una struttura */
typedef struct 	{
	       		char c;         /* carattere controllato */
			long int n;     /* numero di occorrenze del carattere */
		} tipoS;

int main(int argc, char **argv)
{
   int pid;    		/* pid per fork */
   int N;    		/* numero di caratteri e quindi numero di processi */
   int fdr;     	/* per open */
   int n;     		/* indice processi */
   char c;      	/* per leggere dal file */
   int p[2];    	/* singola pipe */
   tipoS msg;		/* struttura per la comunicazione da figli a padre */
   int pidFiglio, status, ritorno;    /* variabili per wait*/
  
           /* controllo sul numero di parametri: un nome file e almeno due caratteri ==> controllo lasco! */
       	if (argc < 4)
	{       printf("Errore: Necessari almeno 3 parametri (il nome di un file e almeno due caratteri) per %s e invece argc = %d\n", argv[0], argc);
		exit(1);                                                         
  	}

  	/* numero dei caratteri passati sulla linea di comando che corrispondera' al numero di processi da creare */
  	N = argc - 2;	 /* ATTENZIONE DOBBIAMO TOGLIERE 2, il nome del programma eseguibile e il nome del file */

  	/* controllo se singoli caratteri */
  	for (n=0; n < N; n++)
    		if (strlen(argv[n+2]) != 1)	/* ATTENZIONE: caratteri si trovano incrementando l'indice n di 2 */
    		{ 	printf("Errore nella stringa %s che non e' un singolo carattere\n", argv[n+2]);
      			exit(2);
    		}

  	/* creazione della singola pipe */
  	if (pipe(p) < 0)
  	{ 	printf("Errore nella creazione della pipe\n"); 
    		exit(3);
  	}
  
  	printf("DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);
              
  	for (n=0; n < N; n++)
  	{
    		/* creazione dei figli */
    		if ((pid = fork()) < 0)
    		{
      			printf ("Errore nella fork\n");
      			exit(4);
    		}
    
    		if (pid == 0) /* figlio */
    		{
     		 	printf("DEBUG-Figlio %d con pid %d: sono associato al carattere %c\n", n, getpid(), argv[n+2][0]);
  
      			/* chiude il lato della pipe che non usa */
      			close(p[0]);
      
      			/* ogni figlio apre lo stesso file: ATTENZIONE DI NON FARE QUESTA OPEN nel padre perche' altrimenti i figli condividerebbero il FILE POINTER e quindi non leggerebbero e controllerebbero tutti i caratteri! */
      			if ((fdr = open(argv[1], O_RDONLY)) < 0)
      			{ 	printf("Errore nella apertura del file %s\n", argv[1]);
        			exit(-1);	/* torniamo -1 che verra' interpretato come 255 e quindi come errore */
      			}

      			/* inizializza la struttura */
      			msg.c = argv[n+2][0];	/* carattere associato */
      			msg.n = 0L;		/* contatore delle occorrenze (come costante LONG!) */
      			/* conta le occorrenze del carattere associato */
      			while(read(fdr, &c, 1) > 0)	/* si legge il file un carattere alla volta fino alla fine */
      			{
        			if (c == argv[n+2][0]) 	/* se si e' trovato il carattere associato */
          				msg.n++;	 /* si incrementa il contatore */
      			}	

      			/* comunica al padre */
      			write(p[1], &msg, sizeof(msg));
      			exit(argv[n+2][0]);	/* torniamo il carattere cercato */
    		}
  	}
  
	/* dopo aver concluso il ciclo for di creazione di tutti i figli, si considera il resto del codice che deve eseguire il padre! */
  	/* padre */
  	/* chiude il lato della pipe che non usa */
  	close(p[1]);
  
	/* legge dalla pipe i messaggi */
  	while (read(p[0], &msg, sizeof(msg)) > 0)	/* in questo caso si e' usato un while fino a che ci sono informazioni da leggere dalla unica pipe */
    		printf("Trovate %ld occorrenze del carattere %c nel file %s\n", msg.n, msg.c, argv[1]);	/* i long int si stampano con %ld */

  	/* attesa della terminazione dei figli */
  	for (n=0; n < N; n++)
  	{
   		if ((pidFiglio = wait(&status)) < 0)
   		{
      			printf("Errore wait\n");
      			exit(5);
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

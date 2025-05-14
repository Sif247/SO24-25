/* Programma in C figlio-zombieConStato.c che non ha bisogno di parametri e mostra l'uso della primitiva fork per la creazione di un processo figlio e della primitiva wait per l'attesa del figlio da parte del padre, con recupero del valore tornato dal figlio; a differenza del programma status1.c, il figlio termina subito e il padre prima di fare la wait si mette in attesa di un dato che deve fornire l'utente, per poter verificare lo stato ZOMBIE del processo figlio! */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
   int pid;                           	/* pid per fork */
   int pidFiglio, status, ritorno;    	/* per wait padre */
   int n;				/* per valore letto dal padre */

	/* si genera un processo figlio */
	if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	} 
	
	if (pid == 0) 
	{ 	/* figlio */ 
		printf("Esecuzione del figlio %d\n", getpid()); 
		/* facciamo terminare subito il figlio dato che ci serve termini PRIMA che il padre abbia effettuato la wait */
		exit(5);  /* abbiamo usato lo stesso valore del programma status1.c */
	}

	/* padre */
	printf("Ho generato il figlio %d\n", pid); 
	printf("Esecuzione del padre %d\n", getpid()); 
	/* per fare in modo che il padre non faccia subito la wait gli facciamo aspettare un dato che deve essere fornito dall'utente */
	printf("Fornisci un valore intero\n"); 
	scanf("%d", &n);
	printf("Numero letto dal padre %d\n", n); 
	/* ora possiamo aspettare il figlio */
	if ((pidFiglio=wait(&status)) < 0)
	{
		printf("Errore in wait\n");
		exit(2);
	}

	/* il padre analizza il valore di status per capire se il figlio e' terminato in modo anomalo cioe' involontario */
	if ((status & 0xFF) != 0)
    		printf("Figlio terminato in modo involontario (cioe' anomalo)\n");
    	else	/* oppure se e' terminato in modo normale e in tal caso recupera il valore ritornato */
    	{
    		/* selezione del byte "alto" */
		ritorno=(int)((status >> 8) & 0xFF);  
		/* stampa del valore 'pulito' ritornato dal figlio */
    		printf("Il figlio %d ha ritornato il valore intero %d\n", pidFiglio, ritorno);
    	}

	exit(0);
}

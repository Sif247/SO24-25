/* Programma in C status1.c che non ha bisogno di parametri e mostra l'uso della primitiva  fork per la creazione di un processo figlio e della primitiva wait per l'attesa del figlio da parte del padre, con recupero del valore tornato dal figlio */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

int main ()
{
     int pid; 				/* pid per fork */
     int pidFiglio, status, ritorno;    /* per wait padre */

	if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("Esecuzione del figlio\n");
		sleep(4); 	/* si simula con un ritardo di 4 secondi che il figlio faccia qualcosa! */
		exit(5);	/* si torna un valore che si suppone possa essere derivante dall'esecuzione di un compito assegnato al figlio */
	}

	/* padre */
	printf("Generato figlio con PID = %d\n", pid);

	/* il padre aspetta il figlio in questo caso interessandosi del valore della exit del figlio */
	if ((pidFiglio=wait(&status)) < 0)
	{
		printf("Errore in wait\n");
		exit(2);
	}

	/* il padre analizza il valore di status per capire se il figlio e' terminato in modo anomalo cio' involontario */
	if ((status & 0xFF) != 0)
    		printf("Figlio terminato in modo involontario (cioe' anomalo)\n");
    	else	/* oppure se e' terminato in modo normale e in tal caso recupera il valore ritornato */
    	{
    		/* selezione del byte "alto" */
    		ritorno = status >> 8;
    		ritorno &= 0xFF;
		/* o anche direttamente:
		ritorno=(int)((status >> 8) & 0xFF);  */
		/* stampa del valore 'pulito' ritornato dal figlio */
    		printf("Il figlio %d ha ritornato il valore intero %d\n", pidFiglio, ritorno);
    	}

	exit(0);
}

/* Programma in C provaValoriWait.c che, partendo dal programma status1.c (visto a lezione), aggiunge nel figlio una lettura dallo standard input di un valore intero, riportando una segnalazione di troncamento in caso di valore > di 255 o negativo oppure di non troncamento; il figlio deve tornare comunque in entrambi i casi tronare il valore letto al padre questo iconon ha bisogno di parametri e mostra l'uso della primitiva fork per la creazione di un processo figlio e della primitiva wait per l'attesa del figlio da parte del padre */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
     int pid;                           /* pid per fork */
     int pidFiglio, status, ritorno;    /* per wait padre */
     int valore;			/* valore per scanf da parte de figlio */

	if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("DEBUG-Esecuzione del figlio\n");
		/* questa volta facciamo fare qualche cosa al figlio */
		printf("Dammi un valore intero per provare la exit:\n");
		scanf("%d", &valore);
		if ((valore > 255) || (valore < 0)) 
			printf("ATTENZIONE IL VALORE SARA' TRONCATO!\n");
		else printf("Il valore fornito non verra' troncato!\n");
		exit(valore);
	}

	/* padre */
	printf("DEBUG-Generato figlio con PID = %d\n", pid);

	/* il padre aspetta il figlio in questo caso interessandosi del valore della exit del figlio */
	if ((pidFiglio=wait(&status)) < 0)
	{
        	printf("Errore in wait\n");
        	exit(2);
	}

	if ((status & 0xFF) != 0)
    		printf("Figlio terminato in modo involontario (cioe' anomalo)\n");
    	else
    	{
        	/* selezione del byte "alto" */
        	ritorno=(int)((status >> 8) & 0xFF);  
        	printf("Il figlio %d ha ritornato il valore intero %d\n", pidFiglio, ritorno);
    	}

	exit(0);
}

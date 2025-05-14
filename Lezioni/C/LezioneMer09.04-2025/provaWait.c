/* Programma in C provaWait.c che non ha bisogno di parametri e mostra l'uso della primitiva fork per la creazione di un processo figlio e della primitiva wait per l'attesa del figlio da parte del padre */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
   int pid, pidFiglio; /* pid per fork e pidFiglio per wait */

	if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("Esecuzione del figlio con PID = %d\n", getpid());
		sleep(4); 	/* si simula con un ritardo di 4 secondi che il figlio faccia qualcosa! */
		exit(5);	/* si torna un valore che si suppone possa essere derivante dall'esecuzione di un compito assegnato al figlio */
	}

	/* padre */
	printf("Generato figlio con PID = %d\n", pid);
	/* il padre aspetta il figlio disinteressandosi del valore della exit del figlio */
	/* N.B. Si deve controllare sempre il valore di ritorno della wait! */
	if ((pidFiglio=wait((int *)0)) < 0)
	{
		printf("Errore in wait\n");
		exit(2);
	}

	printf("Terminato figlio con PID = %d\n", pidFiglio);

	exit(0);
}

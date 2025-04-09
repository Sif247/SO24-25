/* Programma in C unoEdue.c che non ha bisogno di parametri e mostra l'uso della primitiva fork per la creazione di un processo figlio usando anche il valore di ritorno, come si dovra' fare SEMPRE */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
   int pid;

	printf("UNO\n");	/* l'unico processo (il padre) stampa la stringa "UNO" */

	if ((pid = fork()) < 0) /* l'unico processo (il padre) crea un processo figlio */
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("DUE\n");	/* stampa eseguita dal figlio */ 
		exit(0);		/* exit eseguita dal figlio */
	}
	/* dato che il codice del figlio ha almeno una exit al proprio interno, il codice che segue e' sicuramente eseguito solo dal padre (NON abbiamo bisogno dell'else) */
	/* PADRE */
	printf("Ho creato figlio con PID = %d\n", pid);	/* stampa eseguita dal padre */

	exit(0);	/* eseguito solo dal padre  */
}

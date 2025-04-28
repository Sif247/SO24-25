/* Programma in C provaSuid.c che non ha bisogno di parametri e mostra l'uso della primitiva execl  per la esecuzione dell'eseguibile leggiPippo1 che ha il SUID (Set-User-Id) settato */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
   int pid;        			/* per fork */
   int pidFiglio, status, ritorno;     	/* per wait padre */

	/* generiamo un processo figlio dato che stiamo simulando di essere il processo di shell! */
        if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		/* per prima cosa stampiamo i valori di UID reale ed effettivo del processo figlio: ricordiamo che questi sono 'ereditati' dal processo padre */
		printf("Real-user id = %d\n", getuid());
		printf("Effective-user id = %d\n", geteuid());
		printf("Esecuzione di programma leggiPippo1 (che ha il suid settato) che visualizza un file (pippo, leggibile solo dal proprietario)\n");
		execl("leggiPippo1", "leggiPippo1", (char *)0);
		/* si esegue l'istruzione seguente SOLO in caso di fallimento della execl */
		printf("Errore in execl\n");
		exit(-1); /* torniamo al padre un -1 che sara' interpretato come 255 e quindi identificato come errore */
	}

	/* padre aspetta subito il figlio perche' deve simulare la shell e la esecuzione in foreground! */
	if ((pidFiglio=wait(&status)) < 0)
	{
      		printf("Errore wait\n");
      		exit(2);
	}
	if ((status & 0xFF) != 0)
        	printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
	else
	{
       		ritorno=(int)((status >> 8) & 0xFF);
       		printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
	}

	exit(0);
}

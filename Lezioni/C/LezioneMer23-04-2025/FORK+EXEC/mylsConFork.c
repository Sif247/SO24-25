/* Programma in C mylsConFork.c che non ha bisogno di parametri e mostra l'uso della primitiva execlp per la esecuzione del comando ls da parte di un processo figlio (generato con fork e con il padre che attende la fine con wait) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
   int pid;				/* per fork */
   int pidFiglio, status, ritorno;	/* per wait padre */

	/* generiamo un processo figlio dato che stiamo simulando di essere il processo di shell! */
        if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("DEBUG-Esecuzione di ls -l da parte del figlio con pid %d\n", getpid());
		execlp("ls", "ls", "-l", (char *)0); /* il processo sotto-shell usa sempre la versione con p! */

		/* si esegue l'istruzione seguente SOLO in caso di fallimento della execlp */
		printf("Errore in execlp\n");
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
		/* se il figlio e' terminato in modo normale, recuperiamo il valore di ritorno che corrisponde in SHELL a stampare il valore della variabile $? */
       		ritorno=(int)((status >> 8) & 0xFF);
       		printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
	}	

	exit(0);
}

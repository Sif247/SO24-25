/* Programma in C mylsConFork1.c che ha bisogno di un solo parametro e mostra l'uso della primitiva execlp per la esecuzione del comando ls da parte di un processo figlio (generato con fork e con il padre che attende la fine con wait) applicato sul parametro passato */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char** argv)
{
   int pid;				/* per fork */
   int pidFiglio, status, ritorno;	/* per wait padre */

	/* controlliamo che si passi un solo parametro che verra' considerato come nome (assoluto/relativo alla directory corrente/relativo semplice) di un file o di una directory! */
        if (argc != 2)
        {
                printf("Errore nel numero di parametri che deve essere esattamente uno (nome di file o directory), mentre argc = %d\n", argc);
                exit(1);
        }

	/* generiamo un processo figlio dato che stiamo simulando di essere il processo di shell! */
        if ((pid = fork()) < 0)
	{ 	/* fork fallita */
		printf("Errore in fork\n");
		exit(2);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("DEBUG-Esecuzione di ls -l da parte del figlio con pid %d e con parametro %s\n", getpid(), argv[1]);
		execlp("ls", "ls", "-l", argv[1], (char *)0); /* il processo sotto-shell usa sempre la versione con p! */

		/* si esegue l'istruzione seguente SOLO in caso di fallimento della execlp */
		printf("Errore in execlp\n");
		exit(-1); /* torniamo al padre un -1 che sara' interpretato come 255 e quindi identificato come errore */
	}

	/* padre aspetta subito il figlio perche' deve simulare la shell e la esecuzione in foreground! */
        if ((pidFiglio=wait(&status)) < 0)
	{
      		printf("Errore wait\n");
      		exit(3);
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

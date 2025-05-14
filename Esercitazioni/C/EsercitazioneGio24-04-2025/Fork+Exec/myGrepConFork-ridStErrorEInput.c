/* Programma in C myGrepConFork-ridStErrorEInput.c che ha bisogno di DUE parametri (la stringa da cercare e il nome del file) e mostra l'uso della primitiva execlp per la esecuzione del comando grep da parte di un processo figlio, oltre che l'uso delle ridirezione su /dev/null (come fatto nella SHELL), in questo caso sia dello standard output che dello standard output e anche dello standard input usando il file passato come parametro, per avere solo il risultato di successo/insuccesso del comando-filtro grep! */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char** argv)
{
    int pid;        			/* per fork */
    int pidFiglio, status, ritorno;     /* per wait padre */

    	/* controlliamo che si passino esattamente due parametri: stringa da cercare nome del file dove cercare! */ 
	if (argc != 3)
	{
       		printf("Errore nel numero di parametri che devono essere esattamente due (stringa da cercare e nome del file dove cercare), mentre argc = %d\n", argc);
       		exit(1);	
	}

	/* generiamo un processo figlio dato che stiamo simulando di essere il processo di shell! */
        if ((pid = fork()) < 0)
	{	/* fork fallita */
		printf("Errore in fork\n");
		exit(2);
	}

	if (pid == 0)
	{ 	/* figlio */
		printf("DEBUG-Esecuzione di grep da parte del figlio con pid %d\n", getpid());

		/* ridirezionamo lo standard input in modo da leggere dal file passato come secondo parametro */
		close(0);
		if (open(argv[2], O_RDONLY))
		{ 	printf("Errore in apertura file %s\n", argv[2]);
			exit(-1); /* torniamo al padre un -1 che sara' interpretato come 255 e quindi identificato come errore */
		}

	/* ridirezionamo lo standard output su /dev/null perche' ci interessa solo se il comando grep ha successo o meno */
		close(1);
		open("/dev/null", O_WRONLY);

		/* ridirezionamo anche lo standard error su /dev/null perche' ci interessa solo se il comando grep ha successo o meno */
		close(2);
		open("/dev/null", O_WRONLY);
		
		/* ora invochiamo la primitiva execlp */
		execlp("grep", "grep", argv[1], (char *)0); /* in questo caso passiamo come parametro solo la stringa da cercare */

 		/* si esegue l'istruzione seguente SOLO in caso di fallimento della execlp */
		/* ATTENZIONE SE LA EXEC FALLISCE NON SI PUO' USARE printf("Errore in execlp\n"); e NON si puo'² usare write(2, "ERRORE IN EXEC\n", 15); DATO CHE SIA LO STANDARD OUTPUT CHE L'ERROR SONO RIDIRETTI SU /dev/null */
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
       		ritorno=(int)((status >> 8) & 0xFF);
       		printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
		if (ritorno == 0) /* verifichiamo il successo del comando grep */
       			printf("Quindi, il figlio %d ha trovato la stringa %s nel file %s\n", pidFiglio, argv[1], argv[2]);
		else
       			printf("Quindi, il figlio %d NON ha trovato la stringa %s nel file %s oppure il file %s non esiste\n", pidFiglio, argv[1], argv[2], argv[2]);
	}	

	exit(0);
}

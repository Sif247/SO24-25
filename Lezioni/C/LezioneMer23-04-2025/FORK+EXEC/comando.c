/* Programma in C comando.c che non ha bisogno di parametri e rappresenta un 'embrione' di una SHELL, con la semplice esecuzione di comandi che non hanno bisogno di parametri o di opzioni (quindi senza uso di metacaratteri e di ridirezione/poping) e il solo funzionamento in foreground; si fara' un uso massivo della funzione perror (che scrive sullo standard error!) e della variabile globale errno */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main  (int argc, char **argv) 
{	
   int pid;        			/* per fork */
   int pidFiglio, status, ritorno;      /* per wait padre */
   char st[80];				/* array di caratteri per leggere (da standard input) il comando (SENZA OPZIONI O PARAMETRI) immesso dall'utente */

	for (;;) 	/* ciclo infinito: stiamo simulando una shell che deve restare sempre in attesa di un comando */
	{ 
		printf("Inserire il comando da eseguire:\n"); 	/* rappresenta la simulazione del prompt dei comandi */
		scanf("%s", st);				/* leggiamo il comando da standard input: in questo embrione, il comando (ESTERNO) non deve prevedere opzioni o parametri! */
		/* una volta che la nostra SHELL simulata riceve un comando, delega un processo per eseguirlo (come fa la SHELL!) */
		if ((pid = fork()) < 0) 	/* solito controllo che la fork NON fallisca */ 
		{ 	perror("Errore fork"); 
			exit(errno);
		}

		if (pid == 0) 
		{	/*  FIGLIO: esegue i comandi */
			execlp(st, st, (char *)0);		/* mandiamo in esecuzione il comando (ESTERNO) come fa la SHELL figlia */
			perror("Errore esecuzione comando");	/* se si torna qui vuole dire che la execlp e' fallita! */
			exit(errno); 				/* torniamo il valore della variabile globale errno */
		}

		/* padre aspetta subito il figlio, dato che siamo simulando l'esecuzione in foreground */
		if ((pidFiglio = wait(&status)) < 0)
		{
      			perror("Errore wait");
      			exit(errno);
		}
		if ((status & 0xFF) != 0)
        		printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
		else
		{
       			ritorno=(int)((status >> 8) & 0xFF);
       			printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);	/* con questa stampa e' come se stessimo eseguendo echo $? */
			/* se siamo arrivati qui vuole dire che tutto e' andato bene e quindi chiediamo all'utente se si vuole proseguire: in caso non si voglia proseguire, stiamo simulando il comando interno exit! */
			printf ("Vuoi eseguire un altro comando? (si/no) \n"); 
			scanf ("%s", st);
			if (strcmp(st, "si"))	/* se si inserisce la stringa "si" la strcmp tornera' 0 e quindi NON si eseguira' l'exit: qualunque risposta diversa da "si" in realta' comportera' la terminazione! */ 
				exit(0); /* se l'utente non vuole proseguire terminiamo tornando il valore 0 (successo) e quindi questo ci fa uscire dal ciclo infinito */
			/* altrimenti rimaniamo all'interno del ciclo for infinito */
		}
	}
}

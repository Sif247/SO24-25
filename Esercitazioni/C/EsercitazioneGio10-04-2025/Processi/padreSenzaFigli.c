/* File padreSenzaFigli.c che non ha bisogno di parametri e in cui il padre NON crea alcun processo figlio, ma esegue la primitiva wait, che chiaramente riportera' un ERRORE! */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main ()
{
   int pidFiglio;  /* per valore di ritorno della wait */

	/* stampiamo quanto richiesto dal testo */
	printf("Sono il processo padre con pid %d\n", getpid());

	/* padre (!?!) */
        if ((pidFiglio=wait((int *)0)) < 0)	 /* in questo caso si e' usata la wait disinteressandoci del valore di ritorno dato che avremo errore! */
	/* nonostante questo processo non abbia creato figli, invoca la primitiva wait; chiaramente il codice potrebbe essere, 'a monte', molto piu' complicato e potrebbe essere NON chiaro il fatto che non e' stato creato alcun processo figlio: quindi bisogna sempre controllare il valore di ritorno della wait! */
	{
		printf("ERRORE nella wait %d\n", pidFiglio);
		exit(1);
	}
	
	exit(0);	/* chiaramente in questo caso NON si eseguira' mai questa istruzione, dato che si uscira' sempre con errore */
}

/* Programma in C  mylsErrato.c che non ha bisogno di parametri e mostra l'uso della primitiva execl per la esecuzione del comando ls1 che pero' NON esiste! */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	printf("DEBUG-Esecuzione di ls: versione ERRATA!\n");  
	execl("/bin/ls1", "ls", "-l", (char *)0); 	/* abbiamo scritto il nome di un eseguibile che NON esiste scorretto e quindi la execl fallira' */

	/* si esegue l'istruzione seguente SOLO in caso di fallimento della execl */
	printf("Errore in execl\n");
	exit(1); 	 /* torniamo quindi un valore diverso da 0 per indicare che ci sono stati dei problemi */
}

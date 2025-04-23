/* Programma in C myls2.c che non ha bisogno di parametri e mostra l'uso della primitiva execl per la esecuzione del comando ls */ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	printf("DEBUG-Esecuzione di ls: seconda versione\n");  
	execl("/bin/ls", "ls", "-l", (char *)0);	/* vale lo stesso commento fatto nella versione precedente riguardo alla 'posizione' dell'eseguibile di ls! */

	/* si esegue l'istruzione seguente SOLO in caso di fallimento della execl */
	printf("Errore in execl\n");
	exit(1);  	/* torniamo quindi un valore diverso da 0 per indicare che ci sono stati dei problemi */
}

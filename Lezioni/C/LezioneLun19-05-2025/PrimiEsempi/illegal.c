/* Programma in C illegal.c che non ha bisogno di parametri e mostra un esempio del segnale SIGILL che viene mandato dal kernel quando usiamo una zona di memoria che non fa parte dello spazio di indirizzamento del processo */
#include <stdio.h>
#include <stdlib.h>

char *s=(char *)64000;  /* istruzione assolutamente ERRATA solo per incorrere nell'errore che produce l'invio, da parte del kernel, del segnale SIGILL */

int main()
{
	printf("SONO UN PROGRAMMA CHE VA IN ERRORE e DOVREBBE CREARE UN CORE\n");
	printf("Dammi una stringa\n");
	printf("ATTENZIONE NON ABBIAMO ALLOCATO LA MEMORIA PER LA STRINGA\n");
	scanf("%s", s);
	printf("Non si arrivera' mai qui!!!!!!\n");

	exit(0);
}

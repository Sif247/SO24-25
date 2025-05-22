/* Programma in C loop.c che non ha bisogno di parametri e mostra un esempio del segnale SIGINT che viene mandato dal kernel quando usiamo la combinazione di tasti CTRL-C */
#include <stdio.h>

/* ricordarsi di invocare questo programma usando la ridirezione dello standard output su /dev/null */

int main()
{
	printf("SONO UN PROGRAMMA CHE VA IN LOOP\n");
	while (1)
		printf("Sono nel ciclo\n");
}

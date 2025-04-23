/* Programma in C myecho.c che ha bisogno di parametri (almeno uno) e visualizza tali parametri sullo standard output, compreso il nome dell'eseguibile stesso */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
   int i; 	/* indice per for */

 	/* controllo numero di parametri */
        if (argc == 1)
	{ 	printf("Errore ci vogliono dei parametri (almeno uno) invece argc = %d\n", argc); 
		exit (1);
	}

	printf("DEBUG-Sono myecho\n");	
	/* Riportiamo su standard output tutti i parametri di invocazione (oltre che il nome del programma eseguibile stesso) */
	for (i=0; i < argc; i++)
		printf("Argomento argv[%d]= %s\n", i, argv[i]);

	exit(0);
}

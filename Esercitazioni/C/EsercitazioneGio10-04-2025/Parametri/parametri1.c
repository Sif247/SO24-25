/* File parametri1.c che stampa il nome dell'eseguibile, il numero (variabile) di parametri e ogni singolo parametro  */
#include <stdio.h>
#include <stdlib.h>

int main  (int argc, char **argv)
{ 	
   int n; 	/* n serve per scorrere i parametri */
   int N; 	/* N serve per salvare il numero dei parametri */

	/* controllo numero di parametri */
	if (argc < 2) 	/* controllo lasco: ci deve essere almeno un parametro e quindi argc deve essere >= 2, altrimenti errore */
	{ 	
		printf("Errore: Necessario almeno 1 parametro per %s e invece argc = %d\n", argv[0], argc); 
		exit(1); 
	}

	/* salviamo, come richiesto il numero di parametri nella varibile di nome N */
	N = argc - 1; 	/* ricordarsi che argc conta sempre anche il nome dell'eseguibile */

	printf("Eseguo il programma %s con %d parametri\n", argv[0], N); 

	for (n = 0; n < N; n++)	 /* facciamo partire l'indice del for da 0 e poi usiamo pero' n+1: il perche' di questa scelta sara' chiaro in seguito! */
		printf ("Il parametro di indice %d e' %s\n", n+1, argv[n+1]);

	exit(0);	
}

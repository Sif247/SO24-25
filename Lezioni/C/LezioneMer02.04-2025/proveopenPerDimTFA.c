/* Programma in C proveopenPerDimTFA.c che ha bisogno di un solo nome di file leggibile e verifichera' il comportamento delle primitive open eseguendo un ciclo infinito che portera' a saturazione la TFA! */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{       
        int i=0; 	/* variabile contatore usata dentro il ciclo 'teoricamente' infinito */
	int fd;		/* variabile per valore di ritorno open */

	if (argc != 2) 	 /* per prima cosa (come negli script) controlliamo il numero di parametri ==> ce ne deve essere esattamente 1 e quindi dato che argc conta anche il comando stesso (arvg[0]) controlliamo se argc e' diverso da 2! */
	{       printf("Errore nel numero di parametri: ho bisogno di 1 parametro, ma argc = %d\n", argc);
		exit(1);        /* in caso di errore (esattamente come negli script) dobbiamo uscire tornando sempre un numero diverso! */
	}

       	/* se si arriva qui, e' stato passato esattamente 1 parametro */
	while (1)	/* ciclo infinito */
	{ 	
		if ((fd = open(argv[1], O_RDONLY)) < 0)	/* OSSERVAZIONE: apriamo sempre lo stesso file per verificare la dimensione della tabella dei file aperti del singolo processo! */
		{       printf("Errore in apertura file dato che fd = %d\n", fd);
		/* dopo aver segnalato l'errore e prima di uscire stampiamo il valore corrente dell'indice */
			printf("Valore di i = %d\n", i);
                	exit(2);	/* si esce dal ciclo solo quando si avra' un errore nella open che derivera', nel nostro caso, solo dall'esaurimento dello spazio nella tabella dei file aperti del processo! */ 
		}
		i++;	/* ad ogni iterazione incrementiamo l'indice: si eseguira' questo incremento solo in caso di successo della open! */
	}

	exit(0);
}

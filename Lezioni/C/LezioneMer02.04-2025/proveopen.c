/* Programma in C proveopen.c che ha bisogno di tre nomi di file leggibili e verifichera' il comportamento delle primitive open e close */
#include <stdio.h> 	/* per poter usare printf e altre funzioni di I/O */
#include <stdlib.h>	/* per poter usare la primitiva exit */
#include <unistd.h>	/* per poter usare la primitiva close */
#include <fcntl.h>	/* per poter usare le costanti per la open (O_RDONLY, O_WRONLY e O_RDWR)*/

int main(int argc, char **argv)
{       
        int fd1, fd2, fd3;	/* variabili per valore di ritorno open */
	/* N.B.: 1) i commenti, in generale, verranno sempre indicati in questo modo;
	         2) la parte di definizione delle variabili (se locali al main o ad altre funzioni) verra' sempre riportata prima di qualunque istruzione; questo consente di concentrare in un solo punto TUTTE le definizioni delle varibili con i rispettivi commenti e semplifica il controllo sui nomi usati e sui tipi usati! */

	if (argc != 4) 		/* per prima cosa (come negli script) controlliamo il numero di parametri ==> ce ne devono essere esattamente 3 e quindi dato che argc conta anche il comando stesso (arvg[0]) controlliamo se argc e' diverso da 4! */
	{ 	printf("Errore nel numero di parametri: ho bisogno di 3 parametri, ma argc = %d\n", argc);
		exit(1); 	/* in caso di errore (esattamente come negli script) dobbiamo uscire tornando sempre un numero diverso! */
	}
	/* NOTA BENE: non serve l'else perche' in caso di errore si fa la exit! */

	/* se si arriva qui, sono stati passati esattamente 3 parametri, che supponiamo siano nomi di file esistenti e leggibili! */

	/* tentiamo l'apertura in lettura del file il cui nome e' stato passato come primo parametro */
	if ((fd1 = open(argv[1], O_RDONLY)) < 0)  	/* dobbiamo sempre controllare il valore di ritorno delle open: ATTENZIONE ALLE PARENTESI! */
	/* N.B. Unix controllera' i diritti del file rispetto al processo in esecuzione controllando UID e GID effettivi (che si trovano nel descrittore di processo) nei confronti di UID e GID del file (che si trovano nell'Inode)! */
	/* Questa operazione servira' nei compiti per verificare esistenza e leggibilita' dei file che dovranno essere usati dai processi che risolveranno un qualche problema */
	{ 	printf("Errore in apertura file per %s dato che fd1 = %d\n", argv[1], fd1);
        	exit(2); 
	}	
	/* NOTA BENE: non serve l'else perche' in caso di errore si fa la exit! */
	/* se arriviamo qui siamo riusciti ad aprire il primo file perche' esisteva e il processo corrente aveva il diritto di lettura, quindi stampiamo il valore tornato dalla open */
	printf("Valore di fd1 = %d per %s\n", fd1, argv[1]);
	
	/* tentiamo l'apertura in lettura del file il cui nome e' stato passato come secondo parametro */
	if ((fd2 = open(argv[2], O_RDONLY)) < 0)	/*  apriamo un altro file per verificare che verra' usato un altro elemento della tabella dei file aperti del singolo processo! */
	{ 	printf("Errore in apertura file per %s dato che fd2 = %d\n", argv[2], fd2);
        	exit(3); 
	}
	/* NOTA BENE: non serve l'else perche' in caso di errore si fa la exit! */
	/* se arriviamo qui siamo riusciti ad aprire anche il secondo file perche' esisteva e il processo corrente aveva il diritto di lettura, quindi stampiamo il valore tornato dalla open */
	printf("Valore di fd2 = %d per %s\n", fd2, argv[2]);

	close(fd1);	/* chiudiamo e quindi eliminiamo le informazioni relative all'elemento della tabella dei file aperti identificato da fd1 */

	/* tentiamo l'apertura in lettura del file il cui nome e' stato passato come terzo parametro */
	if ((fd3 = open(argv[3], O_RDONLY)) < 0)	/* apriamo un ulteriore file per verificare che verra' riutilizzato l'elemento appena liberato della tabella dei file aperti del singolo processo! */
	{ 	printf("Errore in apertura file per %s dato che fd3 = %d\n", argv[3], fd3);
        	exit(4); 
	}
	/* NOTA BENE: non serve l'else perche' in caso di errore si fa la exit! */
	/* se arriviamo qui siamo riusciti ad aprire anche il terzo file perche' esisteva e il processo corrente aveva il diritto di lettura, quindi stampiamo il valore tornato dalla open */
	printf("Valore di fd3 = %d per %s\n", fd3, argv[3]);

	/* se arriviamo qui abbiamo finito e quindi terminiamo l'esecuzione in modo esplicio con una exit usando il valore 0, che - ricordiamo - in UNIX significa SUCCESSO; potevamo usare anche return 0, ma dato che siamo a livello di programmazione di sistema è più opportuno usare la primitiva exit, anche perche' se fossimo in un'altra funzione, invece che nel main, l'effetto NON sarebbe equivalente! */
	exit(0);
}
